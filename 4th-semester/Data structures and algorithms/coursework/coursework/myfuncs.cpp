#include <iostream>
#include <fstream>
#include <string>
#include "myfuncs.h"

/*���������������� �������*/
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
//�������������� �������� ������������� ������ � ����� ����� ��������.
int convertStrToInt(std::string convertStr)
{
	double number{};
	for (int i{}; i < convertStr.length(); i++)
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
	return number;
}
//�������� �� ������������ ������� ���������� ��������.
bool checkLatinSymbol(const char& specific_symbol)
{
	return (specific_symbol >= 'A' && specific_symbol <= 'Z' || specific_symbol >= 'a' && specific_symbol <= 'z') ? true : false;
}
//�������� �� ������������ ������� �������� ��������.
bool checkRussianSymbol(const char& specific_symbol)
{
	return (specific_symbol >= '�' && specific_symbol <= '�' || specific_symbol >= '�' && specific_symbol <= '�') ? true : false;
}
//����� ����������������� ���� �� �����.
void userMenu(const std::string& city_name)
{
	std::cout << "�� ���������� � ���� ������ " << city_name << "." << std::endl;
	std::cout << "�������� ��������, ������� �� ������ ���������:\n" <<
		"1 - ������� ���������� � �������� ������ � �����, ������������� �� ���.\n" <<
		"2 - �������� ����� ����� � ����� ������� (����� ����� ��������� ��� �������� ����� ���������).\n" <<
		"3 - ������� ����� �� ������ ������� (�����, ����������� ����� ���������).\n" <<
		"4 - ������� � ���������� �����.\n" <<
		"5 - ��������� ����������� ���� ������ � ��������� ����.\n" <<
		"6 - ��������� ���� ������ �� ���������� �����.\n" <<
		"0 - ��������� ���������." << std::endl;
}
//����� ����������������� ������� �� �����.
void userSubmenu(const std::string& specific_city_street_name)
{
	std::cout << "�� ���������� � ���� ����� " << specific_city_street_name << "." << std::endl;
	std::cout << "�������� ��������, ������� �� ������ ���������:\n" <<
		"1 - ��������� ����� �� ������� ���� �� ������ ����.\n" <<
		"2 - �������� ����� ���.\n" <<
		"3 - ������� ��������� ���.\n" <<
		"4 - ����� ��������� ���.\n" <<
		"5 - �������� ���� ���� �����.\n" <<
		"0 - ��������� � ������� ���� ������." << std::endl;
}
//���������������� ����� ������ ����/�������.
char getUserChoice(const int& flag)
{
	std::cout << "��� �����: ";
	while (true)
	{
		std::string user_choice{};
		std::getline(std::cin, user_choice);
		if (checkStrIsNumeric(user_choice) && (flag == 0 && convertStrToInt(user_choice) >= 0 && convertStrToInt(user_choice) <= 6 ||
			flag == 1 && convertStrToInt(user_choice) >= 0 && convertStrToInt(user_choice) <= 5))
			return user_choice[0];
		else
			std::cout << "������ �����. �� ������ ������ �����, ��������������� ������ ����. ��������� ����: ";
	}
}
//����� ����������� ���������� ����� ���������� ������������ �� �������.
void printDashes()
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << std::endl;
}
//�������� ����� �������� ����� ��� ������ �� ������������.
bool checkCityOrStreetName(const std::string& check_str)
{
	bool latin_alphabet{}, russian_alphabet{};
	//������ ����� - ���������.
	if (check_str[0] >= 'A' && check_str[0] <= 'Z')
		latin_alphabet = true;
	else if (check_str[0] >= '�' && check_str[0] <= '�')
		russian_alphabet = true;
	else
		return false;
	//��������� ����� �������� ��� ���������, �� ����������� ����������� ��������. ����� ����������� ������ '-' ��� ������.
	for (int i{ 1 }; i < check_str.size(); i++)
	{
		if (latin_alphabet && checkLatinSymbol(check_str[i]) || russian_alphabet && checkRussianSymbol(check_str[i]) || check_str[i] == '-' || check_str[i] == ' ')
		{
			if (check_str[i] == '-' || check_str[i] == ' ')
			{
				if (i != check_str.size() - 1)
				{
					if (!(check_str[static_cast<char>(i - 1)] >= 'a' && check_str[static_cast<char>(i - 1)] <= 'z' ||
						check_str[static_cast<char>(i - 1)] >= '�' && check_str[static_cast<char>(i - 1)] <= '�') ||
						!(check_str[static_cast<char>(i + 1)] >= 'A' && check_str[static_cast<char>(i + 1)] <= 'Z' ||
							check_str[static_cast<char>(i + 1)] >= '�' && check_str[static_cast<char>(i + 1)] <= '�'))
					{
						return false;
					}
				}
				else
					return false;
			}
		}
		else
			return false;
	}
	return true;
}
//�������� ����� ���� �������� ���� �� ������������.
bool checkTypeBuildingFromUser(const std::string& check_str)
{
	bool latin_alphabet{}, russian_alphabet{};
	if (check_str[0] == '-' || check_str[0] == ' ')
		return false;
	for (int i{}; i < check_str.size(); i++)
	{
		if (check_str[i] >= '0' && check_str[i] <= '9' || check_str[i] == ' ' || check_str[i] == '-')
			continue;
		else
		{
			if (checkLatinSymbol(check_str[i]))
				latin_alphabet = true;
			else if (checkRussianSymbol(check_str[i]))
				russian_alphabet = true;
			else
				return false;
			break;
		}
	}
	for (int i{ 1 }; i < check_str.size(); i++)
	{
		if (latin_alphabet && checkLatinSymbol(check_str[i]) || russian_alphabet && checkRussianSymbol(check_str[i]) || check_str[i] == '-' || check_str[i] == ' ' || 
			check_str[i] >= '0' && check_str[i] <= '9')
		{
			if (check_str[i] == '-' || check_str[i] == ' ')
			{
				if (i != check_str.size() - 1)
				{
					if (!(check_str[static_cast<char>(i - 1)] >= 'a' && check_str[static_cast<char>(i - 1)] <= 'z' ||
						check_str[static_cast<char>(i - 1)] >= '�' && check_str[static_cast<char>(i - 1)] <= '�' || 
						check_str[static_cast<char>(i - 1)] >= '0' && check_str[static_cast<char>(i - 1)] <= '9') ||
						!(checkLatinSymbol(check_str[static_cast<char>(i + 1)]) || checkRussianSymbol(check_str[static_cast<char>(i + 1)])))
					{
						return false;
					}
				}
				else
					return false;
			}
		}
		else
			return false;
	}
	return true;
}
//��������� �������� ������ �� ������������.
std::string getCityNameFromUser()
{
	std::cout << "������� �������� ������, ������� �� ������ �������� � ���� ������: " << std::endl;
	while (true)
	{
		std::string city_name{};
		std::getline(std::cin, city_name);
		if (!checkCityOrStreetName(city_name) || city_name.empty())
		{
			system("cls");
			std::cout << "������ �����. �������� ������ ������ �������� �� ���� �������� ��� ���������� ��������, ����� ��������� �������\n '-' � ' ', ���������� � ��������� �����." << std::endl <<
				"��������� ������� �����: '��������-������', '�������� ������', 'City-Name', 'City Name'.\n��������� ����: ";
		}
		else	
			return city_name;
	}
}
//��������� �������� ����� �� ������������.
std::string getStreetNameFromUser(City* current_city_ptr)
{
	std::cout << "������� �������� �����, ������� ���������� �������� � �����: ";
	while (true)
	{
		std::string name_of_new_street{};
		std::getline(std::cin, name_of_new_street);
		if (!name_of_new_street.empty() && checkCityOrStreetName(name_of_new_street) && current_city_ptr->transitionToTheStreetInTheCity(name_of_new_street) == nullptr)
			return name_of_new_street;
		else
		{
			system("cls");
			std::cout << "������ �����. ����� �� ������ ����� ����� � ����������� ����������, ��� ��� ��� ������������� ����������.\n" <<
				"��������� ������� �����: '��������-�����', '�������� �����', 'Street-Name', 'Street Name'." << std::endl << std::endl;
			showTheCity(current_city_ptr);
			std::cout << std::endl << "��������� ���� �������� �����, ������� ���������� ��������: ";
		}
	}
}
//��������� ������ ���� ��� ���������� ��� �� ����� �� ������������.
int getHouseNumberForAddingFromUser(Street* current_street_ptr)
{
	std::cout << "������� ����� ����, ������� ������ �������� �� ����� " << current_street_ptr->getStreetName() << ": ";
	while (true)
	{
		std::string new_house_number{};
		std::getline(std::cin, new_house_number);
		if (checkStrIsNumeric(new_house_number) && convertStrToInt(new_house_number) >= 0 && current_street_ptr->houseSearchOnTheStreet(convertStrToInt(new_house_number)) == nullptr)
			return convertStrToInt(new_house_number);
		else
		{
			system("cls");
			std::cout << "������ �����. �������� ����� �� ����� �������� ����� ��������������� �����, ������� �� ������ �����������." << std::endl;
			if (!current_street_ptr->theStreetIsEmpty())
				showTheStreet(current_street_ptr);
			std::cout << "��������� ���� ������ ������������ ����: ";
		}
	}
}
//��������� ���� �������� ���� �� ������������.
std::string getHouseTypeBuildingFromUser()
{
	std::cout << "������� ��� �������� ���������� ����: ";
	while (true)
	{
		std::string new_house_type_building{};
		std::getline(std::cin, new_house_type_building);
		if (!new_house_type_building.empty() && checkTypeBuildingFromUser(new_house_type_building))
			return new_house_type_building;
		else
			std::cout << "��� �������� ���� ������ �����������. ��������� ������� �����:\n'9-�����������'. '9 �����������', '��� ��������', 'Building Type'.\n��������� ����: ";
	}
}
//��������� ������ ���� ��� �������� ��� � ����� ��� ������ ��� �� ����� �� ������������.
int getHouseNumberForRemovingOrSearchingFromUser()
{
	while (true)
	{
		std::string specific_house_number{};
		std::getline(std::cin, specific_house_number);
		if (checkStrIsNumeric(specific_house_number))
			return convertStrToInt(specific_house_number);
		else
			std::cout << "������ �����. �� ������ ������ ����� ��������������� �����. ��������� ���� ������ ����: ";
	}
}
//�������� ���������� ������������� ����� �� ����������� ���������� �������� ������.
bool protectInputFile(std::ifstream& f, const std::string& input_file_name)
{
	f.open(input_file_name);
	if (!f.fail())
	{
		std::string check_string{};
		std::getline(f, check_string);
		if (check_string.empty() || !checkCityOrStreetName(check_string))
		{
			std::cout << "�������� ������ �� ����� " << input_file_name << " ������������: ������ ��� ������ �� � ������ �������.\n������� ������ ���� ����������!" << std::endl;
			f.close();
			return false;
		}
		bool reading_street{ true };
		while (std::getline(f, check_string))
		{
			if (check_string.size() >= 1)
			{
				if (reading_street)
				{
					if (check_string[check_string.size() - 1] == ':')
					{
						check_string = check_string.erase(check_string.size() - 1);
						reading_street = false;
					}
					if (check_string.empty() || !checkCityOrStreetName(check_string))
					{
						std::cout << "��� ���������� ������ �� ����� " << input_file_name << " ��������� ������! ��������� ������������ �������� ���� � �����." << std::endl;
						f.close();
						return false;
					}
				}
				else
				{
					if (check_string[check_string.size() - 1] != ';')
						reading_street = true;
					else
						check_string.erase(check_string.size() - 1);
					//������ �����������.
					int separator_index{ static_cast<int>(check_string.find('|')) };
					//������ ����.
					std::string new_house_number{ check_string.substr(0, separator_index) }, new_house_building_type{ check_string.substr(separator_index + 1) };
					if (!checkStrIsNumeric(new_house_number) || new_house_building_type.empty() || !checkTypeBuildingFromUser(new_house_building_type))
					{
						std::cout << "��� ���������� ������ �� ����� " << input_file_name << " ��������� ������! ��������� ������������ ������ � ����� � �����." << std::endl;
						f.close();
						return false;
					}
				}
			}
			else
			{
				std::cout << "��� ���������� ������ �� ����� " << input_file_name << " ��������� ������! ��������� ���������� ������ ����� � �����." << std::endl;
				f.close();
				return false;
			}
		}
		f.close();
		return true;
	}
	else
	{
		std::cout << "�� ������� ������� ����: " << input_file_name << "!" << std::endl;
		f.close();
		return false;
	}
}
//��������� �� ������������ ������� � ������ �������� ������.
bool getUserWishesAboutCityName(City* current_city_ptr, const std::string& new_city_name)
{
	std::cout << "�� ������ �������� �������� ������ " << current_city_ptr->getCityName() << " �� �������� " << new_city_name << ", ���������� �� �����?" << std::endl;
	std::cout << "�� (yes)/ ��� (no): ";
	while (true)
	{
		std::string user_wishes{};
		std::getline(std::cin, user_wishes);
		if (user_wishes == "yes")
			return true;
		else if (user_wishes == "no")
			return false;
		else
			std::cout << "������ �����. ������� 'yes' ��� 'no': ";
	}
}

