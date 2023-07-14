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
		"1) ������ ������ �� ���� ��������� � ������� ���� ���������." << std::endl <<
		"2) ����� ��������� �������� �� ���� ���������." << std::endl <<
		"3) ���������� ������ ���������� ������ � ������ �� ���������� ��������." << std::endl <<
		"4) ���������� ������ ���������� ������ � ������ ����� ���������� ��������." << std::endl <<
		"5) ���������� ������ �������� � ��������� ��������� ������ �� ���������� ��������." << std::endl <<
		"6) ���������� ������ �������� � ��������� ��������� ������ ����� ���������� ��������." << std::endl <<
		"7) �������� �������� �� ���������� ���������� ������ ������������� ������." << std::endl <<
		"8) �������� ���������� ���������� ������ �� ������������� ������." << std::endl <<
		"9) �����." << std::endl;
}
//������ �������� �� ���������� � ������������.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8" || choice == "9")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 9). ��������� ����:" << std::endl;
		}
	}
}

/*�������� �������*/
//����� �������������� ������ ��������� ��������� ������� ��������� �� �������.
void printListOfLists(ListOfLists* f_myListOfLists)
{
	if (isEmptyListOfLists(f_myListOfLists))
		std::cout << "������ ������� ����." << std::endl;
	else
	{
		List* tempHeadListPtr = f_myListOfLists->headListPointer;
		std::cout << "������� ��������� ������ �������: " << std::endl;
		for (int i{}; i < f_myListOfLists->count; i++)
		{
			tempHeadListPtr = tempHeadListPtr->nextList;
			std::cout << i + 1 << "-��(-��, -��) ��������� ������ ������� � ������� " << tempHeadListPtr->symbolischer_name << ":" << std::endl;
			Node* tempHeadPtr = tempHeadListPtr->headPointer;
			if (tempHeadListPtr->count == 0)
				std::cout << "\t��������� ����." << std::endl;
			else
			{
				for (int j{}; j < tempHeadListPtr->count; j++)
				{
					tempHeadPtr = tempHeadPtr->next;
					std::cout << "\t" << j + 1 << "-��(-��,-��) ������� ������:\t" << tempHeadPtr->data << std::endl;
				}
			}
			std::cout << std::endl;
		}
	}
}
//����� ��������� �������� � ������ �������.
void searchListOfLists(ListOfLists* f_myListOfLists)
{
	if (isEmptyListOfLists(f_myListOfLists))
		std::cout << "������ ������� ����. �������� ������ �������� � ��������� ����������." << std::endl;
	else
	{
		while (true)
		{
			std::string exit_or_searchingElem{ getElem() };
			if (exit_or_searchingElem != "q")
			{
				List* tempHeadListPtr = f_myListOfLists->headListPointer;
				int total_searched_elems{}, searching_elem{ convertStrToInt(exit_or_searchingElem) };
				for (int i{}; i < f_myListOfLists->count; i++)
				{
					int searched_elems{};
					tempHeadListPtr = tempHeadListPtr->nextList;
					Node* tempHeadPtr = tempHeadListPtr->headPointer;
					std::cout << i + 1 << "-��(-��, -��) ��������� ������ ������� � ������� " << tempHeadListPtr->symbolischer_name << ":" << std::endl;
					for (int j{}; j < tempHeadListPtr->count; j++)
					{
						tempHeadPtr = tempHeadPtr->next;
						if (tempHeadPtr->data == searching_elem)
						{
							searched_elems++;
							std::cout << "\t" << j + 1 << "-��(-��,-��) ������� ������:\t" << tempHeadPtr->data << std::endl;
						}
					}
					std::cout << std::endl;
					if (searched_elems != 0)
						std::cout << "\t����� ���� ������� " << searched_elems << " �������(-�,-��) � ���������." << std::endl;
					else
						std::cout << "\t��������� ������� ����������� � ���������." << std::endl;
					std::cout << std::endl;
					total_searched_elems += searched_elems;
				}
				if (total_searched_elems != 0)
				{
					std::cout << "����� ���� ������� " << total_searched_elems << " �������(-�,-��) � ������ �������." << std::endl;
					break;
				}
				else
					std::cout << "��������� ������� ����������� � ��������� ������ �������. ��������� ���� �������� �������� ��� ������� � ����." << std::endl;
			}
			else
				break;
		}
	}
}
//���������� ������ ��������-������ � ������ �������.
void addNewElemToListOfLists(ListOfLists*& f_myListOfLists, const int& before_or_after)
{
	if (isEmptyListOfLists(f_myListOfLists))
	{
		std::cout << "������ ������� ����. ������� ����� ������, ������� ���������� ��������, ��� ������� � ����." << std::endl;
		std::string exit_or_newList{ getElem() };
		if (exit_or_newList != "q")
		{
			int new_list{ convertStrToInt(exit_or_newList) };
			try
			{
				List* headList = new List{};
				headList->symbolischer_name = new_list;
				Node* headerNode = new Node{};
				headerNode->data = 0;
				headerNode->next = headerNode;
				headerNode->prev = headerNode;
				headList->nextList = nullptr;
				headList->count = 0;
				headList->headPointer = headerNode;
				f_myListOfLists->headListPointer->nextList = headList;
				f_myListOfLists->count++;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
				std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
				clearListOfLists(f_myListOfLists);
				exit(-1);
			}
		}
	}
	else
	{
		std::cout << "������� ����� ������, ������� ���������� ��������, ��� ������� � ����." << std::endl;
		std::string exit_or_newList{ getElem() };
		if (exit_or_newList != "q")
		{
			int new_list{ convertStrToInt(exit_or_newList) };
			if (before_or_after == 3)
				std::cout << "������� ����� ������, ����� ������� ���������� �������� �����, ��� ������� � ����." << std::endl;
			else
				std::cout << "������� ����� ������, ����� �������� ���������� �������� �����, ��� ������� � ����." << std::endl;
			while (true)
			{
				std::string specified_list_or_exit{ getElem() };
				if (specified_list_or_exit != "q")
				{
					int specified_list{ convertStrToInt(specified_list_or_exit) };
					List* prevTempHeadListPtr{ checkListExist(f_myListOfLists, specified_list)};
					if (prevTempHeadListPtr)
					{
						try
						{
							List* headList = new List{};
							headList->symbolischer_name = new_list;
							Node* headerNode = new Node{};
							headerNode->data = 0;
							headerNode->next = headerNode;
							headerNode->prev = headerNode;
							headList->count = 0;
							headList->headPointer = headerNode;
							if (before_or_after == 3)
							{
								headList->nextList = prevTempHeadListPtr->nextList;
								prevTempHeadListPtr->nextList = headList;
								f_myListOfLists->count++;
							}
							else
							{	
								headList->nextList = prevTempHeadListPtr->nextList->nextList;
								prevTempHeadListPtr->nextList->nextList = headList;
								f_myListOfLists->count++;
							}

						}
						catch (const std::exception& e)
						{
							std::cout << e.what() << std::endl;
							std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
							clearListOfLists(f_myListOfLists);
							exit(-1);
						}
						break;
					}
					else
						std::cout << "��������� � ��������� ������� ����������� � ������ �������. ��������� ���� ������ ������ ��� ������� � ����." << std::endl;
				}
				else
					break;
			}
		}
	}
}
//���������� ������ �������� � ��������� ������ ������ ������� ��/����� ���������� ��������.
void addNewElemToList(ListOfLists*& f_myListOfLists, const int& before_or_after)
{
	if (isEmptyListOfLists(f_myListOfLists))
		std::cout << "������ ������� ����. �������� ���������� ������ �������� � ��������� ������ ������� ����������. ���������� ������� �������� ��������� � ������ �������." << std::endl;
	else
	{
		std::cout << "������� ����� ������, � ������� ���������� �������� ����� �������, ��� ������� � ����." << std::endl;
		while (true)
		{
			std::string exit_or_getList{ getElem() };
			if (exit_or_getList != "q")
			{
				int get_list{ convertStrToInt(exit_or_getList) };
				List* prevTempHeadListPtr{ checkListExist(f_myListOfLists, get_list) };
				if (prevTempHeadListPtr)
				{
					if (isEmptyList(prevTempHeadListPtr->nextList))
					{
						std::cout << "��������� ������ ����. ������� �������, ������� ���������� ��������, ��� ������� � ����." << std::endl;
						std::string exit_or_newElem{ getElem() };
						if (exit_or_newElem != "q")
						{
							int new_elem{ convertStrToInt(exit_or_newElem) };
							try
							{
								Node* new_node = new Node{};
								new_node->data = new_elem;
								new_node->next = prevTempHeadListPtr->nextList->headPointer;
								new_node->prev = prevTempHeadListPtr->nextList->headPointer;
								prevTempHeadListPtr->nextList->headPointer->next = new_node;
								prevTempHeadListPtr->nextList->headPointer->prev = new_node;
								prevTempHeadListPtr->nextList->count++;
								std::cout << "������� '" << new_elem << "' ��� ������� �������� � ������ � ������� '" << prevTempHeadListPtr->nextList->symbolischer_name << "'." << std::endl;
							}
							catch (const std::exception& e)
							{
								std::cout << e.what() << std::endl;
								std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
								clearListOfLists(f_myListOfLists);
								exit(-1);
							}
						}
						break;
					}
					else
					{
						std::cout << "������� �������, ������� ���������� ��������, ��� ������� � ����." << std::endl;
						std::string newElem_or_exit{ getElem() };
						if (newElem_or_exit != "q")
						{
							int new_elem{ convertStrToInt(newElem_or_exit) };
							if (before_or_after == 5)
								std::cout << "������� ������� ���������, ����� ������� ���������� �������� �����, ��� ������� � ����." << std::endl;
							else
								std::cout << "������� ������� ���������, ����� �������� ���������� �������� �����, ��� ������� � ����." << std::endl;
							while (true)
							{
								std::string exit_or_specifiedElement{ getElem() };
								if (exit_or_specifiedElement != "q")
								{
									int specified_elem{ convertStrToInt(exit_or_specifiedElement) };
									Node* specified_node = searchElem(prevTempHeadListPtr->nextList, specified_elem);
									if (specified_node == nullptr)
										std::cout << "��������� ������� ����������� � ������. ��������� ���� �������� ������ ��� ������� � ����." << std::endl;
									else
									{
										try
										{
											Node* new_node = new Node{};
											new_node->data = new_elem;
											if (before_or_after == 5)
											{
												specified_node->prev->next = new_node;
												new_node->next = specified_node;
												new_node->prev = specified_node->prev;
												specified_node->prev = new_node;
											}
											else
											{
												new_node->next = specified_node->next;
												new_node->prev = specified_node;
												specified_node->next->prev = new_node;
												specified_node->next = new_node;
											}
											prevTempHeadListPtr->nextList->count++;
												
										}
										catch (const std::exception& e)
										{
											std::cout << e.what() << std::endl;
											std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
											clearListOfLists(f_myListOfLists);
											exit(-1);
										}
										if (before_or_after == 5)
											std::cout << "����� ������� '" << new_elem << "' ��� ������� �������� ����� ��������� '" << specified_elem << "' � ��������� � ������� '" << prevTempHeadListPtr->nextList->symbolischer_name << "'." << std::endl;
										else
											std::cout << "����� ������� '" << new_elem << "' ��� ������� �������� ����� �������� '" << specified_elem << "' � ��������� � ������� '" << prevTempHeadListPtr->nextList->symbolischer_name << "'." << std::endl;
										break;
									}
								}
								else
									break;
							}
							break;
						}
						else
							break;
					}
				}
				else
					std::cout << "��������� � ��������� ������� ����������� � ������. ��������� ���� ������ ��������� ��� ������� � ����." << std::endl;
			}
			else
				break;
		}
	}
}
//�������� ���������� ��������-������ �� ������ �������.
void removeList(ListOfLists*& f_myListOfLists)
{
	if (isEmptyListOfLists(f_myListOfLists))
		std::cout << "������ ������� ����. �������� �������� ��������-������ �� ������ ������� ����������." << std::endl;
	else
	{
		std::cout << "������� ����� ������, ������� ���������� �������, ��� ������� � ����." << std::endl;
		while (true)
		{
			std::string exit_or_getList{ getElem() };
			if (exit_or_getList != "q")
			{
				int get_list{ convertStrToInt(exit_or_getList) };
				List* prevTempHeadListPtr{ checkListExist(f_myListOfLists, get_list) };
				if (prevTempHeadListPtr)
				{
					clearList(f_myListOfLists, prevTempHeadListPtr->nextList);
					break;
				}
				else
					std::cout << "��������� � ��������� ������� ����������� � ������. ��������� ���� ������ ��������� ��� ������� � ����." << std::endl;
			}
			else
				break;
		}
	}
}
//�������� ���������� �������� ��������� ������ �������.
void removeElemOfList(ListOfLists* f_myListOfLists)
{
	if (isEmptyListOfLists(f_myListOfLists))
		std::cout << "������ ������� ����. �������� �������� �������� �� ��������� ����������." << std::endl;
	else
	{
		printListOfLists(f_myListOfLists);
		std::cout << "������� ����� ������, � ������� ���������� ������� �������, ��� ������� � ����." << std::endl;
		while (true)
		{
			std::string getList_or_exit{ getElem() };
			if (getList_or_exit != "q")
			{
				int get_list{ convertStrToInt(getList_or_exit) };
				List* prevTempHeadListPtr{ checkListExist(f_myListOfLists, get_list) };
				if (prevTempHeadListPtr)
				{
					if (isEmptyList(prevTempHeadListPtr->nextList))
						std::cout << "��������� ����. �������� �������� �������� �� ��������� ����������." << std::endl;
					else
					{
						while (true)
						{
							std::cout << "������� �������, ������� ���������� ������� �� ���������� ������." << std::endl;
							std::string exit_or_fixedElem{ getElem() };
							if (exit_or_fixedElem != "q")
							{
								int fixed_elem{ convertStrToInt(exit_or_fixedElem) };
								Node* ptr_removing_elem = searchElem(prevTempHeadListPtr->nextList, fixed_elem);
								if (ptr_removing_elem != nullptr)
								{
									int rem_data{ ptr_removing_elem->data };
									ptr_removing_elem->prev->next = ptr_removing_elem->next;
									ptr_removing_elem->next->prev = ptr_removing_elem->prev;
									ptr_removing_elem->next = nullptr;
									ptr_removing_elem->prev = nullptr;
									delete ptr_removing_elem;
									prevTempHeadListPtr->nextList->count--;
									std::cout << "������� '" << rem_data << "' ��� ������� ������ �� ������ � �������� '" << prevTempHeadListPtr->nextList->symbolischer_name << "'." << std::endl;
									break;
								}
								else
									std::cout << "��������� ������� ����������� � ���������. ��������� ���� ���������� �������� ��� ������� � ����." << std::endl;
							}
							else
								break;
						}
						break;
					}
				}
				else
					std::cout << "��������� � ��������� ������� ����������� � ������. ��������� ���� ������ ��������� ��� ������� � ����." << std::endl;
			}
			else
				break;
		}
	}
}
//����������� ���� ���������� ������������ ������ ��� ������ ������� � ����.
void clearListOfLists(ListOfLists*& f_myListOfLists)
{
	List* tempHeadListPtr = f_myListOfLists->headListPointer;
	int count_listoflists_elems{ f_myListOfLists->count };
	for (int i{}; i < count_listoflists_elems; i++)
		clearList(f_myListOfLists, f_myListOfLists->headListPointer->nextList);
	delete f_myListOfLists->headListPointer;
	delete f_myListOfLists;
	std::cout << "���������� ������������ ������ ��� ������ ������� ���������� � ����." << std::endl << std::endl;
	std::cout << std::endl << "��� ���������� ������������ ������ ���� ���������� � ����. ���������� ��������� . . ." << std::endl;
}

