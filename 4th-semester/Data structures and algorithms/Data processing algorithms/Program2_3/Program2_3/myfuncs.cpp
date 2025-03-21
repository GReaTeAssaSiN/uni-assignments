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
		"5) Сортировка массива кучей (пирамидальная сортировка)." << std::endl <<
		"6) Cортировка массива быстрой сортировкой Хоара." << std::endl <<
		"7) Сортировка массива сортировкой Шелла." << std::endl <<
		"8) Простейшая карманная (блочная, корзинная) сортировка." << std::endl <<
		"9) Обобщенная карманная (блочная, корзинная) сортировка." << std::endl <<
		"10) Поразрядная сортировка." << std::endl <<
		"11) Вывод текущего состояния массива на экран." << std::endl <<
		"12) Выход." << std::endl;
}
//Запрос действий с двоичным деревом у пользователя.
std::string getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8" || choice == "9" || 
			choice == "10" || choice == "11" || choice == "12")
			return choice;
		else
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 12). Повторите ввод:" << std::endl;
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
int* copyMyArray(DynamicArray& numbers)
{
	int* copy_numbers{};
	try
	{
		copy_numbers = new int[numbers.count] {};
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
//Выбор пользователем разновидности той или иной сортировки. 
std::string getUserSortChoice()
{
	while (true)
	{
		std::string shellChoice{};
		std::getline(std::cin, shellChoice);
		if (shellChoice == "1" || shellChoice == "2" || shellChoice == "q")
			return shellChoice;
		else
			std::cout << "Вы должны ввести '1', '2' или 'q'. Повторите ввод: ";
	}
}

/*ПОЛЬЗОВАТЕЛЬСКИЙ ВВОД ДЛЯ СОРТИРОВКИ ШЕЛЛА*/
//Получение количества шагов при произвольной сортировки Шелла от пользователя.
std::string getUserShellSortingCountSteps(const int& max_count_steps)
{
	while (true)
	{
		std::string user_count_steps_or_exit{};
		std::getline(std::cin, user_count_steps_or_exit);
		if (checkStrIsNumeric(user_count_steps_or_exit) && convertStrToInt(user_count_steps_or_exit) > 0
			&& convertStrToInt(user_count_steps_or_exit) <= max_count_steps || user_count_steps_or_exit == "q")
			return user_count_steps_or_exit;
		else
			std::cout << "Ошибка ввода. Вы должны ввести количество шагов в сортировке Шелла от 1 до "
			<< max_count_steps << " или 'q'. Повторите ввод:" << std::endl;
	}
}
//Получение размера каждого шага при произвольной сортировке Шелла от пользователя.
std::string getUserValueSteps(const DynamicArray& numbers, const DynamicArray& mass_of_steps)
{
	while (true)
	{
		std::string value_step_or_exit{};
		std::getline(std::cin, value_step_or_exit);
		if (value_step_or_exit == "q")
			return value_step_or_exit;
		else if (checkStrIsNumeric(value_step_or_exit) && convertStrToInt(value_step_or_exit) > 0 && convertStrToInt(value_step_or_exit) <= numbers.count / 2)
		{
			int value_step{ convertStrToInt(value_step_or_exit) };
			bool add_step{ true };
			for (int i{}; i < mass_of_steps.count; i++)
			{
				if (mass_of_steps.myArray[i] == value_step)
				{
					std::cout << "Данный шаг уже добавлен в массив." << std::endl << "Вводить шаги с повторяющимися значениями быссмысленно. " <<
						"Повторите ввод или выйдите в меню:" << std::endl;
					add_step = false;
					break;
				}
			}
			if (add_step)
				return value_step_or_exit;
		}
		else
			std::cout << "Ошибка ввода. Вы должны ввести целое положительное число от 1 до " << numbers.count / 2 << " или 'q'. Повторите ввод:" << std::endl;
	}
}
//Настройка сортировки Шелла с введенными пользователем параметрами.
void userShellSortingWishes(const DynamicArray& numbers, DynamicArray& mass_of_steps)
{
	int number_of_comporisons{}, number_of_assignments{};
	std::cout << "Введите количество шагов для сортировки Шелла (шаг размера 1 будет введен автоматически, т.к. он обязателен) " << std::endl <<
		"или 'q', чтобы выйти в меню:" << std::endl;
	int max_count_steps{}, sorted_array_size{ numbers.count };
	while (sorted_array_size != 1)
	{
		sorted_array_size /= 2;
		max_count_steps++;
	}
	std::string user_count_steps{ getUserShellSortingCountSteps(max_count_steps) };
	if (user_count_steps != "q")
	{
		int size_mass_of_steps{ convertStrToInt(user_count_steps) };
		std::cout << "Введите величину(-ы) шага(-ов) или 'q', чтобы выйти в меню." << std::endl;
		try
		{
			mass_of_steps.myArray = new int[size_mass_of_steps] {};
			mass_of_steps.count = size_mass_of_steps;
			mass_of_steps.myArray[mass_of_steps.count - 1] = 1;
			bool flag_exit{ false };
			std::cout << "Шаг " << mass_of_steps.count << ": 1" << std::endl;
			for (int i{ 1 }; i < mass_of_steps.count; i++)
			{
				std::cout << "Шаг " << mass_of_steps.count - i << ": ";
				std::string user_value_step{ getUserValueSteps(numbers, mass_of_steps) };
				if (user_value_step != "q")
				{
					int value_step{ convertStrToInt(user_value_step) };
					mass_of_steps.myArray[i - 1] = value_step;
				}
				else
				{
					delete[] mass_of_steps.myArray;
					mass_of_steps.myArray = nullptr;
					flag_exit = true;
					break;
				}
			}
			if (!flag_exit)
			{
				std::cout << "Шаги должны выполняться от наибольшого шага к наименьшему (по убыванию), поэтому введеные значения были отсортированы." << std::endl;
				quickSorting(mass_of_steps, 0, mass_of_steps.count - 1, number_of_comporisons, number_of_assignments);
				for (int i{ mass_of_steps.count - 1 }; i >= 0; i--)
					std::cout << "Шаг " << mass_of_steps.count - i << ": " << mass_of_steps.myArray[i] << std::endl;
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
			delete[] mass_of_steps.myArray;
			exit(-1);
		}
	}
}

/*ПОЛЬЗОВАТЕЛЬСКИЙ ВВОД ДЛЯ ПРОСТЕЙШЕЙ КАРМАННОЙ (БЛОЧНОЙ, КОРЗИННОЙ) СОРТИРОВКИ*/
//Проверка исходного массива на возможность применения к нему простейшей карманной сортировки.
bool checkBucketSortingIsPossible(const DynamicArray& numbers)
{
	for (int i{}; i < numbers.count; i++)
	{
		if (numbers.myArray[i] < 0 || numbers.myArray[i] >= numbers.count)
			return false;
		for (int j{ i + 1 }; j < numbers.count; j++)
		{
			if (numbers.myArray[i] == numbers.myArray[j])
				return false;
		}
	}
	return true;
}
//Генерация массива, подходящего условиям сортировки.
void generateRequiredBucketSortingArray(const DynamicArray& numbers)
{
	for (int i{}; i < numbers.count; i++)
		numbers.myArray[i] = i;
}
//Перемешивание элементов массива случайным образом.
void random_shuffle(const DynamicArray& numbers)
{
	for (int i{}; i < numbers.count; i++)
	{
		int random_index{ static_cast<int>(getRandomNumber(0, static_cast<float>(numbers.count - 1))) }, temp{ numbers.myArray[i] };
		numbers.myArray[i] = numbers.myArray[random_index];
		numbers.myArray[random_index] = temp;
	}
}
//Управление выполнением сортировки.
void userBucketSortingWishes(DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments, clock_t& start_time, clock_t& end_time, bool& sort_exit)
{
	std::cout << "Вы хотите использовать простейшую карманную сортировку с использованием второго массива ('1'), без него ('2')\nили выйти в меню ('q'): " << std::endl;
	std::string user_choice_or_exit{ getUserSortChoice() };
	if (user_choice_or_exit != "q")
	{
		int user_choice{ convertStrToInt(user_choice_or_exit) };
		switch (user_choice)
		{
		case 1:
			bucketSortingWithSecondArray(numbers, number_of_comparisons, number_of_assignments, start_time, end_time);
			break;
		case 2:
			start_time = clock();
			bucketSortingWithoutSecondArray(numbers, number_of_comparisons, number_of_assignments);
			end_time = clock();
			break;
		default:;
		}
	}
	else
		sort_exit = true;
}

/*ПОЛЬЗОВАТЕЛЬСКИЙ ВВОД ДЛЯ ОБОБЩЕННОЙ КАРМАННОЙ(БЛОЧНОЙ, КОРИЗННОЙ) СОРТИРОВКИ И ПОРАЗРЯДНОЙ СОРТИРОВКИ*/
//Проверка исходного массива на возможность применения к нему обобщенной карманной сортировки.
bool checkGenericBucketSortingAndRadixSortingIsPossible(const DynamicArray& numbers)
{
	for (int i{}; i < numbers.count; i++)
	{
		if (numbers.myArray[i] < 0 || numbers.myArray[i] >= numbers.count)
			return false;
		else
			continue;
	}
	return true;
}
//Генерация массива, подходящего условиям сортировки.
void generateRequiredGenericBucketSortingAndRadixSortingArray(const DynamicArray& numbers)
{
	for (int i{}; i < numbers.count; i++)
		numbers.myArray[i] = static_cast<int>(getRandomNumber(0, static_cast<float>(numbers.count - 1)));
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
//Вывод массива на экран.
void printArray(const DynamicArray& numbers)
{
	for (int i{}; i < numbers.count; i++)
		std::cout << numbers.myArray[i] << ((((i + 1) % 10) == 0) ? "\n" : "\t");
	std::cout << std::endl << std::endl;
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

/*СОРТИРОВКИ МАССИВА*/
//Управление алгоритмами сортировки с выводом соответствующих измерений.
void sortSelectionAndRuntimeCalculation(DynamicArray numbers, const int& algorithm_number)
{
	bool sort_exit{};//Выход из сортировки.;
	if (algorithm_number != 7 && algorithm_number != 8 && algorithm_number != 9)
		numbers.myArray = copyMyArray(numbers);
	int number_of_comparisons{};
	int number_of_assignments{};
	//Переменная для вычисления прошедшего времени в секундах.
	double time_spent = 0.0;
	//Переменная для хранения начального времени выполнения кода.
	clock_t start_time{};
	//Переменная для хранения конечного времени выполнения кода.
	clock_t end_time{};
	switch (algorithm_number)
	{
	case 1://Сортировка обменом (метод пузырька).
		start_time = clock();
		bubbleSorting(numbers, number_of_comparisons, number_of_assignments);
		end_time = clock();
		std::cout << "Сортировка массива обменом (метод пузырька) успешно завершена." << std::endl;
		break;
	case 2://Сортировка выбором.
		start_time = clock();
		selectionSorting(numbers, number_of_comparisons, number_of_assignments);
		end_time = clock();
		std::cout << "Сортировка массива выбором успешно завершена." << std::endl;
		break;
	case 3://Сортировка вставками.
		start_time = clock();
		insertionSorting(numbers, number_of_comparisons, number_of_assignments);
		end_time = clock();
		std::cout << "Сортировка массива вставками успешно завершена." << std::endl;
		break;
	case 4://Сортировка кучей (пирамидальная сортировка).
		start_time = clock();
		heapSorting(numbers, number_of_comparisons, number_of_assignments);
		end_time = clock();
		std::cout << "Сортировка массива кучей (пирамидальная сортировка) успешно завершена." << std::endl;
		break;
	case 5://Быстрая сортировка Хоара.
		start_time = clock();
		quickSorting(numbers, 0, numbers.count - 1, number_of_comparisons, number_of_assignments);
		end_time = clock();
		std::cout << "Сортировка массива быстрой сортировкой Хоара успешно завершена." << std::endl;
		break;
	case 6://Сортировка Шелла.
	{
		std::cout << "Вы хотите использовать стандартную сортировку Шелла ('1'), задать шаги сами ('2') или выйти в меню ('q'): " << std::endl;
		std::string user_choice_or_exit{ getUserSortChoice() };
		if (user_choice_or_exit != "q")
		{
			int user_choice{ convertStrToInt(user_choice_or_exit) };
			DynamicArray mass_of_steps{};
			mass_of_steps.myArray = nullptr;
			mass_of_steps.myArray = 0;
			switch (user_choice)
			{
			case 1:
				start_time = clock();
				shellSorting(numbers, number_of_comparisons, number_of_assignments);
				end_time = clock();
				std::cout << "Сортировка массива быстрой сортировкой Шелла успешно завершена." << std::endl;
				break;
			case 2:
				if (numbers.count > 1)
				{
					userShellSortingWishes(numbers, mass_of_steps);
					if (mass_of_steps.myArray != nullptr)
					{
						start_time = clock();
						userShellSorting(numbers, mass_of_steps, number_of_comparisons, number_of_assignments);
						end_time = clock();
						std::cout << "Сортировка массива быстрой сортировкой Шелла успешно завершена." << std::endl;
					}
					else
						sort_exit = true;
					delete[] mass_of_steps.myArray;
				}
				break;
			default:;
			}
		}
		else
			sort_exit = true;
		break;
	}
	case 7://Простейшая карманная сортировка.
	{
		bool bucket_sort_is_possible{ checkBucketSortingIsPossible(numbers) };
		if (bucket_sort_is_possible)
		{
			numbers.myArray = copyMyArray(numbers);
			userBucketSortingWishes(numbers, number_of_comparisons, number_of_assignments, start_time, end_time, sort_exit);
		}
		else
		{
			std::cout << "Исходный массив не может быть отсортирован простейшей карманной сортировкой, т.к. его элементы не являются\nцелыми числами от 0 до " << numbers.count <<
				" или среди них есть повторяющиеся элементы, вызывающие бесконечное выполнение сортировки." << std::endl << std::endl <<
				"Вы хотите построить новый массив, удовлетворяющий условиям, с изменением исходного массива ('1'),\nбез его изменения ('2') или выйти в меню ('q'):" << std::endl;
			std::string user_choice_or_exit{ getUserSortChoice() };
			if (user_choice_or_exit != "q")
			{
				int user_choice{ convertStrToInt(user_choice_or_exit) };
				switch (user_choice)
				{
				case 1:
					generateRequiredBucketSortingArray(numbers);
					random_shuffle(numbers);
					numbers.myArray = copyMyArray(numbers);
					break;
				case 2:
					numbers.myArray = copyMyArray(numbers);
					generateRequiredBucketSortingArray(numbers);
					random_shuffle(numbers);
					break;
				default:;
				}
				std::cout << "Скорректированный исходный массив (вывод по 10 элементов в строке): " << std::endl;
				printArray(numbers);
				std::cout << std::endl;
				userBucketSortingWishes(numbers, number_of_comparisons, number_of_assignments, start_time, end_time, sort_exit);
				std::cout << "Сортировка массива простейшей карманной сортировкой успешно завершена." << std::endl;
			}
			else
				sort_exit = true;
		}
		break;
	}
	case 8:
	{
		bool generic_bucket_sort_is_possible{ checkGenericBucketSortingAndRadixSortingIsPossible(numbers) };
		if (generic_bucket_sort_is_possible)
		{
			numbers.myArray = copyMyArray(numbers);
			genericBucketSorting(numbers, number_of_comparisons, number_of_assignments, start_time, end_time);
		}
		else
		{
			std::cout << "Исходный массив не может быть отсортирован обобщенной карманной сортировкой, т.к. его элементы не являются\nцелыми числами от 0 до "
				<< numbers.count - 1 << "." << std::endl << std::endl <<
				"Вы хотите построить новый массив, удовлетворяющий условиям, с изменением исходного массива ('1'),\nбез его изменения ('2') или выйти в меню ('q'):" << std::endl;
			std::string user_choice_or_exit{ getUserSortChoice() };
			if (user_choice_or_exit != "q")
			{
				int user_choice{ convertStrToInt(user_choice_or_exit) };
				switch (user_choice)
				{
				case 1:
					generateRequiredGenericBucketSortingAndRadixSortingArray(numbers);
					random_shuffle(numbers);
					numbers.myArray = copyMyArray(numbers);
					break;
				case 2:
					numbers.myArray = copyMyArray(numbers);
					generateRequiredGenericBucketSortingAndRadixSortingArray(numbers);
					random_shuffle(numbers);
					break;
				default:;
				}
				std::cout << "Скорректированный исходный массив (вывод по 10 элементов в строке): " << std::endl;
				printArray(numbers);
				genericBucketSorting(numbers, number_of_comparisons, number_of_assignments, start_time, end_time);
				std::cout << "Сортировка массива обобщенной карманной сортировкой успешно завершена." << std::endl;
			}
			else
				sort_exit = true;
		}
		break;
	}
	case 9:
	{
		bool radix_sort_is_possible{ checkGenericBucketSortingAndRadixSortingIsPossible(numbers) };
		if (radix_sort_is_possible)
		{
			numbers.myArray = copyMyArray(numbers);
			radixSorting(numbers, number_of_comparisons, number_of_assignments, start_time, end_time);
		}
		else
		{
			std::cout << "Исходный массив не может быть отсортирован поразрядной сортировкой, т.к. его элементы не являются\nцелыми числами от 0 до "
				<< numbers.count - 1 << "." << std::endl << std::endl <<
				"Вы хотите построить новый массив, удовлетворяющий условиям, с изменением исходного массива ('1'),\nбез его изменения ('2') или выйти в меню ('q'):" << std::endl;
			std::string user_choice_or_exit{ getUserSortChoice() };
			if (user_choice_or_exit != "q")
			{
				int user_choice{ convertStrToInt(user_choice_or_exit) };
				switch (user_choice)
				{
				case 1:
					generateRequiredGenericBucketSortingAndRadixSortingArray(numbers);
					random_shuffle(numbers);
					numbers.myArray = copyMyArray(numbers);
					break;
				case 2:
					numbers.myArray = copyMyArray(numbers);
					generateRequiredGenericBucketSortingAndRadixSortingArray(numbers);
					random_shuffle(numbers);
					break;
				default:;
				}
				std::cout << "Скорректированный исходный массив (вывод по 10 элементов в строке): " << std::endl;
				printArray(numbers);
				radixSorting(numbers, number_of_comparisons, number_of_assignments, start_time, end_time);
				std::cout << "Сортировка массива поразрядной сортировкой успешно завершена." << std::endl;
			}
			else
				sort_exit = true;
		}
		break;
	}
	default:;
	}
	if (!sort_exit)
	{
		time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		std::cout << std::endl << "Отсортированный массив (вывод по 10 элементов в строке):" << std::endl;
		printArray(numbers);
		std::cout << "Время выполнения сортировки: " << time_spent << " сек." << std::endl;
		std::cout << "Число произведенных сравнений: " << number_of_comparisons << std::endl <<
			"Число произведенных пересылок: " << number_of_assignments << std::endl << std::endl;
		clear_copy(numbers);
	}
}
//Сортировка обменом (метод пузырька). Сложность O(n^2).
void bubbleSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments)
{
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
}
//Сортировка выбором. Сложность O(n^2).
void selectionSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments)
{
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
}
//Сортировка вставками. Сложность O(n^2).
void insertionSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments)
{
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
}

/*СОРТИРОВКА КУЧЕЙ*/
//Построение двоичной кучи для максимума из исходного массива (построение производится в копии исходного массива).
void heapifyFromArray(const DynamicArray& numbers, const int& size_heap, int index_current_elem, int& number_of_comparisons, int& number_of_assignments)
{
	/*Двоичная куча (пирамида) для максимума строится таким образом, чтобы получающееся двоичное подвешенное дерево удолетворяло след. условиям:
	 *на каждом уровне дерева значение "родителя" не меньше каждого из значений его левого и правого "ребенка";
	 *правила построения двоичных деревьев.
	 Если индекс в массиве "родителя" = i, то индексы левого и правого "ребенка" соответственно = 2*i+1 и 2*i+2, если таковые имеются.*/

	 //Поиск максимального элемента среди предка и 2-х потомков (левого и правого).
	int largest_elem{ index_current_elem };//Индекс предка (предполагается максимальным элементом).
	int left_elem{ 2 * index_current_elem + 1 };//Индекс левого потомка.
	int right_elem{ 2 * index_current_elem + 2 };//Индекс правого потомка.

	//Поиск максимального элемента из левого потомка и предка путем сравнения.
	number_of_comparisons++;
	if (left_elem < size_heap && numbers.myArray[left_elem] > numbers.myArray[largest_elem])
		largest_elem = left_elem;

	//Поиск максимального элемента из правого потомка и максимального элемента, получившегося при сравнении ранее.
	number_of_comparisons++;
	if (right_elem < size_heap && numbers.myArray[right_elem] > numbers.myArray[largest_elem])
		largest_elem = right_elem;

	//Если изменился индекс максимального элемента среди указанных трех в результате сравнений.
	if (largest_elem != index_current_elem)
	{
		//Меняем местами указанные элементы кучи путем 3-х пересылок.
		number_of_assignments += 3;
		int temp = numbers.myArray[index_current_elem];
		numbers.myArray[index_current_elem] = numbers.myArray[largest_elem];
		numbers.myArray[largest_elem] = temp;
		//Рекурсивно восстанавливаем вид двоичной кучи (пирамиды) после выполнения пересылок.
		heapifyFromArray(numbers, size_heap, largest_elem, number_of_comparisons, number_of_assignments);
	}
}
//Сортировка кучей (пирамидальная сортировка). Сложность O(n*log(n)).
void heapSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments)
{
	for (int i{ numbers.count / 2 - 1 }; i >= 0; i--)//Формирование двочиной кучи для максимума из исходного массива.
		heapifyFromArray(numbers, numbers.count, i, number_of_comparisons, number_of_assignments);
	//Построенная двоичная куча для максимума интерпретируется как массив, у которого максимальный элемент из оставшихся является самым первым (он уже отсортирован).
	for (int i{ numbers.count - 1 }; i > 0; i--)/*Рассматриваем каждый неотсортированный элемент построенной кучи с конца в начало кроме первого (он уже отсортирован),
												 *т.е. пока размер кучи >1.
												 */
	{
		if (numbers.myArray[0] != numbers.myArray[i])//Если значения переставляемых элементов не совпадают.
		{
			//Меняем местами отсортированный первый и неотсортированный последний элемент кучи путем 3-х пересылок.
			number_of_assignments += 3;
			int temp{ numbers.myArray[0] };
			numbers.myArray[0] = numbers.myArray[i];
			numbers.myArray[i] = temp;
			/*Рекурсивно восстанавливаем вид двоичной кучи (пирамиды) после выполнения пересылок, уменьшив ее размер на 1:
			 *т.к.на каждом шаге увеличивается число отсортированных элементов.
			 */
			heapifyFromArray(numbers, i, 0, number_of_comparisons, number_of_comparisons);
		}
	}
}

//Быстрая сортировка Хоара. Сложность: лучшая O(n*log(n)), худшая O(n^2).
void quickSorting(const DynamicArray& numbers, int left_border, int right_border, int& number_of_comparisons, int& number_of_assignments)
{
	/*При первом вызове функции рассматривается весь исходный массив.
	 *Разбиения массива происходят по след. условиям:
	 *выбирается точка опоры, например, центр. элемент массива;
	 *все элементы, которые меньше элемента в точке опоры, располагаются слева от него;
	 *все элементы, которые больше элемента в точке опоры, располагаются справа от него;
	 *элементы, которые совпадают с элементом в точке опоры, могут располагаться как слева, так и справа от него (зависит от выбора точки опоры и разбиения массива).
	 */
	int pivot{ numbers.myArray[(left_border + right_border) / 2] };//Точка опоры (например, центр. элемент массива), относительно которой сортируются другие элементы.
	int index_low_elem{ left_border };//Индекс элемента, рассматриваемого от левой границы рассматриваемого разбиения массива.
	int index_high_elem{ right_border };//Индекс элемента, рассматриваемого от правой границы рассматриваемого разбиения массива.

	//Поиск "конфликтных" элементов в разбиениях, согласно алгоритму.
	while (index_low_elem <= index_high_elem)
	{
		//Сравнивание рассматриваемого элемента от левой границы рассматриваемого разбиения массива с элементом в точке опоры.
		number_of_comparisons++;//Т.к. цикл while (цикл с предусловием), то сравнивание происходит один раз не в теле цикла.
		while (numbers.myArray[index_low_elem] < pivot)
		{
			index_low_elem++;//Если рассматриваемый элемент меньше элемента в точке опоры, то производится переход к след. элементу (пропуск элемента).
			number_of_comparisons++;
		}

		//Сравнивание рассматриваемого элемента от правой границы рассматриваемого разбиения массива с элементом в точке опоры.
		number_of_comparisons++;//Т.к. цикл while (цикл с предусловием), то сравнивание происходит один раз не в теле цикла.
		while (numbers.myArray[index_high_elem] > pivot)
		{
			index_high_elem--;//Если рассматриваемый элемент больше элемента в точке опоры, то производится переход к пред. элементу (пропуск элемента).
			number_of_comparisons++;
		}

		//Если рассматриваемые "конфликтные" элементы от левой и правой границы рассматриваемого разбиения находятся в разных разбиениях.
		if (index_low_elem <= index_high_elem)
		{
			number_of_comparisons++;//Сравнивание значений указанных элементов на равенство (т.к. происходит переход через точку опоры границ разбиений).
			if (numbers.myArray[index_low_elem] != numbers.myArray[index_high_elem])//Путем 3-х пересылок указанные элементы переставляются местами.
			{
				number_of_assignments += 3;
				int temp{ numbers.myArray[index_low_elem] };
				numbers.myArray[index_low_elem] = numbers.myArray[index_high_elem];
				numbers.myArray[index_high_elem] = temp;
			}
			//Пропуск "исправленных" элементов разбиений.
			index_low_elem++;
			index_high_elem--;
		}
	}
	//Рекурсивный вызов алгоритма для получившихся левого и правого разбиений массива.
	if (left_border < index_high_elem)
		quickSorting(numbers, left_border, index_high_elem, number_of_comparisons, number_of_assignments);
	if (index_low_elem < right_border)
		quickSorting(numbers, index_low_elem, right_border, number_of_comparisons, number_of_assignments);
}

/*СОРТИРОВКА ШЕЛЛА. Сложность: лучшая O(n*log(n)^2), худшая O(n^2).*/
//Стандартная сортировка Шелла.
void shellSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments)
{
	for (int step{ numbers.count / 2 }; step > 0; step /= 2)//Стандартный шаг сортировки Шелла = (размер массива) div 2.
	{
		for (int i{ step }; i < numbers.count; i++)//Сортировка вставками элементов с указанным шагом.
		{
			int temp{ numbers.myArray[i] };//Присваивание буферной переменной сортируемого элемента массива - пересылка.
			number_of_assignments++;
			int j{ i - step };

			number_of_comparisons++;//Т.к. цикл while (цикл с предусловием), то сравнивание происходит один раз не в теле цикла.
			while (j >= 0 && temp < numbers.myArray[j])//Сравнивание сортируемого элемента с предыдущими, пока выполняется условие, с учетом шага.
			{
				number_of_comparisons++;
				numbers.myArray[j + step] = numbers.myArray[j];
				number_of_assignments++;
				j -= step;
			}

			if (numbers.myArray[j + step] != temp)
			{
				number_of_assignments++;//Вставка сортируемого элемента на соответствующую позицию - пересылка.
				numbers.myArray[j + step] = temp;
			}
		}
	}
}
//Сортировка Шелла с данными, введенными пользователем.
void userShellSorting(const DynamicArray& numbers, const DynamicArray& mass_of_steps, int& number_of_comparisons, int& number_of_assignments)
{
	//Аналогична стандартной сортировке Шелла, но значения шагов "вынимаются" из вспомогательного массива.
	for (int step_index{ mass_of_steps.count - 1 }; step_index >= 0; step_index--)
	{
		int step{ mass_of_steps.myArray[step_index] };
		for (int i{ step }; i < numbers.count; i++)
		{
			int temp{ numbers.myArray[i] };
			number_of_assignments++;
			int j{ i - step };

			number_of_comparisons++;
			while (j >= 0 && temp < numbers.myArray[j])
			{
				number_of_comparisons++;
				numbers.myArray[j + step] = numbers.myArray[j];
				number_of_assignments++;
				j -= step;
			}

			if (numbers.myArray[j + step] != temp)
			{
				number_of_assignments++;//Вставка сортируемого элемента на соответствующую позицию - пересылка.
				numbers.myArray[j + step] = temp;
			}
		}
	}
}

