#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystruct.h"

void MenuForChoices();
char getCase();

float getRandomNumber(float min, float max);
bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);
void printDashes();
void getNewNumberVertices(Tree*& binary_tree, Stack*& stack);

int getNumberVertices();
bool empty_tree(Node* tree_root);
void recursivelyBuildingPBT(Node*& tree_root, int count);
void order_1(Node*& tree_root, int level);
void order_2(Node*& tree_root, int level);
void order_3(Node*& tree_root, int level);
void NoRecursiveOrder2(Tree*& binary_tree, Stack*& stack);
void clearTreeNodes(Node*& tree_root);
void clearBinaryTreeAndStack(Tree*& binary_tree, Stack*& stack);

#endif /* MYFUNCS_H_ */