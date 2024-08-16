#include <iostream>
#include <iomanip>
#include <string>
#include "myfuncs.h"
#include "constants.h"

/*������� ��� �������� ���������������� �����*/
//�������� �������� ������������� ������ �� ����������� �������������� � �����.
bool checkStrIsNumeric(std::string const& tempStr)
{
	bool negative_number{ false }, separator{ false };
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((i == 0) && (tempStr[i] == '-'))
		{
			negative_number = true;
			continue;
		}
		if (!separator && i != 0 && (i != tempStr.length() - 1) && (tempStr[i] == '.' || tempStr[i] == ',' || tempStr[i] == '/'))
		{
			separator = true;
			continue;
		}
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//�������������� �������� ������������� ������ � �����.
long double convertStrToNumber(std::string convertStr)
{
	long double number{}, number_for_fraction{};
	bool negative_number{ false }, fraction{ false };
	int separator_index{ -1 }, k{};
	for (int i{}; i < convertStr.length(); i++)
	{
		if (convertStr[i] == '.' || convertStr[i] == ',' || convertStr[i] == '/')
		{
			if (convertStr[i] == '/') fraction = true;
			separator_index = i;
			break;
		}
	}
	for (int i{}; i < convertStr.length(); i++)
	{
		if ((i == 0) && convertStr[i] == '-')
		{
			negative_number = true;
			continue;
		}
		if (convertStr[i] == '.' || convertStr[i] == ',' || convertStr[i] == '/')
			continue;
		if (separator_index == -1)
			number += static_cast<long double>(convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
		else
			if (!fraction)
				number += static_cast<long double>(convertStr[i] - '0') * pow(10, (i < separator_index) ? (convertStr.length() - i - 1 - 1) : (convertStr.length() - i - 1));
			else
			{
				i < separator_index ? number += static_cast<long double>(convertStr[i] - '0')* pow(10, separator_index - i - 1)
					: number_for_fraction += static_cast<long double>(convertStr[i] - '0') * pow(10, convertStr.length() - separator_index - 1 - k - 1);
				if (i > separator_index) k++;
			}
	}
	if (separator_index != -1 && !fraction)
		number /= pow(10, convertStr.length() - separator_index - 1);
	if (!fraction)
		return negative_number ? static_cast<long double>(-number) : static_cast<long double>(number);
	else
		return negative_number ? static_cast<long double>(-number / number_for_fraction) : static_cast<long double>(number / number_for_fraction);
}

/*������� ��� ������ ���������� �� �������*/
//����� ���������� �� ������, ��������, �������.
void printTask()
{
	std::cout << std::setw(210) << "������� ������� ��������," << std::endl << std::setw(209) << "������ 4312" << std::endl;
	printDash();
	std::cout << "������� ��������������� �������: 2." << std::endl;
	std::cout << "���������� ���������:" << std::endl;
	std::cout << "\tsin(2x) - ln(x) = 0." << std::endl;
	std::cout << "������� [a;b] = [pi/3;(23pi)/48] = [" << std::setprecision(15) << a << "; " << std::setprecision(15) << b << "]." << std::endl;
}
//����� �������������� �����.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//����� ����� �������� ������� ��� ���, �� � ���.
void printTable()
{
	std::cout << std::string(80, '_') << std::endl;
	std::cout << "|" << std::setw(10) << "k + 1" <<
		"|" << std::setw(12) << "x_k" <<
		"|" << std::setw(13) << "x_(k+1)" <<
		"|" << std::setw(20) << "   |x_(k+1) - x_k|  " <<
		"|" << std::setw(20) << "   |f(x_(k+1))|   " 
		"|" << std::endl;
	std::cout << std::string(80, '_') << std::endl;
}

/*���������������� �������*/
//���������������� ����.
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) ��������� ��������� �� ��������� (�������� ����������)." << std::endl <<
		"2) ������ � ��������� ��� �������� �������� ������� � ������, � ����� ��������� ���, �� � ��� ��� ��������� ����������� ���������." << std::endl <<
		"3) ����� �� ���������." << std::endl;
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
		if (choice == "1" || choice == "2" || choice == "3")
			return choice[0];
		else
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 3). ��������� ����:" << std::endl;
	}
}

