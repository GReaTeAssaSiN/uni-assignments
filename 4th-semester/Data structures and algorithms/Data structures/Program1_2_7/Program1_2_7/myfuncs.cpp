#include <iostream>
#include <string>
#include "myfuncs.h"

/*ВТОРОСТЕПЕННЫЕ ФУНКЦИИ*/
//ГПСЧ
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}
//Проверка введенной пользователем строки на соответствие символу 'q'
bool isSymbolQ()
{
	std::cout << "Введите символ 'q', если желаете выйти из программы, иначе можете просто нажать Enter: ";
	std::string symbol{};
	std::getline(std::cin, symbol);
	if (symbol == "q")
		return true;
	return false;
}
//Вывод визуального разделения между действиями пользователя в консоль.
void printDashes()
{
	std::cout << "---------------------------------------------------------------------------------------------------------------" << "\t" << std::endl;
}

/*ФУНКЦИИ ДЛЯ РАБОТЫ С ОЧЕРЕДЬЮ*/
//Проверка очереди на пустоту
bool isEmptyQueue(Queue* f_queue)
{
	return (f_queue->frnt == nullptr) ? true : false;
}
//Добавление элемента в очередь
void enQueue(Queue*& f_queue, char f_symbol)
{
	try
	{
		Node* new_elem = new Node{};
		if (f_queue->frnt == nullptr)
		{
			f_queue->frnt = new_elem;
			f_queue->rear = f_queue->frnt;
		}
		else
		{
			f_queue->rear->next = new_elem;
			f_queue->rear = new_elem;
		}
		std::cout << "В очередь был добавлен элемент '" << f_symbol << "'." << std::endl;
		f_queue->rear->data = f_symbol;
		f_queue->rear->next = f_queue->frnt;
		f_queue->count++;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Не удалось выделить память из кучи. Куча переполнена!" << std::endl;
		clearQueue(f_queue);
		exit(-1);
	}
}
//Удаление элемента из очереди
void deQueue(Queue*& f_queue)
{
	if (isEmptyQueue(f_queue))
		std::cout << "Очередь пуста, операция удаления элемента из очереди невозможна." << std::endl;
	else
	{
		Node* temp = f_queue->frnt;
		if (f_queue->frnt == f_queue->rear)
		{
			f_queue->frnt = nullptr;
			f_queue->rear = nullptr;
		}
		else
		{
			f_queue->frnt = f_queue->frnt->next;
			f_queue->rear->next = f_queue->frnt;
		}
		temp->next = nullptr;
		std::cout << "Элемент '" << temp->data << "' из очереди успешно удален." << std::endl;
		delete temp;
		f_queue->count--;
	}
}
//Вывод текущего состояния очереди на экран
void printQueue(Queue* f_queue)
{
	if (isEmptyQueue(f_queue))
		std::cout << "Очередь пуста.";
	else
	{
		Node* temp = f_queue->frnt;
		std::cout << "Текущее состояние очереди: ";
		for (int i{ f_queue->count }; i > 0; i--)
		{
			std::cout << temp->data;
			temp = temp->next;
		}
		temp = nullptr;
	}
	std::cout << std::endl << std::endl;
}
//Очистка выделенной памяти для очереди
void clearQueue(Queue*& f_queue)
{
	for (int i{ f_queue->count }; i > 0; i--)
	{
		Node* temp = f_queue->frnt->next;
		f_queue->frnt->next = nullptr;
		delete f_queue->frnt;
		f_queue->frnt = temp;
		f_queue->rear->next = f_queue->frnt;
		f_queue->count--;
		temp = nullptr;
	}
	delete f_queue;
	std::cout << "Вся выделенная память была возвращена в кучу. Завершение программы . . ." << std::endl;
}