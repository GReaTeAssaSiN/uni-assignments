#include <iostream>
#include <string>
#include "myfuncs.h"

/*���������������� ����*/
//���������������� ����.
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) ������� ������ ������ � ��������� ����� � �������� ������ ���������." << std::endl <<
		"2) ���������� ������� ������� (����� ��������)." << std::endl <<
		"3) ���������� ������� �������." << std::endl <<
		"4) ���������� ������� ���������." << std::endl <<
		"5) ����� �������� ��������� ������� �� �����." << std::endl <<
		"6) �����." << std::endl;
}
//������ �������� � �������� ������� � ������������.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6")
			return choice[0];
		else
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 6). ��������� ����:" << std::endl;
	}
}

/*��������������� �������*/
//����
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}
//�������� �������� ������������� ������ �� ����������� �������������� � ����� �����.
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
//�������������� �������� ������������� ������ � �����.
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
//����� ����������� ���������� ����� ���������� ������������ � �������.
void printDashes()
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << "\t" << std::endl;
}
//����������� ������� � ��������� DynamicArray ��� �������� ��������� ������������ � �������.
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
		std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
		clear_copy(numbers);
		exit(-1);
	}
}
//������� �������������� �������.
void clear_copy(DynamicArray& numbers)
{
	delete[] numbers.myArray;
	numbers.myArray = nullptr;
	numbers.count = 0;
	std::cout << "������, ������������� ��� �������� � ������� ��������� ������������, ������� ������." << std::endl <<
		"��� ���������� ������������ ������ ��� ���� ���� ���������� � ����." << std::endl;
}

