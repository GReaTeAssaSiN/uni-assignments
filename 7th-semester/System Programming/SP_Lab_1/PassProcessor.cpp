#include "PassProcessor.h"
#include "SourceAssemblerCodeLine.h"
#include "TableCodeOperation.h"
#include "SymbolicNameTable.h"
#include "StructSupportTable.h"
#include "Checks.h"
#include "Convert.h"
#include "vector"
#include "QTableWidget"
#include "QTextEdit"

//Первый проход двухпросмотровой схемы простого ассемблера.
bool PassProcessor::FirstPass(const std::vector<AssemblerInstruction> &source_code,
                                                const TableCodeOperation &TCO,
                                                QTableWidget *tableWidget_auxTable,
                                                std::vector<SupportTable>& sup_table,
                                                QTableWidget *tableWidget_ToSN,
                                                SymbolicNameTable &symbolic_table, QTextEdit *textEdit_FPE)
{
    //Очищаем таблицы и устанавливаем 2 столбца в ТСИ и 4 столбца в вспомогательной таблице.
    tableWidget_auxTable->clear();
    tableWidget_auxTable->setColumnCount(4);
    tableWidget_auxTable->setRowCount(1);

    tableWidget_ToSN->clear();
    tableWidget_ToSN->setColumnCount(2);
    tableWidget_ToSN->setRowCount(1);

    //Поле ошибок первого прохода тоже.
    textEdit_FPE->clear();

    //УЧЕТ АДРЕСОВ ЗАГРУЗКИ, ТОЧКИ ВХОДА, НАЗВАНИЯ ПРОГРАММЫ И СА//
    int load_address{}; //Адрес загрузки программы.
    this->address_entry_point = 0; //Адрес точки входа в программу.
    QString prog_name{}; //Название программы.
    this->address_counter = 0; //СА.

    //Проверка ТКО.
    if (!checks.CheckTableCodeOperation(TCO, textEdit_FPE))
        return false;

    //Флаги для учета найденных директив START и END.
    bool start_flag{false};
    bool end_flag{false};

    //ЦИКЛ ОБРАБОТКИ КАЖДОЙ СТРОКИ ИСХОДНОГО ТЕКСТА ПРОГРАММЫ.
    for (int i{}; i < source_code.size(); ++i){
        //Извлекаем текущую инструкцию.
        const AssemblerInstruction& instruction = source_code[i];
        /*-------------------------------------------------------------------------------------------------------------
         * 2.1. Разбиваем строку на составляющие: Метка | МКОП | Операндная часть (операнд 1 | операнд 2 (опционально)).|
         -------------------------------------------------------------------------------------------------------------*/ 
        QString label{instruction.label.value_or("")};
        QString mnemonic_code{instruction.mnemonic_code.value_or("")};
        QString operand1{instruction.operand1.value_or("")};
        QString operand2{instruction.operand2.value_or("")};
        bool label_flag{false};

        //Если найдена директива START, то имеет смысл проверять СА на допустимость.
        if (start_flag){
            //Адрес загрузки программы записан в СА и необходимо проверить, чтобы СА не выходил за максимальный допустимый объем памяти (0xFFFFFF) (т.к. 2^24 ~ 3 байт ~ 6 символов СА).
            if (!checks.CheckAddressCounterAvailable(textEdit_FPE, i, this->address_counter)){
                return false;
            }
        }
        //Если найдена директива END - выход.
        if (end_flag){
            if (this->address_entry_point >= this->address_counter || this->address_entry_point < load_address){//Если точка входа за пределами адресного пространства.
                textEdit_FPE->append("Строка " + QString::number(i+1) + ": Адрес точки входа в программу находится за пределами адресного пространства (директива END)!\n"
                                                                          "Адресное пространство: от " + Convert::ConvertDecToHex(load_address).rightJustified(6,'0') + " до " +
                                                                          Convert::ConvertDecToHex(this->address_counter - 1).rightJustified(6, '0') + ".\n");
                return false;
            }
            break;
        }

        //Проверка строки исходного текста программы на корректность.
        if (!checks.CheckRowSourceCode(textEdit_FPE, i, prog_name, label, mnemonic_code)){
            return false;
        }

        /*------------------------
         * 2.2. Поиск метки в ТСИ. |
         ------------------------*/
        //Сначала проверяем метку в ТСИ. Название программы опускается за счет флага start_flag далее.
        QString address{};
        if (symbolic_table.Find(label, address)){
            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Дважды определенное символическое имя " + label + ".\n");
            return false;
        }
        else{
            //Если метка не пустая и встречена после нахождения директивы START, то добавляем в ТСИ.
            if (!label.isEmpty() && start_flag){//Метка корректная.
                symbolic_table.Insert(label, Convert::ConvertDecToHex(this->address_counter).rightJustified(6, '0'));
                this->manager.AddStringToToSN(tableWidget_ToSN, symbolic_table, label);
                label_flag = true;
            }
            /*---------------------------
             * 2.3. Анализируем поле МКОП |
             ---------------------------*/
            //Если поле МКОП не пустое, иначе ошибка.
            if (!mnemonic_code.isEmpty()){//МКОП не пустой.
                //Проверяем - это директива?
                QString current_mnemonic_code = checks.CheckDirective(mnemonic_code);
                if (current_mnemonic_code != ""){
                    if (current_mnemonic_code == "START"){
                        //Если START не в начале исходного текста ассемблирующей программы и встречен еще раз - это ошибка.
                        if (i == 0 && !start_flag){
                            start_flag = true;

                            QString error{};
                            //Имя программы.
                            error = checks.CheckProgrammName(label);
                            if (error != ""){
                                textEdit_FPE->append(error);
                                return false;
                            }else{
                                prog_name = label;
                            }

                            //Проверка адреса загрузки программы.
                            error = checks.CheckProgrammDownloadAddress(operand1);
                            if (error != ""){
                                textEdit_FPE->append(error);
                                return false;
                            }

                            //Проверка оставшейся операндной части.
                            error = checks.CheckOtherOperandPart(operand2, mnemonic_code, i);
                            if (error != ""){
                                textEdit_FPE->append(error);
                            }

                            //Устанавливаем Адрес загрузки программы и увеличиваем СА = СА + Адрес загрузки программы (СА = Адрес загрузки программы).
                            load_address = Convert::ConvertHexToDec(operand1);
                            this->address_counter = Convert::ConvertHexToDec(operand1);
                            //Выводим в вспомогательную таблицу строчку.
                            sup_table.push_back({label, mnemonic_code, operand1, ""});
                            this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                        }
                        else{
                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Директива START найдена повторно.\n");
                            return false;
                        }
                    }
                    if (current_mnemonic_code == "END"){
                        if (start_flag && !end_flag){
                            if (!label_flag){
                                end_flag = true;
                                if (operand1.isEmpty()){
                                    this->address_entry_point = load_address;
                                    operand1 = Convert::ConvertDecToHex(this->address_entry_point);
                                    textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ. Строка " + QString::number(i+1) + ": Адрес точки входа в программу установлен таким же, как адрес загрузки программы.\n"
                                                                                                              "Адрес точки входа: " + Convert::ConvertDecToHex(load_address).rightJustified(6, '0') + ".\n");
                                }
                                else{
                                    if (!checks.CheckAmountMemoryForAddress(operand1)){
                                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Адрес точки входа программы содержит недопустимые символы!\n"
                                                                                                  "Адрес точки входа: " + operand1 + ".\n");
                                        return false;
                                    }else{
                                        this->address_entry_point = Convert::ConvertHexToDec(operand1);//Устанавливаем адрес точки входа.
                                    }
                                }
                                if (i != source_code.size() - 1){//Директива END встречена не в конце программы.
                                    textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ. Строка " + QString::number(i+1) + ": Весь следующий текст программы после строки с директивой END учитываться не будет.\n");
                                }
                                //Второй операнд не учитывается.
                                QString error = checks.CheckOtherOperandPart(operand2, mnemonic_code, i);
                                if (error != ""){
                                    textEdit_FPE->append(error);
                                }
                                //Выводим в вспомогательную таблицу строчку.
                                QString str_AC = Convert::ConvertDecToHex(this->address_counter).rightJustified(6,'0');
                                sup_table.push_back({str_AC, mnemonic_code, operand1, ""});
                                this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                            }
                            else{
                                textEdit_FPE->append("Строка " + QString::number(i+1) + ": Обнаружена метка перед директивой END.\nМетка = " + label + ".\n");
                                return false;
                            }
                        }
                        else{
                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Директива END обнаружена без директивы START.");
                            return false;
                        }
                    }
                    if (current_mnemonic_code == "BYTE"){
                        if (label_flag){
                            if (!operand1.isEmpty()){//Если операндн не пуст.
                                if (checks.CheckCorrectAmountMemoryForDecNumber(operand1)){//Значит под выделенный байт записывается десятичное число.
                                    if (checks.CheckAllocAmountMemoryForByte(operand1)){//Если десятичное число умещается в байт.
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::ConvertDecToHex(this->address_counter).rightJustified(6,'0');
                                        sup_table.push_back({str_AC, mnemonic_code, operand1,""});
                                        this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                        //Увеличиваем СА = СА + кол-во рез. памяти.
                                        this->address_counter += 1;//СА = СА + 1.
                                    }
                                    else{
                                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Переполнение допустимого выделения памяти для BYTE.\n"
                                                                                                  "Операнд: " + operand1 + ".\n");
                                        return false;
                                    }
                                }
                                else{//16ричное число или юникодная строка - неважно, сколько выделили памяти, главное, чтобы СА не переполнился.
                                    if (checks.CheckCorrectAmountMemoryForHexNumber(operand1) && checks.CheckAmountMemoryForAddress(operand1.split('\'')[1])){//Выделение под 16ричное число.
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::ConvertDecToHex(this->address_counter).rightJustified(6,'0');
                                        sup_table.push_back({str_AC, mnemonic_code, operand1,""});
                                        this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                        //Увеличваем СА = СА + кол-во рез. памяти (длина числа / 2 + остаточный байт; 2 символа = 1 байт).
                                        int operand_length = operand1.split('\'')[1].length();
                                        this->address_counter += operand_length / 2 + operand_length % 2;
                                    }
                                    else{//Иначе под юникодную строку или ошибка.
                                        if (checks.CheckCorrectAmountMemoryForUnicodeString(operand1)){//Выделение под юникодную строку.
                                            //Выводим в вспомогательную таблицу строчку.
                                            QString str_AC = Convert::ConvertDecToHex(this->address_counter).rightJustified(6,'0');
                                            sup_table.push_back({str_AC, mnemonic_code, operand1,""});
                                            this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                            //Увеливаем СА = СА + кол-во рез. памяти (длина юникодной строки, каждый символ = 1 байт).
                                            int operand_length = operand1.mid(2, operand1.length() - 3).trimmed().length();
                                            this->address_counter += operand_length;
                                        }
                                        else{//Иначе неизвестно, что задано.
                                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Неверно задан операнд для BYTE!\n"
                                                                                                      "Операнд: " + operand1 + ".\n");
                                            return false;
                                        }
                                    }
                                }
                                //Если был задан второй операнд, то от игнорируется.
                                QString error = checks.CheckOtherOperandPart(operand2, mnemonic_code, i);
                                if (error != ""){
                                    textEdit_FPE->append(error);
                                }
                            }
                            else{//Иначе ошибка в задании операнда - его нет.
                                textEdit_FPE->append("Строка " + QString::number(i+1) + ": Значение операнда не может быть пустым (BYTE)!\n");
                                return false;
                            }
                        }
                        else{//Директива должна содержать метку.
                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Отсутствует метка перед директивой BYTE.");
                            return false;
                        }
                    }
                    if (current_mnemonic_code == "WORD"){
                        if (label_flag){
                            if (!operand1.isEmpty()){//Если операнд не пуст.
                                if (checks.CheckCorrectAmountMemoryForDecNumber(operand1)){//Проверка операнда на десятичное число.
                                    if (checks.CheckAllocAmountMemoryForWord(operand1)){//Максимум на значение выделяется 3 байта (как и на значение СА).
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::ConvertDecToHex(this->address_counter).rightJustified(6,'0');
                                        sup_table.push_back({str_AC, mnemonic_code, operand1,""});
                                        this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                        //Увеличиваем СА = СА + кол-во рез. памяти (3 байт).
                                        this->address_counter += 3;//Выделение 3 байт памяти.
                                    }
                                    else{
                                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Переполнение допустимого выделения памяти для WORD.\n"
                                                                                                  "Операнд: " + operand1 + ".\n");
                                        return false;
                                    }
                                }//Иначе ошибка.
                                else{
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Неверно задан операнд для WORD!\n"
                                                                                              "Операнд: " + operand1 + ".\n");
                                    return false;
                                }
                                //Второй операнд игнорируется.
                                QString error = checks.CheckOtherOperandPart(operand2, mnemonic_code, i);
                                if (error != ""){
                                    textEdit_FPE->append(error);
                                }
                            }//Операнд не может быть пустым.
                            else{
                                textEdit_FPE->append("Строка " + QString::number(i+1) + ": Значение операнда не может быть пустым (WORD)!\n");
                                return false;
                            }
                        }
                        else{//Метка обязана быть.
                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Отсутствует метка перед директивой WORD.");
                            return false;
                        }
                    }
                    if (current_mnemonic_code == "RESB"){
                        if (label_flag){
                            if (!operand1.isEmpty()){
                                if (checks.CheckCorrectAmountMemoryForDecNumber(operand1)){//Можно преобразовать в число.
                                    if (checks.CheckAllocAmountMemoryForRES(operand1)){//В пределах логичного (размерность Int - 4 байт: по 2 байт в обе стороны).
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::ConvertDecToHex(this->address_counter).rightJustified(6,'0');
                                        sup_table.push_back({str_AC, mnemonic_code, operand1,""});
                                        this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                        //СА = СА + кол-во рез. памяти (т.е. кол-во байт * 1, т.к. подсчет СА в байтах).
                                        int reserve_byte_memory = operand1.toInt(nullptr, 10) * 1;
                                        this->address_counter += reserve_byte_memory;
                                    }
                                    else{
                                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Переполнение допустимого выделения памяти для RESB!\n"
                                                                                                  "Операнд: " + operand1 + ".\n");
                                        return false;
                                    }
                                }
                                else{
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Неверно задан операнд для RESB!\n"
                                                                                              "Операнд: " + operand1 + ".\n");
                                    return false;
                                }
                                //Второй операнд игнорируется.
                                QString error = checks.CheckOtherOperandPart(operand2, mnemonic_code, i);
                                if (error != ""){
                                    textEdit_FPE->append(error);
                                }
                            }
                            else{//Операнд не может быть пустым.
                                textEdit_FPE->append("Строка " + QString::number(i+1) + ": Значение операнда не может быть пустым (RESB)!\n");
                                return false;
                            }
                        }
                        else{//Метка обязана быть.
                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Отсутствует метка перед директивой RESB.");
                            return false;
                        }
                    }
                    if (current_mnemonic_code == "RESW"){
                        if (label_flag){
                            if (!operand1.isEmpty()){
                                if (checks.CheckCorrectAmountMemoryForDecNumber(operand1)){//Можно преобразовать в число.
                                    if (checks.CheckAllocAmountMemoryForRES(operand1)){//Как и для RESB - в пределах логичного.
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::ConvertDecToHex(this->address_counter).rightJustified(6,'0');
                                        sup_table.push_back({str_AC, mnemonic_code, operand1,""});
                                        this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                        //СА = СА + кол-во рез. памяти (число * 3 байт).
                                        int reserve_word_memory = operand1.toInt(nullptr, 10) * 3;
                                        this->address_counter += reserve_word_memory;
                                    }
                                    else{
                                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Переполнение допустимого выделения памяти для RESW!\n"
                                                                                                  "Операнд: " + operand1 + ".\n");
                                        return false;
                                    }
                                }
                                else{
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Неверно задан операнд для RESW!\n"
                                                                                              "Операнд: " + operand1 + ".\n");
                                    return false;
                                }
                                //Второй операнд игнорируется.
                                QString error = checks.CheckOtherOperandPart(operand2, mnemonic_code, i);
                                if (error != ""){
                                    textEdit_FPE->append(error);
                                }
                            }//Операнд не может быть пустым.
                            else{
                                textEdit_FPE->append("Строка " + QString::number(i+1) + ": Значение операнда не может быть пустым (RESW)!\n"
                                                                                          "Операнд: " + operand1 + ".\n");
                                return false;
                            }
                        }
                        else{//Метка обязана быть.
                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Отсутствует метка перед директивой RESW.");
                            return false;
                        }
                    }
                }
                //Проверяем - это команда?
                else{
                    TCOElem TCO_elem;//Для получения элемента ТКО.
                    if (TCO.Find(mnemonic_code, TCO_elem))
                    {
                        //Различная обработка в зависимости от байт команды - обработка общая, не специализрованная на определенные команды.
                        if (TCO_elem.code_size == "1"){//Однобайтная команда.
                            //Один байт выделяется под МКОП, на операнды памяти не выделяется - они не рассматриваются. Например, NOP.
                            //Тип адресации считается никаким, т.е прибавляется 0.
                            int opcode = checks.GetDecOpcode(TCO_elem.binary_code, 0);//Р.дв.код = дв.код * 4 + тип адр.
                            if (opcode != -1){
                                //Выводим в вспомогательную таблицу строчку.
                                QString str_AC = Convert::ConvertDecToHex(this->address_counter).rightJustified(6,'0');
                                sup_table.push_back({str_AC, Convert::ConvertDecToHex(opcode).rightJustified(2,'0'),"",""});
                                this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                //Увеличиваем СА = СА + длина команды.
                                this->address_counter += 1;
                                //Операнды не учитываются.
                                if (!operand1.isEmpty() || !operand2.isEmpty()){
                                    textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ! Строка " + QString::number(i+1) + ": Операнды учитываться не будут в команде " +
                                                         TCO_elem.mnemonic_code + "!\n"
                                                         "Операнды: " + operand1 + " " + operand2 + ".\n");
                                }
                            }
                        }
                        if (TCO_elem.code_size == "2"){//Двухбайтная команда.
                            //Один байт выделяется под МКОП, на операнды выделяется либо по 4 бита (регистры), либо 1 байт (целое число).
                            //Если первый операнд - число, то это непосредственная адресация.
                            if (checks.CheckCorrectAmountMemoryForDecNumber(operand1)){//Если можно преобразовать в десятичное число.
                                if (checks.CheckAllocAmountMemoryForByte(operand1)){//Если умещается в байт.
                                    int opcode = checks.GetDecOpcode(TCO_elem.binary_code, 0);//Р.дв.код = дв.код * 4 + тип адр.
                                    if (opcode != -1){
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::ConvertDecToHex(this->address_counter).rightJustified(6,'0');
                                        sup_table.push_back({str_AC, Convert::ConvertDecToHex(opcode).rightJustified(2,'0'),operand1,""});
                                        this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                        //Увеличиваем СА = СА + длина команды.
                                        this->address_counter += 2;
                                        //Второй операнд не учитывается.
                                        if (!operand2.isEmpty()){
                                            textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ! Строка " + QString::number(i+1) + ": Второй операнд учитываться не будет в команде " +
                                                                 TCO_elem.mnemonic_code + "!\nОперанд: " + operand2 + ".\n");
                                        }
                                    }
                                }
                                else{
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Команда " + mnemonic_code + ". Операнд пуст или переполнение допустимого выделения памяти для целочисленного операнда.\n");
                                    return false;
                                }
                            }
                            else{//Иначе это регистровая адресация == непосредственная (по абстрактному ассемблеру).
                                if (!checks.CheckRegister(operand1).isEmpty() && !checks.CheckRegister(operand2).isEmpty()){//Если регистры.
                                    int opcode = checks.GetDecOpcode(TCO_elem.binary_code, 0);//Р.дв.код = дв.код * 4 + тип адр.
                                    if (opcode != -1){
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::ConvertDecToHex(this->address_counter).rightJustified(6,'0');
                                        sup_table.push_back({str_AC, Convert::ConvertDecToHex(opcode).rightJustified(2,'0'),operand1,operand2});
                                        this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                        //Увеличиваем СА = СА + длина команды.
                                        this->address_counter += 2;
                                    }
                                }
                                else{
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Команда " + mnemonic_code + ". Операнды (оба) должны представлять собой регистры или целое число (первый) в команде " +
                                                         TCO_elem.mnemonic_code + "! \n");
                                    return false;
                                }
                            }
                        }
                        if (TCO_elem.code_size == "3"){//Трехбайтная команда.
                            //Один байт выделяется под МКОП, на операнды выделяется 2 байта.
                            int opcode = checks.GetDecOpcode(TCO_elem.binary_code, 1);
                            if (opcode != -1){
                                //Выводим в вспомогательную таблицу строчку.
                                QString str_AC = Convert::ConvertDecToHex(this->address_counter).rightJustified(6,'0');
                                sup_table.push_back({str_AC, Convert::ConvertDecToHex(opcode).rightJustified(2,'0'),operand1,""});
                                this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                //Увеличиваем СА = СА + длина команды.
                                this->address_counter += 3;
                                //Второй операнд не учитывается.
                                if (!operand2.isEmpty()){
                                    textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ! Строка " + QString::number(i+1) + ": Второй операнд учитываться не будет в команде " +
                                                         TCO_elem.mnemonic_code + "!\nОперанд: " + operand2 + ".\n");
                                }
                            }
                        }
                        if (TCO_elem.code_size == "4"){//Четырехбайтная команда.
                            //Один байт выделяется под МКОП, на операнды выделяется 3 байта.
                            int opcode = checks.GetDecOpcode(TCO_elem.binary_code, 1);
                            if (opcode != -1){
                                //Выводим в вспомогательную таблицу строчку.
                                QString str_AC = Convert::ConvertDecToHex(this->address_counter).rightJustified(6,'0');
                                sup_table.push_back({str_AC, Convert::ConvertDecToHex(opcode).rightJustified(2,'0'),operand1,""});
                                this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                //Увеличиваем СА = СА + длина команды.
                                this->address_counter += 4;
                                //Второй операнд не учитывается.
                                if (!operand2.isEmpty()){
                                    textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ! Строка " + QString::number(i+1) + ": Второй операнд учитываться не будет в команде " +
                                                         TCO_elem.mnemonic_code + "!\nОперанд: " + operand2 + ".\n");
                                }
                            }
                        }
                    }
                    //Значит - что-то непонятное.
                    else{
                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": МКОП не найден в ТКО.");
                        return false;
                    }
                }
            }else{
                textEdit_FPE->append("Строка " + QString::number(i+1) + ": Поле МКОП не может быть пустым.");
                return false;
            }
        }
    }
    if (!end_flag){
        textEdit_FPE->append("Не найдена точка входа в программу (END)!");
        return false;
    }
    else{
        if (this->address_entry_point >= this->address_counter || this->address_entry_point < load_address){
            textEdit_FPE->append("Адрес точки входа в программу находится за пределами адресного пространства (директива END)!\n"
                                 "Адресное пространство: от " + Convert::ConvertDecToHex(load_address).rightJustified(6, '0') + " до " +
                                 Convert::ConvertDecToHex(this->address_counter - 1).rightJustified(6, '0') + ".\n");
            return false;
        }
    }
    return true;
}

