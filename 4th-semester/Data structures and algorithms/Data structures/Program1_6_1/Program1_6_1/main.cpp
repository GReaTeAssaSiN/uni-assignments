#include <iostream>
#include <cstdlib> //��� ������� rand() � srand()
#include <ctime> //��� ������� time()
#include "myfuncs.h"

int main()
{
	std::setlocale(LC_ALL, "Rus");
	//�������� ���� � ������������ ������� (��������� ������������������ ��������� ����� �� ���������).
	srand(static_cast<unsigned int>(time(0)));
	//������� ����� ���������� ������.
	Tree* binary_tree = new Tree{};
	binary_tree->root = nullptr;
	binary_tree->number_vertices = 0;
	//���� ��������� ����������������� �����.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case '1':
			if (isBinaryTreeEmpty(binary_tree->root))
				userCase1(binary_tree);
			else
				std::cout << "��������� ������ ��� ���� ���������. ������� ������ ������, ��� ������� ����� ������ ��������." << std::endl;
			break;
		case '2':
			userCase2(binary_tree);
			break;
		case '3':
			std::cout << "���������� ��������� ���������� ������: " << binary_tree->number_vertices << std::endl;
			if (!isBinaryTreeEmpty(binary_tree->root))
				userCase3(binary_tree->root);
			else
				std::cout << "������� ���������� ������� �������� ��������� ������." << std::endl;
			break;
		case '4':
			std::cout << "���������� ��������� ���������� ������: " << binary_tree->number_vertices << std::endl;
			if (!isBinaryTreeEmpty(binary_tree->root))
				userCase4(binary_tree->root);
			else
				std::cout << "������� ���������� ������� �������� ��������� ������." << std::endl;
			break;
		case '5':
			if (!isBinaryTreeEmpty(binary_tree->root))
				userCase5(binary_tree->root);
			else
				std::cout << "������� ���������� ������� �������� ��������� ������." << std::endl;
			break;
		case '6':
			if (!isBinaryTreeEmpty(binary_tree->root))
				userCase6(binary_tree);
			else
				std::cout << "������� ���������� ������� �������� ��������� ������." << std::endl;
			break;
		case '7':
			if (!isBinaryTreeEmpty(binary_tree->root))
				userCase7(binary_tree);
			else
				std::cout << "������� ���������� ������� �������� ��������� ������." << std::endl;
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