/*�������� �������*/
//�������� ������� �� �������.
bool isEmpty(const DynamicArray& numbers)
{
	return (numbers.myArray == nullptr) ? true : false;
}
//���������� �������.
void generateArray(DynamicArray& numbers)
{
	std::cout << "������� ���������� ��������� �������: ";
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
			std::cout << "������ � ����������� ��������� " << numbers.count << " ��� ������� ������ � �������� ���������� ������� �� -1000 �� 1000." << std::endl;
			break;
		}
		else
			std::cout << "������ �����. �� ������ ������ ����� ������������� ����� (�� ����� 10000). ��������� ����: " << std::endl;
	}
}
//�������������� �������.
void regenerateArray(DynamicArray& numbers)
{
	std::cout << "������� ���������� ��������� ������ ������� ��� 'q', ����� ����� � ����: ";
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
				std::cout << "����� ������ � ����������� ��������� " << numbers.count << " ������� ������ � �������� ���������� ������� �� -1000 �� 1000." << std::endl;
				break;
			}
			else
				std::cout << "������ �����. �� ������ ������ ����� ������������� ����� (�� ����� 10000) ��� 'q'. ��������� ����: " << std::endl;
		}
		else
			break;
	}
}
//���������� ������� (����� ��������). ��������� O(n^2).
void bubbleSorting(DynamicArray numbers)
{
	int* copy_my_array{ copyMyArray(numbers) };
	numbers.myArray = copy_my_array;
	int number_of_comparisons{};
	int number_of_assignments{};
	//���������� ��� ���������� ���������� ������� � ��������.
	double time_spent = 0.0;
	//���������� ��� �������� ���������� ������� ���������� ����.
	clock_t start_time = clock();
	/*������ ����������*/
	for (int i{}; i < numbers.count - 1; i++)
		for (int j{}; j < numbers.count - i - 1; j++)//����������� ������������ �������� �� ���������� ������������������.
		{
			number_of_comparisons++;
			if (numbers.myArray[j] > numbers.myArray[j + 1])//���� ����������� ������� �� �����������, �� ����� 3-� ��������� "��������" ��� ����.
			{
				number_of_assignments += 3;
				int temp = numbers.myArray[j];
				numbers.myArray[j] = numbers.myArray[j + 1];
				numbers.myArray[j + 1] = temp;
			}
		}
	/*����� ����������*/
	//���������� ��� ��������� ������� ���������� ����.
	clock_t end_time = clock();
	time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	std::cout << "���������� ������� ������� (������� ��������) ������� ���������." << std::endl << std::endl;
	std::cout << "��������������� ������ (����� �� 10 ��������� � ������):" << std::endl;
	printArray(numbers);
	std::cout << "����� ���������� ����������: " << time_spent << " ���." << std::endl;
	std::cout << "����� ������������� ���������: " << number_of_comparisons << std::endl <<
		"����� ������������� ���������: " << number_of_assignments << std::endl << std::endl;
	clear_copy(numbers);
}
//���������� �������. ��������� O(n^2).
void selectionSorting(DynamicArray numbers)
{
	int* copy_my_array{ copyMyArray(numbers) };
	numbers.myArray = copy_my_array;
	int number_of_comparisons{};
	int number_of_assignments{};
	//���������� ��� ���������� ���������� ������� � ��������.
	double time_spent = 0.0;
	//���������� ��� �������� ���������� ������� ���������� ����.
	clock_t start_time = clock();
	/*������ ����������*/
	for (int i{}; i < numbers.count - 1; i++)
	{
		int index_of_min_elem{ i };
		for (int j{ i + 1 }; j < numbers.count; j++)//����� ������������ �������� ����� ����������������� ����� ���������.
		{
			number_of_comparisons++;
			if (numbers.myArray[j] < numbers.myArray[index_of_min_elem])
				index_of_min_elem = j;
		}

		//���� ����������� ������� �������� �� �����������, �� ����� 3-� ��������� ������ ����������� � ����������� ������� �������.
		if (numbers.myArray[index_of_min_elem] != numbers.myArray[i])
		{
			number_of_assignments += 3;
			int temp = numbers.myArray[index_of_min_elem];
			numbers.myArray[index_of_min_elem] = numbers.myArray[i];
			numbers.myArray[i] = temp;
		}
	}
	/*����� ����������*/
	//���������� ��� ��������� ������� ���������� ����.
	clock_t end_time = clock();
	time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	std::cout << "���������� ������� ������� ������� ���������." << std::endl << std::endl;
	std::cout << "��������������� ������ (����� �� 10 ��������� � ������):" << std::endl;
	printArray(numbers);
	std::cout << "����� ���������� ����������: " << time_spent << " ���." << std::endl;
	std::cout << "����� ������������� ���������: " << number_of_comparisons << std::endl <<
		"����� ������������� ���������: " << number_of_assignments << std::endl << std::endl;
	clear_copy(numbers);
}
//���������� ���������. ��������� O(n^2).
void insertionSorting(DynamicArray numbers)
{
	int* copy_my_array{ copyMyArray(numbers) };
	numbers.myArray = copy_my_array;
	int number_of_comparisons{};
	int number_of_assignments{};
	//���������� ��� ���������� ���������� ������� � ��������.
	double time_spent = 0.0;
	//���������� ��� �������� ���������� ������� ���������� ����.
	clock_t start_time = clock();
	/*������ ����������*/
	for (int i{ 1 }; i < numbers.count; i++)
	{
		number_of_assignments++;
		int current_elem{ numbers.myArray[i] };//������������ �������� ���������� ������������ �������� ������� - ���������.
		int j{ i - 1 };

		while (j >= 0 && numbers.myArray[j] > current_elem)//����������� ������������ �������� � �����������, ���� ����������� �������.
		{
			number_of_comparisons++;
			numbers.myArray[j + 1] = numbers.myArray[j];
			number_of_assignments++;
			j--;
		}//����������� ������������ �������� � ��������������� ����������, ����� ����� ��������� ��������� ����� �� �����.
		number_of_comparisons++;

		if (numbers.myArray[j + 1] != current_elem)
		{
			number_of_assignments++;//������� ������������ �������� �� ��������������� ������� - ���������.
			numbers.myArray[j + 1] = current_elem;
		}
	}
	/*����� ����������*/
	//���������� ��� ��������� ������� ���������� ����.
	clock_t end_time = clock();
	time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	std::cout << "���������� ������� ��������� ������� ���������." << std::endl << std::endl;
	std::cout << "��������������� ������ (����� �� 10 ��������� � ������):" << std::endl;
	printArray(numbers);
	std::cout << "����� ���������� ����������: " << time_spent << " ���." << std::endl;
	std::cout << "����� ������������� ���������: " << number_of_comparisons << std::endl <<
		"����� ������������� ���������: " << number_of_assignments << std::endl << std::endl;
	clear_copy(numbers);
}
//����� ������� �� �����.
void printArray(const DynamicArray& numbers)
{
	for (int i{}; i < numbers.count; i++)
		std::cout << numbers.myArray[i] << ((((i + 1) % 10) == 0) ? "\n" : "\t");
	std::cout << std::endl;
}
//������� �������.
void clear(DynamicArray& numbers)
{
	delete[] numbers.myArray;
	numbers.myArray = nullptr;
	numbers.count = 0;
	std::cout << "�������� ������ ������� ������." << std::endl <<
		"��� ���������� ������������ ������ ��� ���� ���� ���������� � ����." << std::endl;
}