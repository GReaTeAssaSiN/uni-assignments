#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	List myList{};
	myList.count = 0;
	for (int i{}; i < size + 1; i++)
		myList.Refs[i] = -1;
	myList.Refs[0] = 1;
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
			addNewElem(myList, 3);
			break;
	    case '4':
			addNewElem(myList, 4);
			break;
		case '5':
			removeElem(myList);
			break;
		case '6':
			cycle = false;
			break;
		default:;
		}
		printDashes();
	}
	return 0;
}