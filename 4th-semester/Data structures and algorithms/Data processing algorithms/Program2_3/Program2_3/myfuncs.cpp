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
		"5) ���������� ������� ����� (������������� ����������)." << std::endl <<
		"6) C��������� ������� ������� ����������� �����." << std::endl <<
		"7) ���������� ������� ����������� �����." << std::endl <<
		"8) ���������� ��������� (�������, ���������) ����������." << std::endl <<
		"9) ���������� ��������� (�������, ���������) ����������." << std::endl <<
		"10) ����������� ����������." << std::endl <<
		"11) ����� �������� ��������� ������� �� �����." << std::endl <<
		"12) �����." << std::endl;
}
//������ �������� � �������� ������� � ������������.
std::string getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8" || choice == "9" || 
			choice == "10" || choice == "11" || choice == "12")
			return choice;
		else
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 12). ��������� ����:" << std::endl;
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
//����� ������������� ������������� ��� ��� ���� ����������. 
std::string getUserSortChoice()
{
	while (true)
	{
		std::string shellChoice{};
		std::getline(std::cin, shellChoice);
		if (shellChoice == "1" || shellChoice == "2" || shellChoice == "q")
			return shellChoice;
		else
			std::cout << "�� ������ ������ '1', '2' ��� 'q'. ��������� ����: ";
	}
}

/*���������������� ���� ��� ���������� �����*/
//��������� ���������� ����� ��� ������������ ���������� ����� �� ������������.
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
			std::cout << "������ �����. �� ������ ������ ���������� ����� � ���������� ����� �� 1 �� "
			<< max_count_steps << " ��� 'q'. ��������� ����:" << std::endl;
	}
}
//��������� ������� ������� ���� ��� ������������ ���������� ����� �� ������������.
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
					std::cout << "������ ��� ��� �������� � ������." << std::endl << "������� ���� � �������������� ���������� ������������. " <<
						"��������� ���� ��� ������� � ����:" << std::endl;
					add_step = false;
					break;
				}
			}
			if (add_step)
				return value_step_or_exit;
		}
		else
			std::cout << "������ �����. �� ������ ������ ����� ������������� ����� �� 1 �� " << numbers.count / 2 << " ��� 'q'. ��������� ����:" << std::endl;
	}
}
//��������� ���������� ����� � ���������� ������������� �����������.
void userShellSortingWishes(const DynamicArray& numbers, DynamicArray& mass_of_steps)
{
	int number_of_comporisons{}, number_of_assignments{};
	std::cout << "������� ���������� ����� ��� ���������� ����� (��� ������� 1 ����� ������ �������������, �.�. �� ����������) " << std::endl <<
		"��� 'q', ����� ����� � ����:" << std::endl;
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
		std::cout << "������� ��������(-�) ����(-��) ��� 'q', ����� ����� � ����." << std::endl;
		try
		{
			mass_of_steps.myArray = new int[size_mass_of_steps] {};
			mass_of_steps.count = size_mass_of_steps;
			mass_of_steps.myArray[mass_of_steps.count - 1] = 1;
			bool flag_exit{ false };
			std::cout << "��� " << mass_of_steps.count << ": 1" << std::endl;
			for (int i{ 1 }; i < mass_of_steps.count; i++)
			{
				std::cout << "��� " << mass_of_steps.count - i << ": ";
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
				std::cout << "���� ������ ����������� �� ����������� ���� � ����������� (�� ��������), ������� �������� �������� ���� �������������." << std::endl;
				quickSorting(mass_of_steps, 0, mass_of_steps.count - 1, number_of_comporisons, number_of_assignments);
				for (int i{ mass_of_steps.count - 1 }; i >= 0; i--)
					std::cout << "��� " << mass_of_steps.count - i << ": " << mass_of_steps.myArray[i] << std::endl;
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
			delete[] mass_of_steps.myArray;
			exit(-1);
		}
	}
}

