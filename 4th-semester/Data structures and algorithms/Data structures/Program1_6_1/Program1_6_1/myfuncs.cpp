#include <iostream>
#include <string>
#include "myfuncs.h"

/*���������������� ����*/
//���������������� ����.
void MenuForChoices()
{
	std::cout << "��� �� ������ ������� � �������� ��������� �������?" << std::endl <<
		"1) ��������� ��������� ������ � �������� ������ ������ �� ���������� �������." << std::endl <<
		"2) �������� ����� ������� � ��������� ������." << std::endl <<
		"3) ���������� ����� ���������� ������ �� ������ ��������� ������ � �������-������������ �������." << std::endl <<
		"4) ������� ��� ������� ���������� ������ � ���� ������ �� ������� ���������� ������ � ��������� ��� ������ ������� �������� �� �������� ���������." << std::endl <<
		"5) ����� ������� � �������� ��������� ����� � ������� �������� ����� ��������� ������� ����� � ��������� ������." << std::endl <<
		"6) ������� ������� � �������� ��������� ����� �� ���������� ������." << std::endl <<
		"7) ��������� ���������� ������������ �������� ������." << std::endl <<
		"8) �����." << std::endl;
}
//������ �������� � �������� ������� � ������������.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8")
			return choice[0];
		else
		{
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 8). ��������� ����." << std::endl;
			printDashes();
		}
	}
}

/*��������������� �������*/
//����
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}
//����� ������������/�������������� ���������� �������.
std::string get0_1()
{
	while (true)
	{
		std::string zero_or_one{};
		std::getline(std::cin, zero_or_one);
		if (zero_or_one == "q" || zero_or_one == "0" || zero_or_one == "1")
			return zero_or_one;
		else
			std::cout << "������ �����. �� ������ ������ '0', '1' ��� 'q'. ��������� ����: ";
	}
}
//�������� �������� ������������� ������ �� ����������� �������������� � ����� �����.
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
//�������������� �������� ������������� ������ � �����.
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
//����� ����������� ���������� ����� ���������� ������������ � �������.
void printDashes()
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << "\t" << std::endl;
}
//������ ��������������� ����� �������� � ������������.
std::string getElem()
{
	std::cout << "������� �������������� ����� �������� - ���� (����� �����), ��� 'q', ����� ����� � ����: ";
	while (true)
	{
		std::string new_elem{};
		std::getline(std::cin, new_elem);
		if (checkStrIsNumeric(new_elem) || new_elem == "q")
			return new_elem;
		else
			std::cout << "������ �����. �� ������ ������ ����� ����� ��� 'q'. ��������� ����: ";
	}
}
//��������������� ���������� ��� �������� ������� �� ���������� ������.
void changePointersOnDeletion(Node*& tree_root, Node*& changing_parent, Node*& changing_child)
{
	if (changing_parent->parent == nullptr)//���� ���������� ��������� ����� ������.
		tree_root = changing_child;
	else if (changing_parent == changing_parent->parent->left)//���� ���������� ��������� ��������, ����������� ����� ��������.
		changing_parent->parent->left = changing_child;
	else//���� ���������� ��������� ��������, ����������� ������ ��������.
		changing_parent->parent->right = changing_child;
	if (changing_child != nullptr)//���� ���������� ��������� ��������� �������.
		changing_child->parent = changing_parent->parent;
}

