#include <iostream>
#include <iomanip>
#include <string>
#include "myfuncs.h"
#include "constants.h"

/*������� ��� ������ ���������� �� �������*/
//����� ���������� �� ������, ��������, �������.
void printTask()
{
	std::cout << std::setw(210) << "������� ������� ��������," << std::endl << std::setw(209) << "������ 4312" << std::endl;
	printDash();
	std::cout << "������� ��������������� �������: 9." << std::endl;
	std::cout << "������ ���� (�������� ������������ ���������������� ��������� � ��������� �������):" << std::endl;
	std::cout << "  _\n |\n | dy/dx = (x - 1) * y;\n<\n | y(-2) = -2.\n |_" << std::endl << std::endl;
	std::cout << "�������� �������: [-2, -1]." << std::endl;
	std::cout << "����� ������� ��: y = Ce^(x^2/2 - x), C ����������� R." << std::endl;
	std::cout << "������� ������� �� (������ ����): y = -2e^(x^2/2 - x - 4)." << std::endl;
}
//����� �������������� �����.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//����� ����� �������� ������� ��� ������ ������, ������ �����-����� ��� ��������� � ������ ������.
void printTableOne()
{
	std::cout << std::string(144, '_') << std::endl;
	std::cout << "|" << std::setw(15) << "xi     " <<
		"|" << std::setw(15) << "yi     " <<
		"|" << std::setw(15) << "yi^�     " <<
		"|" << std::setw(20) << "     |yi - yi^�|    " <<
		"|" << std::setw(15) << "yi^(�-�)  " <<
		"|" << std::setw(20) << "   |yi - yi^(�-�)|  " <<
		"|" << std::setw(15) << "yi^�     " <<
		"|" << std::setw(20) << "     |yi - yi^�|    " <<
		"|" << std::endl;
	std::cout << std::string(144, '_') << std::endl;
}
//����� ����� �������� ������� ��� ������ �����-����� � ����������.
void printTableTwo()
{
	std::cout << std::string(134, '_') << std::endl;
	std::cout << "|" << std::setw(15) << "xi     " <<
		"|" << std::setw(15) << "yi     " <<
		"|" << std::setw(15) << "yi^(�-�)  " <<
		"|" << std::setw(20) << "   |yi - yi^(�-�)|  " <<
		"|" << std::setw(15) << "step" <<
		"|" << std::setw(15) << "y_H      " <<
		"|" << std::setw(20) << "|yi^(�-�) - y_H|  " <<
		"|" << std::setw(10) << " correct  " <<
		"|" << std::endl;
	std::cout << std::string(134, '_') << std::endl;
}

/*���������������� �������*/
//���������������� ����.
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) ��������� ��������� (�������� ����������)." << std::endl <<
		"2) ����� �� ���������." << std::endl;
}
//������ �������� � ������������.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2")
			return choice[0];
		else
			std::cout << std::endl << "������ �����! ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 2). ��������� ����:" << std::endl;
	}
}

