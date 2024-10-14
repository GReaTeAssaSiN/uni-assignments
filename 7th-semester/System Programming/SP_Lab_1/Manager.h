#ifndef MANAGER_H
#define MANAGER_H

#include "QTextEdit"
#include "QTableWidget"
#include "SourceAssemblerCodeLine.h"
#include "StructSupportTable.h"
#include "TableCodeOperation.h"
#include "SymbolicNameTable.h"

class Manager{
public:
    Manager()=default;

    //Методы для получения данных из визуальных элементов.
    std::vector<AssemblerInstruction> ImportSourceAssemblerCodeFromField(QTextEdit* textEdit_source);
    TableCodeOperation ImportTCOFromTableCodeOperation(QTableWidget* tableWidget_ToOC);

    //Методы для визуализации данных и работы с визуализацией.
    void ExportDataToTextEditSource(QTextEdit* textEdit_source);
    void ExportDataToTableWidgetToOC(QTableWidget* tableWidget_ToOC);
    void ExportCustomDataToTextEditSource(QTextEdit* textEdit_source);
    void ExportCustomDataToTableWidgetToOC(QTableWidget* tableWidget_ToOC);
    void UpdateRowInSpecifiedTable(QTableWidget *tableWidget_specified, const int& row, const int& column);
    void TableCodeOperationFormatBinaryOpcode(QTableWidget *tableWidget_ToOC) const;
    void AddStringToAuxTable(QTableWidget* tableWidget_auxTable, const SupportTable& sup_table_elem);
    void AddStringToToSN(QTableWidget* tableWidget_ToSN, const SymbolicNameTable& symbolic_table, const QString& symbolic_name);

    ~Manager()=default;

private:
    void LoadDefaultSourceAssemblerCodeLine(QTextEdit* textEdit_source, const AssemblerInstruction& asmbr_instr);
    void LoadDataRowToToOC(QTableWidget* tableWidget_ToOC, const TCOElem& opcode_table_elem);
};

#endif // MANAGER_H
