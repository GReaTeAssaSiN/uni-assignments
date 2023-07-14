#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_

struct Node
{
	int data{};
	Node* left{};
	Node* right{};
};

struct Tree
{
	int number_vertices{};
	Node* root{};
};

#endif /* MYSTRUCT_H_ */