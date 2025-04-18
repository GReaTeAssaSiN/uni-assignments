#include "Checks.h"
#include "Convert.h"

//ВНУТРЕННИЕ ПРОВЕРКИ//
//Проверка на регистр (поле Операндная часть).
QString Checks::CheckRegister(const QString& reg){
    std::array<QString, 16> regsMass = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15"};
    for (int i{}; i < regsMass.size(); ++i){
        if (reg == regsMass[i])
            return reg;
    }
    return "";
}
//Проверка длины символического имени (СИ).
bool Checks::CheckLengthSymbolicName(const QString &symbolic_name)
{
    if (!symbolic_name.isEmpty() && symbolic_name.length() > 6)
        return false;
    return true;
}
//Посимвольная проверка корректности СИ.
bool Checks::CheckCharsSymbolicName(const QString &symbolic_name)
{
    if (symbolic_name.isEmpty())//Если пустая, то хорошо.
        return true;
    if (!(symbolic_name[0] >= 'A' && symbolic_name[0] <= 'Z')){//Должна начинаться с буквы.
        return false;
    }
    for (int i{1}; i < symbolic_name.length(); ++ i){//Остальные символы могут быть цифрами/буквами.
        QChar currentChar = symbolic_name[i];
        if (!((currentChar >= '0' && currentChar <= '9') || (currentChar >= 'A' && currentChar <= 'Z'))){
            return false;
        }
    }
    return true;
}
//Проверка совпадения метки с названием директивы или регистром (аналогично для МКОП в ТКО).
bool Checks::CheckIncorrectSymbolicName(const QString &symbolic_name)
{
    if (!CheckDirective(symbolic_name).isEmpty() || !CheckRegister(symbolic_name).isEmpty())
        return false;
    return true;
}
//Посимвольная проверка корректности МКОП.
bool Checks::CheckCharsMCOP(const QString &mnemonic_code)
{
    if (mnemonic_code.isEmpty())//Если пусто, то нехорошо, но проверять нечего.
        return true;
    for (int i{1}; i < mnemonic_code.length(); ++ i){//Cимволы могут быть цифрами/буквами.
        QChar currentChar = mnemonic_code[i];
        if (!((currentChar >= '0' && currentChar <= '9') || (currentChar >= 'A' && currentChar <= 'Z'))){
            return false;
        }
    }
    if (!(mnemonic_code[0] >= 'A' && mnemonic_code[0] <= 'Z'))
        return false;
    return true;
}
//Проверка совпадения СИ с коммандой в ТКО.
bool Checks::CheckSymbolicNameIsCommand(const TableCodeOperation &opcode_table, const QString& label)
{
    TCOElem TCO_elem;//Для получения элемента ТКО.
    if (opcode_table.Find(label, TCO_elem))
        return true;
    return false;
}

//ПРОВЕРКИ//
//Проверка ТСИ на корректные адреса у всех ВИ.
bool Checks::CheckToSNForCorrectEXTDEFAddress(QTextEdit *textEdit_FPE, QTableWidget *tableWidget_ToSN)
{
    int rowCount = tableWidget_ToSN->rowCount();
    for (int i{}; i < rowCount; ++i){
        QTableWidgetItem *Item2 = tableWidget_ToSN->item(i, 1); // 2-й столбец.
        QTableWidgetItem *Item4 = tableWidget_ToSN->item(i, 3); // 4-й столбец.

        // Проверяем, что элемент существует и его значение равно "ВИ".
        if (Item2 && Item4 && Item4->text() == "ВИ") {
            // Проверяем, что 2-й столбец не пустой.
            if (!Item2 || Item2->text().isEmpty()) {
                textEdit_FPE->append("Найдено неопределенное внешнее имя: " + tableWidget_ToSN->item(i, 0)->text() + "!\n");
                return false;
            }
        }
    }
    return true;
}

