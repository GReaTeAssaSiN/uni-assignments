#include "passprocessor.h"

#include "StructAssemblerLine.h"
#include "codeoperationtable.h"
#include "symbolicnamestable.h"
#include "AdditionalListOfSymbolicNames.h"
#include "checks.h"
#include "convert.h"

#include <vector>
#include <QTableWidget>
#include <QTextEdit>
#include <QString>
#include <QTextCursor>

bool PassProcessor::Pass(QTextEdit* textEdit_Errors, const std::vector<AssemblerInstruction>& textEdit_source, const CodeOperationTable& opCode_table,
                              std::vector<OneSymbolicName>& list_of_symb_names, QTableWidget* tableWidget_ToSN, SymbolicNamesTable& symb_table,
                              const bool& all_iters, size_t& step, QTextEdit* binaryCode_text)
{
    if (all_iters)
    {
        //Построчно обрабатываем каждую строку исходной программы.
        for (size_t i{ step }; i < textEdit_source.size(); ++i)
        {
            if(!OneStep(textEdit_Errors, textEdit_source, opCode_table, list_of_symb_names, tableWidget_ToSN, symb_table, i, binaryCode_text))
                return false;
        }
    }
    else
    {
        if (!OneStep(textEdit_Errors, textEdit_source, opCode_table, list_of_symb_names, tableWidget_ToSN, symb_table, step, binaryCode_text))
            return false;
    }
    //Если все хорошо - выход.
    return true;
}

