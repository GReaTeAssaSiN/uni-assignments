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
	//�������� a ��� ���������� ����.
	//double a{};
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//���������� ����������, ��������� � �������.
		case '1':
			printDash();

			//a = getAvalue();
			printDash();
			std::cout << std::endl;
			//std::cout << "���������� ���������� ��� a = " << a << std::endl;
			std::cout << "����� �����:" << std::endl;
			grid_method(1.0);

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