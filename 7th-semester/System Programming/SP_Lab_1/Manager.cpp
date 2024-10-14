#include "Manager.h"

//Загрузка исходного кода ассемблирующей программы в структуру.
std::vector<AssemblerInstruction> Manager::ImportSourceAssemblerCodeFromField(QTextEdit *textEdit_source)
{
    std::vector<AssemblerInstruction> source_code{};
    //Обработка исходного текста построчно и заполнение структуры.
    QString text = textEdit_source->toPlainText();
    QStringList lines = text.split("\n");
    for (const QString &line : lines){
        static const QRegularExpression for_split_on_parts{"\\s+"};
        QStringList parts = line.split(for_split_on_parts, Qt::SkipEmptyParts);
        AssemblerInstruction temp_code_line{};
        bool startsWithSpace = line.startsWith(" ") || line.startsWith("\t");
        if (startsWithSpace){
            parts.prepend("");
        }
        if (parts.size() > 0){ temp_code_line.label = parts[0];};
        if (parts.size() > 1){ temp_code_line.mnemonic_code = parts[1];};
        if (parts.size() > 2){ temp_code_line.operand1 = parts[2];};
        if (parts.size() > 3){ temp_code_line.operand2 = parts.mid(3).join(" ");};
        source_code.push_back(temp_code_line);
    }

    return source_code;
}
//Загрузка ТКО в структуру.
TableCodeOperation Manager::ImportTCOFromTableCodeOperation(QTableWidget *tableWidget_ToOC)
{
    TableCodeOperation opcode_table{};
    for (int row{}; row < tableWidget_ToOC->rowCount(); ++row)
    {
        QString mnemonic_code{tableWidget_ToOC->item(row, 0) == nullptr ? "" : tableWidget_ToOC->item(row, 0)->text()};
        QString binary_code{tableWidget_ToOC->item(row, 1) == nullptr ? "" : tableWidget_ToOC->item(row, 1)->text()};
        QString code_size{tableWidget_ToOC->item(row, 2) == nullptr ? "" : tableWidget_ToOC->item(row, 2)->text()};
        opcode_table.Insert(mnemonic_code, binary_code, code_size);
    }
    return opcode_table;
}

