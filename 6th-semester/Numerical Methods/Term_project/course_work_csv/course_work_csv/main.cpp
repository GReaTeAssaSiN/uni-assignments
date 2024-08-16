#include <iostream>
#include "myfuncs.h"
#include "constants.h"
//��� ������ � ������.
#include <fstream>

int main()
{
	//system("color F0");
	setlocale(LC_ALL, "Rus");
	//���� ������ �����������.
	std::ofstream outputFile;
	outputFile.open("C:\\Users\\Alex\\Downloads\\output.txt");
	//����� ���������� � �������� �������.
	printTask();
	printDash();
	//������� n1=10, n2=20.
	int n1{ 10 }, n2{ 20 };
	double epsilon1{ 3 * pow(10, -3) };
	double epsilon2{ 0.00003 };
	double epsilon3{ 2.2 * pow(10, -9) };
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
			outputFile << "����� ������ �����������,n = " << n1 << ",Epsilon = " << epsilon1 << "\n";
			printTableHeaderSecondDerivativeMethod(outputFile);
			second_derivative_method(n1, epsilon1, outputFile);
			//��� n = 10.
			outputFile << "����� ������� �����������,n = " << n1 << ",Epsilon = " << epsilon1 << "\n";
			printTableHeaderThirdDerivativeMethod(outputFile);
			third_derivative_method(n1, epsilon1, outputFile);
			//��� n = 20.
			outputFile << "����� ������ �����������,n = " << n2 << ",Epsilon = " << epsilon2 << "\n";
			printTableHeaderSecondDerivativeMethod(outputFile);
			second_derivative_method(n2, epsilon2, outputFile);
			//��� n = 20.
			outputFile << "����� ������� �����������,n = " << n2 << ",Epsilon = " << epsilon2 << "\n";
			printTableHeaderThirdDerivativeMethod(outputFile);
			third_derivative_method(n2, epsilon2, outputFile);
			//��� n = 10.
			outputFile << "����� ������ �����������,n = " << n1 << ",Epsilon = " << epsilon3 << "\n";
			printTableHeaderSecondDerivativeMethod(outputFile);
			second_derivative_method(n1, epsilon3, outputFile);
			//��� n = 20.
			outputFile << "����� ������� �����������,n = " << n1 << ",Epsilon = " << epsilon3 << "\n";
			printTableHeaderThirdDerivativeMethod(outputFile);
			third_derivative_method(n1, epsilon3, outputFile);

			std::cout << "������ ���� ��������� � .txt ����. ����: C:\\Users\\Alex\\Downloads\\output.txt" 
				<< "\n������������ ���� � Excel � �������� � ������������ �����������." << std::endl;
			break;
		case '2':
			outputFile.close();
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	return 0;
}