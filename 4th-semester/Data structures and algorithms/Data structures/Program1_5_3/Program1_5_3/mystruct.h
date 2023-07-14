#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_

struct Node
{
	int data{};
	int level{ -1 };
	Node* left{};
	Node* right{};
};

struct Tree
{
	int number_vertices{};
	Node* root{};
};

#endif /*BINARYTREE_H_*/