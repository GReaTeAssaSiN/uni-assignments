#include <iostream>
#include <string>
#include "myfuncs.h"

/*ПОЛЬЗОВАТЕЛЬСКОЕ МЕНЮ*/
//Пользовательское меню.
void MenuForChoices()
{
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1) Построение идеально сбалансированного двоичного дерева (ИСД) с заданным числом вершин." << std::endl <<
		"2) Построчный вывод дерева на основе процедуры обхода в прямом порядке." << std::endl <<
		"3) Построчный вывод дерева на основе процедуры обхода в симметричном порядке." << std::endl <<
		"4) Построчный вывод дерева на основе процедуры обхода в обратно-симметричном порядке." << std::endl <<
		"5) Выбор нового количества вершин в двоичном дереве." << std::endl <<
		"6) Выход." << std::endl;
}
//Запрос дейтсвий с двоичным деревом у пользователя.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6")
			return choice[0];
		else
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 6). Повторите ввод:" << std::endl;
	}
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//ГПСЧ
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}
//Проверка введённой пользователем строки на возможность преобразования в целое число.
bool checkStrIsNumeric(std::string const& tempStr)
{
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((i == 0) && (tempStr[i] == '-'))
			continue;
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//Преобразование введённой пользователем строки в число.
int convertStrToInt(std::string convertStr)
{
	double number{};
	bool negative_number{ false };
	for (int i{}; i < convertStr.length(); i++)
	{
		if ((i == 0) && (convertStr[i] == '-'))
		{
			negative_number = true;
			continue;
		}
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
	}
	return negative_number ? static_cast<int>(-number) : static_cast<int>(number);
}
//Вывод визуального разделения между действиями пользователя в консоль.
void printDashes()
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << "\t" << std::endl;
}
//Запрос у пользователя желания ввода нового числа вершин в двоичном дереве.
void getNewNumberVertices(Tree*& binary_tree)
{
	while (true)
	{
		std::cout << "Вы хотите ввести новое количество вершин?(yes/no)" << std::endl;
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "yes")
		{ 
			clearBinaryTree(binary_tree);
			binary_tree = new Tree{};
			binary_tree->number_vertices = getNumberVertices();
			break;
		}
		else if (choice == "no")
			break;
		else
			std::cout << "Ошибка ввода. Вы должны ввести 'yes' или 'no'. Повторите ввод." << std::endl;
	}
}


/*ОСНОВНЫЕ ФУНКЦИИ*/
//Запрос числа вершин двоичного дерева у пользователя.
int getNumberVertices()
{
	std::cout << "Введите число вершин идеально сбалансированного дерева(ИСД): ";
	while (true)
	{
		std::string number_vertices{};
		std::getline(std::cin, number_vertices);
		if (checkStrIsNumeric(number_vertices) && convertStrToInt(number_vertices) > 0)
			return convertStrToInt(number_vertices);
		else
			std::cout << "Ошибка ввода. Вы должны ввести целое положительное число. Повторите ввод: ";
	}
}
//Проверка пустоты двоичного дерева.
bool empty_tree(Node* tree_root)
{
	return tree_root == nullptr ? true : false;
}
//Рекурсивное построение идельно сбалансированного дерева (ИСД).
void recursivelyBuildingPBT(Node*& tree_root, int count)
{
	if (count == 0)
		return;
	else
	{
		tree_root = new Node{};
		tree_root->data = static_cast<int>(getRandomNumber(0, 99));
		recursivelyBuildingPBT(tree_root->left, (count - 1) / 2 + (count - 1) % 2);
		recursivelyBuildingPBT(tree_root->right, (count - 1) / 2);
	}
}
//Прямой обход ИСД.
void order_1(Node*& tree_root, int level) 
{
	if (empty_tree(tree_root))
		return;
	else 
	{
		std::cout << std::string(level * 5, ' ');
		std::cout << tree_root->data << std::endl;
		order_1(tree_root->left, level + 1);
		order_1(tree_root->right, level + 1);
	}
}
//Симметричный обход ИСД.
void order_2(Node*& tree_root, int level) 
{
	if (empty_tree(tree_root))
		return;
	else
	{
		order_2(tree_root->left, level + 1);
		std::cout << std::string(level * 5, ' ');
		std::cout << tree_root->data << std::endl;
		order_2(tree_root->right, level + 1);
	}
}
//Обратно-симметричный обход ИСД.
void order_3(Node*& tree_root, int level) 
{
	if (empty_tree(tree_root))
		return;
	else {
		order_3(tree_root->right, level + 1);
		std::cout << std::string(level * 5, ' ');
		std::cout << tree_root->data << std::endl;
		order_3(tree_root->left, level + 1);
	}
}
//Очистка выделенной динамической памяти под двоичное дерево.
void clearTreeNodes(Node*& tree_root)
{
	if (tree_root != nullptr)
	{
		clearTreeNodes(tree_root->left);
		clearTreeNodes(tree_root->right);
		delete tree_root;
	}
}
void clearBinaryTree(Tree*& binary_tree)
{
	clearTreeNodes(binary_tree->root);
	delete binary_tree;
}