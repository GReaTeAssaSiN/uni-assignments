#ifndef CHECKS_H
#define CHECKS_H

#include "TableCodeOperation.h"

#include "QString"
#include "QTableWidget"
#include "QTextEdit"
#include "QChar"

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
    //Базовый деструктор.
    ~Checks() = default;
    //ПРОВЕРКИ//
    bool CheckTableCodeOperation(const TableCodeOperation& opcode_table, QTextEdit* textEdit_FPE);
    QString CheckRegister(const QString& reg);
    bool CheckAmountMemoryForAddress(const QString &amountMemory);
    bool CheckAddressCounterAvailable(QTextEdit* textEdit_FPE, const int& row, const int& address_counter);
    bool CheckRowSourceCode(QTextEdit* textEdit_FPE, const int& row, const QString& prog_name, const QString& label, const QString& mnemonic_code);
    QString CheckProgrammName(const QString& prog_name);
    QString CheckProgrammDownloadAddress(const QString& download_address);
    QString CheckOtherOperandPart(const QString &second_operand, const QString& mnemonic_code, const int& row);
    QString CheckDirective(const QString& mnemonic_code);
    QString CheckCorrectAmountMemoryForCodeOperation(const QString& amount_memory);
    bool CheckCorrectAmountMemoryForDecNumber(const QString& amount_memory);
    bool CheckAllocAmountMemoryForByte(const QString& alloc_memory);
    bool CheckCorrectAmountMemoryForHexNumber(const QString& amount_memory);
    bool CheckCorrectAmountMemoryForUnicodeString(const QString& amount_memory);
    bool CheckAllocAmountMemoryForWord(const QString& alloc_memory);
    bool CheckAllocAmountMemoryForRES(const QString& amount_memory);
    const int GetDecOpcode(QString const& command_binary_code, const int& type_addressing);
};

#endif // CHECKS_H
