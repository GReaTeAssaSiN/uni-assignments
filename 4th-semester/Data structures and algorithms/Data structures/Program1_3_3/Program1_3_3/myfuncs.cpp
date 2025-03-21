#include <iostream>
#include <string>
#include "myfuncs.h"

/*ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ*/
//Пользовательское меню
void MenuForChoices()
{
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1) Пройтись по списку с выводом на экран информационных частей элементов." << std::endl <<
		"2) Найти в списке элемент(-ы) с заданной информационной частью." << std::endl <<
		"3) Добаваить в список элемент перед заданным." << std::endl <<
		"4) Добавить в список элемент после заданного." << std::endl <<
		"5) Удалить из списка заданный элемент." << std::endl <<
		"6) Выход." << std::endl;
}
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 6). Повторите ввод:" << std::endl;
		}
	}
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Вывод информационных частей элементов списка на консоль.
void printList(const List& f_list)
{
	if (isEmptyList(f_list))
		std::cout << "Список пуст." << std::endl;
	else
	{
		std::cout << "Текущее состояние списка: " << std::endl;
		int ref_current_elem{ f_list.Refs[0] }, count_passed_elems{};
		while (ref_current_elem != -1)
		{
			std::cout << count_passed_elems + 1 << "-ый(-ой, -ий) элемент списка:\t" << f_list.Elems[ref_current_elem] << std::endl;
			ref_current_elem = f_list.Refs[ref_current_elem];
			count_passed_elems++;
		}
	}
}
//Поиск элемента с заданной информационной частью.
void searchList(List& f_list)
{
	if (isEmptyList(f_list))
		std::cout << "Список пуст. Операция поиска элемента невозможна." << std::endl;
	else
	{
		while (true)
		{
			std::string exit_or_searchingElem{ getElem() };
			if (exit_or_searchingElem != "q")
			{
				int searched_elems{}, searching_elem{ convertStrToInt(exit_or_searchingElem) };
				int ref_current_elem{ f_list.Refs[0] }, count_passed_elems{};
				while (ref_current_elem != -1)
				{
					if (f_list.Elems[ref_current_elem] == searching_elem)
					{
						searched_elems++;
						std::cout << count_passed_elems + 1 << "-ый элемент списка:\t" << f_list.Elems[ref_current_elem] << std::endl;
					}
					ref_current_elem = f_list.Refs[ref_current_elem];
					count_passed_elems++;
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
//Добавление элемента в список до/после заданного.
void addNewElem(List& f_list, const int& before_after)
{
	if (isFullnesList(f_list))
		std::cout << "Список полон. Операция добавления нового элемента невозможна." << std::endl;
	else if (isEmptyList(f_list))
	{
		std::cout << "Список пуст. Задайте элемент, который необходимо добавить, или выйдите в меню." << std::endl;
		std::string exit_or_newElem{ getElem() };
		if (exit_or_newElem != "q")
		{
			int newElem{ convertStrToInt(exit_or_newElem) };
			f_list.Elems[f_list.Refs[0]] = newElem;
			f_list.count++;
			std::cout << "Элемент '" << newElem << "' был успешно добавлен в список." << std::endl;
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
					int ref_current_elem{ f_list.Refs[0] };
					while (ref_current_elem != -1)
					{
						if (f_list.Elems[ref_current_elem] == specified_elem)
							break;
						ref_current_elem = f_list.Refs[ref_current_elem];
					}
					if (ref_current_elem == -1)
						std::cout << "Указанный элемент отсутствует в списке. Повторите ввод элемента списка." << std::endl;
					else
					{
						int free_index{};
						bool free_space{ false };
						for (int i{1}; i < size + 1; i++)
							if (f_list.Refs[i] == -1)
							{
								free_space = true;
								for (int j{}; j < size + 1; j++)
								{
									if (f_list.Refs[j] == i)
									{
										free_space = false;
										break;
									}
								}
								if (free_space)
								{
									free_index = i;
									break;
								}
							}
						if (before_after == 4)
							ref_current_elem = f_list.Refs[ref_current_elem];	
						f_list.Elems[free_index] = new_elem;
						f_list.Refs[free_index] = free_index;
						f_list.count++;
						for (int i{}; i < size + 1; i++)
							if ((ref_current_elem != -1 && f_list.Refs[i] == ref_current_elem) || (ref_current_elem == -1 && f_list.Elems[i] == specified_elem))	
							{
								int temp{ ref_current_elem };
								f_list.Refs[i] = free_index;
								f_list.Refs[free_index] = temp;
								break;
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
//Удаление элемента из списка.
void removeElem(List& f_list)
{
	if (isEmptyList(f_list))
		std::cout << "Список пуст. Операция удаления элемента из списка невозможна." << std::endl;
	else
	{
		printList(f_list);
		while (true)
		{
			std::string exit_or_fixedElem{ getElem() };
			if (exit_or_fixedElem != "q")
			{
				int fixed_elem{ convertStrToInt(exit_or_fixedElem) };
				int ref_current_elem{ f_list.Refs[0] };
				while (ref_current_elem != -1)
				{
					if (f_list.Elems[ref_current_elem] == fixed_elem)
					{
						for (int i{}; i < size + 1; i++)
							if (f_list.Refs[i] == ref_current_elem)
							{
								f_list.Elems[ref_current_elem] = 0;
								f_list.Refs[i] = f_list.Refs[ref_current_elem];
								f_list.Refs[ref_current_elem] = -1;
								f_list.count--;
								if (f_list.count == 0)
									f_list.Refs[0] = 1;
								std::cout << "Элемент '" << fixed_elem << "' был успешно удален из списка." << std::endl;
								break;
							}
						break;
					}
					ref_current_elem = f_list.Refs[ref_current_elem];
				}
				if (ref_current_elem != -1)
					break;
				std::cout << "Указанный элемент отсутствует в списке. Повторите ввод удаляемого элемента или выйдите в меню." << std::endl;
			}
			else
				break;
		}
	}
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//Проверка списка на пустоту (наличие хотя бы одного элемента).
bool isEmptyList(const List& f_list)
{
	return (f_list.count == 0) ? true : false;
}
//Проверка списка на заполненность (наличие свободных ячеек для новых элементов).
bool isFullnesList(const List& f_list)
{
	return (f_list.count == size) ? true : false;
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

/*ФУНКЦИИ ДЛЯ ПРОВЕРКИ ПОЛЬЗОВАТЕЛЬСКОГО ВВОДА*/
//Проверка введённой пользователем строки на возможность преобразования в целое неотрицательное число.
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