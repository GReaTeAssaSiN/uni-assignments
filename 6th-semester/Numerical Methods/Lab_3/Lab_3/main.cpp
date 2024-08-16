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
	//�������� S ��� ������� ����� ������ �����.
	double S{};
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//���������� ����������, ��������� � �������.
		case '1':
			printDash();

			S = getSvalue();
			printDash();
			std::cout << std::endl;
			std::cout.unsetf(std::ios::fixed);
			std::cout << "���������� ���������� ��� S = " << S << std::endl;
			std::cout << "����� �����. ����� �����:" << std::endl;
			explicit_schema();
			std::cout << std::endl;
			std::cout << "����� �����. ������� �����:" << std::endl;
			implicit_schema(S);
			
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