/*������� ��������� ���������� ������������� ��������*/
/*�������� ����*/
//�������� '1'.
void showTheCity(City* current_city_ptr)
{
	std::cout << "��� ������� ���������� � ������ " << current_city_ptr->getCityName() << "." << std::endl;
	current_city_ptr->showTheCity();
}
//�������� '2'.
void addNewStreetInTheCity(City* current_city_ptr)
{
	current_city_ptr->addNewStreetToTheCity(getStreetNameFromUser(current_city_ptr));
	std::cout << "����� ���� ������� ��������� � �����." << std::endl;
}
//�������� '3'.
void removeThFirsteStreetFromTheCity(City* current_city_ptr)
{
	if (current_city_ptr->removeTheFirstStreetOfTheCity().empty())
		std::cout << "����� ����. ���������� ������ �������� ����������." << std::endl;
}
//�������� '4'.
void selectionOfASpecificCityStreet(City* current_city_ptr)
{
	if (current_city_ptr->theCityIsEmpty())
		std::cout << "����� ����. ���������� ������ �������� ����������." << std::endl;
	else
	{
		std::cout << "������� �������� ����� ������ " << current_city_ptr->getCityName() << ", � ������� ������ �������: ";
		std::string specific_city_street_name{};
		std::getline(std::cin, specific_city_street_name);
		Street* specific_city_street_ptr{ current_city_ptr->transitionToTheStreetInTheCity(specific_city_street_name) };
		if (specific_city_street_ptr != nullptr)
		{
			system("cls");
			bool cycle{ true };
			while (cycle)
			{
				userSubmenu(specific_city_street_name);
				char user_choice{ getUserChoice(1) };
				system("cls");
				switch (user_choice)
				{
				case '1':
					checkTheStreet(specific_city_street_ptr);
					break;
				case '2':
					addTheHouse(specific_city_street_ptr);
					break;
				case '3':
					removeTheHouse(specific_city_street_ptr);
					break;
				case '4':
					searchTheHouse(specific_city_street_ptr);
					break;
				case '5':
					showTheStreet(specific_city_street_ptr);
					break;
				case '0':
					cycle = false;
					break;
				default:;
				}
				printDashes();
			}
			std::cout << "�� ����� �� ���� ����� " << specific_city_street_ptr->getStreetName() << "." << std::endl;
		}
		else
			std::cout << "������ ����� ����������� � ������. ���������� ������ �������� ����������." << std::endl;
	}
}
//�������� '5'.
void exportTheCityToFile(City* current_city_ptr)
{
	if (!current_city_ptr->theCityIsEmpty())
	{
		std::cout << "��� ���������� ������ ���� �� ����� ������ ��� ������ Enter, ����� ������� ����, ��������� � � �������." << std::endl;
		const std::string default_output_path{ "default_output_file.txt" };
		std::string output_file_name{};
		std::cout << "������� ���� �� ����� ������ [" << default_output_path << "]: ";
		std::getline(std::cin, output_file_name);
		if (output_file_name.empty())
			output_file_name = default_output_path;
		std::ofstream fout;
		fout.open(output_file_name);
		if (!fout.fail())
		{
			//������� ��� ������ � ����.
			fout << current_city_ptr->getCityName() << std::endl;
			//������� ����� � ���� � ����.
			Street* temp_street_ptr{ current_city_ptr->getPFirst()->getPNext() };
			while (temp_street_ptr != current_city_ptr->getPFirst())
			{
				fout << temp_street_ptr->getStreetName();
				if (!temp_street_ptr->theStreetIsEmpty())
				{
					fout << ":" << std::endl;
					House* temp_house_ptr{ temp_street_ptr->getHeadHousePtr()->getPNext() };
					while (temp_house_ptr != temp_street_ptr->getHeadHousePtr())
					{
						fout << temp_house_ptr->getHouseNumber() << "|" << temp_house_ptr->getBuildingType();
						if (temp_house_ptr->getPNext() != temp_street_ptr->getHeadHousePtr())
							fout << ";";
						fout << std::endl;
						temp_house_ptr = temp_house_ptr->getPNext();
					}
				}
				else
					fout << std::endl;
				temp_street_ptr = temp_street_ptr->getPNext();
			}
			std::cout << "������ ������� ��������� � ����: " << output_file_name << std::endl;
		}
		else
			std::cout << "�� ������� ������� ����: " << output_file_name << "!" << std::endl;
		fout.close();
	}
	else
		std::cout << "����� ����. ��������� ������ � ���� �� ����� ��������." << std::endl;
}
//�������� '6'.
void importTheCityFromFile(City* current_city_ptr)
{
	if (current_city_ptr->theCityIsEmpty())
	{
		std::cout << "��� ���������� ������ ���� �� ����� ����� ��� ������ Enter, ����� ������� ����, ��������� � � �������." << std::endl;
		const std::string default_input_path{ "default_input_file.txt" };
		std::string input_file_name{};
		std::cout << "������� ���� �� ����� ����� [" << default_input_path << "]: ";
		std::getline(std::cin, input_file_name);
		if (input_file_name.empty())
			input_file_name = default_input_path;
		std::ifstream fin{};
		if (protectInputFile(fin, input_file_name))
		{
			fin.open(input_file_name);
			std::string buffer_string{};
			std::getline(fin, buffer_string);
			if (getUserWishesAboutCityName(current_city_ptr, buffer_string))
			{
				current_city_ptr->setCityName(buffer_string);
				std::cout << "�������� ������ ���� ������� ��������." << std::endl;
			}
			bool reading_street{ true };
			while (std::getline(fin, buffer_string))
			{
				if (reading_street)
				{
					if (buffer_string[buffer_string.size() - 1] == ':')
					{
						current_city_ptr->addNewStreetToTheCity(buffer_string.erase(buffer_string.size() - 1));
						reading_street = false;
					}
					else
						current_city_ptr->addNewStreetToTheCity(buffer_string);
					std::cout << "����� ����� ���� ������� ��������� � �����." << std::endl;
				}
				else
				{
					if (buffer_string[buffer_string.size() - 1] != ';')
						reading_street = true;
					else
						buffer_string.erase(buffer_string.size() - 1);
					//������ �����������.
					int separator_index{ static_cast<int>(buffer_string.find('|')) };
					//������ ����.
					int new_house_number{ convertStrToInt(buffer_string.substr(0, separator_index)) };
					std::string new_house_building_type{ buffer_string.substr(separator_index + 1) };
					current_city_ptr->getPLast()->addNewHouseToTheStreet(new_house_number, new_house_building_type);
					std::cout << "����� ��� ��� ������� �������� � ����� �� ��������������� �����." << std::endl;
				}
			}
			std::cout << "��� ������ ������ �� ���������� ����� ���� ������� ���������." << std::endl;
			fin.close();
		}
	}
	else
		std::cout << "����� �� ����. �������� ������ �� ����� �� ����� ���� ���������." << std::endl;
}

