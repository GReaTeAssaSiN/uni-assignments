#include <iostream>
#include <string>
#include "myfuncs.h"
#include "mystruct.h"

/*������� ��� �������� ���������������� �����*/
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

/*���������������� ����*/
//���������������� ����.
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) �������� �� ��������� ������ � ������� �� ����� �������������� ������ ���������." << std::endl <<
		"2) ����� �������� � �������� �������������� ������ � �������� ������." << std::endl <<
		"3) � �������� ������ �������� ����� ������� ����� ��������." << std::endl <<
		"4) � �������� ������ �������� ����� ������� ����� ���������." << std::endl <<
		"5) ������� �������� ������� �� ��������� ������ � ����������� ����� �������� �� ��������������� ������." << std::endl <<
		"6) ����� �������� ��������� ���������������� ������ �� �����." << std::endl <<
		"7) �����." << std::endl;
}
//������ �������� �� ������� � ������������.
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

/*�������� �������*/
//����� �������������� ������ ��������� ������ �� �������.
void printList(List* f_myList)
{
	if (isEmptyList(f_myList))
		std::cout << "������ ����." << std::endl;
	else
	{
		Node* tempPtr = f_myList->listPointer;
		std::cout << "������� ��������� ������: " << std::endl;
		for (int i{}; i < f_myList->count; i++)
		{
			tempPtr = tempPtr->next;
			std::cout << i + 1 << "-��(-��,-��) ������� ������:\t" << tempPtr->data << std::endl;
		}
	}
}
//����� �������� � �������� �������������� ������ � �������� ������.
void searchList(List* f_myList)
{
	if (isEmptyList(f_myList))
		std::cout << "������ ����. �������� ������ �������� ����������." << std::endl;
	else
	{
		while (true)
		{
			std::string exit_or_searchingElem{ getElem() };
			if (exit_or_searchingElem != "q")
			{
				Node* tempPtr = f_myList->listPointer;
				int searched_elems{}, searching_elem{ convertStrToInt(exit_or_searchingElem) };
				for (int i{}; i < f_myList->count; i++)
				{
					tempPtr = tempPtr->next;
					if (tempPtr->data == searching_elem)
					{
						searched_elems++;
						std::cout << i + 1 << "-��(-��,-��) ������� ������:\t" << tempPtr->data << std::endl;
					}
				}
				if (searched_elems != 0)
				{
					std::cout << "����� ���� ������� " << searched_elems << " �������(-�,-��)." << std::endl;
					break;
				}
				else
					std::cout << "��������� ������� ����������� � ������." << std::endl;
			}
			else
				break;
		}
	}
}
//���������� �������� ��/����� ��������� � �������� ������.
void addNewElem(List*& f_myList, List*& f_auxiliary_myList, const int& before_after)
{
	if (isEmptyList(f_myList))
	{
		std::cout << "������ ����. ������� �������, ������� ���������� ��������, ��� ������� � ����." << std::endl;
		std::string exit_or_newElem{ getElem() };
		if (exit_or_newElem != "q")
		{
			int new_elem{ convertStrToInt(exit_or_newElem) };
			try
			{
				Node* new_node = new Node{};
				new_node->data = new_elem;
				new_node->next = nullptr;
				f_myList->listPointer->next = new_node;
				f_myList->count++;
				std::cout << "������� '" << new_elem << "' ��� ������� �������� � ������." << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
				std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
				clearList(f_myList, f_auxiliary_myList);
				exit(-1);
			}
		}
	}
	else
	{
		std::cout << "������� �������, ������� ���������� ��������, ��� ������� � ����." << std::endl;
		std::string newElem_or_exit{ getElem() };
		if (newElem_or_exit != "q")
		{
			int new_elem{ convertStrToInt(newElem_or_exit) };
			if (before_after == 3)
				std::cout << "������� �������, ����� ������� ���������� �������� �����, ��� ������� � ����." << std::endl;
			else
				std::cout << "������� �������, ����� �������� ���������� �������� �����, ��� ������� � ����." << std::endl;
			while (true)
			{
				std::string exit_or_specifiedElement{ getElem() };
				if (exit_or_specifiedElement != "q")
				{
					int specified_elem{ convertStrToInt(exit_or_specifiedElement) };
					Node* tempPtr = f_myList->listPointer, * specified_node = searchElem(f_myList, specified_elem);
					if (specified_node == nullptr)
						std::cout << "��������� ������� ����������� � ������. ��������� ���� �������� ������ ��� ������� � ����." << std::endl;
					else
					{
						if (before_after == 3)
						{
							try
							{
								Node* new_node = new Node{};
								new_node->data = new_elem;
								new_node->next = specified_node;
								while (tempPtr->next != specified_node)
									tempPtr = tempPtr->next;
								tempPtr->next = new_node;
								f_myList->count++;
							}
							catch (const std::exception& e)
							{
								std::cout << e.what() << std::endl;
								std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
								clearList(f_myList, f_auxiliary_myList);
								exit(-1);
							}
						}
						else
						{
							try
							{
								Node* new_node = new Node{};
								new_node->data = new_elem;
								new_node->next = specified_node->next;
								specified_node->next = new_node;
								f_myList->count++;
							}
							catch (const std::exception& e)
							{
								std::cout << e.what() << std::endl;
								std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
								clearList(f_myList, f_auxiliary_myList);
								exit(-1);
							}
						}
						if (before_after == 3)
							std::cout << "����� ������� '" << new_elem << "' ��� ������� �������� ����� ��������� '" << specified_elem << "'." << std::endl;
						else
							std::cout << "����� ������� '" << new_elem << "' ��� ������� �������� ����� �������� '" << specified_elem << "'." << std::endl;
						break;
					}
				}
				else
					break;
			}
		}
	}
}
//����������� ���� ���������� ������������ ������ � ����.
void clearList(List*& f_myList, List*& f_auxiliary_myList)
{
	clear(f_myList);
	clear(f_auxiliary_myList);
	std::cout << std::endl << "��� ���������� ������ ���� ���������� � ����. ���������� ��������� . . ." << std::endl;
}
//�������� �������� �� ��������� ������ � ����������� ���������� �������� �� ��������������� ������.
void removeElem(List*& f_myList, List*& f_auxiliary_myList)
{
	if (isEmptyList(f_myList))
		std::cout << "������ ����. �������� �������� �������� �� ������ ����������." << std::endl;
	else
	{
		printList(f_myList);
		while (true)
		{
			std::string exit_or_fixedElem{ getElem() };
			if (exit_or_fixedElem != "q")
			{
				int fixed_elem{ convertStrToInt(exit_or_fixedElem) };
				Node* tempPtr = f_myList->listPointer, * ptr_removing_elem = searchElem(f_myList, fixed_elem);
				if (ptr_removing_elem != nullptr)
				{
					while (tempPtr->next != ptr_removing_elem)
						tempPtr = tempPtr->next;
					tempPtr->next = ptr_removing_elem->next;
					ptr_removing_elem->next = f_auxiliary_myList->listPointer->next;
					f_auxiliary_myList->listPointer->next = ptr_removing_elem;
					f_myList->count--;
					f_auxiliary_myList->count++;
					std::cout << "������� '" << ptr_removing_elem->data << "' ��� ������� ������ �� ��������� ������ � �������� �� ��������������� ������ (����)." << std::endl;
					break;
				}
				else
					std::cout << "��������� ������� ����������� � ������. ��������� ���� ���������� �������� ��� ������� � ����." << std::endl;
			}
			else
				break;
		}
	}
}

