#include <iostream>
#include "myfuncs.h"

int main() 
{
	setlocale(LC_ALL, "Rus");
	std::system("chcp 1251 > nul"); //���������� ����������� ������� �������� std::cin.
	WelcomeUser();
	bool cycle{ true };
	while (cycle) {
		switch (GetCase()) {
		case '1'://������� �������������� ������.
			DrawLine();
			std::cout << std::endl;
			SimpleSubstitutionProcess();
			break;
		case '2'://������� ���������� ��������.
			DrawLine();
			std::cout << std::endl;
			ViginerProcess();
			break;
		case '0'://�����.
			cycle = false;
			break;
		default:;
		}
		DrawLine();
		std::cout << std::endl;
	}
	std::system("chcp 866 > nul"); //�������.
	return 0;
}