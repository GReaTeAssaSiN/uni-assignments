#include <iostream>
#include <string>
#include "myfuncs.h"

/*���������������� ����*/
//���������������� ����.
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) �������� ������� � ������������ �������� ������." << std::endl <<
		"2) ���������� ����� ������������� ��������� ������ �� ������ ��������� ������ � ������ �������." << std::endl <<
		"3) ���������� ����� ������������� ��������� ������ �� ������ ��������� ������ � ������������ �������." << std::endl <<
		"4) ���������� ����� ������������� ��������� ������ �� ������ ��������� ������ � �������-������������ �������." << std::endl <<
		"5) ����� ������� ������������� ��������� ������ � �������� �������������� ������." << std::endl <<
		"6) ��������� ���������� ������������ �������� ������." << std::endl <<
		"7) �����." << std::endl;
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
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
			return choice[0];
		else
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 7). ��������� ����:" << std::endl;
	}
}

/*��������������� �������*/
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
	std::cout << "������� �������������� ����� �������� (����� �����) ��� 'q', ����� ����� � ����: ";
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
//������ � ������������ ������ ������ ��� ������� ������� ������������ �������.
std::string getChoiceLeftRight()
{
	std::cout << "�� ������ �������� ������ (l) ��� ������� (r) ������� ������� �������? ";
	while (true)
	{
		std::string left_right{};
		std::getline(std::cin, left_right);
		if (left_right == "l" || left_right == "r")
			return left_right;
		else
			std::cout << "������ �����. �� ������ ������ 'l' ��� 'r'. ��������� ����: ";
	}
}

/*�������� �������*/
//���������� ����� ������� � ������������ �������� ������.
void createNewNode(Tree*& binary_tree)
{
	if (binary_tree->root != nullptr)
	{
		Node* parentNode{ nullptr };
		bool flag = false;
		order_1(binary_tree->root);
		std::cout << "������� �������������� ����� ������� ������������� ��������� ������, ����� ������� ������ �������� �������, ��� ������� � ����." << std::endl;
		while (true)
		{
			std::string parent_data_or_exit{ getElem() };
			if (parent_data_or_exit != "q")
			{
				searchPBT(binary_tree->root, convertStrToInt(parent_data_or_exit), flag, parentNode);
				if (parentNode != nullptr)
				{
					std::cout << "������� ������� ������ � �������������� ������ '" << parentNode->data << "' ���� ������� ������� �� ������ '" <<
						parentNode->level << "'." << std::endl;
					if (parentNode->left != nullptr && parentNode->right != nullptr)
						std::cout << "��������� ������� ��� ����� ���� ��������. ���������� ����� ����������." << std::endl;
					else
					{
						Node* new_node = new Node{};
						std::cout << "������� �������������� ����� ������� ������ - �������, ��� ������� � ����." << std::endl;
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
								std::cout << "����� ������� � �������������� ������ '" << new_node->data << "' ���� ������� ��������� � ������." << std::endl;
								break;
							}
							else
								break;
						}
					}
					break;
				}
				else
					std::cout << "� ������� ������ ��� ������� �������. ��������� ���� ��� ������� � ����." << std::endl;
			}
			else
				break;
		}
	}
	else
	{
		std::cout << "������������ �������� ������ ������ �� ������ ������, �������� �������� ������� ��� ������� 'q', ����� ����� � ����." << std::endl;
		while (true)
		{
			std::string new_root_or_exit{ getElem() };
			if (new_root_or_exit != "q")
			{
				binary_tree->root = new Node{};
				binary_tree->root->level = 0;
				binary_tree->root->data = convertStrToInt(new_root_or_exit);
				binary_tree->number_vertices++;
				std::cout << "������ ������ � �������������� ������ '" << binary_tree->root->data << "' ��� ������� ������." << std::endl;
			}
			break;
		}
	}
}
//������ ����� ���.
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
//������������ ����� ���.
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
//�������-������������ ����� ���.
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
//��������� ������� ������������ � ������ ������� � ���.
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
				std::cout << "������� ������� ������������� ��������� ������ � �������������� ������ '" << parentNode->data << "' ���� ������� ������� �� ������ '" 
					<< parentNode->level << "'." << std::endl;
				break;
			}
			else
				std::cout << "� ������ ������������ �������� ������ ��� ������ � �������� �������������� ������. ��������� ���� ��� ������� � ����." << std::endl;
		}
		else
			break;
	}
}
//����� ������� ��� � �������� �������������� ������.
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
//������� ���������� ������������ ������ ��� �������� ������.
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
//��������� ���������� ��� ������.
void DestroyAllTree(Node*& tree_root)
{
	if (tree_root != nullptr)
	{
		DestroyAllTree(tree_root->left);
		DestroyAllTree(tree_root->right);
		std::cout << "������� " << tree_root->data << " ���� ������� �������." << std::endl;
		delete tree_root;
	}
}