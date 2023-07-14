#include <iostream>
#include <sstream>
#include <fstream>
#include "mystructs.h"
#include "myfuncs.h"
#include "ArrayThreeStrings.h"

//�������� �������
//����� ������ �� ����� � ������������ ������
bool LoadingList(const std::string fileName, Trade*& head)
{
	std::ifstream out_DataFile(fileName);
	if (!out_DataFile)
	{
		std::cerr << "�� ������� ������� ����!" << std::endl;
		return false;
	}
	else
	{
		if (getListFromFile(head, out_DataFile))
			return true;
		else
			return false;
	}
}

//����� ������ �� ������������� ������ � ����
bool UnloadingList(const std::string fileName, Trade* head)
{
	Trade* tail{ head };
	std::ofstream in_DataFile(fileName);
	if (!in_DataFile)
	{
		std::cerr << "�� ������� ������� ����!" << std::endl;
		return false;
	}
	else
	{
		if (head != nullptr)
		{
			do {
				if (tail->next != head)
				{
					in_DataFile << tail->data.TypeOfSecurities << ";" << tail->data.AmountOfDeals << ";" << tail->data.TradingVolume << std::endl;
					tail = tail->next;
				}
				else
				{
					in_DataFile << tail->data.TypeOfSecurities << ";" << tail->data.AmountOfDeals << ";" << tail->data.TradingVolume;
					tail = tail->next;
				}
			} while (tail != head);
			while (true)
			{
				Trade* clean_ptr{ tail };
				tail = tail->next;
				std::cout << "������ � ������ ������ " << clean_ptr->data.TypeOfSecurities << ",... ��������� � ������� �� ����������� ������." << std::endl;
				delete clean_ptr;
				if (tail == head)
					break;
			}
		}

		in_DataFile.close();
		return true;
	}
}

//��� case1 - ���������� ��������� ������������� ������
unsigned ListLength(Trade* head)
{
	Trade* current{ head };
	unsigned length{0};
	if (head != nullptr)
	{
		if (current->next != head)
		{
			while (current->next != head)
			{
				length++;
				current = current->next;
			}
			return ++length;
		}
		else
		{
			return ++length;
		}
	}
	else
	{
		return length;
	}
}

//��� case2 - �������� ����� ������� ������������ � ������
void AddNewElement(Trade*& previous, Trade* ea)
{
	std::string AddNewElement{};
	Trade* after{};

	ea = new Trade{};
	after = previous->next;
	previous->next = ea;
	std::cout << "������� ������ � ����� ��������:" << std::endl;

	std::cout << "<�������� ������ ������>: ";
	std::getline(std::cin, AddNewElement);
	ea->data.TypeOfSecurities = AddNewElement;

	std::cout << "<���������� ������>: ";
	AddNewElement = checkData2();
	ea->data.AmountOfDeals = AddNewElement;

	std::cout << "<����� ������>. ";
	if (!FastInput_TradingVolume(ea, AddNewElement))
	{
		std::cout << "<����� ������>: ";
		std::getline(std::cin, AddNewElement);
		ea->data.TradingVolume = AddNewElement;
	}

	ea->next = after;
}

//��� case3 - ������� ������� �� ������
void DeleteElement(Trade* search_prev_del, const Trade* ed)
{
	while (search_prev_del->next != ed)
	{
		search_prev_del = search_prev_del->next;
	}
	search_prev_del->next = ed->next;
	delete ed;
}

//��� case4 - ������������� ������������ ������
void SortList(Trade* head)
{
	if (head == nullptr)
	{
		std::cout << "������ ����." << std::endl;
	}
	else
	{
		unsigned choice{ getSortChoice() };
		Trade* current{ head };
		Trade* index{ nullptr };
		while (current->next != head)
		{
			index = current->next;
			while (index != head)
			{
				SortChoice(choice, current, index);
				index = index->next;
			}
			current = current->next;
		}
	}
}

//��� case5 - ������ ������ �� �������
void PrintList(const Trade* head)
{
	const Trade* tail{ head };
	if (head != nullptr)
	{
		int index_number{};
		std::cout << "____________________ ��� ������: ____________________" << std::endl;
		do {
			index_number++;
			std::cout << index_number << ") " << tail->data.TypeOfSecurities << ";" << tail->data.AmountOfDeals << ";" << tail->data.TradingVolume << std::endl;
			tail = tail->next;
		} while (tail != head);
	}
	else
	{
		std::cout << "������ ����." << std::endl;
	}
}


