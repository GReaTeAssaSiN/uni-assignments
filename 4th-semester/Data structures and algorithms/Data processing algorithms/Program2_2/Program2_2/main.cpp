#include <iostream>
#include <cstdlib> //для функций rand() и srand()
#include <ctime> //для функции time()
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//Привзяка ГПСЧ к календарному времени (случайные последовательности случайных чисел из диапазона).
	srand(static_cast<unsigned int>(time(0)));
	//Задание массива и его заполнение.
	DynamicArray numbers{};
	generateArray(numbers);
	printDashes();
	//Цикл обработки пользовательского ввода.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			regenerateArray(numbers);
			break;
		case '2':
			sortSelectionAndRuntimeCalculation(numbers, 1);
			break;
		case '3':
			sortSelectionAndRuntimeCalculation(numbers, 2);
			break;
		case '4':
			sortSelectionAndRuntimeCalculation(numbers, 3);
			break;
		case '5':
			sortSelectionAndRuntimeCalculation(numbers, 4);
			break;
		case '6':
			sortSelectionAndRuntimeCalculation(numbers, 5);
			break;
		case '7':
			sortSelectionAndRuntimeCalculation(numbers, 6);
			break;
		case '8':
			std::cout << "Исходное состояние массива (вывод по 10 элементов в строке):" << std::endl;
			printArray(numbers);
			break;
		case '9':
			cycle = false;
			clear(numbers);
			std::cout << "Завершение программы . . ." << std::endl;
			break;
		default:;
		}
		printDashes();
	}
	return 0;
}