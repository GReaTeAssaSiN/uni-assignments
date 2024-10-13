#include "tablesmanager.h"

////////////////////////////////////////////////////////////////////////////////
/*Основные методы для загрузки данных по умолчанию и их стандартной обработки*/
////////////////////////////////////////////////////////////////////////////////

//Построчное заполнение исходного текста ассемблирующей программы.
void TablesManager::LoadAssemblerSourceCodeLine(QTextEdit *textEdit_source, const SourceAssemblyCode& source_code_line)
{
    QString formattedLine;
    formattedLine += source_code_line.label.value_or("") + "\t";
    formattedLine += source_code_line.mnemonic_code.value_or("") + "\t";
    formattedLine += source_code_line.firstOperand.value_or("") + "\t";
    formattedLine += source_code_line.secondOperand.value_or("");
    textEdit_source->append(formattedLine);
}

//Построчное заполнение ТКО.
void TablesManager::LoadTableOperationCodeElem(QTableWidget *tableWidget_ToOC, const OpcodeTable &opcode_table_elem)
{
    int last_row = tableWidget_ToOC->rowCount() - 1;
    tableWidget_ToOC->insertRow(last_row);

    for (int column{}; column < tableWidget_ToOC->columnCount(); ++column)
    {
        tableWidget_ToOC->setItem(last_row, 0, new QTableWidgetItem(opcode_table_elem.code.value_or("")));
        tableWidget_ToOC->setItem(last_row, 1, new QTableWidgetItem(opcode_table_elem.binary_opcode.value_or("")));
        tableWidget_ToOC->setItem(last_row, 2, new QTableWidgetItem(opcode_table_elem.size.value_or("")));
    }
}

//Заполнение исходного текста ассемблирующей программы по умолчанию.
void TablesManager::LoadDefaultAssemblerSourceCodeToField(QTextEdit *textEdit_source)
{
    if (textEdit_source == nullptr){
        qDebug() << "texEdit_source has returned a nullptr in a method TablesManager::LoadAssemblerSourceCodeToField.";
        return;
    }
    else{
        LoadAssemblerSourceCodeLine(textEdit_source, SourceAssemblyCode{"PROG1", "START", "100", ""});
        LoadAssemblerSourceCodeLine(textEdit_source, SourceAssemblyCode{"", "JMP", "L1", ""});
        LoadAssemblerSourceCodeLine(textEdit_source, SourceAssemblyCode{"A1", "RESB", "10", ""});
        LoadAssemblerSourceCodeLine(textEdit_source, SourceAssemblyCode{"A2", "RESW", "20", ""});
        LoadAssemblerSourceCodeLine(textEdit_source, SourceAssemblyCode{"B1", "WORD", "4096", ""});
        LoadAssemblerSourceCodeLine(textEdit_source, SourceAssemblyCode{"B2", "BYTE", "X'2F4C008A'", ""});
        LoadAssemblerSourceCodeLine(textEdit_source, SourceAssemblyCode{"B3", "BYTE", "C'Hello!'", ""});
        LoadAssemblerSourceCodeLine(textEdit_source, SourceAssemblyCode{"B4", "BYTE", "128", ""});
        LoadAssemblerSourceCodeLine(textEdit_source, SourceAssemblyCode{"L1", "LOADR1", "B1", ""});
        LoadAssemblerSourceCodeLine(textEdit_source, SourceAssemblyCode{"", "LOADR2", "B4", ""});
        LoadAssemblerSourceCodeLine(textEdit_source, SourceAssemblyCode{"", "ADD", "R1", "R2"});
        LoadAssemblerSourceCodeLine(textEdit_source, SourceAssemblyCode{"", "SAVER1", "B1", ""});
        LoadAssemblerSourceCodeLine(textEdit_source, SourceAssemblyCode{"", "END", "100", ""});
    }
}

//Заполнение ТКО по умолчанию.
void TablesManager::LoadDefaultOperationCodeToTable(QTableWidget *tableWidget_ToOC)
{
    if (tableWidget_ToOC == nullptr){
        qDebug() << "tableWidget_ToOC has returned a nullptr in a method TablesManager::LoadOperationCodeToTable.";
        return;
    }
    else{
        tableWidget_ToOC->setColumnCount(3);
        tableWidget_ToOC->setRowCount(1);
        LoadTableOperationCodeElem(tableWidget_ToOC, OpcodeTable{"JMP", "01", "4"});
        LoadTableOperationCodeElem(tableWidget_ToOC, OpcodeTable{"LOADR1", "02", "4"});
        LoadTableOperationCodeElem(tableWidget_ToOC, OpcodeTable{"LOADR2", "03", "4"});
        LoadTableOperationCodeElem(tableWidget_ToOC, OpcodeTable{"ADD", "04", "2"});
        LoadTableOperationCodeElem(tableWidget_ToOC, OpcodeTable{"SAVER1", "05", "4"});
    }
}

//Заполнение исходного текста ассемблирующей программы пользователем.
void TablesManager::LoadCustomAssemblerSourceCodeToField(QTextEdit *textEdit_source, const std::vector<SourceAssemblyCode> &source_code)
{
    textEdit_source->clear();
    for (const auto& source_code_line : source_code){
        LoadAssemblerSourceCodeLine(textEdit_source, source_code_line);
    }
}

//Заполнение ТКО пользователем.
void TablesManager::LoadCustomOperationCodeTable(QTableWidget *tableWidget_ToOC, const std::vector<OpcodeTable> &opcode_table)
{
    tableWidget_ToOC->clear();
    tableWidget_ToOC->setColumnCount(3);
    tableWidget_ToOC->setRowCount(1);
    for (const auto& opcode_table_elem : opcode_table){
        LoadTableOperationCodeElem(tableWidget_ToOC, opcode_table_elem);
    }
}