//Проверка символического имени в EXTDEF и EXTREF.
bool Checks::CheckEXTSymbolicName(QTextEdit *textEdit_FPE, const int &row, const QStringList &prog_names, const TableCodeOperation &TCO, const QString& symbolic_name, const QString& type_name)
{
    QString error{};
    if (!symbolic_name.isEmpty()){//Если метка не пустая.
        if (!CheckCharsSymbolicName(symbolic_name)){ //Символы метки.
            error = "Строка " + QString::number(row+1) + ": " + (type_name == "ВИ" ? "ВИ " : "ВС " ) + symbolic_name + " содержит недопустимые символы, отличные от цифр и заглавных букв, или начинается не с буквы!\n";
            textEdit_FPE->append(error);
            return false;
        }
        if (!CheckIncorrectSymbolicName(symbolic_name) || CheckSymbolicNameIsCommand(TCO, symbolic_name)){//Совпадение метки по названию (зарезервированное слово).
            error = "Строка " + QString::number(row+1) + ": " + (type_name == "ВИ" ? "ВИ " : "ВС " ) + symbolic_name + " совпадает с директивой, регистром или МКОП в ТКО.\n";
            textEdit_FPE->append(error);
            return false;
        }
        //Проверка совпадения СИ с названием программы или управляющей секции.
        if (symbolic_name == prog_names.first()){
            error = "Строка " + QString::number(row+1) + ": " + (type_name == "ВИ" ? "ВИ " : "ВС " ) + symbolic_name + " совпадает с названием программы без учета регистра. Измените название программы или " + (type_name == "ВИ" ? "ВИ" : "ВС" ) + "!\n";
            textEdit_FPE->append(error);
            return false;
        }
        if (symbolic_name == prog_names.last()){
            error = "Строка " + QString::number(row+1) + ": " + (type_name == "ВИ" ? "ВИ " : "ВС " ) + symbolic_name + " совпадает с названием управляющей секции без учета регистра. Измените название управляющей секции или " + (type_name == "ВИ" ? "ВИ" : "ВС" ) + "!\n";
            textEdit_FPE->append(error);
            return false;
        }
    }
    return true;
}

