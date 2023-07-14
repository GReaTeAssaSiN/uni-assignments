#include <iostream>
#include <cstdlib> //��� ������� rand() � srand()
#include <ctime> //��� ������� time()
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//�������� ���� � ������������ ������� (��������� ������������������ ��������� ����� �� ���������).
	srand(static_cast<unsigned int>(time(0)));
	//������� ����� ������.
	Tree* binary_tree = new Tree{};
	binary_tree->number_vertices = getNumberVertices();
	//���� ��������� ����������������� �����.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			recursivelyBuildingPBT(binary_tree->root, binary_tree->number_vertices);
			std::cout << "�������� ���������������� �������� ������ ���������." << std::endl;
			break;
		case '2':
			if (empty_tree(binary_tree->root))
				std::cout << "�������� �� ����� ���� ���������, ������� ���������� ��������� ���." << std::endl;
			else
				order_1(binary_tree->root, 0);
			break;
		case '3':
			if (empty_tree(binary_tree->root))
				std::cout << "�������� �� ����� ���� ���������, ������� ���������� ��������� ���." << std::endl;
			else
				order_2(binary_tree->root, 0);
			break;
		case '4':
			if (empty_tree(binary_tree->root))
				std::cout << "�������� �� ����� ���� ���������, ������� ���������� ��������� ���." << std::endl;
			else
				order_3(binary_tree->root, 0);
			break;
		case '5':
			getNewNumberVertices(binary_tree);
			break;
		case '6':
			clearBinaryTree(binary_tree);
			cycle = false;
			std::cout << "��� ���������� ������������ ������ ���� ���������� � ����. ���������� ��������� . . ." << std::endl;
			break;
		}
		printDashes();
	}
	return 0;
}