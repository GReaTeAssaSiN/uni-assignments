#include <iostream>
#include <string>
#include "myfuncs.h"

/*ПОЛЬЗОВАТЕЛЬСКОЕ МЕНЮ*/
//Пользовательское меню.
void MenuForChoices()
{
	std::cout << "Что вы хотите сделать?" << std::endl <<
		"1) Добавить вершину в произвольное двоичное дерево." << std::endl <<
		"2) Построчный вывод произвольного двоичного дерева на основе процедуры обхода в прямом порядке." << std::endl <<
		"3) Построчный вывод произвольного двоичного дерева на основе процедуры обхода в симметричном порядке." << std::endl <<
		"4) Построчный вывод произвольного двоичного дерева на основе процедуры обхода в обратно-симметричном порядке." << std::endl <<
		"5) Поиск вершины произвольного двоичного дерева с заданной информационной частью." << std::endl <<
		"6) Полностью уничтожить произвольное двоичное дерево." << std::endl <<
		"7) Выход." << std::endl;
}
//Запрос действий с двоичным деревом у пользователя.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
			return choice[0];
		else
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 7). Повторите ввод:" << std::endl;
	}
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
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
//Запрос иниформационной части элемента у пользователя.
std::string getElem()
{
	std::cout << "Введите информационную часть элемента (целое число) или 'q', чтобы выйти в меню: ";
	while (true)
	{
		std::string new_elem{};
		std::getline(std::cin, new_elem);
		if (checkStrIsNumeric(new_elem) || new_elem == "q")
			return new_elem;
		else
			std::cout << "Ошибка ввода. Вы должны ввести целое число или 'q'. Повторите ввод: ";
	}
}
//Запрос у пользователя выбора левого или правого потомка родительской вершины.
std::string getChoiceLeftRight()
{
	std::cout << "Вы хотите добавить левого (l) или правого (r) потомка текущей вершины? ";
	while (true)
	{
		std::string left_right{};
		std::getline(std::cin, left_right);
		if (left_right == "l" || left_right == "r")
			return left_right;
		else
			std::cout << "Ошибка ввода. Вы должны ввести 'l' или 'r'. Повторите ввод: ";
	}
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Добавление новой вершины в произвольное двоичное дерево.
void createNewNode(Tree*& binary_tree)
{
	if (binary_tree->root != nullptr)
	{
		Node* parentNode{ nullptr };
		bool flag = false;
		order_1(binary_tree->root);
		std::cout << "Введите информационную часть вершины произвольного двоичного дерева, после которой хотите добавить потомка, или выйдите в меню." << std::endl;
		while (true)
		{
			std::string parent_data_or_exit{ getElem() };
			if (parent_data_or_exit != "q")
			{
				searchPBT(binary_tree->root, convertStrToInt(parent_data_or_exit), flag, parentNode);
				if (parentNode != nullptr)
				{
					std::cout << "Искомая вершина дерева с информационной частью '" << parentNode->data << "' была успешно найдена на уровне '" <<
						parentNode->level << "'." << std::endl;
					if (parentNode->left != nullptr && parentNode->right != nullptr)
						std::cout << "Указанная вершина уже имеет двух потомков. Добавление новых невозможно." << std::endl;
					else
					{
						Node* new_node = new Node{};
						std::cout << "Задайте информационную часть вершины дерева - потомка, или выйдите в меню." << std::endl;
						while (true)
						{
							std::string new_node_data_or_exit{getElem()};
							if (new_node_data_or_exit != "q")
							{
								new_node->level = parentNode->level + 1;
								new_node->data = convertStrToInt(new_node_data_or_exit);
								binary_tree->number_vertices++;
								if (parentNode->left == nullptr && parentNode->right == nullptr)
								{
									std::string userChoice{ getChoiceLeftRight() };
									if (userChoice == "l")
										parentNode->left = new_node;
									else
										parentNode->right = new_node;
								}
								else if (parentNode->left == nullptr) 
									parentNode->left = new_node;
								else 
									parentNode->right = new_node;
								std::cout << "Новая вершина с информационной частью '" << new_node->data << "' была успешно добавлена в дерево." << std::endl;
								break;
							}
							else
								break;
						}
					}
					break;
				}
				else
					std::cout << "В текущем дереве нет искомой вершины. Повторите ввод или выйдите в меню." << std::endl;
			}
			else
				break;
		}
	}
	else
	{
		std::cout << "Произвольное двоичное дерево пустое на данный момент, добавьте корневую вершину или введите 'q', чтобы выйти в меню." << std::endl;
		while (true)
		{
			std::string new_root_or_exit{ getElem() };
			if (new_root_or_exit != "q")
			{
				binary_tree->root = new Node{};
				binary_tree->root->level = 0;
				binary_tree->root->data = convertStrToInt(new_root_or_exit);
				binary_tree->number_vertices++;
				std::cout << "Корень дерева с информационной частью '" << binary_tree->root->data << "' был успешно создан." << std::endl;
			}
			break;
		}
	}
}
//Прямой обход ИСД.
void order_1(Node*& tree_root)
{
	if (tree_root == nullptr)
		return;
	else
	{
		std::cout << std::string(tree_root->level * 5, ' ');
		std::cout << tree_root->data << std::endl;
		order_1(tree_root->left);
		order_1(tree_root->right);
	}
}
//Симметричный обход ИСД.
void order_2(Node*& tree_root)
{
	if (tree_root == nullptr)
		return;
	else
	{
		order_2(tree_root->left);
		std::cout << std::string(tree_root->level * 5, ' ');
		std::cout << tree_root->data << std::endl;
		order_2(tree_root->right);
	}
}
//Обратно-симметричный обход ИСД.
void order_3(Node*& tree_root)
{
	if (tree_root == nullptr)
		return;
	else {
		order_3(tree_root->right);
		std::cout << std::string(tree_root->level * 5, ' ');
		std::cout << tree_root->data << std::endl;
		order_3(tree_root->left);
	}
}
//Обработка запроса пользователя о поиске вершины в ИСД.
void userSearchNodePBT(Node* tree_root)
{
	while (true)
	{
		std::string searched_node_data_or_exit{ getElem() };
		if (searched_node_data_or_exit != "q")
		{
			int searched_node_data{ convertStrToInt(searched_node_data_or_exit) };
			Node* parentNode{ nullptr };
			bool succesfully_recursion{};
			order_1(tree_root);
			searchPBT(tree_root, searched_node_data, succesfully_recursion, parentNode);
			if (parentNode != nullptr)
			{
				std::cout << "Искомая вершина произвольного двоичного дерева с информационной частью '" << parentNode->data << "' была успешно найдена на уровне '" 
					<< parentNode->level << "'." << std::endl;
				break;
			}
			else
				std::cout << "В данном произвольном двоичном дереве нет вершин с заданной информационной частью. Повторите ввод или выйдите в меню." << std::endl;
		}
		else
			break;
	}
}
//Поиск вершины ИСД с заданной информационной частью.
void searchPBT(Node* tree_root, const int& searched_data, bool& succesful_recursion, Node*& parentNode)
{
	if (!succesful_recursion)
	{
		if (tree_root != nullptr)
		{
			if (tree_root->data == searched_data)
			{
				succesful_recursion = true;
				parentNode = tree_root;
			}
			else
			{
				searchPBT(tree_root->left, searched_data, succesful_recursion, parentNode);
				searchPBT(tree_root->right, searched_data, succesful_recursion, parentNode);
			}
		}
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
//Полностью уничтожить все дерево.
void DestroyAllTree(Node*& tree_root)
{
	if (tree_root != nullptr)
	{
		DestroyAllTree(tree_root->left);
		DestroyAllTree(tree_root->right);
		std::cout << "Вершина " << tree_root->data << " была успешно удалена." << std::endl;
		delete tree_root;
	}
}