bool PassProcessor::OneStep(QTextEdit *textEdit_Errors, const std::vector<AssemblerInstruction> &textEdit_source, const CodeOperationTable &opCode_table,
                            std::vector<OneSymbolicName> &list_of_symb_names, QTableWidget *tableWidget_ToSN, SymbolicNamesTable &symb_table, size_t &i,
                            QTextEdit* binaryCode_text)
{
    if (i == 0)
    {
        tableWidget_ToSN->setColumnCount(3);
        tableWidget_ToSN->setRowCount(1);

        /*Адреса (хранятся в 10-ичной системе).*/
        //Счетчик адреса (СА).
        this->addressCounter = 0;
        //Адрес загрузки программы.
        this->start_prog_address = 0;
        //Адрес точки входа в программу.
        this->end_prog_address = 0;
        //Флаги для учета найденных директив START и END.
        start_dir_flag = false;
        end_dir_flag = false;

        //Проверка ТКО.
        if (!check.CorrectTableCodeOperation(opCode_table, textEdit_Errors))
            return false;
    }
    if (i > 0 && !start_dir_flag){
        textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Не обнаружена директива START!\n");
        return false;
    }
    //Извлекаем текущую инструкцию.
    const AssemblerInstruction instruction = textEdit_source[i];
    //Переменные для записи двоичного представления команд и данных (адрес метки, число, строка и тд.).
    QString binary_opCode{};
    QString data{};
    /*------------------------------------------------------------------------------------------------------------
    * 1. Разбиваем строку на составляющие: Метка | МКОП | Операндная часть (операнд 1 | операнд 2 (опционально)).|
    -------------------------------------------------------------------------------------------------------------*/
    QString label = instruction.label.value_or("");
    QString mnemonic = instruction.mnemonic.toUpper();
    QString operand1 = instruction.operand1;
    QString operand2 = instruction.operand2.value_or("");
    //Наличие метки.
    bool label_flag{false};

    //Если найдена директива START, то имеет смысл проверять СА на допустимость.
    if (this->start_dir_flag)
    {
        //Адрес загрузки программы записан в СА и необходимо проверить, чтобы СА не выходил за максимальный допустимый объем памяти (0xFFFFFF).
        if (!check.CheckAddressCounterAvailable(textEdit_Errors, i, this->addressCounter))
            return false;
    }
    //Если найдена директива END - выход.
    if (this->end_dir_flag)
        return true;

    //Проверка строки исходного текста программы на корректность.
    if (!check.CheckRowSourceCode(textEdit_Errors, i, this->prog_name, label, mnemonic, opCode_table))
    {
        return false;
    }
    /*------------------------
     * 2. Поиск метки в ТСИ. |
    ------------------------*/
    //Название программы опускается за счет флага start_flag далее.
    //Найдена существующая метка.
    QString address{};
    if (symb_table.find(label, address))
    {
        textEdit_Errors->append("Строка ТСИ " + QString::number(i + 1) + ": Дважды определенное символическое имя " + label + ".\n");
        return false;
    }
    else
    {
        //Если метка не пустая и встречена после нахождения директивы START, то добавляем в ТСИ.
        //Метка корректная.
        if (!label.isEmpty() && this->start_dir_flag)
        {
            symb_table.insert(label, Convert::DecToHex(this->addressCounter).rightJustified(6, '0'));
            this->TManager.LoadOneLineToSymbolicNamesTable(tableWidget_ToSN, symb_table, label);
            label_flag = true;
            if (!list_of_symb_names.empty())
            {
                // Перебираем элементы вектора
                for (size_t i{}; i < list_of_symb_names.size(); i++) {
                    if (list_of_symb_names[i].name == label) {
                        // Проходим по всем строкам таблицы
                        for (int row = tableWidget_ToSN->rowCount() - 1; row >= 0; --row) {
                            // Проверяем, совпадает ли значение в первом столбце с элементом
                            QTableWidgetItem* item = tableWidget_ToSN->item(row, 0);
                            if (item && item->text() == label) {
                                tableWidget_ToSN->removeRow(row); // Удаляем строку
                            }
                        }

                        symb_table.insert(label, Convert::DecToHex(this->addressCounter).rightJustified(6, '0'));
                        this->TManager.LoadOneLineToSymbolicNamesTable(tableWidget_ToSN, symb_table, label);
                        replaceLineWithUnknownSN(
                            binaryCode_text,
                            "#" + label + "#",
                            Convert::DecToHex(this->addressCounter).rightJustified(6, '0')
                            );
                        list_of_symb_names.erase(list_of_symb_names.begin() + i);
                    }
                }
            }
        }
        /*---------------------------
        * 3. Анализируем поле МКОП |
        ---------------------------*/
        //Если поле МКОП пустое, то ошибка. Иначе продолжаем...
        if (!mnemonic.isEmpty())
        {
            //Проверяем - это директива?
            QString current_mnemonic_code = check.CheckDirective(mnemonic);
            if (current_mnemonic_code != "")
            {
                if (current_mnemonic_code == "START")
                {
                    //Если START не в начале исходного текста ассемблирующей программы и встречен еще раз - это ошибка.
                    if (i == 0 && !this->start_dir_flag)
                    {
                        this->start_dir_flag = true;

                        QString error{};
                        //Имя программы.
                        error = check.CheckProgramName(label);
                        if (error != ""){
                            textEdit_Errors->append(error);
                            return false;
                        }
                        else
                            this-> prog_name = label;

                        //Проверка адреса загрузки программы.
                        error = check.CheckProgramDownloadAddress(operand1);
                        if (error != ""){
                            textEdit_Errors->append(error);
                            return false;
                        }

                        //Проверка оставшейся операндной части.
                        error = check.CheckOtherOperandPart(operand2, mnemonic, i);
                        if (error != "")
                        {
                            textEdit_Errors->append(error);
                            return false;
                        }

                        //Устанавливаем Адрес загрузки программы и увеличиваем СА = СА + Адрес загрузки программы (СА = Адрес загрузки программы).
                        this->start_prog_address = Convert::HexToDec(operand1);
                        this->addressCounter = Convert::HexToDec(operand1);
                        //Выводим в двоичный код строчку.
                        //Для двоичного кода.
                        binaryCode_text->append("H  " + this->prog_name + "\t" + Convert::DecToHex(this->start_prog_address).rightJustified(6, '0') + "\t" + "");
                    }
                    else
                    {
                        textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Директива START найдена повторно.\n");
                        return false;
                    }
                }
                if (current_mnemonic_code == "END")
                {
                    if (this->start_dir_flag && !end_dir_flag)
                    {
                        if (!label_flag)
                        {
                            this->end_dir_flag = true;
                            if (operand1.isEmpty())
                            {
                                this->end_prog_address = this->start_prog_address;
                                textEdit_Errors->append("Предупреждение: Строка " + QString::number(i + 1) + ": Адрес точки входа в программу установлен таким же, как адрес загрузки программы.\n");
                            }
                            else
                            {
                                if (!check.CheckAmountMemoryForAddress(operand1))
                                {
                                    textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Адрес точки входа программы содержит недопустимые символы!\n");
                                    return false;
                                }
                                else
                                {
                                    //Устанавливаем адрес точки входа.
                                    this->end_prog_address = Convert::HexToDec(operand1);
                                }
                            }
                            //Директива END встречена не в конце программы.
                            if (i != textEdit_source.size() - 1)
                            {
                                textEdit_Errors->append("Предупреждение: Строка " + QString::number(i + 1) + ": Весь следующий текст программы после строки с директивой END учитываться не будет.\n");
                            }
                            //Если Точка входа программы не укладывается в адресное пространство.
                            if (this->end_prog_address < this->start_prog_address || this->end_prog_address > this->addressCounter)
                            {
                                textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Точка входа программы не укладывается в адресное пространство (Директива END)!");
                                return false;
                            }
                            //Второй операнд не учитывается.
                            QString error = check.CheckOtherOperandPart(operand2, mnemonic, i);
                            if (error != ""){
                                textEdit_Errors->append(error);
                                return false;
                            }
                            //Выводим в двоичный код строчку.
                            QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                            //Вычисляем длину программы: СА = СА - АЗ.
                            int length_programm{this->addressCounter - this->start_prog_address};
                            this->replaceLineWithH(binaryCode_text,
                                                   "H  " + this->prog_name + "\t" +
                                                       Convert::DecToHex(this->start_prog_address).rightJustified(6, '0') + "\t" + "",
                                                   "H  " + this->prog_name + "\t" +
                                                       Convert::DecToHex(this->start_prog_address).rightJustified(6, '0') + "\t" +
                                                       Convert::DecToHex(length_programm).rightJustified(6, '0'));
                            binaryCode_text->append("E  " + Convert::DecToHex(this->end_prog_address).rightJustified(6,'0'));

                            //Убираем возможность пошаговой итерации.
                            i = textEdit_source.size() - 1;
                        }
                        else
                        {
                            textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Обнаружена метка перед директивой END.\nМетка = " + label + ".\n");
                            return false;
                        }
                    }
                    else
                    {
                        textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Директива END обнаружена без директивы START.");
                        return false;
                    }
                }
                if (current_mnemonic_code == "BYTE")
                {
                    if (label_flag)
                    {
                        //Если операнд не пуст.
                        if (!operand1.isEmpty())
                        {
                            //Значит под выделенный байт записывается десятичное число.
                            if (check.CheckCorrectAmountMemoryForDecNumber(operand1))
                            {
                                //Если десятичное число умещается в байт.
                                if (check.CheckAllocAmountMemoryForByte(operand1))
                                {
                                    //Выводим в двоичный код строчку.
                                    QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                    binary_opCode = "";
                                    data = Convert::DecToHex(operand1.toInt()).rightJustified(2, '0');
                                    binaryCode_text->append("T  " + str_AC + "\t" +
                                                            Convert::DecToHex(binary_opCode.length() + data.length()).rightJustified(2, '0') +
                                                            (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                                            (data.isEmpty() ? "" : "\t") + data);
                                    //Увеличиваем СА = СА + кол-во рез. памяти.
                                    //СА = СА + 1
                                    this->addressCounter += 1;
                                }
                                else
                                {
                                    textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Переполнение допустимого выделения памяти для BYTE.\n");
                                    return false;
                                }
                            }
                            //или 16-ричное число или юникодная строка - неважно, главное, чтобы СА не переполнился, а число уместилось  в байт.
                            else
                            {
                                //Выделение под 16-ричное число.
                                if (check.CheckCorrectAmountMemoryForHexNumber(operand1) && check.CheckAmountMemoryForAddress(operand1.split('\'')[1]))
                                {
                                    //Выводим в двоичный код строчку.
                                    QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                    binary_opCode = "";
                                    data = operand1.split('\'')[1];
                                    binaryCode_text->append("T  " + str_AC + "\t" +
                                                            Convert::DecToHex(binary_opCode.length() + data.length()).rightJustified(2, '0') +
                                                            (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                                            (data.isEmpty() ? "" : "\t") + data);
                                    //Увеличваем СА = СА + кол-во рез. памяти (длина числа / 2 + остаток, 2 символа = 1 байт).
                                    int operand_length = operand1.split('\'')[1].length();
                                    this->addressCounter += operand_length / 2 + operand_length % 2;
                                }
                                //Иначе под юникодную строку или ошибка.
                                else
                                {
                                    //Выделение под юникодную строку.
                                    if (check.CheckCorrectAmountMemoryForUnicodeString(operand1))
                                    {
                                        //Выводим в двоичный код строчку.
                                        QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                        binary_opCode = "";
                                        QString unicode_string{operand1.mid(2, operand1.length() - 3)};
                                        for (QChar chr : unicode_string)
                                        {
                                            int ASCII_code = chr.unicode();
                                            data.append(Convert::DecToHex(ASCII_code));
                                        }
                                        binaryCode_text->append("T  " + str_AC + "\t" +
                                                                Convert::DecToHex(binary_opCode.length() + data.length()).rightJustified(2, '0') +
                                                                (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                                                (data.isEmpty() ? "" : "\t") + data);
                                        //Увеливаем СА = СА + кол-во рез. памяти (длина юникодной строки, каждый символ = 1 байт).
                                        int operand_length = operand1.mid(2, operand1.length() - 3).trimmed().length();
                                        this->addressCounter += operand_length;
                                    }
                                    //Иначе неизвестно, что задано.
                                    else
                                    {
                                        textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Неверно задан операнд для BYTE!\n");
                                        return false;
                                    }
                                }
                            }
                            //Если был задан второй операнд, то от игнорируется.
                            QString error = check.CheckOtherOperandPart(operand2, mnemonic, i);
                            if (error != "")
                            {
                                textEdit_Errors->append(error);
                                return false;
                            }
                        }
                        //Иначе ошибка в задании операнда - его нет.
                        else
                        {
                            textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Значение операнда не может быть пустым (BYTE)!\n");
                            return false;
                        }
                    }
                    //Директива должна содержать метку.
                    else
                    {
                        textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Отсутствует метка перед директивой BYTE.");
                        return false;
                    }
                }
                if (current_mnemonic_code == "WORD")
                {
                    if (label_flag)
                    {
                        //Если операнд не пуст.
                        if (!operand1.isEmpty())
                        {
                            //Проверка операнда на десятичное число.
                            if (check.CheckCorrectAmountMemoryForDecNumber(operand1))
                            {
                                //Максимум на значение выделяется 3 байта (как и на значение СА).
                                if (check.CheckAllocAmountMemoryForWord(operand1))
                                {
                                    //Выводим в двоичный код строчку.
                                    QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                    binary_opCode = "";
                                    data = Convert::DecToHex(operand1.toInt()).rightJustified(6, '0');
                                    binaryCode_text->append("T  " + str_AC + "\t" +
                                                            Convert::DecToHex(binary_opCode.length() + data.length()).rightJustified(2, '0') +
                                                            (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                                            (data.isEmpty() ? "" : "\t") + data);
                                    //Увеличиваем СА = СА + кол-во рез. памяти (3 байт).
                                    this->addressCounter += 3;
                                }
                                else
                                {
                                    textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Переполнение допустимого выделения памяти для WORD.\n");
                                    return false;
                                }
                            }
                            //Иначе ошибка.
                            else
                            {
                                textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Неверно задан операнд для WORD!\n");
                                return false;
                            }
                            //Второй операнд игнорируется.
                            QString error = check.CheckOtherOperandPart(operand2, mnemonic, i);
                            if (error != ""){
                                textEdit_Errors->append(error);
                                return false;
                            }
                        }
                        //Операнд не может быть пустым.
                        else
                        {
                            textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Значение операнда не может быть пустым (WORD)!\n");
                            return false;
                        }
                    }
                    //Метка обязана быть.
                    else
                    {
                        textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Отсутствует метка перед директивой WORD.");
                        return false;
                    }
                }
                if (current_mnemonic_code == "RESB")
                {
                    if (label_flag)
                    {
                        if (!operand1.isEmpty())
                        {
                            //Если можно преобразовать в число.
                            if (check.CheckCorrectAmountMemoryForDecNumber(operand1))
                            {
                                //В пределах логичного (размерность Int - 4 байт: по 2 байта в обе стороны).
                                if (check.CheckAllocAmountMemoryForRES(operand1))
                                {
                                    //Выводим в двоичный строчку.
                                    QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                    binary_opCode = "";
                                    data = "";
                                    binaryCode_text->append("T  " + str_AC + "\t" +
                                                            Convert::DecToHex(binary_opCode.length() + data.length()).rightJustified(2, '0') +
                                                            (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                                            (data.isEmpty() ? "" : "\t") + data);
                                    //СА = СА + кол-во рез. памяти (т.е. кол-во байт * 1, т.к. подсчет СА в байтах).
                                    int reserve_byte_memory = operand1.toInt(nullptr, 10) * 1;
                                    addressCounter += reserve_byte_memory;
                                }
                                else
                                {
                                    textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Переполнение допустимого выделения памяти для RESB!\n");
                                    return false;
                                }
                            }
                            else
                            {
                                textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Неверно задан операнд для RESB!\n");
                                return false;
                            }
                            //Второй операнд игнорируется.
                            QString error = check.CheckOtherOperandPart(operand2, mnemonic, i);
                            if (error != "")
                            {
                                textEdit_Errors->append(error);
                                return false;
                            }
                        }
                        //Операнд не может быть пустым.
                        else
                        {
                            textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Значение операнда не может быть пустым (RESB)!\n");
                            return false;
                        }
                    }
                    //Метка обязана быть.
                    else
                    {
                        textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Отсутствует метка перед директивой RESB.");
                        return false;
                    }
                }
                if (current_mnemonic_code == "RESW")
                {
                    if (label_flag)
                    {
                        if (!operand1.isEmpty())
                        {
                            //Можно преобразовать в число.
                            if (check.CheckCorrectAmountMemoryForDecNumber(operand1))
                            {
                                //Как и для RESB - в пределах логичного.
                                if (check.CheckAllocAmountMemoryForRES(operand1))
                                {
                                    //Выводим в вспомогательную таблицу строчку.
                                    QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                    binary_opCode = "";
                                    data = "";
                                    binaryCode_text->append("T  " + str_AC + "\t" +
                                                            Convert::DecToHex(binary_opCode.length() + data.length()).rightJustified(2, '0') +
                                                            (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                                            (data.isEmpty() ? "" : "\t") + data);
                                    //СА = СА + кол-во рез. памяти (число * 3 байт).
                                    int reserve_word_memory = operand1.toInt(nullptr, 10) * 3;
                                    addressCounter += reserve_word_memory;
                                }
                                else
                                {
                                    textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Переполнение допустимого выделения памяти для RESW!\n");
                                    return false;
                                }
                            }
                            else
                            {
                                textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Неверно задан операнд для RESW!\n");
                                return false;
                            }
                            //Второй операнд игнорируется.
                            QString error = check.CheckOtherOperandPart(operand2, mnemonic, i);
                            if (error != "")
                            {
                                textEdit_Errors->append(error);
                                return false;
                            }
                        }
                        //Операнд не может быть пустым.
                        else
                        {
                            textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Значение операнда не может быть пустым (RESW)!\n");
                            return false;
                        }
                    }
                    //Метка обязана быть.
                    else
                    {
                        textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Отсутствует метка перед директивой RESW.");
                        return false;
                    }
                }
            }
            //Проверяем - это команда?
            else
            {
                //Получение команды из ТКО.
                CodeOperation opCode{};
                //Если команда найдена.
                if (opCode_table.find(mnemonic.toUpper(), opCode))
                {
                    //Различная обработка в зависимости от байт команды - обработка общая, не специализрованная на определенные команды.
                    //Однобайтная команда.
                    if (opCode.size == "1")
                    {
                        //Один байт выделяется под МКОП, на операнды памяти не выделяется - они не рассматриваются. Например, NOP.
                        //Тип адресации считается никаким, т.е прибавляется 0.
                        //Реальный дв.код = дв.код * 4 + тип адр.
                        int opcode = check.GetDecOpcode(opCode.binary_code, 0);
                        if (opcode != -1)
                        {
                            //Выводим в вспомогательную таблицу строчку.
                            QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                            if (!operand1.isEmpty() || !operand2.isEmpty())
                            {
                                textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Данная команда не может иметь операндов!");
                                return false;
                            }
                            //Нет операндов.
                            else
                            {
                                binary_opCode = Convert::DecToHex(opcode).rightJustified(2, '0');
                                data = "";
                            }
                            binaryCode_text->append("T  " + str_AC + "\t" +
                                                    Convert::DecToHex(binary_opCode.length() + data.length()).rightJustified(2, '0') +
                                                    (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                                    (data.isEmpty() ? "" : "\t") + data);
                            //Увеличиваем СА = СА + длина команды.
                            addressCounter += 1;
                            //Операнды не учитываются.
                            if (!operand1.isEmpty() || !operand2.isEmpty())
                            {
                                textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Операнды не должны быть в команде " +
                                                 opCode.mnemonic_code + "!\n");
                                return false;
                            }
                        }
                    }
                    //Двухбайтная команда.
                    if (opCode.size == "2")
                    {
                        //Один байт выделяется под МКОП, на операнды выделяется либо по 4 бита (регистры), либо 1 байт (целое число).
                        //Если первый операнд - число, то это непосредственная адресация.
                        //Если можно преобразовать в десятичное число.
                        if (check.CheckCorrectAmountMemoryForDecNumber(operand1))
                        {
                            //Если умещается в байт.
                            if (check.CheckAllocAmountMemoryForByte(operand1))
                            {
                                //Реальный дв.код = дв.код * 4 + тип адр.
                                int opcode = check.GetDecOpcode(opCode.binary_code, 0);
                                if (opcode != -1)
                                {
                                    //Выводим в двоичный код строчку.
                                    QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                    //Один операнд-число (проверка непосредственной адресации в первом проходе).
                                    if (!operand1.isEmpty() && operand2.isEmpty())
                                    {
                                        binary_opCode = Convert::DecToHex(opcode).rightJustified(2, '0');
                                        data = Convert::DecToHex(operand1.toInt()).rightJustified(2,'0');
                                    }
                                    //Нет операндов.
                                    else
                                    {
                                        binary_opCode = Convert::DecToHex(opcode).rightJustified(2, '0');
                                        data = "";
                                    }
                                    binaryCode_text->append("T  " + str_AC + "\t" +
                                                            Convert::DecToHex(binary_opCode.length() + data.length()).rightJustified(2, '0') +
                                                            (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                                            (data.isEmpty() ? "" : "\t") + data);
                                    //Увеличиваем СА = СА + длина команды.
                                    addressCounter += 2;
                                    //Второй операнд не учитывается.
                                    if (!operand2.isEmpty())
                                    {
                                        textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Второй операнл не должен быть в команде " +
                                                         opCode.mnemonic_code + "!\nОперанд: " + operand2 + ".\n");
                                        return false;
                                    }
                                }
                            }
                            else
                            {
                                textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Переполнение допустимого выделения памяти для операнда.\n");
                                return false;
                            }
                        }
                        //Иначе это регистровая адресация == непосредственная (по абстрактному ассемблеру).
                        else
                        {
                            //Если регистры.
                            if (!check.CheckRegister(operand1).isEmpty() && !check.CheckRegister(operand2).isEmpty())
                            {
                                //Реальный дв.код = дв.код * 4 + тип адр.
                                int opcode = check.GetDecOpcode(opCode.binary_code, 0);
                                if (opcode != -1)
                                {
                                    //Выводим в вспомогательную таблицу строчку.
                                    QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                    binary_opCode = Convert::DecToHex(opcode).rightJustified(2, '0');
                                    data = Convert::DecToHex(operand1.split('R')[1].toInt()) +
                                           Convert::DecToHex(operand2.split('R')[1].toInt());
                                    binaryCode_text->append("T  " + str_AC + "\t" +
                                                            Convert::DecToHex(binary_opCode.length() + data.length()).rightJustified(2, '0') +
                                                            (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                                            (data.isEmpty() ? "" : "\t") + data);
                                    //Увеличиваем СА = СА + длина команды.
                                    addressCounter += 2;
                                }
                            }
                            else
                            {
                                textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Операнды должны представлять собой регистры в команде " +
                                                 opCode.mnemonic_code + "!\n");
                                return false;
                            }
                        }
                    }
                    //Трехбайтная команда.
                    if (opCode.size == "3")
                    {
                        //Один байт выделяется под МКОП, на операнды выделяется 2 байта.
                        int opcode = check.GetDecOpcode(opCode.binary_code, 1);
                        if (opcode != -1)
                        {
                            //Выводим в двоичный код строчку.
                            QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');

                            if (operand1.isEmpty() && operand2.isEmpty()){
                                textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Неверно задан операнд, т.к. тип адресации (прямая) подразумевает "
                                                                                      "обязательное наличие операнда.");
                                return false;
                            }
                            QString address{};
                            //Поиск СИ в ТСИ.
                            if (symb_table.find(operand1, address))
                            {
                                binary_opCode = Convert::DecToHex(opcode).rightJustified(2, '0');
                                data = address;
                                binaryCode_text->append("T  " + str_AC + "\t" +
                                                        Convert::DecToHex(binary_opCode.length() + data.length()).rightJustified(2, '0') +
                                                        (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                                        (data.isEmpty() ? "" : "\t") + data);
                            }
                            else
                            {
                                if (!check.CheckSymbolicNameInOperandPart(operand1, textEdit_Errors, i, opCode_table)){
                                    return false;
                                }
                                binary_opCode = Convert::DecToHex(opcode).rightJustified(2, '0');
                                data = "#" + operand1 + "#";
                                list_of_symb_names.push_back({operand1, str_AC});
                                this->TManager.LoadElemOfListToSymbolicNamesTable(tableWidget_ToSN, list_of_symb_names.back());
                                binaryCode_text->append("T  " + str_AC + "\t" +
                                                        "" +
                                                        (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                                        (data.isEmpty() ? "" : "\t") + data);
                            }

                            //Увеличиваем СА = СА + длина команды.
                            addressCounter += 3;
                            //Второй операнд не учитывается.
                            if (!operand2.isEmpty())
                            {
                                textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Второй операнд не должен быть в команде " +
                                                 opCode.mnemonic_code + "!\nОперанд: " + operand2 + ".\n");
                                return false;
                            }
                        }
                    }
                    //Четырехбайтная команда.
                    if (opCode.size == "4")
                    {
                        //Один байт выделяется под МКОП, на операнды выделяется 3 байта.
                        int opcode = check.GetDecOpcode(opCode.binary_code, 1);
                        if (opcode != -1)
                        {
                            //Выводим в двоичный код строчку.
                            QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');

                            if (operand1.isEmpty() && operand2.isEmpty()){
                                textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Неверно задан операнд, т.к. тип адресации (прямая) подразумевает "
                                                                                      "обязательное наличие операнда.");
                                return false;
                            }
                            QString address{};
                            //Поиск СИ в ТСИ.
                            if (symb_table.find(operand1, address))
                            {
                                binary_opCode = Convert::DecToHex(opcode).rightJustified(2, '0');
                                data = address;
                                binaryCode_text->append("T  " + str_AC + "\t" +
                                                        Convert::DecToHex(binary_opCode.length() + data.length()).rightJustified(2, '0') +
                                                        (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                                        (data.isEmpty() ? "" : "\t") + data);
                            }
                            else
                            {
                                if (!check.CheckSymbolicNameInOperandPart(operand1, textEdit_Errors, i, opCode_table)){
                                    return false;
                                }
                                binary_opCode = Convert::DecToHex(opcode).rightJustified(2, '0');
                                data = "#" + operand1 + "#";
                                list_of_symb_names.push_back({operand1, str_AC});
                                this->TManager.LoadElemOfListToSymbolicNamesTable(tableWidget_ToSN, list_of_symb_names.back());
                                binaryCode_text->append("T  " + str_AC + "\t" +
                                                        "" +
                                                        (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                                        (data.isEmpty() ? "" : "\t") + data);
                            }

                            //Увеличиваем СА = СА + длина команды.
                            addressCounter += 4;
                            //Второй операнд не учитывается.
                            if (!operand2.isEmpty())
                            {
                                textEdit_Errors->append("Строка " + QString::number(i+1) + ": Второй операнд не должен быть в команде " +
                                                 opCode.mnemonic_code + "!\nОперанд: " + operand2 + ".\n");
                                return false;
                            }
                        }
                    }
                }
                //Значит - что-то непонятное.
                else
                {
                    textEdit_Errors->append("Строка " + QString::number(i+1) + ": МКОП не найден в ТКО.");
                    return false;
                }
            }
        }
        else
        {
            textEdit_Errors->append("Строка " + QString::number(i + 1) + ": Поле МКОП не может быть пустым.");
            return false;
        }

        if (i == (textEdit_source.size() - 1))
        {
            if (!end_dir_flag){
                textEdit_Errors->append("Не найдена точка входа в программу (END)!");
                return false;
            }
            if (!check.CheckToSNForCorrectAddress(textEdit_Errors, tableWidget_ToSN)){
                return false;
            }
        }
    }
    return true;
}
//Замена строки при нахождении метки.
void PassProcessor::replaceLineWithUnknownSN(QTextEdit* binaryCode_text, const QString& marker, const QString& replacement)
{
    if (!binaryCode_text) return;

    //Получаем весь текст.
    QString content = binaryCode_text->toPlainText();

    //Разделяем текст на строки.
    QStringList lines = content.split("\n");

    //Перебираем все строки.
    for (int i = 0; i < lines.size(); ++i)
    {
        QString line = lines[i];
        // Проверяем, если строка содержит.
        if (line.contains(marker))
        {
            //Разделяем строку на части по символу табуляции.
            QStringList parts = line.split("\t");

            QString firstPart = parts[0];
            QString secondPart = parts[1];
            QString thirdPart = parts[2];

            parts[3].replace(marker, replacement);
            QString fourthPart = parts[3];

            //Новый третий элемент - длина третьего и четвертого элемента.
            QString newSecondPart = Convert::DecToHex(thirdPart.length() + fourthPart.length()).rightJustified(2, '0');
            QString newLine = firstPart + "\t" + newSecondPart + "\t" + thirdPart + "\t" + fourthPart;
            // Заменяем старую строку на новую
            lines[i] = newLine;

        }
    }

    //Объединяем строки.
    QString updatedContent;
    for (int i = 0; i < lines.size(); ++i)
    {
        updatedContent += lines[i];
        if (i < lines.size() - 1)
        {
            updatedContent += "\n";
        }
    }

    //Устанавливаем обновленный текст обратно.
    binaryCode_text->setPlainText(updatedContent);
}
//Замена строки при нахождении директивы END.
void PassProcessor::replaceLineWithH(QTextEdit *binaryCode_text, const QString &target, const QString &replacement)
{
    if (!binaryCode_text) return;

    //Получаем весь текст.
    QString content = binaryCode_text->toPlainText();

    //Разбиваем текст на строки.
    QStringList lines = content.split('\n');

    //Проходим по каждой строке и заменяем целевые.
    for (int i = 0; i < lines.size(); ++i)
    {
        //Если строка совпадает с целевой.
        if (lines[i] == target)
        {
            lines[i] = replacement; //Заменяем строку
        }
    }

    //Объединяем строки.
    QString updatedContent;
    for (int i = 0; i < lines.size(); ++i)
    {
        updatedContent += lines[i];
        if (i < lines.size() - 1)
        {
            updatedContent += "\n";
        }
    }

    //Устанавливаем обновленный текст обратно.
    binaryCode_text->setPlainText(updatedContent);
}
