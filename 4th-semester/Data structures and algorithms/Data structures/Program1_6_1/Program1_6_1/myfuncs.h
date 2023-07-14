#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystruct.h"

void MenuForChoices();
char getCase();

std::string get0_1();
bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);
void printDashes();
std::string getElem();
void changePointersOnDeletion(Node*& tree_root, Node*& changing_parent, Node*& changing_child);

bool isBinaryTreeEmpty(Node* tree_root);
Node* searchTreeNode(Node*& tree_root, const int& searched_key);
void addNewNodeToTreeNonRecursive(Node*& tree_root, const int& adding_key);
Node* addNewNodeToTreeRecursive(Node*& tree_root, Node* parent, const int& adding_key);
void printTreeInBackwardSymmetricOrder(Node*& tree_root, int level);
void printTreeInSymmetricalOrderWithCount(Node*& tree_root);
void removeNodeFromTree(Node*& tree_root, const int& removing_key);
void DestroyAllTree(Node*& tree_root);

void userCase1(Tree*& binary_tree);
void userCase2(Tree*& binary_tree);
void userCase3(Node*& tree_root);
void userCase4(Node*& tree_root);
void userCase5(Node*& tree_root);
void userCase6(Tree*& binary_tree);
void userCase7(Tree*& binary_tree);
void userCase8(Tree*& binary_tree);

#endif /*MYFUNCS_H_*/