#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "rus");
	//����� ���������� � �������� �������.
	printTask();
	printDash();
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//���������� ����������, ��������� � �������.
		case '1':
			printDash();
			//����� �������.
			printTable();
			formulas_for_n_4();
			formulas_for_n_8();
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