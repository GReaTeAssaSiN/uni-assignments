#include <iostream>
#include <string>
#include "myfuncs.h"

/*���������������� �������*/
//���������������� ����
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) �������� �� ������ � ������� �� ����� �������������� ������ ���������." << std::endl <<
		"2) ����� � ������ �������(-�) � �������� �������������� ������." << std::endl <<
		"3) ��������� � ������ �������� �������." << std::endl <<
		"4) ������� �� ������ �������� �������." << std::endl <<
		"5) �����." << std::endl;
}
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 5). ��������� ����:" << std::endl;
		}
	}
}

/*�������� �������*/
//����� �������������� ������ ��������� ������ �� �������.
void printList(const List& f_list)
{
	if (isEmptyList(f_list))
		std::cout << "������ ����." << std::endl;
	else
	{
		std::cout << "������� ��������� ������: " << std::endl;
		for (int i{}; i < f_list.count; i++)
			std::cout << i + 1 << "-��(-��,-��) ������� ������:\t" << f_list.list[i] << std::endl;
	}
}
//����� �������� � �������� �������������� ������.
void searchList(List& f_list)
{
	if (isEmptyList(f_list))
		std::cout << "������ ����. �������� ������ �������� ����������." << std::endl;
	else
	{
		while (true)
		{
			std::string exit_or_searchingElem{ getElem() };
			if (exit_or_searchingElem != "q")
			{
				int searched_elems{}, searching_elem{ convertStrToInt(exit_or_searchingElem) };
				for (int i{}; i < f_list.count; i++)
				{
					if (f_list.list[i] == searching_elem)
					{
						searched_elems++;
						std::cout << i + 1 << "-�� ������� ������:\t" << f_list.list[i] << std::endl;
					}
				}
				if (searched_elems != 0)
				{
					std::cout << "����� ���� ������� " << searched_elems << " �������(-�,-��)." << std::endl;
					break;
				}
				else
					std::cout << "��������� ������� ����������� � ������." << std::endl;
			}
			else
				break;
		}
	}
}
//���������� �������� � ������ ��/����� ���������.
void addNewElem(List& f_list)
{
	if (isFullnesList(f_list))
		std::cout << "������ �����. �������� ���������� ������ �������� ����������." << std::endl;
	else if (isEmptyList(f_list))
	{
		std::cout << "������ ����. ������� �������, ������� ���������� ��������, ��� ������� � ����." << std::endl;
		std::string exit_or_newElem{ getElem() };
		if (exit_or_newElem != "q")
		{
			int new_elem{ convertStrToInt(exit_or_newElem) };
			f_list.list[f_list.count] = new_elem;
			f_list.count++;
			std::cout << "������� '" << new_elem << "' ��� ������� �������� � ������." << std::endl;
		}
	}
	else
	{
		bool is_max_elem{true};
		std::cout << "������� �������, ������� ���������� ��������, ��� ������� � ����." << std::endl;
		std::string exit_or_newElem{ getElem() };
		if (exit_or_newElem != "q")
		{
			int new_elem{ convertStrToInt(exit_or_newElem) };
			for (int i{}; i < f_list.count; i++)
			{
				if (f_list.list[i] > new_elem)
				{
					for (int j{ f_list.count }; j > i; j--)
						f_list.list[j] = f_list.list[j - 1];
					f_list.list[i] = new_elem;
					f_list.count++;
					is_max_elem = false;
					std::cout << "����� ������� '" << new_elem << "' ��� ������� �������� � ������." << std::endl;
					break;
				}
			}
			if (is_max_elem)
			{
				f_list.list[f_list.count] = new_elem;
				f_list.count++;
			}
		}
	}
}
//�������� �������� �� ������.
void removeElem(List& f_list)
{
	if (isEmptyList(f_list))
		std::cout << "������ ����. �������� �������� �������� �� ������ ����������." << std::endl;
	else
	{
		printList(f_list);
		bool cycle{ true };
		while (cycle)
		{
			std::string exit_or_fixedElem{ getElem() };
			if (exit_or_fixedElem != "q")
			{
				int fixed_elem{ convertStrToInt(exit_or_fixedElem) };
				for (int i{}; i < f_list.count; i++)
				{
					if (f_list.list[i] == fixed_elem)
					{
						f_list.list[i] = 0;
						for (int j{ i }; j < f_list.count - 1; j++)
							f_list.list[j] = f_list.list[j + 1];
						f_list.count--;
						std::cout << "������� '" << fixed_elem << "' ��� ������� ������ �� ������." << std::endl;
						cycle = false;
						break;
					}
				}
				if (!cycle)
					break;
				std::cout << "��������� ������� ����������� � ������." << std::endl;
			}
			else
				break;
		}
	}
}

/*��������������� �������*/
//�������� ������ �� ������� (������� ���� �� ������ ��������).
bool isEmptyList(const List& f_list)
{
	return (f_list.count == 0) ? true : false;
}
//�������� ������ �� ������������� (������� ��������� ����� ��� ����� ���������).
bool isFullnesList(const List& f_list)
{
	return (f_list.count == size) ? true : false;
}
//������ ��������������� ����� �������� � ������������.
std::string getElem()
{
	std::cout << "������� �������������� ����� �������� (����� �����) ��� 'q', ����� ����� � ����: ";
	while (true)
	{
		std::string new_elem{};
		std::getline(std::cin, new_elem);
		if (checkStrIsNumeric(new_elem) || new_elem == "q")
			return new_elem;
		else
			std::cout << "������ �����. �� ������ ������ ����� ����� ��� 'q'. ��������� ����: ";
	}
}
//����� ����������� ���������� ����� ���������� ������������ � �������.
void printDashes()
{
	std::cout << "---------------------------------------------------------------------------------------------------------------" << "\t" << std::endl;
}

/*������� ��� �������� ����������������� �����*/
//�������� �������� ������������� ������ �� ����������� �������������� � ����� ��������������� �����.
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