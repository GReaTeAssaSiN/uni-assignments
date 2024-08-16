#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "rus");
	//����� ���������� � �������� �������.
	printTask();
	printDash();
	int n_values[3]{}, m_values[3]{};
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//���������� ����������, ��������� � �������.
		case '1':
			printDash();
			//��������� �������� n � m (3 �������� ���).
			for (int i{}; i < 3; i++)
			{
				n_values[i] = get_n_m_values('n', i);
				m_values[i] = get_n_m_values('m', i);
				std::cout << std::endl;
			}
			//����� �������.
			printTable();
			for (int i{}; i < 3; i++)
				simpsonFormula(n_values[i], m_values[i]);
			break;

			//����� �� ���������.
		case '2':
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	return 0;
}