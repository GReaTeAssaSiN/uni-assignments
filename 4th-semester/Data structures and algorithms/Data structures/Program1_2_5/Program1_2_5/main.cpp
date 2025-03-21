#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	Queue myQueue{};
	myQueue.frnt = -1, myQueue.rear = -1;
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			if (isEmptyQueue(myQueue))
				std::cout << "Очередь пуста." << std::endl;
			else
			{
				if (myQueue.frnt <= myQueue.rear)
					std::cout << "Очередь не пуста. Она содержит " << myQueue.rear - myQueue.frnt + 1 << " элемент(-а, -ов)" << std::endl;
				else
					std::cout << "Очередь не пуста. Она содержит " << (sizeQueue - myQueue.frnt) + (myQueue.rear + 1) << " элемент(-а, -ов)" << std::endl;
			}
			break;
		case '2':
			if (isFullnessQueue(myQueue))
				std::cout << "Очередь заполнена. " << std::endl;
			else
				if (myQueue.frnt != -1 && myQueue.rear != -1)
				{
					if (myQueue.frnt <= myQueue.rear)
						std::cout << "Очередь не заполнена. В ней доступно для заполнения " << sizeQueue - (myQueue.rear - myQueue.frnt + 1) << " элемент(-а, -ов)." << std::endl;
					else
						std::cout << "Очередь не заполнена. В ней доступно для заполнения " << sizeQueue - ((sizeQueue - myQueue.frnt) + (myQueue.rear + 1)) << " элемент(-а, -ов)." << std::endl;
				}
				else
					std::cout << "Очередь не заполнена. В ней доступно для заполнения " << sizeQueue << " элемент(-а, -ов)." << std::endl;
			break;
		case '3':
			enQueue(myQueue);
			break;
		case '4':
			deQueue(myQueue);
			break;
		case '5':
			printQueue(myQueue);
			break;
		case '6':
			cycle = false;
			break;
		default:;
		}
		std::cout << std::endl;
	}
	return 0;
}