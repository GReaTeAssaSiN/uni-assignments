#include <iostream>
#include <string> //для строгой обработки пользовательского ввода
#include <cstdlib> //для функций rand() и srand()
#include <ctime> //для функции time()
#include <stdlib.h> //для функции exit()
#include "myfuncs.h"
#include "mystruct.h"

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
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
//ГПСЧ
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}
//Выбор между основным(0)/вспомогательным(1) стеком.
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
			std::cout << "Ошибка ввода. Введите 0 или 1: \n";
		}
	}
}

/*ПОЛЬЗОВАТЕЛЬСКОЕ МЕНЮ*/
//Пользовательское меню.
void MenuForChoices()
{
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1) Проверить пустоту основного стека." << std::endl <<
		"2) Добавить элемент в вершину основного стека." << std::endl <<
		"3) Добавить несколько новых значений (элементов) в вершину основного стека." << std::endl <<
		"4) Удалить элемент из вершины основного стека." << std::endl <<
		"5) Вывод текущего состояния основного стека на экран." << std::endl <<
		"6) Вывод текущего состояния вспомогательного стека на экран." << std::endl <<
		"7) Выход." << std::endl;
}
//Запрос дейтсвий со стеком у пользователя.
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

/*ОСНОВНЫЕ ФУНКЦИИ РАБОТЫ СО СТЕКОМ*/
//Проверка стека на пустоту.
bool isEmpty(Stack* stack)
{
	return stack->sp == nullptr ? true : false;
}
//Добавление элемента в вершину стека.
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
		std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
		clear(stack);
		exit(-1);
	}
}
//Передача элемента из вершины одного стека в вершину другого стека.
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
//Удаление элемента из вершины стека.
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
//Вывод текущего состояния стека на экран.
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
//Очистка выделенной памяти для стека.
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

/*ОСНОВНЫЕ ФУНКЦИИ РАБОТЫ СО СТЕКОМ И ВЫВОДОМ СООБЩЕНИЙ ДЛЯ ПОЛЬЗОВАТЕЛЯ*/
//Добавление элемента (нового/из вспомогательного стека) в вершину основного стека.
void user_push(Stack* baseStack, Stack* auxiliaryStack)
{
	std::cout << "Вы хотите добавить новый элемент(0) или вернуть элемент с вершины вспомогательного стека(1): ";
	unsigned char base_auxiliary{ get_0_1() };
	if (base_auxiliary == '0' || (base_auxiliary == '1' && !pass(auxiliaryStack, baseStack)))
	{
		if (base_auxiliary == '1')
			std::cout << "Вспомогательный стек пуст на данный момент. Воспользуйтесь основным стеком." << std::endl;
		std::cout << "Введите новый элемент (целое число), который хотите добавить в вершину стека: ";
		std::string newElem{};
		while (true)
		{
			std::getline(std::cin, newElem);
			if (checkStrIsNumeric(newElem))
			{
				push(baseStack, convertStrToInt(newElem));
				std::cout << "Новый элемент успешно добавлен в вершину стека." << std::endl;
				break;
			}
			else
			{
				std::cout << "Ошибка ввода. Вы должны ввести целое число. Повторите ввод: " << std::endl;
			}
		}
	}
	else
	{
		pass(auxiliaryStack, baseStack);
		std::cout << "Из вершины вспомогательного стека успешно добавлен элемент в вершину основного стека." << std::endl;
	}
}
//Добавление произвольного количества случайных элементов в вершину основного стека.
void user_push_random(Stack* baseStack)
{
	//Привзяка ГПСЧ к календарному времени (случайные последовательности случайных чисел из диапазона).
	srand(static_cast<unsigned int>(time(0)));
	std::cout << "Введите количество значений (элементов), которое хотите занести в стек: ";
	std::string count{};
	while (true)
	{
		std::getline(std::cin, count);
		if (checkStrIsNumeric(count) && convertStrToInt(count) >= 0)
		{
			int count_new_elems{ convertStrToInt(count) };
			for (int i{}; i < count_new_elems; i++)
				push(baseStack, static_cast<int>(getRandomNumber(-1000, 1000)));
			std::cout << "Все новые элементы (" << count_new_elems << ") были успешно занесены в стек." << std::endl;
			break;
		}
		else
		{
			std::cout << "Ошибка ввода. Вы должны ввести целое неотрицательное число. Повторите ввод: " << std::endl;
		}
	}
}
//Удаление элемента (окончательно/с занесением во вспомогательный стек) из вершины основного стека.
void user_pop(Stack* baseStack, Stack* auxiliaryStack)
{
	if (isEmpty(baseStack))
		std::cout << "Стек пуст, операция удаления элемента из вершины стека невозможна." << std::endl;
	else
	{
		std::cout << "Вы хотите безвозвратно удалить элемент с освобождением памяти под него(0) или включить его в вершину вспомогательного стека удаленных элементов(1): ";
		unsigned char base_auxiliary{ get_0_1() };
		if (base_auxiliary == '0')
		{
			pop(baseStack);
			std::cout << "Элемент из вершины стека успешно удален." << std::endl;
		}
		else
		{
			if (pass(baseStack, auxiliaryStack))
				std::cout << "Элемент из вершины основного стека успешно включен в вершину вспомогательного стека удаленных элементов." << std::endl;
		}
	}
}
//Вывод текущего состояния стеков на экран.
void user_printBaseStack(Stack* baseStack)
{
	if (isEmpty(baseStack))
		std::cout << "Основной стек пуст." << std::endl;
	else
	{
		std::cout << "Текущее состояние основного стека: " << std::endl;
		print(baseStack);
	}
}
void user_printAuxiliaryStack(Stack* auxiliaryStack)
{
	if (isEmpty(auxiliaryStack))
		std::cout << "Вспомогательный стек пуст." << std::endl;
	else
	{
		std::cout << "Текущее состояние вспомогательного стека: " << std::endl;
		print(auxiliaryStack);
	}
}
//Очистка выделенной памяти для стеков
void user_clear(Stack*& baseStack, Stack*& auxiliaryStack)
{
	clear(baseStack);
	clear(auxiliaryStack);
	std::cout << std::endl << "Вся выделенная память была возвращена в кучу. Завершение программы . . ." << std::endl;
}