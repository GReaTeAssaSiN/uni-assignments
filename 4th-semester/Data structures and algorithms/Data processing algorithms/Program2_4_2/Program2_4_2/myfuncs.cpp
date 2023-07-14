#include <iostream>
#include "myfuncs.h"

/*ПОЛЬЗОВАТЕЛЬСКОЕ МЕНЮ*/
//Вывод визуального разделения между действиями пользователя на консоль.
void printDashes()
{
	std::cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl;
}
//Пользовательское меню.
void MenuForChoices()
{
	std::cout << "Что вы хотите сделать?" << std::endl <<
		"1) Добавление нового ключа в хеш-таблицу с подсчетом сделанных при этом сравнений." << std::endl <<
		"2) Поиск заданного ключа в хеш-таблице с подсчетом сделанных при этом сравнений." << std::endl <<
		"3) Вывод текущего состояния хеш-таблицы на экран." << std::endl <<
		"0) Выход." << std::endl;
}
//Запрос действий с хеш-таблицей у пользователя.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "0" || choice == "1" || choice == "2" || choice == "3")
			return choice[0];
		else
			std::cout << std::endl << "Ошибка ввода. Вы должны ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 0 до 3). Повторите ввод:" << std::endl;
	}
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//Проверка введённой пользователем строки на возможность преобразования в целое неотрицательное число.
bool checkStrIsNumeric(std::string const& tempStr)
{
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//Преобразование введённой пользователем строки в целое неотрицательное число.
int convertStrToInt(std::string convertStr)
{
	double number{};
	for (int i{}; i < convertStr.length(); i++)
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
	return number;
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Хеш-функция, возвращающая индекс ключа в хеш-таблице.
int hashFunctionKeyToValue(const int& sum_of_character_codes_of_the_current_key, const int& number_m)
{
	return sum_of_character_codes_of_the_current_key % number_m;
}
//Получение от пользователя константы m, определяющей размер хеш-таблицы.
int getNumberM()
{
	std::cout << "Введите константу m, определяющую размер хеш-таблицы: ";
	while (true)
	{
		std::string number_m{};
		std::getline(std::cin, number_m);
		if (checkStrIsNumeric(number_m) && convertStrToInt(number_m) >= 1)
			return convertStrToInt(number_m);
		else
			std::cout << "Ошибка ввода. Вы должны ввести целое положительное число >= 1. Повторите ввод: ";
	}
}
//Получение нового ключа хеш-таблицы от пользователя (любое слово, например, фамилии).
std::string getKeyFromUser()
{
	while (true)
	{
		std::string new_key{};
		std::getline(std::cin, new_key);
		bool correct_new_key{ true };
		for (int i{}; i < new_key.size(); i++)
		{
			if (!(new_key[i] >= 'a' && new_key[i] <= 'z' || new_key[i] >= 'A' && new_key[i] <= 'Z'))
			{
				correct_new_key = false;
				break;
			}
		}
		if (new_key.empty() || !correct_new_key)
			std::cout << "Ошибка ввода. Ключ должен представлять собой слово из любых букв латинского алфавита. Повторите ввод: " << std::endl;
		else
			return new_key;
	}
}
//Добавление нового ключа в хеш-таюлицу с использованием метода внутреннего хеширования.
void addNewKeyToHashTable(HashTable* f_hash_table)
{
	if (f_hash_table->count == f_hash_table->number_m)
		std::cout << "Хеш-таблица заполнена. Операция добавления нового ключа невозможна." << std::endl;
	else if (f_hash_table->count == maxSize)
		std::wcout << "Добавлено максимально возможное количество ключей. Операция добавления нового ключа невозможна." << std::endl;
	else
	{
		int number_of_comparisons{}, sum_character_codes{}, default_character_index{};
		std::cout << "Введите ключ, который хотите добавить в хеш-таблицу: ";
		std::string new_key{ getKeyFromUser() };
		for (int i{}; i < new_key.size(); i++)
			sum_character_codes += static_cast<int>(new_key[i]);
		default_character_index = hashFunctionKeyToValue(sum_character_codes, f_hash_table->number_m);
		bool has_already_been_added{};
		number_of_comparisons++;//Сравнение (хеш-таблица не имеет ключа в рассматриваемом индексе).
		if (f_hash_table->array[default_character_index].empty())
			f_hash_table->array[default_character_index] = new_key;
		else
		{
			int iteration{ 1 }, current_index{ default_character_index };
			//number_of_comparisons++;//Сравнение (условие цикла while до тела цикла) - уже проверено в условие выше (ключ f_hash_table->array[default_character_index].empty()).
			while (!f_hash_table->array[current_index].empty())
			{
				number_of_comparisons++;//Сравнение (был ли добавляемый ключ уже добавлен).
				if (f_hash_table->array[current_index] == new_key)
				{
					has_already_been_added = true;
					break;
				}
				current_index = (default_character_index + iteration) % f_hash_table->number_m;
				iteration++;
				number_of_comparisons++;//Сравнение (условие цикла while в теле цикла) (после проверки условия на совпадение добавляемого ключа с текущим).
			}
			if (!has_already_been_added)
				f_hash_table->array[current_index] = new_key;
		}
		if (!has_already_been_added)
		{
			f_hash_table->count++;
			std::cout << "Указанный ключ успешно добавлен в хеш-таблицу." << std::endl;
		}
		else
			std::cout << "Указанный ключ уже был добавлен в хеш-таблицу." << std::endl;
		std::cout << "Количество произведенных сравнений: " << number_of_comparisons << std::endl;
	}
}
//Поиск ключа в хеш-таблице.
void searchKeyInHashTable(const HashTable* f_hash_table)
{
	if (f_hash_table->count == 0)
		std::cout << "Хеш-таблица пуста. Операция поиска ключа невозможна." << std::endl;
	else
	{
		int number_of_comparisons{}, sum_character_codes{}, default_character_index{};
		std::cout << "Введите ключ, который хотите найти в хеш-таблице: ";
		std::string searched_key{ getKeyFromUser() };
		for (int i{}; i < searched_key.size(); i++)
			sum_character_codes += static_cast<int>(searched_key[i]);
		default_character_index = hashFunctionKeyToValue(sum_character_codes, f_hash_table->number_m);
		bool not_found{ true };
		number_of_comparisons++;//Сравнение (хеш-таблица не имеет ключа в рассматриваемом индексе).
		if (!f_hash_table->array[default_character_index].empty())
		{
			int iteration{ 1 }, current_index{ default_character_index };
			while (iteration <= f_hash_table->number_m - 1)
			{
				number_of_comparisons++;//Сравненивание текущего ключа с искомым.
				if (f_hash_table->array[current_index] == searched_key)
				{
					not_found = false;
					std::cout << "Указанный ключ был успешно найден в хеш-таблице:\n" << current_index << ": " << searched_key << std::endl;
					std::cout << "Количество произведенных сравнений: " << number_of_comparisons << std::endl;
					break;
				}
				else
				{
					current_index = (default_character_index + iteration) % f_hash_table->number_m;
					iteration++;
				}
			}
		}	
		if (not_found)
		{
			std::cout << "Указанный ключ не найден в хеш-таблице." << std::endl;
			std::cout << "Количество произведенных сравнений: " << number_of_comparisons << std::endl;
		}
	}
}
//Вывод хеш-таблицы на экран.
void printHashTable(const HashTable* f_hash_table)
{
	if (f_hash_table->count == 0)
		std::cout << "Хеш-таблица пуста." << std::endl;
	else
	{
		std::cout << "Текущее состояние хеш-таблицы:" << std::endl;
		for (int i{}; i < f_hash_table->number_m; i++)
			std::cout << i << ": " << f_hash_table->array[i] << std::endl;
	}
}