/*��������������� �������*/
//�������� ������ �� ������� (������� ���� �� ������ ��������)
bool isEmptyList(List* f_myList)
{
	return (f_myList->listPointer->next == nullptr) ? true : false;
}
//����������� ���� ���������� ������������ ������ ��� ������� ������ � ����.
void clear(List*& f_list)
{
	int count_elems{ f_list->count };
	for (int i{}; i <= count_elems; i++)
	{
		Node* tempPtr = f_list->listPointer->next;
		f_list->listPointer->next = nullptr;
		delete f_list->listPointer;
		f_list->listPointer = tempPtr;
		f_list->count--;
	}
	delete f_list;
}
//����� �������� � �������� �������������� ������ � �������� ������ � ����������� ��������� �� ��� "����" (Node*).
Node* searchElem(List* f_myList, const int& searching_elem)
{
	Node* tempPtr = f_myList->listPointer;
	for (int i{}; i < f_myList->count; i++)
	{
		tempPtr = tempPtr->next;
		if (tempPtr->data == searching_elem)
			return tempPtr;
	}
	return nullptr;
}
//������ ��������������� ����� �������� � ������������.
std::string getElem()
{
	std::cout << "������� �������������� ����� �������� (����� �����) ��� 'q', ����� ����� � ����: ";
	while (true)
	{
		std::string new_elem{};
		std::getline(std::cin, new_elem);
		if (checkStrIsNumeric(new_elem) || new_elem == "q")
			return new_elem;
		else
			std::cout << "������ �����. �� ������ ������ ����� ����� ��� 'q'. ��������� ����: ";
	}
}
//����� ����������� ���������� ����� ���������� ������������ � �������.
void printDashes()
{
	std::cout << "---------------------------------------------------------------------------------------------------------------" << "\t" << std::endl;
}