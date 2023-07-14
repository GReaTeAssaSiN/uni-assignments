#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//Инициализация указателя на список списков.
	ListOfLists* myListOfLists = new ListOfLists{};
	myListOfLists->headListPointer = nullptr;
	myListOfLists->count = 0;
	//Задание заголовочного элемента списка списков.
	List* headerList = new List{};
	headerList->count = 0;
	headerList->headPointer = nullptr;
	headerList->nextList = nullptr;
	headerList->symbolischer_name = 0;
	myListOfLists->headListPointer = headerList;
	//Цикл обработки пользовательского ввода.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			printListOfLists(myListOfLists);
			break;
		case '2':
			searchListOfLists(myListOfLists);
			break;
		case '3':
			addNewElemToListOfLists(myListOfLists, 3);
			break;
		case '4':
			addNewElemToListOfLists(myListOfLists, 4);
			break;
		case '5':
			addNewElemToList(myListOfLists, 5);
			break;
		case '6':
			addNewElemToList(myListOfLists, 6);
			break;
		case '7':
			removeElemOfList(myListOfLists);
			break;
		case '8':
			removeList(myListOfLists);
			break;
		case '9':
			clearListOfLists(myListOfLists);
			cycle = false;
			break;
		default:;
		}
		printDashes();
	}
	return 0;
}