/*���������������� ���� ��� ���������� ��������� (�������, ���������) ����������*/
//�������� ��������� ������� �� ����������� ���������� � ���� ���������� ��������� ����������.
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
//��������� �������, ����������� �������� ����������.
void generateRequiredBucketSortingArray(const DynamicArray& numbers)
{
	for (int i{}; i < numbers.count; i++)
		numbers.myArray[i] = i;
}
//������������� ��������� ������� ��������� �������.
void random_shuffle(const DynamicArray& numbers)
{
	for (int i{}; i < numbers.count; i++)
	{
		int random_index{ static_cast<int>(getRandomNumber(0, static_cast<float>(numbers.count - 1))) }, temp{ numbers.myArray[i] };
		numbers.myArray[i] = numbers.myArray[random_index];
		numbers.myArray[random_index] = temp;
	}
}
//���������� ����������� ����������.
void userBucketSortingWishes(DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments, clock_t& start_time, clock_t& end_time, bool& sort_exit)
{
	std::cout << "�� ������ ������������ ���������� ��������� ���������� � �������������� ������� ������� ('1'), ��� ���� ('2')\n��� ����� � ���� ('q'): " << std::endl;
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

/*���������������� ���� ��� ���������� ���������(�������, ���������) ���������� � ����������� ����������*/
//�������� ��������� ������� �� ����������� ���������� � ���� ���������� ��������� ����������.
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
//��������� �������, ����������� �������� ����������.
void generateRequiredGenericBucketSortingAndRadixSortingArray(const DynamicArray& numbers)
{
	for (int i{}; i < numbers.count; i++)
		numbers.myArray[i] = static_cast<int>(getRandomNumber(0, static_cast<float>(numbers.count - 1)));
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
//����� ������� �� �����.
void printArray(const DynamicArray& numbers)
{
	for (int i{}; i < numbers.count; i++)
		std::cout << numbers.myArray[i] << ((((i + 1) % 10) == 0) ? "\n" : "\t");
	std::cout << std::endl << std::endl;
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

/*���������� �������*/
//���������� ����������� ���������� � ������� ��������������� ���������.
void sortSelectionAndRuntimeCalculation(DynamicArray numbers, const int& algorithm_number)
{
	bool sort_exit{};//����� �� ����������.;
	if (algorithm_number != 7 && algorithm_number != 8 && algorithm_number != 9)
		numbers.myArray = copyMyArray(numbers);
	int number_of_comparisons{};
	int number_of_assignments{};
	//���������� ��� ���������� ���������� ������� � ��������.
	double time_spent = 0.0;
	//���������� ��� �������� ���������� ������� ���������� ����.
	clock_t start_time{};
	//���������� ��� �������� ��������� ������� ���������� ����.
	clock_t end_time{};
	switch (algorithm_number)
	{
	case 1://���������� ������� (����� ��������).
		start_time = clock();
		bubbleSorting(numbers, number_of_comparisons, number_of_assignments);
		end_time = clock();
		std::cout << "���������� ������� ������� (����� ��������) ������� ���������." << std::endl;
		break;
	case 2://���������� �������.
		start_time = clock();
		selectionSorting(numbers, number_of_comparisons, number_of_assignments);
		end_time = clock();
		std::cout << "���������� ������� ������� ������� ���������." << std::endl;
		break;
	case 3://���������� ���������.
		start_time = clock();
		insertionSorting(numbers, number_of_comparisons, number_of_assignments);
		end_time = clock();
		std::cout << "���������� ������� ��������� ������� ���������." << std::endl;
		break;
	case 4://���������� ����� (������������� ����������).
		start_time = clock();
		heapSorting(numbers, number_of_comparisons, number_of_assignments);
		end_time = clock();
		std::cout << "���������� ������� ����� (������������� ����������) ������� ���������." << std::endl;
		break;
	case 5://������� ���������� �����.
		start_time = clock();
		quickSorting(numbers, 0, numbers.count - 1, number_of_comparisons, number_of_assignments);
		end_time = clock();
		std::cout << "���������� ������� ������� ����������� ����� ������� ���������." << std::endl;
		break;
	case 6://���������� �����.
	{
		std::cout << "�� ������ ������������ ����������� ���������� ����� ('1'), ������ ���� ���� ('2') ��� ����� � ���� ('q'): " << std::endl;
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
				std::cout << "���������� ������� ������� ����������� ����� ������� ���������." << std::endl;
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
						std::cout << "���������� ������� ������� ����������� ����� ������� ���������." << std::endl;
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
	case 7://���������� ��������� ����������.
	{
		bool bucket_sort_is_possible{ checkBucketSortingIsPossible(numbers) };
		if (bucket_sort_is_possible)
		{
			numbers.myArray = copyMyArray(numbers);
			userBucketSortingWishes(numbers, number_of_comparisons, number_of_assignments, start_time, end_time, sort_exit);
		}
		else
		{
			std::cout << "�������� ������ �� ����� ���� ������������ ���������� ��������� �����������, �.�. ��� �������� �� ��������\n������ ������� �� 0 �� " << numbers.count <<
				" ��� ����� ��� ���� ������������� ��������, ���������� ����������� ���������� ����������." << std::endl << std::endl <<
				"�� ������ ��������� ����� ������, ��������������� ��������, � ���������� ��������� ������� ('1'),\n��� ��� ��������� ('2') ��� ����� � ���� ('q'):" << std::endl;
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
				std::cout << "����������������� �������� ������ (����� �� 10 ��������� � ������): " << std::endl;
				printArray(numbers);
				std::cout << std::endl;
				userBucketSortingWishes(numbers, number_of_comparisons, number_of_assignments, start_time, end_time, sort_exit);
				std::cout << "���������� ������� ���������� ��������� ����������� ������� ���������." << std::endl;
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
			std::cout << "�������� ������ �� ����� ���� ������������ ���������� ��������� �����������, �.�. ��� �������� �� ��������\n������ ������� �� 0 �� "
				<< numbers.count - 1 << "." << std::endl << std::endl <<
				"�� ������ ��������� ����� ������, ��������������� ��������, � ���������� ��������� ������� ('1'),\n��� ��� ��������� ('2') ��� ����� � ���� ('q'):" << std::endl;
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
				std::cout << "����������������� �������� ������ (����� �� 10 ��������� � ������): " << std::endl;
				printArray(numbers);
				genericBucketSorting(numbers, number_of_comparisons, number_of_assignments, start_time, end_time);
				std::cout << "���������� ������� ���������� ��������� ����������� ������� ���������." << std::endl;
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
			std::cout << "�������� ������ �� ����� ���� ������������ ����������� �����������, �.�. ��� �������� �� ��������\n������ ������� �� 0 �� "
				<< numbers.count - 1 << "." << std::endl << std::endl <<
				"�� ������ ��������� ����� ������, ��������������� ��������, � ���������� ��������� ������� ('1'),\n��� ��� ��������� ('2') ��� ����� � ���� ('q'):" << std::endl;
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
				std::cout << "����������������� �������� ������ (����� �� 10 ��������� � ������): " << std::endl;
				printArray(numbers);
				radixSorting(numbers, number_of_comparisons, number_of_assignments, start_time, end_time);
				std::cout << "���������� ������� ����������� ����������� ������� ���������." << std::endl;
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
		std::cout << std::endl << "��������������� ������ (����� �� 10 ��������� � ������):" << std::endl;
		printArray(numbers);
		std::cout << "����� ���������� ����������: " << time_spent << " ���." << std::endl;
		std::cout << "����� ������������� ���������: " << number_of_comparisons << std::endl <<
			"����� ������������� ���������: " << number_of_assignments << std::endl << std::endl;
		clear_copy(numbers);
	}
}
//���������� ������� (����� ��������). ��������� O(n^2).
void bubbleSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments)
{
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
}
//���������� �������. ��������� O(n^2).
void selectionSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments)
{
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
}
//���������� ���������. ��������� O(n^2).
void insertionSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments)
{
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
}

/*���������� �����*/
//���������� �������� ���� ��� ��������� �� ��������� ������� (���������� ������������ � ����� ��������� �������).
void heapifyFromArray(const DynamicArray& numbers, const int& size_heap, int index_current_elem, int& number_of_comparisons, int& number_of_assignments)
{
	/*�������� ���� (��������) ��� ��������� �������� ����� �������, ����� ������������ �������� ����������� ������ ������������ ����. ��������:
	 *�� ������ ������ ������ �������� "��������" �� ������ ������� �� �������� ��� ������ � ������� "�������";
	 *������� ���������� �������� ��������.
	 ���� ������ � ������� "��������" = i, �� ������� ������ � ������� "�������" �������������� = 2*i+1 � 2*i+2, ���� ������� �������.*/

	 //����� ������������� �������� ����� ������ � 2-� �������� (������ � �������).
	int largest_elem{ index_current_elem };//������ ������ (�������������� ������������ ���������).
	int left_elem{ 2 * index_current_elem + 1 };//������ ������ �������.
	int right_elem{ 2 * index_current_elem + 2 };//������ ������� �������.

	//����� ������������� �������� �� ������ ������� � ������ ����� ���������.
	number_of_comparisons++;
	if (left_elem < size_heap && numbers.myArray[left_elem] > numbers.myArray[largest_elem])
		largest_elem = left_elem;

	//����� ������������� �������� �� ������� ������� � ������������� ��������, ������������� ��� ��������� �����.
	number_of_comparisons++;
	if (right_elem < size_heap && numbers.myArray[right_elem] > numbers.myArray[largest_elem])
		largest_elem = right_elem;

	//���� ��������� ������ ������������� �������� ����� ��������� ���� � ���������� ���������.
	if (largest_elem != index_current_elem)
	{
		//������ ������� ��������� �������� ���� ����� 3-� ���������.
		number_of_assignments += 3;
		int temp = numbers.myArray[index_current_elem];
		numbers.myArray[index_current_elem] = numbers.myArray[largest_elem];
		numbers.myArray[largest_elem] = temp;
		//���������� ��������������� ��� �������� ���� (��������) ����� ���������� ���������.
		heapifyFromArray(numbers, size_heap, largest_elem, number_of_comparisons, number_of_assignments);
	}
}
//���������� ����� (������������� ����������). ��������� O(n*log(n)).
void heapSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments)
{
	for (int i{ numbers.count / 2 - 1 }; i >= 0; i--)//������������ �������� ���� ��� ��������� �� ��������� �������.
		heapifyFromArray(numbers, numbers.count, i, number_of_comparisons, number_of_assignments);
	//����������� �������� ���� ��� ��������� ���������������� ��� ������, � �������� ������������ ������� �� ���������� �������� ����� ������ (�� ��� ������������).
	for (int i{ numbers.count - 1 }; i > 0; i--)/*������������� ������ ����������������� ������� ����������� ���� � ����� � ������ ����� ������� (�� ��� ������������),
												 *�.�. ���� ������ ���� >1.
												 */
	{
		if (numbers.myArray[0] != numbers.myArray[i])//���� �������� �������������� ��������� �� ���������.
		{
			//������ ������� ��������������� ������ � ����������������� ��������� ������� ���� ����� 3-� ���������.
			number_of_assignments += 3;
			int temp{ numbers.myArray[0] };
			numbers.myArray[0] = numbers.myArray[i];
			numbers.myArray[i] = temp;
			/*���������� ��������������� ��� �������� ���� (��������) ����� ���������� ���������, �������� �� ������ �� 1:
			 *�.�.�� ������ ���� ������������� ����� ��������������� ���������.
			 */
			heapifyFromArray(numbers, i, 0, number_of_comparisons, number_of_comparisons);
		}
	}
}

//������� ���������� �����. ���������: ������ O(n*log(n)), ������ O(n^2).
void quickSorting(const DynamicArray& numbers, int left_border, int right_border, int& number_of_comparisons, int& number_of_assignments)
{
	/*��� ������ ������ ������� ��������������� ���� �������� ������.
	 *��������� ������� ���������� �� ����. ��������:
	 *���������� ����� �����, ��������, �����. ������� �������;
	 *��� ��������, ������� ������ �������� � ����� �����, ������������� ����� �� ����;
	 *��� ��������, ������� ������ �������� � ����� �����, ������������� ������ �� ����;
	 *��������, ������� ��������� � ��������� � ����� �����, ����� ������������� ��� �����, ��� � ������ �� ���� (������� �� ������ ����� ����� � ��������� �������).
	 */
	int pivot{ numbers.myArray[(left_border + right_border) / 2] };//����� ����� (��������, �����. ������� �������), ������������ ������� ����������� ������ ��������.
	int index_low_elem{ left_border };//������ ��������, ���������������� �� ����� ������� ���������������� ��������� �������.
	int index_high_elem{ right_border };//������ ��������, ���������������� �� ������ ������� ���������������� ��������� �������.

	//����� "�����������" ��������� � ����������, �������� ���������.
	while (index_low_elem <= index_high_elem)
	{
		//����������� ���������������� �������� �� ����� ������� ���������������� ��������� ������� � ��������� � ����� �����.
		number_of_comparisons++;//�.�. ���� while (���� � ������������), �� ����������� ���������� ���� ��� �� � ���� �����.
		while (numbers.myArray[index_low_elem] < pivot)
		{
			index_low_elem++;//���� ��������������� ������� ������ �������� � ����� �����, �� ������������ ������� � ����. �������� (������� ��������).
			number_of_comparisons++;
		}

		//����������� ���������������� �������� �� ������ ������� ���������������� ��������� ������� � ��������� � ����� �����.
		number_of_comparisons++;//�.�. ���� while (���� � ������������), �� ����������� ���������� ���� ��� �� � ���� �����.
		while (numbers.myArray[index_high_elem] > pivot)
		{
			index_high_elem--;//���� ��������������� ������� ������ �������� � ����� �����, �� ������������ ������� � ����. �������� (������� ��������).
			number_of_comparisons++;
		}

		//���� ��������������� "�����������" �������� �� ����� � ������ ������� ���������������� ��������� ��������� � ������ ����������.
		if (index_low_elem <= index_high_elem)
		{
			number_of_comparisons++;//����������� �������� ��������� ��������� �� ��������� (�.�. ���������� ������� ����� ����� ����� ������ ���������).
			if (numbers.myArray[index_low_elem] != numbers.myArray[index_high_elem])//����� 3-� ��������� ��������� �������� �������������� �������.
			{
				number_of_assignments += 3;
				int temp{ numbers.myArray[index_low_elem] };
				numbers.myArray[index_low_elem] = numbers.myArray[index_high_elem];
				numbers.myArray[index_high_elem] = temp;
			}
			//������� "������������" ��������� ���������.
			index_low_elem++;
			index_high_elem--;
		}
	}
	//����������� ����� ��������� ��� ������������ ������ � ������� ��������� �������.
	if (left_border < index_high_elem)
		quickSorting(numbers, left_border, index_high_elem, number_of_comparisons, number_of_assignments);
	if (index_low_elem < right_border)
		quickSorting(numbers, index_low_elem, right_border, number_of_comparisons, number_of_assignments);
}

/*���������� �����. ���������: ������ O(n*log(n)^2), ������ O(n^2).*/
//����������� ���������� �����.
void shellSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments)
{
	for (int step{ numbers.count / 2 }; step > 0; step /= 2)//����������� ��� ���������� ����� = (������ �������) div 2.
	{
		for (int i{ step }; i < numbers.count; i++)//���������� ��������� ��������� � ��������� �����.
		{
			int temp{ numbers.myArray[i] };//������������ �������� ���������� ������������ �������� ������� - ���������.
			number_of_assignments++;
			int j{ i - step };

			number_of_comparisons++;//�.�. ���� while (���� � ������������), �� ����������� ���������� ���� ��� �� � ���� �����.
			while (j >= 0 && temp < numbers.myArray[j])//����������� ������������ �������� � �����������, ���� ����������� �������, � ������ ����.
			{
				number_of_comparisons++;
				numbers.myArray[j + step] = numbers.myArray[j];
				number_of_assignments++;
				j -= step;
			}

			if (numbers.myArray[j + step] != temp)
			{
				number_of_assignments++;//������� ������������ �������� �� ��������������� ������� - ���������.
				numbers.myArray[j + step] = temp;
			}
		}
	}
}
//���������� ����� � �������, ���������� �������������.
void userShellSorting(const DynamicArray& numbers, const DynamicArray& mass_of_steps, int& number_of_comparisons, int& number_of_assignments)
{
	//���������� ����������� ���������� �����, �� �������� ����� "����������" �� ���������������� �������.
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
				number_of_assignments++;//������� ������������ �������� �� ��������������� ������� - ���������.
				numbers.myArray[j + step] = temp;
			}
		}
	}
}

