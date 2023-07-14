#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Lab_6", sf::Style::Close);
	window.setPosition(sf::Vector2i(X_BASE_POINT, Y_BASE_POINT));

	//Размер динамического массива (контейнер)
	int size_container_figures_dynamic_array{};
	//Размер линейного динамического списка (контейнер)
	int size_container_figures_lynear_dynamic_list{};
	//Указатель на объект класса-контейнера на базе динамического массива
	DynamicArray* ptr_container_figures_dynamic_array{};
	//Указатель на объект класса-контейнера на базе линейного динамического списка
	LynearDynamicList* ptr_container_figures_lynear_dynamic_list{};
	//Указатель на любой графический примитив (объект класса TFigure)
	TFigure* ptr_graphic_primitive{};

	menu_processing(window, ptr_container_figures_dynamic_array, ptr_container_figures_lynear_dynamic_list, 
		ptr_graphic_primitive, size_container_figures_dynamic_array, size_container_figures_lynear_dynamic_list);

	if (ptr_container_figures_dynamic_array != nullptr)
	{
		delete ptr_container_figures_dynamic_array;
		ptr_container_figures_dynamic_array = nullptr;
		size_container_figures_dynamic_array = 0;
	}
	if (ptr_container_figures_lynear_dynamic_list != nullptr)
	{
		delete ptr_container_figures_lynear_dynamic_list;
		ptr_container_figures_lynear_dynamic_list = nullptr;
		size_container_figures_lynear_dynamic_list = 0;
	}

	return 0;
}