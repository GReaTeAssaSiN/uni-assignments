#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//����� ���������� � �������� �������.
	printTask();
	printDash();
	//������������� �������� �������� �������, ������, ���������� ����������� x_0;
	long double epsilon{}, delta{}, init_approx_x_0{};
	//���� ��� ����� ������ ���������� ����������� x_0.
	bool flag_init_approx{};
	//����������� ������������ ���������� ���������.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//���������� ����������, ��������� � �������.
		case '1':
			//������� �������� ������� � ������ pow(10, -3);
			epsilon = 0.001;
			delta = 0.001;

			/*��������� ������*/
			//1)
			//�������������� �����.
			printDash();
			std::cout << "����� ������� �������� (���)." << std::endl;
			//����� ������� �������� (���).
			simpleIterationMethod(epsilon, delta, init_approx_x_0, flag_init_approx);

			//2)
			//�������������� �����.
			printDash();
			std::cout << "����� ������� (��)." << std::endl;
			//����� ������� (��).
			NewtonsMethod(epsilon, delta, init_approx_x_0, flag_init_approx);

			//3)
			//�������������� �����.
			printDash();
			std::cout << "���������������� ����� ������� (���)." << std::endl;
			//���������������� ����� ������� (���).
			modifiedNewtonsMethod(epsilon, delta, init_approx_x_0, flag_init_approx);

			//������� �������� ������� � ������ pow(10, -5);
			epsilon = 0.00001;
			delta = 0.00001;

			//4)
			//�������������� �����.
			printDash();
			std::cout << "����� ������� �������� (���)." << std::endl;
			//����� ������� �������� (���).
			simpleIterationMethod(epsilon, delta, init_approx_x_0, flag_init_approx);

			//5)
			//�������������� �����.
			printDash();
			std::cout << "����� ������� (��)." << std::endl;
			//����� ������� (��).
			NewtonsMethod(epsilon, delta, init_approx_x_0, flag_init_approx);

			//6)
			//�������������� �����.
			printDash();
			std::cout << "���������������� ����� ������� (���)." << std::endl;
			//���������������� ����� ������� (���).
			modifiedNewtonsMethod(epsilon, delta, init_approx_x_0, flag_init_approx);

			flag_init_approx = false;
			break;

			//����� ������ �������� �������� ������� � ������.
		case '2':
			printDash();
			//������� �������� ������� � ������.
			if (epsilon == 0)
				epsilon = getEpsilonDelta(1);
			else
				reselectEpsilonDeltaValue(epsilon, 1);
			if (delta == 0)
				delta = getEpsilonDelta(2);
			else
				reselectEpsilonDeltaValue(delta, 2);

			/*��������� ������*/
			//1)
			//�������������� �����.
			printDash();
			std::cout << "����� ������� �������� (���)." << std::endl;
			//����� ������� �������� (���).
			simpleIterationMethod(epsilon, delta, init_approx_x_0, flag_init_approx);

			//2)
			//�������������� �����.
			printDash();
			std::cout << "����� ������� (��)." << std::endl;
			//����� ������� (��).
			NewtonsMethod(epsilon, delta, init_approx_x_0, flag_init_approx);

			//3)
			//�������������� �����.
			printDash();
			std::cout << "���������������� ����� ������� (���)." << std::endl;
			//���������������� ����� ������� (���).
			modifiedNewtonsMethod(epsilon, delta, init_approx_x_0, flag_init_approx);

			flag_init_approx = false;
			break;

			//����� �� ���������.
		case '3':
			cycle = false;
			break;
		default:;
		}
		printDash();
	}

	return 0;
}