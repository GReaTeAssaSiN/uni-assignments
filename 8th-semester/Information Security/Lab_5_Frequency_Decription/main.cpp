#include <iostream>
#include "mystruct.h"
#include "myfuncs.h"

int main() {
	setlocale(LC_ALL, "Rus");
	WelcomeUser();
	bool cycle{ true };
	while (cycle) {
		switch (GetCase()) {
		case '1'://��������� ������ ��������.
			DrawLine('=');
			std::cout << std::endl;
			AnalyzeFrequencyProcess();
			break;
		case '2'://���������� �����.
			DrawLine('=');
			std::cout << std::endl;
			DecryptFileProcess();
			break;
		case '0'://�����.
			cycle = false;
			break;
		default:;
		}
		DrawLine('=');
		std::cout << std::endl;
	}
	return 0;
}