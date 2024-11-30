#ifndef PASSPROCESSOR_H
#define PASSPROCESSOR_H

#include "QTextEdit"
#include "QTableWidget"
#include "Manager.h"
#include "SourceAssemblerCodeLine.h"
#include "TableCodeOperation.h"
#include "SymbolicNameTable.h"
#include "Checks.h"

class PassProcessor{
    Manager manager{};
    //Объект класса Checks для различных глобальных проверок.
    Checks checks{};
    //Список названий: программы + управляющих секций.
    QStringList prog_names{};
    //Список счетчиков адреса: программы + управляющих секций.
    QList<int> address_counters{};
    //Список адресов загрузки: программы + управляющих секций.
    QList<int> load_addresses{};
    //Адрес точки входа в программу.
    int address_entry_point{};


public:
    bool FirstPass(const int& type_addr, const std::vector<AssemblerInstruction>& source_code, const TableCodeOperation& TCO,
                   QTableWidget* tableWidget_auxTable, std::vector<SupportTable>& sup_table,
                   QTableWidget* tableWidget_ToSN, SymbolicNameTable& symbolic_table, QTextEdit* textEdit_FPE);
    bool SecondPass(QTableWidget* tableWidget_OMH, QTableWidget* tableWidget_modTable, QTextEdit* textEdit_SPE, QTextEdit* textEdit_binary_code,
                    const std::vector<SupportTable>& sup_table, const SymbolicNameTable& symbolic_table);
};


#endif // PASSPROCESSOR_H