/*�������� �������*/
//�������� ������� ���������� ������.
bool isBinaryTreeEmpty(Node* tree_root)
{
	return (tree_root == nullptr) ? true : false;
}
//����� ������� � ��������� ������.
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
//���������� ����� ������� � ��������� ������ �� ����������.
void addNewNodeToTreeNonRecursive(Node*& tree_root, const int& adding_key)
{
	Node* parent{};
	Node* current{ tree_root };
	//����� ����������� �����.
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
			std::cout << "����������� ���� '" << adding_key << "' ��� ������������ � ��������� ������. ������� ������� ����� �������� �� '" << current->count << "'." << std::endl;
			return;
		}
	}
	//���������� ����� �������.
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
		std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
		DestroyAllTree(tree_root);
		exit(-1);
	}
}
//���������� ����� ������� � ��������� ������ ����������.
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
			std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
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
			std::cout << "����������� ���� '" << adding_key << "' ��� ������������ � ��������� ������. ������� ������� ����� �������� �� '" << tree_root->count << "'." << std::endl;
		}
	}
	return tree_root;
}
//����������� ����� ���������� ������ � �������-������������ �������.
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
//����������� ����� ���� ������ ���������� ������ � ������� ����������� �� ������ � ���� ������.
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
//�������� ������� �� ���������� ������.
void removeNodeFromTree(Node*& tree_root, const int& removing_key)
{
	Node* removing_node = searchTreeNode(tree_root, removing_key);//���� ��������� ���� � ��������� ������.
	if (!removing_node)//���� ��������� ���� �����������.
		std::cout << "��������� ���� ����������� � ��������� ������. �������� �������� ����� ����������." << std::endl;
	else//���� ��������� ���� ������������.
	{
		if (removing_node->left == nullptr)//���� ���������� ������ ������ �������.
			changePointersOnDeletion(tree_root, removing_node, removing_node->right);
		else if (removing_node->right == nullptr)//���� ���������� ������ ����� �������.
			changePointersOnDeletion(tree_root, removing_node, removing_node->left);
		else//���� ���������� ��� �������.
		{
			//�������� ��������� ���� �� ����� ����� ���� � ������ ���������.
			Node* nodeToReplaceRemovingNode = removing_node->right;//��������� � ������ ���������.
			while (nodeToReplaceRemovingNode->left != nullptr)//���� ����� ����� ����.
				nodeToReplaceRemovingNode = nodeToReplaceRemovingNode->left;
			if (nodeToReplaceRemovingNode->parent != removing_node)//���� ������ ��������� ������� �� �� ������ ����.
			{
				changePointersOnDeletion(tree_root, nodeToReplaceRemovingNode, nodeToReplaceRemovingNode->right);
				nodeToReplaceRemovingNode->right = removing_node->right;
				nodeToReplaceRemovingNode->right->parent = nodeToReplaceRemovingNode;
			}
			changePointersOnDeletion(tree_root, removing_node, nodeToReplaceRemovingNode);
			nodeToReplaceRemovingNode->left = removing_node->left;
			nodeToReplaceRemovingNode->left->parent = nodeToReplaceRemovingNode;
		}
		//������� ��������� ����.
		std::cout << "������� �� ��������� ����� '" << removing_node->key << "' � ��������� '" << removing_node->count << "' ���� ������� ������� �� ���������� ������." << std::endl;
		removing_node->parent = nullptr;
		removing_node->left = nullptr;
		removing_node->right = nullptr;
		removing_node->key = 0;
		removing_node->count = 0;
		delete removing_node;
	}
}
//��������� ���������� ��� ������.
void DestroyAllTree(Node*& tree_root)
{
	if (tree_root != nullptr)
	{
		DestroyAllTree(tree_root->left);
		DestroyAllTree(tree_root->right);
		std::cout << "������� " << tree_root->key << " ���� ������� �������." << std::endl;
		delete tree_root;
	}
}

/*���������������� �������*/
void userCase1(Tree*& binary_tree)
{
	std::cout << "������� ���������� ������ ���������� ������ (����� ������������� �����) ��� 'q', ����� ����� � ����: " << std::endl;
	while (true)
	{
		std::string count_nodes_or_exit{};
		std::getline(std::cin, count_nodes_or_exit);
		if (count_nodes_or_exit != "q" && checkStrIsNumeric(count_nodes_or_exit) && convertStrToInt(count_nodes_or_exit) > 0)
		{
			int count_nodes{ convertStrToInt(count_nodes_or_exit) };
			std::cout << "�������� ����� ���������� ������ ��� ������� 'q', ����� ����� � ����:\n0 - �� ����������;\n1 - ����������." << std::endl;
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
			std::cout << "������ �����. ��������� ���� ��� ������� � ����: ";
	}
}
void userCase2(Tree*& binary_tree)
{
	std::cout << "������� ������� (����), ������� ���������� �������� � ��������� ������, ��� 'q', ����� ����� � ����." << std::endl;
	while (true)
	{
		std::string new_key_or_exit{ getElem() };
		if (new_key_or_exit != "q")
		{
			int new_key{ convertStrToInt(new_key_or_exit) };
			std::cout << "�������� ����� ���������� ������� ��� ������� 'q', ����� ����� � ����:\n0 - �� ����������;\n1 - ����������." << std::endl;
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
	std::cout << "����� ���������� ������ � �������-������������ �������:" << std::endl;
	printTreeInBackwardSymmetricOrder(tree_root, 0);
}
void userCase4(Node*& tree_root)
{
	std::cout << "����� ���������� ������ � ���� ������ � ��������� ������ � ��������������� ���������:" << std::endl;
	printTreeInSymmetricalOrderWithCount(tree_root);
	std::cout << std::endl;
}
void userCase5(Node*& tree_root)
{
	std::cout << "������� ����, ������� ����� ����� � ��������� ������, ��� 'q', ����� ����� � ����." << std::endl;
	while (true)
	{
		std::string searching_key_or_exit{ getElem() };
		if (searching_key_or_exit != "q")
		{
			int searching_key{ convertStrToInt(searching_key_or_exit) };
			Node* searching_node = searchTreeNode(tree_root, searching_key);
			if (searching_node)
			{
				std::cout << "��������� ���� '" << searching_node->key << "' ��� ������� ������ � ��������� ������." << std::endl;
				std::cout << "������� ����� ����� '" << searching_node->count << "'." << std::endl;
				break;
			}
			else
				std::cout << "��������� ���� ����������� � ��������� ������. ��������� ���� ��� ������� � ����." << std::endl;
		}
		else
			break;
	}
}
void userCase6(Tree*& binary_tree)
{
	printTreeInBackwardSymmetricOrder(binary_tree->root, 0);
	std::cout << "������� ������� (����), ������� ���������� ������� �� ���������� ������, ��� 'q', ����� ����� � ����." << std::endl;
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
	std::cout << "��������� ������ ���� ������� �������. ������ ������� ������." << std::endl;
}
void userCase8(Tree*& binary_tree)
{
	DestroyAllTree(binary_tree->root);
	delete binary_tree;
	std::cout << "��� ���������� ������ ���� ���������� � ����. ���������� ��������� . . ." << std::endl;
}