//��������������� �������
//���������� ������ ������ �� ����� \, ���� ������ � �������� ����� ������������� ������, ���� ���� ������
bool getListFromFile(Trade*& head, std::ifstream& fileName)
{
	int count_str{ 0 }, flag{};
	std::string DataLine{};
	while (!fileName.eof())
	{
		if (std::getline(fileName, DataLine))
		{
			count_str++;
			flag++;
			std::stringstream lineStream{ DataLine };
			if (CheckCorrectField(DataLine, count_str))
				getNewTrade(head, lineStream);
			else
				return false;
		}
		else if (flag == 0)
		{
			std::cout << "��� ���� ������. �� ������ ������ ������ �������?" << std::endl <<
				"�� - 1" << std::endl <<
				"��� - 0" << std::endl;
			while (true)
			{
				char sm;
				std::cin >> sm;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (sm == '0')
				{
					return false;
				}
				else if (sm == '1')
				{
					Trade* ea{ head };
					CreateHeadOfList(head);
					return true;
				}
				else
				{
					std::cerr << "������ �����. ������� 0 ��� 1. ��������� ����: ";
				}
			}
		}
	}
	return true;
}

// ��������, ����� � ����� ���� 3 ����, 2-�� �� ������� - �����
bool CheckCorrectField(std::string check_DataLine, unsigned count)
{
	std::stringstream DataNode{ check_DataLine };
	std::string field{}, check{};
	int index_field{ 1 };
	std::getline(DataNode, check, ';');
	while (std::getline(DataNode, field, ';'))
	{
		index_field++;
		if (index_field == 2)
		{
			for (unsigned i = 0; i < field.length(); i++)
			{
				if (!isdigit(field[i]))
				{
					if (field[i] == '-' && field.length() == 1)
					{
						continue;
					}
					else
					{
						std::cout << count << "-� ������� ����� ������������ ������ �� 2-� �������������� ����." << std::endl;
						return false;
					}
				}
			}
		}
	}
	if (index_field != 3)
	{
		std::cout << count << "-� ������� ����� ����������� ���������� ������ ��������������� ����." << std::endl;
		return false;
	}
	return true;
}

//������� ���� 3-�� ���� � �������������� ���� �������� <����� ������>
bool FastInput_TradingVolume(Trade* ea, std::string fast_AddNewElement)
{
	std::cout << "�������� ���� �� ��������� ��������� ��� ������� ����, ����������� �� ������." << std::endl <<
		"����� ��������� -\t 1" << std::endl <<
		"��������� \t-\t 2" << std::endl <<
		"������� \t-\t 3" << std::endl <<
		"������� \t-\t 4" << std::endl <<
		"����� ������� \t-\t 5" << std::endl <<
		"������ ���� \t-\t 6" << std::endl;
	while (true)
	{
		{
			char sm;
			std::cin >> sm;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			switch (sm)
			{
			case '1':
				fast_AddNewElement = "����� ���������";
				ea->data.TradingVolume = fast_AddNewElement;
				return true;
			case '2':
				fast_AddNewElement = "���������";
				ea->data.TradingVolume = fast_AddNewElement;
				return true;
			case '3':
				fast_AddNewElement = "�������";
				ea->data.TradingVolume = fast_AddNewElement;
				return true;
			case '4':
				fast_AddNewElement = "�������";
				ea->data.TradingVolume = fast_AddNewElement;
				return true;
			case '5':
				fast_AddNewElement = "����� �������";
				ea->data.TradingVolume = fast_AddNewElement;
				return true;
			case '6':
				return false;
			default:
				std::cout << "������� ���� �� ��������� ���� (�����). ��������� ����:" << std::endl;
			}
		}
	}
}

//��������� ������ �������� �� ��������� � ��������������� ����
void getNewTrade(Trade*& head, std::stringstream& lineStream)
{
	if (head == nullptr)
	{
		head = new Trade{};
		InitializationNewTrade(lineStream, head);
		head->next = head;
	}
	else
	{
		Trade* tail{ head };
		while (tail->next != head)
		{
			tail = tail->next;
		}
		tail->next = new Trade{};
		tail = tail->next;
		InitializationNewTrade(lineStream, tail);
		tail->next = head;
	}
}

//����������� ������ ������ � �������������� ���� �������� ������������� ������ � ������������� �� � ���������
void InitializationNewTrade(std::stringstream& lineStream, Trade*& init_head)
{
	std::string data{};
	ArrayThreeStrings str_value;
	int index_head{ 0 };
	while(std::getline(lineStream, data, ';'))
	{
		str_value[index_head] = data;
		index_head++;
	}

	init_head->data.TypeOfSecurities = str_value[0];
	init_head->data.AmountOfDeals = str_value[1];
	init_head->data.TradingVolume = str_value[2];
}

