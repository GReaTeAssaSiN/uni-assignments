#include "symbolicnametable.h"

//Конструктор.
SymbolicNameTable::SymbolicNameTable(): root(nullptr){}
//Деструктор.
SymbolicNameTable::~SymbolicNameTable()
{
    Clear();
}

/*МЕТОДЫ ОБРАБОТКИ ТСИ*/
//Вставка нового узла (элемента ТСИ).
void SymbolicNameTable::Insert(const QString &name, const QString &address, const QString& section, const QString& name_type){
    root = Insert(root, name, address, section, name_type);
}
//Удаление узла (элемента ТСИ) по СИ и секции.
bool SymbolicNameTable::Remove(const QString &name, const QString& section){
    QString address{}, name_type{};
    if (Find(name, address, section, name_type)){
        root = Remove(root, name, section);
        return true;
    }
    return false;
}
//Поиска узла (элемента ТСИ) по СИ и секции.
bool SymbolicNameTable::Find(const QString &name, QString &address, const QString& section, QString& name_type) const{
    TreeNode* node = Find(root, name, section);
    if (node){
        address = node->address.value();
        name_type = node->name_type.value();
        return true;
    }
    return false;
}
//Изменение адреса узла с текущей меткой и секцией в ТСИ.
bool SymbolicNameTable::Update(const QString &name, const QString &section, const QString &new_address)
{
    TreeNode* node = Find(root, name, section);
    if (node) {
        node->address = new_address;
        return true;
    }
    return false;
}
//Удаление ТСИ.
void SymbolicNameTable::Clear()
{
    Clear(root);
    root = nullptr;
}

/*МЕТОДЫ ДЛЯ ОБРАБОТКИ СБАЛАНСИРОВАННОГО АВЛ-ДЕРЕВА*/
//Вставка нового узла в дерево с балансировкой.
TreeNode *SymbolicNameTable::Insert(TreeNode *node, const QString &name, const QString &address, const QString& section, const QString& name_type){
    if (!node)
        return new TreeNode(name, address, section, name_type);

    if (std::make_pair(name, section) < std::make_pair(node->name.value(), node->section.value()))
        node->left = Insert(node->left, name, address, section, name_type);
    else if (std::make_pair(name, section) > std::make_pair(node->name.value(), node->section.value()))
        node->right = Insert(node->right, name, address, section, name_type);
    else {
        // Если метка совпадает и секция совпадает, обновляем данные
        node->address = address;
        node->name_type = name_type;
        return node;
    }

    node->height = 1 + std::max(Height(node->left), Height(node->right));

    int balance = GetBalance(node);

    if (balance == 2 && Height(node->right->left) <= Height(node->right->right))
    {
        return SmallLeftRotate(node);
    }
    if (balance == 2 && Height(node->right->left) > Height(node->right->right))
    {
        return BigLeftRotate(node);
    }
    if (balance == -2 && Height(node->left->right) <= Height(node->left->left))
    {
        return SmallRightRotate(node);
    }
    if (balance == -2 && Height(node->left->right) > Height(node->left->left))
    {
        return BigRightRotate(node);
    }

    return node;
}
//Удаление узла из дерева с балансировкой.
TreeNode *SymbolicNameTable::Remove(TreeNode *node, const QString &name, const QString& section){
    if (!node)
        return node;

    if (std::make_pair(name, section) < std::make_pair(node->name.value(), node->section.value()))
        node->left = Remove(node->left, name, section);
    else if (std::make_pair(name, section) > std::make_pair(node->name.value(), node->section.value()))
        node->right = Remove(node->right, name, section);
    else {
        // Найден узел для удаления.
        if (!node->left || !node->right) {
            TreeNode *temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }

        TreeNode *temp = node->right;
        while (temp->left)
            temp = temp->left;

        node->name = temp->name;
        node->address = temp->address;
        node->section = temp->section;
        node->name_type = temp->name_type;
        node->right = Remove(node->right, temp->name.value(), temp->section.value());
    }

    node->height = 1 + std::max(Height(node->left), Height(node->right));

    int balance = GetBalance(node);

    // Балансировка дерева
    if (balance == 2 && Height(node->right->left) <= Height(node->right->right))
    {
        return SmallLeftRotate(node);
    }
    if (balance == 2 && Height(node->right->left) > Height(node->right->right))
    {
        return BigLeftRotate(node);
    }
    if (balance == -2 && Height(node->left->right) <= Height(node->left->left))
    {
        return SmallRightRotate(node);
    }
    if (balance == -2 && Height(node->left->right) > Height(node->left->left))
    {
        return BigRightRotate(node);
    }

    return node;
}
//Поиск узла в дереве по СИ и секции.
TreeNode *SymbolicNameTable::Find(TreeNode *node, const QString &name, const QString &section) const {
    if (!node)
        return nullptr;

    if (std::make_pair(name, section) == std::make_pair(node->name.value(), node->section.value()))
        return node;

    if (std::make_pair(name, section) < std::make_pair(node->name.value(), node->section.value()))
        return Find(node->left, name, section);

    return Find(node->right, name, section);
}
//Удаление дерева.
void SymbolicNameTable::Clear(TreeNode *node){
    if (node) {
        Clear(node->left);
        Clear(node->right);
        delete node;
    }
}
//Получение высоты узла.
int SymbolicNameTable::Height(TreeNode *node) const{
    return node ? node->height : 0;
}
//Получение баланса (balance factor) узла.
int SymbolicNameTable::GetBalance(TreeNode *node) const{
    return node ? Height(node->right) - Height(node->left) : 0;
};
//Малое левое вращение.
TreeNode* SymbolicNameTable::SmallLeftRotate(TreeNode* a)
{
    TreeNode* b{a->right};
    TreeNode* c{b->left};

    a->right = c;
    b->left = a;

    a->height = 1 + std::max(Height(a->left), Height(a->right));
    b->height = 1 + std::max(Height(b->left), Height(b->right));

    return b;
}
//Большое левое вращение.
TreeNode* SymbolicNameTable::BigLeftRotate(TreeNode* a)
{
    TreeNode* b{a->right};
    TreeNode* c{b->left};
    TreeNode* M{c->left};
    TreeNode* N{c->right};

    c->left = a;
    c->right = b;
    a->right = M;
    b->left = N;

    a->height = 1 + std::max(Height(a->left), Height(a->right));
    b->height = 1 + std::max(Height(b->left), Height(b->right));
    c->height = 1 + std::max(Height(c->left), Height(c->right));

    return c;
}
//Малое правое вращение.
TreeNode* SymbolicNameTable::SmallRightRotate(TreeNode* a)
{
    TreeNode* b{a->left};
    TreeNode* с{b->right};

    a->left = с;
    b->right = a;

    a->height = 1 + std::max(Height(a->left), Height(a->right));
    b->height = 1 + std::max(Height(b->left), Height(b->right));

    return b;
}
// Большое правое вращение
TreeNode* SymbolicNameTable::BigRightRotate(TreeNode* a)
{
    TreeNode* b{a->left};
    TreeNode* c{b->right};
    TreeNode* M{c->left};
    TreeNode* N{c->right};

    c->left = b;
    c->right = a;
    a->left = N;
    b->right = M;

    a->height = 1 + std::max(Height(a->left), Height(a->right));
    b->height = 1 + std::max(Height(b->left), Height(b->right));
    c->height = 1 + std::max(Height(c->left), Height(c->right));

    return c;
}