//Проверка ТКО.
bool Checks::CheckTableCodeOperation(const TableCodeOperation& TCO, QTextEdit *textEdit_FPE)
{
    const std::vector<TCOElem> opcode_table = TCO.GetOpcodeTable();
    for (int row{}; row < opcode_table.size(); ++row){
        //Проверка ячеек на пустоту.
        if (!opcode_table[row].mnemonic_code.isEmpty() && (opcode_table[row].binary_code.isEmpty()
                                                           || opcode_table[row].code_size.isEmpty()))
        {
            textEdit_FPE->append("Пустая ячейка в ТКО не допустима.\n");
            return false;
        }
        if (opcode_table[row].mnemonic_code.isEmpty() && (!opcode_table[row].binary_code.isEmpty()
                                                          || !opcode_table[row].code_size.isEmpty()))
        {
            textEdit_FPE->append("Пустая ячейка в ТКО не допустима.\n");
            return false;
        }
        //По заполненным строкам.
        if (!opcode_table[row].mnemonic_code.isEmpty())
        {
            //Проверка ячеек на длину.
            if (opcode_table[row].mnemonic_code.length() > 7 || opcode_table[row].binary_code.length() > 2
                || opcode_table[row].code_size.length() > 1)
            {
                textEdit_FPE->append("МКОП в ТКО должен быть от 1 до 7 символов, двоичный код МКОП - от 1 до 2 символов, длина МКОП в байтах - не более одного символа.\n");
                return false;
            }
            //Проверка посимвольно МКОП.
            if (!CheckCharsMCOP(opcode_table[row].mnemonic_code)){
                textEdit_FPE->append("МКОП в ТКО должен начинаться с буквы и не содержать некорректных символов, отличных от цифр и заглавных букв.\n");
                return false;
            }
            //Проверка МКОП на зарезервированное слово.
            if (!CheckIncorrectSymbolicName(opcode_table[row].mnemonic_code)){
                textEdit_FPE->append("МКОП в ТКО не может совпадать с директивой или регистром.\n");
                return false;
            }
            //Проверка команд LOAD и SAVE.
            if (opcode_table[row].mnemonic_code.startsWith("LOAD") || opcode_table[row].mnemonic_code.startsWith("SAVE")){
                //Проверка комманд LOAD и SAVE на указание регистра в своем названии.
                static const QRegularExpression load_save_check{R"(^(LOAD|SAVE)(R([0-9]|1[0-5]))$)"};
                if (!load_save_check.match(opcode_table[row].mnemonic_code).hasMatch()){
                    textEdit_FPE->append("МКОП LOAD или SAVE в ТКО должен содержать в названии регистр R0, R1, R2,... или R15. ");
                    return false;
                }
            }
            //Проверка двоичного кода МКОП.
            if (CheckAmountMemoryForAddress(opcode_table[row].binary_code)){
                int bin_code_dec = Convert::ConvertHexToDec(opcode_table[row].binary_code);
                const int MAX_BINARY_CODE{63};//(р.дв.КОП)Т.к. 63*4=252, а двоичный код МКОП максимум может принимать значение 255. Поэтому на адресацию в запасе остается от 0 до 3 бит.
                if (bin_code_dec > MAX_BINARY_CODE){
                    textEdit_FPE->append("Двоичный код МКОП в 16-ричной СИ не должен превышать " + Convert::ConvertDecToHex(MAX_BINARY_CODE) + ".\n");
                    return false;
                }
            }
            else{
                textEdit_FPE->append("Двоичный код МКОП должен быть представлен из символов 16-ричной СИ.\n");
                return false;
            }
            //Проверка длины команды.
            if (CheckCorrectAmountMemoryForDecNumber(opcode_table[row].code_size)){
                QString size_mcop = opcode_table[row].code_size;//Получение длины МКОП в байтах.
                bool ok{false};//Учет успешной конвертации из QString -> int.
                int size_mcop_int = size_mcop.toInt(&ok);
                if (ok){
                    if (size_mcop_int <= 0 || size_mcop_int > 4){
                        textEdit_FPE->append("Длина МКОП в байтах может принимать значения 1, 2, 3 или 4 байт без учета специфики МКОП.\n");
                        return false;
                    }
                }else{
                    textEdit_FPE->append("Длина МКОП в байтах превышает логически допустимый объем байт при учете ограничений.\n");
                    return false;
                }
            }
            else{
                textEdit_FPE->append("Длина команды должна состоять из цифр десятичной СИ.");
                return false;
            }
            //Проверка уникальности МКОП в ТКО.
            for (int k = row+1; k < opcode_table.size(); ++k){
                QString mcop_first = opcode_table[row].mnemonic_code;
                QString mcop_second = opcode_table[k].mnemonic_code;
                if (mcop_first == mcop_second){
                    textEdit_FPE->append("Найдены совпадения в названиях МКОП!\nСовпадающий МКОП: " + mcop_first + ".\n");
                    return false;
                }
            }
            //Проверка уникальности двоичного кода МКОП в ТКО.
            for (int k = row+1; k < opcode_table.size(); ++k){
                if (!opcode_table[k].mnemonic_code.isEmpty()){
                    QString bin_code_first = opcode_table[row].binary_code.rightJustified(2,'0');
                    QString bin_code_second = opcode_table[k].binary_code.rightJustified(2,'0');
                    if (bin_code_first == bin_code_second){
                        textEdit_FPE->append("Найдены совпадения в двоичных кодах МКОП!\nСовпадающий двоичный код МКОП: " + bin_code_first + ".\n");
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

//Проверка корректности указания объема памяти посимвольно (вообще, для 16-ричных чисел).
bool Checks::CheckAmountMemoryForAddress(const QString &amountMemory)
{
    std::array<char,16> hexMass = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    for (auto const& chr : amountMemory){
        if (std::find(hexMass.begin(), hexMass.end(), chr) == hexMass.end()){
            return false;
        }
    }
    return true;
}

//Проверка, что СА <= допустимого объема памяти.
bool Checks::CheckAddressCounterAvailable(QTextEdit* textEdit_FPE, const int& row, const int &address_counter){
    const int MAX_AMOUNT_ALLOC_MEMORY{16777215};
    if (address_counter > MAX_AMOUNT_ALLOC_MEMORY){
        //Если переполнение зафиксировано на текущей строке, то возникло оно на предыдущей.
        textEdit_FPE->append("Строка " + QString::number(row) + ": Произошло переполнение СА! СА = " + Convert::ConvertDecToHex(address_counter).rightJustified(6,'0') + ".\n");
        return false;
    }
    return true;
}

//Проверка каждой строки исходного кода ассмеблирующей программы.
bool Checks::CheckRowSourceCode(QTextEdit *textEdit_FPE, const int &row, const QStringList& prog_names, const TableCodeOperation& TCO, const QString &label, const QString &mnemonic_code)
{
    QString error{};//Для записи ошибок.
    //Проверка метки.
    if (row != 0 && mnemonic_code != "CSEC" && mnemonic_code != "EXTREF" && mnemonic_code != "EXTDEF" && mnemonic_code != "END" && !label.isEmpty()){
        if (!CheckLengthSymbolicName(label)){//Длина метки.
            error = "Строка " + QString::number(row+1) + ": Длина СИ должна быть не более 6 символов!\n";
            textEdit_FPE->append(error);
            return false;
        }
        if (!CheckCharsSymbolicName(label)){//Символы метки.
            error = "Строка " + QString::number(row+1) + ": Символическое имя содержит недопустимые символы, отличные от цифр и заглавных букв, или начинается не с буквы!\n";
            textEdit_FPE->append(error);
            return false;
        }
        if (!CheckIncorrectSymbolicName(label) || CheckSymbolicNameIsCommand(TCO, label)){//Совпадение метки по названию (зарезервированное слово).
            error = "Строка " + QString::number(row+1) + (row != 0 ? (": Символическое имя") : (": Название программы")) + " совпадает с директивой, регистром или МКОП в ТКО.\n";
            textEdit_FPE->append(error);
            return false;
        }
        bool label_is_prog_name{false};//Проверка совпадения СИ с названием программы.
        for (const auto& prog_name : prog_names){
            if (label == prog_name.toUpper()){
                label_is_prog_name = true;
            }
        }
        if (label_is_prog_name){
            error = "Строка " + QString::number(row+1) + ": Символическое имя " + label + " совпадает с названием программы/управляющей секции без учета регистра. Измените название программы/управляющей секции или символическое имя!\n";
            textEdit_FPE->append(error);
            return false;
        }
    }
    //Проверка МКОП.
    if (!CheckCharsMCOP(mnemonic_code)){//Символы МКОП.
        error = "Строка " + QString::number(row+1) + ": МКОП содержит недопустимые символы, отличные от цифр и заглавных букв, или начинается не с буквы!\n";
        textEdit_FPE->append(error);
        return false;
    }
    //Иначе все корректно на данном этапе.
    return true;
}

//Проверка имени программы.
QString Checks::CheckProgrammName(const QString &prog_name, const int& i){
    if (prog_name.isEmpty()) return "Строка " + QString::number(i+1) + ": Имя программы/управляющей секции не задано!\n";
    if (prog_name.length() > 6) return "Строка " + QString::number(i+1) + ": Имя программы/управляющей секции слишком длинное! Ограничение на длину: 6 символов.\n";
    for (const auto& symbol : prog_name) {
        int code = symbol.unicode();
        if (!((code >= 48 && code <= 57) ||   // Цифры: '0'-'9'
              (code >= 65 && code <= 90) ||   // Заглавные буквы: 'A'-'Z'
              (code >= 97 && code <= 122) ||  // Строчные буквы: 'a'-'z'
              code == 95)){                   // Подчеркивание: '_'
            return "Строка " + QString::number(i+1) + ": Имя программы/управляющей секции содержит недопустимые символы! Разрешены только цифры, буквы и символ подчеркивания.\n";
        }
    }
    if (prog_name[0] >= '0' && prog_name[0] <= '9')
        return "Строка " + QString::number(i+1) + ": Имя программы/управляющей секции не может начинаться с цифры.\n";
    if (!CheckDirective(prog_name).isEmpty() || !CheckRegister(prog_name).isEmpty()){
        return "Имя программы не может совпадать с директивой или регистром.\n";
    }
    //Проверка на совпадение метки и имени программы осуществляется в проверке строк относительно меток.
    return "";
}

//Проверка адреса загрузки программы.
QString Checks::CheckProgrammDownloadAddress(const QString& download_address, const int& i) {
    if (!download_address.isEmpty())
    {
        if (!CheckAmountMemoryForAddress(download_address)) {
            return "Строка " + QString::number(i+1) + ": Адрес загрузки программы/управляющей секции содержит недопустимые символы! Текущий адрес загрузки: " + download_address + ".";
        }
        const int MAX_LOAD_ADDRESS_VALUE{0}; //ПвППФ.
        int load_address = Convert::ConvertHexToDec(download_address);
        if (load_address > MAX_LOAD_ADDRESS_VALUE) {
            return "Строка " + QString::number(i+1) + ": АЗ программы/управляющей секции должен быть равен 0!\n";
        }
    }

    return "";
}

//Проверка наличия операндной части после директивы.
QString Checks::CheckOtherOperandPart(const QString &second_operand, const QString& mnemonic_code, const int& row)
{
    if (!second_operand.isEmpty()){
        return "ПРЕДУПРЕЖДЕНИЕ! Строка " + QString::number(row+1) + ": Второй операнд после директивы " + mnemonic_code + " учитываться не будет!\n"
                                                                                                                            "Операнд: " + second_operand + ".\n";
    }
    return "";
}

//Проверка на директиву (поле МКОП).
QString Checks::CheckDirective(const QString &mnemonic_code)
{
    if (mnemonic_code == "START") return "START";
    if (mnemonic_code == "END") return "END";
    if (mnemonic_code == "BYTE") return "BYTE";
    if (mnemonic_code == "WORD") return "WORD";
    if (mnemonic_code == "RESB") return "RESB";
    if (mnemonic_code == "RESW") return "RESW";
    if (mnemonic_code == "EXTDEF") return "EXTDEF";
    if (mnemonic_code == "EXTREF") return "EXTREF";
    if (mnemonic_code == "CSEC") return "CSEC";
    return "";
}

//Проверка корректности указания объема выделения памяти для директив BYTE, WORD, RESB, RESW.
bool Checks::CheckCorrectAmountMemoryForDecNumber(const QString &amount_memory)
{
    std::array<char,10> decMass = {'0','1','2','3','4','5','6','7','8','9'};
    for (auto const& chr : amount_memory){
        if (std::find(decMass.begin(), decMass.end(), chr) == decMass.end()){
            return false;
        }
    }
    return true;
}

//Проверка корректно указанного объема выделения памяти на доступность для BYTE (или в целом под байт).
bool Checks::CheckAllocAmountMemoryForByte(const QString &alloc_memory_byte){
    bool ok{};
    const int MAX_BYTE_MEMORY{255};
    int alloc_memory_byte_int = alloc_memory_byte.toInt(&ok);
    if (!ok || alloc_memory_byte_int > MAX_BYTE_MEMORY){
        return false;
    }
    return true;
}

//Проверка на то, что операнд после директивы BYTE начинается на 'X' и корректно задан.
bool Checks::CheckCorrectAmountMemoryForHexNumber(const QString &amount_memory) {
    if (amount_memory.startsWith('X')) {
        QStringList parts = amount_memory.split('\'');
        if (parts.size() == 3 && parts[2].isEmpty() &&
            parts[0].length() == 1 && !parts[1].isEmpty()) {
            return true;
        }
    }
    return false;
}

//Проверка на то, что операнд после директивы BYTE начинается на 'C' и корректно задан.
bool Checks::CheckCorrectAmountMemoryForASCIIString(const QString &amount_memory) {
    if (amount_memory.startsWith('C') &&
        amount_memory.endsWith("'") &&
        amount_memory.indexOf("'") == 1 &&
        amount_memory.lastIndexOf("'") == amount_memory.length() - 1) {
        return true;
    }
    return false;
}

//Проверка корректно указанного объема выделения памяти на доступность для WORD.
bool Checks::CheckAllocAmountMemoryForWord(const QString &alloc_memory)
{
    bool ok{};
    const int max_word_memory{16777215};
    int alloc_memory_word_int = alloc_memory.toInt(&ok);
    if (!ok || alloc_memory_word_int > max_word_memory){
        return false;
    }
    return true;
}

//Проверка корректно указанного объема выделения памяти на доступность для RESB или RESW.
bool Checks::CheckAllocAmountMemoryForRES(const QString &alloc_memory){
    bool ok{};
    alloc_memory.toInt(&ok);
    return ok;
}

//Получение реального двоичного кода адресации со всеми проверками.
const int Checks::GetDecOpcode(const QString &command_binary_code, const int &type_addressing)
{
    int opcode{};
    const int SHIFT{4};
    const int MAX_BYTE_MEMORY{255};
    if (command_binary_code.isEmpty()){//Если двоичный КОП пустой - это ошибка.
        return -1;
    }

    opcode = Convert::ConvertHexToDec(command_binary_code);//Получаем десятичное представление шестнадцатиричного КОП.
    opcode = opcode * SHIFT + type_addressing;//Получаем реальный двоичный код.
    if (opcode > MAX_BYTE_MEMORY){//Если резервируемая память > байта, т.е. значения 255, то ошибка.
        return -1;
    }
    return opcode;
}
