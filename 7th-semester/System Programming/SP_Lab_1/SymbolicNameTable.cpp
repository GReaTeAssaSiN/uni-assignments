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
void SymbolicNameTable::Insert(const QString &name, const QString &address){
    root = Insert(root, name, address);
}
//Удаление узла (элемента ТСИ) по СИ.
bool SymbolicNameTable::Remove(const QString &name){
    QString address{};
    if (Find(name, address)){
        root = Remove(root, name);
        return true;
    }
    return false;
}
//Поиска узла (элемента ТСИ) по СИ.
bool SymbolicNameTable::Find(const QString &name, QString &address) const{
    TreeNode* node = Find(root, name);
    if (node){
        address = node->address.value();
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
TreeNode *SymbolicNameTable::Insert(TreeNode *node, const QString &name, const QString &address){
    if (!node)
        return new TreeNode(name, address);

    if (name < node->name.value())
        node->left = Insert(node->left, name, address);
    else if (name > node->name.value())
        node->right = Insert(node->right, name, address);
    else{
        node->address = address; //Если СИ совпадают, то обновляем адреса.
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
TreeNode *SymbolicNameTable::Remove(TreeNode *node, const QString &name){
    if (!node)
        return node;

    if (name < node->name.value())
        node->left = Remove(node->left, node->name.value());
    else if (name > node->name.value())
        node->right = Remove(node->right, node->name.value());
    else{
        if (!node->left){
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right){
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }
        TreeNode* temp = node->right;
        while (temp->left) {
            temp = temp->left;
        }
        node->name = temp->name;
        node->address = temp->address;
        node->right = Remove(node->right, temp->name.value());
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
//Поиск узла в дереве по адресу.
TreeNode *SymbolicNameTable::Find(TreeNode *node, const QString &name) const{
    if (!node || node->name.value() == name)
        return node;
    if (name < node->name.value())
        return Find(node->left, name);
    return Find(node->right, name);
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
