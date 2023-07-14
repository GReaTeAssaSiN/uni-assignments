#include <iostream>
#include <cstdlib> //��� ������� rand() � srand()
#include <windows.h>//��� ������� Sleep()
#include <ctime> //��� ������� time()
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	Queue* myQueue = new Queue{};
	srand(static_cast<unsigned int>(time(0)));//�������� ���� � ������������ ������� (��������� ������������������ ��������� ����� �� ���������).
	std::cout << "������ ��������������� ����� ��� ��������������." << std::endl;
	printDashes();
	int add_remove_elems{}, number_added_removed_elems{}; char symbol{};//���������� ��� ������ � ���������� �������� ������ ��������� ������� �������.
	bool cycle{ true }; int numberActions{};//���������� ��� ������ � �������������.
	while (cycle)
	{
		numberActions++;
		add_remove_elems = static_cast<int>(getRandomNumber(1, 100));
		number_added_removed_elems = static_cast<int>(getRandomNumber(1, 3));
		if (add_remove_elems % 2 == 0)
		{
			std::cout << numberActions << ": � ������� ����� ��������(-�) " << number_added_removed_elems << " �������(-�,-��)." << std::endl;
			for (int i{ number_added_removed_elems }; i > 0; i--)
			{
				symbol = static_cast<char>(getRandomNumber(65, 90));
				enQueue(myQueue, symbol);
			}
		}
		else
		{
			std::cout << numberActions << ": �� ������� ����� ������(-�) " << number_added_removed_elems << " �������(-�,-��)." << std::endl;
			for (int i{ number_added_removed_elems }; i > 0; i--)
			{
				if (isEmptyQueue(myQueue))
				{
					std::cout << "�������� �������� " << i << " (�����������(-����)) ��������(-��) �� ������� ����������." << std::endl;
					break;
				}
				else
					deQueue(myQueue);
			}
		}
		printQueue(myQueue);
		if (isSymbolQ())//����� �� ��������� ��� ����� ������������� ������� 'q'.
			break;
		printDashes();
		//Sleep(5000);//Sleep() ������� ����� � �������� ����� �������.
	}
	printDashes();
	clearQueue(myQueue);
	return 0;
}