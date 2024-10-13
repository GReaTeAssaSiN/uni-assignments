#ifndef ASSEMBLERSOURCECODE_H
#define ASSEMBLERSOURCECODE_H

#include <QString>

struct SourceAssemblyCode{
    std::optional<QString> label{}; //Метка
    std::optional<QString> mnemonic_code{}; //МКОП
    std::optional<QString> firstOperand{}; //Первый операнд операндной чатси
    std::optional<QString> secondOperand{}; //Второй операнд операндной части

    //Базовый конструктор.
    SourceAssemblyCode() = default;
    //Конструктор для передачи временных экземпляров структуры.
    SourceAssemblyCode(const QString &lbl, const QString &mnemonic, const QString &firstOp, const QString &secondOp)
        : label(lbl), mnemonic_code(mnemonic), firstOperand(firstOp), secondOperand(secondOp){};
};

#endif // ASSEMBLERSOURCECODE_H
