#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Lab_5", sf::Style::Close);
	window.setPosition(sf::Vector2i(X_BASE_POINT, Y_BASE_POINT));

	//Массив полиморфных указателей
	int size_figures_array{};
	TFigure** figures_array = new TFigure * [size_figures_array];

	menu_processing(window, figures_array, size_figures_array);

	//Зачистка массива полиморфных указателей (необязательно...)
	for (int i{}; i < size_figures_array; i++)
	{
		delete figures_array[i];
		figures_array[i] = nullptr;
	}
	delete[] figures_array;

	return 0;
}