#ifndef STRUCTSUPPORTTABLE_H
#define STRUCTSUPPORTTABLE_H

#include "QString"

struct SupportTable
{
    QString address_counter{};
    QString operation_code{};
    QString operand1{};
    QString operand2{};
    //Базовый конструктор.
    SupportTable() = default;
    //Конструктор с параметрами.
    SupportTable(const QString& adr_count, const QString& op_code, const QString& op1, const QString& op2 = "")
        : address_counter(adr_count), operation_code(op_code), operand1(op1), operand2(op2) {}
};

#endif // STRUCTSUPPORTTABLE_H
