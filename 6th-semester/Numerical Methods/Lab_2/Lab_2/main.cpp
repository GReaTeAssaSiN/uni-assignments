#include <iostream>
#include "myfuncs.h"
#include "constants.h"

int main()
{
	//system("color F0");
	setlocale(LC_ALL, "Rus");
	//����� ���������� � �������� �������.
	printTask();
	printDash();
	//������� n1 = 10, n2 = 20.
	int n1{ 10 }, n2{ 20 };
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//���������� ����������, ��������� � �������.
		case '1':
			printDash();
			
			//����� ������� ��� n=10.
			std::cout << std::endl << "������� �������� ������� ������ ������� �������� ��� n = " << n1 << ":" << std::endl;
			printTable();
			sweep_method(n1);

			//����� ������� ��� n=20.
			std::cout << std::endl << "������� �������� ������� ������ ������� �������� ��� n = " << n2 << ":" << std::endl;
			printTable();
			sweep_method(n2);

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