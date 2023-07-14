#include <iostream>
#include "myfuncs.h"

/*���������������� ����*/
//����� ����������� ���������� ����� ���������� ������������ �� �������.
void printDashes()
{
	std::cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl;
}
//���������������� ����.
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) ���������� ������ ����� � ���-������� � ��������� ��������� ��� ���� ���������." << std::endl <<
		"2) ����� ��������� ����� � ���-������� � ��������� ��������� ��� ���� ���������." << std::endl <<
		"3) ����� �������� ��������� ���-������� �� �����." << std::endl <<
		"4) �������� ��������� ����� �� ���-�������." << std::endl <<
		"0) �����." << std::endl;
}
//������ �������� � ���-�������� � ������������.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "0" || choice == "1" || choice == "2" || choice == "3" || choice == "4")
			return choice[0];
		else
			std::cout << std::endl << "������ �����. �� ������ ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 0 �� 3). ��������� ����:" << std::endl;
	}
}

/*��������������� �������*/
//�������� �������� ������������� ������ �� ����������� �������������� � ����� ��������������� �����.
bool checkStrIsNumeric(std::string const& tempStr)
{
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//�������������� �������� ������������� ������ � ����� ��������������� �����.
int convertStrToInt(std::string convertStr)
{
	double number{};
	for (int i{}; i < convertStr.length(); i++)
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
	return number;
}

/*�������� �������*/
//���-�������, ������������ ������ ����� � ���-�������.
int hashFunctionKeyToValue(const int& sum_of_character_codes_of_the_current_key, const int& number_m)
{
	return sum_of_character_codes_of_the_current_key % number_m;
}
//��������� �� ������������ ��������� m, ������������ ������ ���-�������.
int getNumberM()
{
	std::cout << "������� ��������� m, ������������ ������ ���-�������: ";
	while (true)
	{
		std::string number_m{};
		std::getline(std::cin, number_m);
		if (checkStrIsNumeric(number_m) && convertStrToInt(number_m) >= 1)
			return convertStrToInt(number_m);
		else
			std::cout << "������ �����. �� ������ ������ ����� ������������� ����� >= 1. ��������� ����: ";
	}
}
//��������� ������ ����� ���-������� �� ������������ (����� �����, ��������, �������).
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
			std::cout << "������ �����. ���� ������ ������������ ����� ����� �� ����� ���� ���������� ��������. ��������� ����: " << std::endl;
		else
			return new_key;
	}
}
//���������� ������ ����� � ���-������� � �������������� ������ ����������� �����������.
void addNewKeyToHashTable(HashTable* f_hash_table)
{
	if (f_hash_table->count == maxSize)
		std::cout << "���� ��������� ������������ ���������� ������. �������� ���������� ������ ����� ����������." << std::endl;
	else
	{
		int number_of_comparisons{}, sum_character_codes{}, default_character_index{};
		std::cout << "������� ����, ������� ������ �������� � ���-�������: ";
		std::string new_key{ getKeyFromUser() };
		for (int i{}; i < new_key.size(); i++)
			sum_character_codes += static_cast<int>(new_key[i]);
		default_character_index = hashFunctionKeyToValue(sum_character_codes, f_hash_table->number_m);
		bool has_already_been_added{};
		number_of_comparisons++;//��������� (���-������� �� ����� ����� � ��������������� �������).
		if (f_hash_table->array[default_character_index].key.empty())
		{
			//���������� ���� � ������ ���-������� � ������� ������������ ������� ���������������� ������.
			f_hash_table->array[default_character_index].key = new_key;
			f_hash_table->array[default_character_index].head = new Node{};
			f_hash_table->array[default_character_index].tail = f_hash_table->array[default_character_index].head;
		}
		else
		{
			number_of_comparisons++;
			if (f_hash_table->array[default_character_index].key == new_key)
				has_already_been_added = true;
			else
			{
				Node* current{ f_hash_table->array[default_character_index].head->next };
				while (current != nullptr)
				{
					number_of_comparisons++;
					if (current->key == new_key)
					{
						has_already_been_added = true;
						break;
					}
					current = current->next;
				}
				if (!has_already_been_added)
				{
					//��������� ������� � ����� ���������������� ������.
					f_hash_table->array[default_character_index].tail->next = new Node{};
					f_hash_table->array[default_character_index].tail->next->key = new_key;
					f_hash_table->array[default_character_index].tail = f_hash_table->array[default_character_index].tail->next;
				}
			}
		}
		if (!has_already_been_added)
		{
			f_hash_table->count++;
			std::cout << "��������� ���� ������� �������� � ���-�������." << std::endl;
		}
		else
			std::cout << "��������� ���� ��� ��� �������� � ���-�������." << std::endl;
		std::cout << "���������� ������������� ���������: " << number_of_comparisons << std::endl;
	}
}
//����� ����� � ���-�������.
void searchKeyInHashTable(const HashTable* f_hash_table)
{
	if (f_hash_table->count == 0)
		std::cout << "���-������� �����. �������� ������ ����� ����������." << std::endl;
	else
	{
		int number_of_comparisons{}, sum_character_codes{}, default_character_index{};
		std::cout << "������� ����, ������� ������ ����� � ���-�������: ";
		std::string searched_key{ getKeyFromUser() };
		for (int i{}; i < searched_key.size(); i++)
			sum_character_codes += static_cast<int>(searched_key[i]);
		default_character_index = hashFunctionKeyToValue(sum_character_codes, f_hash_table->number_m);
		bool not_found{ true };
		number_of_comparisons++;
		if (f_hash_table->array[default_character_index].key.empty())
			not_found = true;
		else
		{
			number_of_comparisons++;
			if (f_hash_table->array[default_character_index].key == searched_key)
			{
				not_found = false;
				std::cout << "��������� ���� ��� ������� ������ � ���-�������:\n" << default_character_index << ": " << searched_key << std::endl;
				std::cout << "���������� ������������� ���������: " << number_of_comparisons << std::endl;
			}
			else
			{
				Node* current{ f_hash_table->array[default_character_index].head->next };
				while (current != nullptr)
				{
					number_of_comparisons++;
					if (current->key == searched_key)
					{
						not_found = false;
						std::cout << "��������� ���� ��� ������� ������ � ���-�������:\n" << default_character_index << ": " << searched_key << std::endl;
						std::cout << "���������� ������������� ���������: " << number_of_comparisons << std::endl;
						break;
					}
					current = current->next;
				}
			}
		}
		if (not_found)
		{
			std::cout << "��������� ���� �� ������ � ���-�������." << std::endl;
			std::cout << "���������� ������������� ���������: " << number_of_comparisons << std::endl;
		}
	}
}
//�������� ����� �� ���-�������.
void deleteKeyFromHashTable(HashTable* f_hash_table)
{
	if (f_hash_table->count == 0)
		std::cout << "���-������� �����. �������� �������� ����� �� ���-������� ����������." << std::endl;
	else
	{
		int number_of_comparisons{}, sum_character_codes{}, default_character_index{};
		std::cout << "������� ����, ������� ������ ������� �� ���-�������: ";
		std::string deleted_key{ getKeyFromUser() };
		for (int i{}; i < deleted_key.size(); i++)
			sum_character_codes += static_cast<int>(deleted_key[i]);
		default_character_index = hashFunctionKeyToValue(sum_character_codes, f_hash_table->number_m);
		bool key_have_been_deleted{};
		if (!f_hash_table->array[default_character_index].key.empty())
		{
			Node* current_node{ f_hash_table->array[default_character_index].head->next };
			if (f_hash_table->array[default_character_index].key == deleted_key)
			{
				if (current_node == nullptr)
				{
					delete f_hash_table->array[default_character_index].head;
					f_hash_table->array[default_character_index].head = nullptr;
					f_hash_table->array[default_character_index].tail = f_hash_table->array[default_character_index].head;
					f_hash_table->array[default_character_index].key.clear();
				}
				else
				{
					f_hash_table->array[default_character_index].key = current_node->key;
					f_hash_table->array[default_character_index].head->next = current_node->next;
					delete current_node;
					if (f_hash_table->array[default_character_index].head->next == nullptr)
						f_hash_table->array[default_character_index].tail = f_hash_table->array[default_character_index].head;
				}
				key_have_been_deleted = true;
			}
			else
			{
				Node* prev_current_node{ f_hash_table->array[default_character_index].head };
				while (current_node != nullptr)
				{
					if (current_node->key == deleted_key)
					{
						key_have_been_deleted = true;
						prev_current_node->next = current_node->next;
						delete current_node;
						break;
					}
					prev_current_node = prev_current_node->next;
					current_node = current_node->next;
				}
			}
		}
		if (key_have_been_deleted)
			std::cout << "��������� ���� ��� ������� ������ �� ���-�������." << std::endl;
		else
			std::cout << "��������� ���� ���������� ������� �� ���-�������, ��������� �� � ��� �����������." << std::endl;
	}
}
//����� ���-������� �� �����.
void printHashTable(const HashTable* f_hash_table)
{
	if (f_hash_table->count == 0)
		std::cout << "���-������� �����." << std::endl;
	else
	{
		std::cout << "������� ��������� ���-�������:" << std::endl;
		for (int i{}; i < f_hash_table->number_m; i++)
		{
			std::cout << i << ": " << f_hash_table->array[i].key;
			if (!f_hash_table->array[i].key.empty())
			{
				Node* current{ f_hash_table->array[i].head };
				while (current->next != nullptr)
				{
					std::cout << ", " << current->next->key;
					current = current->next;
				}
			}
			std::cout << std::endl;
		}
	}
}