//Второй проход двухпросмотровой схемы простого ассемблера.
bool PassProcessor::SecondPass(QTableWidget *tableWidget_OMH, QTextEdit *textEdit_SPE, QTextEdit *textEdit_binary_code,
                               const std::vector<SupportTable> &sup_table, const SymbolicNameTable &symbolic_table)
{
    //Очищаем таблицу заголовка объектного модуля и устанавливаем 3 столбца, 1 строку..
    tableWidget_OMH->clear();
    tableWidget_OMH->setColumnCount(3);
    tableWidget_OMH->setRowCount(1);

    //Поле ошибок первого прохода тоже.
    textEdit_SPE->clear();

    //Вычисляем длину программы: СА = СА - АЗ.
    int length_programm{this->address_counter - this->address_entry_point};
    /*-------------------------------------------------------------------------------------------------------------
     * 1. Считываем первую строку вспомогательной таблицы и формируем запись-заголовок.
     -------------------------------------------------------------------------------------------------------------*/
    //Для заголовка объектного модуля.
    tableWidget_OMH->setItem(0, 0, new QTableWidgetItem(sup_table[0].address_counter));
    tableWidget_OMH->setItem(0, 1, new QTableWidgetItem(Convert::ConvertDecToHex(length_programm).rightJustified(6, '0')));
    tableWidget_OMH->setItem(0, 2, new QTableWidgetItem(Convert::ConvertDecToHex(this->address_entry_point).rightJustified(6, '0')));
    //Для двоичного кода.
    textEdit_binary_code->append("H_" + sup_table[0].address_counter + "_" +
                                 Convert::ConvertDecToHex(this->address_entry_point).rightJustified(6, '0') + "_" +
                                 Convert::ConvertDecToHex(this->address_counter).rightJustified(6, '0'));

    /*-----------------------------------------------------------------
     * 2. Цикл строки исходного текста (через вспомогательную таблицу).
     ------------------------------------------------------------------*/
    for (int i{1}; i < sup_table.size(); i++){
        /*----------------------------
         * 3. Обработка записи-конец.
        -----------------------------*/
        //Если найдена директива END, то формируется запись-конец и запись двоичного кода завершается.
        if (!sup_table[i].operation_code.isEmpty() && sup_table[i].operation_code == "END"){
            textEdit_binary_code->append("E_" + Convert::ConvertDecToHex(this->address_entry_point).rightJustified(6,'0'));
            break;
        }
        //Переменные для записи двоичного представления команд и данных (адрес метки, число, строка и тд.).
        QString binary_view{};
        QString data{};
        //Директивы START и END встречены быть не могут, т.к. обработаны выше.
        if (checks.CheckDirective(sup_table[i].operation_code) != ""){//Директивы BYTE, WORD, RESB, RESW.
            if (checks.CheckCorrectAmountMemoryForDecNumber(sup_table[i].operand1)){//Операнд является числом в 10 СИ.
                if (sup_table[i].operation_code=="RESB" || sup_table[i].operation_code=="RESW"){//Директивы резервирования памяти.
                    binary_view="";
                    data="";
                }
                else{//Директивы выделения памяти под 1б (BYTE) или 3б (WORD).
                    binary_view="";
                    data = Convert::ConvertDecToHex(sup_table[i].operand1.toInt());
                    sup_table[i].operation_code == "BYTE" ? (data = data.rightJustified(2, '0')) : (data = data.rightJustified(6, '0'));
                }
            }
            else{//Это либо unicode-строка, либо число в 16 СИ.
                if (checks.CheckCorrectAmountMemoryForHexNumber(sup_table[i].operand1)){//Это число в 16 СИ.
                    binary_view="";
                    data = sup_table[i].operand1.split('\'')[1];
                }
                else{//Это unicode строка.
                    binary_view="";
                    QString unicode_string{sup_table[i].operand1.mid(2, sup_table[i].operand1.length() - 3).trimmed()};
                    for (QChar chr : unicode_string){
                        int ASCII_code = chr.unicode();
                        data.append(Convert::ConvertDecToHex(ASCII_code));
                    }
                }
            }
        }
        else{//Иначе это может быть только реальный двоичный КОП.
            int type_addr{Convert::ConvertHexToDec(sup_table[i].operation_code) % 2};//Если = 0, то непосредственная/регистровая адресация, иначе прямая.
            if (type_addr != 0){//Операнды обязаны быть.
                if (sup_table[i].operand1.isEmpty() && sup_table[i].operand2.isEmpty()){
                    textEdit_SPE->append("Строка " + QString::number(i+1) + ": Неверно задан операнд, т.к. тип адресации (прямая) подразумевает "
                                                                              "обязательное наличие операнда.");
                    return false;
                }
                QString address{};
                //Поиск СИ в ТСИ (операнд точно должен быть СИ).
                if (symbolic_table.Find(sup_table[i].operand1, address)){
                    binary_view = sup_table[i].operation_code;
                    data = address;
                }
                else{
                    textEdit_SPE->append("Строка " + QString::number(i+1) + ": Неверно задан операнд, т.к. тип адресации (прямая) подразумевает, "
                                                                              "что операнд является меткой. Метка: " + sup_table[i].operand1 +
                                                                              " не найдена в ТСИ.");
                    return false;
                }
            }
            else{//Операнды могут не быть, а могут быть.
                if (!sup_table[i].operand1.isEmpty() && !sup_table[i].operand2.isEmpty()){//Два операнда-регистра (проверка регистровой адресации в первом проходе).
                    binary_view = sup_table[i].operation_code;
                    data = Convert::ConvertDecToHex(sup_table[i].operand1.split('R')[1].toInt()) +
                           Convert::ConvertDecToHex(sup_table[i].operand2.split('R')[1].toInt());
                }
                else if (!sup_table[i].operand1.isEmpty() && sup_table[i].operand2.isEmpty()){//Один операнд-число (проверка непосредственной адресации в первом проходе).
                    binary_view = sup_table[i].operation_code;
                    data = Convert::ConvertDecToHex(sup_table[i].operand1.toInt()).rightJustified(2,'0');
                }
                else{//Нет операндов.
                    binary_view = sup_table[i].operation_code;
                    data = "";
                }
            }
        }
        //Вывод результатов в поле Двоичного кода.
        textEdit_binary_code->append("T_" + sup_table[i].address_counter + "_" +
                                     Convert::ConvertDecToHex(binary_view.length() + data.length()).rightJustified(2, '0') +
                                     (binary_view.isEmpty() ? "" : "_") + binary_view +
                                     (data.isEmpty() ? "" : "_") + data);
    }
    return true;
}
