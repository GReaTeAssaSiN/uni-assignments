#ifndef CHECKS_H
#define CHECKS_H

#include "QString"
#include "QTableWidget"
#include "OperationCodeTable.h"
#include <QTextEdit>

class Checks
{
private:
    //ВНУТРЕННИЕ ПРОВЕРКИ//
    bool CheckLengthSymbolicName(const QString& symbolic_name);
    bool CheckCharsSymbolicName(const QString& symbolic_name);
    bool CheckIncorrectSymbolicName(const QString& symbolic_name);
    bool CheckCharsMCOP(const QString& mnemonic_code);

public:
    //Базовый конструктор.
    Checks() = default;
    //ПРОВЕРКИ//
    bool CheckOpcodeTable(std::vector<OpcodeTable> opcode_table, QTextEdit* textEdit_FPE);
    QString CheckRegister(const QString& reg);
    bool CheckAmountMemoryForAddress(const QString &amountMemory);
    bool CheckAddressCounterAvailable(QTextEdit* textEdit_FPE, const int& row, const QString& address_counter);
    bool CheckRowSourceCode(QTextEdit* textEdit_FPE, const int& row, QString& prog_name, const QString& label, const QString& mnemonic_code);
    QString CheckProgrammName(const QString& prog_name);
    QString CheckProgrammDownloadAddress(const QString& download_address);
    QString CheckOtherOperandPart(const QString &second_operand, const QString& mnemonic_code, const int& row);
    int SearchSymbolicNameInToSN(const QString &symbolic_name, QTableWidget* tableWidget_ToSN, QTextEdit* textEdit_FPE);
    QString CheckDirective(const QString& mnemonic_code);
    bool CheckCorrectAmountMemoryForDecNumber(const QString& amount_memory);
    bool CheckAllocAmountMemoryForByte(const QString& alloc_memory);
    bool CheckCorrectAmountMemoryForHexNumber(const QString& amount_memory);
    bool CheckCorrectAmountMemoryForUnicodeString(const QString& amount_memory);
    bool CheckAllocAmountMemoryForWord(const QString& alloc_memory);
    bool CheckAllocAmountMemoryForRES(const QString& amount_memory);
    int SearchCommandInToOC(QString const& command, std::vector<OpcodeTable> opcode_table);
    int GetDecOpcode(QString const& command_binary_code, const int& type_addressing);
};

#endif // CHECKS_H
