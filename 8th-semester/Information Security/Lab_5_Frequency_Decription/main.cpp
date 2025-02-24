#include <iostream>
#include "mystruct.h"
#include "myfuncs.h"

int main() {
	setlocale(LC_ALL, "Rus");
	WelcomeUser();
	bool cycle{ true };
	while (cycle) {
		switch (GetCase()) {
		case '1'://Частотный анализ символов.
			DrawLine('=');
			std::cout << std::endl;
			AnalyzeFrequencyProcess();
			break;
		case '2'://Дешифровка файла.
			DrawLine('=');
			std::cout << std::endl;
			DecryptFileProcess();
			break;
		case '0'://Выход.
			cycle = false;
			break;
		default:;
		}
		DrawLine('=');
		std::cout << std::endl;
	}
	return 0;
}