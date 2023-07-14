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

struct StackNode
{
	int level{};
	Node* introduced_tree_node{};
	StackNode* next_stack_node{};
};

struct Stack
{
	int level{ -1 };
	StackNode* stackPtr{};
};

#endif /* MYSTRUCT_H_ */