/*��������������� �������*/
//��������� �������� �������� �������/������ �� ������������.
long double getEpsilonDelta(const int&epsilon_delta)
{
	switch (epsilon_delta)
	{
	case 1:
		std::cout << "������� �������� �������: ";
		break;
	case 2:
		std::cout << "������� �������� ������: ";
		break;
	default:;
	}
	std::string f_epsilon_delta{};
	while (true)
	{
		std::getline(std::cin, f_epsilon_delta);
		if (checkStrIsNumeric(f_epsilon_delta))
		{
			long double f_numeric_epsilon_delta{ convertStrToNumber(f_epsilon_delta) };
			if (f_numeric_epsilon_delta > 0)
				return f_numeric_epsilon_delta;
			else
			{
				switch (epsilon_delta)
				{
				case 1:
					std::cout << "������ �����! �������� ������� ������ ���� ������ 0 (�� �������). ��������� ����: ";
					break;
				case 2:
					std::cout << "������ �����! �������� ������ ������ ���� ������ 0 (�� �������). ��������� ����: ";
				default:;
				}
			}
		}
		else
			std::cout << "������ �����! �� ����� �� �����. ��������� ����: ";
	}
}
//����� ������ �������� �������� �������/������ �� ������������ ��� ���������� �������.
void reselectEpsilonDeltaValue(long double& f_epsilon_delta, const int& epsilon_delta)
{
	switch (epsilon_delta)
	{
	case 1:
		std::cout << "�� ������� �������� ������ �������� �������� ������� ��� ������� �����?(\"enter\"/������� �����)" << std::endl;
		break;
	case 2:
		std::cout << "�� ������� �������� ������ �������� �������� ������ ��� ������� �����?(\"enter\"/������� �����)" << std::endl;
		break;
	default:;
	}
	std::string new_or_old_epsilon_delta{};
	while (true)
	{
		std::getline(std::cin, new_or_old_epsilon_delta);
		if (new_or_old_epsilon_delta.empty())
			break;
		else if (checkStrIsNumeric(new_or_old_epsilon_delta))
		{
			f_epsilon_delta = convertStrToNumber(new_or_old_epsilon_delta);
			break;
		}
		else
			std::cout << "������ �����! �� ������ ������ Enter ��� ������ ����� ��������. ��������� ����: ";
	}
}
//��������� �������� ���������� ����������� x_0 �� ��������� ������� [pi/3; (23pi)/48].
long double getValueInitApprox(const int& method)
{
	std::string str_init_approx_x_0{};
	while (true)
	{
		std::cout << "x_0 = ";
		std::getline(std::cin, str_init_approx_x_0);
		if (checkStrIsNumeric(str_init_approx_x_0))
		{
			long double value_init_approx_x_0{ convertStrToNumber(str_init_approx_x_0) };
			if (value_init_approx_x_0 >= a && value_init_approx_x_0 <= b)
				return value_init_approx_x_0;
			else
				std::cout << "������ �����! �� ������ ������ �������� ���������� ����������� x_0 �� ������� [pi/3;(23pi)/48] = " <<
				"[" << std::setprecision(15) << a << "; " << std::setprecision(15) << b << "]. ��������� ����:" << std::endl;
		}
		else
			std::cout << "������ �����! �� ����� �� �����. ��������� ����: ";
	}
}
//������� ���������� ����������� x_0 � ��������� �� ����������� ������� ���������� ���������������� ������.
bool getInitialApproximation(long double& f_init_approx_x_0, bool& f_flag_init_approx, const int& method)
{
	std::cout << "������� ��������� ����������� x_0:" << std::endl;
	if (!f_flag_init_approx)
	{
		f_init_approx_x_0 = getValueInitApprox(method);
		f_flag_init_approx = true;
	}
	switch (method)
	{
	case 1:
		return true;
		break;
	case 2:
	{
		long double expression_value{ (sin(2 * f_init_approx_x_0) - std::log(f_init_approx_x_0)) * (-4 * sin(2 * f_init_approx_x_0) + 1 / pow(f_init_approx_x_0, 2)) };
		if (expression_value > 0)
			return true;
		else
			return false;
		break;
	}
	default:;
	}
}

