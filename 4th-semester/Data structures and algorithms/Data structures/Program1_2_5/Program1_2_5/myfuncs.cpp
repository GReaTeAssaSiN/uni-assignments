#include <iostream>
#include <string>
#include "myfuncs.h"

/*���������������� �������*/
//���������������� ����
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) ��������� ������� �������." << std::endl <<
		"2) ��������� ������������� �������." << std::endl <<
		"3) ��������� ������� � ����� �������." << std::endl <<
		"4) ������� ������� �� ������ �������." << std::endl <<
		"5) ����� �������� ��������� ������� �� �����." << std::endl <<
		"6) �����." << std::endl;
}
//������ �������� � �������� � ������������
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 6). ��������� ����:" << std::endl;
		}
	}
}

/*�������� �������*/
//�������� ������� �� �������
bool isEmptyQueue(const Queue& f_queue)
{
	return (f_queue.frnt == -1) ? true : false;
}
//�������� ������� �� �������������
bool isFullnessQueue(const Queue& f_queue)
{
	return ((f_queue.frnt == 0) && (f_queue.rear == sizeQueue - 1) || (f_queue.frnt == f_queue.rear + 1)) ? true : false;
}
//���������� �������� � �������
void enQueue(Queue& f_queue)
{
	if (isFullnessQueue(f_queue))
		std::cout << "������� ���������. ���������� ������ �������� � ������� ����������." << std::endl;
	else
	{
		if (f_queue.frnt == -1)
			f_queue.frnt = 0;
		f_queue.rear = (f_queue.rear + 1) % sizeQueue;
		std::cout << "������� ����� ������� (����� �����), ������� ������ �������� � �������: ";
		std::string newElem{};
		while (true)
		{
			std::getline(std::cin, newElem);
			if (checkStrIsNumeric(newElem))
			{
				f_queue.queue[f_queue.rear] = convertStrToInt(newElem);
				std::cout << "����� ������� ������� �������� � �������." << std::endl;
				break;
			}
			else
			{
				std::cout << "������ �����. �� ������ ������ ����� �����. ��������� ����: " << std::endl;
			}
		}
	}
}
//�������� �������� �� �������
void deQueue(Queue& f_queue)
{
	if (isEmptyQueue(f_queue))
	{
		std::cout << "������� �����, �������� �������� �������� �� ������� ����������." << std::endl;
	}
	else
	{
		int item{ f_queue.queue[f_queue.frnt] };
		if (f_queue.frnt == f_queue.rear)
		{
			f_queue.frnt = -1;
			f_queue.rear = -1;
		}
		else
		{
			f_queue.queue[f_queue.frnt] = 0;
			f_queue.frnt = (f_queue.frnt + 1) % sizeQueue;
		}
		std::cout << "������� " << item << " �� ������� ������� ������." << std::endl;
	}
}
//����� �������� ��������� ������� �� �����
void printQueue(const Queue& f_queue)
{
	if (isEmptyQueue(f_queue))
		std::cout << "������� �����." << std::endl;
	else
	{
		std::cout << "��������� frnt -> " << f_queue.frnt << std::endl;
		std::cout << "��������� rear -> " << f_queue.rear << std::endl;
		std::cout << "������� ��������� �������: " << std::endl;
		for (int i{ f_queue.frnt }; i != f_queue.rear; i = (i + 1) % sizeQueue)
			std::cout << f_queue.queue[i] << " ";
		std::cout << f_queue.queue[f_queue.rear % sizeQueue] << std::endl;
	}
}

/*��������������� �������*/
//�������� �������� ������������� ������ �� ����������� �������������� � ����� ��������������� �����.
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