/*ПРОСТЕЙШАЯ КАРМАННАЯ (БЛОЧНАЯ, КОРЗИННАЯ) СОРТИРОВКА. Сложность: O(n).*/
//С использованием второго массива.
void bucketSortingWithSecondArray(DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments, clock_t& start_time, clock_t& end_time)
{
	start_time = clock();
	DynamicArray sorted_numbers{};//Вспомогательный второй массив.
	sorted_numbers.count = numbers.count;
	try
	{
		sorted_numbers.myArray = new int[sorted_numbers.count] {};
		for (int i{}; i < numbers.count; i++)//Путем пересылки формируются элементы вспомогательного массива из копии исходного (индекс элемента должен соответствовать его значению).
		{
			number_of_assignments ++;
			sorted_numbers.myArray[numbers.myArray[i]] = numbers.myArray[i] ;
		}
		end_time = clock();
		delete[] numbers.myArray;
		numbers.myArray = sorted_numbers.myArray;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
		delete[] sorted_numbers.myArray;
		exit(-1);
	}
}
//Без использования второго массива.
void bucketSortingWithoutSecondArray(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments)
{
	for (int i{}; i < numbers.count; i++)//Путем сравнивания и пересылки сортируются элементы копии исходного массива (индекс соответствует значению элемента).
	{
		number_of_comparisons++;//Т.к. цикл while - цикл с предусловием.
		while (numbers.myArray[i] != i)//Сравнивание индекса элемента и значения элемента по этому индексу в копии исходного массива.
		{
			number_of_comparisons++;
			number_of_assignments += 3;//Путем трех пересылок элементы переставляются, вставая на свои места.
			int temp{ numbers.myArray[i] };
			numbers.myArray[i] = numbers.myArray[numbers.myArray[i]];
			numbers.myArray[temp] = temp;
		}
	}
}

