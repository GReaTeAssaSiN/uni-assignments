#include <iostream>
#include <iomanip>
#include <string>
#include "myfuncs.h"
#include "constants.h"
#include "math.h"

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
	std::cout << "������� ��������������� �������: 9." << std::endl << std::endl;
	std::cout << "���������:" << std::endl;
	std::cout << "\tgamma\t=    " << gamma << std::endl;
	std::cout << "\tm\t=     " << m << std::endl;
	std::cout << "\talpha\t=    " << alpha << std::endl;
	std::cout << "\tbeta\t=     " << beta << std::endl;
	std::cout << "\tM\t=    " << M << std::endl;
	std::cout << "\tN\t=    " << N << std::endl << std::endl;
	std::cout << "��������� �������:\n";
	std::cout << " u(x,0) = -1 + cosx\n" << std::endl;
	std::cout << "��������� �������:\n";
	std::cout << "  _\n | u(0,t) = -t + sin(0.5t)\n<\n |_u(l,t) = e^(-0.7t) + 0.1sin(0.7)\n" << std::endl;
}
//����� �������������� �����.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
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

/*��������������� �������*/
//��������� �������� S �� ������������.
long double getSvalue()
{
	std::cout << "������� �������� S: ";
	std::string S_value{};
	while (true)
	{
		std::getline(std::cin, S_value);
		if (checkStrIsNumeric(S_value))
		{
			long double numeric_S_value{ convertStrToNumber(S_value) };
			if (numeric_S_value > 0)
				return numeric_S_value;
			else
				std::cout << "S ������ ���� ������������� ������. ��������� ����: ";
		}
		else
			std::cout << "������ �����! �� ����� �� �����. ��������� ����: ";
	}
}
//����� �������.
void printTable(const double* const& x, const double* const& t, const double* const* const& u)
{
	std::cout << std::string(144, '_') << std::endl;
	std::cout << "|" << std::setw(10) << "    t     " << "|";
	for (int i{}; i < n + 1; i++)
	{
		std::cout << std::setw(5) << std::right << "x=" << std::fixed << std::setprecision(2) << std::right << x[i] << "  |";
	}
	std::cout << std::endl;
	std::cout << std::string(144, '_') << std::endl;
	for (int j{}; j < n + 1; j++)
	{
		std::cout << "|" << std::setw(3) << " t=" << std::setw(7) << std::left << std::setprecision(4) << t[j] << "|";
		for (int i{}; i < n + 1; i++)
		{
			if (u[i][j] < 0)
				std::cout << std::setw(2) << "";
			else
				std::cout << std::setw(3) << "";
			std::cout << std::setw(6) << std::setprecision(4) << u[i][j] << std::setw(2) << "" << "|";
		}
		std::cout << std::endl;
		std::cout << std::string(144, '_') << std::endl;
	}
}

