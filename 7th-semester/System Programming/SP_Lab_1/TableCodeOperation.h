#ifndef TABLECODEOPERATION_H
#define TABLECODEOPERATION_H

#include <QString>
#include "vector"

struct TCOElem{
    QString mnemonic_code{}; //МКОП
    QString binary_code{}; //Двоичный КОП
    QString code_size{}; //Длина КОП (байт)

    TCOElem() = default;
    TCOElem(const QString &mnemonic_code, const QString &binary_code, const QString &code_size)
        : mnemonic_code(mnemonic_code), binary_code(binary_code), code_size(code_size){};
};

class TableCodeOperation{
private:
    std::vector<TCOElem> opcode_table{};

public:
    TableCodeOperation(size_t size = 6);
    bool Insert(const QString& mnemonic_code, const QString& binary_code, const QString& code_size);
    bool Find(const QString mnemonic_code, TCOElem& TCO_elem) const;
    void Remove(const QString& mnemonic_code);
    void Clear();
    const std::vector<TCOElem>& GetOpcodeTable() const;
    ~TableCodeOperation();
private:
    size_t Hash(const QString& key) const;
    void Resize();
    size_t CountFilledElems() const;
};

#endif // TABLECODEOPERATION_H
