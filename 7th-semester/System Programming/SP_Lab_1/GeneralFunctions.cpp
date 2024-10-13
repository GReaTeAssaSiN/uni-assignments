#include "GeneralFunctions.h"
#include "checks.h"
#include "convert.h"

bool FirstPass(const std::vector<SourceAssemblyCode> &source_code,const std::vector<OpcodeTable> &opcode_table,
               QTableWidget* tableWidget_auxTable, QTableWidget* tableWidget_ToSN, QTextEdit* textEdit_FPE, TablesManager* manager)
{
    //УЧЕТ КОЛИЧЕСТВА ЗАРЕЗЕРВИРОВАННОЙ ПАМЯТИ//
    QString address_counter{"0"}; //Счетчик адреса (СА) в шестнадцатиричной СИ.
    QString load_address{"0"}; //Адрес загрузки программы в шестнадцатиричной СИ.
    QString end_address{"0"}; //Адрес точки входа в программу в шестнадцатиричной СИ.
    QString prog_name{}; //Название программы.

    //Объект класса Checks для различных глобальных проверок.
    Checks checks{Checks()};

    //Проверка ТКО.
    if (!checks.CheckOpcodeTable(opcode_table, textEdit_FPE))
        return false;

    //Флаги для учета найденных директив START и END.
    bool start_flag{false};
    bool end_flag{false};

    //Устанавливаем 4 столбца во вспомогательной таблице и 2 столбца в ТСИ.
    tableWidget_auxTable->setColumnCount(4);
    tableWidget_ToSN->setColumnCount(2);

    //ЦИКЛ ОБРАБОТКИ КАЖДОЙ СТРОКИ ИСХОДНОГО ТЕКСТА ПРОГРАММЫ.
    for (int i{}; i < source_code.size(); ++i){
        //Заносим в переменные соответствующие значения.
        QString label{source_code[i].label.value_or("")};
        QString mnemonic_code{source_code[i].mnemonic_code.value_or("")};
        QString operand1{source_code[i].firstOperand.value_or("")};
        QString operand2{source_code[i].secondOperand.value_or("")};
        bool label_flag{false};

        //Если найдена директива START, то имеет смысл проверять СА на допустимость.
        if (start_flag){
            //Адрес загрузки программы записан в СА и необходимо проверить, чтобы СА не выходил за максимальный допустимый объем памяти (0xFFFFFF) (т.к. 2^24 ~ 3 байт ~ 6 символов СА).
            if (!checks.CheckAddressCounterAvailable(textEdit_FPE, i, address_counter)){
                return false;
            }
        }
        //Если найдена директива END - выход.
        if (end_flag)
            break;

        //Проверка строки исходного текста программы на корректность.
        if (!checks.CheckRowSourceCode(textEdit_FPE, i, prog_name, label, mnemonic_code)){
            return false;
        }

        //Сначала проверяем метку в ТСИ. Название программы опускается за счет флага start_flag далее.
        if (checks.SearchSymbolicNameInToSN(label, tableWidget_ToSN, textEdit_FPE) != -1){//Найдена существующая метка.
            return false;
        }
        else{
            //Если метка не пустая и встречена после нахождения директивы START, то добавляем в ТСИ.
            if (!label.isEmpty() && start_flag){//Метка корректная.
                manager->AddStringToToSN(label, Convert::ConvertToSixNumber(address_counter), tableWidget_ToSN);
                label_flag = true;
            }
            //Если поле МКОП не пустое, иначе ошибка.
            if (!mnemonic_code.isEmpty()){//МКОП символьно корректные.
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
                            load_address = Convert::ConvertToSixNumber(operand1);
                            address_counter = Convert::SumHexNumbersResult(Convert::ConvertToSixNumber(address_counter), load_address);
                            //Выводим в вспомогательную таблицу строчку.
                            manager->AddStringToAuxTable(prog_name, mnemonic_code, operand1, "", tableWidget_auxTable);
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
                                    end_address = load_address;
                                    textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ. Строка " + QString::number(i+1) + ": Адрес точки входа в программу установлен таким же, как адрес загрузки программы.\n");
                                }
                                else{
                                    if (!checks.CheckAmountMemoryForAddress(operand1)){
                                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Адрес точки входа программы содержит недопустимые символы!\n");
                                        return false;
                                    }else{
                                        end_address = Convert::ConvertToSixNumber(operand1);//Устанавливаем адрес точки входа.
                                    }
                                }
                                if (i != source_code.size() - 1){//Директива END встречена не в конце программы.
                                    textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ. Строка " + QString::number(i+1) + ": Весь следующий текст программы после строки с директивой END учитываться не будет.\n");
                                }
                                if (load_address != end_address){//Если АЗ и точка входа не совпадают.
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Адрес загрузки программы не совпадает с точкой входа (Директивы START и END)!");
                                    return false;
                                }
                                //Второй операнд не учитывается.
                                QString error = checks.CheckOtherOperandPart(operand2, mnemonic_code, i);
                                if (error != ""){
                                    textEdit_FPE->append(error);
                                }
                                //Выводим в вспомогательную таблицу строчку.
                                manager->AddStringToAuxTable(address_counter, mnemonic_code, operand1, "", tableWidget_auxTable);
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
                                        manager->AddStringToAuxTable(address_counter, mnemonic_code, operand1, "", tableWidget_auxTable);
                                        //Увеличиваем СА = СА + кол-во рез. памяти.
                                        address_counter = Convert::SumHexNumbersResult(address_counter,
                                                                                       Convert::ConvertToSixNumber(Convert::ConvertDecToHex(1)));//СА = СА + 1.
                                    }
                                    else{
                                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Переполнение допустимого выделения памяти для BYTE.\n");
                                        return false;
                                    }
                                }
                                else{//16ричное число или юникодная строка - неважно, сколько выделили памяти, главное, чтобы СА не переполнился.
                                    if (checks.CheckCorrectAmountMemoryForHexNumber(operand1)){//Выделение под 16ричное число.
                                        //Выводим в вспомогательную таблицу строчку.
                                        manager->AddStringToAuxTable(address_counter, mnemonic_code, operand1, "", tableWidget_auxTable);
                                        //Увеличваем СА = СА + кол-во рез. памяти (длина числа / 2 + остаточный байт; 2 символа = 1 байт).
                                        int operand_length = operand1.split('\'')[1].length();
                                        address_counter =
                                            Convert::SumHexNumbersResult(address_counter, Convert::ConvertToSixNumber(Convert::ConvertDecToHex(operand_length / 2 + operand_length % 2)));
                                    }
                                    else{//Иначе под юникодную строку или ошибка.
                                        if (checks.CheckCorrectAmountMemoryForUnicodeString(operand1)){//Выделение под юникодную строку.
                                            //Выводим в вспомогательную таблицу строчку.
                                            manager->AddStringToAuxTable(address_counter, mnemonic_code, operand1, "", tableWidget_auxTable);
                                            //Увеливаем СА = СА + кол-во рез. памяти (длина юникодной строки, каждый символ = 1 байт).
                                            int operand_length = operand1.split('\'')[1].length();
                                            address_counter =
                                                Convert::SumHexNumbersResult(address_counter, Convert::ConvertToSixNumber(Convert::ConvertDecToHex(operand_length)));
                                        }
                                        else{//Иначе неизвестно, что задано.
                                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Неверно задан операнд для BYTE!\n");
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
                                        manager->AddStringToAuxTable(address_counter, mnemonic_code, operand1, "", tableWidget_auxTable);
                                        //Увеличиваем СА = СА + кол-во рез. памяти (3 байт).
                                        address_counter = Convert::SumHexNumbersResult(address_counter,
                                                                                       Convert::ConvertToSixNumber(Convert::ConvertDecToHex(3)));//Выделение 3 байт памяти.
                                    }
                                    else{
                                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Переполнение допустимого выделения памяти для WORD.\n");
                                        return false;
                                    }
                                }//Иначе ошибка.
                                else{
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Неверно задан операнд для WORD!\n");
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
                                    if (checks.CheckAllocAmountMemoryForRES(source_code[i].firstOperand.value_or(""))){//В пределах логичного (размерность Int - 4 байт: по 2 байт в обе стороны).
                                        //Выводим в вспомогательную таблицу строчку.
                                        manager->AddStringToAuxTable(address_counter, mnemonic_code, operand1, "", tableWidget_auxTable);
                                        //СА = СА + кол-во рез. памяти (т.е. кол-во байт * 1, т.к. подсчет СА в байтах).
                                        int reserve_byte_memory = operand1.toInt() * 1;
                                        address_counter =
                                            Convert::SumHexNumbersResult(address_counter, Convert::ConvertToSixNumber(Convert::ConvertDecToHex(reserve_byte_memory)));
                                    }
                                    else{
                                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Переполнение допустимого выделения памяти для RESB!\n");
                                        return false;
                                    }
                                }
                                else{
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Неверно задан операнд для RESB!\n");
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
                                    if (checks.CheckAllocAmountMemoryForRES(source_code[i].firstOperand.value_or(""))){//Как и для RESB - в пределах логичного.
                                        //Выводим в вспомогательную таблицу строчку.
                                        manager->AddStringToAuxTable(address_counter, mnemonic_code, operand1, "", tableWidget_auxTable);
                                        //СА = СА + кол-во рез. памяти (число * 3 байт).
                                        int reserve_word_memory = operand1.toInt() * 3;
                                        address_counter =
                                            Convert::SumHexNumbersResult(address_counter, Convert::ConvertToSixNumber(Convert::ConvertDecToHex(reserve_word_memory)));
                                    }
                                    else{
                                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Переполнение допустимого выделения памяти для RESW!\n");
                                        return false;
                                    }
                                }
                                else{
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Неверно задан операнд для RESW!\n");
                                    return false;
                                }
                                //Второй операнд игнорируется.
                                QString error = checks.CheckOtherOperandPart(operand2, mnemonic_code, i);
                                if (error != ""){
                                    textEdit_FPE->append(error);
                                }
                            }//Операнд не может быть пустым.
                            else{
                                textEdit_FPE->append("Строка " + QString::number(i+1) + ": Значение операнда не может быть пустым (RESW)!\n");
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
                    int index_command = checks.SearchCommandInToOC(mnemonic_code, opcode_table);//Получение индекса команды из ТКО.
                    if (index_command  != -1){//Команда найдена.
                        //Различная обработка в зависимости от байт команды - обработка общая, не специализрованная на определенные команды.
                        if (opcode_table[index_command].size.value_or("") == "1"){//Однобайтная команда.
                            //Один байт выделяется под МКОП, на операнды памяти не выделяется - они не рассматриваются. Например, NOP.
                            //Тип адресации считается никаким, т.е прибавляется 0.
                            int opcode = checks.GetDecOpcode(opcode_table[index_command].binary_opcode.value_or(""), 0);//Р.дв.код = дв.код * 4 + тип адр.
                            if (opcode != -1){
                                //Выводим в вспомогательную таблицу строчку.
                                manager->AddStringToAuxTable(address_counter, Convert::ConvertToTwoNumber(Convert::ConvertDecToHex(opcode)), "", "", tableWidget_auxTable);
                                //Увеличиваем СА = СА + длина команды.
                                address_counter = Convert::SumHexNumbersResult(address_counter, Convert::ConvertToSixNumber(Convert::ConvertDecToHex(1)));
                                //Операнды не учитываются.
                                if (!operand1.isEmpty() || !operand2.isEmpty()){
                                    textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ! Строка " + QString::number(i+1) + ": Операнды учитываться не будут в команде " +
                                                             opcode_table[index_command].code.value_or("") + "!\n");
                                }
                            }
                        }
                        if (opcode_table[index_command].size.value_or("") == "2"){//Двухбайтная команда.
                            //Один байт выделяется под МКОП, на операнды выделяется либо по 4 бита (регистры), либо 1 байт (целое число).
                            //Если первый операнд - число, то это непосредственная адресация.
                            if (checks.CheckCorrectAmountMemoryForDecNumber(operand1)){//Если можно преобразовать в десятичное число.
                                if (checks.CheckAllocAmountMemoryForByte(operand1)){//Если умещается в байт.
                                    int opcode = checks.GetDecOpcode(opcode_table[index_command].binary_opcode.value_or(""), 0);//Р.дв.код = дв.код * 4 + тип адр.
                                    if (opcode != -1){
                                        //Выводим в вспомогательную таблицу строчку.
                                        manager->AddStringToAuxTable(address_counter, Convert::ConvertToTwoNumber(Convert::ConvertDecToHex(opcode)), operand1, "", tableWidget_auxTable);
                                        //Увеличиваем СА = СА + длина команды.
                                        address_counter = Convert::SumHexNumbersResult(address_counter, Convert::ConvertToSixNumber(Convert::ConvertDecToHex(2)));
                                        //Второй операнд не учитывается.
                                        if (!operand2.isEmpty()){
                                            textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ! Строка " + QString::number(i+1) + ": Второй операнд учитываться не будет в команде " +
                                                                 opcode_table[index_command].code.value_or("") + "!\nОперанд: " + operand2 + ".\n");
                                        }
                                    }
                                }
                                else{
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Переполнение допустимого выделения памяти для операнда.\n");
                                    return false;
                                }
                            }
                            else{//Иначе это регистровая адресация == непосредственная (по абстрактному ассемблеру).
                                if (!checks.CheckRegister(operand1).isEmpty() && !checks.CheckRegister(operand2).isEmpty()){//Если регистры.
                                    int opcode = checks.GetDecOpcode(opcode_table[index_command].binary_opcode.value_or(""), 0);//Р.дв.код = дв.код * 4 + тип адр.
                                    if (opcode != -1){
                                        //Выводим в вспомогательную таблицу строчку.
                                        manager->AddStringToAuxTable(address_counter, Convert::ConvertToTwoNumber(Convert::ConvertDecToHex(opcode)), operand1, operand2, tableWidget_auxTable);
                                        //Увеличиваем СА = СА + длина команды.
                                        address_counter = Convert::SumHexNumbersResult(address_counter, Convert::ConvertToSixNumber(Convert::ConvertDecToHex(2)));
                                    }
                                }
                                else{
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Операнды должны представлять собой регистры в команде " +
                                                         opcode_table[index_command].code.value_or("") + "!\n");
                                    return false;
                                }
                            }
                        }
                        if (opcode_table[index_command].size.value_or("") == "3"){//Трехбайтная команда.
                            //Один байт выделяется под МКОП, на операнды выделяется 2 байта.
                            int opcode = checks.GetDecOpcode(opcode_table[index_command].binary_opcode.value_or(""), 1);
                            if (opcode != -1){
                                //Выводим в вспомогательную таблицу строчку.
                                manager->AddStringToAuxTable(address_counter, Convert::ConvertToTwoNumber(Convert::ConvertDecToHex(opcode)), operand1, "", tableWidget_auxTable);
                                address_counter = Convert::SumHexNumbersResult(address_counter, Convert::ConvertToSixNumber(Convert::ConvertDecToHex(3)));
                                //Второй операнд не учитывается.
                                if (!operand2.isEmpty()){
                                    textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ! Строка " + QString::number(i+1) + ": Второй операнд учитываться не будет в команде " +
                                                         opcode_table[index_command].code.value_or("") + "!\nОперанд: " + operand2 + ".\n");
                                }
                            }
                        }
                        if (opcode_table[index_command].size.value_or("") == "4"){//Четырехбайтная команда.
                            //Один байт выделяется под МКОП, на операнды выделяется 3 байта.
                            int opcode = checks.GetDecOpcode(opcode_table[index_command].binary_opcode.value_or(""), 1);
                            if (opcode != -1){
                                //Выводим в вспомогательную таблицу строчку.
                                manager->AddStringToAuxTable(address_counter, Convert::ConvertToTwoNumber(Convert::ConvertDecToHex(opcode)), operand1, "", tableWidget_auxTable);
                                //Увеличиваем СА = СА + длина команды.
                                address_counter = Convert::SumHexNumbersResult(address_counter, Convert::ConvertToSixNumber(Convert::ConvertDecToHex(4)));
                                //Второй операнд не учитывается.
                                if (!operand2.isEmpty()){
                                    textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ! Строка " + QString::number(i+1) + ": Второй операнд учитываться не будет в команде " +
                                                         opcode_table[index_command].code.value_or("") + "!\nОперанд: " + operand2 + ".\n");
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
    return true;
}

//Реализация второго прохода.
