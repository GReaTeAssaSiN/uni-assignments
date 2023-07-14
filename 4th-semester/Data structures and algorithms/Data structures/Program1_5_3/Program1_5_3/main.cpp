#include <iostream>
#include <string>
#include "myfuncs.h"

int main()
{
	std::setlocale(LC_ALL, "Rus");
	//������� ����� ������.
	Tree* binary_tree = new Tree{};
	binary_tree->number_vertices = 0;
	binary_tree->root = nullptr;
	//���� ��������� ����������������� �����.
	bool create{};
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			createNewNode(binary_tree);
			create = true;
			break;
		case '2':
			if (create)
				order_1(binary_tree->root);
			else 
				std::cout << "������� ���������� ������� ������������ �������� ������." << std::endl;
			break;
		case '3':
			if (create)
				order_2(binary_tree->root);
			else 
				std::cout << "������� ���������� ������� ������������ �������� ������." << std::endl;
			break;
		case '4':
			if (create)
				order_3(binary_tree->root);
			else 
				std::cout << "������� ���������� ������� ������������ �������� ������." << std::endl;
			break;
		case '5':
			if (create)
				userSearchNodePBT(binary_tree->root);
			else 
				std::cout << "������� ���������� ������� ������������ �������� ������." << std::endl;
			break;
		case '6':
			if (!create)
				std::cout << "������ ��� �� ���� �������, ����� ���� ����������� ��� ����������." << std::endl;
			else
			{
				DestroyAllTree(binary_tree->root);
				binary_tree->number_vertices = 0;
				binary_tree->root = nullptr;
				std::cout << "������ ���� �������. ������ ������� ������." << std::endl;
				create = false;
			}
			break;
		case '7':
			if (create)
				clearBinaryTree(binary_tree);
			else 
				delete binary_tree;
			cycle = false;
			std::cout << "��� ���������� ������������ ������ ���������� � ����. ���������� ��������� . . ." << std::endl;
			break;
		}
		printDashes();
	}
	return 0;
}