//�������� ����� ������
void CreateHeadOfList(Trade*& head)
{
	std::string AddDataToHead{};
	head = new Trade{};
	std::cout << "������� ������ ��������� ��������: " << std::endl;
	std::cout << "<�������� ������ ������>: ";
	std::getline(std::cin, AddDataToHead);
	head->data.TypeOfSecurities = AddDataToHead;

	std::cout << "<���������� ������>: ";
	AddDataToHead = checkData2();
	head->data.AmountOfDeals = AddDataToHead;

	std::cout << "<����� ������>: ";
	if (!FastInput_TradingVolume(head, AddDataToHead))
	{
		std::getline(std::cin, AddDataToHead);
		head->data.TradingVolume = AddDataToHead;
	}

	head->next = head;
}

//�������� 2-�� ���� � �������������� ���� �������� �� ����� ��� "-"
std::string checkData2()
{
	while (true)
	{
		unsigned count_char{ 0 };
		std::string check_AddNewElement{};
		std::getline(std::cin, check_AddNewElement);
		for (unsigned i = 0; i < check_AddNewElement.length(); i++)
		{
			count_char++;
			if (isdigit(check_AddNewElement[i]))
			{
				if (count_char == check_AddNewElement.length())
					return check_AddNewElement;
			}
			else
			{
				if ((check_AddNewElement.length() == 1) && (check_AddNewElement[i] == '-'))
				{
					return check_AddNewElement;
				}
				else
				{
					std::cout << "��� ����� ������ ������ ����� ��� ������ ������� \"-\". ��������� ����:" << std::endl;
					break;
				}
			}
		}
	}
}

//����� ���� ����������
unsigned getSortChoice()
{
	std::cout << "���������� ��: " << std::endl <<
		"�������� ������ ������\t\t- 1" << std::endl <<
		"���������� ������\t\t- 2" << std::endl <<
		"������ ������\t\t\t- 3" << std::endl;
	while (true)
	{
		double choice;
		std::cin >> choice;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "������ �����, �� ����� �� �����. ��������� ����:\n";
		}
		else if (static_cast<int>(choice) != choice || choice < 1 || choice > 3)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "����� ������ ����������� ����� �� 1 �� 3 � ������������ � ����������������� �������. ��������� ����:\n";
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return static_cast<unsigned>(choice);
		}
	}
}

//�������� � ������� swapData ����� � �������������� ���� �������� ������������ ��������� ����������
void SortChoice(unsigned choice, Trade* def_current, Trade* def_index)
{
	switch (choice)
	{
	case 1: swapData(def_current->data.TypeOfSecurities, def_index->data.TypeOfSecurities, def_current->data, def_index->data, choice); break;
	case 2: swapData(def_current->data.AmountOfDeals, def_index->data.AmountOfDeals, def_current->data, def_index->data, choice); break;
	case 3: swapData(def_current->data.TradingVolume, def_index->data.TradingVolume, def_current->data, def_index->data, choice); break;
	default: std::cout << "getSortChoice function fail!"; break;
	}
}

//������������ ������ � �������������� ����� ��������� - ����������
void swapData(const std::string& currentDataStr, const std::string& indexDataStr, TradeData& currentData, TradeData& indexData, unsigned choice)
{
	if (choice == 1 || choice == 3)
	{
		if (currentDataStr > indexDataStr)
		{
			TradeData temp{ currentData };
			currentData = indexData;
			indexData = temp;
		}
	}
	else if (choice == 2)
	{
		ComparisonNumber(currentDataStr, indexDataStr, currentData, indexData);
	}
}

//��������� ����� �� ������� ���� � �������������� ����� ��������� ��� ����������
void ComparisonNumber(const std::string& currentDataStr, const std::string& indexDataStr, TradeData& currentData, TradeData& indexData)
{
	if ((currentDataStr != "-") && (indexDataStr != "-"))
	{
		unsigned a = std::stoi(currentDataStr);
		unsigned b = std::stoi(indexDataStr);
		if (a > b)
		{
			TradeData temp{ currentData };
			currentData = indexData;
			indexData = temp;
		}
	}
}

//������ �������� � ������������ ������� � ������������
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 7). ��������� ����:" << std::endl;
		}
	}
}

