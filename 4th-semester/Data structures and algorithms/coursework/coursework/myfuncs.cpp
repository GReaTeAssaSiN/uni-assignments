#include <iostream>
#include <fstream>
#include <string>
#include "myfuncs.h"

/*ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ*/
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
//Преобразование введённой пользователем строки в число после проверки.
int convertStrToInt(std::string convertStr)
{
	double number{};
	for (int i{}; i < convertStr.length(); i++)
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
	return number;
}
//Проверка на соответствие символу латинского алфавита.
bool checkLatinSymbol(const char& specific_symbol)
{
	return (specific_symbol >= 'A' && specific_symbol <= 'Z' || specific_symbol >= 'a' && specific_symbol <= 'z') ? true : false;
}
//Проверка на соответствие символу русского алвафита.
bool checkRussianSymbol(const char& specific_symbol)
{
	return (specific_symbol >= 'А' && specific_symbol <= 'Я' || specific_symbol >= 'а' && specific_symbol <= 'я') ? true : false;
}
//Вывод пользовательского меню на экран.
void userMenu(const std::string& city_name)
{
	std::cout << "Вы находитесь в меню города " << city_name << "." << std::endl;
	std::cout << "Выберите действие, которое Вы хотите выполнить:\n" <<
		"1 - Вывести информацию о городсих улицах и домах, расположенных на них.\n" <<
		"2 - Добавить новую улицу в конец очереди (улица будет удаляться при удалении позже остальных).\n" <<
		"3 - Удалить улицу из начала очереди (улицу, добавленную ранее остальных).\n" <<
		"4 - Перейти к конкретной улице.\n" <<
		"5 - Сохранить построенную базу данных в указанный файл.\n" <<
		"6 - Загрузить базу данных из указанного файла.\n" <<
		"0 - Завершить программу." << std::endl;
}
//Вывод пользовательского подменю на экран.
void userSubmenu(const std::string& specific_city_street_name)
{
	std::cout << "Вы находитесь в меню улицы " << specific_city_street_name << "." << std::endl;
	std::cout << "Выберите действие, которое Вы хотите выполнить:\n" <<
		"1 - Проверить улицу на наличие хотя бы одного дома.\n" <<
		"2 - Добавить новый дом.\n" <<
		"3 - Удалить указанный дом.\n" <<
		"4 - Найти указанный дом.\n" <<
		"5 - Показать дома этой улицы.\n" <<
		"0 - Вернуться в главное меню города." << std::endl;
}
//Пользовательский выбор пункта меню/подменю.
char getUserChoice(const int& flag)
{
	std::cout << "Ваш выбор: ";
	while (true)
	{
		std::string user_choice{};
		std::getline(std::cin, user_choice);
		if (checkStrIsNumeric(user_choice) && (flag == 0 && convertStrToInt(user_choice) >= 0 && convertStrToInt(user_choice) <= 6 ||
			flag == 1 && convertStrToInt(user_choice) >= 0 && convertStrToInt(user_choice) <= 5))
			return user_choice[0];
		else
			std::cout << "Ошибка ввода. Вы должны ввести цифру, соответствующую пункту меню. Повторите ввод: ";
	}
}
//Вывод визуального разделения между действиями пользователя на консоль.
void printDashes()
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << std::endl;
}
//Проверка ввода названия улицы или города от пользователя.
bool checkCityOrStreetName(const std::string& check_str)
{
	bool latin_alphabet{}, russian_alphabet{};
	//Первая буква - прописная.
	if (check_str[0] >= 'A' && check_str[0] <= 'Z')
		latin_alphabet = true;
	else if (check_str[0] >= 'А' && check_str[0] <= 'Я')
		russian_alphabet = true;
	else
		return false;
	//Остальные буквы строчные или прописные, но принадлежат конкретному алфавиту. Может встречаться символ '-' или пробел.
	for (int i{ 1 }; i < check_str.size(); i++)
	{
		if (latin_alphabet && checkLatinSymbol(check_str[i]) || russian_alphabet && checkRussianSymbol(check_str[i]) || check_str[i] == '-' || check_str[i] == ' ')
		{
			if (check_str[i] == '-' || check_str[i] == ' ')
			{
				if (i != check_str.size() - 1)
				{
					if (!(check_str[static_cast<char>(i - 1)] >= 'a' && check_str[static_cast<char>(i - 1)] <= 'z' ||
						check_str[static_cast<char>(i - 1)] >= 'а' && check_str[static_cast<char>(i - 1)] <= 'я') ||
						!(check_str[static_cast<char>(i + 1)] >= 'A' && check_str[static_cast<char>(i + 1)] <= 'Z' ||
							check_str[static_cast<char>(i + 1)] >= 'А' && check_str[static_cast<char>(i + 1)] <= 'Я'))
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
//Проверка ввода типа строения дома от пользователя.
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
						check_str[static_cast<char>(i - 1)] >= 'а' && check_str[static_cast<char>(i - 1)] <= 'я' || 
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
//Получение названия города от пользователя.
std::string getCityNameFromUser()
{
	std::cout << "Введите название города, который Вы хотите добавить в базу данных: " << std::endl;
	while (true)
	{
		std::string city_name{};
		std::getline(std::cin, city_name);
		if (!checkCityOrStreetName(city_name) || city_name.empty())
		{
			system("cls");
			std::cout << "Ошибка ввода. Название города должно состоять из букв русского ИЛИ латинского алфавита, может содержать символы\n '-' и ' ', начинается с прописной буквы." << std::endl <<
				"Шаблонные примеры ввода: 'Название-Города', 'Название Города', 'City-Name', 'City Name'.\nПовторите ввод: ";
		}
		else	
			return city_name;
	}
}
//Получение названия улицы от пользователя.
std::string getStreetNameFromUser(City* current_city_ptr)
{
	std::cout << "Введите название улицы, которую необходимо добавить в город: ";
	while (true)
	{
		std::string name_of_new_street{};
		std::getline(std::cin, name_of_new_street);
		if (!name_of_new_street.empty() && checkCityOrStreetName(name_of_new_street) && current_city_ptr->transitionToTheStreetInTheCity(name_of_new_street) == nullptr)
			return name_of_new_street;
		else
		{
			system("cls");
			std::cout << "Ошибка ввода. Город не должен иметь улицы с одинаковыми названиями, без них или некорректными названиями.\n" <<
				"Шаблонные примеры ввода: 'Название-Улицы', 'Название Улицы', 'Street-Name', 'Street Name'." << std::endl << std::endl;
			showTheCity(current_city_ptr);
			std::cout << std::endl << "Повторите ввод названия улицы, которую необходимо добавить: ";
		}
	}
}
//Получение номера дома для добавления его на улицу от пользователя.
int getHouseNumberForAddingFromUser(Street* current_street_ptr)
{
	std::cout << "Введите номер дома, который хотите добавить на улицу " << current_street_ptr->getStreetName() << ": ";
	while (true)
	{
		std::string new_house_number{};
		std::getline(std::cin, new_house_number);
		if (checkStrIsNumeric(new_house_number) && convertStrToInt(new_house_number) >= 0 && current_street_ptr->houseSearchOnTheStreet(convertStrToInt(new_house_number)) == nullptr)
			return convertStrToInt(new_house_number);
		else
		{
			system("cls");
			std::cout << "Ошибка ввода. Номерами домов на улице являются целые неотрицательные числа, которые не должны повторяться." << std::endl;
			if (!current_street_ptr->theStreetIsEmpty())
				showTheStreet(current_street_ptr);
			std::cout << "Повторите ввод номера добавляемого дома: ";
		}
	}
}
//Получение типа строения дома от пользователя.
std::string getHouseTypeBuildingFromUser()
{
	std::cout << "Введите тип строения указанного дома: ";
	while (true)
	{
		std::string new_house_type_building{};
		std::getline(std::cin, new_house_type_building);
		if (!new_house_type_building.empty() && checkTypeBuildingFromUser(new_house_type_building))
			return new_house_type_building;
		else
			std::cout << "Тип строения дома указан некорректно. Шаблонные примеры ввода:\n'9-ТипСтроения'. '9 Типстроения', 'Тип Строения', 'Building Type'.\nПовторите ввод: ";
	}
}
//Получение номера дома для удаления его с улицы или поиска его на улице от пользователя.
int getHouseNumberForRemovingOrSearchingFromUser()
{
	while (true)
	{
		std::string specific_house_number{};
		std::getline(std::cin, specific_house_number);
		if (checkStrIsNumeric(specific_house_number))
			return convertStrToInt(specific_house_number);
		else
			std::cout << "Ошибка ввода. Вы должны ввести целое неотрицательное число. Повторите ввод номера дома: ";
	}
}
//Проверка указанного пользователем файла на возможность корректной загрузки данных.
bool protectInputFile(std::ifstream& f, const std::string& input_file_name)
{
	f.open(input_file_name);
	if (!f.fail())
	{
		std::string check_string{};
		std::getline(f, check_string);
		if (check_string.empty() || !checkCityOrStreetName(check_string))
		{
			std::cout << "Название города из файла " << input_file_name << " некорректное: пустое или задано не в верном формате.\nСчитать данный файл невозможно!" << std::endl;
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
						std::cout << "При считывании данных из файла " << input_file_name << " произошла ошибка! Проверьте корректность названия улиц в файле." << std::endl;
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
					//Индекс разделителя.
					int separator_index{ static_cast<int>(check_string.find('|')) };
					//Данные дома.
					std::string new_house_number{ check_string.substr(0, separator_index) }, new_house_building_type{ check_string.substr(separator_index + 1) };
					if (!checkStrIsNumeric(new_house_number) || new_house_building_type.empty() || !checkTypeBuildingFromUser(new_house_building_type))
					{
						std::cout << "При считывании данных из файла " << input_file_name << " произошла ошибка! Проверьте корректность данных о домах в файле." << std::endl;
						f.close();
						return false;
					}
				}
			}
			else
			{
				std::cout << "При считывании данных из файла " << input_file_name << " произошла ошибка! Проверьте отсутствие пустых строк в файле." << std::endl;
				f.close();
				return false;
			}
		}
		f.close();
		return true;
	}
	else
	{
		std::cout << "Не удалось открыть файл: " << input_file_name << "!" << std::endl;
		f.close();
		return false;
	}
}
//Получение от пользователя решения о замене названия города.
bool getUserWishesAboutCityName(City* current_city_ptr, const std::string& new_city_name)
{
	std::cout << "Вы хотите заменить название города " << current_city_ptr->getCityName() << " на название " << new_city_name << ", полученное из файла?" << std::endl;
	std::cout << "Да (yes)/ Нет (no): ";
	while (true)
	{
		std::string user_wishes{};
		std::getline(std::cin, user_wishes);
		if (user_wishes == "yes")
			return true;
		else if (user_wishes == "no")
			return false;
		else
			std::cout << "Ошибка ввода. Введите 'yes' или 'no': ";
	}
}

/*ФУНКЦИИ ОБРАБОТКИ ВЫБРАННОГО ПОЛЬЗОВАТЕЛЕМ ДЕЙСТВИЯ*/
/*Основное меню*/
//Дейтсвие '1'.
void showTheCity(City* current_city_ptr)
{
	std::cout << "Вот текущая информация о городе " << current_city_ptr->getCityName() << "." << std::endl;
	current_city_ptr->showTheCity();
}
//Дейтсвие '2'.
void addNewStreetInTheCity(City* current_city_ptr)
{
	current_city_ptr->addNewStreetToTheCity(getStreetNameFromUser(current_city_ptr));
	std::cout << "Улица была успешно добавлена в город." << std::endl;
}
//Дейтсвие '3'.
void removeThFirsteStreetFromTheCity(City* current_city_ptr)
{
	if (current_city_ptr->removeTheFirstStreetOfTheCity().empty())
		std::cout << "Город пуст. Выполнение данной операции невозможно." << std::endl;
}
//Дейтсвие '4'.
void selectionOfASpecificCityStreet(City* current_city_ptr)
{
	if (current_city_ptr->theCityIsEmpty())
		std::cout << "Город пуст. Выполнение данной операции невозможно." << std::endl;
	else
	{
		std::cout << "Введите название улицы города " << current_city_ptr->getCityName() << ", к которой хотите перейти: ";
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
			std::cout << "Вы вышли из меню улицы " << specific_city_street_ptr->getStreetName() << "." << std::endl;
		}
		else
			std::cout << "Данная улица отсутствует в городе. Выполнение данной операции невозможно." << std::endl;
	}
}
//Действие '5'.
void exportTheCityToFile(City* current_city_ptr)
{
	if (!current_city_ptr->theCityIsEmpty())
	{
		std::cout << "Вам необходимо ввести путь до файла вывода или нажать Enter, чтобы принять файл, указанный в в скобках." << std::endl;
		const std::string default_output_path{ "default_output_file.txt" };
		std::string output_file_name{};
		std::cout << "Задайте путь до файла вывода [" << default_output_path << "]: ";
		std::getline(std::cin, output_file_name);
		if (output_file_name.empty())
			output_file_name = default_output_path;
		std::ofstream fout;
		fout.open(output_file_name);
		if (!fout.fail())
		{
			//Заносим имя города в файл.
			fout << current_city_ptr->getCityName() << std::endl;
			//Заносим улицы и дома в файл.
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
			std::cout << "Данные успешно загружены в файл: " << output_file_name << std::endl;
		}
		else
			std::cout << "Не удалось открыть файл: " << output_file_name << "!" << std::endl;
		fout.close();
	}
	else
		std::cout << "Город пуст. Сохарнять данные в файл не имеет значения." << std::endl;
}
//Действие '6'.
void importTheCityFromFile(City* current_city_ptr)
{
	if (current_city_ptr->theCityIsEmpty())
	{
		std::cout << "Вам необходимо ввести путь до файла ввода или нажать Enter, чтобы принять файл, указанный в в скобках." << std::endl;
		const std::string default_input_path{ "default_input_file.txt" };
		std::string input_file_name{};
		std::cout << "Задайте путь до файла ввода [" << default_input_path << "]: ";
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
				std::cout << "Название города было успешно изменено." << std::endl;
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
					std::cout << "Новая улица была успешно добавлена в город." << std::endl;
				}
				else
				{
					if (buffer_string[buffer_string.size() - 1] != ';')
						reading_street = true;
					else
						buffer_string.erase(buffer_string.size() - 1);
					//Индекс разделителя.
					int separator_index{ static_cast<int>(buffer_string.find('|')) };
					//Данные дома.
					int new_house_number{ convertStrToInt(buffer_string.substr(0, separator_index)) };
					std::string new_house_building_type{ buffer_string.substr(separator_index + 1) };
					current_city_ptr->getPLast()->addNewHouseToTheStreet(new_house_number, new_house_building_type);
					std::cout << "Новый дом был успешно добавлен в город на соответствующую улицу." << std::endl;
				}
			}
			std::cout << "Все данные города из указанного файла были успешно загружены." << std::endl;
			fin.close();
		}
	}
	else
		std::cout << "Город не пуст. Загрузка данных из файла не может быть выполнена." << std::endl;
}

