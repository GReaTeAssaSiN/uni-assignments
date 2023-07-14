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
		"3) Добаваить в список заданный элемент." << std::endl <<
		"4) Удалить из списка заданный элемент." << std::endl <<
		"5) Выход." << std::endl;
}
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 5). Повторите ввод:" << std::endl;
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
		for (int i{}; i < f_list.count; i++)
			std::cout << i + 1 << "-ый(-ой,-ий) элемент списка:\t" << f_list.list[i] << std::endl;
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
				for (int i{}; i < f_list.count; i++)
				{
					if (f_list.list[i] == searching_elem)
					{
						searched_elems++;
						std::cout << i + 1 << "-ый элемент списка:\t" << f_list.list[i] << std::endl;
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
//Добавление элемента в список до/после заданного.
void addNewElem(List& f_list)
{
	if (isFullnesList(f_list))
		std::cout << "Список полон. Операция добавления нового элемента невозможна." << std::endl;
	else if (isEmptyList(f_list))
	{
		std::cout << "Список пуст. Задайте элемент, который необходимо добавить, или выйдите в меню." << std::endl;
		std::string exit_or_newElem{ getElem() };
		if (exit_or_newElem != "q")
		{
			int new_elem{ convertStrToInt(exit_or_newElem) };
			f_list.list[f_list.count] = new_elem;
			f_list.count++;
			std::cout << "Элемент '" << new_elem << "' был успешно добавлен в список." << std::endl;
		}
	}
	else
	{
		bool is_max_elem{true};
		std::cout << "Задайте элемент, который необходимо добавить, или выйдите в меню." << std::endl;
		std::string exit_or_newElem{ getElem() };
		if (exit_or_newElem != "q")
		{
			int new_elem{ convertStrToInt(exit_or_newElem) };
			for (int i{}; i < f_list.count; i++)
			{
				if (f_list.list[i] > new_elem)
				{
					for (int j{ f_list.count }; j > i; j--)
						f_list.list[j] = f_list.list[j - 1];
					f_list.list[i] = new_elem;
					f_list.count++;
					is_max_elem = false;
					std::cout << "Новый элемент '" << new_elem << "' был успешно добавлен в список." << std::endl;
					break;
				}
			}
			if (is_max_elem)
			{
				f_list.list[f_list.count] = new_elem;
				f_list.count++;
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
		bool cycle{ true };
		while (cycle)
		{
			std::string exit_or_fixedElem{ getElem() };
			if (exit_or_fixedElem != "q")
			{
				int fixed_elem{ convertStrToInt(exit_or_fixedElem) };
				for (int i{}; i < f_list.count; i++)
				{
					if (f_list.list[i] == fixed_elem)
					{
						f_list.list[i] = 0;
						for (int j{ i }; j < f_list.count - 1; j++)
							f_list.list[j] = f_list.list[j + 1];
						f_list.count--;
						std::cout << "Элемент '" << fixed_elem << "' был успешно удален из списка." << std::endl;
						cycle = false;
						break;
					}
				}
				if (!cycle)
					break;
				std::cout << "Указанный элемент отсутствует в списке." << std::endl;
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