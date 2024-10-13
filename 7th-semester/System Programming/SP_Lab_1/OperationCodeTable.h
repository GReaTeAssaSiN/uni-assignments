#ifndef OPERATIONCODETABLE_H
#define OPERATIONCODETABLE_H

#include <QString>

struct OpcodeTable{
    std::optional<QString> code{}; //МКОП
    std::optional<QString> binary_opcode{}; //Двоичный КОП
    std::optional<QString> size{}; //Длина КОП (байт)

    //Базовый конструктор.
    OpcodeTable() = default;
    //Конструктор для передачи временных экземпляров структуры.
    OpcodeTable(const QString &code, const QString &binary_opcode, const QString &size)
        : code(code), binary_opcode(binary_opcode), size(size){};
};

#endif // OPERATIONCODETABLE_H
