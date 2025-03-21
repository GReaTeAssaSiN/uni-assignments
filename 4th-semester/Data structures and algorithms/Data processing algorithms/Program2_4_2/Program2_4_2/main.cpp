#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	HashTable* hash_table = new HashTable{};
	hash_table->number_m = getNumberM();
	hash_table->array = new std::string[hash_table->number_m]{};
	printDashes();
	//Цикл обработки пользовательского ввода.
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
			std::cout << "Вся выделенная динамическая память для хеш-таблицы была возвращена в кучу.\nЗавершение программы . . ." << std::endl;
			break;
		default:;
		}
		printDashes();
	}
	return 0;
}