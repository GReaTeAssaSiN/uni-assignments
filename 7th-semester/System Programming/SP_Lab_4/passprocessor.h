#ifndef PASSPROCESSOR_H
#define PASSPROCESSOR_H

#include "StructAssemblerLine.h"
#include "codeoperationtable.h"
#include "symbolicnamestable.h"
#include "TablesManager.h"
#include "AdditionalListOfSymbolicNames.h"
#include "checks.h"

#include <QTableWidget>
#include <QTextEdit>

class PassProcessor
{
private:
    TablesManager TManager{};
    //Объект класса Checks для различных проверок.
    Checks check{};
    //Счетчик адреса.
    int addressCounter{};
    //Адрес точки входа в программу.
    int end_prog_address{};
    //Адрес загрузки программы.
    int start_prog_address{};
    //Название программы.
    QString prog_name{};
    //Флаги для учета найденных директив START и END.
    bool start_dir_flag{};
    bool end_dir_flag{};

public:
    PassProcessor() = default;

    bool Pass(QTextEdit* fpe_text, const std::vector<AssemblerInstruction>& sourceText_code, const CodeOperationTable& opCode_table,
                   std::vector<OneSymbolicName>& list_of_symb_names, QTableWidget* table_symbolic_names, SymbolicNamesTable& symb_table,
                   const bool& all_iters, size_t& step, QTextEdit* binaryCode_text);

    bool OneStep(QTextEdit *fpe_text, const std::vector<AssemblerInstruction> &sourceText_code, const CodeOperationTable &opCode_table,
                 std::vector<OneSymbolicName> &list_of_symb_names, QTableWidget *table_symbolic_names, SymbolicNamesTable &symb_table, size_t& i,
                 QTextEdit* binaryCode_text);

    void replaceLineWithUnknownSN(QTextEdit* binaryCode_text, const QString& marker, const QString& replacement);
    void replaceLineWithH(QTextEdit* binaryCode_text, const QString& target, const QString& replacement);
};

#endif // PASSPROCESSOR_H
