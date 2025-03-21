#include <iostream>
#include <sstream>
#include <fstream>
#include "mystructs.h"
#include "myfuncs.h"
#include "ArrayThreeStrings.h"

//ОСНОВНЫЕ ФУНКЦИИ
//Вывод данных из файла в динамический список
bool LoadingList(const std::string fileName, Trade*& head)
{
	std::ifstream out_DataFile(fileName);
	if (!out_DataFile)
	{
		std::cerr << "Не удалось открыть файл!" << std::endl;
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

//Вывод данных из динамического списка в файл
bool UnloadingList(const std::string fileName, Trade* head)
{
	Trade* tail{ head };
	std::ofstream in_DataFile(fileName);
	if (!in_DataFile)
	{
		std::cerr << "Не удалось открыть файл!" << std::endl;
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
				std::cout << "Данные о ценной бумаге " << clean_ptr->data.TypeOfSecurities << ",... выгружены и удалены из оперативной памяти." << std::endl;
				delete clean_ptr;
				if (tail == head)
					break;
			}
		}

		in_DataFile.close();
		return true;
	}
}

//Для case1 - количество элементов динамического списка
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

//Для case2 - добавить новый элемент динамический в список
void AddNewElement(Trade*& previous, Trade* ea)
{
	std::string AddNewElement{};
	Trade* after{};

	ea = new Trade{};
	after = previous->next;
	previous->next = ea;
	std::cout << "Введите данные о новом элементе:" << std::endl;

	std::cout << "<Название ценной бумаги>: ";
	std::getline(std::cin, AddNewElement);
	ea->data.TypeOfSecurities = AddNewElement;

	std::cout << "<Количество сделок>: ";
	AddNewElement = checkData2();
	ea->data.AmountOfDeals = AddNewElement;

	std::cout << "<Объём продаж>. ";
	if (!FastInput_TradingVolume(ea, AddNewElement))
	{
		std::cout << "<Объём продаж>: ";
		std::getline(std::cin, AddNewElement);
		ea->data.TradingVolume = AddNewElement;
	}

	ea->next = after;
}

//Для case3 - удалить элемент из списка
void DeleteElement(Trade* search_prev_del, const Trade* ed)
{
	while (search_prev_del->next != ed)
	{
		search_prev_del = search_prev_del->next;
	}
	search_prev_del->next = ed->next;
	delete ed;
}

//Для case4 - отсортировать динамический список
void SortList(Trade* head)
{
	if (head == nullptr)
	{
		std::cout << "Список пуст." << std::endl;
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

//Для case5 - печать списка на консоль
void PrintList(const Trade* head)
{
	const Trade* tail{ head };
	if (head != nullptr)
	{
		int index_number{};
		std::cout << "____________________ Ваш список: ____________________" << std::endl;
		do {
			index_number++;
			std::cout << index_number << ") " << tail->data.TypeOfSecurities << ";" << tail->data.AmountOfDeals << ";" << tail->data.TradingVolume << std::endl;
			tail = tail->next;
		} while (tail != head);
	}
	else
	{
		std::cout << "Список пуст." << std::endl;
	}
}


//ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
//Построчное чтение данных из файла \, либо запрос о введении корня динамического списка, если файл пустой
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
			std::cout << "Ваш файл пустой. Вы хотите ввести первый элемент?" << std::endl <<
				"Да - 1" << std::endl <<
				"Нет - 0" << std::endl;
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
					std::cerr << "Ошибка ввода. Введите 0 или 1. Повторите ввод: ";
				}
			}
		}
	}
	return true;
}

// Проверка, чтобы в файле было 3 поля, 2-ое из которых - число
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
						std::cout << count << "-й элемент имеет неправильные данные во 2-м информационном поле." << std::endl;
						return false;
					}
				}
			}
		}
	}
	if (index_field != 3)
	{
		std::cout << count << "-й элемент имеет неправильно количество данных информационного поля." << std::endl;
		return false;
	}
	return true;
}

//Быстрый ввод 3-го поля в информационном поле элемента <Объём продаж>
bool FastInput_TradingVolume(Trade* ea, std::string fast_AddNewElement)
{
	std::cout << "Выберите один из следуюших вариантов или введите свой, отказавшись от выбора." << std::endl <<
		"Очень маленький -\t 1" << std::endl <<
		"Маленький \t-\t 2" << std::endl <<
		"Средний \t-\t 3" << std::endl <<
		"Большой \t-\t 4" << std::endl <<
		"Очень большой \t-\t 5" << std::endl <<
		"Ввести свой \t-\t 6" << std::endl;
	while (true)
	{
		{
			char sm;
			std::cin >> sm;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			switch (sm)
			{
			case '1':
				fast_AddNewElement = "Очень маленький";
				ea->data.TradingVolume = fast_AddNewElement;
				return true;
			case '2':
				fast_AddNewElement = "Маленький";
				ea->data.TradingVolume = fast_AddNewElement;
				return true;
			case '3':
				fast_AddNewElement = "Средний";
				ea->data.TradingVolume = fast_AddNewElement;
				return true;
			case '4':
				fast_AddNewElement = "Большой";
				ea->data.TradingVolume = fast_AddNewElement;
				return true;
			case '5':
				fast_AddNewElement = "Очень большой";
				ea->data.TradingVolume = fast_AddNewElement;
				return true;
			case '6':
				return false;
			default:
				std::cout << "Введите один из вариантов выше (цифру). Повторите ввод:" << std::endl;
			}
		}
	}
}

//Получение нового элемента по указателю и информационному полю
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

//Обеспечение записи данных в информационное поле элемента динамического списка с привязыванием их к указателю
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

