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
		"3) ��������� � ������ ������� ����� ��������." << std::endl <<
		"4) �������� � ������ ������� ����� ���������." << std::endl <<
		"5) ������� �� ������ �������� �������." << std::endl <<
		"6) �����." << std::endl;
}
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 6). ��������� ����:" << std::endl;
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
		int ref_current_elem{ f_list.Refs[0] }, count_passed_elems{};
		while (ref_current_elem != -1)
		{
			std::cout << count_passed_elems + 1 << "-��(-��, -��) ������� ������:\t" << f_list.Elems[ref_current_elem] << std::endl;
			ref_current_elem = f_list.Refs[ref_current_elem];
			count_passed_elems++;
		}
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
				int ref_current_elem{ f_list.Refs[0] }, count_passed_elems{};
				while (ref_current_elem != -1)
				{
					if (f_list.Elems[ref_current_elem] == searching_elem)
					{
						searched_elems++;
						std::cout << count_passed_elems + 1 << "-�� ������� ������:\t" << f_list.Elems[ref_current_elem] << std::endl;
					}
					ref_current_elem = f_list.Refs[ref_current_elem];
					count_passed_elems++;
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
void addNewElem(List& f_list, const int& before_after)
{
	if (isFullnesList(f_list))
		std::cout << "������ �����. �������� ���������� ������ �������� ����������." << std::endl;
	else if (isEmptyList(f_list))
	{
		std::cout << "������ ����. ������� �������, ������� ���������� ��������, ��� ������� � ����." << std::endl;
		std::string exit_or_newElem{ getElem() };
		if (exit_or_newElem != "q")
		{
			int newElem{ convertStrToInt(exit_or_newElem) };
			f_list.Elems[f_list.Refs[0]] = newElem;
			f_list.count++;
			std::cout << "������� '" << newElem << "' ��� ������� �������� � ������." << std::endl;
		}
	}
	else
	{
		std::cout << "������� �������, ������� ���������� ��������, ��� ������� � ����." << std::endl;
		std::string newElem_or_exit{ getElem() };
		if (newElem_or_exit != "q")
		{
			int new_elem{ convertStrToInt(newElem_or_exit) };
			if (before_after == 3)
				std::cout << "������� �������, ����� ������� ���������� �������� �����, ��� ������� � ����." << std::endl;
			else
				std::cout << "������� �������, ����� �������� ���������� �������� �����, ��� ������� � ����." << std::endl;
			while (true)
			{
				std::string exit_or_specifiedElement{ getElem() };
				if (exit_or_specifiedElement != "q")
				{
					int specified_elem{ convertStrToInt(exit_or_specifiedElement) };
					int ref_current_elem{ f_list.Refs[0] };
					while (ref_current_elem != -1)
					{
						if (f_list.Elems[ref_current_elem] == specified_elem)
							break;
						ref_current_elem = f_list.Refs[ref_current_elem];
					}
					if (ref_current_elem == -1)
						std::cout << "��������� ������� ����������� � ������. ��������� ���� �������� ������." << std::endl;
					else
					{
						int free_index{};
						bool free_space{ false };
						for (int i{1}; i < size + 1; i++)
							if (f_list.Refs[i] == -1)
							{
								free_space = true;
								for (int j{}; j < size + 1; j++)
								{
									if (f_list.Refs[j] == i)
									{
										free_space = false;
										break;
									}
								}
								if (free_space)
								{
									free_index = i;
									break;
								}
							}
						if (before_after == 4)
							ref_current_elem = f_list.Refs[ref_current_elem];	
						f_list.Elems[free_index] = new_elem;
						f_list.Refs[free_index] = free_index;
						f_list.count++;
						for (int i{}; i < size + 1; i++)
							if ((ref_current_elem != -1 && f_list.Refs[i] == ref_current_elem) || (ref_current_elem == -1 && f_list.Elems[i] == specified_elem))	
							{
								int temp{ ref_current_elem };
								f_list.Refs[i] = free_index;
								f_list.Refs[free_index] = temp;
								break;
							}
						if (before_after == 3)
							std::cout << "����� ������� '" << new_elem << "' ��� ������� �������� ����� ��������� '" << specified_elem << "'." << std::endl;
						else
							std::cout << "����� ������� '" << new_elem << "' ��� ������� �������� ����� �������� '" << specified_elem << "'." << std::endl;
						break;
					}
				}
				else
					break;
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
		while (true)
		{
			std::string exit_or_fixedElem{ getElem() };
			if (exit_or_fixedElem != "q")
			{
				int fixed_elem{ convertStrToInt(exit_or_fixedElem) };
				int ref_current_elem{ f_list.Refs[0] };
				while (ref_current_elem != -1)
				{
					if (f_list.Elems[ref_current_elem] == fixed_elem)
					{
						for (int i{}; i < size + 1; i++)
							if (f_list.Refs[i] == ref_current_elem)
							{
								f_list.Elems[ref_current_elem] = 0;
								f_list.Refs[i] = f_list.Refs[ref_current_elem];
								f_list.Refs[ref_current_elem] = -1;
								f_list.count--;
								if (f_list.count == 0)
									f_list.Refs[0] = 1;
								std::cout << "������� '" << fixed_elem << "' ��� ������� ������ �� ������." << std::endl;
								break;
							}
						break;
					}
					ref_current_elem = f_list.Refs[ref_current_elem];
				}
				if (ref_current_elem != -1)
					break;
				std::cout << "��������� ������� ����������� � ������. ��������� ���� ���������� �������� ��� ������� � ����." << std::endl;
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