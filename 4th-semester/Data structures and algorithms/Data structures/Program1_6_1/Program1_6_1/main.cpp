#include <iostream>
#include <cstdlib> //для функций rand() и srand()
#include <ctime> //для функции time()
#include "myfuncs.h"

int main()
{
	std::setlocale(LC_ALL, "Rus");
	//Привзяка ГПСЧ к календарному времени (случайные последовательности случайных чисел из диапазона).
	srand(static_cast<unsigned int>(time(0)));
	//Задание корня поискового дерева.
	Tree* binary_tree = new Tree{};
	binary_tree->root = nullptr;
	binary_tree->number_vertices = 0;
	//Цикл обработки пользовательского ввода.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			if (isBinaryTreeEmpty(binary_tree->root))
				userCase1(binary_tree);
			else
				std::cout << "Поисковое дерево уже было построено. Удалите старое прежде, чем создать новое данной командой." << std::endl;
			break;
		case '2':
			userCase2(binary_tree);
			break;
		case '3':
			std::cout << "Количество элементов поискового дерева: " << binary_tree->number_vertices << std::endl;
			if (!isBinaryTreeEmpty(binary_tree->root))
				userCase3(binary_tree->root);
			else
				std::cout << "Сначала необходимо создать двоичное поисковое дерево." << std::endl;
			break;
		case '4':
			std::cout << "Количество элементов поискового дерева: " << binary_tree->number_vertices << std::endl;
			if (!isBinaryTreeEmpty(binary_tree->root))
				userCase4(binary_tree->root);
			else
				std::cout << "Сначала необходимо создать двоичное поисковое дерево." << std::endl;
			break;
		case '5':
			if (!isBinaryTreeEmpty(binary_tree->root))
				userCase5(binary_tree->root);
			else
				std::cout << "Сначала необходимо создать двоичное поисковое дерево." << std::endl;
			break;
		case '6':
			if (!isBinaryTreeEmpty(binary_tree->root))
				userCase6(binary_tree);
			else
				std::cout << "Сначала необходимо создать двоичное поисковое дерево." << std::endl;
			break;
		case '7':
			if (!isBinaryTreeEmpty(binary_tree->root))
				userCase7(binary_tree);
			else
				std::cout << "Сначала необходимо создать двоичное поисковое дерево." << std::endl;
			break;
		case '8':
			userCase8(binary_tree);
			cycle = false;
			break;
		default:;
		}
		printDashes();
	}
	return 0;
}