/*�������� �������*/
//����� ������, ����� �����-����� ��� ��������� � ����� ������ ��� n = 10;20.
void FirstTable_methods(const int& n)
{
	//���������� ���� h.
	double h{ (b - a) / n };
	//������� �������� xi � yi (��� i = 0, ��������� �������).
	double xi{ x_0 }, yi{ y_0 };

	//���������� ��� �������� yi^�, yi^(�-�), yi^�.
	double yi_E{ y_0 }, yi_RK{ y_0 }, yi_A{ y_0 };
	//������� �� 4-� ��������� ����������� �������� xi, xi_1, xi_2, xi_3 � yi, yi_1, yi_2, yi_3 ��� ������ ������.
	double Adams_xi_mass[4]{}, Adams_yi_mass[4]{};

	//���������� �������.
	for (int i{}; i <= n; i++)
	{
		//��������� ������� y(x0) = y0.
		if (i == 0)
		{
			//������������ �������� � �������� ��� ������ ������.
			Adams_xi_mass[3] = xi;
			Adams_yi_mass[3] = yi;
		}
		//���������� xi � yi �� ��������������� �������� �������.
		else
		{
			//���������� ������� ��������.
			yi = -2 * exp(pow(xi, 2) / 2 - xi - 4);
			//��������, ����������� �� �������� �������.
			//����� ������.
			yi_E = Eulers_method(xi - h, yi_E, h);
			//����� �����-����� ��� ���������.
			yi_RK = RKs_method_without_recalculation(xi - h, yi_RK, h);
			//����� ������.
			//��� i < 4 yi ��������� �� ������� ������ �����-����� 4-�� ������� �������� ��� ���������.
			if (i < 4)
			{
				yi_A = yi_RK;
				//������������ �������� � �������� ��� ������ ������.
				Adams_xi_mass[3 - i] = xi;
				Adams_yi_mass[3 - i] = yi_A;
			}
			//����� �� ������� ������ ������.
			else
			{
				yi_A = Adams_method(h, Adams_xi_mass, Adams_yi_mass);

				//���������������� �������� ��� ������ ������ (��� �������� ���������� �� 1 ������, ������ ��������� ��������� �������).
				for (int i{ 3 }; i > 0; i--)
				{
					Adams_xi_mass[i] = Adams_xi_mass[i - 1];
					Adams_yi_mass[i] = Adams_yi_mass[i - 1];
				}
				Adams_xi_mass[0] = xi;
				Adams_yi_mass[0] = yi_A;
			}
		}

		//���������� ������� ��� ������� i.
		std::cout << "|" << std::setw(15) << std::setprecision(10) << xi <<
			"|" << std::setw(15) << std::setprecision(10) << yi <<
			"|" << std::setw(15) << std::setprecision(10) << yi_E <<
			"|" << std::setw(20) << std::setprecision(10) << abs(yi - yi_E) <<
			"|" << std::setw(15) << std::setprecision(10) << yi_RK <<
			"|" << std::setw(20) << std::setprecision(10) << abs(yi - yi_RK) <<
			"|" << std::setw(15) << std::setprecision(10) << yi_A <<
			"|" << std::setw(20) << std::setprecision(10) << abs(yi - yi_A) <<
			"|" << std::endl;
		std::cout << std::string(144, '_') << std::endl;

		//���������� x_(i+1) ��� ��������� ��������.
		xi += h;
	}
}
//����� �����-����� � ���������� ��� n = 10;20.
void SecondTable_methods(const int& n, const double& epsilon)
{
	//���������� ���� h � H.
	double h{ (b - a) / n }, H{ 2 * h };
	//������� �������� xi � yi (��� i = 0, ��������� �������), yi^(�-�) (��� i = 0 yi^(�-�) = y_0).
	double xi{ x_0 }, yi{ y_0 }, yi_RK{ y_0 };
	//���������� ��� �������� �������� y_h � y_H (��� �������� ������������ ������ ���� h).
	double y_h{}, y_H{};
	//������, �������� �������� xi � ����� h �� ���������� 2-� �����.
	double RK_xi_mass[3]{};
	//������, �������� �������� yi^(�-�) � ����� h �� ���������� 2-� �����.
	double RK_yi_mass[3]{};
	//���� ��� ����� ������ � ������� ��������, ��������� � ������� ���������� ��������.
	bool correct_ouput{};

	//����� �����-����� 4-�� ������� �������� � ����������.
	//���� ��������������� �������� xi, x_(i+1), x_(i+2) ��������� �� ������� [a, b] = [-2, -1].
	while ((xi + 2 * h) - b <= 0.000000000000001) // ������������ xi + 2h <= b (����������, ����� ���������� �� ����������� �������� � ������������� ����� ���� double �� ���).
	{
		//������ �������� �������� �������� xi � yi^(�-�) ����� ������� xi � yi^(�-�).
		RK_xi_mass[0] = xi; RK_yi_mass[0] = yi_RK;
		//���������� y_(i+1) �� ������ �����-����� 4-�� ������� ��������.
		yi_RK = RKs_method_without_recalculation(xi, yi_RK, h);
		//��������� ������������ y_(i+1) � ������ �������� yi^(�-�).
		RK_yi_mass[1] = yi_RK;
		//���������� x_(i+1).
		xi += h;
		//��������� ������������ x_(i+1) � ������ �������� xi.
		RK_xi_mass[1] = xi;
		//���������� y_(i+2) �� ������ �����-����� 4-�� ������� ��������.
		yi_RK = RKs_method_without_recalculation(xi, yi_RK, h);
		//��������� ������������ y_(i+2) � ������ �������� yi^(�-�).
		RK_yi_mass[2] = yi_RK;
		//���������� x_(i+2).
		xi += h;
		//��������� ������������ x_(i+2) � ������ �������� xi.
		RK_xi_mass[2] = xi;

		//���������� y_h (��������� ������� ������� �������� yi^(�-�)) � y_H � ������� ����� H (������������ ������ �������� �������� �������� xi � yi^(�-�)).
		y_h = RK_yi_mass[2];
		y_H = RKs_method_without_recalculation(RK_xi_mass[0], RK_yi_mass[0], H);

		//���������� ������� ��� ������� i (�� ���������� 2-� �����).
		for (int i{}; i <= 2; i++) /* ������ �������� �������� RK_xi_mass � RK_yi_mass ������������ ��� "������" � ������ ��������� ������ ���� � "������" ��� ������������ 2-� ����� �� ������ ��������.
									* � ������ ����������� �������� ����� ������ ������ ��������� ������� ������� �������� ��������� ������� �� ���������� ��������.
									*/
		{
			if (i == 0 && correct_ouput)
				continue;
			//���������� ������� �������� yi.
			yi = -2 * exp(pow(RK_xi_mass[i], 2) / 2 - RK_xi_mass[i] - 4);
			std::cout << "|" << std::setw(15) << std::setprecision(10) << RK_xi_mass[i] <<
				"|" << std::setw(15) << std::setprecision(10) << yi <<
				"|" << std::setw(15) << std::setprecision(10) << RK_yi_mass[i] <<
				"|" << std::setw(20) << std::setprecision(10) << abs(yi - RK_yi_mass[i]) <<
				"|" << std::setw(15) << std::setprecision(10) << h << "|";
			if (i != 2)
				std::cout << std::setw(15) << std::setprecision(10) << "" <<
				"|" << std::setw(20) << std::setprecision(10) << "" <<
				"|" << std::setw(10) << "" <<
				"|" << std::endl;
			else
			{
				std::cout << std::setw(15) << std::setprecision(10) << y_H <<
					"|" << std::setw(20) << std::setprecision(10) << abs(y_h - y_H) << "|";
				if (abs(y_h - y_H) <= epsilon)
					std::cout << std::setw(10) << "true";
				else
					std::cout << std::setw(10) << "false";
					std::cout << "|" << std::endl;
			}
			if (!correct_ouput)
				correct_ouput = true;
			std::cout << std::string(134, '_') << std::endl;
		}

		//�������� ������������ ������ ���� h.
		if (abs(y_h - y_H) > epsilon)
		{
			//������� �� ��� ���� �����.
			xi = RK_xi_mass[0];
			yi = RK_yi_mass[0];
			//��������� ������� ��� h �����.
			h /= 2;
			//������ ��������� ��� H = 2 * h.
			H = 2 * h;
		}
	}
}
//����� ������.
double Eulers_method(const double& xi, const double& yi, const double& h)
{
	//���������� y_(i+1).
	return (yi + h * (xi - 1) * yi);
}
//����� �����-����� 4-�� ������� �������� ��� ���������.
double RKs_method_without_recalculation(const double& xi, const double& yi, const double& h)
{
	//���������� ���������� K1i, K2i, K3i � K4i.
	double K1i{ h * (xi - 1) * yi };
	double K2i{ h * (xi + h / 2 - 1) * (yi + K1i / 2) };
	double K3i{ h * (xi + h / 2 - 1) * (yi + K2i / 2) };
	double K4i{ h * (xi + h - 1) * (yi + K3i) };
	//���������� y_(i+1).
	return (yi + 1.0 / 6.0 * (K1i + 2 * K2i + 2 * K3i + K4i));
}
//����� ������.
double Adams_method(const double& h, const double Adams_xi_mass[], const double Adams_yi_mass[])
{	
	//���������� y'i, y'i_1, y'i_2, y'i_3.
	double yi{ Adams_yi_mass[0] }, dyi{ (Adams_xi_mass[0] - 1) * Adams_yi_mass[0] }, dyi_1{ (Adams_xi_mass[1] - 1) * Adams_yi_mass[1] },
		dyi_2{ (Adams_xi_mass[2] - 1) * Adams_yi_mass[2] }, dyi_3{ (Adams_xi_mass[3] - 1) * Adams_yi_mass[3] };
	//���������� y_(i+1).
	return (yi + h / 24.0 * (55 * dyi - 59 * dyi_1 + 37 * dyi_2 - 9 * dyi_3));
}