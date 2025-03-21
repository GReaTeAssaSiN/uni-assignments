#include <cstdlib> //для функций rand() и srand()
#include <ctime> //для функции time()
#include "myfuncs.h"
#include "FiguresFuncs.h"
#include "user_buttons.h"

//ГПСЧ
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}

//Оновная работа программы
int menu_processing(sf::RenderWindow& window, TFigure**& figures_array, int& size_figures_array)
{
	/*СОЗДАНИЕ ФОНА ОКНА*/
	//Меню
	Rect_BG_buttons BG_general(0, 0, 700, 895, 5);
	BG_general.m_setFillColor(5, 90, 1);
	//IMAGE
	User_texts image_text("Comic_Sans_MS.TTF", " I  M  A  G  E ", 870, 0, 70);
	//Панель меню
	Rect_BG_buttons BG_menu(5, 5, 695, 85, 5);
	User_texts menu_text("Comic_Sans_MS.TTF", " M   E   N   U ", 120, 0, 70);
	//Кнопка EXIT
	Rect_BG_buttons BG_exit(5, 840, 160, 50, 5);
	User_texts exit_text("Comic_Sans_MS.TTF", "E X I T", 25, 850, 30);

	/*КНОПКИ ОБРАБОТКИ СОБЫТИЙ*/
	//Массив
	Rect_BG_buttons BG_ArrayFigures(5, 96, 200, 60, 5);
	User_texts ArrayFigures_text("Comic_Sans_MS.TTF", "A R R A Y", 28, 110, 30);
	//Создать массив
	Rect_BG_buttons BG_CreateFigures(15, 171, 180, 40, 5);
	User_texts CreateFigures_text("Comic_Sans_MS.TTF", "CREATE", 45, 175, 27);
	//Уничтожить массв
	Rect_BG_buttons BG_DestroyFigures(15, 226, 180, 40, 5);
	User_texts DestroyFigures_text("Comic_Sans_MS.TTF", "DESTROY", 35, 230, 27);
	//Стереть массв
	Rect_BG_buttons BG_EraseFigures(15, 281, 180, 40, 5);
	User_texts EraseFigures_text("Comic_Sans_MS.TTF", "ERASE", 35, 285, 27);
	//Показать массв
	Rect_BG_buttons BG_ShowFigures(15, 336, 180, 40, 5);
	User_texts ShowFigures_text("Comic_Sans_MS.TTF", "SHOW", 35, 340, 27);
	//Переместить массв
	Rect_BG_buttons BG_MoveFigures(15, 391, 180, 40, 5);
	User_texts MoveFigures_text("Comic_Sans_MS.TTF", "MOVE", 35, 395, 27);
	//Подиерархия кругов
	Rect_BG_buttons BG_MoveUnderCircleHierarchy(15, 446, 535, 40, 5);
	User_texts MoveUnderCircleHierarchy_text("Comic_Sans_MS.TTF", "MOVE UNDER CIRCLE HEIRARCHY", 35, 450, 27);
	User_texts ChangeDimensionsUnderCircleHierarchy_text("Comic_Sans_MS.TTF",
		"\t\tUNDER CIRCLE HIERARCHY\n(q) - increase radius (circle)\n(e) - decrease radius (circle)\n(z) - increase semi major axis (ellipse)"
		"\n(x) - decrease semi major axis(ellipse)\n(c) - increase semi minor axis(ellipse)\n(v) - decrease semi minor axis(ellipse)\n(f) - rotate(ellipse)", 
		20, 560, 16);
	//Подиерархия четырехугольников
	Rect_BG_buttons BG_MoveUnderQuadrilateralHierarchy(15, 501, 600, 40, 5);
	User_texts MoveUnderQuadrilateralHierarchy_text("Comic_Sans_MS.TTF", "MOVE UNDER QUADRILATERAL HEIRARCHY", 35, 505, 24);
	User_texts ChangeDimensionsUnderQuadrilateralHierarchy_text("Comic_Sans_MS.TTF",
		"UNDER QUADRILATERAL HIERARCHY\n(r) - increase length (rectangle)\n(t) - decrease length (rectangle)\n(g) - increase width (rectangle)\n(h) - decrease width (rectangle)\n(b) - rotate(rectangle)"
		"\n(y) - increase dimensions (quadrilateral)\n(u) - decrease dimensions (quadrilateral)\n(i) - increase length (rhomb)\n(o) - decrease length (rhomb)\n(j) - increase degree (rhomb)\n(k) - decrease degree (rhomb)"
		"\n(n) - increase TopBase (trapeze)\n(m) - decrease TopBase (trapeze)\n(UP) - increase height (trapeze)\n(DOWN) - decrease height (trapeze)\n(RIGHT) - increase BottomBase (trapeze)\n(LEFT) - decrease BottomBase (trapeze)",
		230, 110, 13);

	//Подиерархия четырехугольников

	//Привзяка ГПСЧ к календарному времени (случайные последовательности случайных чисел из диапазона)
	srand(static_cast<unsigned int>(time(0)));

	//Внешние переменные функции
	bool submenu_array{ false };//ARRAY->открывается подменю
	//Подменю
	bool create_array{ false }, destroy_array{false}, show_array{true}, move_array{ false };//bool erase_array{false}; было бы странно создавать...
	//Обработка подиерархий
	bool move_under_circle_hierarchy{ false }, move_under_quadrilateral_hierarchy{ false };

	while (window.isOpen())
	{
		/*ПОКАДРОВАЯ ОБРАБОТКА ЦВЕТОВ СОЗДАННЫХ ОБЪЕКТОВ НА ОКНЕ*/
		//Фон меню и кнопки меню
		image_text.m_setFillColor(111, 206, 253);
		BG_exit.m_setDefaultColor();
		exit_text.m_setDefaultColor();
		//Кнопки обработки фигур
		BG_ArrayFigures.m_setFillColor(26, 255, 255);
		ArrayFigures_text.m_setFillColor(24, 48, 229);
		BG_CreateFigures.m_setFillColor(195, 195, 195);
		CreateFigures_text.m_setDefaultColor();
		BG_DestroyFigures.m_setFillColor(195, 195, 195);
		DestroyFigures_text.m_setDefaultColor();
		BG_EraseFigures.m_setFillColor(195, 195, 195);
		EraseFigures_text.m_setDefaultColor();
		BG_ShowFigures.m_setFillColor(195, 195, 195);
		ShowFigures_text.m_setDefaultColor();
		ChangeDimensionsUnderCircleHierarchy_text.m_setFillColor(209, 255, 26);
		ChangeDimensionsUnderQuadrilateralHierarchy_text.m_setFillColor(209, 255, 26);

		/*БУЛЕВЫЕ ПЕРЕМЕННЫЕ ДЛЯ ПОЛОЖЕНИЯ КУРСОРА НА КНОПКЕ*/
		//Кнопки меню
		bool stage_exit{ false };
		//Кнопки обработки фигур
		bool stage_array{ false }, stage_create_array{ false }, stage_destroy_array{ false }, stage_erase_array{false}, stage_show_array{false}, stage_move_array{false};
		//Кнопки обработки подиерархий
		bool stage_move_under_circle_hierarchy{ false }, stage_move_under_quadrilateral_hierarchy{false};

		/*ОКРАШИВАНИЕ АКТИВНЫХ КНОПОК*/
		if (!submenu_array)
		{
			BG_ArrayFigures.m_setDefaultColor();
			ArrayFigures_text.m_setDefaultColor();
		}
		if (!move_array)
		{
			BG_MoveFigures.m_setFillColor(195, 195, 195);
			MoveFigures_text.m_setDefaultColor();
		}
		if (!move_under_circle_hierarchy)
		{
			BG_MoveUnderCircleHierarchy.m_setFillColor(195, 195, 195);
			MoveUnderCircleHierarchy_text.m_setDefaultColor();
		}
		if (!move_under_quadrilateral_hierarchy)
		{
			BG_MoveUnderQuadrilateralHierarchy.m_setFillColor(195, 195, 195);
			MoveUnderQuadrilateralHierarchy_text.m_setDefaultColor();
		}

		/*ОКРАШИВАНИЕ КНОПОК ПРИ НАВЕДЕНИИ КУРСОРА МЫШИ (с изменением значения соответствующих переменных*/
		//EXIT
		if (sf::IntRect(5, 840, 160, 50).contains(sf::Mouse::getPosition(window)))
		{
			BG_exit.m_setActiveColor();
			exit_text.m_setActiveColor();
			stage_exit = true;
		}
		//Меню Array
		if (sf::IntRect(5, 96, 200, 60).contains(sf::Mouse::getPosition(window)))
		{
			BG_ArrayFigures.m_setActiveColor();
			ArrayFigures_text.m_setActiveColor();
			stage_array = true;
		}
		//Подменю Array
		if (sf::IntRect(15, 171, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_array)
		{
			BG_CreateFigures.m_setActiveColor();
			CreateFigures_text.m_setActiveColor();
			stage_create_array = true;
		}
		if (sf::IntRect(15, 226, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_array)
		{
			BG_DestroyFigures.m_setActiveColor();
			DestroyFigures_text.m_setActiveColor();
			stage_destroy_array = true;
		}
		if (sf::IntRect(15, 281, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_array)
		{
			BG_EraseFigures.m_setActiveColor();
			EraseFigures_text.m_setActiveColor();
			stage_erase_array = true;
		}
		if (sf::IntRect(15, 336, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_array)
		{
			BG_ShowFigures.m_setActiveColor();
			ShowFigures_text.m_setActiveColor();
			stage_show_array = true;
		}
		if (sf::IntRect(15, 391, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_array)
		{
			BG_MoveFigures.m_setActiveColor();
			MoveFigures_text.m_setActiveColor();
			stage_move_array = true;
		}
		if (sf::IntRect(15, 446, 535, 40).contains(sf::Mouse::getPosition(window)) && submenu_array)
		{
			BG_MoveUnderCircleHierarchy.m_setActiveColor();
			MoveUnderCircleHierarchy_text.m_setActiveColor();
			stage_move_under_circle_hierarchy = true;
		}
		if (sf::IntRect(15, 501, 600, 40).contains(sf::Mouse::getPosition(window)) && submenu_array)
		{
			BG_MoveUnderQuadrilateralHierarchy.m_setActiveColor();
			MoveUnderQuadrilateralHierarchy_text.m_setActiveColor();
			stage_move_under_quadrilateral_hierarchy = true;
		}

		sf::Event event_menu_click;
		while (window.pollEvent(event_menu_click))
		{
			//Закрытие окна на "крестик"
			if (event_menu_click.type == sf::Event::Closed)
				window.close();
			//Обработчик события формы OnCreate (нажатие на кнопку)
			if (event_menu_click.type == event_menu_click.MouseButtonReleased && event_menu_click.mouseButton.button == sf::Mouse::Left)
			{
				//EXIT
				if (stage_exit)
					window.close();
				//ARRAY
				if (stage_array)
					submenu_array = !submenu_array;
				if (stage_move_array && create_array)
				{
					move_array = !move_array;
					move_under_circle_hierarchy = false;
					move_under_quadrilateral_hierarchy = false;
				}
				if (stage_move_under_circle_hierarchy && create_array)
				{
					move_under_circle_hierarchy = !move_under_circle_hierarchy;
					move_array = false;
					move_under_quadrilateral_hierarchy = false;
				}
				if (stage_move_under_quadrilateral_hierarchy && create_array)
				{
					move_under_quadrilateral_hierarchy = !move_under_quadrilateral_hierarchy;
					move_array = false;
					move_under_circle_hierarchy = false;
				}
				if (stage_erase_array && create_array)
					show_array = false;
				if (stage_show_array && create_array)
					show_array = true;
				if (stage_create_array && !create_array)
				{
					create_array = true;
					int number_elems{ static_cast<int>(getRandomNumber(20, 30)) };
					std::cout << "Создан массив из " << number_elems << " элемент(-а, -ов)." << std::endl;
					for (int i{}; i < number_elems; i++)
					{
						int type_objs{ static_cast<int>(getRandomNumber(1, 6)) };
						switch (type_objs)
						{
						case 1:
						{
							float radius_circle{ getRandomNumber(10,100) };
							float x_circle{ getRandomNumber(720, 1485) };
							float y_circle{ getRandomNumber(110, 885) };
							TFigure* ptr_new_elem{ new TCircle(x_circle, y_circle, radius_circle) };
							ptr_new_elem->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
								static_cast<int>(getRandomNumber(0, 255)));
							ptr_new_elem->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
							ptr_new_elem->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
								static_cast<int>(getRandomNumber(0, 255)));
							push_back_shapes<TFigure>(figures_array, size_figures_array, ptr_new_elem);
							break;
						}
						case 2:
						{
							float x_ellipse{ getRandomNumber(770, 1435) };
							float y_ellipse{ getRandomNumber(130, 835) };
							float ellipse_semi_major_axis{ getRandomNumber(60, 150) };
							float ellipse_semi_minor_axis{ getRandomNumber(30, ellipse_semi_major_axis - 10) };
							TFigure* ptr_new_elem{ new TEllipse(x_ellipse, y_ellipse, ellipse_semi_major_axis, ellipse_semi_minor_axis) };
							ptr_new_elem->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
								static_cast<int>(getRandomNumber(0, 255)));
							ptr_new_elem->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
							ptr_new_elem->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
								static_cast<int>(getRandomNumber(0, 255)));
							push_back_shapes<TFigure>(figures_array, size_figures_array, ptr_new_elem);
							break;
						}
						case 3:
						{
							float corner_x1{ getRandomNumber(725, 1395) };
							float corner_x2{ getRandomNumber(corner_x1 + 50, corner_x1 + 100) };
							float corner_x3{ getRandomNumber(corner_x1 + 50, corner_x1 + 100) };
							float corner_x4{ getRandomNumber(corner_x1 - 25, corner_x3 - 50) };
							float corner_y1{ getRandomNumber(125, 770) };
							float corner_y2{ getRandomNumber(corner_y1 - 25, corner_y1 + 25) };
							float corner_y3{ getRandomNumber(corner_y2 + 50, corner_y2 + 100) };
							float corner_y4{ getRandomNumber(corner_y1 + 50, corner_y1 + 100) };
							TFigure* ptr_new_elem{ new TQuadrilateral(corner_x1, corner_y1, corner_x2, corner_y2, corner_x3, corner_y3, corner_x4, corner_y4) };
							ptr_new_elem->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
								static_cast<int>(getRandomNumber(0, 255)));
							ptr_new_elem->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
							ptr_new_elem->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
								static_cast<int>(getRandomNumber(0, 255)));
							push_back_shapes<TFigure>(figures_array, size_figures_array, ptr_new_elem);
							break;
						}
						case 4:
						{
							float length_rect{ getRandomNumber(50, 300) };
							float width_rect{ getRandomNumber(25, 150) };
							float x_rect{ getRandomNumber(710, 1445) };
							float y_rect{ getRandomNumber(100, 870) };
							TFigure* ptr_new_elem{ new TRectangle(x_rect, y_rect, length_rect, width_rect) };
							ptr_new_elem->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
								static_cast<int>(getRandomNumber(0, 255)));
							ptr_new_elem->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
							ptr_new_elem->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
								static_cast<int>(getRandomNumber(0, 255)));
							push_back_shapes<TFigure>(figures_array, size_figures_array, ptr_new_elem);
							break;
						}
						case 5:
						{
							float rhomb_length{ getRandomNumber(60, 150) };
							int rhomb_degree{ static_cast<int>(getRandomNumber(30, 60)) };
							float x_rhomb{ getRandomNumber(710, 1495 - 2 * rhomb_length * cos(rhomb_degree * PI / 180)) };
							float y_rhomb{ getRandomNumber(100 + rhomb_length * sin(rhomb_degree * PI / 180), 895 - rhomb_length * sin(rhomb_degree * PI / 180)) };
							TFigure* ptr_new_elem{ new TRhomb(x_rhomb, y_rhomb, rhomb_length, rhomb_degree) };
							ptr_new_elem->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
								static_cast<int>(getRandomNumber(0, 255)));
							ptr_new_elem->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
							ptr_new_elem->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
								static_cast<int>(getRandomNumber(0, 255)));
							push_back_shapes<TFigure>(figures_array, size_figures_array, ptr_new_elem);
							break;
						}
						case 6:
						{
							int degree{ static_cast<int>(getRandomNumber(30, 90)) };
							float height{ getRandomNumber(50, 80) };
							float bottom_base_length{ getRandomNumber(130, 300) };
							float top_base_length{ getRandomNumber(60, bottom_base_length - height / tan(degree * PI / 180)) };
							float x_trapeze{ getRandomNumber(710, 1495 - bottom_base_length) };
							float y_trapeze{ getRandomNumber(100 + height, 895) };
							TFigure* ptr_new_elem{ new TTrapeze(x_trapeze, y_trapeze, degree, bottom_base_length, top_base_length, height) };
							ptr_new_elem->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
								static_cast<int>(getRandomNumber(0, 255)));
							ptr_new_elem->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
							ptr_new_elem->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
								static_cast<int>(getRandomNumber(0, 255)));
							push_back_shapes<TFigure>(figures_array, size_figures_array, ptr_new_elem);
							break;
						}
						default:
							std::cout << "Error! type_objs не принадлежит отрезку [1,6]." << std::endl;
							break;
						}
					}
				}
				if (stage_destroy_array && create_array)
				{
					int temp{ size_figures_array };
					for (int i{}; i < temp; i++)
						deleteFigure(figures_array, size_figures_array);
					create_array = false;
					move_array = false;
					move_under_circle_hierarchy = false;
					move_under_quadrilateral_hierarchy = false;
					show_array = true;
				}
			}
			else if ((event_menu_click.type == sf::Event::KeyPressed) && show_array)
			{
				switch (event_menu_click.key.code)
				{
				case sf::Keyboard::Q:
				{
					for (int i{}; i < size_figures_array; i++)
						increaseRadius(figures_array, i);
					break;
				}
				case sf::Keyboard::E:
				{
					for (int i{}; i < size_figures_array; i++)
						decreaseRadius(figures_array, i);
					break;
				}
				case sf::Keyboard::Z:
				{
					for (int i{}; i < size_figures_array; i++)
						increaseSemiMajorAxis(figures_array, i);
					break;
				}
				case sf::Keyboard::X:
				{
					for (int i{}; i < size_figures_array; i++)
						decreaseSemiMajorAxis(figures_array, i);
					break;
				}
				case sf::Keyboard::C:
				{
					for (int i{}; i < size_figures_array; i++)
						increaseSemiMinorAxis(figures_array, i);
					break;
				}
				case sf::Keyboard::V:
				{
					for (int i{}; i < size_figures_array; i++)
						decreaseSemiMinorAxis(figures_array, i);
					break;
				}
				case sf::Keyboard::F:
				{
					for (int i{}; i < size_figures_array; i++)
						rotateEllipse(figures_array, i);
					break;
				}
				case sf::Keyboard::R:
				{
					for (int i{}; i < size_figures_array; i++)
						increaseLengthRect(figures_array, i);
					break;
				}
				case sf::Keyboard::T:
				{
					for (int i{}; i < size_figures_array; i++)
						decreaseLengthRect(figures_array, i);
					break;
				}
				case sf::Keyboard::G:
				{
					for (int i{}; i < size_figures_array; i++)
						increaseWidthRect(figures_array, i);
					break;
				}
				case sf::Keyboard::H:
				{
					for (int i{}; i < size_figures_array; i++)
						decreaseWidthRect(figures_array, i);
					break;
				}
				case sf::Keyboard::B:
				{
					for (int i{}; i < size_figures_array; i++)
						rotateRect(figures_array, i);
					break;
				}
				case sf::Keyboard::Y:
				{
					for (int i{}; i < size_figures_array; i++)
						increaseDimensionsQuadrilateral(figures_array, i);
					break;
				}
				case sf::Keyboard::U:
				{
					for (int i{}; i < size_figures_array; i++)
						decreaseDimensionsQuadrilateral(figures_array, i);
					break;
				}
				case sf::Keyboard::I:
				{
					for (int i{}; i < size_figures_array; i++)
						increaseLengthRhomb(figures_array, i);
					break;
				}
				case sf::Keyboard::O:
				{
					for (int i{}; i < size_figures_array; i++)
						decreaseLengthRhomb(figures_array, i);
					break;
				}
				case sf::Keyboard::J:
				{
					for (int i{}; i < size_figures_array; i++)
						increaseDegreeRhomb(figures_array, i);
					break;
				}
				case sf::Keyboard::K:
				{
					for (int i{}; i < size_figures_array; i++)
						decreaseDegreeRhomb(figures_array, i);
					break;
				}
				case sf::Keyboard::N:
				{
					for (int i{}; i < size_figures_array; i++)
						increaseTopBaseTrapeze(figures_array, i);
					break;
				}
				case sf::Keyboard::M:
				{
					for (int i{}; i < size_figures_array; i++)
						decreaseTopBaseTrapeze(figures_array, i);
					break;
				}
				case sf::Keyboard::Up:
				{
					for (int i{}; i < size_figures_array; i++)
						increaseHeightTrapeze(figures_array, i);
					break;
				}
				case sf::Keyboard::Down:
				{
					for (int i{}; i < size_figures_array; i++)
						decreaseHeightTrapeze(figures_array, i);
					break;
				}
				case sf::Keyboard::Right:
				{
					for (int i{}; i < size_figures_array; i++)
						increaseBottomBaseTrapeze(figures_array, i);
					break;
				}
				case sf::Keyboard::Left:
				{
					for (int i{}; i < size_figures_array; i++)
						decreaseBottomBaseTrapeze(figures_array, i);
					break;
				}
				default:
					break;
				}

				if (move_array)
				{
					switch (event_menu_click.key.code)
					{
					case sf::Keyboard::W:
					{
						for (int i{}; i < size_figures_array; i++)
							figuresMoveW(figures_array, i);
						break;
					}
					case sf::Keyboard::A:
					{
						for (int i{}; i < size_figures_array; i++)
							figuresMoveA(figures_array, i);
						break;
					}
					case sf::Keyboard::S:
					{
						for (int i{}; i < size_figures_array; i++)
							figuresMoveS(figures_array, i);
						break;
					}
					case sf::Keyboard::D:
					{
						for (int i{}; i < size_figures_array; i++)
							figuresMoveD(figures_array, i);
						break;
					}
					default:
						break;
					}
				}
				else if (move_under_circle_hierarchy)
				{
					switch (event_menu_click.key.code)
					{
					case sf::Keyboard::W:
					{
						for (int i{}; i < size_figures_array; i++)
							if ((getChoiceFigure(figures_array, i) == 1) || (getChoiceFigure(figures_array, i) == 2))
								figuresMoveW(figures_array, i);
						break;
					}
					case sf::Keyboard::A:
					{
						for (int i{}; i < size_figures_array; i++)
							if ((getChoiceFigure(figures_array, i) == 1) || (getChoiceFigure(figures_array, i) == 2))
								figuresMoveA(figures_array, i);
						break;
					}
					case sf::Keyboard::S:
					{
						for (int i{}; i < size_figures_array; i++)
							if ((getChoiceFigure(figures_array, i) == 1) || (getChoiceFigure(figures_array, i) == 2))
								figuresMoveS(figures_array, i);
						break;
					}
					case sf::Keyboard::D:
					{
						for (int i{}; i < size_figures_array; i++)
							if ((getChoiceFigure(figures_array, i) == 1) || (getChoiceFigure(figures_array, i) == 2))
								figuresMoveD(figures_array, i);
						break;
					}
					default:
						break;
					}
				}
				else if (move_under_quadrilateral_hierarchy)
				{
					switch (event_menu_click.key.code)
					{
					case sf::Keyboard::W:
					{
						for (int i{}; i < size_figures_array; i++)
							if ((getChoiceFigure(figures_array, i) >= 3) && (getChoiceFigure(figures_array, i) <= 6))
								figuresMoveW(figures_array, i);
						break;
					}
					case sf::Keyboard::A:
					{
						for (int i{}; i < size_figures_array; i++)
							if ((getChoiceFigure(figures_array, i) >= 3) && (getChoiceFigure(figures_array, i) <= 6))
								figuresMoveA(figures_array, i);
						break;
					}
					case sf::Keyboard::S:
					{
						for (int i{}; i < size_figures_array; i++)
							if ((getChoiceFigure(figures_array, i) >= 3) && (getChoiceFigure(figures_array, i) <= 6))
								figuresMoveS(figures_array, i);
						break;
					}
					case sf::Keyboard::D:
					{
						for (int i{}; i < size_figures_array; i++)
							if ((getChoiceFigure(figures_array, i) >= 3) && (getChoiceFigure(figures_array, i) <= 6))
								figuresMoveD(figures_array, i);
						break;
					}
					default:
						break;
					}
				}
			}
		}

		window.clear(sf::Color(67, 136, 169));

		/*РЕНДЕРИНГ ОКНА*/
		//Фон меню и кнопки меню
		BG_general.Show(window);
		BG_menu.Show(window);
		image_text.Show(window);
		menu_text.Show(window);
		BG_exit.Show(window);
		exit_text.Show(window);
		//Кнопки обработки фигур
		BG_ArrayFigures.Show(window);
		ArrayFigures_text.Show(window);
		if (submenu_array)
		{
			BG_CreateFigures.Show(window);
			CreateFigures_text.Show(window);
			BG_DestroyFigures.Show(window);
			DestroyFigures_text.Show(window);
			BG_EraseFigures.Show(window);
			EraseFigures_text.Show(window);
			BG_ShowFigures.Show(window);
			ShowFigures_text.Show(window);
			BG_MoveFigures.Show(window);
			MoveFigures_text.Show(window);
			BG_MoveUnderCircleHierarchy.Show(window);
			MoveUnderCircleHierarchy_text.Show(window);
			BG_MoveUnderQuadrilateralHierarchy.Show(window);
			MoveUnderQuadrilateralHierarchy_text.Show(window);
		}

		if (create_array)
		{
			ChangeDimensionsUnderCircleHierarchy_text.Show(window);
			ChangeDimensionsUnderQuadrilateralHierarchy_text.Show(window);
		}

		if (create_array && show_array)
		{
			for (int i{}; i < size_figures_array; i++)
				figures_array[i]->Show(window);
		}

		window.display();
	}
	return 0;
}