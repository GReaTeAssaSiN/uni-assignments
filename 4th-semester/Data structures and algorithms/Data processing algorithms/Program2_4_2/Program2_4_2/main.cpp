#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	HashTable* hash_table = new HashTable{};
	hash_table->number_m = getNumberM();
	hash_table->array = new std::string[hash_table->number_m]{};
	printDashes();
	//���� ��������� ����������������� �����.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			addNewKeyToHashTable(hash_table);
			break;
		case '2':
			searchKeyInHashTable(hash_table);
			break;
		case '3':
			printHashTable(hash_table);
			break;
		case '0':
			cycle = false;
			delete[] hash_table->array;
			delete hash_table;
			std::cout << "��� ���������� ������������ ������ ��� ���-������� ���� ���������� � ����.\n���������� ��������� . . ." << std::endl;
			break;
		default:;
		}
		printDashes();
	}
	return 0;
}