//��������� ������ �������� � ������������ (��� ���������� � �������� ��������� � ������)
double GetNumber()
{
	while (true)
	{
		double num;
		std::cin >> num;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "������ �����, �� ����� �� �����. ��������� ����:\n";
		}
		else if (num != static_cast<int>(num))
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "�� ����� �� ����������� �����. ��������� ����:\n ";
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return num;
		}
	}
}


//���������������� �������
//���������������� ����
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) ���������� ����� ��������� ������." << std::endl <<
		"2) �������� �������� ������� � ������ �� ����������� ������. " << std::endl <<
		"3) ������� �������� ������� �� ������ �� ����������� ������." << std::endl <<
		"4) ���������� ������ (�� ���������� ����)." << std::endl <<
		"5) ������ ���� ��������� (����� �� �������)." << std::endl <<
		"6) ����� �������� ���� ��������� (��� �������� ��������� ����� ��������)." << std::endl <<
		"7) �����." << std::endl;
}

//������ ���������� ��������� � ������ � �������������
void case1(Trade* head)
{
	unsigned length = ListLength(head);
	std::cout << "����� ������ ������ �� ������ ������: " << length << std::endl;
}

//������ ���������� �������� � ������ � �������������
void case2(Trade* head)
{
	if (head != nullptr)
	{
		Trade* previous{ head }, * ea{};
		double num{};
		std::cout << "����� ������ ����������� ������ ��������� � ������ �� ������ �������� ����� �������?" << std::endl;
		bool inList{ false };
		while (!inList)
		{
			num = GetNumber();
			unsigned length = ListLength(head);
			if (num < 1 || num > length)
			{
				std::cout << "��� ��������� ��������� nullptr, �������� �� ������� ����������� ������ � ������ �� ����������." << std::endl;
			}
			else
			{
				inList = true;
			}
		}
		for (unsigned i = 1; i < num; i++)
		{
			previous = previous->next;
		}
		AddNewElement(previous, ea);
		std::cout << "����� " << num + 1 << "-� ������� ��� ��������." << std::endl;
	}
	else
	{
		CreateHeadOfList(head);
	}
}

//������ �������� �������� � ������ � �������������
void case3(Trade*& head)
{
	if (head != nullptr)
	{
		Trade* current{ head }, * search{ head };
		double num{};
		std::cout << "����� ������� �� ����������� ������ �� ������ �������?" << std::endl;
		bool inList{ false };
		unsigned length{};
		while (!inList)
		{
			num = GetNumber();
			length = ListLength(head);
			if (num < 1 || num > length)
			{
				std::cout << "��� ��������� ��������� nullptr, �������� �� ������� ����������� ������ � ������ �� ����������." << std::endl;
			}
			else
			{
				inList = true;
			}
		}
		for (unsigned i = 1; i < num; i++)
		{
			current = current->next;
		}
		if (num != 1)
		{
			DeleteElement(search, current);
		}
		else
		{
			while (search->next != head)
				search = search->next;
			if (length > 1)
			{
				search->next = head->next;
				head = head->next;
				delete current;
			}
			else
			{
				head = nullptr;
			}
		}
		std::cout << num << "-� ������� ��� ������." << std::endl;
	}
	else
	{
		std::cerr << "������ ����, ������ �������� �� ����� ���� ���������." << std::endl;
	}
}

//������ ���������� ������ � �������������
void case4(Trade* head)
{
	SortList(head);
}

//������ ������ ������ � �������������
void case5(const Trade* head)
{
	PrintList(head);
}

//�������� ������� � ���������������� - ������ ������ �������� ��������� � ������ � �������������
void case6(Trade* head)
{
	if (head != nullptr)
	{
		Trade* tail{ head };
		std::cout << "�� �������?" << std::endl <<
			"�� - 1" << std::endl <<
			"��� - 2" << std::endl;
		while (true)
		{
			char sm;
			std::cin >> sm;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (sm == '1')
			{
				do {
					tail->data.TypeOfSecurities = DEFAULT_TRADE.def_TypeOfSecurities;
					tail->data.AmountOfDeals = DEFAULT_TRADE.def_AmountOfDeals;
					tail->data.TradingVolume = DEFAULT_TRADE.def_TradingVolume;
					tail = tail->next;
				} while (tail != head);
				std::cout << "������ ��� ��������: ��� �������� ��������� ��������." << std::endl;
				break;
			}
			else if (sm == '2')
			{
				break;
			}
			else
			{
				std::cout << "������ �����. ������� 1 ��� 2: \n";
			}
		}
	}
	else
	{
		std::cerr << "������ ����, ������ �������� �� ����� ���� ���������." << std::endl;
	}
}