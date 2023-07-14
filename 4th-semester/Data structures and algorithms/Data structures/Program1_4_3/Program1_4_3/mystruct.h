#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_

struct Node
{
	int data{};
	Node* next{};
	Node* prev{};
};

struct List
{
	int symbolischer_name{};
	int count{};
	Node* headPointer{};
	List* nextList{};
};

struct ListOfLists
{
	int count{};
	List* headListPointer;
};

#endif /* MYSTRUCT_H_ */