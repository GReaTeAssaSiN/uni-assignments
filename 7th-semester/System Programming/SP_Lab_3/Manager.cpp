#include "Manager.h"

//Загрузка исходного кода ассемблирующей программы в структуру.
std::vector<AssemblerInstruction> Manager::ImportSourceAssemblerCodeFromField(QTextEdit *textEdit_source) {
    std::vector<AssemblerInstruction> source_code;
    QString text = textEdit_source->toPlainText();
    QStringList lines = text.split("\n", Qt::SkipEmptyParts); // Разделяем строки, пропуская пустые.

    for (const QString &line : lines) {
        if (!line.trimmed().isEmpty()){
            AssemblerInstruction temp_code_line{};
            QStringList parts{GetLineItems(line)}; // Разделяем строку на элементы.
            // Проверяем, начинается ли строка с пробела или табуляции.
            if (line.startsWith(" ") || line.startsWith('\t')) {
                // Если да, то присваиваем элементы с учетом смешения.
                temp_code_line.label = "";
                temp_code_line.mnemonic_code = parts.size() > 0 ? parts[0] : "";
                temp_code_line.operand1 = parts.size() > 1 ? parts[1] : "";
                temp_code_line.operand2 = parts.size() > 2 ? parts.mid(2).join(" ") : ""; // Операнд 2 - все, что осталось после operand1.
            } else {
                // Иначе заполняем так же, как в parts.
                temp_code_line.label = parts.size() > 0 ? parts[0] : "";
                temp_code_line.mnemonic_code = parts.size() > 1 ? parts[1] : "";
                temp_code_line.operand1 = parts.size() > 2 ? parts[2] : "";
                temp_code_line.operand2 = parts.size() > 3 ? parts.mid(3).join(" ") : ""; // Операнд 2 - все, что осталось после operand1.
            }

            source_code.push_back(temp_code_line);
        }
    }
    return source_code;
}
//Загрузка ТКО в структуру.
TableCodeOperation Manager::ImportTCOFromTableCodeOperation(QTableWidget *tableWidget_ToOC)
{
    TableCodeOperation opcode_table{};
    for (int row{}; row < tableWidget_ToOC->rowCount() - 1; ++row)
    {
        QString mnemonic_code{tableWidget_ToOC->item(row, 0) == nullptr ? "" : tableWidget_ToOC->item(row, 0)->text()};
        QString binary_code{tableWidget_ToOC->item(row, 1) == nullptr ? "" : tableWidget_ToOC->item(row, 1)->text()};
        QString code_size{tableWidget_ToOC->item(row, 2) == nullptr ? "" : tableWidget_ToOC->item(row, 2)->text()};
        opcode_table.Insert(mnemonic_code, binary_code, code_size);
    }
    return opcode_table;
}