/*Подменю*/
//Дейтсвие '4'->'1'.
void checkTheStreet(Street* current_street_ptr)
{
	if (current_street_ptr->theStreetIsEmpty())
		std::cout << "Улица " << current_street_ptr->getStreetName() << ": дома отсутствуют." << std::endl;
	else
		std::cout << "Улица " << current_street_ptr->getStreetName() << ": дом(-а) присутствуют." << std::endl;
}
//Дейтсвие '4'->'2'.
void addTheHouse(Street* current_street_ptr)
{
	current_street_ptr->addNewHouseToTheStreet(getHouseNumberForAddingFromUser(current_street_ptr), getHouseTypeBuildingFromUser());
	system("cls");
	std::cout << "На улицу " << current_street_ptr->getStreetName() << " был успешно добавлен новый дом." << std::endl;
}
//Дейтсвие '4'->'3'.
void removeTheHouse(Street* current_street_ptr)
{
	if (!current_street_ptr->theStreetIsEmpty())
	{
		std::cout << "Введите номер дома, который хотите удалить с улицы " << current_street_ptr->getStreetName() << ": ";
		if (current_street_ptr->removeTheHouseFromTheStreet(getHouseNumberForRemovingOrSearchingFromUser()) == -1)
			std::cout << "На улице " << current_street_ptr->getStreetName() << " нет дома с указанным номером." << std::endl;
	}
	else
		std::cout << "Улица " << current_street_ptr->getStreetName() << " пуста. Операция удаления дома невозможна." << std::endl;
}
//Дейтсвие '4'->'4'.
void searchTheHouse(Street* current_street_ptr)
{
	if (!current_street_ptr->theStreetIsEmpty())
	{
		std::cout << "Введите номер дома, который хотите найти на улице " << current_street_ptr->getStreetName() << ": ";
		House* searched_house_ptr{ current_street_ptr->houseSearchOnTheStreet(getHouseNumberForRemovingOrSearchingFromUser()) };
		if (searched_house_ptr == nullptr)
			std::cout << "На улице " << current_street_ptr->getStreetName() << " нет дома с указанным номером." << std::endl;
		else
			std::cout << "На улице " << current_street_ptr->getStreetName() << " есть дом с номером " << searched_house_ptr->getPNext()->getHouseNumber() <<
			", тип строения дома: " << searched_house_ptr->getPNext()->getBuildingType() << "." << std::endl;
	}
	else
		std::cout << "Улица " << current_street_ptr->getStreetName() << " пуста. Операция поиска дома невозможна." << std::endl;
}
//Действие '4'->'5'.
void showTheStreet(Street* current_street_ptr)
{
	std::cout << "Вот информация о домах на улице " << current_street_ptr->getStreetName() << "." << std::endl;
	current_street_ptr->showHousesOnTheStreet();
}