/*���������� ��������� (�������, ���������) ����������. ���������: O(n).*/
//� �������������� ������� �������.
void bucketSortingWithSecondArray(DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments, clock_t& start_time, clock_t& end_time)
{
	start_time = clock();
	DynamicArray sorted_numbers{};//��������������� ������ ������.
	sorted_numbers.count = numbers.count;
	try
	{
		sorted_numbers.myArray = new int[sorted_numbers.count] {};
		for (int i{}; i < numbers.count; i++)//����� ��������� ����������� �������� ���������������� ������� �� ����� ��������� (������ �������� ������ ��������������� ��� ��������).
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
		std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
		delete[] sorted_numbers.myArray;
		exit(-1);
	}
}
//��� ������������� ������� �������.
void bucketSortingWithoutSecondArray(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments)
{
	for (int i{}; i < numbers.count; i++)//����� ����������� � ��������� ����������� �������� ����� ��������� ������� (������ ������������� �������� ��������).
	{
		number_of_comparisons++;//�.�. ���� while - ���� � ������������.
		while (numbers.myArray[i] != i)//����������� ������� �������� � �������� �������� �� ����� ������� � ����� ��������� �������.
		{
			number_of_comparisons++;
			number_of_assignments += 3;//����� ���� ��������� �������� ��������������, ������� �� ���� �����.
			int temp{ numbers.myArray[i] };
			numbers.myArray[i] = numbers.myArray[numbers.myArray[i]];
			numbers.myArray[temp] = temp;
		}
	}
}

