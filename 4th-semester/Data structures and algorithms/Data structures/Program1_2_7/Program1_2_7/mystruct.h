#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_

struct Node
{
	char data{};
	Node* next{};
};

struct Queue
{
	int count{};
	Node* frnt{}, * rear{};
};

#endif /* MYSTRUCT_H_*/