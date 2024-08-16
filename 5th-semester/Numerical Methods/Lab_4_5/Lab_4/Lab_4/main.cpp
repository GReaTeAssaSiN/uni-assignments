#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//����� ���������� � �������� �������.
	printTask();
	printDash();
	//����� 3-� �������� �� ���������� ������� [a;b];
	long double x1{}, x2{}, x3{};
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//���������� ����������, ��������� � �������.
		case '1':
			printDash();
			//��������� 3-� �������� �� ���������� ������� [a;b].
			x1 = getXValue(1);
			x2 = getXValue(2);
			x3 = getXValue(3);
			//����� ���������� � ���������� ���������.
			printDash();
			std::cout << "�� ������� [-0.72;-0.7] ���� ������� �������� ��������:" << std::endl;
			std::cout << "������ �������� x: " << x1 << std::endl;
			std::cout << "������ �������� x: " << x2 << std::endl;
			std::cout << "������ �������� x: " << x3 << std::endl;
			
			//����� ������� ��� ����������������.
			std::cout << std::endl << "����������������: I � II ���������������� ������� ������, ���������������� ������� ��������. "<< std::endl << std::endl;
			printTableInterpolation();
			interpolation_formulas(x1, x2, x3);

			std::cout << std::endl;

			//����� ������� ��� ���������� �����������������.
			std::cout << std::endl << "��������� �����������������, ���������� �� I � II ���������������� ������� �������." << std::endl << std::endl;
			printTableNumericalDefferentiation();
			numerical_differentiation_formulas(x1, x2, x3);
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