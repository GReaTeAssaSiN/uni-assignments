#ifndef FIRSTPASSPROCESSOR_H
#define FIRSTPASSPROCESSOR_H

#include "QTextEdit"
#include "QTableWidget"
#include "Manager.h"
#include "SourceAssemblerCodeLine.h"
#include "TableCodeOperation.h"
#include "SymbolicNameTable.h"
#include "Checks.h"

class FirstPassProcessor{
    SymbolicNameTable symbolic_table{};
    Manager manager{};
    //Объект класса Checks для различных глобальных проверок.
    Checks checks{};

public:
    FirstPassProcessor() : symbolic_table(){};

    bool LoadTableSymbolicNames(const std::vector<AssemblerInstruction>& source_code, const TableCodeOperation& TCO,
                                QTableWidget* tableWidget_auxTable, std::vector<SupportTable> sup_table,
                                QTableWidget* tableWidget_ToSN, SymbolicNameTable& symbolic_table, QTextEdit* textEdit_FPE);
};


#endif // FIRSTPASSPROCESSOR_H
