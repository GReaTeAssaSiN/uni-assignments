#include <iostream>
#include <string>
#include "myfuncs.h"

/*���������������� ����*/
//���������������� ����.
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) ���������� �������� ����������������� ��������� ������ (���) � �������� ������ ������." << std::endl <<
		"2) ���������� ����� ������ �� ������ ��������� ������ � ������ �������." << std::endl <<
		"3) ���������� ����� ������ �� ������ ��������� ������ � ������������ �������." << std::endl <<
		"4) ���������� ����� ������ �� ������ ��������� ������ � �������-������������ �������." << std::endl <<
		"5) ����� ������ ���������� ������ � �������� ������." << std::endl <<
		"6) �����." << std::endl;
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
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6")
			return choice[0];
		else
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 6). ��������� ����:" << std::endl;
	}
}

/*��������������� �������*/
//����
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
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
//������ � ������������ ������� ����� ������ ����� ������ � �������� ������.
void getNewNumberVertices(Tree*& binary_tree)
{
	while (true)
	{
		std::cout << "�� ������ ������ ����� ���������� ������?(yes/no)" << std::endl;
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
			std::cout << "������ �����. �� ������ ������ 'yes' ��� 'no'. ��������� ����." << std::endl;
	}
}


/*�������� �������*/
//������ ����� ������ ��������� ������ � ������������.
int getNumberVertices()
{
	std::cout << "������� ����� ������ �������� ����������������� ������(���): ";
	while (true)
	{
		std::string number_vertices{};
		std::getline(std::cin, number_vertices);
		if (checkStrIsNumeric(number_vertices) && convertStrToInt(number_vertices) > 0)
			return convertStrToInt(number_vertices);
		else
			std::cout << "������ �����. �� ������ ������ ����� ������������� �����. ��������� ����: ";
	}
}
//�������� ������� ��������� ������.
bool empty_tree(Node* tree_root)
{
	return tree_root == nullptr ? true : false;
}
//����������� ���������� ������� ����������������� ������ (���).
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
//������ ����� ���.
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
//������������ ����� ���.
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
//�������-������������ ����� ���.
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