//Чтение данных исходного текста ассемблирующей программы (без проверок на допустимость).
std::vector<SourceAssemblyCode> TablesManager::GetAssemblerSourceCodeFromField(QTextEdit* textEdit_source)
{
    std::vector<SourceAssemblyCode> source_code{};//Для хранения структур (строк исходного текста) в динамическом массиве.
    //Обработка исходного текста построчно и заполнение динамического массива.
    QString text = textEdit_source->toPlainText();
    QStringList lines = text.split("\n");
    for (const QString &line : lines){
        static const QRegularExpression for_split_on_parts{"\\s+"};
        QStringList parts = line.split(for_split_on_parts, Qt::SkipEmptyParts);
        SourceAssemblyCode temp_code_line{};
        bool startsWithSpace = line.startsWith(" ") || line.startsWith("\t");
        if (startsWithSpace){
            parts.prepend("");
        }
        if (parts.size() > 0){ temp_code_line.label = parts[0];};
        if (parts.size() > 1){ temp_code_line.mnemonic_code = parts[1];};
        if (parts.size() > 2){ temp_code_line.firstOperand = parts[2];};
        if (parts.size() > 3){ temp_code_line.secondOperand = parts.mid(3).join(" ");};
        source_code.push_back(temp_code_line);
    }

    return source_code;
}

//Чтение данных ТКО (без проверок на допустимость).
std::vector<OpcodeTable> TablesManager::GetOperationCodeTable(QTableWidget* tableWidget_ToOC)
{
    std::vector<OpcodeTable> opcode_table{};//Для хранения структур (строки ТКО) в динамическом массиве.
    for (int row{}; row < tableWidget_ToOC->rowCount(); ++row){
        //Пропуск пустой сроки.
        if (tableWidget_ToOC->item(row, 0) == nullptr &&
            tableWidget_ToOC->item(row, 1) == nullptr &&
            tableWidget_ToOC->item(row, 2) == nullptr) {
            qDebug() << "Null item found at row " << row;
            continue;
        }
        QString code{tableWidget_ToOC->item(row, 0) == nullptr ? "" : tableWidget_ToOC->item(row, 0)->text()};
        QString binary_code{tableWidget_ToOC->item(row, 1) == nullptr ? "" : tableWidget_ToOC->item(row, 1)->text()};
        QString size{tableWidget_ToOC->item(row, 2) == nullptr ? "" : tableWidget_ToOC->item(row, 2)->text()};
        opcode_table.push_back(OpcodeTable{code, binary_code, size});
    }
    return opcode_table;
}

///////////////////////////////////////////////////////////////////////////////////////////
/*Дополнительные методы для особой обработки действий пользователя посредством интерфейса*/
///////////////////////////////////////////////////////////////////////////////////////////
//Обновление строки указанной таблицы (добавление, удаление строки или бездействие)
void TablesManager::UpdateRowInSpecifiedTable(QTableWidget *tableWidget_specified, const int& row, const int& column)
{
    if (tableWidget_specified == nullptr) {
        qDebug() << "tableWidget_specified has returned a nullptr in a method TablesManager::updateRowInSpecifiedTable.";
        return;
    }

    //Добавление пустой строки в конце таблицы при необходимости.
    if (row == tableWidget_specified->rowCount() - 1) {
        if (tableWidget_specified->item(row, column) != nullptr &&
            !tableWidget_specified->item(row, column)->text().isEmpty()) {
            tableWidget_specified->insertRow(row + 1);
            // Инициализация всех ячеек новой строки пустыми значениями
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

//Очистка указанной таблицы.
void TablesManager::ClearTable(QTableWidget *tableWidget_specified)
{
    tableWidget_specified->clear();
    tableWidget_specified->setColumnCount(0);
    tableWidget_specified->setRowCount(0);
}

//Форматирование столбца с двоичным кодом МКОП.
void TablesManager::OpcodeTableFormatBinaryOpcode(QTableWidget *tableWidget_ToOC)
{
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

///////////////////////////////////////////////////////////////
/*Методы работы с таблицами для первого или второго прохода.*/
///////////////////////////////////////////////////////////////
//Добавление строки в вспомогательную таблицу (СА/Название программы + реальный двочиный КОП + операндная часть).
void TablesManager::AddStringToAuxTable(const QString& prog_name_or_AC, const QString& real_binary_opcode, const QString& operand1, const QString& operand2, QTableWidget* tableWidget_auxTable)
{
    tableWidget_auxTable->insertRow(tableWidget_auxTable->rowCount());
    int last_row = tableWidget_auxTable->rowCount() - 1;
    tableWidget_auxTable->setItem(last_row, 0, new QTableWidgetItem(prog_name_or_AC));
    tableWidget_auxTable->setItem(last_row, 1, new QTableWidgetItem(real_binary_opcode));
    tableWidget_auxTable->setItem(last_row, 2, new QTableWidgetItem(operand1));
    tableWidget_auxTable->setItem(last_row, 3, new QTableWidgetItem(operand2));
}
//Добавление строки в ТСИ (СИ + текущий СА).
void TablesManager::AddStringToToSN(const QString& symbolic_name, const QString& current_address_counter, QTableWidget* tableWidget_ToSN){
    tableWidget_ToSN->insertRow(tableWidget_ToSN->rowCount());
    int last_row = tableWidget_ToSN->rowCount() - 1;
    tableWidget_ToSN->setItem(last_row, 0, new QTableWidgetItem(symbolic_name));
    tableWidget_ToSN->setItem(last_row, 1, new QTableWidgetItem(current_address_counter));
}

