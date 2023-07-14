#include <iostream>
#include <string> //��� ������� ��������� ����������������� �����
#include <cstdlib> //��� ������� rand() � srand()
#include <ctime> //��� ������� time()
#include <stdlib.h> //��� ������� exit()
#include "myfuncs.h"
#include "mystruct.h"

/*��������������� �������*/
//�������� �������� ������������� ������ �� ����������� �������������� � ����� �����.
bool checkStrIsNumeric(std::string const& tempStr)
{
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((i == 0) && (tempStr[i] == '-'))
			continue;
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//�������������� �������� ������������� ������ � �����.
int convertStrToInt(std::string convertStr)
{
	double number{};
	bool negative_number{ false };
	for (int i{}; i < convertStr.length(); i++)
	{
		if ((i == 0) && (convertStr[i] == '-'))
		{
			negative_number = true;
			continue;
		}
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
	}
	return negative_number ? static_cast<int>(-number) : static_cast<int>(number);
}
//����
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}
//����� ����� ��������(0)/���������������(1) ������.
unsigned char get_0_1()
{
	while (true)
	{
		char sm;
		std::cin >> sm;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (sm == '0' || sm == '1')
		{
			return sm;
		}
		else
		{
			std::cout << "������ �����. ������� 0 ��� 1: \n";
		}
	}
}

/*���������������� ����*/
//���������������� ����.
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) ��������� ������� ��������� �����." << std::endl <<
		"2) �������� ������� � ������� ��������� �����." << std::endl <<
		"3) �������� ��������� ����� �������� (���������) � ������� ��������� �����." << std::endl <<
		"4) ������� ������� �� ������� ��������� �����." << std::endl <<
		"5) ����� �������� ��������� ��������� ����� �� �����." << std::endl <<
		"6) ����� �������� ��������� ���������������� ����� �� �����." << std::endl <<
		"7) �����." << std::endl;
}
//������ �������� �� ������ � ������������.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 7). ��������� ����:" << std::endl;
		}
	}
}

/*�������� ������� ������ �� ������*/
//�������� ����� �� �������.
bool isEmpty(Stack* stack)
{
	return stack->sp == nullptr ? true : false;
}
//���������� �������� � ������� �����.
void push(Stack* stack, const int& x)
{
	try
	{
		Node* node = new Node{};
		node->data = x;
		node->next = stack->sp;
		stack->sp = node;
		stack->count++;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
		clear(stack);
		exit(-1);
	}
}
//�������� �������� �� ������� ������ ����� � ������� ������� �����.
bool pass(Stack* from_stack, Stack* to_stack)
{
	if (isEmpty(from_stack))
		return false;
	else
	{
		Node* tempPtr = from_stack->sp->next;
		from_stack->sp->next = to_stack->sp;
		to_stack->sp = from_stack->sp;
		from_stack->sp = tempPtr;
		to_stack->count++;
		from_stack->count--;
		return true;
	}
}
//�������� �������� �� ������� �����.
void pop(Stack* stack)
{
	if (!isEmpty(stack))
	{
		Node* freePtr = stack->sp;
		stack->sp = stack->sp->next;
		delete freePtr;
		stack->count--;
	}
}
//����� �������� ��������� ����� �� �����.
void print(Stack* stack)
{
	Node* tempPtr = stack->sp;
	for (int i{ stack->count }; i > 0; i--)
	{
		std::cout << stack->sp->data << ((((i - 1) % 10) == 0) ? "\n" : "\t");
		stack->sp = stack->sp->next;
	}
	stack->sp = tempPtr;
}
//������� ���������� ������ ��� �����.
void clear(Stack*& stack)
{
	for (int i{ stack->count }; i > 0; i--)
	{
		Node* tempPtr = stack->sp->next;
		delete stack->sp;
		stack->sp = tempPtr;
		stack->count--;
	}
	delete stack;
}

