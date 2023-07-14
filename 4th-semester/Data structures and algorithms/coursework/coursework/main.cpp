#include <Windows.h>
#include <iostream>
#include <string>

#include "myfuncs.h"

int main()
{
	system("color F0");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//Название города.
	std::string city_name{ getCityNameFromUser() };
	system("cls");
	City* city{ new City(city_name) };
	//Цикл обработки выбора действий пользователя.
	bool cycle{ true };
	while (cycle)
	{
		userMenu(city->getCityName());
		char user_choice{ getUserChoice(0) };
		system("cls");
		switch (user_choice)
		{
		case '1':
			showTheCity(city);
			break;
		case '2':
			addNewStreetInTheCity(city);
			break;
		case '3':
			removeThFirsteStreetFromTheCity(city);
			break;
		case '4':
			selectionOfASpecificCityStreet(city);
			break;
		case '5':
			exportTheCityToFile(city);
			break;
		case '6':
			importTheCityFromFile(city);
			break;
		case '0':
			delete city;
			cycle = false;
			std::cout << "Вся выделенная динамическая память для комбинированной структуры данных была возвращена в кучу.\n\nЗавершение программы . . ." << std::endl;
			break;
		default:;
		}
		printDashes();

	}
	return 0;
}