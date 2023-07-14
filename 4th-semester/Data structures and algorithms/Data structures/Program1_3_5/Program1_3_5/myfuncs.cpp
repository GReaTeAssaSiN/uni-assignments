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
		"1) Пройтись по основному списку с выводом на экран информационных частей элементов." << std::endl <<
		"2) Поиск элемента с заданной информационной частью в основном списке." << std::endl <<
		"3) В основной список добавить новый элемент перед заданным." << std::endl <<
		"4) В основной список добавить новый элемент после заданного." << std::endl <<
		"5) Удалить заданный элемент из основного списка с добавлением этого элемента во вспомогательный список." << std::endl <<
		"6) Вывод текущего состояния вспомогательного списка на экран." << std::endl <<
		"7) Выход." << std::endl;
}
//Запрос дейтсвий со списком у пользователя.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 7). Повторите ввод:" << std::endl;
		}
	}
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Вывод информационных частей элементов списка на консоль.
void printList(List* f_myList)
{
	if (isEmptyList(f_myList))
		std::cout << "Список пуст." << std::endl;
	else
	{
		Node* tempPtr = f_myList->listPointer;
		std::cout << "Текущее состояние списка: " << std::endl;
		for (int i{}; i < f_myList->count; i++)
		{
			tempPtr = tempPtr->next;
			std::cout << i + 1 << "-ый(-ой,-ий) элемент списка:\t" << tempPtr->data << std::endl;
		}
	}
}
//Поиск элемента с заданной информационной частью в основном списке.
void searchList(List* f_myList)
{
	if (isEmptyList(f_myList))
		std::cout << "Список пуст. Операция поиска элемента невозможна." << std::endl;
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
						std::cout << i + 1 << "-ый(-ой,-ий) элемент списка:\t" << tempPtr->data << std::endl;
					}
				}
				if (searched_elems != 0)
				{
					std::cout << "Всего было найдено " << searched_elems << " элемент(-а,-ов)." << std::endl;
					break;
				}
				else
					std::cout << "Указанный элемент отсутствует в списке." << std::endl;
			}
			else
				break;
		}
	}
}
//Добавление элемента до/после заданного в основном списке.
void addNewElem(List*& f_myList, List*& f_auxiliary_myList, const int& before_after)
{
	if (isEmptyList(f_myList))
	{
		std::cout << "Список пуст. Задайте элемент, который необходимо добавить, или выйдите в меню." << std::endl;
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
				std::cout << "Элемент '" << new_elem << "' был успешно добавлен в список." << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
				std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
				clearList(f_myList, f_auxiliary_myList);
				exit(-1);
			}
		}
	}
	else
	{
		std::cout << "Задайте элемент, который необходимо добавить, или выйдите в меню." << std::endl;
		std::string newElem_or_exit{ getElem() };
		if (newElem_or_exit != "q")
		{
			int new_elem{ convertStrToInt(newElem_or_exit) };
			if (before_after == 3)
				std::cout << "Задайте элемент, перед которым необходимо добавить новый, или выйдите в меню." << std::endl;
			else
				std::cout << "Задайте элемент, после которого необходимо добавить новый, или выйдите в меню." << std::endl;
			while (true)
			{
				std::string exit_or_specifiedElement{ getElem() };
				if (exit_or_specifiedElement != "q")
				{
					int specified_elem{ convertStrToInt(exit_or_specifiedElement) };
					Node* tempPtr = f_myList->listPointer, * specified_node = searchElem(f_myList, specified_elem);
					if (specified_node == nullptr)
						std::cout << "Указанный элемент отсутствует в списке. Повторите ввод элемента списка или выйдите в меню." << std::endl;
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
								std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
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
								std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
								clearList(f_myList, f_auxiliary_myList);
								exit(-1);
							}
						}
						if (before_after == 3)
							std::cout << "Новый элемент '" << new_elem << "' был успешно добавлен перед элементом '" << specified_elem << "'." << std::endl;
						else
							std::cout << "Новый элемент '" << new_elem << "' был успешно добавлен после элемента '" << specified_elem << "'." << std::endl;
						break;
					}
				}
				else
					break;
			}
		}
	}
}
//Возвращение всей выделенной динамической памяти в кучу.
void clearList(List*& f_myList, List*& f_auxiliary_myList)
{
	clear(f_myList);
	clear(f_auxiliary_myList);
	std::cout << std::endl << "Вся выделенная память была возвращена в кучу. Завершение программы . . ." << std::endl;
}
//Удаление элемента из основного списка с добавлением удаляемого элемента во вспомогательный список.
void removeElem(List*& f_myList, List*& f_auxiliary_myList)
{
	if (isEmptyList(f_myList))
		std::cout << "Список пуст. Операция удаления элемента из списка невозможна." << std::endl;
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
					std::cout << "Элемент '" << ptr_removing_elem->data << "' был успешно удален из основного списка и добавлен во вспомогательный список (стек)." << std::endl;
					break;
				}
				else
					std::cout << "Указанный элемент отсутствует в списке. Повторите ввод удаляемого элемента или выйдите в меню." << std::endl;
			}
			else
				break;
		}
	}
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//Проверка списка на пустоту (наличие хотя бы одного элемента)
bool isEmptyList(List* f_myList)
{
	return (f_myList->listPointer->next == nullptr) ? true : false;
}
//Возвращение всей выделенной динамической памяти для данного списка в кучу.
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
//Поиск элемента с заданной информационной частью в основном списке и возвращение указателя на его "узел" (Node*).
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
	std::cout << "---------------------------------------------------------------------------------------------------------------" << "\t" << std::endl;
}