/*�������� �������*/
//����� �����.
void explicit_schema() {
	//���������� ����� h �� ��� x � k �� ��� t.
	double h{ l / n };
	double k{ pow(h,2) / 6 };

	//������ �� ���������� xi.
	double* x = new double[n + 1] {};
	//������ �� ���������� tj.
	double* t = new double[n + 1] {};
	//��������� ������ �� ���������� uij=u(xi,tj).
	double** u = new double* [n + 1] {};
	for (int iter{}; iter < n + 1; iter++) {
		u[iter] = new double[n + 1] {};
	}

	//���������� ������� �� ���������� xi.
	for (int i{}; i < n + 1; i++) {
		x[i] = i * h;
	}
	//���������� ������� �� ���������� tj.
	for (int j{}; j < n + 1; j++) {
		t[j] = j * k;
	}
	//���������� ���������� ������� �� ���������� uij=u(xi,tj).
	/*�� ���������� �������*/
	for (int i{}; i < n + 1; i++) {
		u[i][0] = -1 + cos(x[i]); //f_i
	}
	/*�� ��������� ��������*/
	for (int j{1}; j < n + 1; j++)
	{
		u[0][j] = -t[j] + sin(0.5 * t[j]); //phi_j
		u[n][j] = exp(-0.7 * t[j]) + 0.1 * sin(0.7); //psi_j
	}
	/*�� �������-����������� �����������*/
	for (int j{}; j < n; j++)
	{
		for (int i{ 1 }; i < n; i++)
			u[i][j + 1] = 1.0 / 6.0 * (u[i - 1][j] + 4 * u[i][j] + u[i + 1][j]);
	}

	//����� �������.
	printTable(x, t, u);

	//������������ ���������� ������������ ������.
	delete[] x;
	delete[] t;
	for (int i{}; i < n + 1; i++)
		delete[] u[i];
	delete[] u;
}
//������� �����.
void implicit_schema(const double& S) 
{
	//���������� ����� h �� ��� x � k �� ��� t.
	double h{ l / n };
	double k{ pow(h,2) / S };

	//������ �� ���������� xi.
	double* x = new double[n + 1] {};
	//������ �� ���������� tj.
	double* t = new double[n + 1] {};
	//��������� ������ �� ���������� uij=u(xi,tj).
	double** u = new double* [n + 1] {};
	for (int iter{}; iter < n + 1; iter++) {
		u[iter] = new double[n + 1] {};
	}
	//��������� ������ �� ���������� aij=a(xi,tj).
	double** a = new double* [n + 1] {};
	for (int iter{}; iter < n + 1; iter++) {
		a[iter] = new double[n + 1] {};
	}
	//��������� ������ �� ���������� bij=b(xi,tj).
	double** b = new double* [n + 1] {};
	for (int iter{}; iter < n + 1; iter++) {
		b[iter] = new double[n + 1] {};
	}

	//���������� ������� �� ���������� xi.
	for (int i{}; i < n + 1; i++) {
		x[i] = i * h;
	}
	//���������� ������� �� ���������� tj.
	for (int j{}; j < n + 1; j++) {
		t[j] = j * k;
	}
	//���������� ���������� ������� �� ���������� uij=u(xi,tj).
	/*�� ���������� �������*/
	for (int i{}; i < n + 1; i++) {
		u[i][0] = -1 + cos(x[i]); //f_i
	}
	/*�� ��������� ��������*/
	for (int j{1}; j < n + 1; j++)
	{
		u[0][j] = -t[j] + sin(0.5 * t[j]); //phi_j
		u[n][j] = exp(-0.7 * t[j]) + 0.1 * sin(0.7); //psi_j
	}
	
	//���������� ��������������� ������������� ��� ������ ���� �� ���� ����� ��� x=x1.
	for (int j{}; j < n; j++)
	{
		a[1][j + 1] = 1 / (2 + S);
		b[1][j + 1] = -t[j + 1] + sin(0.5 * t[j + 1]) + S * u[1][j];
	}
	//���������� ���������� ��������������� ������������� ��� �������� ���� �� ���� ����� ��� x=x2,x3,...,x(n-1).
	for (int j{}; j < n; j++)
	{
		for (int i{ 2 }; i < n; i++)
		{
			a[i][j + 1] = 1 / (2 + S - a[i - 1][j + 1]);
			b[i][j + 1] = a[i - 1][j + 1] * b[i - 1][j + 1] + S * u[i][j];
		}
		//���������� �������� uij ��� �������� ���� �� ������ ����.
		for (int i{ n - 1 }; i > 0; i--)
			u[i][j + 1] = a[i][j + 1] * (b[i][j + 1] + u[i + 1][j + 1]);
	}

	//����� �������.
	printTable(x, t, u);

	//������������ ���������� ������������ ������.
	delete[] x;
	delete[] t;
	for (int i{}; i < n + 1; i++)
	{
		delete[] u[i];
		delete[] a[i];
		delete[] b[i];
	}
	delete[] u;
	delete[] a;
	delete[] b;
}