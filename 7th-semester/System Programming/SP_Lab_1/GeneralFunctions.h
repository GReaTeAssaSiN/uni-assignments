#ifndef GENERALFUNCTIONS_H
#define GENERALFUNCTIONS_H

#include "QTextEdit"
#include "tablesmanager.h"

bool FirstPass(const std::vector<SourceAssemblyCode> &source_code,const std::vector<OpcodeTable> &opcode_table,
                QTableWidget* tableWidget_auxTable, QTableWidget* tableWidget_ToSN, QTextEdit* textEdit_FPE, TablesManager* manager);

#endif // GENERALFUNCTIONS_H
