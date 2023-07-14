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
			if (exit_or_searchingElem != "-1")
			{
				int searched_elems{};
				for (int i{}; i < f_list.count; i++)
				{
					if (f_list.list[i] == exit_or_searchingElem)
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
		if (exit_or_newElem != "-1")
		{
			f_list.list[f_list.count] = exit_or_newElem;
			f_list.count++;
			std::cout << "������� " << exit_or_newElem << " ��� ������� �������� � ������." << std::endl;
		}
	}
	else
	{
		bool is_max_elem{ true };
		std::cout << "������� �������, ������� ���������� ��������, ��� ������� � ����." << std::endl;
		std::string exit_or_newElem{ getElem() };
		if (exit_or_newElem != "-1")
		{
			for (int i{}; i < f_list.count; i++)
			{
				if (f_list.list[i] > exit_or_newElem)
				{
					for (int j{ f_list.count }; j > i; j--)
						f_list.list[j] = f_list.list[j - 1];
					f_list.list[i] = exit_or_newElem;
					f_list.count++;
					is_max_elem = false;
					std::cout << "����� ������� '" << exit_or_newElem << "' ��� ������� �������� � ������." << std::endl;
					break;
				}
			}
			if (is_max_elem)
			{
				f_list.list[f_list.count] = exit_or_newElem;
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
			if (exit_or_fixedElem != "-1")
			{
				for (int i{}; i < f_list.count; i++)
				{
					if (f_list.list[i] == exit_or_fixedElem)
					{
						f_list.list[i] = "";
						for (int j{ i }; j < f_list.count - 1; j++)
							f_list.list[j] = f_list.list[j + 1];
						f_list.count--;
						std::cout << "������� '" << exit_or_fixedElem << "' ��� ������� ������ �� ������." << std::endl;
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
	std::cout << "������� �������������� ����� �������� (�������� ��������� ������ ��� ��������) ��� '-1', ����� ����� � ����: " << std::endl;
	while (true)
	{
		std::string new_elem{};
		std::getline(std::cin, new_elem);
		if (new_elem == "-1" || checkStrIsText(new_elem))
			return new_elem;
		else
		{
			if (new_elem.length() > maxLength)
				std::cout << "������ �����. �������� ���� ������ ������� �������. ��������� ����: " << std::endl;
			else
				std::cout << "������ �����. �� ������ ������ ������, ��������� �� ���� ���. �������� ��� ��������, ��� '-1'. ��������� ����: " << std::endl;
		}
	}
}
//����� ����������� ���������� ����� ���������� ������������ � �������.
void printDashes()
{
	std::cout << "---------------------------------------------------------------------------------------------------------------" << "\t" << std::endl;
}

/*������� ��� �������� ����������������� �����*/
//�������� �������� ������������� ������ �� ������������ "�������� ��������� ������".
bool checkStrIsText(std::string const& tempStr)
{
	if (tempStr.length() > maxLength)
		return false;
	else
	{
		for (int i{}; i < tempStr.length(); i++)
		{
			if ((static_cast<int>(tempStr[i]) < 65) || (static_cast<int>(tempStr[i]) > 90 && (static_cast<int>(tempStr[i]) < 97)) || (static_cast<int>(tempStr[i]) > 122))
				return false;
		}
		return !tempStr.empty();
	}
}