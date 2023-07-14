#ifndef MYSTRUCTS_H_
#define MYSTRUCTS_H_

struct Node
{
	Node* next{};
	std::string key{};
};

struct Element
{
	Node* head{};
	Node* tail{};
	std::string key{};
};

struct HashTable
{
	int number_m{}, count{};
	Element* array{};
};

#endif /* MYSTRUCTS_H_ */