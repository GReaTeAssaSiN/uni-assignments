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
int menu_processing(sf::RenderWindow& window, DynamicArray*& ptr_container_figures_dynamic_array, LynearDynamicList*& ptr_container_figures_lynear_dynamic_list, 
	TFigure*& ptr_graphic_primitive, int& size_container_figures_dynamic_array, int& size_container_figures_lynear_dynamic_list)
{
	/*СОЗДАНИЕ ФОНА ОКНА*/
	//Меню
	Rect_BG_buttons BG_general(0, 0, 700, 895, 5);
	BG_general.m_setFillColor(5, 90, 1);
	//IMAGE
	User_texts image_text("Comic_Sans_MS.TTF", " I  M  A  G  E ", 870, 0, 70);
	//Панель меню
	Rect_BG_buttons BG_menu(5, 5, 695, 85, 5);
	User_texts menu_text("Comic_Sans_MS.TTF", "M E N U ", 120, 0, 70);
	//Кнопка EXIT
	Rect_BG_buttons BG_exit(5, 840, 160, 50, 5);
	User_texts exit_text("Comic_Sans_MS.TTF", "E X I T", 25, 850, 30);
	//Переход на следующую или предыдущую страницу
	Rect_BG_buttons BG_next(600, 5, 100, 85, 5);
	User_texts next_text("Comic_Sans_MS.TTF", "NEXT", 605, 30, 30);
	Rect_BG_buttons BG_back(495, 5, 100, 85, 5);
	User_texts back_text("Comic_Sans_MS.TTF", "BACK", 500, 30, 30);

	/*КНОПКИ ОБРАБОТКИ СОБЫТИЙ*/
	//Контейнер на базе динамического массива
	Rect_BG_buttons BG_ContainerFiguresDynamicArray(5, 96, 200, 60, 5);
	User_texts ContainerFiguresDynamicArray_text("Comic_Sans_MS.TTF", "   CONTAINER\n(DYNAMIC_ARRAY)", 10, 100, 18);
	//Создать
	Rect_BG_buttons BG_CreateContainerFiguresDynamicArray(15, 171, 180, 40, 5);
	User_texts CreateContainerFiguresDynamicArray_text("Comic_Sans_MS.TTF", "CREATE", 45, 175, 27);
	//Добавить элемент
	Rect_BG_buttons BG_AddNewElemCFDA(15, 226, 180, 40, 5);
	User_texts AddNewElemCFDA_text("Comic_Sans_MS.TTF", "ADD NEW ELEM", 25, 235, 20);
	//Уничтожить
	Rect_BG_buttons BG_DestroyCFDA(15, 281, 180, 40, 5);
	User_texts DestroyCFDA_text("Comic_Sans_MS.TTF", "DESTROY", 35, 285, 27);
	//Стереть
	Rect_BG_buttons BG_EraseCFDA(15, 336, 180, 40, 5);
	User_texts EraseCFDA_text("Comic_Sans_MS.TTF", "ERASE", 35, 340, 27);
	//Показать
	Rect_BG_buttons BG_ShowCFDA(15, 391, 180, 40, 5);
	User_texts ShowCFDA_text("Comic_Sans_MS.TTF", "SHOW", 35, 395, 27);
	//Переместить
	Rect_BG_buttons BG_MoveCFDA(15, 446, 180, 40, 5);
	User_texts MoveCFDA_text("Comic_Sans_MS.TTF", "MOVE", 35, 450, 27);
	//Подиерархия кругов
	Rect_BG_buttons BG_MoveUnderCircleHierarchyCFDA(15, 501, 600, 40, 5);
	User_texts MoveUnderCircleHierarchyCFDA_text("Comic_Sans_MS.TTF", "MOVE UNDER CIRCLE HEIRARCHY", 35, 505, 24);
	User_texts ChangeDimensionsUnderCircleHierarchyCFDA_text("Comic_Sans_MS.TTF",
		"\t\tUNDER CIRCLE HIERARCHY\n(q) - increase radius (circle)\n(e) - decrease radius (circle)\n(z) - increase semi major axis (ellipse)"
		"\n(x) - decrease semi major axis(ellipse)\n(c) - increase semi minor axis(ellipse)\n(v) - decrease semi minor axis(ellipse)\n(f) - rotate(ellipse)",
		20, 605, 16);
	//Подиерархия четырехугольников
	Rect_BG_buttons BG_MoveUnderQuadrilateralHierarchyCFDA(15, 556, 600, 40, 5);
	User_texts MoveUnderQuadrilateralHierarchyCFDA_text("Comic_Sans_MS.TTF", "MOVE UNDER QUADRILATERAL HEIRARCHY", 35, 560, 24);
	User_texts ChangeDimensionsUnderQuadrilateralHierarchyCFDA_text("Comic_Sans_MS.TTF",
		"UNDER QUADRILATERAL HIERARCHY\n(r) - increase length (rectangle)\n(t) - decrease length (rectangle)\n(g) - increase width (rectangle)\n(h) - decrease width (rectangle)\n(b) - rotate(rectangle)"
		"\n(y) - increase dimensions (quadrilateral)\n(u) - decrease dimensions (quadrilateral)\n(i) - increase length (rhomb)\n(o) - decrease length (rhomb)\n(j) - increase degree (rhomb)\n(k) - decrease degree (rhomb)"
		"\n(n) - increase TopBase (trapeze)\n(m) - decrease TopBase (trapeze)\n(UP) - increase height (trapeze)\n(DOWN) - decrease height (trapeze)\n(RIGHT) - increase BottomBase (trapeze)\n(LEFT) - decrease BottomBase (trapeze)",
		230, 110, 13);

	//Контейнер на базе линейного списка (односвязного динамического)
	Rect_BG_buttons BG_ContainerFiguresLinearDynamicList(5, 96, 200, 60, 5);
	User_texts ContainerFiguresLinearDynamicList_text("Comic_Sans_MS.TTF", "         CONTAINER\n(LYNEAR_DYNAMIC_LIST)", 6, 110, 13);
	//Создать
	Rect_BG_buttons BG_CreateContainerFiguresLinearDynamicList(15, 171, 180, 40, 5);
	User_texts CreateContainerFiguresLinearDynamicList_text("Comic_Sans_MS.TTF", "CREATE", 45, 175, 27);
	//Добавить элемент
	Rect_BG_buttons BG_AddNewElemCFLDL(15, 226, 180, 40, 5);
	User_texts AddNewElemCFLDL_text("Comic_Sans_MS.TTF", "ADD NEW ELEM", 25, 235, 20);
	//Уничтожить
	Rect_BG_buttons BG_DestroyCFLDL(15, 281, 180, 40, 5);
	User_texts DestroyCFLDL_text("Comic_Sans_MS.TTF", "DESTROY", 35, 285, 27);
	//Стереть
	Rect_BG_buttons BG_EraseCFLDL(15, 336, 180, 40, 5);
	User_texts EraseCFLDL_text("Comic_Sans_MS.TTF", "ERASE", 35, 340, 27);
	//Показать
	Rect_BG_buttons BG_ShowCFLDL(15, 391, 180, 40, 5);
	User_texts ShowCFLDL_text("Comic_Sans_MS.TTF", "SHOW", 35, 395, 27);
	//Переместить
	Rect_BG_buttons BG_MoveCFLDL(15, 446, 180, 40, 5);
	User_texts MoveCFLDL_text("Comic_Sans_MS.TTF", "MOVE", 35, 450, 27);
	//Подиерархия кругов
	Rect_BG_buttons BG_MoveUnderCircleHierarchyCFLDL(15, 501, 600, 40, 5);
	User_texts MoveUnderCircleHierarchyCFLDL_text("Comic_Sans_MS.TTF", "MOVE UNDER CIRCLE HEIRARCHY", 35, 505, 24);
	User_texts ChangeDimensionsUnderCircleHierarchyCFLDL_text("Comic_Sans_MS.TTF",
		"\t\tUNDER CIRCLE HIERARCHY\n(q) - increase radius (circle)\n(e) - decrease radius (circle)\n(z) - increase semi major axis (ellipse)"
		"\n(x) - decrease semi major axis(ellipse)\n(c) - increase semi minor axis(ellipse)\n(v) - decrease semi minor axis(ellipse)\n(f) - rotate(ellipse)",
		20, 605, 16);
	//Подиерархия четырехугольников
	Rect_BG_buttons BG_MoveUnderQuadrilateralHierarchyCFLDL(15, 556, 600, 40, 5);
	User_texts MoveUnderQuadrilateralHierarchyCFLDL_text("Comic_Sans_MS.TTF", "MOVE UNDER QUADRILATERAL HEIRARCHY", 35, 560, 24);
	User_texts ChangeDimensionsUnderQuadrilateralHierarchyCFLDL_text("Comic_Sans_MS.TTF",
		"UNDER QUADRILATERAL HIERARCHY\n(r) - increase length (rectangle)\n(t) - decrease length (rectangle)\n(g) - increase width (rectangle)\n(h) - decrease width (rectangle)\n(b) - rotate(rectangle)"
		"\n(y) - increase dimensions (quadrilateral)\n(u) - decrease dimensions (quadrilateral)\n(i) - increase length (rhomb)\n(o) - decrease length (rhomb)\n(j) - increase degree (rhomb)\n(k) - decrease degree (rhomb)"
		"\n(n) - increase TopBase (trapeze)\n(m) - decrease TopBase (trapeze)\n(UP) - increase height (trapeze)\n(DOWN) - decrease height (trapeze)\n(RIGHT) - increase BottomBase (trapeze)\n(LEFT) - decrease BottomBase (trapeze)",
		230, 110, 13);


	//Привзяка ГПСЧ к календарному времени (случайные последовательности случайных чисел из диапазона)
	srand(static_cast<unsigned int>(time(0)));

	//EXTRAMENU
	int extramenu{ 1 };

	//Внешние переменные функции
	bool submenu_container_figures_dynamic_array{ false };//CONTAINER_FIGURES_DYNAMIC_ARRAY->открывается подменю
	bool submenu_container_figures_linear_dynamic_list{ false };//CONTAINER_FIGURES_LINEAR_DYNAMIC_LIST->открывается подменю
	//Подменю
	bool create_CFDA{ false }, destroy_CFDA{ false }, show_CFDA{ true }, move_CFDA{ false };
	bool create_CFLDL{ false }, destroy_CFLDL{ false }, show_CFLDL{ true }, move_CFLDL{ false };
	//Обработка подиерархий
	bool move_under_circle_hierarchy_CFDA{ false }, move_under_quadrilateral_hierarchy_CFDA{ false };
	bool move_under_circle_hierarchy_CFLDL{ false }, move_under_quadrilateral_hierarchy_CFLDL{ false };

	while (window.isOpen())
	{
		/*ПОКАДРОВАЯ ОБРАБОТКА ЦВЕТОВ СОЗДАННЫХ ОБЪЕКТОВ НА ОКНЕ*/
		//Фон меню и кнопки меню
		image_text.m_setFillColor(111, 206, 253);
		BG_exit.m_setDefaultColor();
		exit_text.m_setDefaultColor();
		BG_next.m_setFillColor(195, 195, 195);
		next_text.m_setDefaultColor();
		BG_back.m_setFillColor(195, 195, 195);
		back_text.m_setDefaultColor();
		//Кнопки обработки фигур
		//Динамический массив
		BG_ContainerFiguresDynamicArray.m_setFillColor(26, 255, 255);
		ContainerFiguresDynamicArray_text.m_setFillColor(24, 48, 229);
		BG_CreateContainerFiguresDynamicArray.m_setFillColor(195, 195, 195);
		CreateContainerFiguresDynamicArray_text.m_setDefaultColor();
		BG_AddNewElemCFDA.m_setFillColor(195, 195, 195);
		AddNewElemCFDA_text.m_setDefaultColor();
		BG_DestroyCFDA.m_setFillColor(195, 195, 195);
		DestroyCFDA_text.m_setDefaultColor();
		BG_EraseCFDA.m_setFillColor(195, 195, 195);
		EraseCFDA_text.m_setDefaultColor();
		BG_ShowCFDA.m_setFillColor(195, 195, 195);
		ShowCFDA_text.m_setDefaultColor();
		ChangeDimensionsUnderCircleHierarchyCFDA_text.m_setFillColor(209, 255, 26);
		ChangeDimensionsUnderQuadrilateralHierarchyCFDA_text.m_setFillColor(209, 255, 26);
		//Динамический линейный список
		BG_ContainerFiguresLinearDynamicList.m_setFillColor(26, 255, 255);
		ContainerFiguresLinearDynamicList_text.m_setFillColor(24, 48, 229);
		BG_CreateContainerFiguresLinearDynamicList.m_setFillColor(195, 195, 195);
		CreateContainerFiguresLinearDynamicList_text.m_setDefaultColor();
		BG_AddNewElemCFLDL.m_setFillColor(195, 195, 195);
		AddNewElemCFLDL_text.m_setDefaultColor();
		BG_DestroyCFLDL.m_setFillColor(195, 195, 195);
		DestroyCFLDL_text.m_setDefaultColor();
		BG_EraseCFLDL.m_setFillColor(195, 195, 195);
		EraseCFLDL_text.m_setDefaultColor();
		BG_ShowCFLDL.m_setFillColor(195, 195, 195);
		ShowCFLDL_text.m_setDefaultColor();
		ChangeDimensionsUnderCircleHierarchyCFLDL_text.m_setFillColor(209, 255, 26);
		ChangeDimensionsUnderQuadrilateralHierarchyCFLDL_text.m_setFillColor(209, 255, 26);

		/*БУЛЕВЫЕ ПЕРЕМЕННЫЕ ДЛЯ ПОЛОЖЕНИЯ КУРСОРА НА КНОПКЕ*/
		//Кнопки меню
		bool stage_exit{ false }, stage_next{ false }, stage_back{ false };
		//Кнопки обработки фигур
		/*Контейнер на базе динамического массива*/
		bool stage_container_figures_dynamic_array{ false }, stage_create_CFDA{ false }, stage_add_new_elem_CFDA{ false }, stage_destroy_CFDA{ false },
			stage_erase_CFDA{ false }, stage_show_CFDA{ false }, stage_move_CFDA{ false };
		//Кнопки обработки подиерархий
		bool stage_move_under_circle_hierarchy_CFDA{ false }, stage_move_under_quadrilateral_hierarchy_CFDA{ false };
		/*Контейнер на базе динамического линейного списка*/
		bool stage_container_figures_linear_dynamic_list{ false }, stage_create_CFLDL{ false }, stage_add_new_elem_CFLDL{ false }, stage_destroy_CFLDL{ false },
			stage_erase_CFLDL{ false }, stage_show_CFLDL{ false }, stage_move_CFLDL{ false };
		//Кнопки обработки подиерархий
		bool stage_move_under_circle_hierarchy_CFLDL{ false }, stage_move_under_quadrilateral_hierarchy_CFLDL{ false };

		/*ОКРАШИВАНИЕ АКТИВНЫХ КНОПОК*/
		if (!submenu_container_figures_dynamic_array)
		{
			BG_ContainerFiguresDynamicArray.m_setDefaultColor();
			ContainerFiguresDynamicArray_text.m_setDefaultColor();
		}
		if (!move_CFDA)
		{
			BG_MoveCFDA.m_setFillColor(195, 195, 195);
			MoveCFDA_text.m_setDefaultColor();
		}
		if (!move_under_circle_hierarchy_CFDA)
		{
			BG_MoveUnderCircleHierarchyCFDA.m_setFillColor(195, 195, 195);
			MoveUnderCircleHierarchyCFDA_text.m_setDefaultColor();
		}
		if (!move_under_quadrilateral_hierarchy_CFDA)
		{
			BG_MoveUnderQuadrilateralHierarchyCFDA.m_setFillColor(195, 195, 195);
			MoveUnderQuadrilateralHierarchyCFDA_text.m_setDefaultColor();
		}
		if (!submenu_container_figures_linear_dynamic_list)
		{
			BG_ContainerFiguresLinearDynamicList.m_setDefaultColor();
			ContainerFiguresLinearDynamicList_text.m_setDefaultColor();
		}
		if (!move_CFLDL)
		{
			BG_MoveCFLDL.m_setFillColor(195, 195, 195);
			MoveCFLDL_text.m_setDefaultColor();
		}
		if (!move_under_circle_hierarchy_CFLDL)
		{
			BG_MoveUnderCircleHierarchyCFLDL.m_setFillColor(195, 195, 195);
			MoveUnderCircleHierarchyCFLDL_text.m_setDefaultColor();
		}
		if (!move_under_quadrilateral_hierarchy_CFLDL)
		{
			BG_MoveUnderQuadrilateralHierarchyCFLDL.m_setFillColor(195, 195, 195);
			MoveUnderQuadrilateralHierarchyCFLDL_text.m_setDefaultColor();
		}

		/*ОКРАШИВАНИЕ КНОПОК ПРИ НАВЕДЕНИИ КУРСОРА МЫШИ (с изменением значения соответствующих переменных*/
		//EXIT
		if (sf::IntRect(5, 840, 160, 50).contains(sf::Mouse::getPosition(window)))
		{
			BG_exit.m_setActiveColor();
			exit_text.m_setActiveColor();
			stage_exit = true;
		}
		if (sf::IntRect(600, 5, 100, 85).contains(sf::Mouse::getPosition(window)))
		{
			BG_next.m_setActiveColor();
			next_text.m_setActiveColor();
			stage_next = true;
		}
		if (sf::IntRect(495, 5, 100, 85).contains(sf::Mouse::getPosition(window)))
		{
			BG_back.m_setActiveColor();
			back_text.m_setActiveColor();
			stage_back = true;
		}
		if (extramenu == 1)
		{
			//Меню контейнера на базе динамического массива
			if (sf::IntRect(5, 96, 200, 60).contains(sf::Mouse::getPosition(window)))
			{
				BG_ContainerFiguresDynamicArray.m_setActiveColor();
				ContainerFiguresDynamicArray_text.m_setActiveColor();
				stage_container_figures_dynamic_array = true;
			}
			//Подменю
			if (sf::IntRect(15, 171, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_dynamic_array)
			{
				BG_CreateContainerFiguresDynamicArray.m_setActiveColor();
				CreateContainerFiguresDynamicArray_text.m_setActiveColor();
				stage_create_CFDA = true;
			}
			if (sf::IntRect(15, 226, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_dynamic_array)
			{
				BG_AddNewElemCFDA.m_setActiveColor();
				AddNewElemCFDA_text.m_setActiveColor();
				stage_add_new_elem_CFDA = true;
			}
			if (sf::IntRect(15, 281, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_dynamic_array)
			{
				BG_DestroyCFDA.m_setActiveColor();
				DestroyCFDA_text.m_setActiveColor();
				stage_destroy_CFDA = true;
			}
			if (sf::IntRect(15, 336, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_dynamic_array)
			{
				BG_EraseCFDA.m_setActiveColor();
				EraseCFDA_text.m_setActiveColor();
				stage_erase_CFDA = true;
			}
			if (sf::IntRect(15, 391, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_dynamic_array)
			{
				BG_ShowCFDA.m_setActiveColor();
				ShowCFDA_text.m_setActiveColor();
				stage_show_CFDA = true;
			}
			if (sf::IntRect(15, 446, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_dynamic_array)
			{
				BG_MoveCFDA.m_setActiveColor();
				MoveCFDA_text.m_setActiveColor();
				stage_move_CFDA = true;
			}
			if (sf::IntRect(15, 501, 600, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_dynamic_array)
			{
				BG_MoveUnderCircleHierarchyCFDA.m_setActiveColor();
				MoveUnderCircleHierarchyCFDA_text.m_setActiveColor();
				stage_move_under_circle_hierarchy_CFDA = true;
			}
			if (sf::IntRect(15, 556, 600, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_dynamic_array)
			{
				BG_MoveUnderQuadrilateralHierarchyCFDA.m_setActiveColor();
				MoveUnderQuadrilateralHierarchyCFDA_text.m_setActiveColor();
				stage_move_under_quadrilateral_hierarchy_CFDA = true;
			}
		}
		else if (extramenu == 2)
		{
			//Меню контейнера на базе линейного динамического списка
			if (sf::IntRect(5, 96, 200, 60).contains(sf::Mouse::getPosition(window)))
			{
				BG_ContainerFiguresLinearDynamicList.m_setActiveColor();
				ContainerFiguresLinearDynamicList_text.m_setActiveColor();
				stage_container_figures_linear_dynamic_list = true;
			}
			//Подменю
			if (sf::IntRect(15, 171, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_linear_dynamic_list)
			{
				BG_CreateContainerFiguresLinearDynamicList.m_setActiveColor();
				CreateContainerFiguresLinearDynamicList_text.m_setActiveColor();
				stage_create_CFLDL = true;
			}
			if (sf::IntRect(15, 226, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_linear_dynamic_list)
			{
				BG_AddNewElemCFLDL.m_setActiveColor();
				AddNewElemCFLDL_text.m_setActiveColor();
				stage_add_new_elem_CFLDL = true;
			}
			if (sf::IntRect(15, 281, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_linear_dynamic_list)
			{
				BG_DestroyCFLDL.m_setActiveColor();
				DestroyCFLDL_text.m_setActiveColor();
				stage_destroy_CFLDL = true;
			}
			if (sf::IntRect(15, 336, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_linear_dynamic_list)
			{
				BG_EraseCFLDL.m_setActiveColor();
				EraseCFLDL_text.m_setActiveColor();
				stage_erase_CFLDL = true;
			}
			if (sf::IntRect(15, 391, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_linear_dynamic_list)
			{
				BG_ShowCFLDL.m_setActiveColor();
				ShowCFLDL_text.m_setActiveColor();
				stage_show_CFLDL = true;
			}
			if (sf::IntRect(15, 446, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_linear_dynamic_list)
			{
				BG_MoveCFLDL.m_setActiveColor();
				MoveCFLDL_text.m_setActiveColor();
				stage_move_CFLDL = true;
			}
			if (sf::IntRect(15, 501, 600, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_linear_dynamic_list)
			{
				BG_MoveUnderCircleHierarchyCFLDL.m_setActiveColor();
				MoveUnderCircleHierarchyCFLDL_text.m_setActiveColor();
				stage_move_under_circle_hierarchy_CFLDL = true;
			}
			if (sf::IntRect(15, 556, 600, 40).contains(sf::Mouse::getPosition(window)) && submenu_container_figures_linear_dynamic_list)
			{
				BG_MoveUnderQuadrilateralHierarchyCFLDL.m_setActiveColor();
				MoveUnderQuadrilateralHierarchyCFLDL_text.m_setActiveColor();
				stage_move_under_quadrilateral_hierarchy_CFLDL = true;
			}
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
				//NEXT
				if (stage_back)
					extramenu = 1;
				//BACK
				if (stage_next)
					extramenu = 2;
				//EXIT
				if (stage_exit)
					window.close();
				//CFDA
				if (stage_container_figures_dynamic_array)
					submenu_container_figures_dynamic_array = !submenu_container_figures_dynamic_array;
				if (stage_move_CFDA && create_CFDA)
				{
					move_CFDA = !move_CFDA;
					move_under_circle_hierarchy_CFDA = false;
					move_under_quadrilateral_hierarchy_CFDA = false;
					move_CFLDL = false;
					move_under_circle_hierarchy_CFLDL = false;
					move_under_quadrilateral_hierarchy_CFLDL = false;
				}
				if (stage_move_under_circle_hierarchy_CFDA && create_CFDA)
				{
					move_under_circle_hierarchy_CFDA = !move_under_circle_hierarchy_CFDA;
					move_CFDA = false;
					move_under_quadrilateral_hierarchy_CFDA = false;
					move_CFLDL = false;
					move_under_circle_hierarchy_CFLDL = false;
					move_under_quadrilateral_hierarchy_CFLDL = false;
				}
				if (stage_move_under_quadrilateral_hierarchy_CFDA && create_CFDA)
				{
					move_under_quadrilateral_hierarchy_CFDA = !move_under_quadrilateral_hierarchy_CFDA;
					move_CFDA = false;
					move_under_circle_hierarchy_CFDA = false;
					move_CFLDL = false;
					move_under_circle_hierarchy_CFLDL = false;
					move_under_quadrilateral_hierarchy_CFLDL = false;
				}
				if (stage_erase_CFDA && create_CFDA)
					show_CFDA = false;
				if (stage_show_CFDA && create_CFDA)
					show_CFDA = true;
				if (stage_create_CFDA && !create_CFDA)
				{
					create_CFDA = true;
					int number_elems{ static_cast<int>(getRandomNumber(20, 30)) };
					ptr_container_figures_dynamic_array = new DynamicArray(number_elems);
				}
				if (stage_add_new_elem_CFDA && create_CFDA && (size_container_figures_dynamic_array + 1 <= ptr_container_figures_dynamic_array->getSize()))
				{
					size_container_figures_dynamic_array++;
					int type_objs{ static_cast<int>(getRandomNumber(1, 6)) };
					switch (type_objs)
					{
					case 1:
					{
						float radius_circle{ getRandomNumber(10,100) };
						float x_circle{ getRandomNumber(720, 1485) };
						float y_circle{ getRandomNumber(110, 885) };
						ptr_graphic_primitive = new TCircle(x_circle, y_circle, radius_circle);
						ptr_graphic_primitive->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						break;
					}
					case 2:
					{
						float x_ellipse{ getRandomNumber(770, 1435) };
						float y_ellipse{ getRandomNumber(130, 835) };
						float ellipse_semi_major_axis{ getRandomNumber(60, 150) };
						float ellipse_semi_minor_axis{ getRandomNumber(30, ellipse_semi_major_axis - 10) };
						ptr_graphic_primitive = new TEllipse(x_ellipse, y_ellipse, ellipse_semi_major_axis, ellipse_semi_minor_axis);
						ptr_graphic_primitive->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
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
						ptr_graphic_primitive = new TQuadrilateral(corner_x1, corner_y1, corner_x2, corner_y2, corner_x3, corner_y3, corner_x4, corner_y4);
						ptr_graphic_primitive->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						break;
					}
					case 4:
					{
						float length_rect{ getRandomNumber(50, 300) };
						float width_rect{ getRandomNumber(25, 150) };
						float x_rect{ getRandomNumber(710, 1445) };
						float y_rect{ getRandomNumber(100, 870) };
						ptr_graphic_primitive = new TRectangle(x_rect, y_rect, length_rect, width_rect);
						ptr_graphic_primitive->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						break;
					}
					case 5:
					{
						float rhomb_length{ getRandomNumber(60, 150) };
						int rhomb_degree{ static_cast<int>(getRandomNumber(30, 60)) };
						float x_rhomb{ getRandomNumber(710, 1495 - 2 * rhomb_length * cos(rhomb_degree * PI / 180)) };
						float y_rhomb{ getRandomNumber(100 + rhomb_length * sin(rhomb_degree * PI / 180), 895 - rhomb_length * sin(rhomb_degree * PI / 180)) };
						ptr_graphic_primitive = new TRhomb(x_rhomb, y_rhomb, rhomb_length, rhomb_degree);
						ptr_graphic_primitive->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
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
						ptr_graphic_primitive = new TTrapeze(x_trapeze, y_trapeze, degree, bottom_base_length, top_base_length, height);
						ptr_graphic_primitive->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						break;
					}
					default:
						std::cout << "Error! type_objs не принадлежит отрезку [1,6]." << std::endl;
						break;
					}
					ptr_container_figures_dynamic_array->addNewElem(size_container_figures_dynamic_array - 1, ptr_graphic_primitive);
					ptr_graphic_primitive = nullptr;
				}
				if (stage_destroy_CFDA && create_CFDA)
				{
					ptr_container_figures_dynamic_array->Iterator(1, size_container_figures_dynamic_array, window);
					ptr_container_figures_dynamic_array->Free();
					delete ptr_container_figures_dynamic_array;
					ptr_container_figures_dynamic_array = nullptr;
					size_container_figures_dynamic_array = 0;
					create_CFDA = false;
					move_CFDA = false;
					move_under_circle_hierarchy_CFDA = false;
					move_under_quadrilateral_hierarchy_CFDA = false;
					show_CFDA = true;
				}

				//CFLDL
				if (stage_container_figures_linear_dynamic_list)
					submenu_container_figures_linear_dynamic_list = !submenu_container_figures_linear_dynamic_list;
				if (stage_move_CFLDL && create_CFLDL)
				{
					move_CFLDL = !move_CFLDL;
					move_under_circle_hierarchy_CFLDL = false;
					move_under_quadrilateral_hierarchy_CFLDL = false;
					move_CFDA = false;
					move_under_circle_hierarchy_CFDA = false;
					move_under_quadrilateral_hierarchy_CFDA = false;
				}
				if (stage_move_under_circle_hierarchy_CFLDL && create_CFLDL)
				{
					move_under_circle_hierarchy_CFLDL = !move_under_circle_hierarchy_CFLDL;
					move_CFLDL = false;
					move_under_quadrilateral_hierarchy_CFLDL = false;
					move_CFDA = false;
					move_under_circle_hierarchy_CFDA = false;
					move_under_quadrilateral_hierarchy_CFDA = false;
				}
				if (stage_move_under_quadrilateral_hierarchy_CFLDL && create_CFLDL)
				{
					move_under_quadrilateral_hierarchy_CFLDL = !move_under_quadrilateral_hierarchy_CFLDL;
					move_CFLDL = false;
					move_under_circle_hierarchy_CFLDL = false;
					move_CFDA = false;
					move_under_circle_hierarchy_CFDA = false;
					move_under_quadrilateral_hierarchy_CFDA = false;
				}
				if (stage_erase_CFLDL && create_CFLDL)
					show_CFLDL = false;
				if (stage_show_CFLDL && create_CFLDL)
					show_CFLDL = true;
				if (stage_create_CFLDL && !create_CFLDL)
				{
					create_CFLDL = true;
				    size_container_figures_lynear_dynamic_list = static_cast<int>(getRandomNumber(20, 30));
					ptr_container_figures_lynear_dynamic_list = new LynearDynamicList(size_container_figures_lynear_dynamic_list);
				}
				if (stage_add_new_elem_CFLDL && create_CFLDL && (ptr_container_figures_lynear_dynamic_list->getSize() + 1 <= size_container_figures_lynear_dynamic_list))
				{
					int type_objs{ static_cast<int>(getRandomNumber(1, 6)) };
					switch (type_objs)
					{
					case 1:
					{
						float radius_circle{ getRandomNumber(10,100) };
						float x_circle{ getRandomNumber(720, 1485) };
						float y_circle{ getRandomNumber(110, 885) };
						ptr_graphic_primitive = new TCircle(x_circle, y_circle, radius_circle);
						ptr_graphic_primitive->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						break;
					}
					case 2:
					{
						float x_ellipse{ getRandomNumber(770, 1435) };
						float y_ellipse{ getRandomNumber(130, 835) };
						float ellipse_semi_major_axis{ getRandomNumber(60, 150) };
						float ellipse_semi_minor_axis{ getRandomNumber(30, ellipse_semi_major_axis - 10) };
						ptr_graphic_primitive = new TEllipse(x_ellipse, y_ellipse, ellipse_semi_major_axis, ellipse_semi_minor_axis);
						ptr_graphic_primitive->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
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
						ptr_graphic_primitive = new TQuadrilateral(corner_x1, corner_y1, corner_x2, corner_y2, corner_x3, corner_y3, corner_x4, corner_y4);
						ptr_graphic_primitive->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						break;
					}
					case 4:
					{
						float length_rect{ getRandomNumber(50, 300) };
						float width_rect{ getRandomNumber(25, 150) };
						float x_rect{ getRandomNumber(710, 1445) };
						float y_rect{ getRandomNumber(100, 870) };
						ptr_graphic_primitive = new TRectangle(x_rect, y_rect, length_rect, width_rect);
						ptr_graphic_primitive->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						break;
					}
					case 5:
					{
						float rhomb_length{ getRandomNumber(60, 150) };
						int rhomb_degree{ static_cast<int>(getRandomNumber(30, 60)) };
						float x_rhomb{ getRandomNumber(710, 1495 - 2 * rhomb_length * cos(rhomb_degree * PI / 180)) };
						float y_rhomb{ getRandomNumber(100 + rhomb_length * sin(rhomb_degree * PI / 180), 895 - rhomb_length * sin(rhomb_degree * PI / 180)) };
						ptr_graphic_primitive = new TRhomb(x_rhomb, y_rhomb, rhomb_length, rhomb_degree);
						ptr_graphic_primitive->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
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
						ptr_graphic_primitive = new TTrapeze(x_trapeze, y_trapeze, degree, bottom_base_length, top_base_length, height);
						ptr_graphic_primitive->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_graphic_primitive->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						break;
					}
					default:
						std::cout << "Error! type_objs не принадлежит отрезку [1,6]." << std::endl;
						break;
					}
					ptr_container_figures_lynear_dynamic_list->addNewElem(ptr_graphic_primitive);
					ptr_graphic_primitive = nullptr;
				}
				if (stage_destroy_CFLDL && create_CFLDL)
				{
					ptr_container_figures_lynear_dynamic_list->Iterator(1, window);
					ptr_container_figures_lynear_dynamic_list->Free(ptr_container_figures_lynear_dynamic_list);
					size_container_figures_lynear_dynamic_list = 0;
					create_CFLDL = false;
					move_CFLDL = false;
					move_under_circle_hierarchy_CFLDL = false;
					move_under_quadrilateral_hierarchy_CFLDL = false;
					show_CFLDL = true;
				}

			}
			else if ((event_menu_click.type == sf::Event::KeyPressed))
			{
				if (show_CFDA)
				{
					if (extramenu == 1)
					{
						switch (event_menu_click.key.code)
						{
						case sf::Keyboard::Q:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								increaseRadiusCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::E:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								decreaseRadiusCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::Z:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								increaseSemiMajorAxisCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::X:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								decreaseSemiMajorAxisCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::C:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								increaseSemiMinorAxisCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::V:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								decreaseSemiMinorAxisCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::F:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								rotateEllipseCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::R:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								increaseLengthRectCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::T:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								decreaseLengthRectCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::G:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								increaseWidthRectCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::H:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								decreaseWidthRectCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::B:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								rotateRectCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::Y:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								increaseDimensionsQuadrilateralCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::U:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								decreaseDimensionsQuadrilateralCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::I:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								increaseLengthRhombCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::O:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								decreaseLengthRhombCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::J:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								increaseDegreeRhombCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::K:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								decreaseDegreeRhombCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::N:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								increaseTopBaseTrapezeCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::M:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								decreaseTopBaseTrapezeCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::Up:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								increaseHeightTrapezeCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::Down:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								decreaseHeightTrapezeCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::Right:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								increaseBottomBaseTrapezeCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						case sf::Keyboard::Left:
						{
							for (int i{}; i < size_container_figures_dynamic_array; i++)
								decreaseBottomBaseTrapezeCFDA(ptr_container_figures_dynamic_array, i);
							break;
						}
						default:
							break;
						}
					}

					if (move_CFDA)
					{
						switch (event_menu_click.key.code)
						{
						case sf::Keyboard::W:
						{
							ptr_container_figures_dynamic_array->Iterator(2, size_container_figures_dynamic_array, window);
							break;
						}
						case sf::Keyboard::A:
						{
							ptr_container_figures_dynamic_array->Iterator(3, size_container_figures_dynamic_array, window);
							break;
						}
						case sf::Keyboard::S:
						{
							ptr_container_figures_dynamic_array->Iterator(4, size_container_figures_dynamic_array, window);
							break;
						}
						case sf::Keyboard::D:
						{
							ptr_container_figures_dynamic_array->Iterator(5, size_container_figures_dynamic_array, window);
							break;
						}
						default:
							break;
						}
					}
					else if (move_under_circle_hierarchy_CFDA)
					{
						switch (event_menu_click.key.code)
						{
						case sf::Keyboard::W:
						{
							ptr_container_figures_dynamic_array->Iterator(6, size_container_figures_dynamic_array, window);
							break;
						}
						case sf::Keyboard::A:
						{
							ptr_container_figures_dynamic_array->Iterator(7, size_container_figures_dynamic_array, window);
							break;
						}
						case sf::Keyboard::S:
						{
							ptr_container_figures_dynamic_array->Iterator(8, size_container_figures_dynamic_array, window);
							break;
						}
						case sf::Keyboard::D:
						{
							ptr_container_figures_dynamic_array->Iterator(9, size_container_figures_dynamic_array, window);
							break;
						}
						default:
							break;
						}
					}
					else if (move_under_quadrilateral_hierarchy_CFDA)
					{
						switch (event_menu_click.key.code)
						{
						case sf::Keyboard::W:
						{
							ptr_container_figures_dynamic_array->Iterator(10, size_container_figures_dynamic_array, window);
							break;
						}
						case sf::Keyboard::A:
						{
							ptr_container_figures_dynamic_array->Iterator(11, size_container_figures_dynamic_array, window);
							break;
						}
						case sf::Keyboard::S:
						{
							ptr_container_figures_dynamic_array->Iterator(12, size_container_figures_dynamic_array, window);
							break;
						}
						case sf::Keyboard::D:
						{
							ptr_container_figures_dynamic_array->Iterator(13, size_container_figures_dynamic_array, window);
							break;
						}
						default:
							break;
						}
					}
				}

				if (show_CFLDL)
				{
					if (extramenu == 2)
					{
						switch (event_menu_click.key.code)
						{
						case sf::Keyboard::Q:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								increaseRadiusCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::E:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								decreaseRadiusCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::Z:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								increaseSemiMajorAxisCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::X:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								decreaseSemiMajorAxisCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::C:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								increaseSemiMinorAxisCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::V:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								decreaseSemiMinorAxisCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::F:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								rotateEllipseCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::R:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								increaseLengthRectCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::T:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								decreaseLengthRectCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::G:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								increaseWidthRectCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::H:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								decreaseWidthRectCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::B:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								rotateRectCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::Y:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								increaseDimensionsQuadrilateralCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::U:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								decreaseDimensionsQuadrilateralCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::I:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								increaseLengthRhombCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::O:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								decreaseLengthRhombCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::J:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								increaseDegreeRhombCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::K:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								decreaseDegreeRhombCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::N:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								increaseTopBaseTrapezeCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::M:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								decreaseTopBaseTrapezeCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::Up:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								increaseHeightTrapezeCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::Down:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								decreaseHeightTrapezeCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::Right:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								increaseBottomBaseTrapezeCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						case sf::Keyboard::Left:
						{
							for (int i{}; i < ptr_container_figures_lynear_dynamic_list->getSize(); i++)
								decreaseBottomBaseTrapezeCFLDL(ptr_container_figures_lynear_dynamic_list, ptr_container_figures_lynear_dynamic_list->getNodeData(i));
							break;
						}
						default:
							break;
						}
					}

					if (move_CFLDL)
					{
						switch (event_menu_click.key.code)
						{
						case sf::Keyboard::W:
						{
							ptr_container_figures_lynear_dynamic_list->Iterator(2, window);
							break;
						}
						case sf::Keyboard::A:
						{
							ptr_container_figures_lynear_dynamic_list->Iterator(3, window);
							break;
						}
						case sf::Keyboard::S:
						{
							ptr_container_figures_lynear_dynamic_list->Iterator(4, window);
							break;
						}
						case sf::Keyboard::D:
						{
							ptr_container_figures_lynear_dynamic_list->Iterator(5, window);
							break;
						}
						default:
							break;
						}
					}
					else if (move_under_circle_hierarchy_CFLDL)
					{
						switch (event_menu_click.key.code)
						{
						case sf::Keyboard::W:
						{
							ptr_container_figures_lynear_dynamic_list->Iterator(6, window);
							break;
						}
						case sf::Keyboard::A:
						{
							ptr_container_figures_lynear_dynamic_list->Iterator(7, window);
							break;
						}
						case sf::Keyboard::S:
						{
							ptr_container_figures_lynear_dynamic_list->Iterator(8, window);
							break;
						}
						case sf::Keyboard::D:
						{
							ptr_container_figures_lynear_dynamic_list->Iterator(9, window);
							break;
						}
						default:
							break;
						}
					}
					else if (move_under_quadrilateral_hierarchy_CFLDL)
					{
						switch (event_menu_click.key.code)
						{
						case sf::Keyboard::W:
						{
							ptr_container_figures_lynear_dynamic_list->Iterator(10, window);
							break;
						}
						case sf::Keyboard::A:
						{
							ptr_container_figures_lynear_dynamic_list->Iterator(11, window);
							break;
						}
						case sf::Keyboard::S:
						{
							ptr_container_figures_lynear_dynamic_list->Iterator(12, window);
							break;
						}
						case sf::Keyboard::D:
						{
							ptr_container_figures_lynear_dynamic_list->Iterator(13, window);
							break;
						}
						default:
							break;
						}
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
		if (extramenu == 1)
		{
			BG_ContainerFiguresDynamicArray.Show(window);
			ContainerFiguresDynamicArray_text.Show(window);
			BG_next.Show(window);
			next_text.Show(window);
			if (submenu_container_figures_dynamic_array)
			{
				BG_CreateContainerFiguresDynamicArray.Show(window);
				CreateContainerFiguresDynamicArray_text.Show(window);
				BG_AddNewElemCFDA.Show(window);
				AddNewElemCFDA_text.Show(window);
				BG_DestroyCFDA.Show(window);
				DestroyCFDA_text.Show(window);
				BG_EraseCFDA.Show(window);
				EraseCFDA_text.Show(window);
				BG_ShowCFDA.Show(window);
				ShowCFDA_text.Show(window);
				BG_MoveCFDA.Show(window);
				MoveCFDA_text.Show(window);
				BG_MoveUnderCircleHierarchyCFDA.Show(window);
				MoveUnderCircleHierarchyCFDA_text.Show(window);
				BG_MoveUnderQuadrilateralHierarchyCFDA.Show(window);
				MoveUnderQuadrilateralHierarchyCFDA_text.Show(window);
			}

			if (create_CFDA && size_container_figures_dynamic_array != 0)
			{
				ChangeDimensionsUnderCircleHierarchyCFDA_text.Show(window);
				ChangeDimensionsUnderQuadrilateralHierarchyCFDA_text.Show(window);
			}
		}
		else if (extramenu == 2)
		{
			BG_ContainerFiguresLinearDynamicList.Show(window);
			ContainerFiguresLinearDynamicList_text.Show(window);
			BG_back.Show(window);
			back_text.Show(window);
			if (submenu_container_figures_linear_dynamic_list)
			{
				BG_CreateContainerFiguresLinearDynamicList.Show(window);
				CreateContainerFiguresLinearDynamicList_text.Show(window);
				BG_AddNewElemCFLDL.Show(window);
				AddNewElemCFLDL_text.Show(window);
				BG_DestroyCFLDL.Show(window);
				DestroyCFLDL_text.Show(window);
				BG_EraseCFLDL.Show(window);
				EraseCFLDL_text.Show(window);
				BG_ShowCFLDL.Show(window);
				ShowCFLDL_text.Show(window);
				BG_MoveCFLDL.Show(window);
				MoveCFLDL_text.Show(window);
				BG_MoveUnderCircleHierarchyCFLDL.Show(window);
				MoveUnderCircleHierarchyCFLDL_text.Show(window);
				BG_MoveUnderQuadrilateralHierarchyCFLDL.Show(window);
				MoveUnderQuadrilateralHierarchyCFLDL_text.Show(window);
			}

			if (create_CFLDL && ptr_container_figures_lynear_dynamic_list->getSize() != 0)
			{
				ChangeDimensionsUnderCircleHierarchyCFLDL_text.Show(window);
				ChangeDimensionsUnderQuadrilateralHierarchyCFLDL_text.Show(window);
			}
		}

		if (create_CFDA && show_CFDA)
		{
			ptr_container_figures_dynamic_array->Iterator(14, size_container_figures_dynamic_array, window);
		}

		if (create_CFLDL && show_CFLDL)
		{
			ptr_container_figures_lynear_dynamic_list->Iterator(14, window);
		}

		window.display();
	}
	return 0;
}