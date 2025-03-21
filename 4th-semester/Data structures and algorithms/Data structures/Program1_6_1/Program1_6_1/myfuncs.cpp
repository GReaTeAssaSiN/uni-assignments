#include <iostream>
#include <string>
#include "myfuncs.h"

/*ПОЛЬЗОВАТЕЛЬСКОЕ МЕНЮ*/
//Пользовательское меню.
void MenuForChoices()
{
	std::cout << "Что вы хотите сделать с двоичным поисковым деревом?" << std::endl <<
		"1) Построить поисковое дерево с заданным числом вершин со случайными ключами." << std::endl <<
		"2) Добавить новую вершину в поисковое дерево." << std::endl <<
		"3) Построчный вывод поискового дерева на основе процедуры обхода в обратно-симметричном порядке." << std::endl <<
		"4) Вывести все вершины поискового дерева в одну строку по порядку следования ключей с указанием для каждой вершины значения ее счетчика появлений." << std::endl <<
		"5) Найти вершину с заданным значением ключа и выводом счетчика числа появлений данного ключа в поисковом дереве." << std::endl <<
		"6) Удалить вершину с заданным значением ключа из поискового дерева." << std::endl <<
		"7) Полностью уничтожить произвольное двоичное дерево." << std::endl <<
		"8) Выход." << std::endl;
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
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8")
			return choice[0];
		else
		{
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер Вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 8). Повторите ввод." << std::endl;
			printDashes();
		}
	}
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//ГПСЧ
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}
//Выбор рекурсивного/нерекурсивного добавления вершины.
std::string get0_1()
{
	while (true)
	{
		std::string zero_or_one{};
		std::getline(std::cin, zero_or_one);
		if (zero_or_one == "q" || zero_or_one == "0" || zero_or_one == "1")
			return zero_or_one;
		else
			std::cout << "Ошибка ввода. Вы должны ввести '0', '1' или 'q'. Повторите ввод: ";
	}
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
//Запрос иниформационной части элемента у пользователя.
std::string getElem()
{
	std::cout << "Введите информационную часть элемента - ключ (целое число), или 'q', чтобы выйти в меню: ";
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
//Переопределение указателей при удалении вершины из поискового дерева.
void changePointersOnDeletion(Node*& tree_root, Node*& changing_parent, Node*& changing_child)
{
	if (changing_parent->parent == nullptr)//Если изменяется указатель корня дерева.
		tree_root = changing_child;
	else if (changing_parent == changing_parent->parent->left)//Если изменяется указатель родителя, являющегося левым потомком.
		changing_parent->parent->left = changing_child;
	else//Если изменяется указатель родителя, являющегося правым потомком.
		changing_parent->parent->right = changing_child;
	if (changing_child != nullptr)//Если изменяется ненулевой указатель ребенка.
		changing_child->parent = changing_parent->parent;
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Проверка пустоты поискового дерева.
bool isBinaryTreeEmpty(Node* tree_root)
{
	return (tree_root == nullptr) ? true : false;
}
//Поиск вершины в поисковом дереве.
Node* searchTreeNode(Node*& tree_root, const int& searched_key)
{
	if (tree_root == nullptr || tree_root->key == searched_key)
		return tree_root;
	else
	{
		if (searched_key < tree_root->key)
			return searchTreeNode(tree_root->left, searched_key);
		else
			return searchTreeNode(tree_root->right, searched_key);
	}
}
//Добавление новой вершины в поисковое дерево не рекурсивно.
void addNewNodeToTreeNonRecursive(Node*& tree_root, const int& adding_key)
{
	Node* parent{};
	Node* current{ tree_root };
	//Поиск подходящего места.
	while (current != nullptr)
	{
		parent = current;
		if (adding_key < current->key)
			current = current->left;
		else if (adding_key > current->key)
			current = current->right;
		else
		{
			++current->count;
			std::cout << "Добавляемый ключ '" << adding_key << "' уже присутствует в поисковом дереве. Счетчик данного ключа увеличен до '" << current->count << "'." << std::endl;
			return;
		}
	}
	//Добавление новой вершины.
	try
	{
		Node* newNode = new Node{};
		newNode->parent = parent;
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->key = adding_key;
		++newNode->count;
		if (parent == nullptr)
			tree_root = newNode;
		else if (newNode->key < parent->key)
			parent->left = newNode;
		else
			parent->right = newNode;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
		DestroyAllTree(tree_root);
		exit(-1);
	}
}
//Добавление новой вершины в поисковое дерево рекурсивно.
Node* addNewNodeToTreeRecursive(Node*& tree_root, Node* parent, const int& adding_key)
{
	if (tree_root == nullptr)
	{
		try
		{
			tree_root = new Node{};
			tree_root->parent = parent;
			tree_root->left = nullptr;
			tree_root->right = nullptr;
			tree_root->key = adding_key;
			++tree_root->count;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
			DestroyAllTree(tree_root);
			exit(-1);
		}
	}
	else
	{
		parent = tree_root;
		if (adding_key < tree_root->key)
			tree_root->left = addNewNodeToTreeRecursive(tree_root->left, parent, adding_key);
		else if (adding_key > tree_root->key)
			tree_root->right = addNewNodeToTreeRecursive(tree_root->right, parent, adding_key);
		else
		{
			++tree_root->count;
			std::cout << "Добавляемый ключ '" << adding_key << "' уже присутствует в поисковом дереве. Счетчик данного ключа увеличен до '" << tree_root->count << "'." << std::endl;
		}
	}
	return tree_root;
}
//Рекурсивный вывод поискового дерева в обратно-симметричном порядке.
void printTreeInBackwardSymmetricOrder(Node*& tree_root, int level)
{
	if (tree_root == nullptr)
		return;
	else {
		printTreeInBackwardSymmetricOrder(tree_root->right, level + 1);
		std::cout << std::string(level * 5, ' ');
		std::cout << tree_root->key << std::endl;
		printTreeInBackwardSymmetricOrder(tree_root->left, level + 1);
	}
}
//Рекурсивный вывод всех вершин поискового дерева в порядке возрастания их ключей в одну строку.
void printTreeInSymmetricalOrderWithCount(Node*& tree_root)
{
	if (tree_root == nullptr)
		return;
	else
	{
		printTreeInSymmetricalOrderWithCount(tree_root->left);
		std::cout << tree_root->key << "(" << tree_root->count << ") ";
		printTreeInSymmetricalOrderWithCount(tree_root->right);
	}
}
//Удаление вершины из поискового дерева.
void removeNodeFromTree(Node*& tree_root, const int& removing_key)
{
	Node* removing_node = searchTreeNode(tree_root, removing_key);//Ищем удаляемый узел в поисковом дереве.
	if (!removing_node)//Если удаляемый узел отсутствует.
		std::cout << "Указанный ключ отсутствует в поисковом дереве. Операция удаления ключа невозможна." << std::endl;
	else//Если удаляемый узел присутствует.
	{
		if (removing_node->left == nullptr)//Если существует только правый потомок.
			changePointersOnDeletion(tree_root, removing_node, removing_node->right);
		else if (removing_node->right == nullptr)//Если существует только левый потомок.
			changePointersOnDeletion(tree_root, removing_node, removing_node->left);
		else//Если существуют оба потомка.
		{
			//Замещаем удаляемый узел на самый левый узел в правом поддереве.
			Node* nodeToReplaceRemovingNode = removing_node->right;//Переходим в правое поддерево.
			while (nodeToReplaceRemovingNode->left != nullptr)//Ищем самый левый узел.
				nodeToReplaceRemovingNode = nodeToReplaceRemovingNode->left;
			if (nodeToReplaceRemovingNode->parent != removing_node)//Если правое поддерево состоит не из одного узла.
			{
				changePointersOnDeletion(tree_root, nodeToReplaceRemovingNode, nodeToReplaceRemovingNode->right);
				nodeToReplaceRemovingNode->right = removing_node->right;
				nodeToReplaceRemovingNode->right->parent = nodeToReplaceRemovingNode;
			}
			changePointersOnDeletion(tree_root, removing_node, nodeToReplaceRemovingNode);
			nodeToReplaceRemovingNode->left = removing_node->left;
			nodeToReplaceRemovingNode->left->parent = nodeToReplaceRemovingNode;
		}
		//Удаляем указанный узел.
		std::cout << "Вершина со значением ключа '" << removing_node->key << "' и счетчиком '" << removing_node->count << "' была успешно удалена из поискового дерева." << std::endl;
		removing_node->parent = nullptr;
		removing_node->left = nullptr;
		removing_node->right = nullptr;
		removing_node->key = 0;
		removing_node->count = 0;
		delete removing_node;
	}
}
//Полностью уничтожить все дерево.
void DestroyAllTree(Node*& tree_root)
{
	if (tree_root != nullptr)
	{
		DestroyAllTree(tree_root->left);
		DestroyAllTree(tree_root->right);
		std::cout << "Вершина " << tree_root->key << " была успешно удалена." << std::endl;
		delete tree_root;
	}
}

/*ПОЛЬЗОВАТЕЛЬСКИЕ ЗАПРОСЫ*/
void userCase1(Tree*& binary_tree)
{
	std::cout << "Введите количество вершин поискового дерева (целое положительное число) или 'q', чтобы выйти в меню: " << std::endl;
	while (true)
	{
		std::string count_nodes_or_exit{};
		std::getline(std::cin, count_nodes_or_exit);
		if (count_nodes_or_exit != "q" && checkStrIsNumeric(count_nodes_or_exit) && convertStrToInt(count_nodes_or_exit) > 0)
		{
			int count_nodes{ convertStrToInt(count_nodes_or_exit) };
			std::cout << "Выберите режим добавления вершин или введите 'q', чтобы выйти в меню:\n0 - не рекурсивно;\n1 - рекурсивно." << std::endl;
			while (true)
			{
				std::string zero_or_one_or_exit{ get0_1() };
				if (zero_or_one_or_exit != "q")
				{
					binary_tree->number_vertices = count_nodes;
					int zero_or_one{ convertStrToInt(zero_or_one_or_exit) };
					for (int i{}; i < binary_tree->number_vertices; i++)
					{
						if (zero_or_one == 0)
							addNewNodeToTreeNonRecursive(binary_tree->root, static_cast<int>(getRandomNumber(1, 99)));
						else
							addNewNodeToTreeRecursive(binary_tree->root, nullptr, static_cast<int>(getRandomNumber(1, 99)));
					}
				}
				break;
			}
			break;
		}
		else if (count_nodes_or_exit == "q")
			break;
		else
			std::cout << "Ошибка ввода. Повторите ввод или выйдите в меню: ";
	}
}
void userCase2(Tree*& binary_tree)
{
	std::cout << "Введите вершину (ключ), который необходимо добавить в поисковое дерево, или 'q', чтобы выйти в меню." << std::endl;
	while (true)
	{
		std::string new_key_or_exit{ getElem() };
		if (new_key_or_exit != "q")
		{
			int new_key{ convertStrToInt(new_key_or_exit) };
			std::cout << "Выберите режим добавления вершины или введите 'q', чтобы выйти в меню:\n0 - не рекурсивно;\n1 - рекурсивно." << std::endl;
			std::string zero_or_one_or_exit{ get0_1() };
			if (zero_or_one_or_exit != "q")
			{
				int zero_or_one{ convertStrToInt(zero_or_one_or_exit) };
				if (zero_or_one == 0)
					addNewNodeToTreeNonRecursive(binary_tree->root, new_key);
				else
					addNewNodeToTreeRecursive(binary_tree->root, nullptr, new_key);
				binary_tree->number_vertices++;
			}
			break;
		}
		else
			break;
	}
}
void userCase3(Node*& tree_root)
{
	std::cout << "Вывод поискового дерева в обратно-симметричном порядке:" << std::endl;
	printTreeInBackwardSymmetricOrder(tree_root, 0);
}
void userCase4(Node*& tree_root)
{
	std::cout << "Вывод поискового дерева в одну строку с указанием ключей и соответствующих счетчиков:" << std::endl;
	printTreeInSymmetricalOrderWithCount(tree_root);
	std::cout << std::endl;
}
void userCase5(Node*& tree_root)
{
	std::cout << "Введите ключ, который нужно найти в поисковом дереве, или 'q', чтобы выйти в меню." << std::endl;
	while (true)
	{
		std::string searching_key_or_exit{ getElem() };
		if (searching_key_or_exit != "q")
		{
			int searching_key{ convertStrToInt(searching_key_or_exit) };
			Node* searching_node = searchTreeNode(tree_root, searching_key);
			if (searching_node)
			{
				std::cout << "Указанный ключ '" << searching_node->key << "' был успешно найден в поисковом дереве." << std::endl;
				std::cout << "Счетчик ключа равен '" << searching_node->count << "'." << std::endl;
				break;
			}
			else
				std::cout << "Указанный ключ отсутствует в поисковом дереве. Повторите ввод или выйдите в меню." << std::endl;
		}
		else
			break;
	}
}
void userCase6(Tree*& binary_tree)
{
	printTreeInBackwardSymmetricOrder(binary_tree->root, 0);
	std::cout << "Введите вершину (ключ), который необходимо удалить из поискового дерева, или 'q', чтобы выйти в меню." << std::endl;
	while (true)
	{
		std::string removing_key_or_exit{ getElem() };
		if (removing_key_or_exit != "q")
		{
			int removing_key{ convertStrToInt(removing_key_or_exit) };
			removeNodeFromTree(binary_tree->root, removing_key);
			binary_tree->number_vertices--;
		}
		break;
	}
}
void userCase7(Tree*& binary_tree)
{
	DestroyAllTree(binary_tree->root);
	binary_tree->number_vertices = 0;
	binary_tree->root = nullptr;
	std::cout << "Поисковое дерево было успешно удалено. Корень остался пустым." << std::endl;
}
void userCase8(Tree*& binary_tree)
{
	DestroyAllTree(binary_tree->root);
	delete binary_tree;
	std::cout << "Вся выделенная память была возвращена в кучу. Завершение программы . . ." << std::endl;
}