#include <iostream>
#include <string>
#include "myfuncs.h"

/*�������������� �������*/
//����
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}
//�������� ��������� ������������� ������ �� ������������ ������� 'q'
bool isSymbolQ()
{
	std::cout << "������� ������ 'q', ���� ������� ����� �� ���������, ����� ������ ������ ������ Enter: ";
	std::string symbol{};
	std::getline(std::cin, symbol);
	if (symbol == "q")
		return true;
	return false;
}
//����� ����������� ���������� ����� ���������� ������������ � �������.
void printDashes()
{
	std::cout << "---------------------------------------------------------------------------------------------------------------" << "\t" << std::endl;
}

/*������� ��� ������ � ��������*/
//�������� ������� �� �������
bool isEmptyQueue(Queue* f_queue)
{
	return (f_queue->frnt == nullptr) ? true : false;
}
//���������� �������� � �������
void enQueue(Queue*& f_queue, char f_symbol)
{
	try
	{
		Node* new_elem = new Node{};
		if (f_queue->frnt == nullptr)
		{
			f_queue->frnt = new_elem;
			f_queue->rear = f_queue->frnt;
		}
		else
		{
			f_queue->rear->next = new_elem;
			f_queue->rear = new_elem;
		}
		std::cout << "� ������� ��� �������� ������� '" << f_symbol << "'." << std::endl;
		f_queue->rear->data = f_symbol;
		f_queue->rear->next = f_queue->frnt;
		f_queue->count++;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
		clearQueue(f_queue);
		exit(-1);
	}
}
//�������� �������� �� �������
void deQueue(Queue*& f_queue)
{
	if (isEmptyQueue(f_queue))
		std::cout << "������� �����, �������� �������� �������� �� ������� ����������." << std::endl;
	else
	{
		Node* temp = f_queue->frnt;
		if (f_queue->frnt == f_queue->rear)
		{
			f_queue->frnt = nullptr;
			f_queue->rear = nullptr;
		}
		else
		{
			f_queue->frnt = f_queue->frnt->next;
			f_queue->rear->next = f_queue->frnt;
		}
		temp->next = nullptr;
		std::cout << "������� '" << temp->data << "' �� ������� ������� ������." << std::endl;
		delete temp;
		f_queue->count--;
	}
}
//����� �������� ��������� ������� �� �����
void printQueue(Queue* f_queue)
{
	if (isEmptyQueue(f_queue))
		std::cout << "������� �����.";
	else
	{
		Node* temp = f_queue->frnt;
		std::cout << "������� ��������� �������: ";
		for (int i{ f_queue->count }; i > 0; i--)
		{
			std::cout << temp->data;
			temp = temp->next;
		}
		temp = nullptr;
	}
	std::cout << std::endl << std::endl;
}
//������� ���������� ������ ��� �������
void clearQueue(Queue*& f_queue)
{
	for (int i{ f_queue->count }; i > 0; i--)
	{
		Node* temp = f_queue->frnt->next;
		f_queue->frnt->next = nullptr;
		delete f_queue->frnt;
		f_queue->frnt = temp;
		f_queue->rear->next = f_queue->frnt;
		f_queue->count--;
		temp = nullptr;
	}
	delete f_queue;
	std::cout << "��� ���������� ������ ���� ���������� � ����. ���������� ��������� . . ." << std::endl;
}