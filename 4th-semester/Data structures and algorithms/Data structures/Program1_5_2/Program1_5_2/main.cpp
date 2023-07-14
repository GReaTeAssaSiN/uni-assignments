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
	recursivelyBuildingPBT(binary_tree->root, binary_tree->number_vertices);
	std::cout << "�������� ���������������� �������� ������ ���� ���������." << std::endl << std::endl;
	//������������� ���������������� �����.
	Stack* auxiliary_stack = new Stack{};
	auxiliary_stack->stackPtr = nullptr;
	//���� ��������� ����������������� �����.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			order_1(binary_tree->root, 0);
			break;
		case '2':
			order_2(binary_tree->root, 0);
			break;
		case '3':
			order_3(binary_tree->root, 0);
			break;
		case '4':
			NoRecursiveOrder2(binary_tree, auxiliary_stack);
			break;
		case '5':
			getNewNumberVertices(binary_tree, auxiliary_stack);
			break;
		case '6':
			clearBinaryTreeAndStack(binary_tree, auxiliary_stack);
			cycle = false;
			std::cout << "��� ���������� ������������ ������ ���� ���������� � ����. ���������� ��������� . . ." << std::endl;
			break;
		}
		printDashes();
	}
	return 0;
}