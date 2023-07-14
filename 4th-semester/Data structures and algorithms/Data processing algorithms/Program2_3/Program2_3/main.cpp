#include <iostream>
#include <cstdlib> //��� ������� rand() � srand()
#include <ctime> //��� ������� time()
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//�������� ���� � ������������ ������� (��������� ������������������ ��������� ����� �� ���������).
	srand(static_cast<unsigned int>(time(0)));
	//������� ������� � ��� ����������.
	DynamicArray numbers{};
	generateArray(numbers);
	printDashes();
	//���� ��������� ����������������� �����.
	bool cycle{ true };
	while (cycle)
	{
		int case_number{ convertStrToInt(getCase()) };
		switch (case_number)
		{
		case 1:
			regenerateArray(numbers);
			break;
		case 2:
			sortSelectionAndRuntimeCalculation(numbers, 1);
			break;
		case 3:
			sortSelectionAndRuntimeCalculation(numbers, 2);
			break;
		case 4:
			sortSelectionAndRuntimeCalculation(numbers, 3);
			break;
		case 5:
			sortSelectionAndRuntimeCalculation(numbers, 4);
			break;
		case 6:
			sortSelectionAndRuntimeCalculation(numbers, 5);
			break;
		case 7:
			sortSelectionAndRuntimeCalculation(numbers, 6);
			break;
		case 8:
			sortSelectionAndRuntimeCalculation(numbers, 7);
			break;
		case 9:
			sortSelectionAndRuntimeCalculation(numbers, 8);
			break;
		case 10:
			sortSelectionAndRuntimeCalculation(numbers, 9);
			break;
		case 11:
			std::cout << "�������� ��������� ������� (����� �� 10 ��������� � ������):" << std::endl;
			printArray(numbers);
			break;
		case 12:
			cycle = false;
			clear(numbers);
			std::cout << "���������� ��������� . . ." << std::endl;
			break;
		default:;
		}
		printDashes();
	}
	return 0;
}