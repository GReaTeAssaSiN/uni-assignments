#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	List myList{};
	myList.count = 0;
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
			addNewElem(myList);
			break;
		case '4':
			removeElem(myList);
			break;
		case '5':
			cycle = false;
			break;
		default:;
		}
		printDashes();
	}
	return 0;
}