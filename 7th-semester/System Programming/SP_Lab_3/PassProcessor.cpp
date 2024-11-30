#include "PassProcessor.h"
#include "SourceAssemblerCodeLine.h"
#include "TableCodeOperation.h"
#include "SymbolicNameTable.h"
#include "SupportTable.h"
#include "Checks.h"
#include "Convert.h"
#include "vector"
#include "QTableWidget"
#include "QTextEdit"

//Первый проход двухпросмотровой схемы простого ассемблера.
bool PassProcessor::FirstPass(const int& type_addr, const std::vector<AssemblerInstruction> &source_code,
                              const TableCodeOperation &TCO,
                              QTableWidget *tableWidget_auxTable,
                              std::vector<SupportTable>& sup_table,
                              QTableWidget *tableWidget_ToSN,
                              SymbolicNameTable &symbolic_table, QTextEdit *textEdit_FPE)
{
    //Очищаем таблицы и устанавливаем 4 столбца в ТСИ и 4 столбца в вспомогательной таблице.
    tableWidget_auxTable->clear();
    tableWidget_auxTable->setColumnCount(4);
    tableWidget_auxTable->setRowCount(1);

    tableWidget_ToSN->clear();
    tableWidget_ToSN->setColumnCount(4);
    tableWidget_ToSN->setRowCount(1);

    //Поле ошибок первого прохода тоже.
    textEdit_FPE->clear();

    //Очищаем внутренние списки для каждой управляющей секции.
    this->prog_names.clear();
    this->load_addresses.clear();
    this->address_counters.clear();
    this->address_entry_point = 0;

    //Проверка ТКО.
    if (!checks.CheckTableCodeOperation(TCO, textEdit_FPE))
        return false;

    //Флаги для учета найденных директив START и END.
    bool start_flag{false};
    bool end_flag{false};

    //Переменная для записи МКОП предыдущей инструкции.
    QString previous_mnemonic_code{};
    //Переменная для записи названия текущей секции.
    QString current_CSEC{};

    //ЦИКЛ ОБРАБОТКИ КАЖДОЙ СТРОКИ ИСХОДНОГО ТЕКСТА ПРОГРАММЫ.
    for (int i{}; i < source_code.size(); ++i){
        //Извлекаем текущую инструкцию.
        const AssemblerInstruction& instruction = source_code[i];
        /*-------------------------------------------------------------------------------------------------------------
         * 4.1. Разбиваем строку на составляющие: Метка | МКОП | Операндная часть (операнд 1 | операнд 2 (опционально)).|
         -------------------------------------------------------------------------------------------------------------*/
        QString label{instruction.label.value_or("")};
        QString mnemonic_code{instruction.mnemonic_code.value_or("")};
        QString operand1{instruction.operand1.value_or("")};
        QString operand2{instruction.operand2.value_or("")};
        bool label_flag{false};

        //Если найдена директива START, то имеет смысл проверять СА на допустимость.
        if (start_flag){
            //Адрес загрузки программы записан в СА и необходимо проверить, чтобы СА не выходил за максимальный допустимый объем памяти (0xFFFFFF) (т.к. 2^24 ~ 3 байт ~ 6 символов СА).
            if (!checks.CheckAddressCounterAvailable(textEdit_FPE, i, this->address_counters.last())){
                return false;
            }
        }
        //Если найдена директива END - выход.
        if (end_flag){
            if (this->address_entry_point > this->address_counters.first() || this->address_entry_point < this->load_addresses.first()){//Если точка входа за пределами адресного пространства.
                textEdit_FPE->append("Строка " + QString::number(i+1) + ": Адрес точки входа в программу " + this->prog_names.first() + " находится за пределами адресного пространства (директива END)!\n"
                                                                          "Адресное пространство: от " + Convert::ConvertDecToHex(this->load_addresses.first()).rightJustified(6,'0') + " до " +
                                                                Convert::ConvertDecToHex(this->address_counters.first()).rightJustified(6, '0') + ".\n");
                return false;
            }
            break;
        }

        //Проверка строки исходного текста программы на корректность.
        if (!checks.CheckRowSourceCode(textEdit_FPE, i, prog_names, TCO, label, mnemonic_code)){
            return false;
        }

        /*-------------------------------------
         * 4.2. Анализируем поле метки в ТСИ. |
         -------------------------------------*/
        QString address{}, name_type{};
        //Если метка не пустая.
        if (!label.isEmpty()){
            bool symb_name_found{};
            //Сначала проверяем метку в ТСИ. Название программы и названия управляющих секций, а также меток у директив EXTDEF, EXTREF, END опускаются за счет проверки МКОП.
            if (mnemonic_code != "EXTDEF" && mnemonic_code != "EXTREF" && mnemonic_code != "START" && mnemonic_code != "CSEC" && mnemonic_code != "END"){
                //В ТСИ метки и секции идут в парах. Проверяем наличие метки в ТСИ в текущей секции.
                if (symbolic_table.Find(label, address, current_CSEC, name_type)){
                    //Если нашли метку, то проверяем адрес.
                    if (!address.isEmpty()){//Если адрес установлен, то ошибка.
                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Дважды определенное символическое имя " + label + ".\n");
                        return false;
                    }
                    else{//Если адрес не установлен, но тип СИ = ВС, то ошибка (ВС не могут быть определены в текущей секции, они - внешние!).
                        if (name_type == "ВС"){
                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Символическое имя " + label + " совпадает с именем внешней ссылки (ВС).\n");
                            return false;
                        }
                    }
                    symb_name_found = true;
                }
                //Иначе при встрече СИ далее просто устанавливаем в него адрес из СА (для текущей секции).
                //Если метка встречена после директивы START или CSEC при условии наличия директивы START, то добавляем в ТСИ.
                if (start_flag && !current_CSEC.isEmpty()){//Метка корректная, назначаем адрес.
                    if (!symb_name_found){
                        symbolic_table.Insert(label, Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6, '0'), current_CSEC, name_type);
                        this->manager.AddStringToToSN(tableWidget_ToSN, symbolic_table, label, current_CSEC);
                    }
                    else{
                        symbolic_table.Update(label, current_CSEC, Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6, '0'));
                        this->manager.ChangeStringInToSN(tableWidget_ToSN, symbolic_table, label, current_CSEC);
                    }
                    label_flag = true;
                }
            }
        }
        /*------------------------------
         * 4.3. Анализируем поле МКОП  *
         * 4.4. СА = СА + длина команды*
         -----------------------------*/
        //Если поле МКОП не пустое, иначе ошибка.
        if (!mnemonic_code.isEmpty()){//МКОП не пустой.
            //Проверяем - это директива?
            QString current_mnemonic_code = checks.CheckDirective(mnemonic_code);
            if (current_mnemonic_code != ""){
                /*---------------------------------------------
                 * 1. Считываем директиву START. CA = АЗ = 0 *
                 --------------------------------------------*/
                if (current_mnemonic_code == "START"){
                    //Если START не в начале исходного текста ассемблирующей программы и встречен еще раз - это ошибка.
                    if (i == 0 && !start_flag){
                        start_flag = true;

                        QString error{};
                        //Имя программы.
                        error = checks.CheckProgrammName(label, i);
                        if (error != ""){
                            textEdit_FPE->append(error);
                            return false;
                        }else{
                            prog_names.append(label);//Добавляем в список имен текущее имя программы.
                            current_CSEC = label; //Текущее название секции = имени программы.
                        }

                        //Проверка адреса загрузки программы.
                        error = checks.CheckProgrammDownloadAddress(operand1, i);
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
                        if (operand1.isEmpty()){
                            this->load_addresses.append(0);//В список АЗ добавляем новый АЗ со значением 0.
                            textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ! Строка " + QString::number(i + 1) + ": АЗ программы установлен в 0. Рассматривается программа в полном перемещаемом формате.\n");
                        }
                        else{
                            this->load_addresses.append(Convert::ConvertHexToDec(operand1)); //В список АЗ добавляем новый АЗ со значением 0.
                        }
                        this->address_counters.append(Convert::ConvertHexToDec(operand1)); //В список СА добавляем новый СА со значением АЗ.
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
                        if (label.isEmpty()){
                            end_flag = true;
                            if (operand1.isEmpty()){
                                this->address_entry_point = this->load_addresses.first(); //Адрес ТВ в программу = АЗ самой программы.
                                operand1 = Convert::ConvertDecToHex(this->address_entry_point);
                                textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ. Строка " + QString::number(i+1) + ": Адрес точки входа в программу установлен таким же, как адрес загрузки программы.\n"
                                                                                                          "Адрес точки входа: " + Convert::ConvertDecToHex(this->load_addresses.first()).rightJustified(6, '0') + ".\n");
                            }
                            else{
                                if (!checks.CheckAmountMemoryForAddress(operand1)){
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Адрес точки входа программы содержит недопустимые символы!\n"
                                                                                              "Адрес точки входа: " + operand1 + ".\n");
                                    return false;
                                }else{
                                    //Устанавливаем адрес точки входа (если при конвертировании произошло переполнение int типа, обработается при проверке адресного пространства).
                                    this->address_entry_point = Convert::ConvertHexToDec(operand1); //Адрес ТВ в программу = операндной части.
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
                            QString str_AC = Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6,'0');
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
                    if (!start_flag){
                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Отсутствует директива START!\n");
                        return false;
                    }
                    if (label_flag){
                        if (!operand1.isEmpty()){//Если операндн не пуст.
                            if (checks.CheckCorrectAmountMemoryForDecNumber(operand1)){//Значит под выделенный байт записывается десятичное число.
                                if (checks.CheckAllocAmountMemoryForByte(operand1)){//Если десятичное число умещается в байт.
                                    //Выводим в вспомогательную таблицу строчку.
                                    QString str_AC = Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6,'0');
                                    sup_table.push_back({str_AC, mnemonic_code, operand1,""});
                                    this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                    //Увеличиваем СА = СА + кол-во рез. памяти.
                                    this->address_counters.last() += 1;//СА = СА + 1.
                                }
                                else{
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Переполнение допустимого выделения памяти для BYTE.\n"
                                                                                              "Операнд: " + operand1 + ".\n");
                                    return false;
                                }
                            }
                            else{//16ричное число или ASCII строка - неважно, сколько выделили памяти, главное, чтобы СА не переполнился.
                                if (checks.CheckCorrectAmountMemoryForHexNumber(operand1) && checks.CheckAmountMemoryForAddress(operand1.split('\'')[1])){//Выделение под 16ричное число.
                                    //Выводим в вспомогательную таблицу строчку.
                                    QString str_AC = Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6,'0');
                                    sup_table.push_back({str_AC, mnemonic_code, operand1,""});
                                    this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                    //Увеличваем СА = СА + кол-во рез. памяти (длина числа / 2 + остаточный байт; 2 символа = 1 байт).
                                    int operand_length = operand1.split('\'')[1].length();
                                    this->address_counters.last() += operand_length / 2 + operand_length % 2;
                                }
                                else{//Иначе под ASCII строку или ошибка.
                                    if (checks.CheckCorrectAmountMemoryForASCIIString(operand1)){//Выделение под ASCII строку.
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6,'0');
                                        sup_table.push_back({str_AC, mnemonic_code, operand1,""});
                                        this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                        //Увеливаем СА = СА + кол-во рез. памяти (длина ASCII строки, каждый символ = 1 байт).
                                        int operand_length = operand1.mid(2, operand1.length() - 3).length();
                                        this->address_counters.last() += operand_length;
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
                    if (!start_flag){
                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Отсутствует директива START!\n");
                        return false;
                    }
                    if (label_flag){
                        if (!operand1.isEmpty()){//Если операнд не пуст.
                            if (checks.CheckCorrectAmountMemoryForDecNumber(operand1)){//Проверка операнда на десятичное число.
                                if (checks.CheckAllocAmountMemoryForWord(operand1)){//Максимум на значение выделяется 3 байта (как и на значение СА).
                                    //Выводим в вспомогательную таблицу строчку.
                                    QString str_AC = Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6,'0');
                                    sup_table.push_back({str_AC, mnemonic_code, operand1,""});
                                    this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                    //Увеличиваем СА = СА + кол-во рез. памяти (3 байт).
                                    this->address_counters.last() += 3;//Выделение 3 байт памяти.
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
                    if (!start_flag){
                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Отсутствует директива START!\n");
                        return false;
                    }
                    if (label_flag){
                        if (!operand1.isEmpty()){
                            if (checks.CheckCorrectAmountMemoryForDecNumber(operand1)){//Можно преобразовать в число.
                                if (checks.CheckAllocAmountMemoryForRES(operand1)){//В пределах логичного (размерность Int - 4 байт: по 2 байт в обе стороны).
                                    //Выводим в вспомогательную таблицу строчку.
                                    QString str_AC = Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6,'0');
                                    sup_table.push_back({str_AC, mnemonic_code, operand1,""});
                                    this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                    //СА = СА + кол-во рез. памяти (т.е. кол-во байт * 1, т.к. подсчет СА в байтах).
                                    int reserve_byte_memory = operand1.toInt(nullptr, 10) * 1;
                                    this->address_counters.last() += reserve_byte_memory;
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
                    if (!start_flag){
                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Отсутствует директива START!\n");
                        return false;
                    }
                    if (label_flag){
                        if (!operand1.isEmpty()){
                            if (checks.CheckCorrectAmountMemoryForDecNumber(operand1)){//Можно преобразовать в число.
                                if (checks.CheckAllocAmountMemoryForRES(operand1)){//Как и для RESB - в пределах логичного.
                                    //Выводим в вспомогательную таблицу строчку.
                                    QString str_AC = Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6,'0');
                                    sup_table.push_back({str_AC, mnemonic_code, operand1,""});
                                    this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                    //СА = СА + кол-во рез. памяти (число * 3 байт).
                                    int reserve_word_memory = operand1.toInt(nullptr, 10) * 3;
                                    this->address_counters.last() += reserve_word_memory;
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
                /*----------------------------------------------------------------------------------------------------------------------------
                 * 2. Считываем описание внешних имен и заносим в ТСИ с проверкой на уникальность, адрес не назначается, ставится пометка ВИ.*
                 ----------------------------------------------------------------------------------------------------------------------------*/
                if (current_mnemonic_code == "EXTDEF"){
                    if (previous_mnemonic_code == "EXTDEF" || previous_mnemonic_code == "START" || previous_mnemonic_code == "CSEC"){
                        if (!label.isEmpty()){
                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Поле метки (метка " + label + ") не может быть задано перед директивой " + current_mnemonic_code + "!\n");
                            return false;
                        }
                        if (operand1.isEmpty()){
                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Не задано внешнее имя после директивы EXTDEF!");
                            return false;
                        }
                        //Если ВИ задано, то проверяем.
                        if (checks.CheckEXTSymbolicName(textEdit_FPE, i, prog_names, TCO, operand1, "ВИ")){
                            QString address{}, name_type{};
                            //Проверка на уникальность ВИ среди занесенных ВИ текущей секции.
                            if (symbolic_table.Find(operand1, address, current_CSEC, name_type)){
                                textEdit_FPE->append("Строка " + QString::number(i+1) + ": Дважды определенное внешнее имя " + operand1 + ".\n");
                                return false;
                            }
                            //Корректно => добавляем в ТСИ с пометкой ВИ.
                            symbolic_table.Insert(operand1, "", current_CSEC, "ВИ");
                            this->manager.AddStringToToSN(tableWidget_ToSN, symbolic_table, operand1, current_CSEC);
                            //Выводим в вспомогательную таблицу строчку.
                            sup_table.push_back({label, mnemonic_code, operand1, ""});
                            this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                            //Второй операнд не учитывается.
                            QString error = checks.CheckOtherOperandPart(operand2, mnemonic_code, i);
                            if (error != ""){
                                textEdit_FPE->append(error);
                            }
                        }
                        else{//Ошибка.
                            return false;
                        }
                    }
                    else{
                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Неверная позиция директивы EXTDEF.\n");
                        return false;
                    }
                }
                /*----------------------------------------------------------------------------------------------------------------------------
                 * 3. Считываем описание внешних ссылок и заносим в ТСИ с проверкой на уникальность, адрес не назначается, ставится пометка ВС.*
                 ----------------------------------------------------------------------------------------------------------------------------*/
                if (current_mnemonic_code == "EXTREF"){
                    if (previous_mnemonic_code == "EXTREF" || previous_mnemonic_code == "EXTDEF"|| previous_mnemonic_code == "START" || previous_mnemonic_code == "CSEC"){
                        if (!label.isEmpty()){
                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Поле метки (метка " + label + ") не может быть задано перед директивой " + current_mnemonic_code + "!\n");
                            return false;
                        }
                        if (operand1.isEmpty()){
                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Не задана внешняя ссылка после директивы EXTREF!");
                            return false;
                        }
                        //Если ВС задана, то проверяем.
                        if (checks.CheckEXTSymbolicName(textEdit_FPE, i, prog_names, TCO, operand1, "ВС")){
                            QString address{}, name_type{};
                            //Проверка на уникальность ВС среди занесенных ВС текущей секции.
                            if (symbolic_table.Find(operand1, address, current_CSEC, name_type)){
                                if (name_type != "ВС")
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Метка " + operand1 + " уже определена внешнем именем!\n");
                                else
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Дважды определенная внешняя ссылка " + operand1 + ".\n");
                                return false;
                            }
                            //Корректно => добавляем в ТСИ с пометкой ВС.
                            symbolic_table.Insert(operand1, "", current_CSEC, "ВС");
                            this->manager.AddStringToToSN(tableWidget_ToSN, symbolic_table, operand1, current_CSEC);
                            //Выводим в вспомогательную таблицу строчку.
                            sup_table.push_back({label, mnemonic_code, operand1, ""});
                            this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                            //Второй операнд не учитывается.
                            QString error = checks.CheckOtherOperandPart(operand2, mnemonic_code, i);
                            if (error != ""){
                                textEdit_FPE->append(error);
                            }
                        }
                        else{//Ошибка.
                            return false;
                        }
                    }
                    else{
                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Неверная позиция директивы EXTREF.\n");
                        return false;
                    }
                }
                if (current_mnemonic_code == "CSEC"){
                    //Если CSEC не в начале исходного текста ассемблирующей программы и встречен при наличии директивы START.
                    if (i != 0 && start_flag){
                        QString error{};
                        //Имя программы.
                        error = checks.CheckProgrammName(label, i);
                        if (error != ""){
                            textEdit_FPE->append(error);
                            return false;
                        }else{
                            //Проверка совпадения имен программы/управляющих секций.
                            for (const auto& prog_name : prog_names){
                                if (label.toUpper() == prog_name.toUpper()){
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Имя управляющей секции " + label + " совпадает с другими именами программы/управляющих секций без учета регистра!\n");
                                    return false;
                                }
                            }
                            prog_names.append(label);//Добавляем в список имен текущее имя управляющей секции.
                            current_CSEC = label; //Текущее название секции.
                        }

                        //Проверка адреса загрузки управляющей секции.
                        error = checks.CheckProgrammDownloadAddress(operand1, i);
                        if (error != ""){
                            textEdit_FPE->append(error);
                            return false;
                        }

                        //Проверка оставшейся операндной части.
                        error = checks.CheckOtherOperandPart(operand2, mnemonic_code, i);
                        if (error != ""){
                            textEdit_FPE->append(error);
                        }

                        //Устанавливаем Адрес загрузки управляющей секции и увеличиваем СА = СА + Адрес загрузки управляющей секции (СА = АЗ управляющей секции).
                        if (operand1.isEmpty()){
                            this->load_addresses.append(0);//В список АЗ добавляем новый АЗ со значением 0.
                            textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ! Строка " + QString::number(i + 1) + ": АЗ управляющей секции установлен в 0. Рассматривается программа в полном перемещаемом формате.\n");
                        }
                        else{
                            this->load_addresses.append(Convert::ConvertHexToDec(operand1)); //В список АЗ добавляем новый АЗ со значением 0.
                        }
                        QString str_AC = Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6,'0');//Последнее значение СА в предыдущей управляющей секции.
                        this->address_counters.append(Convert::ConvertHexToDec(operand1)); //В список СА добавляем новый СА со значением АЗ.
                        //Выводим в вспомогательную таблицу строчку.
                        sup_table.push_back({str_AC, mnemonic_code, label, ""});
                        this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                    }
                    //Иначе ошибка.
                    else{
                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Программа не может начинаться с управляющей секции.\n");
                        return false;
                    }
                }
            }
            //Проверяем - это команда?
            else{
                TCOElem TCO_elem{};//Для получения элемента ТКО.
                if (TCO.Find(mnemonic_code, TCO_elem))
                {
                    if (!start_flag){
                        textEdit_FPE->append("Строка " + QString::number(i+1) + ": Отсутствует директива START!\n");
                        return false;
                    }
                    //Различная обработка в зависимости от байт команды - обработка общая, не специализрованная на определенные команды.
                    if (TCO_elem.code_size == "1"){//Однобайтная команда.
                        //Один байт выделяется под МКОП, на операнды памяти не выделяется - они не рассматриваются. Например, NOP.
                        //Тип адресации считается никаким, т.е прибавляется 0.
                        int opcode = checks.GetDecOpcode(TCO_elem.binary_code, 0);//Р.дв.код = дв.код * 4 + тип адр.
                        if (opcode != -1){
                            //Выводим в вспомогательную таблицу строчку.
                            QString str_AC = Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6,'0');
                            sup_table.push_back({str_AC, Convert::ConvertDecToHex(opcode).rightJustified(2,'0'),"",""});
                            this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                            //Увеличиваем СА = СА + длина команды.
                            this->address_counters.last() += 1;
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
                                    QString str_AC = Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6,'0');
                                    sup_table.push_back({str_AC, Convert::ConvertDecToHex(opcode).rightJustified(2,'0'),operand1,""});
                                    this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                    //Увеличиваем СА = СА + длина команды.
                                    this->address_counters.last() += 2;
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
                                    QString str_AC = Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6,'0');
                                    sup_table.push_back({str_AC, Convert::ConvertDecToHex(opcode).rightJustified(2,'0'),operand1,operand2});
                                    this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                                    //Увеличиваем СА = СА + длина команды.
                                    this->address_counters.last() += 2;
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
                        //Один байт выделяется под МКОП, на операндную часть выделяется 2 байта.
                        //Тип адресации прямая или относительная (зависит от модификаторов операндной части [])
                        if (operand1.isEmpty()){
                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Не обнаружена операндная часть в команде " +
                                                 TCO_elem.mnemonic_code + "!\n");
                            return false;
                        }
                        int opcode = 0;
                        if ((operand1[0] == '[') && (operand1[operand1.length() - 1] == ']')){//Относительная адресация = 2б.
                            if (type_addr == 0){
                                textEdit_FPE->append("Строка " + QString::number(i+1) + ": Обнаружена попытка относительной адресации. Выбранная адресация - прямая!\n");
                                return false;
                            }
                            else{
                                opcode = checks.GetDecOpcode(TCO_elem.binary_code, 2);
                            }
                        }else{//Прямая адресация = 1б.
                            if (type_addr != 1)
                                opcode = checks.GetDecOpcode(TCO_elem.binary_code, 1);
                            else{
                                bool EXT_ref{false};
                                QString address{}, name_type{};
                                if (symbolic_table.Find(operand1, address, current_CSEC, name_type)){
                                    if (name_type == "ВС")
                                        EXT_ref = true;
                                }
                                if (!EXT_ref){//Если не внешняя ссылка, то ошибка (ВС не могут использоваться с относительной адресацией).
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Обнаружена попытка прямой адресации. Выбранная адресация - относительная!\n");
                                    return false;
                                }
                            }
                        }
                        if (opcode != -1){
                            //Выводим в вспомогательную таблицу строчку.
                            QString str_AC = Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6,'0');
                            sup_table.push_back({str_AC, Convert::ConvertDecToHex(opcode).rightJustified(2,'0'),operand1,""});
                            this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                            //Увеличиваем СА = СА + длина команды.
                            this->address_counters.last() += 3;
                            //Второй операнд не учитывается.
                            if (!operand2.isEmpty()){
                                textEdit_FPE->append("ПРЕДУПРЕЖДЕНИЕ! Строка " + QString::number(i+1) + ": Второй операнд учитываться не будет в команде " +
                                                     TCO_elem.mnemonic_code + "!\nОперанд: " + operand2 + ".\n");
                            }
                        }
                    }
                    if (TCO_elem.code_size == "4"){//Четырехбайтная команда.
                        //Один байт выделяется под МКОП, на операндную часть выделяется 3 байта.
                        //Тип адресации прямая или относительная (зависит от модификаторов операндной части [])
                        if (operand1.isEmpty()){
                            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Не обнаружена операндная часть в команде " +
                                                 TCO_elem.mnemonic_code + "!\n");
                            return false;
                        }
                        int opcode = 0;
                        if ((operand1[0] == '[') && (operand1[operand1.length() - 1] == ']')){//Относительная адресация = 2б.
                            if (type_addr == 0){
                                textEdit_FPE->append("Строка " + QString::number(i+1) + ": Обнаружена попытка относительной адресации. Выбранная адресация - прямая!\n");
                                return false;
                            }
                            else{
                                opcode = checks.GetDecOpcode(TCO_elem.binary_code, 2);
                            }
                        }else{//Прямая адресация = 1б.
                            if (type_addr != 1)
                                opcode = checks.GetDecOpcode(TCO_elem.binary_code, 1);
                            else{
                                bool EXT_ref{false};
                                QString address{}, name_type{};
                                if (symbolic_table.Find(operand1, address, current_CSEC, name_type)){
                                    if (name_type == "ВС")
                                        EXT_ref = true;
                                }
                                if (!EXT_ref){//Если не внешняя ссылка, то ошибка (ВС не могут использоваться с относительной адресацией).
                                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": Обнаружена попытка прямой адресации. Выбранная адресация - относительная!\n");
                                    return false;
                                }
                            }
                        }
                        if (opcode != -1){
                            //Выводим в вспомогательную таблицу строчку.
                            QString str_AC = Convert::ConvertDecToHex(this->address_counters.last()).rightJustified(6,'0');
                            sup_table.push_back({str_AC, Convert::ConvertDecToHex(opcode).rightJustified(2,'0'),operand1,""});
                            this->manager.AddStringToAuxTable(tableWidget_auxTable, sup_table[i]);
                            //Увеличиваем СА = СА + длина команды.
                            this->address_counters.last() += 4;
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
                    textEdit_FPE->append("Строка " + QString::number(i+1) + ": МКОП " + mnemonic_code + " не найден в ТКО.");
                    return false;
                }
            }
            //Прошлый МКОП = МКОП на предыдущей итерации.
            previous_mnemonic_code = current_mnemonic_code;
        }else{
            textEdit_FPE->append("Строка " + QString::number(i+1) + ": Поле МКОП не может быть пустым.");
            return false;
        }
    }
    if (!end_flag){
        textEdit_FPE->append("Не найдена точка входа в программу (END)!");
        return false;
    }
    else{
        if (this->address_entry_point > this->address_counters.first() || this->address_entry_point < this->load_addresses.first()){
            textEdit_FPE->append("Адрес точки входа в программу находится за пределами адресного пространства (директива END)!\n"
                                 "Адресное пространство: от " + Convert::ConvertDecToHex(this->load_addresses.first()).rightJustified(6, '0') + " до " +
                                 Convert::ConvertDecToHex(this->address_counters.first()).rightJustified(6, '0') + ".\n");
            return false;
        }
    }
    /* -----------------------------------
     * 5. Проверяем ТСИ на корректность  *
     * ----------------------------------*/
    //Проверка ТСИ на определенное внешних имен.
    if (!checks.CheckToSNForCorrectEXTDEFAddress(textEdit_FPE, tableWidget_ToSN)){
        return false;
    }
    return true;
}

//Второй проход двухпросмотровой схемы простого ассемблера.
bool PassProcessor::SecondPass(QTableWidget *tableWidget_OMH,  QTableWidget* tableWidget_modTable,
                               QTextEdit *textEdit_SPE, QTextEdit *textEdit_binary_code,
                               const std::vector<SupportTable> &sup_table, const SymbolicNameTable &symbolic_table)
{
    //Очищаем таблицу заголовка объектного модуля и устанавливаем 3 столбца, 1 строку.
    tableWidget_OMH->clear();
    tableWidget_OMH->setColumnCount(3);
    tableWidget_OMH->setRowCount(1);
    //Очищаем таблицу модификаторов и устанавливаем 2 столбец и 1 строку.
    tableWidget_modTable->clear();
    tableWidget_modTable->setColumnCount(2);
    tableWidget_modTable->setRowCount(1);
    //Поле ошибок первого прохода тоже.
    textEdit_SPE->clear();

    //Переменная для запоминания имени текущей секции.
    QString current_CSEC{};

    for (int i{}; i < sup_table.size(); ++i){
        QString label{sup_table[i].address_counter};
        QString mnemonic_code{sup_table[i].operation_code};
        QString operand1{sup_table[i].operand1};
        QString operand2{sup_table[i].operand2};

        //Если это начало новой программы или новой управляющей секции, формируем запись-заголовок.
        if (mnemonic_code == "START" || mnemonic_code == "CSEC"){
            //В случае директивы START просто формируем запись-заголовок.
            if (mnemonic_code == "START"){
                //Вычисляем длину программы.
                int length_programm{this->address_counters.first() - this->load_addresses.first()};
                //Добавляем строку в МПФФ.
                manager.AddStringToOMH(tableWidget_OMH, label, Convert::ConvertDecToHex(this->load_addresses.first()).rightJustified(6, '0'), Convert::ConvertDecToHex(length_programm).rightJustified(6, '0'));
                //Добавляем строку в двоичный код.
                textEdit_binary_code->append("H_" + label + "_" +
                                             Convert::ConvertDecToHex(this->load_addresses.first()).rightJustified(6, '0') + "_" +
                                             Convert::ConvertDecToHex(length_programm).rightJustified(6, '0'));
                //Заносим имя программы в переменную.
                current_CSEC = label;
                //Удаляем использованные элементы из вспомогательных структур.
                this->prog_names.removeFirst();
                this->address_counters.removeFirst();
                this->load_addresses.removeFirst();
            }
            //Иначе сгружаем из ТМ записи-M и формируем запись-конец предыдущей секции, затем запись-заголовок новой управляющей секции.
            else{
                //Сгружаем из ТМ записи предыдущей секции.
                for (int row = 0; row < tableWidget_modTable->rowCount() - 1; ++row){
                    QTableWidgetItem* item = tableWidget_modTable->item(row, 1);
                    if (item && !item->text().isEmpty() && item->text() == current_CSEC){
                        item = tableWidget_modTable->item(row, 0);
                        if (item){
                            QStringList parts = item->text().split(" ");
                            QString OAMK = parts[0];
                            QString EXTR{(parts.length() > 1) ? parts[1] : ""};
                            textEdit_binary_code->append("M_" + OAMK.rightJustified(6, '0') + (!EXTR.isEmpty() ? "_" + EXTR : ""));
                        }
                    }
                }
                //Формируем запись-конец предыдущей секции.
                textEdit_binary_code->append("E_" + Convert::ConvertDecToHex(0).rightJustified(6,'0'));

                //Фомируем запись заголовок новой управляющей секции.
                //Вычисляем длину программы.
                int length_programm{this->address_counters.first() - this->load_addresses.first()};
                //Добавляем строку в МПФФ.
                manager.AddStringToOMH(tableWidget_OMH, operand1, Convert::ConvertDecToHex(this->load_addresses.first()).rightJustified(6, '0'), Convert::ConvertDecToHex(length_programm).rightJustified(6, '0'));
                //Добавляем строку в двоичный код.
                textEdit_binary_code->append("H_" + operand1 + "_" +
                                             Convert::ConvertDecToHex(this->load_addresses.first()).rightJustified(6, '0') + "_" +
                                             Convert::ConvertDecToHex(length_programm).rightJustified(6, '0'));
                //Заносим имя управляющей секции в переменную.
                current_CSEC = operand1;
                //Удаляем использованные элементы из вспомогательных структур.
                this->prog_names.removeFirst();
                this->address_counters.removeFirst();
                this->load_addresses.removeFirst();
            }
        }
        //Формируем запись ВИ.
        else if (mnemonic_code == "EXTDEF"){
            QString address{}, name_type{};
            if (symbolic_table.Find(operand1, address, current_CSEC, name_type)){
                textEdit_binary_code->append("D_" + operand1 + "_" + address.rightJustified(6, '0'));
            }
        }
        //Формируем запись ВС.
        else if (mnemonic_code == "EXTREF"){
            textEdit_binary_code->append("R_" + operand1);
        }
        //Сгружмаем из ТМ записи-М текущей секции и формируем запись конец.
        else if (mnemonic_code == "END"){
            //Сгружаем из ТМ записи текущей секции.
            for (int row = 0; row < tableWidget_modTable->rowCount() - 1; ++row){
                QTableWidgetItem* item = tableWidget_modTable->item(row, 1);
                if (item && !item->text().isEmpty() && item->text() == current_CSEC){
                    item = tableWidget_modTable->item(row, 0);
                    if (item){
                        QStringList parts = item->text().split(" ");
                        QString OAMK{parts[0]};
                        QString EXTR{(parts.length() > 1) ? parts[1] : ""};
                        textEdit_binary_code->append("M_" + OAMK.rightJustified(6, '0') + (!EXTR.isEmpty() ? "_" + EXTR : ""));
                    }
                }
            }
            //Формируем запись-конец текущей секции.
            textEdit_binary_code->append("E_" + Convert::ConvertDecToHex(this->address_entry_point).rightJustified(6,'0'));
            break;
        }
        //Иначе формируем запись-тело.
        else{
            //Переменные для записи двоичного представления команд и данных (адрес метки, число, строка и тд.).
            QString binary_view{};
            QString data{};
            //Директивы START, END, EXTREF, EXTDEF, CSEC встречены быть не могут, т.к. обработаны выше.
            if (checks.CheckDirective(mnemonic_code) != ""){//Директивы BYTE, WORD, RESB, RESW.
                if (checks.CheckCorrectAmountMemoryForDecNumber(operand1)){//Операнд является числом в 10 СИ.
                    if (mnemonic_code=="RESB" || mnemonic_code=="RESW"){//Директивы резервирования памяти.
                        binary_view="";
                        data="";
                    }
                    else{//Директивы выделения памяти под 1б (BYTE) или 3б (WORD).
                        binary_view="";
                        data = Convert::ConvertDecToHex(operand1.toInt());
                        sup_table[i].operation_code == "BYTE" ? (data = data.rightJustified(2, '0')) : (data = data.rightJustified(6, '0'));
                    }
                }
                else{//Это либо ASCII-строка, либо число в 16 СИ.
                    if (checks.CheckCorrectAmountMemoryForHexNumber(operand1)){//Это число в 16 СИ.
                        binary_view="";
                        data = operand1.split('\'')[1];
                    }
                    else{//Это ASCII-строка.
                        binary_view="";
                        QString unicode_string{operand1.mid(2, operand1.length() - 3)};
                        for (QChar chr : unicode_string){
                            int ASCII_code = chr.unicode();
                            data.append(Convert::ConvertDecToHex(ASCII_code));
                        }
                    }
                }
            }
            else{//Иначе это может быть только реальный двоичный КОП.
                //Если = 0, то непосредственная/регистровая адресация, если 1 - прямая, иначе - относительная.
                int type_addr{Convert::ConvertHexToDec(mnemonic_code) & 0x03};
                if (type_addr == 0){//Операнды могут не быть, а могут быть.
                    if (!operand1.isEmpty() && !operand2.isEmpty()){//Два операнда-регистра (проверка регистровой адресации в первом проходе).
                        binary_view = mnemonic_code;
                        data = Convert::ConvertDecToHex(operand1.split('R')[1].toInt()) +
                               Convert::ConvertDecToHex(operand2.split('R')[1].toInt());
                    }
                    else if (!operand1.isEmpty() && operand2.isEmpty()){//Один операнд-число (проверка непосредственной адресации в первом проходе).
                        binary_view = mnemonic_code;
                        data = Convert::ConvertDecToHex(operand1.toInt()).rightJustified(2,'0');
                    }
                    else{//Нет операндов.
                        binary_view = mnemonic_code;
                        data = "";
                    }
                }
                else if (type_addr == 1){//Операндная часть обязана быть - прямая адресация (обработано на первом проходе).
                    QString address{}, name_type{};
                    //Поиск СИ в ТСИ (операнд точно СИ).
                    if (symbolic_table.Find(operand1, address, current_CSEC, name_type)){
                        binary_view = mnemonic_code;

                        //Необходимо занести в ТМ ОАМК + ВС, в двоичный код - адрес СИ = 000000.
                        if (name_type == "ВС"){
                            this->manager.AddStringToTM(tableWidget_modTable, label + " " + operand1, current_CSEC);
                            data = address.rightJustified(6, '0');
                        }
                        //Иначе в ТМ ОАМК, в двоичный код - ОАСИ из ТСИ.
                        else{
                            this->manager.AddStringToTM(tableWidget_modTable, label, current_CSEC);
                            data = address;
                        }
                    }
                    else{
                        textEdit_SPE->append("Строка " + QString::number(i+1) + ": Неверно задан операнд, т.к. тип адресации (прямая) подразумевает, "
                                                                                  "что операнд является меткой. Метка: " + sup_table[i].operand1 + " не найдена в ТСИ текущей секции.");
                        return false;
                    }
                }
                else{//Операндная часть обязана быть - относительная адресация (обработано на первом проходе).
                    QString address{}, name_type{};
                    QString operand = operand1.mid(1, operand1.length() - 2);
                    //Поиск СИ в ТСИ (операнд точно должен быть СИ).
                    if (symbolic_table.Find(operand, address, current_CSEC, name_type)){
                        binary_view = sup_table[i].operation_code;

                        //Необходимо занести в ТМ ОАМК + ВС, в двоичный код - адрес СИ = 000000.
                        if (name_type == "ВС"){
                            textEdit_SPE->append("Строка " + QString::number(i+1) + ": Неверно задан операнд, т.к. тип адресации (относительная) не может быть "
                                                                                      "использован со внешними ссылками!\n");
                            return false;
                        }
                        //Иначе в двоичный код - смещение = ОАСИ из ТСИ - СА.
                        else{
                            data = Convert::SubTwoHexNumbers(address, sup_table[i + 1].address_counter);;
                        }
                    }
                    else{
                        textEdit_SPE->append("Строка " + QString::number(i+1) + ": Неверно задан операнд, т.к. тип адресации (относительная) подразумевает, "
                                                                                  "что операнд является меткой. Метка: " + operand + " не найдена в ТСИ текущей секции.");
                        return false;
                    }
                }
            }
            //Вывод результатов в поле двоичного кода.
            textEdit_binary_code->append("T_" + label + "_" +
                                         Convert::ConvertDecToHex(binary_view.length() + data.length()).rightJustified(2, '0') +
                                         (binary_view.isEmpty() ? "" : "_") + binary_view +
                                         (data.isEmpty() ? "" : "_") + data);
        }
    }
    return true;
}