//Отформатированный исходный код ассемблирующей программы -> интерфейс.
void Manager::ExportFormattedSourceAssemblerCodeToField(std::vector<AssemblerInstruction> &source_code, QTextEdit* textEdit_source)
{
    textEdit_source->clear();
    for (const auto& instruction: source_code){
        LoadSourceAssemblerCodeLineToField(textEdit_source, instruction);
    }
}
//Загрузка исходного кода ассемблирующей программы в интерфейс.
void Manager::ExportDataToTextEditSource(QTextEdit* textEdit_source, const int &ex_num){
    if (!textEdit_source){
        qDebug() << "textEdit_source has returned a nullptr in a method Manager::ExportDataToTextEditSource.";
        return;
    }
    textEdit_source->clear();
    switch(ex_num){
    case 0://Только прямая адресация.
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"PROG", "START", "0", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTDEF", "D23", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTDEF", "D4", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTREF", "D2", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTREF", "D546", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"T1", "RESB", "10", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"D23", "RESW", "10", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"D4", "SAVER1", "D546", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"D42", "LOADR1", "T1", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"T2", "RESB", "10", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"A2", "CSEC", "", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTDEF", "D2", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTREF", "D4", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTREF", "D58", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"D2", "SAVER1", "D2", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"B2", "BYTE", "X\'2F4C008A\'", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"B3", "BYTE", "C\'Hello!\'", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"B4", "BYTE", "128", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "LOADR1", "B2", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "LOADR2", "B4", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "LOADR1", "D2", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"T3", "NOP", "", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "END", "0", ""});

        break;
    case 1://Только относительная адресация.
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"PROG", "START", "0", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTDEF", "D23", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTDEF", "D4", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTREF", "D2", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTREF", "D546", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"T1", "RESB", "10", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"D23", "RESW", "10", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"D4", "SAVER1", "D546", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"D42", "LOADR1", "[T1]", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"T2", "RESB", "10", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"A2", "CSEC", "", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTDEF", "D2", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTREF", "D4", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTREF", "D58", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"D2", "SAVER1", "[D2]", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"B2", "BYTE", "X\'2F4C008A\'", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"B3", "BYTE", "C\'Hello!\'", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"B4", "BYTE", "128", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "LOADR1", "[B2]", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "LOADR2", "[B4]", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "LOADR1", "[D2]", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"T3", "NOP", "", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "END", "0", ""});
        break;
    case 2://Смешанная адресация.
        textEdit_source->clear();
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"PROG", "START", "0", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTDEF", "D23", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTDEF", "D4", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTREF", "D2", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTREF", "D546", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"T1", "RESB", "10", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"D23", "RESW", "10", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"D4", "SAVER1", "D546", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"D42", "LOADR1", "[T1]", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"T", "RESB", "10", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"A2", "CSEC", "", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTDEF", "D2", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTREF", "D4", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "EXTREF", "D58", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"D2", "SAVER1", "[D2]", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"B2", "BYTE", "X\'2F4C008A\'", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"B3", "BYTE", "C\'Hello!\'", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"B4", "BYTE", "128", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "LOADR1", "B2", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "LOADR2", "[B4]", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "LOADR1", "D2", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"T3", "NOP", "", ""});
        this->LoadSourceAssemblerCodeLineToField(textEdit_source, {"", "END", "0", ""});
        break;
    case 3://Чистый ввод.
        break;
    default:
        break;
    }
}
//Загрузка ТКО в интерфейс.
void Manager::ExportDataToTableWidgetToOC(QTableWidget *tableWidget_ToOC, const int &ex_num)
{
    if (!tableWidget_ToOC) {
        qDebug() << "tableWidget_ToOC has returned a nullptr in a method TablesManager::ExportDataToTableWidgetToOC.";
        return;
    }
    tableWidget_ToOC->clear();
    tableWidget_ToOC->setColumnCount(3);
    tableWidget_ToOC->setRowCount(1);

    switch(ex_num){
    case 0://Только прямая адресация.
        LoadDataRowToToOC(tableWidget_ToOC, {"JMP", "01", "4"});
        LoadDataRowToToOC(tableWidget_ToOC, {"LOADR1", "02", "4"});
        LoadDataRowToToOC(tableWidget_ToOC, {"LOADR2", "03", "4"});
        LoadDataRowToToOC(tableWidget_ToOC, {"ADD", "04", "2"});
        LoadDataRowToToOC(tableWidget_ToOC, {"SAVER1", "05", "4"});
        LoadDataRowToToOC(tableWidget_ToOC, {"NOP","06","1"});
        LoadDataRowToToOC(tableWidget_ToOC, {"","",""});
        break;
    case 1://Только относительная адресация.
        LoadDataRowToToOC(tableWidget_ToOC, {"JMP", "01", "4"});
        LoadDataRowToToOC(tableWidget_ToOC, {"LOADR1", "02", "4"});
        LoadDataRowToToOC(tableWidget_ToOC, {"LOADR2", "03", "4"});
        LoadDataRowToToOC(tableWidget_ToOC, {"ADD", "04", "2"});
        LoadDataRowToToOC(tableWidget_ToOC, {"SAVER1", "05", "4"});
        LoadDataRowToToOC(tableWidget_ToOC, {"NOP","06","1"});
        LoadDataRowToToOC(tableWidget_ToOC, {"","",""});
        break;
    case 2://Смешанная адресация.
        LoadDataRowToToOC(tableWidget_ToOC, {"JMP", "01", "4"});
        LoadDataRowToToOC(tableWidget_ToOC, {"LOADR1", "02", "4"});
        LoadDataRowToToOC(tableWidget_ToOC, {"LOADR2", "03", "4"});
        LoadDataRowToToOC(tableWidget_ToOC, {"ADD", "04", "2"});
        LoadDataRowToToOC(tableWidget_ToOC, {"SAVER1", "05", "4"});
        LoadDataRowToToOC(tableWidget_ToOC, {"NOP","06","1"});
        LoadDataRowToToOC(tableWidget_ToOC, {"","",""});
        break;
    case 3://Чистый ввод.
        break;
    default:
        break;
    }
}
//Добавление пустой строки или удаление ненужной при необходимости.
void Manager::UpdateRowInSpecifiedTable(QTableWidget *tableWidget_specified, const int &row, const int &column)
{
    if (!tableWidget_specified) {
        qDebug() << "tableWidget_specified has returned a nullptr in a method TablesManager::updateRowInSpecifiedTable.";
        return;
    }

    //Добавление пустой строки в конце таблицы при необходимости.
    if (row == tableWidget_specified->rowCount() - 1) {
        if (tableWidget_specified->item(row, column) != nullptr &&
            !tableWidget_specified->item(row, column)->text().isEmpty()) {
            tableWidget_specified->insertRow(row + 1);
            //Инициализация всех ячеек новой строки пустыми значениями.
            for (int col = 0; col < tableWidget_specified->columnCount(); ++col) {
                tableWidget_specified->setItem(row+1, col, new QTableWidgetItem(""));
            }
        }
    }

    // Удаление лишних пустых строк в таблице.
    for (int i = 0; i < tableWidget_specified->rowCount() - 1; ++i) {
        bool rowEmpty = true;
        for (int col = 0; col < tableWidget_specified->columnCount(); ++col) {
            if (tableWidget_specified->item(i, col) != nullptr &&
                !tableWidget_specified->item(i, col)->text().isEmpty()) {
                rowEmpty = false;
                break;
            }
        }
        if (rowEmpty) {
            tableWidget_specified->removeRow(i);
            --i; //После удаления строки индексы смещаются.
        }
    }
}
//Форматирование столбца с двоичным кодом МКОП.
void Manager::TableCodeOperationFormatBinaryOpcode(QTableWidget *tableWidget_ToOC) const
{
    if (!tableWidget_ToOC) {
        qDebug() << "tableWidget_ToOC has returned a nullptr in a method TablesManager::TableCodeOperationFormatBinaryOpcode.";
        return;
    }
    for (int row{}; row < tableWidget_ToOC->rowCount() - 1; ++row){
        QTableWidgetItem* item = tableWidget_ToOC->item(row, 1);
        if (item){
            QString text = item->text();
            if (text.length() == 1) {
                text = text.rightJustified(2, '0');
                item->setText(text);
            }
        }
    }
}
//Добавление строки в вспомогательную таблицу (СА/Название программы + реальный двочиный КОП + операндная часть).
void Manager::AddStringToAuxTable(QTableWidget* tableWidget_auxTable, const SupportTable& sup_table_elem)
{
    if (!tableWidget_auxTable){
        qDebug() << "tableWidget_auxTable has returned a nullptr in a method Manager::AddStringToAuxTable";
        return;
    }
    int last_row = tableWidget_auxTable->rowCount() - 1;
    tableWidget_auxTable->setItem(last_row, 0, new QTableWidgetItem(sup_table_elem.address_counter));
    tableWidget_auxTable->setItem(last_row, 1, new QTableWidgetItem(sup_table_elem.operation_code));
    tableWidget_auxTable->setItem(last_row, 2, new QTableWidgetItem(sup_table_elem.operand1));
    tableWidget_auxTable->setItem(last_row, 3, new QTableWidgetItem(sup_table_elem.operand2));
}
//Добавление строки в ТСИ (СИ + текущий СА + секция + тип СИ).
void Manager::AddStringToToSN(QTableWidget* tableWidget_ToSN, const SymbolicNameTable& symbolic_table, const QString& symbolic_name, const QString& section){
    if (!tableWidget_ToSN){
        qDebug() << "tableWidget_ToSN has returned a nullptr in a method Manager::AddStringToToSN.";
        return;
    }
    QString address{}, name_type{};
    symbolic_table.Find(symbolic_name, address, section, name_type);
    int last_row = tableWidget_ToSN->rowCount() - 1;
    tableWidget_ToSN->setItem(last_row, 0, new QTableWidgetItem(symbolic_name));
    tableWidget_ToSN->setItem(last_row, 1, new QTableWidgetItem(address));
    tableWidget_ToSN->setItem(last_row, 2, new QTableWidgetItem(section));
    tableWidget_ToSN->setItem(last_row, 3, new QTableWidgetItem(name_type));
}
//Изменение адреса метки в ТСИ по названию метки и секции.
bool Manager::ChangeStringInToSN(QTableWidget *tableWidget_ToSN, const SymbolicNameTable& symbolic_table, const QString &symbolic_name, const QString &section)
{
    if (!tableWidget_ToSN){
        qDebug() << "tableWidget_ToSN has returned a nullptr in a method Manager::ChangeStringInToSN.";
        return false;
    }

    for (int row = 0; row < tableWidget_ToSN->rowCount(); ++row) {
        // Получение значения из первого и четвертого столбца.
        QTableWidgetItem* item1 = tableWidget_ToSN->item(row, 0); // Первый столбец.
        QTableWidgetItem* item4 = tableWidget_ToSN->item(row, 2); // Четвертый столбец.

        if (item1 && item4 && item1->text() == symbolic_name && item4->text() == section) {
            // Если условия выполнены, обновляем значение во втором столбце.
            QTableWidgetItem* item2 = tableWidget_ToSN->item(row, 1);
            if (!item2) {
                // Создаем ячейку, если она не существует.
                item2 = new QTableWidgetItem();
                tableWidget_ToSN->setItem(row, 1, item2);
            }
            QString address{}, name_type{};
            symbolic_table.Find(symbolic_name, address, section, name_type);
            item2->setText(address);
            return true;
        }
    }
    return false;
}
//Добавление строки в ТМ (ОАМК).
void Manager::AddStringToTM(QTableWidget* tableWidget_modTable, const QString& command_counter, const QString& section){
    if (!tableWidget_modTable){
        qDebug() << "tableWidget_modTable has returned a nullptr in a method Manager::AddStringToTM.";
        return;
    }
    int last_row = tableWidget_modTable->rowCount()-1;
    tableWidget_modTable->setItem(last_row, 0, new QTableWidgetItem(command_counter));
    tableWidget_modTable->setItem(last_row, 1, new QTableWidgetItem(section));
}
//Добавление строки в МППФ.
void Manager::AddStringToOMH(QTableWidget* tableWidget_OMH, const QString& prog_name, const QString& load_address, const QString& length_programm){
    if (!tableWidget_OMH){
        qDebug() << "tableWidget_OMH has returned a nullptr in a method Manager::AddStringToOMH.";
        return;
    }
    int last_row = tableWidget_OMH->rowCount()-1;
    tableWidget_OMH->setItem(last_row, 0, new QTableWidgetItem(prog_name));
    tableWidget_OMH->setItem(last_row, 1, new QTableWidgetItem(load_address));
    tableWidget_OMH->setItem(last_row, 2, new QTableWidgetItem(length_programm));
}

