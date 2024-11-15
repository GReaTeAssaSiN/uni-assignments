#include "TableCodeOperation.h"

//Конструктор.
TableCodeOperation::TableCodeOperation(size_t size) : opcode_table(size){}
//Деструктор.
TableCodeOperation::~TableCodeOperation(){
    this->opcode_table.clear();
}

/*ОСНОВНЫЕ МЕТОДЫ*/
//Вставка элемента ТКО в хэш-таблицу.
bool TableCodeOperation::Insert(const QString &mnemonic_code, const QString& binary_code, const QString& code_size)
{
    //Изменение размера ТКО при заполнении на 80%.
    if (CountFilledElems() >= this->opcode_table.size() * 0.8)
        Resize();
    size_t index = Hash(mnemonic_code) % this->opcode_table.size();
    while (!this->opcode_table[index].mnemonic_code.isEmpty()){
        if (this->opcode_table[index].mnemonic_code == mnemonic_code)
            return false;
        index = (index + 1) % this->opcode_table.size();
    }

    this->opcode_table[index] = TCOElem{mnemonic_code, binary_code, code_size};
    return true;
}
//Поиск элемента ТКО в хэш-таблице.
bool TableCodeOperation::Find(const QString mnemonic_code, TCOElem &TCO_elem) const
{
    size_t index = Hash(mnemonic_code) % this->opcode_table.size();
    while (!this->opcode_table[index].mnemonic_code.isEmpty()){
        if (this->opcode_table[index].mnemonic_code == mnemonic_code){
            TCO_elem = this->opcode_table[index];
            return true;
        }
        index = (index + 1) % this->opcode_table.size();
    }
    return false;
}
//Удаление элемента ТКО в хэш-таблице.
void TableCodeOperation::Remove(const QString &mnemonic_code)
{
    size_t index = Hash(mnemonic_code) % this->opcode_table.size();
    while (!this->opcode_table[index].mnemonic_code.isEmpty()){
        if (this->opcode_table[index].mnemonic_code == mnemonic_code){
            this->opcode_table[index] = TCOElem();
            return;
        }
        index = (index + 1) % this->opcode_table.size();
    }
}
//Удаление ТКО.
void TableCodeOperation::Clear()
{
    this->opcode_table.clear();
}
//Геттер ТКО.
const std::vector<TCOElem>& TableCodeOperation::GetOpcodeTable() const
{
    return this->opcode_table;
}

/*ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ*/
//Хэш-функция (простой алгоритм) - без % длина, т.к. иначе в результате ресайза нарушается основное правило хэш-функции.
size_t TableCodeOperation::Hash(const QString &key) const{
    size_t hash_value{};
    for (QChar ch : key){
        hash_value = (hash_value * 31 + ch.unicode());
    }
    return hash_value;
}
//Увеличение размера хэш-таблицы в 2 раза при необходимости.
void TableCodeOperation::Resize(){
    size_t new_size = this->opcode_table.size() * 2;
    std::vector<TCOElem> new_opcode_table(new_size);
    for (const auto& TCO_elem : this->opcode_table) {
        if (!TCO_elem.mnemonic_code.isEmpty()) {
            size_t index = Hash(TCO_elem.mnemonic_code) % new_size;
            while (!new_opcode_table[index].mnemonic_code.isEmpty()) {
                index = (index + 1) % new_size;
            }
            new_opcode_table[index] = TCO_elem;
        }
    }
    this->opcode_table = std::move(new_opcode_table);
}
//Получение числа не пустых элементов хэш-таблицы.
size_t TableCodeOperation::CountFilledElems() const
{
    size_t count_filled_elems{};
    for (const auto& TCO_elem : this->opcode_table){
        if (!TCO_elem.mnemonic_code.isEmpty())
            count_filled_elems++;
    }
    return count_filled_elems;
};
