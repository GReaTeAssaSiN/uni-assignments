#include <iostream>
#include "myfuncs.h"

//����� ����������� ���������� ����� ���������� ������������ �� �������.
void printDashes()
{
	std::cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl;
}
//���-�������, ������������ ������ ����� � ���-�������.
int hashFunctionKeyToValue(const int& sum_of_character_codes_of_the_current_key)
{
	return sum_of_character_codes_of_the_current_key % maxSize;
}
//��������������� ��������� ��� ���������� ���-�������.
void auxiliaryProgram(HashTable& f_hash_table)
{
	for (int i{}; i < maxSize; i++)
	{
		std::string current_key{ keys[i] };
		int sum_of_charater_codes{};
		for (int character_index{}; character_index < current_key.size(); character_index++)
			sum_of_charater_codes += static_cast<int>(current_key[character_index]);
		f_hash_table.array[hashFunctionKeyToValue(sum_of_charater_codes)] = current_key;
	}
}
//����� ���-������� �� �����.
void printHashTable(const HashTable& f_hash_table)
{
	std::cout << "����������� �������������� ���-�������:" << std::endl;
	for (int i{}; i < maxSize; i++)
		std::cout << i << ": " << f_hash_table.array[i] << "\n";
	std::cout << std::endl;
}
//��������� �� ������������ �����, ����� ���������� � ��� �������/���������� � ����������� ���-�������.
void getKeyAndInformationFromUser(const HashTable& f_hash_table)
{
	while (true)
	{
		std::cout << "������� �������� �����, ����� ��������� ��� ������� � ���-�������, ��� 'q', ����� ��������� ���������:" << std::endl;
		std::string user_key{};
		std::getline(std::cin, user_key);
		if (user_key != "q")
		{
			bool key_is_here{};
			for (int i{}; i < maxSize; i++)
			{
				if (f_hash_table.array[i] == user_key)
				{
					key_is_here = true;
					std::cout << "��������� ���� ��� ������ � ���-�������:\n" << i << ": " << user_key << std::endl;
					break;
				}
			}
			if (!key_is_here)
				std::cout << "��������� ���� ����������� � ���-�������." << std::endl;
			printDashes();
		}
		else
			break;
	}
}