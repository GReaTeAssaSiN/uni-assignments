#ifndef TABLESMANAGER_H
#define TABLESMANAGER_H

#include "AssemblerSourceCode.h"
#include "OperationCodeTable.h"
#include "QTextEdit"
#include "QTableWidget"

class TablesManager
{
private:
    void LoadAssemblerSourceCodeLine(QTextEdit* textEdit_source, const SourceAssemblyCode& source_code_line);
    void LoadTableOperationCodeElem(QTableWidget* teableWidget_ToOC, const OpcodeTable& opcode_table_elem);
public:
    TablesManager() = default;
    void LoadDefaultAssemblerSourceCodeToField(QTextEdit* textEdit_source);
    void LoadDefaultOperationCodeToTable(QTableWidget* tableWidget_ToOC);
    void LoadCustomAssemblerSourceCodeToField(QTextEdit* textEdit_source, const std::vector<SourceAssemblyCode> &source_code);
    void LoadCustomOperationCodeTable(QTableWidget *tableWidget_ToOC, const std::vector<OpcodeTable> &opcode_table);
    std::vector<SourceAssemblyCode> GetAssemblerSourceCodeFromField(QTextEdit* textEdit_source);
    std::vector<OpcodeTable> GetOperationCodeTable(QTableWidget* tableWidget_ToOC);

    void UpdateRowInSpecifiedTable(QTableWidget *tableWidget_specified, const int& row, const int& column);
    void ClearTable(QTableWidget *tableWidget_Specified);
    void OpcodeTableFormatBinaryOpcode(QTableWidget *tableWidget_ToOC);

    void AddStringToAuxTable(const QString& prog_name_or_AC, const QString& real_binary_opcode, const QString& operand1, const QString& operand2, QTableWidget* tableWidget_auxTable);
    void AddStringToToSN(const QString& symbolic_name, const QString& curernt_adress_counter, QTableWidget* tableWidget_ToSN);
};

#endif // TABLESMANAGER_H
