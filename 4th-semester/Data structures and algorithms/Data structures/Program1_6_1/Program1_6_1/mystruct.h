#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_

struct Node
{
	int key{};
	int count{};
	Node* left{};
	Node* right{};
	Node* parent{};
};

struct Tree
{
	int number_vertices{};
	Node* root{};
};

#endif /*BINARYTREE_H_*/