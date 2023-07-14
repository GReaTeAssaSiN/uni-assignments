#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//Цикл обработки действий пользователя.
	bool cycle{ true };
	getAboutInformation();//Вывод информации об авторе и варианте.
	while (cycle)
	{
		programExecution();//Основная функция, запускающая выполнение программы.
		printDashes();//Разделительная черта.
		if (!exitOrContinue())
			break;
	}
	return 0;
}