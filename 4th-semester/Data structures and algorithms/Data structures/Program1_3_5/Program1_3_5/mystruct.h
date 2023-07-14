#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_

struct Node
{
	int data{};
	Node* next{};
};

struct List
{
	int count{};
	Node* listPointer{};
};

#endif /* MYSTRUCT_H_ */