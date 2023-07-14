#include <iostream>
#include <string>
#include "myfuncs.h"

/*ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ*/
//Пользовательское меню
void MenuForChoices()
{
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1) Проверить пустоту очереди." << std::endl <<
		"2) Проверить заполненность очереди." << std::endl <<
		"3) Добаваить элемент в конец очереди." << std::endl <<
		"4) Удалить элемент из начала очереди." << std::endl <<
		"5) Вывод текущего состояния очереди на экран." << std::endl <<
		"6) Выход." << std::endl;
}
//Запрос дейтсвий с очередью у пользователя
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
//Проверка очереди на пустоту
bool isEmptyQueue(const Queue& f_queue)
{
	return (f_queue.frnt == -1) ? true : false;
}
//Проверка очереди на заполненность
bool isFullnessQueue(const Queue& f_queue)
{
	return ((f_queue.frnt == 0) && (f_queue.rear == sizeQueue - 1) || (f_queue.frnt == f_queue.rear + 1)) ? true : false;
}
//Добавление элемента в очередь
void enQueue(Queue& f_queue)
{
	if (isFullnessQueue(f_queue))
		std::cout << "Очередь заполнена. Добавление нового элемента в очередь невозможно." << std::endl;
	else
	{
		if (f_queue.frnt == -1)
			f_queue.frnt = 0;
		f_queue.rear = (f_queue.rear + 1) % sizeQueue;
		std::cout << "Введите новый элемент (целое число), который хотите добавить в очередь: ";
		std::string newElem{};
		while (true)
		{
			std::getline(std::cin, newElem);
			if (checkStrIsNumeric(newElem))
			{
				f_queue.queue[f_queue.rear] = convertStrToInt(newElem);
				std::cout << "Новый элемент успешно добавлен в очередь." << std::endl;
				break;
			}
			else
			{
				std::cout << "Ошибка ввода. Вы должны ввести целое число. Повторите ввод: " << std::endl;
			}
		}
	}
}
//Удаление элемента из очереди
void deQueue(Queue& f_queue)
{
	if (isEmptyQueue(f_queue))
	{
		std::cout << "Очередь пуста, операция удаления элемента из очереди невозможна." << std::endl;
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
		std::cout << "Элемент " << item << " из очереди успешно удален." << std::endl;
	}
}
//Вывод текущего состояния очереди на экран
void printQueue(const Queue& f_queue)
{
	if (isEmptyQueue(f_queue))
		std::cout << "Очередь пуста." << std::endl;
	else
	{
		std::cout << "Указатель frnt -> " << f_queue.frnt << std::endl;
		std::cout << "Указатель rear -> " << f_queue.rear << std::endl;
		std::cout << "Текущее состояние очереди: " << std::endl;
		for (int i{ f_queue.frnt }; i != f_queue.rear; i = (i + 1) % sizeQueue)
			std::cout << f_queue.queue[i] << " ";
		std::cout << f_queue.queue[f_queue.rear % sizeQueue] << std::endl;
	}
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
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