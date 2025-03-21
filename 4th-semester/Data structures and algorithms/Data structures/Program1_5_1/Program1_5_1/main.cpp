#include <iostream>
#include <cstdlib> //для функций rand() и srand()
#include <ctime> //для функции time()
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//Привзяка ГПСЧ к календарному времени (случайные последовательности случайных чисел из диапазона).
	srand(static_cast<unsigned int>(time(0)));
	//Задание корня дерева.
	Tree* binary_tree = new Tree{};
	binary_tree->number_vertices = getNumberVertices();
	//Цикл обработки пользовательского ввода.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			recursivelyBuildingPBT(binary_tree->root, binary_tree->number_vertices);
			std::cout << "Идеально сбалансированное двоичное дерево построено." << std::endl;
			break;
		case '2':
			if (empty_tree(binary_tree->root))
				std::cout << "Операция не может быть выполнена, сначала необходимо построить ИСД." << std::endl;
			else
				order_1(binary_tree->root, 0);
			break;
		case '3':
			if (empty_tree(binary_tree->root))
				std::cout << "Операция не может быть выполнена, сначала необходимо построить ИСД." << std::endl;
			else
				order_2(binary_tree->root, 0);
			break;
		case '4':
			if (empty_tree(binary_tree->root))
				std::cout << "Операция не может быть выполнена, сначала необходимо построить ИСД." << std::endl;
			else
				order_3(binary_tree->root, 0);
			break;
		case '5':
			getNewNumberVertices(binary_tree);
			break;
		case '6':
			clearBinaryTree(binary_tree);
			cycle = false;
			std::cout << "Вся выделенная динамическая память была возвращена в кучу. Завершение программы . . ." << std::endl;
			break;
		}
		printDashes();
	}
	return 0;
}