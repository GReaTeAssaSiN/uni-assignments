#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	HashTable* hash_table = new HashTable{};
	hash_table->number_m = getNumberM();
	hash_table->array = new Element[hash_table->number_m]{};
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
		case '4':
			deleteKeyFromHashTable(hash_table);
			break;
		case '0':
			cycle = false;
			for (int i{}; i < hash_table->number_m; i++)
			{
				if (!hash_table->array[i].key.empty())
				{
					Node* temp_node{ hash_table->array[i].head };
					while (temp_node->next != nullptr)
					{
						temp_node->next = temp_node->next->next;
						delete temp_node->next;
					}
					delete temp_node;
					hash_table->array[i].head = nullptr;
					hash_table->array[i].tail = hash_table->array[i].head;
					hash_table->array[i].key.clear();
				}
			}
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