/*���������� ��������� (�������, ���������) ����������. ���������: O(n).*/
//���������� ����������.
void genericBucketSorting(const DynamicArray& numbers, int& number_of_coparisons, int& number_of_assignments, clock_t& start_time, clock_t& end_time)
{
	start_time = clock();
	Bucket* buckets{};
	try
	{
		buckets = new Bucket[numbers.count];
		for (int i{}; i < numbers.count; i++)//����������� ������ �������, ��� ��������� ������� �������� ��������� ��������, � ������ �������� ������ ��������, ��������������� ����������.
		{
			number_of_assignments++;//����� ��������� �������� �� ����� ��������� ������� ��������� � ��������������� ������.
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
		//����������� ��������������� ��������� � ����� ��������� �������.
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
		std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
		deleteBuckets(buckets, numbers.count);
		exit(-1);
	}
}
//������� ��������������� ������� �������.
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

/*����������� ����������. ���������: O(n).*/
void radixSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments, clock_t& start_time, clock_t& end_time)
{
	start_time = clock();

	int max_elem{};//��� ���������� ������������ ����� ����� ��������.
	for (int i{}; i < numbers.count; i++)
	{
		if (max_elem < numbers.myArray[i])
			max_elem = numbers.myArray[i];
	}

	for (int discharge{ 1 }; max_elem / discharge > 0; discharge *= 10)//���� ���������������� ������� ���������.
	{
		Bucket* buckets{};
		try
		{
			buckets = new Bucket[10];
			for (int i{}; i < numbers.count; i++)/*����������� ������ �������, ��� ��������� ������� �������� ��������� �������� ��������,
												  *� ������ �������� ������ ��������, ��������������� ����������.
												  */
			{
				number_of_assignments++;//����� ��������� �������� �� ����� ��������� ������� ��������� � ��������������� ������.
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
			//����������� ��������������� ��������� � ����� ��������� �������.
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
			std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
			deleteBuckets(buckets, 10);
			exit(-1);
		}
	}

	end_time = clock();
}