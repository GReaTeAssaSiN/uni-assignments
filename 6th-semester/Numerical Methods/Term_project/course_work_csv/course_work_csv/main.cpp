#include <iostream>
#include "myfuncs.h"
#include "constants.h"
//Для работы с файлом.
#include <fstream>

int main()
{
	//system("color F0");
	setlocale(LC_ALL, "Rus");
	//Файл вывода результатов.
	std::ofstream outputFile;
	outputFile.open("C:\\Users\\Alex\\Downloads\\output.txt");
	//Вывод информации о выданном задании.
	printTask();
	printDash();
	//Задание n1=10, n2=20.
	int n1{ 10 }, n2{ 20 };
	double epsilon1{ 3 * pow(10, -3) };
	double epsilon2{ 0.00003 };
	double epsilon3{ 2.2 * pow(10, -9) };
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//Выполнение требования, выданного к заданию.
		case '1':
			printDash();
			//При n = 10.
			outputFile << "Метод второй производной,n = " << n1 << ",Epsilon = " << epsilon1 << "\n";
			printTableHeaderSecondDerivativeMethod(outputFile);
			second_derivative_method(n1, epsilon1, outputFile);
			//При n = 10.
			outputFile << "Метод третьей производной,n = " << n1 << ",Epsilon = " << epsilon1 << "\n";
			printTableHeaderThirdDerivativeMethod(outputFile);
			third_derivative_method(n1, epsilon1, outputFile);
			//При n = 20.
			outputFile << "Метод второй производной,n = " << n2 << ",Epsilon = " << epsilon2 << "\n";
			printTableHeaderSecondDerivativeMethod(outputFile);
			second_derivative_method(n2, epsilon2, outputFile);
			//При n = 20.
			outputFile << "Метод третьей производной,n = " << n2 << ",Epsilon = " << epsilon2 << "\n";
			printTableHeaderThirdDerivativeMethod(outputFile);
			third_derivative_method(n2, epsilon2, outputFile);
			//При n = 10.
			outputFile << "Метод второй производной,n = " << n1 << ",Epsilon = " << epsilon3 << "\n";
			printTableHeaderSecondDerivativeMethod(outputFile);
			second_derivative_method(n1, epsilon3, outputFile);
			//При n = 20.
			outputFile << "Метод третьей производной,n = " << n1 << ",Epsilon = " << epsilon3 << "\n";
			printTableHeaderThirdDerivativeMethod(outputFile);
			third_derivative_method(n1, epsilon3, outputFile);

			std::cout << "Данные были загружены в .txt файл. Путь: C:\\Users\\Alex\\Downloads\\output.txt" 
				<< "\nИмпортируйте файл в Excel и откройте с необходимыми настройками." << std::endl;
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