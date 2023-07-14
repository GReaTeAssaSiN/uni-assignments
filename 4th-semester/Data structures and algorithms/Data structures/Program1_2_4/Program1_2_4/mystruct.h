#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_

struct Node
{
	int data{};
	Node* next{};
};

struct Stack
{
	int count{};
	Node* sp{};
};

#endif /* MYSTRUCT_H_*/