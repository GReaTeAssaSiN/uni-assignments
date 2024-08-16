#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "rus");
	//Вывод информации о выданном задании.
	printTask();
	printDash();
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//Выполнение требования, выданного к заданию.
		case '1':
			printDash();
			//Вывод таблицы.
			printTable();
			formulas_for_n_4();
			formulas_for_n_8();
			break;

			//Выход из программы.
		case '2':
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	return 0;
}