/*ОБОБЩЕННАЯ КАРМАННАЯ (БЛОЧНАЯ, КОРЗИННАЯ) СОРТИРОВКА. Сложность: O(n).*/
//Реализация сортировки.
void genericBucketSorting(const DynamicArray& numbers, int& number_of_coparisons, int& number_of_assignments, clock_t& start_time, clock_t& end_time)
{
	start_time = clock();
	Bucket* buckets{};
	try
	{
		buckets = new Bucket[numbers.count];
		for (int i{}; i < numbers.count; i++)//Формируется массив списков, где индексами массива являются различные значения, а списки содержат каждое значение, соответствующее указанному.
		{
			number_of_assignments++;//Путем пересылки значения из копии исходного массива поступает в соответствующий список.
			Node* new_node{ new Node{} };
			new_node->data = numbers.myArray[i];
			if (buckets[numbers.myArray[i]].head_ptr == nullptr)
			{
				buckets[numbers.myArray[i]].head_ptr = new Node{};
				buckets[numbers.myArray[i]].head_ptr->next = new_node;
			}
			else
				buckets[numbers.myArray[i]].last_element->next = new_node;
			buckets[numbers.myArray[i]].last_element = new_node;
		}
		end_time = clock();

		int numbers_index{};
		//Вовзращение отсортированных элементов в копию исходного массива.
		for (int i{}; i < numbers.count; i++)
		{
			if (buckets[i].head_ptr != nullptr)
			{
				Node* current{ buckets[i].head_ptr };
				while (current->next != nullptr)
				{
					numbers.myArray[numbers_index] = current->next->data;
					numbers_index++;
					current = current->next;
				}
			}
		}
		deleteBuckets(buckets, numbers.count);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
		deleteBuckets(buckets, numbers.count);
		exit(-1);
	}
}
//Очистка дополнительного массива списков.
void deleteBuckets(Bucket*& buckets, const int& buckets_size)
{
	for (int i{}; i < buckets_size; i++)
	{
		if (buckets[i].head_ptr != nullptr)
		{
			while (buckets[i].head_ptr->next != nullptr)
			{
				Node* current{ buckets[i].head_ptr->next };
				buckets[i].head_ptr->next = buckets[i].head_ptr->next->next;
				delete current;
			}
			buckets[i].last_element = buckets[i].head_ptr;
			delete buckets[i].head_ptr;
			buckets[i].last_element = nullptr;
		}
	}
	delete[] buckets;
}

