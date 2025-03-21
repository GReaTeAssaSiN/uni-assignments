#include <iostream>
#include <string>
#include "myfuncs.h"

/*ПОЛЬЗОВАТЕЛЬСКОЕ МЕНЮ*/
//Пользовательское меню.
void MenuForChoices()
{
	std::cout << "Что вы хотите сделать?" << std::endl <<
		"1) Удалить старый массив и заполнить новый с заданным числом элементов." << std::endl <<
		"2) Сортировка массива обменом (метод пузырька)." << std::endl <<
		"3) Сортировка массива выбором." << std::endl <<
		"4) Сортировка массива вставками." << std::endl <<
		"5) Вывод текущего состояния массива на экран." << std::endl <<
		"6) Выход." << std::endl;
}
//Запрос действий с двоичным деревом у пользователя.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6")
			return choice[0];
		else
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 6). Повторите ввод:" << std::endl;
	}
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//ГПСЧ
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}
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
//Вывод визуального разделения между действиями пользователя в консоль.
void printDashes()
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << "\t" << std::endl;
}
//Копирование массива в структуре DynamicArray при передаче структуры копированием в функцию.
int*& copyMyArray(DynamicArray& numbers)
{
	try
	{
		int* copy_numbers = new int[numbers.count] {};
		for (int i{}; i < numbers.count; i++)
			copy_numbers[i] = numbers.myArray[i];
		return copy_numbers;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
		clear_copy(numbers);
		exit(-1);
	}
}
//Очистка скопированного массива.
void clear_copy(DynamicArray& numbers)
{
	delete[] numbers.myArray;
	numbers.myArray = nullptr;
	numbers.count = 0;
	std::cout << "Массив, скопированный при передаче в функцию структуры копированием, успешно очищен." << std::endl <<
		"Вся выделенная динамическая память для него была возвращена в кучу." << std::endl;
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Проверка массива на пустоту.
bool isEmpty(const DynamicArray& numbers)
{
	return (numbers.myArray == nullptr) ? true : false;
}
//Заполнение массива.
void generateArray(DynamicArray& numbers)
{
	std::cout << "Введите количество элементов массива: ";
	while (true)
	{
		std::string str_count_elems{};
		std::getline(std::cin, str_count_elems);
		if (checkStrIsNumeric(str_count_elems) && 0 < convertStrToInt(str_count_elems) && convertStrToInt(str_count_elems) <= 10000)
		{
			numbers.count = convertStrToInt(str_count_elems);
			numbers.myArray = new int[numbers.count] {};
			for (int i{}; i < numbers.count; i++)
				numbers.myArray[i] = static_cast<int>(getRandomNumber(-1000, 1000));
			std::cout << "Массив с количеством элементов " << numbers.count << " был успешно создан и заполнен случайными числами от -1000 до 1000." << std::endl;
			break;
		}
		else
			std::cout << "Ошибка ввода. Вы должны ввести целое положительное число (не более 10000). Повторите ввод: " << std::endl;
	}
}
//Перезаполнение массива.
void regenerateArray(DynamicArray& numbers)
{
	std::cout << "Введите количество элементов нового массива или 'q', чтобы выйти в меню: ";
	while (true)
	{
		std::string new_count_elems_or_exit{};
		std::getline(std::cin, new_count_elems_or_exit);
		if (new_count_elems_or_exit != "q")
		{
			if (checkStrIsNumeric(new_count_elems_or_exit) && 0 < convertStrToInt(new_count_elems_or_exit) && convertStrToInt(new_count_elems_or_exit) <= 10000)
			{
				clear(numbers);
				numbers.count = convertStrToInt(new_count_elems_or_exit);
				numbers.myArray = new int[numbers.count] {};
				for (int i{}; i < numbers.count; i++)
					numbers.myArray[i] = static_cast<int>(getRandomNumber(-1000, 1000));
				std::cout << "Новый массив с количеством элементов " << numbers.count << " успешно создан и заполнен случайными числами от -1000 до 1000." << std::endl;
				break;
			}
			else
				std::cout << "Ошибка ввода. Вы должны ввести целое положительное число (не более 10000) или 'q'. Повторите ввод: " << std::endl;
		}
		else
			break;
	}
}
//Сортировка обменом (метод пузырька). Сложность O(n^2).
void bubbleSorting(DynamicArray numbers)
{
	int* copy_my_array{ copyMyArray(numbers) };
	numbers.myArray = copy_my_array;
	int number_of_comparisons{};
	int number_of_assignments{};
	//Переменная для вычисления прошедшего времени в секундах.
	double time_spent = 0.0;
	//Переменная для хранения начального времени выполнения кода.
	clock_t start_time = clock();
	/*НАЧАЛО СОРТИРОВКИ*/
	for (int i{}; i < numbers.count - 1; i++)
		for (int j{}; j < numbers.count - i - 1; j++)//Сравнивание сортируемого элемента со следующими неотсортированными.
		{
			number_of_comparisons++;
			if (numbers.myArray[j] > numbers.myArray[j + 1])//Если сортируемый элемент не минимальный, то путем 3-х пересылок "подымаем" его выше.
			{
				number_of_assignments += 3;
				int temp = numbers.myArray[j];
				numbers.myArray[j] = numbers.myArray[j + 1];
				numbers.myArray[j + 1] = temp;
			}
		}
	/*КОНЕЦ СОРТИРОВКИ*/
	//Переменная для конечного времени выполнения кода.
	clock_t end_time = clock();
	time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	std::cout << "Сортировка массива обменом (методом пузырька) успешно завершена." << std::endl << std::endl;
	std::cout << "Отсортированный массив (вывод по 10 элементов в строке):" << std::endl;
	printArray(numbers);
	std::cout << "Время выполнения сортировки: " << time_spent << " сек." << std::endl;
	std::cout << "Число произведенных сравнений: " << number_of_comparisons << std::endl <<
		"Число произведенных пересылок: " << number_of_assignments << std::endl << std::endl;
	clear_copy(numbers);
}
//Сортировка выбором. Сложность O(n^2).
void selectionSorting(DynamicArray numbers)
{
	int* copy_my_array{ copyMyArray(numbers) };
	numbers.myArray = copy_my_array;
	int number_of_comparisons{};
	int number_of_assignments{};
	//Переменная для вычисления прошедшего времени в секундах.
	double time_spent = 0.0;
	//Переменная для хранения начального времени выполнения кода.
	clock_t start_time = clock();
	/*НАЧАЛО СОРТИРОВКИ*/
	for (int i{}; i < numbers.count - 1; i++)
	{
		int index_of_min_elem{ i };
		for (int j{ i + 1 }; j < numbers.count; j++)//Поиск минимального элемента среди неотсортированных путем сравнений.
		{
			number_of_comparisons++;
			if (numbers.myArray[j] < numbers.myArray[index_of_min_elem])
				index_of_min_elem = j;
		}

		//Если сортируемый элемент оказался не минимальным, то путем 3-х пересылок меняем минимальный и сортируемый элемент местами.
		if (numbers.myArray[index_of_min_elem] != numbers.myArray[i])
		{
			number_of_assignments += 3;
			int temp = numbers.myArray[index_of_min_elem];
			numbers.myArray[index_of_min_elem] = numbers.myArray[i];
			numbers.myArray[i] = temp;
		}
	}
	/*КОНЕЦ СОРТИРОВКИ*/
	//Переменная для конечного времени выполнения кода.
	clock_t end_time = clock();
	time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	std::cout << "Сортировка массива выбором успешно завершена." << std::endl << std::endl;
	std::cout << "Отсортированный массив (вывод по 10 элементов в строке):" << std::endl;
	printArray(numbers);
	std::cout << "Время выполнения сортировки: " << time_spent << " сек." << std::endl;
	std::cout << "Число произведенных сравнений: " << number_of_comparisons << std::endl <<
		"Число произведенных пересылок: " << number_of_assignments << std::endl << std::endl;
	clear_copy(numbers);
}
//Сортировка вставками. Сложность O(n^2).
void insertionSorting(DynamicArray numbers)
{
	int* copy_my_array{ copyMyArray(numbers) };
	numbers.myArray = copy_my_array;
	int number_of_comparisons{};
	int number_of_assignments{};
	//Переменная для вычисления прошедшего времени в секундах.
	double time_spent = 0.0;
	//Переменная для хранения начального времени выполнения кода.
	clock_t start_time = clock();
	/*НАЧАЛО СОРТИРОВКИ*/
	for (int i{ 1 }; i < numbers.count; i++)
	{
		number_of_assignments++;
		int current_elem{ numbers.myArray[i] };//Присваивание буферной переменной сортируемого элемента массива - пересылка.
		int j{ i - 1 };

		while (j >= 0 && numbers.myArray[j] > current_elem)//Сравнивание сортируемого элемента с предыдущими, пока выполняется условие.
		{
			number_of_comparisons++;
			numbers.myArray[j + 1] = numbers.myArray[j];
			number_of_assignments++;
			j--;
		}//Сравнивание сортируемого элемента с соответствующим предыдущим, после этого сравнения произошел выход из цикла.
		number_of_comparisons++;

		if (numbers.myArray[j + 1] != current_elem)
		{
			number_of_assignments++;//Вставка сортируемого элемента на соответствующую позицию - пересылка.
			numbers.myArray[j + 1] = current_elem;
		}
	}
	/*КОНЕЦ СОРТИРОВКИ*/
	//Переменная для конечного времени выполнения кода.
	clock_t end_time = clock();
	time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	std::cout << "Сортировка массива вставками успешно завершена." << std::endl << std::endl;
	std::cout << "Отсортированный массив (вывод по 10 элементов в строке):" << std::endl;
	printArray(numbers);
	std::cout << "Время выполнения сортировки: " << time_spent << " сек." << std::endl;
	std::cout << "Число произведенных сравнений: " << number_of_comparisons << std::endl <<
		"Число произведенных пересылок: " << number_of_assignments << std::endl << std::endl;
	clear_copy(numbers);
}
//Вывод массива на экран.
void printArray(const DynamicArray& numbers)
{
	for (int i{}; i < numbers.count; i++)
		std::cout << numbers.myArray[i] << ((((i + 1) % 10) == 0) ? "\n" : "\t");
	std::cout << std::endl;
}
//Очистка массива.
void clear(DynamicArray& numbers)
{
	delete[] numbers.myArray;
	numbers.myArray = nullptr;
	numbers.count = 0;
	std::cout << "Исходный массив успешно очищен." << std::endl <<
		"Вся выделенная динамическая память для него была возвращена в кучу." << std::endl;
}