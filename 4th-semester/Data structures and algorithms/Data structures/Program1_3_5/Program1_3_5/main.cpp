#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//Инициализация указателей на будущие списки.
	List* myList = new List{}, * auxiliary_myList = new List{};
	myList->listPointer = nullptr, auxiliary_myList->listPointer = nullptr;
	//Задание заголовочного элемента основного списка.
	Node* head_node = new Node{};
	myList->listPointer = head_node;
	myList->listPointer->data = 0;
	myList->listPointer->next = nullptr;
	//Задание заголовочного элемента вспомогательного списка(стека).
	Node* sp_node = new Node{};
	auxiliary_myList->listPointer = sp_node;
	auxiliary_myList->listPointer->data = 0;
	auxiliary_myList->listPointer->next = nullptr;
	//Цикл обработки пользовательского ввода.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			printList(myList);
			break;
		case '2':
			searchList(myList);
			break;
		case '3':
			addNewElem(myList, auxiliary_myList, 3);
			break;
		case '4':
			addNewElem(myList, auxiliary_myList, 4);
			break;
		case '5':
			removeElem(myList, auxiliary_myList);
			break;
		case '6':
			printList(auxiliary_myList);
			break;
		case '7':
			clearList(myList, auxiliary_myList);
			cycle = false;
			break;
		default:;
		}
		printDashes();
	}
	return 0;
}