/*ПОРАЗРЯДНАЯ СОРТИРОВКА. Сложность: O(n).*/
void radixSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments, clock_t& start_time, clock_t& end_time)
{
	start_time = clock();

	int max_elem{};//Для вычисления необходимого учета числа разрядов.
	for (int i{}; i < numbers.count; i++)
	{
		if (max_elem < numbers.myArray[i])
			max_elem = numbers.myArray[i];
	}

	for (int discharge{ 1 }; max_elem / discharge > 0; discharge *= 10)//Учет рассматриваемого разряда элементов.
	{
		Bucket* buckets{};
		try
		{
			buckets = new Bucket[10];
			for (int i{}; i < numbers.count; i++)/*Формируется массив списков, где индексами массива являются различные значения разрядов,
												  *а списки содержат каждое значение, соответствующее указанному.
												  */
			{
				number_of_assignments++;//Путем пересылки значения из копии исходного массива поступает в соответствующий список.
				Node* new_node{ new Node{} };
				new_node->data = numbers.myArray[i];
				if (buckets[numbers.myArray[i] / discharge % 10].head_ptr == nullptr)
				{
					buckets[numbers.myArray[i] / discharge % 10].head_ptr = new Node{};
					buckets[numbers.myArray[i] / discharge % 10].head_ptr->next = new_node;
				}
				else
					buckets[numbers.myArray[i] / discharge % 10].last_element->next = new_node;
				buckets[numbers.myArray[i] / discharge % 10].last_element = new_node;
			}

			int numbers_index{};
			//Вовзращение отсортированных элементов в копию исходного массива.
			for (int i{}; i < 10; i++)
			{
				if (buckets[i].head_ptr != nullptr)
				{
					Node* current{ buckets[i].head_ptr };
					while (current->next != nullptr)
					{
						numbers.myArray[numbers_index] = current->next->data;
						numbers_index++;
						current = current->next;
					}
				}
			}
			deleteBuckets(buckets, 10);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
			deleteBuckets(buckets, 10);
			exit(-1);
		}
	}

	end_time = clock();
}