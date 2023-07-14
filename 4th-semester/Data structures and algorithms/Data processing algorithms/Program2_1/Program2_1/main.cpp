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
	bool cycle{true};
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			regenerateArray(numbers);
			break;
		case '2':
			bubbleSorting(numbers);
			break;
		case '3':
			selectionSorting(numbers);
			break;
		case '4':
			insertionSorting(numbers);
			break;
		case '5':
			std::cout << "�������� ��������� ������� (����� �� 10 ��������� � ������):" << std::endl;
			printArray(numbers);
			break;
		case '6':
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