//Создание корня списка
void CreateHeadOfList(Trade*& head)
{
	std::string AddDataToHead{};
	head = new Trade{};
	std::cout << "Введите данные корневого элемента: " << std::endl;
	std::cout << "<Название ценной бумаги>: ";
	std::getline(std::cin, AddDataToHead);
	head->data.TypeOfSecurities = AddDataToHead;

	std::cout << "<Количество сделок>: ";
	AddDataToHead = checkData2();
	head->data.AmountOfDeals = AddDataToHead;

	std::cout << "<Объём продаж>: ";
	if (!FastInput_TradingVolume(head, AddDataToHead))
	{
		std::getline(std::cin, AddDataToHead);
		head->data.TradingVolume = AddDataToHead;
	}

	head->next = head;
}

//Проверка 2-го поля в информационном поле элемента на число или "-"
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
					std::cout << "Вам нужно ввести только число или просто прочерк \"-\". Повторите ввод:" << std::endl;
					break;
				}
			}
		}
	}
}

//Выбор поля сортировки
unsigned getSortChoice()
{
	std::cout << "Сортировка по: " << std::endl <<
		"Названию ценной бумаги\t\t- 1" << std::endl <<
		"Количеству сделок\t\t- 2" << std::endl <<
		"Объёму продаж\t\t\t- 3" << std::endl;
	while (true)
	{
		double choice;
		std::cin >> choice;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Ошибка ввода, Вы ввели не число. Повторите ввод:\n";
		}
		else if (static_cast<int>(choice) != choice || choice < 1 || choice > 3)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Нужно ввести натуральное число от 1 до 3 в соответствии с вышеперечисленным выбором. Повторите ввод:\n";
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return static_cast<unsigned>(choice);
		}
	}
}

//Передача в функцию swapData полей в информационном поле элемента относительно выбранной сортировки
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

//Перестановка данных в информационных полях элементов - сортировка
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

//Сравнение чисел из второго поля в информационных полях элементов для сортировки
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

//Запрос дейтсвий с динамическим списком у пользователя
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 7). Повторите ввод:" << std::endl;
		}
	}
}

//Получение номера элемента у пользователя (для добавления и удаления элементов в списке)
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
			std::cout << "Ошибка ввода, Вы ввели не число. Повторите ввод:\n";
		}
		else if (num != static_cast<int>(num))
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Вы ввели не натуральное число. Повторите ввод:\n ";
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return num;
		}
	}
}


//ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ
//Пользовательское меню
void MenuForChoices()
{
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1) Подсчитать число элементов списка." << std::endl <<
		"2) Добавить заданный элемент в список по порядковому номеру. " << std::endl <<
		"3) Удалить заданный элемент из списка по порядковому номеру." << std::endl <<
		"4) Сортировка списка (по указанному полю)." << std::endl <<
		"5) Печать всех элементов (вывод на консоль)." << std::endl <<
		"6) Сброс значений всех элементов (все значения элементов будут обнулены)." << std::endl <<
		"7) Выход." << std::endl;
}

//Запрос количества элементов в списке у пользователем
void case1(Trade* head)
{
	unsigned length = ListLength(head);
	std::cout << "Длина Вашего списка на данный момент: " << length << std::endl;
}

//Запрос добавления элемента в список у пользователем
void case2(Trade* head)
{
	if (head != nullptr)
	{
		Trade* previous{ head }, * ea{};
		double num{};
		std::cout << "После какого порядкового номера элементов в списке Вы хотите добавить новый элемент?" << std::endl;
		bool inList{ false };
		while (!inList)
		{
			num = GetNumber();
			unsigned length = ListLength(head);
			if (num < 1 || num > length)
			{
				std::cout << "Был возвращен указатель nullptr, элемента по данному порядковому номеру в списке не существует." << std::endl;
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
		std::cout << "Новый " << num + 1 << "-й элемент был добавлен." << std::endl;
	}
	else
	{
		CreateHeadOfList(head);
	}
}

//Запрос удаления элемента в списке у пользователем
void case3(Trade*& head)
{
	if (head != nullptr)
	{
		Trade* current{ head }, * search{ head };
		double num{};
		std::cout << "Какой элемент по порядковому номеру Вы хотите удалить?" << std::endl;
		bool inList{ false };
		unsigned length{};
		while (!inList)
		{
			num = GetNumber();
			length = ListLength(head);
			if (num < 1 || num > length)
			{
				std::cout << "Был возвращен указатель nullptr, элемента по данному порядковому номеру в списке не существует." << std::endl;
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
		std::cout << num << "-й элемент был удален." << std::endl;
	}
	else
	{
		std::cerr << "Список пуст, данное действие не может быть выполнено." << std::endl;
	}
}

//Запрос сортировки списка у пользователем
void case4(Trade* head)
{
	SortList(head);
}

//Запрос печати списка у пользователем
void case5(const Trade* head)
{
	PrintList(head);
}

//Основная функция и пользовательская - запрос сброса значений элементов в списке у пользователем
void case6(Trade* head)
{
	if (head != nullptr)
	{
		Trade* tail{ head };
		std::cout << "Вы уверены?" << std::endl <<
			"Да - 1" << std::endl <<
			"Нет - 2" << std::endl;
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
				std::cout << "Список был обновлен: все значения элементов сброшены." << std::endl;
				break;
			}
			else if (sm == '2')
			{
				break;
			}
			else
			{
				std::cout << "Ошибка ввода. Введите 1 или 2: \n";
			}
		}
	}
	else
	{
		std::cerr << "Список пуст, данное действие не может быть выполнено." << std::endl;
	}
}