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
	//������� n1=10, n2=20.
	int n1{ 10 }, n2{ 20 };
	double epsilon1{ 3 * pow(10, -3)};
	double epsilon2{ 1.1 * pow(10, -7) };
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//���������� ����������, ��������� � �������.
		case '1':
			printDash();
			//��� n = 10.
			std::cout << std::endl << "������������ ������� ������ ���� ��� ������������� ����������������� ��������� �������� ����������� ������ �������� (�� �������) " <<
				"��� n = " << n1 << " � epsilon = " << epsilon1 << ":" << std::endl;
			second_derivative_method(n1, epsilon1);
			printDash();
			std::cout << std::endl;
			//��� n = 10.
			std::cout << std::endl << "������������ ������� ������ ���� ��� ������������� ����������������� ��������� �������� ����������� ������ �������� (�� ��������) " <<
				"��� n = " << n1 << " � epsilon = " << epsilon1 << ":" << std::endl;
			third_derivative_method(n1, epsilon1);
			printDash();
			std::cout << std::endl;
			//��� n = 20.
			std::cout << std::endl << "������������ ������� ������ ���� ��� ������������� ����������������� ��������� �������� ����������� ������ �������� (�� �������) " <<
				"��� n = " << n2 << " � epsilon = " << epsilon2 << ":" << std::endl;
			second_derivative_method(n2, epsilon2);
			printDash();
			std::cout << std::endl;
			//��� n = 20.
			std::cout << std::endl << "������������ ������� ������ ���� ��� ������������� ����������������� ��������� �������� ����������� ������ �������� (�� ��������) " <<
				"��� n = " << n2 << " � epsilon = " << epsilon2 << ":" << std::endl;
			third_derivative_method(n2, epsilon2);
			break;
		case '2':
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	return 0;
}