//Поиск элементов в строке исходного кода ассемблирующей программы через регулярное выражение.
QStringList Manager::GetLineItems(const QString &line) {
    QStringList lineItems;

    //Регулярное выражение для поиска возможных последовательностей символов.
    static QRegularExpression regex(R"((\w*'.+'\w*)|(\w+\s*)|([^\s]+\s*))");
    regex.setPatternOptions(QRegularExpression::UseUnicodePropertiesOption);
    //Извлечение готовых последовательностей символов из строки.
    QRegularExpressionMatchIterator it = regex.globalMatch(line);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        lineItems.append(match.captured().trimmed()); // Убираем пробелы и табы по краям.
    }

    return lineItems;
}
//Добавление строки исходного кода ассемблирующей программы в интерфейс.
void Manager::LoadSourceAssemblerCodeLineToField(QTextEdit* textEdit_source, const AssemblerInstruction& asmbr_instr)
{
    QString formatted_line{};
    formatted_line += asmbr_instr.label.value_or("") + "\t";
    formatted_line += asmbr_instr.mnemonic_code.value_or("") + "\t";
    formatted_line += asmbr_instr.operand1.value_or("") + "\t";
    formatted_line += asmbr_instr.operand2.value_or("");
    textEdit_source->append(formatted_line);
}
//Добавление строки ТКО в интерфейс.
void Manager::LoadDataRowToToOC(QTableWidget *tableWidget_ToOC, const TCOElem& opcode_table_elem)
{
    int last_row = tableWidget_ToOC->rowCount() - 1;
    tableWidget_ToOC->setItem(last_row, 0, new QTableWidgetItem(opcode_table_elem.mnemonic_code));
    tableWidget_ToOC->setItem(last_row, 1, new QTableWidgetItem(opcode_table_elem.binary_code));
    tableWidget_ToOC->setItem(last_row, 2, new QTableWidgetItem(opcode_table_elem.code_size));
}