/*�������*/
//�������� '4'->'1'.
void checkTheStreet(Street* current_street_ptr)
{
	if (current_street_ptr->theStreetIsEmpty())
		std::cout << "����� " << current_street_ptr->getStreetName() << ": ���� �����������." << std::endl;
	else
		std::cout << "����� " << current_street_ptr->getStreetName() << ": ���(-�) ������������." << std::endl;
}
//�������� '4'->'2'.
void addTheHouse(Street* current_street_ptr)
{
	current_street_ptr->addNewHouseToTheStreet(getHouseNumberForAddingFromUser(current_street_ptr), getHouseTypeBuildingFromUser());
	system("cls");
	std::cout << "�� ����� " << current_street_ptr->getStreetName() << " ��� ������� �������� ����� ���." << std::endl;
}
//�������� '4'->'3'.
void removeTheHouse(Street* current_street_ptr)
{
	if (!current_street_ptr->theStreetIsEmpty())
	{
		std::cout << "������� ����� ����, ������� ������ ������� � ����� " << current_street_ptr->getStreetName() << ": ";
		if (current_street_ptr->removeTheHouseFromTheStreet(getHouseNumberForRemovingOrSearchingFromUser()) == -1)
			std::cout << "�� ����� " << current_street_ptr->getStreetName() << " ��� ���� � ��������� �������." << std::endl;
	}
	else
		std::cout << "����� " << current_street_ptr->getStreetName() << " �����. �������� �������� ���� ����������." << std::endl;
}
//�������� '4'->'4'.
void searchTheHouse(Street* current_street_ptr)
{
	if (!current_street_ptr->theStreetIsEmpty())
	{
		std::cout << "������� ����� ����, ������� ������ ����� �� ����� " << current_street_ptr->getStreetName() << ": ";
		House* searched_house_ptr{ current_street_ptr->houseSearchOnTheStreet(getHouseNumberForRemovingOrSearchingFromUser()) };
		if (searched_house_ptr == nullptr)
			std::cout << "�� ����� " << current_street_ptr->getStreetName() << " ��� ���� � ��������� �������." << std::endl;
		else
			std::cout << "�� ����� " << current_street_ptr->getStreetName() << " ���� ��� � ������� " << searched_house_ptr->getPNext()->getHouseNumber() <<
			", ��� �������� ����: " << searched_house_ptr->getPNext()->getBuildingType() << "." << std::endl;
	}
	else
		std::cout << "����� " << current_street_ptr->getStreetName() << " �����. �������� ������ ���� ����������." << std::endl;
}
//�������� '4'->'5'.
void showTheStreet(Street* current_street_ptr)
{
	std::cout << "��� ���������� � ����� �� ����� " << current_street_ptr->getStreetName() << "." << std::endl;
	current_street_ptr->showHousesOnTheStreet();
}