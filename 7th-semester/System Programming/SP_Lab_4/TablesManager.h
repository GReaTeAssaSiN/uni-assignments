#ifndef TABLESMANAGER_H
#define TABLESMANAGER_H

#include "StructAssemblerLine.h"
#include "codeoperationtable.h"
#include "symbolicnamestable.h"
#include "AdditionalListOfSymbolicNames.h"

#include <QTextEdit>
#include <QTableWidget>

class TablesManager
{

public:
    TablesManager() = default;
    ~TablesManager() = default;

    void LoadOneLineToAssemblerSourceCode(QTextEdit* source_text_TextEdit, const AssemblerInstruction& AssInstr);
    void LoadOneLIneToAssemblerOperationCode(QTableWidget* table_operation_codes_TableWidget, const CodeOperation& OpCode);
    void LoadOneLineToSymbolicNamesTable(QTableWidget* symb_table, const SymbolicNamesTable& symb, QString name);
    void LoadElemOfListToSymbolicNamesTable(QTableWidget* symb_table, const OneSymbolicName& symb);

    void LoadDefaultAssemblerSourceCode(QTextEdit* source_text_TextEdi);
    void LoadDefaultAssemplerOperationCode(QTableWidget* table_operation_codes_tableWidget);

    QStringList GetLineItems(const QString &line);
    std::vector<AssemblerInstruction> ParseAssemblerSourceCode(QTextEdit* source_text_TextEdit);
    bool ParseAssemblerOperationCode(QTableWidget *table_operation_codes_tableWidget, CodeOperationTable& opCodeTable, QTextEdit* fpe_text);

    void UpdateViewOfTable(QTableWidget* current_table, const int& row, const int& column);

    void ExportFormattedSourceAssemblerCodeToField(std::vector<AssemblerInstruction> &source_code, QTextEdit* textEdit_source);
};

#endif // TABLESMANAGER_H
