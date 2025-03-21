#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	Stack* baseStack = new Stack{}, * auxiliaryStack = new Stack{};
	baseStack->sp = nullptr, auxiliaryStack->sp = nullptr;
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			if (isEmpty(baseStack))
				std::cout << "Основной стек пуст." << std::endl;
			else
				std::cout << "Основной стек содержит " << baseStack->count << " элемент(-а, -ов)." << std::endl;
			break;
		case '2':
			user_push(baseStack, auxiliaryStack);
			break;
		case '3':
			user_push_random(baseStack);
			break;
		case '4':
			user_pop(baseStack, auxiliaryStack);
			break;
		case '5':
			user_printBaseStack(baseStack);
			break;
		case '6':
			user_printAuxiliaryStack(auxiliaryStack);
			break;
		case '7':
			user_clear(baseStack, auxiliaryStack);
			cycle = false;
			break;
		default:;
		}
		std::cout << std::endl;
	}
	return 0;
}