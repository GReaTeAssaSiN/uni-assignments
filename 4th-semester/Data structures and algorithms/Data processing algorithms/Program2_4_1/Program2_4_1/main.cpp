#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	HashTable hash_table{};
	auxiliaryProgram(hash_table);
	printHashTable(hash_table);
	getKeyAndInformationFromUser(hash_table);
	return 0;
}