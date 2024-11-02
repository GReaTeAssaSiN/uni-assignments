#ifndef SOURCEASSEMBLERCODELINE_H
#define SOURCEASSEMBLERCODELINE_H

#include "QString"

struct AssemblerInstruction
{
    std::optional<QString> label{};
    std::optional<QString> mnemonic_code{};
    std::optional<QString> operand1{};
    std::optional<QString> operand2{};
    //Базовый конструктор.
    AssemblerInstruction() = default;
    //Конструктор с параметрами.
    AssemblerInstruction(const QString& lbl, const QString& mnem_code, const QString& op1, const QString& op2 = "")
        : label(lbl), mnemonic_code(mnem_code), operand1(op1), operand2(op2) {}
};

#endif // SOURCEASSEMBLERCODELINE_H