/*�������� ������� ������ �� ������ � ������� ��������� ��� ������������*/
//���������� �������� (������/�� ���������������� �����) � ������� ��������� �����.
void user_push(Stack* baseStack, Stack* auxiliaryStack)
{
	std::cout << "�� ������ �������� ����� �������(0) ��� ������� ������� � ������� ���������������� �����(1): ";
	unsigned char base_auxiliary{ get_0_1() };
	if (base_auxiliary == '0' || (base_auxiliary == '1' && !pass(auxiliaryStack, baseStack)))
	{
		if (base_auxiliary == '1')
			std::cout << "��������������� ���� ���� �� ������ ������. �������������� �������� ������." << std::endl;
		std::cout << "������� ����� ������� (����� �����), ������� ������ �������� � ������� �����: ";
		std::string newElem{};
		while (true)
		{
			std::getline(std::cin, newElem);
			if (checkStrIsNumeric(newElem))
			{
				push(baseStack, convertStrToInt(newElem));
				std::cout << "����� ������� ������� �������� � ������� �����." << std::endl;
				break;
			}
			else
			{
				std::cout << "������ �����. �� ������ ������ ����� �����. ��������� ����: " << std::endl;
			}
		}
	}
	else
	{
		pass(auxiliaryStack, baseStack);
		std::cout << "�� ������� ���������������� ����� ������� �������� ������� � ������� ��������� �����." << std::endl;
	}
}
//���������� ������������� ���������� ��������� ��������� � ������� ��������� �����.
void user_push_random(Stack* baseStack)
{
	//�������� ���� � ������������ ������� (��������� ������������������ ��������� ����� �� ���������).
	srand(static_cast<unsigned int>(time(0)));
	std::cout << "������� ���������� �������� (���������), ������� ������ ������� � ����: ";
	std::string count{};
	while (true)
	{
		std::getline(std::cin, count);
		if (checkStrIsNumeric(count) && convertStrToInt(count) >= 0)
		{
			int count_new_elems{ convertStrToInt(count) };
			for (int i{}; i < count_new_elems; i++)
				push(baseStack, static_cast<int>(getRandomNumber(-1000, 1000)));
			std::cout << "��� ����� �������� (" << count_new_elems << ") ���� ������� �������� � ����." << std::endl;
			break;
		}
		else
		{
			std::cout << "������ �����. �� ������ ������ ����� ��������������� �����. ��������� ����: " << std::endl;
		}
	}
}
//�������� �������� (������������/� ���������� �� ��������������� ����) �� ������� ��������� �����.
void user_pop(Stack* baseStack, Stack* auxiliaryStack)
{
	if (isEmpty(baseStack))
		std::cout << "���� ����, �������� �������� �������� �� ������� ����� ����������." << std::endl;
	else
	{
		std::cout << "�� ������ ������������ ������� ������� � ������������� ������ ��� ����(0) ��� �������� ��� � ������� ���������������� ����� ��������� ���������(1): ";
		unsigned char base_auxiliary{ get_0_1() };
		if (base_auxiliary == '0')
		{
			pop(baseStack);
			std::cout << "������� �� ������� ����� ������� ������." << std::endl;
		}
		else
		{
			if (pass(baseStack, auxiliaryStack))
				std::cout << "������� �� ������� ��������� ����� ������� ������� � ������� ���������������� ����� ��������� ���������." << std::endl;
		}
	}
}
//����� �������� ��������� ������ �� �����.
void user_printBaseStack(Stack* baseStack)
{
	if (isEmpty(baseStack))
		std::cout << "�������� ���� ����." << std::endl;
	else
	{
		std::cout << "������� ��������� ��������� �����: " << std::endl;
		print(baseStack);
	}
}
void user_printAuxiliaryStack(Stack* auxiliaryStack)
{
	if (isEmpty(auxiliaryStack))
		std::cout << "��������������� ���� ����." << std::endl;
	else
	{
		std::cout << "������� ��������� ���������������� �����: " << std::endl;
		print(auxiliaryStack);
	}
}
//������� ���������� ������ ��� ������
void user_clear(Stack*& baseStack, Stack*& auxiliaryStack)
{
	clear(baseStack);
	clear(auxiliaryStack);
	std::cout << std::endl << "��� ���������� ������ ���� ���������� � ����. ���������� ��������� . . ." << std::endl;
}