//Загрузка исходного кода ассемблирующей программы в интерфейс.
void Manager::ExportDataToTextEditSource(QTextEdit* textEdit_source){
    if (!textEdit_source){
        qDebug() << "textEdit_source has returned a nullptr in a method Manager::ExportDataToTextEditSource.";
        return;
    }
    textEdit_source->clear();
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"Prog1", "START", "100", ""});
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"", "JMP", "L1", ""});
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"A1", "RESB", "10", ""});
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"A2", "RESW", "20", ""});
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"B1", "WORD", "4096", ""});
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"B2", "BYTE", "X'2F4C008A'", ""});
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"B3", "BYTE", "C'Hello!'", ""});
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"B4", "BYTE", "128", ""});
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"L1", "LOADR1", "B1", ""});
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"", "LOADR2", "B4", ""});
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"", "ADD", "R1", "R2"});
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"", "SAVER1", "B1", ""});
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"", "END", "100", ""});
}
//Загрузка ТКО в интерфейс.
void Manager::ExportDataToTableWidgetToOC(QTableWidget *tableWidget_ToOC)
{
    if (!tableWidget_ToOC) {
        qDebug() << "tableWidget_ToOC has returned a nullptr in a method TablesManager::ExportDataToTableWidgetToOC.";
        return;
    }
    tableWidget_ToOC->clear();
    tableWidget_ToOC->setColumnCount(3);
    tableWidget_ToOC->setRowCount(1);

    LoadDataRowToToOC(tableWidget_ToOC, {"JMP", "01", "4"});
    LoadDataRowToToOC(tableWidget_ToOC, {"LOADR1", "02", "4"});
    LoadDataRowToToOC(tableWidget_ToOC, {"LOADR2", "03", "4"});
    LoadDataRowToToOC(tableWidget_ToOC, {"ADD", "04", "2"});
    LoadDataRowToToOC(tableWidget_ToOC, {"SAVER1", "05", "4"});
    LoadDataRowToToOC(tableWidget_ToOC, {"","",""});
}
//Пустой исходный код ассемблирующей программы -> Интерфейс.
void Manager::ExportCustomDataToTextEditSource(QTextEdit *textEdit_source)
{
    if (!textEdit_source) {
        qDebug() << "textEdit_source has returned a nullptr in a method TablesManager::ExportCustomDataToTextEditSource";
        return;
    }
    textEdit_source->clear();
    this->LoadDefaultSourceAssemblerCodeLine(textEdit_source, {"", "", "", ""});
}
//Пустая ТКО -> интерфейс.
void Manager::ExportCustomDataToTableWidgetToOC(QTableWidget *tableWidget_ToOC)
{
    if (!tableWidget_ToOC) {
        qDebug() << "tableWidget_ToOC has returned a nullptr in a method TablesManager::ExportCustomDataToTableWidgetToOC.";
        return;
    }
    tableWidget_ToOC->clear();
    tableWidget_ToOC->setColumnCount(3);
    tableWidget_ToOC->setRowCount(1);

    LoadDataRowToToOC(tableWidget_ToOC, {"", "", ""});
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
    if (tableWidget_auxTable == nullptr){
        qDebug() << "tableWidget_auxTable has returned a nullptr in a method Manager::AddStringToAuxTable";
    }
    int last_row = tableWidget_auxTable->rowCount() - 1;
    tableWidget_auxTable->setItem(last_row, 0, new QTableWidgetItem(sup_table_elem.address_counter));
    tableWidget_auxTable->setItem(last_row, 1, new QTableWidgetItem(sup_table_elem.operation_code));
    tableWidget_auxTable->setItem(last_row, 2, new QTableWidgetItem(sup_table_elem.operand1));
    tableWidget_auxTable->setItem(last_row, 3, new QTableWidgetItem(sup_table_elem.operand2));
}
//Добавление строки в ТСИ (СИ + текущий СА).
void Manager::AddStringToToSN(QTableWidget* tableWidget_ToSN, const SymbolicNameTable& symbolic_table, const QString& symbolic_name){
    if (tableWidget_ToSN == nullptr){
        qDebug() << "tableWidget_ToSN has returned a nullptr in a method Manager::AddStringToToSN.";
    }
    QString address{};
    symbolic_table.Find(symbolic_name, address);
    int last_row = tableWidget_ToSN->rowCount() - 1;
    tableWidget_ToSN->setItem(last_row, 0, new QTableWidgetItem(symbolic_name));
    tableWidget_ToSN->setItem(last_row, 1, new QTableWidgetItem(address));
}
//Добавление строки исходного кода ассемблирующей программы в интерфейс.
void Manager::LoadDefaultSourceAssemblerCodeLine(QTextEdit* textEdit_source, const AssemblerInstruction& asmbr_instr)
{
    QString formatted_line{};
    formatted_line += asmbr_instr.label.value_or("") + "\t";
    formatted_line += asmbr_instr.mnemonic_code + "\t";
    formatted_line += asmbr_instr.operand1 + "\t";
    formatted_line += asmbr_instr.operand2.value_or("");
    textEdit_source->append(formatted_line);
}
//Добавление строки ТКО в интерLoadDataRowToToOC(фейс.
void Manager::LoadDataRowToToOC(QTableWidget *tableWidget_ToOC, const TCOElem& opcode_table_elem)
{
    int last_row = tableWidget_ToOC->rowCount() - 1;
    tableWidget_ToOC->setItem(last_row, 0, new QTableWidgetItem(opcode_table_elem.mnemonic_code));
    tableWidget_ToOC->setItem(last_row, 1, new QTableWidgetItem(opcode_table_elem.binary_code));
    tableWidget_ToOC->setItem(last_row, 2, new QTableWidgetItem(opcode_table_elem.code_size));
}
