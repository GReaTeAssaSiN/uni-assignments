#ifndef SYMBOLICNAMETABLE_H
#define SYMBOLICNAMETABLE_H

#include <QString>

struct TreeNode{
    std::optional<QString> name{}; //Символическое имя
    std::optional<QString> address{}; //Адрес в 16-ричной СИ
    TreeNode* left{}; //Левый дочерний узел
    TreeNode* right{}; //Правый дочерний узел
    int height{}; //Высота узла для определения балансировки дерева

    //Конструктор.
    TreeNode(const QString& name, const QString& address):
        name(name), address(address), left(nullptr), right(nullptr), height(1){};
};

class SymbolicNameTable
{
private:
    TreeNode* root{};

public:
    SymbolicNameTable();
    void Insert(const QString& name, const QString& address);
    bool Remove(const QString& name);
    bool Find(const QString& name, QString& address) const;
    void Clear();
    ~SymbolicNameTable();
private:
    TreeNode *Insert(TreeNode* node, const QString& name, const QString& address);
    TreeNode *Remove(TreeNode* node, const QString& name);
    TreeNode *Find(TreeNode* node, const QString& name) const;
    void Clear(TreeNode* node);
    int Height(TreeNode* node) const;
    int GetBalance(TreeNode* node) const;
    TreeNode *SmallRightRotate(TreeNode* a);
    TreeNode *BigRightRotate(TreeNode* a);
    TreeNode *SmallLeftRotate(TreeNode* a);
    TreeNode *BigLeftRotate(TreeNode* a);
};

#endif // SYMBOLICNAMETABLE_H