/*�������� �������*/
//����� ������� �������� (���).
void simpleIterationMethod(long double& f_epsilon, long double& f_delta, long double& f_init_approx_x_0, bool& f_flag_init_approx)
{
	//������� ���������� ����������� x_0.
	bool correct_method{ getInitialApproximation(f_init_approx_x_0, f_flag_init_approx, 1) };
	printDash();
	//�������� ���������� ������������ ������� ���������� �� ���������, �.�. ������ ����������� �� �������� �������.
	//����� ���������� ��� ���.
	std::cout << "����� ������� �������� (���) ��� ��������� ����������� ���������." << std::endl;
	std::cout << "��������� �����������:\t\tx_0 = " << std::setprecision(10) << f_init_approx_x_0 << "." << std::endl;
	std::cout << "�������� �������� �������:\t" << std::setprecision(10) << f_epsilon << "." << std::endl;
	std::cout << "�������� �������� ������:\t" << std::setprecision(10) << f_delta << "." << std::endl;
	//������������� ���������� ��� �������� k-�� � (k+1)-�� �����������, ���������� C.
	long double x_k{ f_init_approx_x_0 }, x_k_plus_1{};
	unsigned int k{};
	//����� ����� ������� ���.
	printTable();
	//������������ �������.
	while (true)
	{
		//���������� ����������� �� (k+1)-� ���� ��������.
		x_k_plus_1 = x_k + C * (sin(2 * x_k) - std::log(x_k));
		//���������� �������.
		std::cout << "|" << std::setw(10) << k + 1 <<
			"|" << std::setw(12) << std::setprecision(10) << x_k <<
			"|" << std::setw(13) << std::setprecision(10) << x_k_plus_1 <<
			"|" << std::setw(20) << std::setprecision(10) << abs(x_k_plus_1 - x_k) <<
			"|" << std::setw(19) << std::setprecision(10) << sin(2 * x_k_plus_1) - std::log(x_k_plus_1) <<
			"|" << std::endl;
		std::cout << std::string(80, '_') << std::endl;
		//�������� ������� ��������� ������������� ��������.
		if (abs(x_k_plus_1 - x_k) <= f_epsilon && (sin(2 * x_k_plus_1) - std::log(x_k_plus_1)) <= f_delta)
			break;
		//������� � ��������� �������� � ������, ����� ������� ���� �� ���� �������������.
		k += 1;
		x_k = x_k_plus_1;
	}
	std::cout << std::endl << "����� �������, ������� ����������� ��������� �� ��� � ��������� �������� ��������� � ��������� ������������: x = " << 
		std::setprecision(10) << x_k_plus_1 << "." << std::endl;
}
//����� ������� (��).
void NewtonsMethod(long double& f_epsilon, long double& f_delta, long double& f_init_approx_x_0, bool& f_flag_init_approx)
{
	//������� ���������� ����������� x_0.
	bool correct_method{ getInitialApproximation(f_init_approx_x_0, f_flag_init_approx, 2) };
	printDash();
	//����� ���������� ��� ��.
	std::cout << "����� ������� (��) ��� ��������� ����������� ���������." << std::endl;
	std::cout << "��������� �����������:\t\tx_0 = " << std::setprecision(10) << f_init_approx_x_0 << "." << std::endl;
	std::cout << "�������� �������� �������:\t" << std::setprecision(10) << f_epsilon << "." << std::endl;
	std::cout << "�������� �������� ������:\t" << std::setprecision(10) << f_delta << "." << std::endl;
	//�������� ���������� ������������ ������� ����������.
	if (correct_method)
	{
		//������������� ���������� ��� �������� k-�� � (k+1)-�� �����������.
		long double x_k{ f_init_approx_x_0 }, x_k_plus_1{};
		unsigned int k{};
		//����� ����� ������� ��.
		printTable();
		//������������ �������.
		while (true)
		{
			//���������� ����������� �� (k+1)-� ���� ��������.
			x_k_plus_1 = x_k - (sin(2 * x_k) - std::log(x_k)) / (2 * cos(2 * x_k) - 1 / x_k);
			//���������� �������.
			std::cout << "|" << std::setw(10) << k + 1 <<
				"|" << std::setw(12) << std::setprecision(10) << x_k <<
				"|" << std::setw(13) << std::setprecision(10) << x_k_plus_1 <<
				"|" << std::setw(20) << std::setprecision(10) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(19) << std::setprecision(10) << sin(2 * x_k_plus_1) - std::log(x_k_plus_1) <<
				"|" << std::endl;
			std::cout << std::string(80, '_') << std::endl;
			//�������� ������� ��������� ������������� ��������.
			if (abs(x_k_plus_1 - x_k) <= f_epsilon && (sin(2 * x_k_plus_1) - std::log(x_k_plus_1)) <= f_delta)
				break;
			//������� � ��������� �������� � ������, ����� ������� ���� �� ���� �������������.
			k += 1;
			x_k = x_k_plus_1;
		}
		std::cout << std::endl << "����� �������, ������� ����������� ��������� �� �� � ��������� �������� ��������� � ��������� ������������: x = " << 
			std::setprecision(10) << x_k_plus_1 << "." << std::endl;
	}
	else
	{
		std::cout << "�� ����������� ����������� ������� ���������� �� ��� ��������� ����������� ���������." << std::endl << std::endl;
		std::cout << "�������� ���������� ����������� x_0 ������ ���� ������� �� ������� [a;b] = [pi/3; (23pi)/48] = [" << 
			std::setprecision(15) << a << ", " << std::setprecision(15) << b << "] ���, ����� " << "����������� ��������� �������: " << std::endl;
		std::cout << "\tf(x_0)*f\"(x_0) > 0, �.�. (sin(2x_0) - ln(x_0)) * (-4sin(2x_0) + 1/(x_0)^2) > 0." << std::endl;
		std::cout << "� ������ ������ �������� ��������� �����: " << std::endl << std::setprecision(15) <<
			(sin(2 * f_init_approx_x_0) - std::log(f_init_approx_x_0)) * (-4 * sin(2 * f_init_approx_x_0) + 1 / pow(f_init_approx_x_0, 2)) << " < 0." << std::endl;
	}
}
//���������������� ����� ������� (���).
void modifiedNewtonsMethod(long double& f_epsilon, long double& f_delta, long double& f_init_approx_x_0, bool& f_flag_init_approx)
{
	//������� ���������� ����������� x_0.
	bool correct_method{ getInitialApproximation(f_init_approx_x_0, f_flag_init_approx, 2) };
	printDash();
	//����� ���������� ��� ��.
	std::cout << "���������������� ����� ������� (���) ��� ��������� ����������� ���������." << std::endl;
	std::cout << "��������� �����������:\t\tx_0 = " << std::setprecision(10) << f_init_approx_x_0 << "." << std::endl;
	std::cout << "�������� �������� �������:\t" << std::setprecision(10) << f_epsilon << "." << std::endl;
	std::cout << "�������� �������� ������:\t" << std::setprecision(10) << f_delta << "." << std::endl;
	//�������� ���������� ������������ ������� ����������.
	if (correct_method)
	{
		//������������� ���������� ��� �������� k-�� � (k+1)-�� �����������.
		long double x_k{ f_init_approx_x_0 }, x_k_plus_1{};
		unsigned int k{};
		//����� ����� ������� ���.
		printTable();
		//������������ �������.
		while (true)
		{
			//���������� ����������� �� (k+1)-� ���� ��������.
			x_k_plus_1 = x_k - (sin(2 * x_k) - std::log(x_k)) / (2 * cos(2 * f_init_approx_x_0) - 1 / f_init_approx_x_0);
			//���������� �������.
			std::cout << "|" << std::setw(10) << k + 1 <<
				"|" << std::setw(12) << std::setprecision(10) << x_k <<
				"|" << std::setw(13) << std::setprecision(10) << x_k_plus_1 <<
				"|" << std::setw(20) << std::setprecision(10) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(19) << std::setprecision(10) << sin(2 * x_k_plus_1) - std::log(x_k_plus_1) <<
				"|" << std::endl;
			std::cout << std::string(80, '_') << std::endl;
			//�������� ������� ��������� ������������� ��������.
			if (abs(x_k_plus_1 - x_k) <= f_epsilon && (sin(2 * x_k_plus_1) - std::log(x_k_plus_1)) <= f_delta)
				break;
			//������� � ��������� �������� � ������, ����� ������� ���� �� ���� �������������.
			k += 1;
			x_k = x_k_plus_1;
		}
		std::cout << std::endl << "����� �������, ������� ����������� ��������� �� ��� � ��������� �������� ��������� � ��������� ������������: x = " << x_k_plus_1 <<
			"." << std::endl;
	}
	else
	{
		std::cout << "�� ����������� ����������� ������� ���������� ��� ��� ��������� ����������� ���������." << std::endl << std::endl;
		std::cout << "�������� ���������� ����������� x_0 ������ ���� ������� �� ������� [a;b] = [pi/3; (23pi)/48] = [" << 
			std::setprecision(15) << a << ", " << std::setprecision(15) << b << "] ���, ����� " << "����������� ��������� �������: " << std::endl;
		std::cout << "\tf(x_0)*f\"(x_0) > 0, �.�. (sin(2x_0) - ln(x_0)) * (-4sin(2x_0) + 1/(x_0)^2) > 0." << std::endl;
		std::cout << "� ������ ������ �������� ��������� �����: " << std::endl << std::setprecision(15) <<
			(sin(2 * f_init_approx_x_0) - std::log(f_init_approx_x_0)) * (-4 * sin(2 * f_init_approx_x_0) + 1 / pow(f_init_approx_x_0, 2)) << " < 0." << std::endl;
	}
}