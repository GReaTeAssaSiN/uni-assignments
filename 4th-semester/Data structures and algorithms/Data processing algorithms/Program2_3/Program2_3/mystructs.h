#ifndef MYSTRUCTS_H_
#define MYSTRUCTS_H_

struct DynamicArray
{
	int* myArray{};
	int count{};
};


//��� ���������� ��������� (�������, ���������) ����������.
struct Node
{
	int data{};
	Node* next{};
};

struct Bucket
{
	Node* head_ptr{};
	Node* last_element{};
};

#endif /* MYSTRUCTS_H_ */