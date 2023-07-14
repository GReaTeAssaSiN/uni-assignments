#include <iostream>
#include <cstdlib> //для функций rand() и srand()
#include <windows.h>//для функции Sleep()
#include <ctime> //для функции time()
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	Queue* myQueue = new Queue{};
	srand(static_cast<unsigned int>(time(0)));//Привзяка ГПСЧ к календарному времени (случайные последовательности случайных чисел из диапазона).
	std::cout << "Датчик псевдослучайных чисел был инициализрован." << std::endl;
	printDashes();
	int add_remove_elems{}, number_added_removed_elems{}; char symbol{};//Переменные для выбора и реализации действия каждую указанную единицу времени.
	bool cycle{ true }; int numberActions{};//Переменные для работы с пользователем.
	while (cycle)
	{
		numberActions++;
		add_remove_elems = static_cast<int>(getRandomNumber(1, 100));
		number_added_removed_elems = static_cast<int>(getRandomNumber(1, 3));
		if (add_remove_elems % 2 == 0)
		{
			std::cout << numberActions << ": В очередь будет добавлен(-о) " << number_added_removed_elems << " элемент(-а,-ов)." << std::endl;
			for (int i{ number_added_removed_elems }; i > 0; i--)
			{
				symbol = static_cast<char>(getRandomNumber(65, 90));
				enQueue(myQueue, symbol);
			}
		}
		else
		{
			std::cout << numberActions << ": Из очереди будет удален(-о) " << number_added_removed_elems << " элемент(-а,-ов)." << std::endl;
			for (int i{ number_added_removed_elems }; i > 0; i--)
			{
				if (isEmptyQueue(myQueue))
				{
					std::cout << "Операция удаления " << i << " (оставшегося(-ихся)) элемента(-ов) из очереди невозможна." << std::endl;
					break;
				}
				else
					deQueue(myQueue);
			}
		}
		printQueue(myQueue);
		if (isSymbolQ())//Выход из программы при вводе пользователем символа 'q'.
			break;
		printDashes();
		//Sleep(5000);//Sleep() считает время в тясячных долях секунды.
	}
	printDashes();
	clearQueue(myQueue);
	return 0;
}