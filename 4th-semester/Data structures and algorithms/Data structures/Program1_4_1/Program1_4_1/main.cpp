#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//Инициализация указателя на двунаправленный список.
	List* myList = new List{};
	myList->listPointer = nullptr;
	//Задание заголовочного элемента двунаправленного писка.
	Node* head_node = new Node{};
	myList->listPointer = head_node;
	myList->listPointer->data = 0;
	myList->listPointer->next = head_node;
	myList->listPointer->prev = head_node;
	//Цикл обработки пользовательского ввода.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			printList(myList, 1);
			break;
		case '2':
			printList(myList, 2);
			break;
		case '3':
			searchList(myList, 3);
			break;
		case '4':
			searchList(myList, 4);
			break;
		case '5':
			addNewElem(myList, 5);
			break;
		case '6':
			addNewElem(myList, 6);
			break;
		case '7':
			removeElem(myList);
			break;
		case '8':
			clearList(myList);
			cycle = false;
			break;
		default:;
		}
		printDashes();
	}
	return 0;
}