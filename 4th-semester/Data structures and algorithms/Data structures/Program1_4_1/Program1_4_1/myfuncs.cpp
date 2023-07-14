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
		"1) Пройтись по списку с выводом на экран информационных частей элементов в ПРЯМОМ направлении." << std::endl <<
		"2) Пройтись по списку с выводом на экран информационных частей элементов в ОБРАТНОМ направлении." << std::endl <<
		"3) Поиск элемента с заданной информационной частью в списке в ПРЯМОМ направлении." << std::endl <<
		"4) Поиск элемента с заданной информационной частью в списке в ОБРАТНОМ направлении." << std::endl <<
		"5) Добавить новый элемент в список ПЕРЕД заданным." << std::endl <<
		"6) Добавить новый элемент в список ПОСЛЕ заданного." << std::endl <<
		"7) Удалить заданный элемент из списка." << std::endl <<
		"8) Выход." << std::endl;
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
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 8). Повторите ввод:" << std::endl;
		}
	}
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Вывод информационных частей элементов списка на консоль.
void printList(List* f_myList, const int& direct_or_reverse)
{
	if (isEmptyList(f_myList))
		std::cout << "Список пуст." << std::endl;
	else
	{
		Node* tempPtr = f_myList->listPointer;
		std::cout << "Текущее состояние списка: " << std::endl;
		if (direct_or_reverse == 1)
			for (int i{}; i < f_myList->count; i++)
			{
				tempPtr = tempPtr->next;
				std::cout << i + 1 << "-ый(-ой,-ий) элемент списка:\t" << tempPtr->data << std::endl;
			}
		else
			for (int i{ f_myList->count }; i > 0; i--)
			{
				tempPtr = tempPtr->prev;
				std::cout << i << "-ый(-ой,-ий) элемент списка:\t" << tempPtr->data << std::endl;
			}
	}
}
//Поиск элемента с заданной информационной частью в списке.
void searchList(List* f_myList, const int& direct_or_reverse)
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
				if (direct_or_reverse == 3)
					for (int i{}; i < f_myList->count; i++)
					{
						tempPtr = tempPtr->next;
						if (tempPtr->data == searching_elem)
						{
							searched_elems++;
							std::cout << i + 1 << "-ый(-ой,-ий) элемент списка:\t" << tempPtr->data << std::endl;
						}
					}
				else
					for (int i{ f_myList->count }; i > 0; i--)
					{
						tempPtr = tempPtr->prev;
						if (tempPtr->data == searching_elem)
						{
							searched_elems++;
							std::cout << i << "-ый(-ой,-ий) элемент списка:\t" << tempPtr->data << std::endl;
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
void addNewElem(List*& f_myList, const int& before_after)
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
				new_node->next = f_myList->listPointer;
				new_node->prev = f_myList->listPointer;
				f_myList->listPointer->next = new_node;
				f_myList->listPointer->prev = new_node;
				f_myList->count++;
				std::cout << "Элемент '" << new_elem << "' был успешно добавлен в список." << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
				std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
				clearList(f_myList);
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
					Node* specified_node = searchElem(f_myList, specified_elem);
					if (specified_node == nullptr)
						std::cout << "Указанный элемент отсутствует в списке. Повторите ввод элемента списка или выйдите в меню." << std::endl;
					else
					{
						if (before_after == 5)
						{
							try
							{
								Node* new_node = new Node{};
								new_node->data = new_elem;
								specified_node->prev->next = new_node;
								new_node->next = specified_node;
								new_node->prev = specified_node->prev;
								specified_node->prev = new_node;
								f_myList->count++;
							}
							catch (const std::exception& e)
							{
								std::cout << e.what() << std::endl;
								std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
								clearList(f_myList);
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
								new_node->prev = specified_node;
								specified_node->next->prev = new_node;
								specified_node->next = new_node;
								f_myList->count++;
							}
							catch (const std::exception& e)
							{
								std::cout << e.what() << std::endl;
								std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
								clearList(f_myList);
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
void clearList(List*& f_myList)
{
	while (f_myList->count >= 0)
	{
		Node* tempPtr = f_myList->listPointer->next;
		f_myList->listPointer->next->prev = f_myList->listPointer->prev;
		f_myList->listPointer->prev->next = f_myList->listPointer->next;
		f_myList->listPointer->next = nullptr;
		f_myList->listPointer->prev = nullptr;
		delete f_myList->listPointer;
		f_myList->listPointer = tempPtr;
		f_myList->count--;
	}
	delete f_myList;
	std::cout << std::endl << "Вся выделенная память была возвращена в кучу. Завершение программы . . ." << std::endl;
}
//Удаление элемента из основного списка с добавлением удаляемого элемента во вспомогательный список.
void removeElem(List*& f_myList)
{
	if (isEmptyList(f_myList))
		std::cout << "Список пуст. Операция удаления элемента из списка невозможна." << std::endl;
	else
	{
		printList(f_myList, 1);
		while (true)
		{
			std::string exit_or_fixedElem{ getElem() };
			if (exit_or_fixedElem != "q")
			{
				int fixed_elem{ convertStrToInt(exit_or_fixedElem) };
				Node* ptr_removing_elem = searchElem(f_myList, fixed_elem);
				if (ptr_removing_elem != nullptr)
				{
					int rem_data{ ptr_removing_elem->data };
					ptr_removing_elem->prev->next = ptr_removing_elem->next;
					ptr_removing_elem->next->prev = ptr_removing_elem->prev;
					ptr_removing_elem->next = nullptr;
					ptr_removing_elem->prev = nullptr;
					delete ptr_removing_elem;
					f_myList->count--;
					std::cout << "Элемент '" << rem_data << "' был успешно удален из списка." << std::endl;
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
	return ((f_myList->listPointer->next == f_myList->listPointer) && (f_myList->listPointer->prev == f_myList->listPointer)) ? true : false;
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