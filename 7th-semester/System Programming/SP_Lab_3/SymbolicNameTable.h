#ifndef SYMBOLICNAMETABLE_H
#define SYMBOLICNAMETABLE_H

#include <QString>

struct TreeNode{
    std::optional<QString> name{}; //Символическое имя
    std::optional<QString> address{}; //Адрес в 16-ричной СИ
    std::optional<QString> section{}; //Имя секции с СИ.
    std::optional<QString> name_type{}; //ВИ или ВС.
    TreeNode* left{}; //Левый дочерний узел
    TreeNode* right{}; //Правый дочерний узел
    int height{}; //Высота узла для определения балансировки дерева

    //Конструктор.
    TreeNode(const QString& name, const QString& address, const QString& section, const QString& name_type):
        name(name), address(address), section(section), name_type(name_type), left(nullptr), right(nullptr), height(1){};
};

class SymbolicNameTable
{
private:
    TreeNode* root{};

public:
    SymbolicNameTable();
    void Insert(const QString& name, const QString& address, const QString& section, const QString& name_type);
    bool Remove(const QString& name, const QString& section);
    bool Find(const QString& name, QString& address, const QString& section, QString& name_type) const;
    bool Update(const QString& name, const QString& section, const QString& new_address);
    void Clear();
    ~SymbolicNameTable();
private:
    TreeNode *Insert(TreeNode* node, const QString& name, const QString& address, const QString& section, const QString& name_type);
    TreeNode *Remove(TreeNode* node, const QString& name, const QString& section);
    TreeNode *Find(TreeNode* node, const QString& name, const QString& section) const;
    void Clear(TreeNode* node);
    int Height(TreeNode* node) const;
    int GetBalance(TreeNode* node) const;
    TreeNode *SmallRightRotate(TreeNode* a);
    TreeNode *BigRightRotate(TreeNode* a);
    TreeNode *SmallLeftRotate(TreeNode* a);
    TreeNode *BigLeftRotate(TreeNode* a);
};

#endif // SYMBOLICNAMETABLE_H
