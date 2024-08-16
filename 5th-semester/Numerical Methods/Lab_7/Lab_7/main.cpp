#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "rus");
	//Вывод информации о выданном задании.
	printTask();
	printDash();
	int n_values[3]{}, m_values[3]{};
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//Выполнение требования, выданного к заданию.
		case '1':
			printDash();
			//Получение значений n и m (3 варианта пар).
			for (int i{}; i < 3; i++)
			{
				n_values[i] = get_n_m_values('n', i);
				m_values[i] = get_n_m_values('m', i);
				std::cout << std::endl;
			}
			//Вывод таблицы.
			printTable();
			for (int i{}; i < 3; i++)
				simpsonFormula(n_values[i], m_values[i]);
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