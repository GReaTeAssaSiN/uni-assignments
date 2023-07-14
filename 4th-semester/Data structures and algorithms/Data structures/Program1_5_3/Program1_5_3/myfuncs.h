#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystruct.h"

void MenuForChoices();
char getCase();

bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);
void printDashes();
std::string getElem();
std::string getChoiceLeftRight();

void createNewNode(Tree*& binary_tree);
void order_1(Node*& tree_root);
void order_2(Node*& tree_root);
void order_3(Node*& tree_root);
void userSearchNodePBT(Node* tree_root);
void searchPBT(Node* tree_root, const int& searched_data, bool& succesful_recursion, Node*& parentNode);
void clearTreeNodes(Node*& tree_root);
void clearBinaryTree(Tree*& binary_tree);
void DestroyAllTree(Node*& tree_root);

#endif /*MYFUNCS_H_*/