/*��������������� �������*/
//�������� ������ ������� �� ������� (������� ���� �� ������ ��������-������).
bool isEmptyListOfLists(ListOfLists* f_myListOfLists)
{
	return (f_myListOfLists->count == 0) ? true : false;
}
//�������� ������ �� ������� (������� ���� �� ������ ��������).
bool isEmptyList(List* f_list)
{
	return ((f_list->headPointer->next == f_list->headPointer) && (f_list->headPointer->prev == f_list->headPointer)) ? true : false;
}
//����������� ���������� ������������ ������ ��� ��������� � ����.
void clearList(ListOfLists* f_myListOfLists, List* f_list)
{
	int list_name{ f_list->symbolischer_name };
	List* tempHeadListPtr{ checkListExist(f_myListOfLists, list_name) };
	while (f_list->count >= 0)
	{
		Node* tempPtr = f_list->headPointer->next;
		f_list->headPointer->next->prev = f_list->headPointer->prev;
		f_list->headPointer->prev->next = f_list->headPointer->next;
		f_list->headPointer->next = nullptr;
		f_list->headPointer->prev = nullptr;
		delete f_list->headPointer;
		f_list->headPointer = tempPtr;
		f_list->count--;
	}
	tempHeadListPtr->nextList = f_list->nextList;
	f_list->nextList = nullptr;
	f_list->headPointer = nullptr;
	delete f_list;
	f_myListOfLists->count--;
	std::cout << "���������� ������ ��� ������ � ������� " << list_name << " ���� ����������� � ����." << std::endl;
}
//����� �������� � ��������� ��������� ���������.
Node* searchElem(List* specified_list, const int& searching_elem)
{
	Node* tempHeadPtr = specified_list->headPointer;
	for (int i{}; i < specified_list->count; i++)
	{
		tempHeadPtr = tempHeadPtr->next;
		if (tempHeadPtr->data == searching_elem)
			return tempHeadPtr;
	}
	return nullptr;
}
//�������� �������������� ������ ������ ������ �������.
List* checkListExist(ListOfLists* f_myListOfLists, const int& number_list)
{
	List* prevTempHeadListPtr = f_myListOfLists->headListPointer;
	for (int i{}; i < f_myListOfLists->count; i++)
	{
		if (prevTempHeadListPtr->nextList->symbolischer_name == number_list)
			return prevTempHeadListPtr;
		prevTempHeadListPtr = prevTempHeadListPtr->nextList;
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
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << "\t" << std::endl;
}