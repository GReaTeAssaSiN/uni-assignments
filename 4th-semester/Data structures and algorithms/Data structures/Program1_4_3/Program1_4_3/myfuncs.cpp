#include <iostream>
#include <string>
#include "myfuncs.h"
#include "mystruct.h"

/*ФУНКЦИИ ДЛЯ ПРОВЕРКИ ПОЛЗОВАТЕЛЬСКОГО ВВОДА*/
//Проверка введённой пользователем строки на возможность преобразования в целое число.
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
//Преобразование введённой пользователем строки в число.
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

/*ПОЛЬЗОВАТЕЛЬСКОЕ МЕНЮ*/
//Пользовательское меню.
void MenuForChoices()
{
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1) Полный проход по всей структуре с выводом всех элементов." << std::endl <<
		"2) Поиск заданного элемента во всей структуре." << std::endl <<
		"3) Добавление нового связанного списка в список ДО указанного элемента." << std::endl <<
		"4) Добавление нового связанного списка в список ПОСЛЕ указанного элемента." << std::endl <<
		"5) Добавление нового элемента в указанный связанный список ДО указанного элемента." << std::endl <<
		"6) Добавление нового элемента в указанный связанный список ПОСЛЕ указанного элемента." << std::endl <<
		"7) Удаление элемента из указанного связанного списка родительского списка." << std::endl <<
		"8) Удаление указанного связанного списка из родительского списка." << std::endl <<
		"9) Выход." << std::endl;
}
//Запрос дейтсвий со структурой у пользователя.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8" || choice == "9")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 9). Повторите ввод:" << std::endl;
		}
	}
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Вывод информационных частей элементов связанных списков структуры на консоль.
void printListOfLists(ListOfLists* f_myListOfLists)
{
	if (isEmptyListOfLists(f_myListOfLists))
		std::cout << "Список списков пуст." << std::endl;
	else
	{
		List* tempHeadListPtr = f_myListOfLists->headListPointer;
		std::cout << "Текущее состояние списка списков: " << std::endl;
		for (int i{}; i < f_myListOfLists->count; i++)
		{
			tempHeadListPtr = tempHeadListPtr->nextList;
			std::cout << i + 1 << "-ый(-ой, -ий) подсписок списка списков с номером " << tempHeadListPtr->symbolischer_name << ":" << std::endl;
			Node* tempHeadPtr = tempHeadListPtr->headPointer;
			if (tempHeadListPtr->count == 0)
				std::cout << "\tПодсписок пуст." << std::endl;
			else
			{
				for (int j{}; j < tempHeadListPtr->count; j++)
				{
					tempHeadPtr = tempHeadPtr->next;
					std::cout << "\t" << j + 1 << "-ый(-ой,-ий) элемент списка:\t" << tempHeadPtr->data << std::endl;
				}
			}
			std::cout << std::endl;
		}
	}
}
//Поиск заданного элемента в списке списков.
void searchListOfLists(ListOfLists* f_myListOfLists)
{
	if (isEmptyListOfLists(f_myListOfLists))
		std::cout << "Список списков пуст. Операция поиска элемента в структуре невозможна." << std::endl;
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
					std::cout << i + 1 << "-ый(-ой, -ий) подсписок списка списков с номером " << tempHeadListPtr->symbolischer_name << ":" << std::endl;
					for (int j{}; j < tempHeadListPtr->count; j++)
					{
						tempHeadPtr = tempHeadPtr->next;
						if (tempHeadPtr->data == searching_elem)
						{
							searched_elems++;
							std::cout << "\t" << j + 1 << "-ый(-ой,-ий) элемент списка:\t" << tempHeadPtr->data << std::endl;
						}
					}
					std::cout << std::endl;
					if (searched_elems != 0)
						std::cout << "\tВсего было найдено " << searched_elems << " элемент(-а,-ов) в подсписке." << std::endl;
					else
						std::cout << "\tУказанный элемент отсутствует в подсписке." << std::endl;
					std::cout << std::endl;
					total_searched_elems += searched_elems;
				}
				if (total_searched_elems != 0)
				{
					std::cout << "Всего было найдено " << total_searched_elems << " элемент(-а,-ов) в списке списков." << std::endl;
					break;
				}
				else
					std::cout << "Указанный элемент отсутствует в структуре списка списков. Повторите ввод искомого элемента или выйдите в меню." << std::endl;
			}
			else
				break;
		}
	}
}
//Добавление нового элемента-списка в список списков.
void addNewElemToListOfLists(ListOfLists*& f_myListOfLists, const int& before_or_after)
{
	if (isEmptyListOfLists(f_myListOfLists))
	{
		std::cout << "Список списков пуст. Задайте номер списка, который необходимо добавить, или выйдите в меню." << std::endl;
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
				std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
				clearListOfLists(f_myListOfLists);
				exit(-1);
			}
		}
	}
	else
	{
		std::cout << "Задайте номер списка, который необходимо добавить, или выйдите в меню." << std::endl;
		std::string exit_or_newList{ getElem() };
		if (exit_or_newList != "q")
		{
			int new_list{ convertStrToInt(exit_or_newList) };
			if (before_or_after == 3)
				std::cout << "Задайте номер списка, перед которым необходимо добавить новый, или выйдите в меню." << std::endl;
			else
				std::cout << "Задайте номер списка, после которого необходимо добавить новый, или выйдите в меню." << std::endl;
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
							std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
							clearListOfLists(f_myListOfLists);
							exit(-1);
						}
						break;
					}
					else
						std::cout << "Подсписок с указанным номером отсутствует в списке списков. Повторите ввод номера списка или выйдите в меню." << std::endl;
				}
				else
					break;
			}
		}
	}
}
//Добавление нового элемента в указанный список списка списков ДО/ПОСЛЕ указанного элемента.
void addNewElemToList(ListOfLists*& f_myListOfLists, const int& before_or_after)
{
	if (isEmptyListOfLists(f_myListOfLists))
		std::cout << "Список списков пуст. Операция добавления нового элемента в подсписок списка списков невозможна. Необходимо сначала добавить подсписок в список списков." << std::endl;
	else
	{
		std::cout << "Задайте номер списка, в который необходимо добавить новый элемент, или выйдите в меню." << std::endl;
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
						std::cout << "Указанный список пуст. Задайте элемент, который необходимо добавить, или выйдите в меню." << std::endl;
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
								std::cout << "Элемент '" << new_elem << "' был успешно добавлен в список с номером '" << prevTempHeadListPtr->nextList->symbolischer_name << "'." << std::endl;
							}
							catch (const std::exception& e)
							{
								std::cout << e.what() << std::endl;
								std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
								clearListOfLists(f_myListOfLists);
								exit(-1);
							}
						}
						break;
					}
					else
					{
						std::cout << "Задайте элемент, который необходимо добавить, или выйдите в меню." << std::endl;
						std::string newElem_or_exit{ getElem() };
						if (newElem_or_exit != "q")
						{
							int new_elem{ convertStrToInt(newElem_or_exit) };
							if (before_or_after == 5)
								std::cout << "Задайте элемент подсписка, перед которым необходимо добавить новый, или выйдите в меню." << std::endl;
							else
								std::cout << "Задайте элемент подсписка, после которого необходимо добавить новый, или выйдите в меню." << std::endl;
							while (true)
							{
								std::string exit_or_specifiedElement{ getElem() };
								if (exit_or_specifiedElement != "q")
								{
									int specified_elem{ convertStrToInt(exit_or_specifiedElement) };
									Node* specified_node = searchElem(prevTempHeadListPtr->nextList, specified_elem);
									if (specified_node == nullptr)
										std::cout << "Указанный элемент отсутствует в списке. Повторите ввод элемента списка или выйдите в меню." << std::endl;
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
											std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
											clearListOfLists(f_myListOfLists);
											exit(-1);
										}
										if (before_or_after == 5)
											std::cout << "Новый элемент '" << new_elem << "' был успешно добавлен перед элементом '" << specified_elem << "' в подсписок с номером '" << prevTempHeadListPtr->nextList->symbolischer_name << "'." << std::endl;
										else
											std::cout << "Новый элемент '" << new_elem << "' был успешно добавлен после элемента '" << specified_elem << "' в подсписок с номером '" << prevTempHeadListPtr->nextList->symbolischer_name << "'." << std::endl;
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
					std::cout << "Подсписок с указанным номером отсутствует в списке. Повторите ввод номера подсписка или выйдите в меню." << std::endl;
			}
			else
				break;
		}
	}
}
//Удаление указанного элемента-списка из списка списков.
void removeList(ListOfLists*& f_myListOfLists)
{
	if (isEmptyListOfLists(f_myListOfLists))
		std::cout << "Список списков пуст. Операция удаления элемента-списка из списка списков невозможна." << std::endl;
	else
	{
		std::cout << "Задайте номер списка, который необходимо удалить, или выйдите в меню." << std::endl;
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
					std::cout << "Подсписок с указанным номером отсутствует в списке. Повторите ввод номера подсписка или выйдите в меню." << std::endl;
			}
			else
				break;
		}
	}
}
//Удаление указанного элемента подсписка списка списков.
void removeElemOfList(ListOfLists* f_myListOfLists)
{
	if (isEmptyListOfLists(f_myListOfLists))
		std::cout << "Список списков пуст. Операция удаления элемента из подсписка невозможна." << std::endl;
	else
	{
		printListOfLists(f_myListOfLists);
		std::cout << "Задайте номер списка, в котором необходимо удалить элемент, или выйдите в меню." << std::endl;
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
						std::cout << "Подсписок пуст. Операция удаления элемента из подсписка невозможна." << std::endl;
					else
					{
						while (true)
						{
							std::cout << "Введите элемент, который необходимо удалить из указанного списка." << std::endl;
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
									std::cout << "Элемент '" << rem_data << "' был успешно удален из списка с номермом '" << prevTempHeadListPtr->nextList->symbolischer_name << "'." << std::endl;
									break;
								}
								else
									std::cout << "Указанный элемент отсутствует в подсписке. Повторите ввод удаляемого элемента или выйдите в меню." << std::endl;
							}
							else
								break;
						}
						break;
					}
				}
				else
					std::cout << "Подсписок с указанным номером отсутствует в списке. Повторите ввод номера подсписка или выйдите в меню." << std::endl;
			}
			else
				break;
		}
	}
}
//Возвращение всей выделенной динамической памяти для списка списков в кучу.
void clearListOfLists(ListOfLists*& f_myListOfLists)
{
	List* tempHeadListPtr = f_myListOfLists->headListPointer;
	int count_listoflists_elems{ f_myListOfLists->count };
	for (int i{}; i < count_listoflists_elems; i++)
		clearList(f_myListOfLists, f_myListOfLists->headListPointer->nextList);
	delete f_myListOfLists->headListPointer;
	delete f_myListOfLists;
	std::cout << "Выделенная динамическая память для списка списков возвращена в кучу." << std::endl << std::endl;
	std::cout << std::endl << "Вся выделенная динамическая память была возвращена в кучу. Завершение программы . . ." << std::endl;
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//Проверка списка списков на пустоту (наличие хотя бы одного элемента-списка).
bool isEmptyListOfLists(ListOfLists* f_myListOfLists)
{
	return (f_myListOfLists->count == 0) ? true : false;
}
//Проверка списка на пустоту (наличие хотя бы одного элемента).
bool isEmptyList(List* f_list)
{
	return ((f_list->headPointer->next == f_list->headPointer) && (f_list->headPointer->prev == f_list->headPointer)) ? true : false;
}
//Возвращение выделенной динамической памяти для подсписка в кучу.
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
	std::cout << "Выделенная память для списка с номером " << list_name << " была возвращаена в кучу." << std::endl;
}
//Поиск элемента в указанном подсписке структуры.
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
//Проверка принадлежности номера списка списку списков.
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
//Запрос иниформационной части элемента у пользователя.
std::string getElem()
{
	std::cout << "Введите информационную часть элемента (целое число) или 'q', чтобы выйти в меню: ";
	while (true)
	{
		std::string new_elem{};
		std::getline(std::cin, new_elem);
		if (checkStrIsNumeric(new_elem) || new_elem == "q")
			return new_elem;
		else
			std::cout << "Ошибка ввода. Вы должны ввести целое число или 'q'. Повторите ввод: ";
	}
}
//Вывод визуального разделения между действиями пользователя в консоль.
void printDashes()
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << "\t" << std::endl;
}