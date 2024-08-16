#include <iostream>
#include "myfuncs.h"
#include "constants.h"

int main()
{
	system("color F0");
	setlocale(LC_ALL, "Rus");
	//����� ���������� � �������� �������.
	printTask();
	printDash();
	//������� n1 = 10, n2 = 20.
	int n1{ 10 }, n2{ 20 };
	double epsilon1{ 0.0009};
	double epsilon2{ 3 * pow(10, -5) };
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//���������� ����������, ��������� � �������.
		case '1':
			printDash();

			//����� ������ �������.
			//��� n = 10.
			std::cout << std::endl << "������������ ������� ������ ���� �������� ������, �����-����� 4-�� ������� �������� ��� ��������� � ������� ������ " <<
				"��� n = " << n1 << ":" << std::endl;
			printTableOne();
			FirstTable_methods(n1);
			std::cout << std::endl;
			//��� n = 20.
			std::cout << std::endl << "������������ ������� ������ ���� �������� ������, �����-����� 4-�� ������� �������� ��� ��������� � ������� ������ " <<
				"��� n = " << n2 << ":" << std::endl;
			printTableOne();
			FirstTable_methods(n2);

			std::cout << std::endl;

			//����� ������ �������.
			//��� n = 10, epsilon = 0.0001.
			std::cout << std::endl << "������������ ������� ������ ���� ������� �����-����� 4-�� ������� �������� � ���������� " <<
				"��� n = " << n1 << ", h = " << (b - a) / n1 << " (�� �������� ���������) � epsilon = " << epsilon1 << ":" << std::endl;
			printTableTwo();
			SecondTable_methods(n1, epsilon1);
			std::cout << std::endl;
			//��� n = 20, epsilon = 0.0001.
			std::cout << std::endl << "������������ ������� ������ ���� ������� �����-����� 4-�� ������� �������� � ���������� " <<
				"��� n = " << n2 << ", h = " << (b - a) / n2 << " (�� �������� ���������) � epsilon = " << epsilon2 << ":" << std::endl;
			printTableTwo();
			SecondTable_methods(n2, epsilon2);

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