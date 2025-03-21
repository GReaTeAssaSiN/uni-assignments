#include <cstdlib> //для функций rand() и srand()
#include <ctime> //для функции time()
#include <iostream> //для вывода информации о действии на консоль
#include "myfuncs.h"
#include "constants.h"
#include "user_buttons.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Linesegment.h"

//ГПСЧ
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}

//Оновная работа программы
int menu_processing(sf::RenderWindow& window, Circle*& f_ptr_obj_circle, Rectangle*& f_ptr_obj_rect, Linesegment*& f_ptr_obj_linesegment,
	int& array_circles_size, Circle**& array_circles,
	int& array_rectangles_size, Rectangle**& array_rectangles,
	int& array_linesegments_size, Linesegment**& array_linesegments)
{
	/*СОЗДАНИЕ ФОНА ОКНА*/
	//Меню
	Rect_BG_buttons BG_general(0, 0, 700, 895, 5);
	BG_general.m_setFillColor(5, 90, 1);
	//IMAGE
	User_texts image_text("Comic_Sans_MS.TTF", " I  M  A  G  E ", 870, 0, 70);
	//Панель меню
	Rect_BG_buttons BG_menu(5, 5, 695, 85, 5);
	User_texts menu_text("Comic_Sans_MS.TTF", " M   E   N   U ", 20, 0, 70);
	//Панель подменю
	Rect_BG_buttons BG_submenu_obj(5, 360, 695, 80, 5);
	User_texts submenu_obj_text("Comic_Sans_MS.TTF", "S U B M E N U", 20, 360, 65);
	//Кнопка создания объектов массивами из 15 фигур
	Rect_BG_buttons BG_create_15_objs(500, 360, 200, 80, 5);
	User_texts create_15_objs_text("Comic_Sans_MS.TTF", "create_15_objs", 505, 380, 23);
	

	/*КНОПКИ МЕНЮ*/
	//Кнопка CREATE
	Rect_BG_buttons BG_create(5, 96, 200, 120, 5);
	User_texts create_text("Comic_Sans_MS.TTF", "C R E A T E", 15, 135, 30);
	//Кнопка MOVE AND CHANGE
	Rect_BG_buttons BG_move_and_change(5, 229, 200, 120, 5);
	User_texts move_and_change_text("Comic_Sans_MS.TTF", " M  O  V  E\n\t  and   \nC H A N G E", 15, 230, 30);
	//Кнопка EXIT
	Rect_BG_buttons BG_exit(5, 840, 160, 50, 5);
	User_texts exit_text("Comic_Sans_MS.TTF", "E X I T", 25, 850, 30);

	/*КНОПКИ ПОДМЕНЮ CREATE*/
	//CREATE->circle
	Rect_BG_buttons BG_circle(220, 97, 140, 40, 5);
	User_texts circle_text("Comic_Sans_MS.TTF", "circle", 250, 100, 25);
	//CREATE->rectangle
	Rect_BG_buttons BG_rect(375, 97, 140, 40, 5);
	User_texts rect_text("Comic_Sans_MS.TTF", "rectangle", 390, 100, 25);
	//CREATE->linesegment
	Rect_BG_buttons BG_linesegment(529, 97, 165, 40, 5);
	User_texts linesegment_text("Comic_Sans_MS.TTF", "linesegment", 540, 100, 25);
	//CREATE->create arrays of graphics primitives
	Rect_BG_buttons BG_create_arrays(220, 160, 473, 40, 5);
	User_texts create_arrays_text("Comic_Sans_MS.TTF", "create arrays of graphics primitives", 231, 165, 25);

	/*КНОПКИ ПОДМЕНЮ CREATE->create array of graphics primitives*/
	//Create->create arrays of graphics primitives->array of circles
	Rect_BG_buttons BG_create_array_circles(5, 460, 175, 40, 5);
	User_texts create_array_circles_text("Comic_Sans_MS.TTF", "array of circles", 10, 467, 20);
	//Create->create arrays of graphics primitives->array of rectangles
	Rect_BG_buttons BG_create_array_rectangles(195, 460, 210, 40, 5);
	User_texts create_array_rectangles_text("Comic_Sans_MS.TTF", "array of rectangles", 195, 467, 20);
	//Create->create arrays of graphics primitives->array of linesegments
	Rect_BG_buttons BG_create_array_linesegments(420, 460, 240, 40, 5);
	User_texts create_array_linesegments_text("Comic_Sans_MS.TTF", "array of linesegments", 420, 467, 20);

	/*СВОЙСТВА ОКРУЖНОСТИ*/
	//Открыть меню обработки свойств: MOVE AND CHANGE->obj_circle
	Rect_BG_buttons BG_obj_circle(220, 229, 140, 40, 5);
	User_texts obj_circle_text("Comic_Sans_MS.TTF", "  obj_circle", 225, 238, 21);
	//Сдвинуть случайным образом по x и по y из диапазона [-50;50]:obj_circle-> circle_random_move
	Rect_BG_buttons BG_RandomMove_obj_circle(5, 455, 230, 40, 5);
	User_texts RandomMove_obj_circle_text("Comic_Sans_MS.TTF", "circle_random_move", 10, 460, 20);
	//Движение по клавишам WASD элементов: obj_circle -> circle_user_move
	Rect_BG_buttons BG_UserMove_obj_circle(250, 455, 230, 40, 5);
	User_texts UserMove_obj_circle_text("Comic_Sans_MS.TTF", "circle_user_move", 270, 460, 20);
	//Увеличить или уменьшить радиус: obj_circle -> circle_change_radius:\n(q) - increase\n(e) - decrease
	Rect_BG_buttons BG_ChangeRadius_obj_circle(5, 510, 300, 80, 5);
	User_texts ChangeRadius_obj_circle_text("Comic_Sans_MS.TTF", "circle_change_radius:\n(q) - increase\n(e) - decrease", 10, 510, 18);
	//Удалить объект: obj_circle -> delete
	Rect_BG_buttons BG_delete_obj_circle(495, 455, 160, 40, 5);
	User_texts delete_obj_circle_text("Comic_Sans_MS.TTF", "delete", 530, 460, 25);

	/*СВОЙСТВА ПРЯМОУГОЛЬНИКА*/
	//Открыть меню обработки свойств: MOVE AND CHANGE->obj_rectangle
	Rect_BG_buttons BG_obj_rect(375, 229, 160, 40, 5);
	User_texts obj_rect_text("Comic_Sans_MS.TTF", "obj_rectangle", 380, 238, 21);
	Rect_BG_buttons BG_RandomMove_obj_rect(5, 455, 230, 40, 5);
	//Сдвинуть случайным образом по x и по y из диапазона [-50;50]:obj_rectangle-> rect_random_move
	User_texts RandomMove_obj_rect_text("Comic_Sans_MS.TTF", "rect_random_move", 10, 460, 20);
	//Движение по клавишам WASD элементов: obj_rectangle -> rect_user_move
	Rect_BG_buttons BG_UserMove_obj_rect(250, 455, 230, 40, 5);
	User_texts UserMove_obj_rect_text("Comic_Sans_MS.TTF", "rect_user_move", 270, 460, 20);
	//Увеличить или уменьшить ширину: obj_circle -> circle_change_radius:\n(q) - increase\n(e) - decrease
	Rect_BG_buttons BG_ChangeWidthLength_obj_rectangle(5, 510, 300, 160, 5);
	User_texts ChangeWidthLength_obj_rectangle_text("Comic_Sans_MS.TTF",
		"rectangle_change_dimensions:\n(z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width", 10, 510, 18);
	//Удалить объект: obj_rectangle -> delete
	Rect_BG_buttons BG_delete_obj_rectangle(495, 455, 160, 40, 5);
	User_texts delete_obj_rectangle_text("Comic_Sans_MS.TTF", "delete", 530, 460, 25);


	/*СВОЙСТВА ОТРЕЗКА*/
	//Открыть меню обработки свойств: MOVE AND CHANGE->obj_linesegment
	Rect_BG_buttons BG_obj_linesegment(220, 280, 185, 40, 5);
	User_texts obj_linesegment_text("Comic_Sans_MS.TTF", "obj_linesegment", 225, 290, 21);
	//Сдвинуть случайным образом по x и по y из диапазона [-50;50]:obj_linesegment-> line_random_move
	Rect_BG_buttons BG_RandomMove_obj_linesegment(5, 455, 230, 40, 5);
	User_texts RandomMove_obj_linesegment_text("Comic_Sans_MS.TTF", "line_random_move", 10, 460, 20);
	//Движение по клавишам WASD элементов: obj_linesegment -> line_user_move
	Rect_BG_buttons BG_UserMove_obj_linesegment(250, 455, 230, 40, 5);
	User_texts UserMove_obj_linesegment_text("Comic_Sans_MS.TTF", "line_user_move", 270, 460, 20);
	//Увеличить или уменьшить длину отрезка, повернуть отрезок: obj_linesegment -> linesegment_change_length:\n(f) - increase\n(g) - decrease\n(h) - rotate
	Rect_BG_buttons BG_ChangeDimensions_obj_linesegment(5, 510, 300, 160, 5);
	User_texts ChangeDimensions_obj_linesegment_text("Comic_Sans_MS.TTF",
		"linesegment_change_length:\n(b) - increase\n(n) - decrease\nlinesegment_change_rotate:\n(f) - rotate clockwise\n(g) - rotate counterclockwise", 10, 510, 18);
	//Удалить объект: obj_linesegment -> delete
	Rect_BG_buttons BG_delete_obj_linesegment(495, 455, 160, 40, 5);
	User_texts delete_obj_linesegment_text("Comic_Sans_MS.TTF", "delete", 530, 460, 25);

	/*СВОЙСТВА МАССИВА ОКРУЖНОСТЕЙ*/
	//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]:array_of_circles -> random move(circles)
	Rect_BG_buttons BG_RandomMove_array_circles(5, 520, 175, 40, 5);
	User_texts RandomMove_array_circles_text("Comic_Sans_MS.TTF", "random move(circles)", 10, 530, 15);
	//Движение по клавишам WASD элементов: array of circles -> user move(circles) 
	Rect_BG_buttons BG_UserMove_array_circles(5, 580, 175, 40, 5);
	User_texts UserMove_array_circles_text("Comic_Sans_MS.TTF", "user move(circles)", 10, 590, 17);
	//Удалить последний элемент: array of circles -> delete_last circle
	Rect_BG_buttons BG_delete_last_elem_array_circles(5, 640, 175, 40, 5);
	User_texts delete_last_elem_array_circles_text("Comic_Sans_MS.TTF", "delete_last circle", 10, 650, 17);
	//Удалить все элементы: array of circles -> delete all circles
	Rect_BG_buttons BG_delete_all_circles(5, 700, 175, 40, 5);
	User_texts delete_all_circles_text("Comic_Sans_MS.TTF", "delete all circles", 10, 710, 17);
	//Увеличение или уменьшение радиуса: array of circles -> (q) - increase radius\n(e) - decrease radius
	User_texts ChangeRadius_array_circles_text("Comic_Sans_MS.TTF", "(q) - increase radius\n(e) - decrease radius", 5, 760, 15);

	/*СВОЙСТВА МАССИВА ПРЯМОУГОЛЬНИКОВ*/
	//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]:array_of_rectangles -> random move(rectangles)
	Rect_BG_buttons BG_RandomMove_array_rectangles(195, 520, 210, 40, 5);
	User_texts RandomMove_array_rectangles_text("Comic_Sans_MS.TTF", "random move(rectangles)", 200, 530, 15);
	//Движение по клавишам WASD элементов: array of rectangles -> user move(rectangles) 
	Rect_BG_buttons BG_UserMove_array_rectangles(195, 580, 210, 40, 5);
	User_texts UserMove_array_rectangles_text("Comic_Sans_MS.TTF", "user move(reactangles)", 200, 590, 17);
	//Удалить последний элемент: array of rectangles -> delete_last rectangle
	Rect_BG_buttons BG_delete_last_elem_array_rectangles(195, 640, 210, 40, 5);
	User_texts delete_last_elem_array_rectangles_text("Comic_Sans_MS.TTF", "delete_last rectangle", 200, 650, 17);
	//Удалить все элементы: array of rectangles -> delete all rectangles
	Rect_BG_buttons BG_delete_all_rectangles(195, 700, 210, 40, 5);
	User_texts delete_all_rectangles_text("Comic_Sans_MS.TTF", "delete all rectangles", 200, 710, 17);
	//Изменение размера элементов массива прямоугольников: array of rectangles -> (z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width
	User_texts ChangeDimensions_array_rectangles_text("Comic_Sans_MS.TTF",
		"(z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width", 200, 760, 15);

	/*СВОЙСТВА МАССИВА ОТРЕЗКОВ*/
	//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]: array_of_linesegments -> random move(linesegments)
	Rect_BG_buttons BG_RandomMove_array_linesegments(420, 520, 240, 40, 5);
	User_texts RandomMove_array_linesegments_text("Comic_Sans_MS.TTF", "random move(linesegments)", 425, 530, 15);
	//Движение по клавишам WASD элементов: array of linesegments -> user move(linesegments)
	Rect_BG_buttons BG_UserMove_array_linesegments(420, 580, 240, 40, 5);
	User_texts UserMove_array_linesegments_text("Comic_Sans_MS.TTF", "user move(linesegments)", 425, 590, 17);
	//Удалить последний элемент: array of linesegments -> delete_last linesegment
	Rect_BG_buttons BG_delete_last_elem_array_linesegments(420, 640, 240, 40, 5);
	User_texts delete_last_elem_array_linesegments_text("Comic_Sans_MS.TTF", "delete_last linesegment", 425, 650, 17);
	//Удалить все элементы: array of linesegments -> delete all linesegments
	Rect_BG_buttons BG_delete_all_linesegments(420, 700, 240, 40, 5);
	User_texts delete_all_linesegments_text("Comic_Sans_MS.TTF", "delete all linesegments", 425, 710, 17);
	//Изменение размера элементов массива прямоугольников: array of rectangles -> (z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width
	User_texts ChangeDimensions_array_linesegments_text("Comic_Sans_MS.TTF",
		"linesegment_change_length:\n(b) - increase\n(n) - decrease\nlinesegment_change_rotate:\n(f) - rotate clockwise\n(g) - rotate counterclockwise", 425, 760, 15);

	//Переход на следующую или предыдущую страницу графических примитивов с последующей обработкой
	Rect_BG_buttons BG_next(600, 5, 100, 85, 5);
	User_texts next_text("Comic_Sans_MS.TTF", "NEXT", 605, 30, 30);
	Rect_BG_buttons BG_back(495, 5, 100, 85, 5);
	User_texts back_text("Comic_Sans_MS.TTF", "BACK", 500, 30, 30);

	//Привзяка ГПСЧ к календарному времени (случайные последовательности случайных чисел из диапазона)
	srand(static_cast<unsigned int>(time(0)));

	//Организация перехода окна между дополнительными меню
	int extra_menu{ 0 };
	//Учет явного нажатия кнопок: CREATE, MOVE_AND_CHANGE (для разных extra_menu)
	bool menu_create_0{ false }, menu_move_and_change_0{ false };
	//ЕДИНИЧНЫЕ ОБЪЕКТЫ
	//Учет явного нажатия кнопок CREATE ->: circle, rectangle, linesegment
	bool circle_show{ false }, rect_show{ false }, linesegment_show{ false };
	//Учет явного нажатия кнопок MOVE AND CHANGE ->: obj_circle, obj_rectangle, obj_;inesegment
	bool submenu_obj_circle{ false }, submenu_obj_rect{ false }, submenu_obj_linesegment{ false };
	//Учет явного нажатия кнопок obj_circle -> circle_random_move, obj_rectangle -> rect_user_move, obj_linesegment -> line_user_move 
	bool circle_user_move{ false }, rect_user_move{ false }, linesegment_user_move{ false };
	//Учет явного нажатия кнопок у obj_circle, obj_rectangle, obj_linesegment изменения размеров
	bool circle_change_radius{ false }, rectangle_change_dimensions{ false }, linesegment_change_dimensions{ false };
	//МАССИВЫ
	//Явное нажатие кнопки CREATE -> create arrays of graphics primitives, create_15_objs
	bool submenu_create_arrays_0{ false }, create_15_objs{ false };
	//Создание одного/нескольких элементов массива с помощью одной переменной
	int mass_or_single{ONE_OBJ};
	//Явное нажатие кнопок create arrays of graphics primitives ->: array of circles, array of rectangles, array of linesegments
	bool array_circles_show{ false }, array_rectangles_show{ false }, array_linesegments_show{ false };
	//Явное нажатие кнопок array of circles -> user move(circles), array of rectangles -> user move(rectangles)
	bool array_circles_user_move{ false }, array_rectangles_user_move{ false }, array_linesegments_user_move{ false };

	while (window.isOpen())
	{
		/*ПОКАДРОВАЯ ОБРАБОТКА ЦВЕТОВ СОЗДАННЫХ ОБЪЕКТОВ НА ОКНЕ*/
		//Меню
		//Текст IMAGE
		image_text.m_setFillColor(111, 206, 253);
		//Кнопка CREATE
		BG_create.m_setDefaultColor();
		create_text.m_setDefaultColor();
		//Кнопка MOVE AND CHANGE
		BG_move_and_change.m_setDefaultColor();
		move_and_change_text.m_setDefaultColor();
		//Кнопка EXIT
		BG_exit.m_setDefaultColor();
		exit_text.m_setDefaultColor();
		//Кнопка NEXT
		BG_next.m_setDefaultColor();
		next_text.m_setDefaultColor();
		//Кнопка BACK
		BG_back.m_setDefaultColor();
		back_text.m_setDefaultColor();

		//Подменю
		BG_submenu_obj.m_setFillColor(34, 177, 76);

		//ПОДМЕНЮ CREATE
		//CREATE -> circle
		BG_circle.m_setFillColor(195, 195, 195); //Т.к. в классе конструкторный цвет - как у MENU и IMAGE
		circle_text.m_setDefaultColor();
		//CREATE -> rectangle
		BG_rect.m_setFillColor(195, 195, 195);
		rect_text.m_setDefaultColor();
		//CREATE -> linesegment
		BG_linesegment.m_setFillColor(195, 195, 195);
		linesegment_text.m_setDefaultColor();
		//CREATE -> create arrays of graphics primitives
		BG_create_arrays.m_setFillColor(195, 195, 195);
		create_arrays_text.m_setDefaultColor();
		//create arrays of graphics primitives -> array of circles
		BG_create_array_circles.m_setFillColor(195, 195, 195);
		create_array_circles_text.m_setDefaultColor();
		//create arrays of graphics primitives -> array of rectangles
		BG_create_array_rectangles.m_setFillColor(195, 195, 195);
		create_array_rectangles_text.m_setDefaultColor();
		//create arrays of graphics primitives -> array of linesegments
		BG_create_array_linesegments.m_setFillColor(195, 195, 195);
		create_array_linesegments_text.m_setDefaultColor();

		//ОБЪЕКТ ОКРУЖНОСТИ
		//MOVE AND CHANGE -> obj_circle
		BG_obj_circle.m_setFillColor(195, 195, 195);
		obj_circle_text.m_setDefaultColor();
		//obj_circle -> circle_random_move
		BG_RandomMove_obj_circle.m_setDefaultColor();
		RandomMove_obj_circle_text.m_setDefaultColor();
		//obj_circle -> delete
		BG_delete_obj_circle.m_setDefaultColor();
		delete_obj_circle_text.m_setDefaultColor();

		//ОБЪЕКТ ПРЯМОУГОЛЬНИКА
		//MOVE AND CHANGE -> obj_rectangle
		BG_obj_rect.m_setFillColor(195, 195, 195);
		obj_rect_text.m_setDefaultColor();
		//obj_rectangle -> rect_random_move
		BG_RandomMove_obj_rect.m_setDefaultColor();
		RandomMove_obj_rect_text.m_setDefaultColor();
		BG_delete_obj_rectangle.m_setDefaultColor();
		delete_obj_rectangle_text.m_setDefaultColor();

		//ОБЪЕКТ ОТРЕЗКА
		//MOVE_AND_CHANGE -> obj_linesegment
		BG_obj_linesegment.m_setFillColor(195, 195, 195);
		obj_linesegment_text.m_setDefaultColor();
		//obj_linesegment -> line_random_move
		BG_RandomMove_obj_linesegment.m_setDefaultColor();
		RandomMove_obj_linesegment_text.m_setDefaultColor();
		//obj_linesegment -> delete
		BG_delete_obj_linesegment.m_setDefaultColor();
		delete_obj_linesegment_text.m_setDefaultColor();

		//МАССИВ ОКРУЖНОСТЕЙ
		//array of circles -> random move(circles)
		BG_RandomMove_array_circles.m_setFillColor(195, 195, 195);
		RandomMove_array_circles_text.m_setDefaultColor();
		//array of circles -> delete_last circle
		BG_delete_last_elem_array_circles.m_setFillColor(195, 195, 195);
		delete_last_elem_array_circles_text.m_setDefaultColor();
		//array of circles -> delete all circles
		BG_delete_all_circles.m_setFillColor(195, 195, 195);
		delete_all_circles_text.m_setDefaultColor();

		//МАССИВ ПРЯМОУГОЛЬНИКОВ
		//array of rectangles -> random move(rectangles)
		BG_RandomMove_array_rectangles.m_setFillColor(195, 195, 195);
		RandomMove_array_rectangles_text.m_setDefaultColor();
		//array of rectangles -> delete_last rectangle
		BG_delete_last_elem_array_rectangles.m_setFillColor(195, 195, 195);
		delete_last_elem_array_rectangles_text.m_setDefaultColor();
		//array of rectangles -> delete all rectangles
		BG_delete_all_rectangles.m_setFillColor(195, 195, 195);
		delete_all_rectangles_text.m_setDefaultColor();

		//МАССИВ ОТРЕЗКОВ
		//array of linesegments -> random move(linesegments)
		BG_RandomMove_array_linesegments.m_setFillColor(195, 195, 195);
		RandomMove_array_linesegments_text.m_setDefaultColor();
		//array of linesegments -> delete_lest_linesegment
		BG_delete_last_elem_array_linesegments.m_setFillColor(195, 195, 195);
		delete_last_elem_array_linesegments_text.m_setDefaultColor();
		//array of linesegments -> delete all linesegments
		BG_delete_all_linesegments.m_setFillColor(195, 195, 195);
		delete_all_linesegments_text.m_setDefaultColor();

		/*ПОКАДРОВАЯ ОБРАБОТКА ЦВЕТОВ СОЗДАННЫХ ОБЪЕКТОВ НА ОКНЕ (при определенном условии)*/
		//ОБЪЕКТ ОКРУЖНОСТИ
		//Нажата кнопка obj_circle -> circle_user_move
		if (!circle_user_move)
		{
			BG_UserMove_obj_circle.m_setDefaultColor();
			UserMove_obj_circle_text.m_setDefaultColor();
		}
		//Нажата кнопка obj_circle -> circle_change_radius:\n(q) - increase\n(e) - decrease
		if (!circle_change_radius)
		{
			BG_ChangeRadius_obj_circle.m_setDefaultColor();
			ChangeRadius_obj_circle_text.m_setDefaultColor();
		}

		//ОБЪЕКТ ПРЯМОУГОЛЬНИКА
		//Нажата кнопка obj_rectangle -> rect_user_move
		if (!rect_user_move)
		{
			BG_UserMove_obj_rect.m_setDefaultColor();
			UserMove_obj_rect_text.m_setDefaultColor();
		}
		//Нажата кнопка obj_rectangle -> rectangle_change_dimensions:\n(z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width
		if (!rectangle_change_dimensions)
		{
			BG_ChangeWidthLength_obj_rectangle.m_setDefaultColor();
			ChangeWidthLength_obj_rectangle_text.m_setDefaultColor();
		}

		//ОБЪЕКТ ОТРЕЗКА
		if (!linesegment_user_move)
		{
			BG_UserMove_obj_linesegment.m_setDefaultColor();
			UserMove_obj_linesegment_text.m_setDefaultColor();
		}
		//Нажата кнопка obj_linesegment -> linesegment_change_length:\n(f) - increase\n(g) - decrease\n(h) - rotate
		if (!linesegment_change_dimensions)
		{
			BG_ChangeDimensions_obj_linesegment.m_setDefaultColor();
			ChangeDimensions_obj_linesegment_text.m_setDefaultColor();
		}

		/*МАССИВ ОБЪЕКТОВ КЛАССА*/
		if (!create_15_objs)
		{
			BG_create_15_objs.m_setDefaultColor();
			create_15_objs_text.m_setDefaultColor();
		}
		//МАССИВ ОКРУЖНОСТЕЙ
		//Нажата кнопка array of circle -> user move(circles)
		if (!array_circles_user_move)
		{
			BG_UserMove_array_circles.m_setFillColor(195, 195, 195);
			UserMove_array_circles_text.m_setDefaultColor();
		}
		//МАССИВ ПРЯМОУГОЛЬНИКОВ
		if (!array_rectangles_user_move)
		{
			BG_UserMove_array_rectangles.m_setFillColor(195, 195, 195);
			UserMove_array_rectangles_text.m_setDefaultColor();
		}

		//МАССИВ ОТРЕЗКОВ
		if (!array_linesegments_user_move)
		{
			BG_UserMove_array_linesegments.m_setFillColor(195, 195, 195);
			UserMove_array_linesegments_text.m_setDefaultColor();
		}

		/*БУЛЕВЫЕ ПЕРЕМЕННЫЕ ДЛЯ ПОЛОЖЕНИЯ КУРСОРА НА КНОПКЕ*/
		//Кнопки меню: NEXT, BACK, CREATE, MOVE AND CHANGE, EXIT
		bool stage_next{ false }, stage_back{ false }, stage_create{ false }, stage_move_and_change{ false }, stage_exit{ false };
		//ОБЪЕКТ ОКРУЖНОСТИ
		bool stage_circle_create{ false }; //Кнопка CREATE -> circle
		bool stage_obj_circle{ false };//Кнопка MOVE AND CHANGE -> obj_circle
		//Кнопки obj_circle ->: circle_random_move, circle_user_move, circle_change_radius, delete
		bool stage_circle_random_move{ false }, stage_circle_user_move{ false }, stage_circle_change_radius{ false }, stage_delete_obj_circle{ false };

		//ОБЪЕКТ ПРЯМОУГОЛЬНИКА
		bool stage_rect_create{ false };//Кнопка CREATE -> rectangle
		bool stage_obj_rect{ false };//MOVE AND CHANGE -> obj_rectangle
		//Кнопки obj_rectangle ->: rect_random_move, rect_user_move, rectangle_change_dimensions, delete
		bool stage_rect_random_move{ false }, stage_rect_user_move{ false }, stage_rect_change_dimensions{ false }, stage_delete_obj_rect{ false };

		//ОБЪЕКТ ОТРЕЗКА
		bool stage_linesegment_create{ false };//Кнопка CREATE -> linesegment
		bool stage_obj_linesegment{ false };//Кнопка MOVE AND CHANGE -> obj_linesegment
		//Кнопки obj_linesegment ->: line_random_move, line_user_move, linesegment_change_dimensions, delete
		bool stage_linesegment_random_move{ false }, stage_linesegment_user_move{ false }, stage_linesegment_change_dimensions{ false }, stage_delete_obj_linesegment{ false };

		//МАССИВЫ
		bool stage_create_arrays{ false }; //Кнопка CREATE -> create arrays of graphics primitives
		bool stage_create_15_objs{ false };//Кнопка create arrays of graphics primitives -> create_15_objs
		//Кнопки arrays of graphics primitives ->: array of circles, array of rectangles, array of linesegments
		bool stage_create_array_circles{ false }, stage_create_array_rectangles(false), stage_create_array_linesegments{ false };
		//МАССИВ ОКРУЖНОСТЕЙ. Кнопки array of circles ->: random move(circles), user move (circles), delete_last circle, delete all circles
		bool stage_RandomMove_array_circles{ false }, stage_user_move_array_circles{ false }, stage_delete_last_elem_array_circles{ false },
			stage_delete_all_circles{ false };
		//МАССИВ ПРЯМОУГОЛЬНИКОВ. Кнопки array of rectangles ->: random move(rectangles), user move(rectangles), delete_last rectangle, delete all rectangles
		bool stage_RandomMove_array_rectangles{ false }, stage_user_move_array_rectangles{ false }, stage_delete_last_elem_array_rectangles{ false },
			stage_delete_all_rectangles{ false };
		//МАССИВ ОТРЕЗКОВ. Кнопки array of linesegments ->: random move(linesegments), user move(linesegments), delete_last linesegment, delete all linesegments
		bool stage_RandomMove_array_linesegments{ false }, stage_user_move_array_linesegments{ false }, stage_delete_last_elem_array_linesegments{ false },
			stage_delete_all_linesegments{ false };

		/*ОКРАШИВАНИЕ КНОПОК ПРИ НАВЕДЕНИИ КУРСОРА МЫШИ (с изменением значения соответствующих переменных*/
		//МЕНЮ
		if (sf::IntRect(600, 5, 100, 85).contains(sf::Mouse::getPosition(window)))//NEXT
		{
			BG_next.m_setActiveColor();
			next_text.m_setActiveColor();
			stage_next = true;
		}

		if (sf::IntRect(495, 5, 100, 85).contains(sf::Mouse::getPosition(window)))//BACK
		{
			BG_back.m_setActiveColor();
			back_text.m_setActiveColor();
			stage_back = true;
		}

		if (sf::IntRect(5, 96, 200, 120).contains(sf::Mouse::getPosition(window)))//CREATE
		{
			BG_create.m_setActiveColor();
			create_text.m_setActiveColor();
			stage_create = true;
		}

		if (sf::IntRect(5, 229, 200, 120).contains(sf::Mouse::getPosition(window)))//MOVE AND CHANGE
		{
			BG_move_and_change.m_setActiveColor();
			move_and_change_text.m_setActiveColor();
			stage_move_and_change = true;
		}
		if (sf::IntRect(5, 840, 160, 50).contains(sf::Mouse::getPosition(window)))//EXIT
		{
			BG_exit.m_setActiveColor();
			exit_text.m_setActiveColor();
			stage_exit = true;
		}

		if (extra_menu == 0)
		{
			//ОБЪЕКТ ОКРУЖНОСТИ
			if (sf::IntRect(220, 97, 140, 40).contains(sf::Mouse::getPosition(window)) && menu_create_0)//CREATE -> circle
			{
				BG_circle.m_setActiveColor();
				circle_text.m_setActiveColor();
				stage_circle_create = true;
			}

			if (sf::IntRect(220, 229, 140, 40).contains(sf::Mouse::getPosition(window)) && menu_move_and_change_0)//MOVE AND CHANGE -> obj_circle
			{
				BG_obj_circle.m_setActiveColor();
				obj_circle_text.m_setActiveColor();
				stage_obj_circle = true;
			}

			if (sf::IntRect(5, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_circle && menu_move_and_change_0)//obj_circle -> dircle_random_move
			{
				BG_RandomMove_obj_circle.m_setActiveColor();
				RandomMove_obj_circle_text.m_setActiveColor();
				stage_circle_random_move = true;
			}

			if (sf::IntRect(250, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_circle && menu_move_and_change_0)//obj_circle -> circle_user_move
			{
				BG_UserMove_obj_circle.m_setActiveColor();
				UserMove_obj_circle_text.m_setActiveColor();
				stage_circle_user_move = true;
			}

			if (sf::IntRect(5, 510, 300, 80).contains(sf::Mouse::getPosition(window)) && submenu_obj_circle && menu_move_and_change_0)//obj_circle -> circle_change_radius:\n(q) - increase\n(e) - decrease
			{
				BG_ChangeRadius_obj_circle.m_setActiveColor();
				ChangeRadius_obj_circle_text.m_setActiveColor();
				stage_circle_change_radius = true;
			}
			if (sf::IntRect(495, 455, 160, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_circle && menu_move_and_change_0)//obj_circle -> delete
			{
				BG_delete_obj_circle.m_setActiveColor();
				delete_obj_circle_text.m_setActiveColor();
				stage_delete_obj_circle = true;
			}

			//ОБЪЕКТ ПРЯМОУГОЛЬНИКА
			if (sf::IntRect(375, 97, 140, 40).contains(sf::Mouse::getPosition(window)) && menu_create_0)//CREATE -> rectangle
			{
				BG_rect.m_setActiveColor();
				rect_text.m_setActiveColor();
				stage_rect_create = true;
			}
			if (sf::IntRect(375, 229, 160, 40).contains(sf::Mouse::getPosition(window)) && menu_move_and_change_0)//MOVE AND CHANGE -> obj_rectangle
			{
				BG_obj_rect.m_setActiveColor();
				obj_rect_text.m_setActiveColor();
				stage_obj_rect = true;
			}

			if (sf::IntRect(5, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_rect && menu_move_and_change_0)//obj_rectangle -> rect_random_move
			{
				BG_RandomMove_obj_rect.m_setActiveColor();
				RandomMove_obj_rect_text.m_setActiveColor();
				stage_rect_random_move = true;
			}

			if (sf::IntRect(250, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_rect && menu_move_and_change_0)//obj_rectangle -> rect_user_move
			{
				BG_UserMove_obj_rect.m_setActiveColor();
				UserMove_obj_rect_text.m_setActiveColor();
				stage_rect_user_move = true;
			}

			if (sf::IntRect(5, 510, 300, 160).contains(sf::Mouse::getPosition(window)) && submenu_obj_rect && menu_move_and_change_0)
			{
				BG_ChangeWidthLength_obj_rectangle.m_setActiveColor();
				ChangeWidthLength_obj_rectangle_text.m_setActiveColor();
				stage_rect_change_dimensions = true;
			}
			if (sf::IntRect(495, 455, 160, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_rect && menu_move_and_change_0)
			{
				BG_delete_obj_rectangle.m_setActiveColor();
				delete_obj_rectangle_text.m_setActiveColor();
				stage_delete_obj_rect = true;
			}

			//ОБЪЕКТ ОТРЕЗКА
			if (sf::IntRect(529, 97, 165, 40).contains(sf::Mouse::getPosition(window)) && menu_create_0)//CREATE -> linesegment
			{
				BG_linesegment.m_setActiveColor();
				linesegment_text.m_setActiveColor();
				stage_linesegment_create = true;
			}
			if (sf::IntRect(220, 280, 185, 40).contains(sf::Mouse::getPosition(window)) && menu_move_and_change_0)//MOVE AND CHANGE -> obj_linesegment
			{
				BG_obj_linesegment.m_setActiveColor();
				obj_linesegment_text.m_setActiveColor();
				stage_obj_linesegment = true;
			}

			if (sf::IntRect(5, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_linesegment && menu_move_and_change_0)//obj_linesegment -> line_random_move
			{
				BG_RandomMove_obj_linesegment.m_setActiveColor();
				RandomMove_obj_linesegment_text.m_setActiveColor();
				stage_linesegment_random_move = true;
			}

			if (sf::IntRect(250, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_linesegment && menu_move_and_change_0)//obj_linesegment -> line_user_move
			{
				BG_UserMove_obj_linesegment.m_setActiveColor();
				UserMove_obj_linesegment_text.m_setActiveColor();
				stage_linesegment_user_move = true;
			}

			if (sf::IntRect(495, 455, 160, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_linesegment && menu_move_and_change_0)//obj_linesegment -> delete
			{
				BG_delete_obj_linesegment.m_setActiveColor();
				delete_obj_linesegment_text.m_setActiveColor();
				stage_delete_obj_linesegment = true;
			}

			if (sf::IntRect(5, 510, 300, 160).contains(sf::Mouse::getPosition(window)) && submenu_obj_linesegment && menu_move_and_change_0)//obj_linesegment -> linesegment_change_dimensions
			{
				BG_ChangeDimensions_obj_linesegment.m_setActiveColor();
				ChangeDimensions_obj_linesegment_text.m_setActiveColor();
				stage_linesegment_change_dimensions = true;
			}

			//МАССИВЫ
			if (sf::IntRect(220, 160, 473, 40).contains(sf::Mouse::getPosition(window)) && menu_create_0)//CREATE -> create arrays of gparhics primitives
			{
				BG_create_arrays.m_setActiveColor();
				create_arrays_text.m_setActiveColor();
				stage_create_arrays = true;
			}

			//Создание по 15 штук примитивов за нажатие кнопки
			if (sf::IntRect(500, 360, 200, 80).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)
			{
				BG_create_15_objs.m_setActiveColor();
				create_15_objs_text.m_setActiveColor();
				stage_create_15_objs = true;
			}
			//МАССИВ ОКРУЖНОСТЕЙ
			if (sf::IntRect(5, 460, 175, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//create arrays of gparhics primitives -> array of circles
			{
				BG_create_array_circles.m_setActiveColor();
				create_array_circles_text.m_setActiveColor();
				stage_create_array_circles = true;
			}

			if (sf::IntRect(5, 520, 175, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//array of circles -> random move(circles)
			{
				BG_RandomMove_array_circles.m_setActiveColor();
				RandomMove_array_circles_text.m_setActiveColor();
				stage_RandomMove_array_circles = true;
			}
			if (sf::IntRect(5, 580, 175, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//array of circles -> user move(circles)
			{
				BG_UserMove_array_circles.m_setActiveColor();
				UserMove_array_circles_text.m_setActiveColor();
				stage_user_move_array_circles = true;
			}
			if (sf::IntRect(5, 640, 175, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//array of circles -> delete_last circle
			{
				BG_delete_last_elem_array_circles.m_setActiveColor();
				delete_last_elem_array_circles_text.m_setActiveColor();
				stage_delete_last_elem_array_circles = true;
			}
			if (sf::IntRect(5, 700, 175, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//array of circles -> delete all circles
			{
				BG_delete_all_circles.m_setActiveColor();
				delete_all_circles_text.m_setActiveColor();
				stage_delete_all_circles = true;
			}

			//МАССИВ ПРЯМОУГОЛЬНИКОВ
			if (sf::IntRect(195, 460, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//create arrays of gparhics primitives -> array of rectangles
			{
				BG_create_array_rectangles.m_setActiveColor();
				create_array_rectangles_text.m_setActiveColor();
				stage_create_array_rectangles = true;
			}

			if (sf::IntRect(195, 520, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//array of rectangles -> random move(rectangles)
			{
				BG_RandomMove_array_rectangles.m_setActiveColor();
				RandomMove_array_rectangles_text.m_setActiveColor();
				stage_RandomMove_array_rectangles = true;
			}

			if (sf::IntRect(195, 580, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//array of rectangles -> user move(rectangles)
			{
				BG_UserMove_array_rectangles.m_setActiveColor();
				UserMove_array_rectangles_text.m_setActiveColor();
				stage_user_move_array_rectangles = true;
			}

			if (sf::IntRect(195, 640, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//array of rectangles -> delete_last rectangle
			{
				BG_delete_last_elem_array_rectangles.m_setActiveColor();
				delete_last_elem_array_rectangles_text.m_setActiveColor();
				stage_delete_last_elem_array_rectangles = true;
			}

			if (sf::IntRect(195, 700, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//array of rectangles -> delete all rectangles
			{
				BG_delete_all_rectangles.m_setActiveColor();
				delete_all_rectangles_text.m_setActiveColor();
				stage_delete_all_rectangles = true;
			}

			//МАССИВ ОТРЕЗКОВ
			if (sf::IntRect(420, 460, 240, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//create arrays of gparhics primitives -> array of linesegments
			{
				BG_create_array_linesegments.m_setActiveColor();
				create_array_linesegments_text.m_setActiveColor();
				stage_create_array_linesegments = true;
			}

			if (sf::IntRect(420, 520, 240, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//array of linesegments -> random move(linesegments)
			{
				BG_RandomMove_array_linesegments.m_setActiveColor();
				RandomMove_array_linesegments_text.m_setActiveColor();
				stage_RandomMove_array_linesegments = true;
			}

			if (sf::IntRect(420, 580, 240, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//array of linesegments -> user move(linesegments)
			{
				BG_UserMove_array_linesegments.m_setActiveColor();
				UserMove_array_linesegments_text.m_setActiveColor();
				stage_user_move_array_linesegments = true;
			}

			if (sf::IntRect(420, 640, 240, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//array of linesegments -> delete_last linesegment
			{
				BG_delete_last_elem_array_linesegments.m_setActiveColor();
				delete_last_elem_array_linesegments_text.m_setActiveColor();
				stage_delete_last_elem_array_linesegments = true;
			}

			if (sf::IntRect(420, 700, 240, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)//array of linesegments -> delete all linesegments
			{
				BG_delete_all_linesegments.m_setActiveColor();
				delete_all_linesegments_text.m_setActiveColor();
				stage_delete_all_linesegments = true;
			}
		}


		sf::Event event_menu_click;
		while (window.pollEvent(event_menu_click))
		{
			//Закрытие окна на "крестик"
			if (event_menu_click.type == sf::Event::Closed)
				window.close();
			//Обработчик события формы OnCreate (обработка кликов по кнопкам, т.е. работа с объектами класса)
			if (event_menu_click.type == event_menu_click.MouseButtonReleased && event_menu_click.mouseButton.button == sf::Mouse::Left)
			{
				//Нажата кнопка NEXT
				if (stage_next)
					extra_menu = 1;
				if (stage_back)
					extra_menu = 0;
				//Нажата кнопка CREATE
				if (stage_create)
				{
					if (extra_menu == 0)
						menu_create_0 = !menu_create_0;
				}
				//Нажата кнопка MOVE AND CHANGE
				if (stage_move_and_change)
				{
					if (extra_menu == 0)
						menu_move_and_change_0 = !menu_move_and_change_0;
				}
				/*ЕДИНИЧНЫЕ ОБЪЕКТЫ*/
				//ОБЪЕКТ ОКРУЖНОСТИ
				//Нажата кнопка CREATE -> circle
				if (stage_circle_create)
				{
					circle_show = true;
					if (f_ptr_obj_circle == nullptr)
					{
						f_ptr_obj_circle = new Circle();
					}
					else
					{
						float radius_circle{ getRandomNumber(10,100) };
						float x_circle{ getRandomNumber(705 + radius_circle, 1500 - radius_circle) };
						float y_circle{ getRandomNumber(95 + radius_circle, 900 - radius_circle) };
						f_ptr_obj_circle->Free(f_ptr_obj_circle);
						f_ptr_obj_circle = new Circle(x_circle, y_circle, radius_circle);
						f_ptr_obj_circle->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_circle->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_circle->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
					}
				}
				if (circle_show)
				{
					//Нажата кнопка MOVE AND CHANGE -> obj_circle
					if (stage_obj_circle)
					{
						submenu_obj_circle = !submenu_obj_circle;
						submenu_obj_rect = false;
						submenu_obj_linesegment = false;
						submenu_create_arrays_0 = false;
					}
					//Нажата кнопка circle -> circle_random_move
					if (stage_circle_random_move)
						doOffsetCircle(f_ptr_obj_circle);
					//Нажата кнопка obj_circle -> circle_user_move
					if (stage_circle_user_move)
					{
						circle_user_move = !circle_user_move;
						rect_user_move = false;
						linesegment_user_move = false;
						array_rectangles_user_move = false;
						array_linesegments_user_move = false;
					}
					//Нажата кнопка изменения радиуса obj_circle -> изменить радиус
					if (stage_circle_change_radius)
						circle_change_radius = !circle_change_radius;
					//Нажата кнопка удаления объекта окружность obj_circle -> delete
					if (stage_delete_obj_circle)
					{
						f_ptr_obj_circle->Free(f_ptr_obj_circle);
						circle_show = false;
						submenu_obj_circle = false;
						circle_user_move = false;
						circle_change_radius = false;
					}
				}

				//ОБЪЕКТ ПРЯМОУГОЛЬНИКА
				//Нажата кнопка CREATE -> rectangle
				if (stage_rect_create)
				{
					rect_show = true;
					if (f_ptr_obj_rect == nullptr)
					{
						f_ptr_obj_rect = new Rectangle();
					}
					else
					{
						float length_rect{ getRandomNumber(50, 300) };
						float width_rect{ getRandomNumber(25, 150) };
						float x_rect{ getRandomNumber(705, 1500 - length_rect) };
						float y_rect{ getRandomNumber(95, 900 - width_rect) };
						f_ptr_obj_rect->Free(f_ptr_obj_rect);
						f_ptr_obj_rect = new Rectangle(x_rect, y_rect, length_rect, width_rect);
						f_ptr_obj_rect->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_rect->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_rect->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
					}
				}
				if (rect_show)
				{
					//Нажата кнопка MOVE AND CHANGE -> obj_rectangle
					if (stage_obj_rect)
					{
						submenu_obj_rect = !submenu_obj_rect;
						submenu_obj_circle = false;
						submenu_obj_linesegment = false;
						submenu_create_arrays_0 = false;
					}
					//Нажата кнопка obj_rectangle -> rect_random_move
					if (stage_rect_random_move)
						doOffsetRect(f_ptr_obj_rect);
					//Нажата кнопка obj_rectangle -> rect_user_move
					if (stage_rect_user_move)
					{
						rect_user_move = !rect_user_move;
						circle_user_move = false;
						linesegment_user_move = false;
						array_circles_user_move = false;
						array_linesegments_user_move = false;
					}
					//Нажата кнопка изменения размеров obj_rectangle -> изменить размеры
					if (stage_rect_change_dimensions)
						rectangle_change_dimensions = !rectangle_change_dimensions;
					//Нажата кнопка удаления объекта прямоугольник obj_rectangle -> delete
					if (stage_delete_obj_rect)
					{
						f_ptr_obj_rect->Free(f_ptr_obj_rect);
						rect_show = false;
						submenu_obj_rect = false;
						rect_user_move = false;
						rectangle_change_dimensions = false;
					}
				}

				//ОБЪЕКТ ОТРЕЗКА
				//Нажата кнопка CREATE -> linesegment
				if (stage_linesegment_create)
				{
					linesegment_show = true;
					if (f_ptr_obj_linesegment == nullptr)
					{
						f_ptr_obj_linesegment = new Linesegment();
					}
					else
					{
						float length_linesegment{ getRandomNumber(100, 300) };
						float degree_linesegment{ getRandomNumber(0, 360) };
						degree_linesegment = static_cast<int>(degree_linesegment);
						float x_linesegment{};
						float y_linesegment{};
						getRandomX_Y(x_linesegment, y_linesegment, length_linesegment, degree_linesegment);
						f_ptr_obj_linesegment->Free(f_ptr_obj_linesegment);
						f_ptr_obj_linesegment = new Linesegment(x_linesegment, y_linesegment, length_linesegment, degree_linesegment);
						f_ptr_obj_linesegment->setColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_linesegment->setVisibility(static_cast<int>(getRandomNumber(150, 255)));
					}
				}
				if (linesegment_show)
				{
					//Нажата кнопка CREATE -> obj_linesegment
					if (stage_obj_linesegment)
					{
						submenu_obj_linesegment = !submenu_obj_linesegment;
						submenu_obj_circle = false;
						submenu_obj_rect = false;
						submenu_create_arrays_0 = false;
					}
					//Нажата кнопка obj_linesegment -> line_random_move
					if (stage_linesegment_random_move)
						doOffsetlinesegment(f_ptr_obj_linesegment);
					//Нажата кнопка obj_linesegment -> line_user_move
					if (stage_linesegment_user_move)
					{
						linesegment_user_move = !linesegment_user_move;
						circle_user_move = false;
						rect_user_move = false;
						array_circles_user_move = false;
						array_rectangles_user_move = false;
					}
					//Нажата кнопка obj_linesegment -> linesegment_change_dimensions
					if (stage_linesegment_change_dimensions)
						linesegment_change_dimensions = !linesegment_change_dimensions;
					//Нажата кнопка obj_linesegment -> delete
					if (stage_delete_obj_linesegment)
					{
						f_ptr_obj_linesegment->Free(f_ptr_obj_linesegment);
						linesegment_show = false;
						submenu_obj_linesegment = false;
						linesegment_user_move = false;
						linesegment_change_dimensions = false;
					}
				}

				/*МАССИВЫ ГРАФИЧЕСКИХ ПРИМИТИВОВ*/
				//Нажата кнопка CREATE -> create arrays of graphics primitives
				if (stage_create_arrays)
				{
					if (extra_menu == 0)
					{
						submenu_create_arrays_0 = !submenu_create_arrays_0;
						submenu_obj_circle = false;
						submenu_obj_rect = false;
						submenu_obj_linesegment = false;
					}
				}

				if (stage_create_15_objs)
				{
					create_15_objs = !create_15_objs;
					if (create_15_objs)
						mass_or_single = SEVERAL_OBJS;
					else
						mass_or_single = ONE_OBJ;
				}
				//МАССИВ ОКРУЖНОСТЕЙ
				//Нажата кнопка create arrays of graphics primitives -> array of circles
				if (stage_create_array_circles)
				{
					array_circles_show = true;
					for (int i{}; i < mass_or_single; i++)
					{
						Circle* ptr_new_elem_array_circles{ nullptr };
						float radius_circle{ getRandomNumber(10,100) };
						float x_circle{ getRandomNumber(705 + radius_circle, 1500 - radius_circle) };
						float y_circle{ getRandomNumber(95 + radius_circle, 900 - radius_circle) };
						ptr_new_elem_array_circles = new Circle(x_circle, y_circle, radius_circle);
						ptr_new_elem_array_circles->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_circles->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_circles->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						push_back_shapes<Circle>(array_circles, array_circles_size, ptr_new_elem_array_circles);
					}
				}
				if (array_circles_show)
				{
					if (stage_RandomMove_array_circles)
						doOffsetArrayCircles(array_circles, array_circles_size);
					if (stage_user_move_array_circles)
					{
						array_circles_user_move = !array_circles_user_move;
						rect_user_move = false;
						linesegment_user_move = false;
						array_rectangles_user_move = false;
						array_linesegments_user_move = false;
					}
					if (stage_delete_last_elem_array_circles && (array_circles_size > 0))
					{
						pop_back_shapes<Circle>(array_circles, array_circles_size);
						if (array_circles_size == 0)
						{
							array_circles_show = false;
							array_circles_user_move = false;
						}
					}
					if (stage_delete_all_circles)
					{
						int array_circles_size_temp{ array_circles_size };
						for (int i{}; i < array_circles_size_temp; i++)
							pop_back_shapes<Circle>(array_circles, array_circles_size);
						array_circles_show = false;
						array_circles_user_move = false;
					}
				}

				//МАССИВ ПРЯМОУГОЛЬНИКОВ
				//Нажата кнопка create arrays of graphics primitives -> array of rectangles
				if (stage_create_array_rectangles)
				{
					array_rectangles_show = true;
					for (int i{}; i < mass_or_single; i++)
					{
						Rectangle* ptr_new_elem_array_rectangles{ nullptr };
						float length_rect{ getRandomNumber(50, 300) };
						float width_rect{ getRandomNumber(25, 150) };
						float x_rect{ getRandomNumber(705, 1500 - length_rect) };
						float y_rect{ getRandomNumber(95, 900 - width_rect) };
						ptr_new_elem_array_rectangles = new Rectangle(x_rect, y_rect, length_rect, width_rect);
						ptr_new_elem_array_rectangles->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_rectangles->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_rectangles->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						push_back_shapes<Rectangle>(array_rectangles, array_rectangles_size, ptr_new_elem_array_rectangles);
					}
				}
				if (array_rectangles_show)
				{
					if (stage_RandomMove_array_rectangles)
						doOffsetArrayRectangles(array_rectangles, array_rectangles_size);
					if (stage_user_move_array_rectangles)
					{
						array_rectangles_user_move = !array_rectangles_user_move;
						circle_user_move = false;
						array_circles_user_move = false;
						linesegment_user_move = false;
						array_linesegments_user_move = false;
					}
					if (stage_delete_last_elem_array_rectangles && (array_rectangles_size > 0))
					{
						pop_back_shapes<Rectangle>(array_rectangles, array_rectangles_size);
						if (array_rectangles_size == 0)
						{
							array_rectangles_show = false;
							array_rectangles_user_move = false;
						}
					}
					if (stage_delete_all_rectangles)
					{
						int array_rectangles_size_temp{ array_rectangles_size };
						for (int i{}; i < array_rectangles_size_temp; i++)
							pop_back_shapes<Rectangle>(array_rectangles, array_rectangles_size);
						array_rectangles_show = false;
						array_rectangles_user_move = false;
					}
				}

				//МАССИВ ОТРЕЗКОВ
				//Нажата кнопка create arrays of graphics primitives -> array of linesegments
				if (stage_create_array_linesegments)
				{
					array_linesegments_show = true;
					for (int i{}; i < mass_or_single; i++)
					{
						Linesegment* ptr_new_elem_array_linesegments{ nullptr };
						float length_linesegment{ getRandomNumber(100, 300) };
						float degree_linesegment{ getRandomNumber(0, 360) };
						degree_linesegment = static_cast<int>(degree_linesegment);
						float x_linesegment{};
						float y_linesegment{};
						getRandomX_Y(x_linesegment, y_linesegment, length_linesegment, degree_linesegment);
						ptr_new_elem_array_linesegments = new Linesegment(x_linesegment, y_linesegment, length_linesegment, degree_linesegment);
						ptr_new_elem_array_linesegments->setColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_linesegments->setVisibility(static_cast<int>(getRandomNumber(150, 255)));
						push_back_shapes<Linesegment>(array_linesegments, array_linesegments_size, ptr_new_elem_array_linesegments);
					}
				}
				if (array_linesegments_show)
				{
					if (stage_RandomMove_array_linesegments)
					{
						for (int i{}; i < array_linesegments_size; i++)
							doOffsetArrayLinesegments(array_linesegments, i);
					}
					if (stage_user_move_array_linesegments)
					{
						array_linesegments_user_move = !array_linesegments_user_move;
						circle_user_move = false;
						array_circles_user_move = false;
						rect_user_move = false;
						array_rectangles_user_move = false;
					}
					if (stage_delete_last_elem_array_linesegments && (array_linesegments_size > 0))
					{
						pop_back_shapes<Linesegment>(array_linesegments, array_linesegments_size);
						if (array_linesegments_size == 0)
						{
							array_linesegments_show = false;
							array_linesegments_user_move = false;
						}
					}
					if (stage_delete_all_linesegments)
					{
						int array_linesegments_size_temp{ array_linesegments_size };
						for (int i{}; i < array_linesegments_size_temp; i++)
							pop_back_shapes<Linesegment>(array_linesegments, array_linesegments_size);
						array_linesegments_show = false;
						array_linesegments_user_move = false;
					}
				}

				if (!submenu_create_arrays_0)
				{
					create_15_objs = false;
					mass_or_single = ONE_OBJ;
				}
				//Нажата кнопка EXIT
				if (stage_exit)
					window.close();
			}
			else if (event_menu_click.type == sf::Event::KeyPressed)
			{
				/*ПОЛЬЗОВАТЕЛЬСКОЕ ДВИЖЕНИЕ ЕДИНИЧНЫМИ ОБЪЕКТАМИ*/
				if (circle_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W && (f_ptr_obj_circle->get_y_coordinate_base_point() - f_ptr_obj_circle->getRadius() - 10 >= 95))
						f_ptr_obj_circle->MoveTo(0, -10);
					if (event_menu_click.key.code == sf::Keyboard::A && (f_ptr_obj_circle->get_x_coordinate_base_point() - f_ptr_obj_circle->getRadius() - 10 >= 705))
						f_ptr_obj_circle->MoveTo(-10, 0);
					if (event_menu_click.key.code == sf::Keyboard::S && (f_ptr_obj_circle->get_y_coordinate_base_point() + f_ptr_obj_circle->getRadius() + 10 <= 900))
						f_ptr_obj_circle->MoveTo(0, 10);
					if (event_menu_click.key.code == sf::Keyboard::D && (f_ptr_obj_circle->get_x_coordinate_base_point() + f_ptr_obj_circle->getRadius() + 10 <= 1500))
						f_ptr_obj_circle->MoveTo(10, 0);
				}

				if (rect_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W && (f_ptr_obj_rect->get_y_coordinate_base_point() - 10 >= 95))
						f_ptr_obj_rect->MoveTo(0, -10);
					if (event_menu_click.key.code == sf::Keyboard::A && (f_ptr_obj_rect->get_x_coordinate_base_point() - 10 >= 705))
						f_ptr_obj_rect->MoveTo(-10, 0);
					if (event_menu_click.key.code == sf::Keyboard::S && (f_ptr_obj_rect->get_y_coordinate_base_point() + f_ptr_obj_rect->getWidth() + 10 <= 900))
						f_ptr_obj_rect->MoveTo(0, 10);
					if (event_menu_click.key.code == sf::Keyboard::D && (f_ptr_obj_rect->get_x_coordinate_base_point() + f_ptr_obj_rect->getLength() + 10 <= 1500))
						f_ptr_obj_rect->MoveTo(10, 0);
				}
				if (linesegment_user_move)
				{
					int degree_linesegment{ static_cast<int>(f_ptr_obj_linesegment->getDegree()) };
					float x_linesegment{ f_ptr_obj_linesegment->get_x_coordinate_base_point() };
					float y_linesegment{ f_ptr_obj_linesegment->get_y_coordinate_base_point() };
					float length_linesegment{ f_ptr_obj_linesegment->getLength() };
					float alpha_linesegment{ degree_linesegment * PI / 180 };
					if (event_menu_click.key.code == sf::Keyboard::W)
					{
						if (degree_linesegment % 360 >= 180 && degree_linesegment % 360 <= 360 || degree_linesegment % 360 >= -180 && degree_linesegment % 360 <= 0)
						{
							if ((y_linesegment + length_linesegment * sin(alpha_linesegment) - 10) >= 96)
								f_ptr_obj_linesegment->MoveTo(0, -10);
						}
						else if ((y_linesegment - 10) >= 95)
						{
							f_ptr_obj_linesegment->MoveTo(0, -10);
						}
					}
					if (event_menu_click.key.code == sf::Keyboard::A)
					{
						if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -90)
						{
							if ((x_linesegment + length_linesegment * cos(alpha_linesegment) - 10) >= 706)
								f_ptr_obj_linesegment->MoveTo(-10, 0);
						}
						else if ((x_linesegment - 10) >= 705)
						{
							f_ptr_obj_linesegment->MoveTo(-10, 0);
						}
					}
					if (event_menu_click.key.code == sf::Keyboard::S)
					{
						if (degree_linesegment % 360 >= 0 && degree_linesegment % 360 <= 180 || degree_linesegment % 360 >= -360 && degree_linesegment % 360 <= -180)
						{
							if ((y_linesegment + length_linesegment * sin(alpha_linesegment) + 10) <= 899)
								f_ptr_obj_linesegment->MoveTo(0, 10);
						}
						else if ((y_linesegment + 10) <= 900)
						{
							f_ptr_obj_linesegment->MoveTo(0, 10);
						}
					}
					if (event_menu_click.key.code == sf::Keyboard::D)
					{
						if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -90)
						{
							if ((x_linesegment + 10) <= 1500)
								f_ptr_obj_linesegment->MoveTo(10, 0);
						}
						else if ((x_linesegment + length_linesegment * cos(alpha_linesegment) + 10) <= 1499)
						{
							f_ptr_obj_linesegment->MoveTo(10, 0);
						}
					}
				}

				/*ИЗМЕНЕНИЕ РАДИУСА ОБЪЕКТА КРУГА*/
				if (circle_change_radius)
				{
					if (event_menu_click.key.code == sf::Keyboard::Q
						&& (f_ptr_obj_circle->get_y_coordinate_base_point() + f_ptr_obj_circle->getRadius() + 2 <= 900)
						&& (f_ptr_obj_circle->get_x_coordinate_base_point() + f_ptr_obj_circle->getRadius() + 2 <= 1500)
						&& (f_ptr_obj_circle->get_y_coordinate_base_point() - f_ptr_obj_circle->getRadius() - 2 >= 95)
						&& (f_ptr_obj_circle->get_x_coordinate_base_point() - f_ptr_obj_circle->getRadius() - 2 >= 705))
					{
						f_ptr_obj_circle->changeRadius(2);
					}
					if (event_menu_click.key.code == sf::Keyboard::E && (f_ptr_obj_circle->getRadius() >= 10))
						f_ptr_obj_circle->changeRadius(-2);
				}

				/*ИЗМЕНЕНИЕ РАЗМЕРОВ ОБЪЕКТА ПРЯМОУГОЛЬНИКА*/
				if (rectangle_change_dimensions)
				{
					if (event_menu_click.key.code == sf::Keyboard::Z && (f_ptr_obj_rect->get_x_coordinate_base_point() + f_ptr_obj_rect->getLength() + 5 <= 1500))
						f_ptr_obj_rect->changeDimensions(5, 0);
					if (event_menu_click.key.code == sf::Keyboard::X && (f_ptr_obj_rect->getLength() >= 50))
						f_ptr_obj_rect->changeDimensions(-5, 0);
					if (event_menu_click.key.code == sf::Keyboard::C && (f_ptr_obj_rect->get_y_coordinate_base_point() + f_ptr_obj_rect->getWidth() + 5 <= 900))
						f_ptr_obj_rect->changeDimensions(0, 5);
					if (event_menu_click.key.code == sf::Keyboard::V && (f_ptr_obj_rect->getWidth() >= 25))
						f_ptr_obj_rect->changeDimensions(0, -5);
				}

				/*ИЗМЕНЕНИЕ РАЗМЕРОВ И ПОВОРОТ ОБЪЕКТА ОТРЕЗКА*/
				if (linesegment_change_dimensions)
				{
					int degree_linesegment{ static_cast<int>(f_ptr_obj_linesegment->getDegree()) };
					float x_linesegment{ f_ptr_obj_linesegment->get_x_coordinate_base_point() };
					float y_linesegment{ f_ptr_obj_linesegment->get_y_coordinate_base_point() };
					float length_linesegment{ f_ptr_obj_linesegment->getLength() };
					float alpha_linesegment{ degree_linesegment * PI / 180 };
					if (event_menu_click.key.code == sf::Keyboard::B)
					{
						if ((x_linesegment + length_linesegment * cos(alpha_linesegment) + 1) <= 1500 &&
							(x_linesegment + length_linesegment * cos(alpha_linesegment) + 1) >= 705 &&
							(y_linesegment + length_linesegment * sin(alpha_linesegment) + 1) <= 900 &&
							(y_linesegment + length_linesegment * sin(alpha_linesegment) + 1) >= 95)
						{
							f_ptr_obj_linesegment->changeLength(1);
						}
					}
					if (event_menu_click.key.code == sf::Keyboard::N)
					{
						if (length_linesegment - 1 >= 50)
						{
							f_ptr_obj_linesegment->changeLength(-1);
						}
					}
					if (event_menu_click.key.code == sf::Keyboard::F)
					{
						if ((x_linesegment + length_linesegment * cos(alpha_linesegment + PI / 180)) <= 1500 &&
							(x_linesegment + length_linesegment * cos(alpha_linesegment + PI / 180)) >= 705 &&
							(y_linesegment + length_linesegment * sin(alpha_linesegment + PI / 180)) <= 900 &&
							(y_linesegment + length_linesegment * sin(alpha_linesegment + PI / 180)) >= 95)
						{
							f_ptr_obj_linesegment->changeDegree(1);
						}
					}
					if (event_menu_click.key.code == sf::Keyboard::G)
					{
						if ((x_linesegment + length_linesegment * cos(alpha_linesegment - PI / 180)) <= 1500 &&
							(x_linesegment + length_linesegment * cos(alpha_linesegment - PI / 180)) >= 705 &&
							(y_linesegment + length_linesegment * sin(alpha_linesegment - PI / 180)) <= 900 &&
							(y_linesegment + length_linesegment * sin(alpha_linesegment - PI / 180)) >= 95)
						{
							f_ptr_obj_linesegment->changeDegree(-1);
						}
					}
				}


				/*МАССИВ ОБЪЕКТОВ*/
				//МАССИВ КРУГОВ
				//Пользовательское движение элементов
				if (array_circles_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W)
						doUserMoveArrayCirclesW(array_circles, array_circles_size);
					if (event_menu_click.key.code == sf::Keyboard::A)
						doUserMoveArrayCirclesA(array_circles, array_circles_size);
					if (event_menu_click.key.code == sf::Keyboard::S)
						doUserMoveArrayCirclesS(array_circles, array_circles_size);
					if (event_menu_click.key.code == sf::Keyboard::D)
						doUserMoveArrayCirclesD(array_circles, array_circles_size);
				}
				//Изменение радиуса элементов
				if (array_circles_show)
				{
					if (event_menu_click.key.code == sf::Keyboard::Q)
						array_circles_RadiusIncrease(array_circles, array_circles_size);
					if (event_menu_click.key.code == sf::Keyboard::E)
						array_circles_RadiusDecrease(array_circles, array_circles_size);
				}

				//МАССИВ ПРЯМОУГОЛЬНИКОВ
				//Пользовательское движение элементов
				if (array_rectangles_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W)
						doUserMoveArrayRectanglesW(array_rectangles, array_rectangles_size);
					if (event_menu_click.key.code == sf::Keyboard::A)
						doUserMoveArrayRectanglesA(array_rectangles, array_rectangles_size);
					if (event_menu_click.key.code == sf::Keyboard::S)
						doUserMoveArrayRectanglesS(array_rectangles, array_rectangles_size);
					if (event_menu_click.key.code == sf::Keyboard::D)
						doUserMoveArrayRectanglesD(array_rectangles, array_rectangles_size);
				}
				//Изменение размеров элементов
				if (array_rectangles_show)
				{
					if (event_menu_click.key.code == sf::Keyboard::Z)
						array_rectangles_ChangeDimensions(array_rectangles, array_rectangles_size, 5, 0);
					if (event_menu_click.key.code == sf::Keyboard::X)
						array_rectangles_ChangeDimensions(array_rectangles, array_rectangles_size, -5, 0);
					if (event_menu_click.key.code == sf::Keyboard::C)
						array_rectangles_ChangeDimensions(array_rectangles, array_rectangles_size, 0, 5);
					if (event_menu_click.key.code == sf::Keyboard::V)
						array_rectangles_ChangeDimensions(array_rectangles, array_rectangles_size, 0, -5);
				}

				//МАССИВ ОТРЕЗКОВ
				//Пользовательское движение элементов
				if (array_linesegments_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W)
						doUserMoveArrayLinesegmentsW(array_linesegments, array_linesegments_size);
					if (event_menu_click.key.code == sf::Keyboard::A)
						doUserMoveArrayLinesegmentsA(array_linesegments, array_linesegments_size);
					if (event_menu_click.key.code == sf::Keyboard::S)
						doUserMoveArrayLinesegmentsS(array_linesegments, array_linesegments_size);
					if (event_menu_click.key.code == sf::Keyboard::D)
						doUserMoveArrayLinesegmentsD(array_linesegments, array_linesegments_size);
				}
				//Изменение размеров элементов и поворот элементов
				if (array_linesegments_show)
				{
					if (event_menu_click.key.code == sf::Keyboard::B)
						array_linesegments_changeDimensions(array_linesegments, array_linesegments_size, 1);
					if (event_menu_click.key.code == sf::Keyboard::N)
						array_linesegments_changeDimensions(array_linesegments, array_linesegments_size, -1);
					if (event_menu_click.key.code == sf::Keyboard::F)
						array_linesegments_changeRotate(array_linesegments, array_linesegments_size, 1);
					if (event_menu_click.key.code == sf::Keyboard::G)
						array_linesegments_changeRotate(array_linesegments, array_linesegments_size, -1);
				}
			}
		}

		window.clear(sf::Color(67, 136, 169));

		/*РЕНДЕРИНГ ОКНА*/
		BG_general.Show(window);
		BG_menu.Show(window);
		image_text.Show(window);
		menu_text.Show(window);
		BG_create.Show(window);
		create_text.Show(window);
		BG_move_and_change.Show(window);
		move_and_change_text.Show(window);
		BG_next.Show(window);
		next_text.Show(window);
		if (extra_menu == 1)
		{
			BG_back.Show(window);
			back_text.Show(window);
		}

		//Вкладка CREATE
		if (menu_create_0 && extra_menu == 0)
		{

			BG_circle.Show(window);
			circle_text.Show(window);
			BG_rect.Show(window);
			rect_text.Show(window);
			BG_linesegment.Show(window);
			linesegment_text.Show(window);
			BG_create_arrays.Show(window);
			create_arrays_text.Show(window);

			//Нажата кнопка CREATE -> create arrays of graphics primitives
			if (submenu_create_arrays_0)
			{
				BG_submenu_obj.m_setFillColor(4, 32, 159);
				BG_submenu_obj.Show(window);
				submenu_obj_text.Show(window);

				BG_create_array_circles.Show(window);
				create_array_circles_text.Show(window);
				BG_create_array_rectangles.Show(window);
				create_array_rectangles_text.Show(window);
				BG_create_array_linesegments.Show(window);
				create_array_linesegments_text.Show(window);

				/*МАССИВЫ ОБЪЕКТОВ*/
				//Вывод на окно кнопки создания по 15 граф. примитивов
				if (submenu_create_arrays_0)
				{
					BG_create_15_objs.Show(window);
					create_15_objs_text.Show(window);
				}
				//Массив окружностей
				if (array_circles_show)
				{
					BG_RandomMove_array_circles.Show(window);
					RandomMove_array_circles_text.Show(window);

					BG_UserMove_array_circles.Show(window);
					UserMove_array_circles_text.Show(window);

					BG_delete_last_elem_array_circles.Show(window);
					delete_last_elem_array_circles_text.Show(window);

					BG_delete_all_circles.Show(window);
					delete_all_circles_text.Show(window);
				}
				//Массив прямоугольников
				if (array_rectangles_show)
				{
					BG_RandomMove_array_rectangles.Show(window);
					RandomMove_array_rectangles_text.Show(window);

					BG_UserMove_array_rectangles.Show(window);
					UserMove_array_rectangles_text.Show(window);

					BG_delete_last_elem_array_rectangles.Show(window);
					delete_last_elem_array_rectangles_text.Show(window);

					BG_delete_all_rectangles.Show(window);
					delete_all_rectangles_text.Show(window);
				}

				//Массив отрезков
				if (array_linesegments_show)
				{
					BG_RandomMove_array_linesegments.Show(window);
					RandomMove_array_linesegments_text.Show(window);

					BG_UserMove_array_linesegments.Show(window);
					UserMove_array_linesegments_text.Show(window);

					BG_delete_last_elem_array_linesegments.Show(window);
					delete_last_elem_array_linesegments_text.Show(window);

					BG_delete_all_linesegments.Show(window);
					delete_all_linesegments_text.Show(window);
				}
			}
		}

		//Вкладка MOVE AND CHANGE
		if (menu_move_and_change_0 && extra_menu == 0)
		{
			//Создан объект круга
			if (circle_show)
			{
				BG_obj_circle.Show(window);
				obj_circle_text.Show(window);

				//Нажата кнопка MOVE AND CHANGE -> obj_circle
				if (submenu_obj_circle)
				{
					BG_submenu_obj.Show(window);
					submenu_obj_text.Show(window);

					BG_RandomMove_obj_circle.Show(window);
					RandomMove_obj_circle_text.Show(window);

					BG_UserMove_obj_circle.Show(window);
					UserMove_obj_circle_text.Show(window);

					BG_ChangeRadius_obj_circle.Show(window);
					ChangeRadius_obj_circle_text.Show(window);

					BG_delete_obj_circle.Show(window);
					delete_obj_circle_text.Show(window);
				}
			}
			//Создан объект прямоугольника
			if (rect_show)
			{
				BG_obj_rect.Show(window);
				obj_rect_text.Show(window);

				//Нажата кнопка MOVE AND CHANGE -> obj_rectangle
				if (submenu_obj_rect)
				{
					BG_submenu_obj.Show(window);
					submenu_obj_text.Show(window);

					BG_RandomMove_obj_rect.Show(window);
					RandomMove_obj_rect_text.Show(window);

					BG_UserMove_obj_rect.Show(window);
					UserMove_obj_rect_text.Show(window);

					BG_ChangeWidthLength_obj_rectangle.Show(window);
					ChangeWidthLength_obj_rectangle_text.Show(window);

					BG_delete_obj_rectangle.Show(window);
					delete_obj_rectangle_text.Show(window);
				}
			}
			//Создан объект отрезка
			if (linesegment_show)
			{
				BG_obj_linesegment.Show(window);
				obj_linesegment_text.Show(window);

				//Нажата кнопка MOVE AND CHANGE -> obj_linesegment
				if (submenu_obj_linesegment)
				{
					BG_submenu_obj.Show(window);
					submenu_obj_text.Show(window);

					BG_RandomMove_obj_linesegment.Show(window);
					RandomMove_obj_linesegment_text.Show(window);

					BG_UserMove_obj_linesegment.Show(window);
					UserMove_obj_linesegment_text.Show(window);

					BG_ChangeDimensions_obj_linesegment.Show(window);
					ChangeDimensions_obj_linesegment_text.Show(window);

					BG_delete_obj_linesegment.Show(window);
					delete_obj_linesegment_text.Show(window);
				}
			}
		}

		/*ЕДИНИЧНЫЕ ОБЪЕКТЫ*/
		//Вывод объектов окружности, прямоугольника и отрезка
		if (circle_show)
		{
			f_ptr_obj_circle->Show(window);
		}
		if (rect_show)
		{
			f_ptr_obj_rect->Show(window);
		}
		if (linesegment_show)
		{
			f_ptr_obj_linesegment->Show(window);
		}

		/*МАССИВЫ ОБЪЕКТОВ*/
		//Массив окружностей
		if (array_circles_show)
		{
			if (extra_menu == 0)
			{
				ChangeRadius_array_circles_text.m_setFillColor(209, 255, 26);
				ChangeRadius_array_circles_text.Show(window);
			}
			for (int i{}; i < array_circles_size; i++)
			{
				array_circles[i]->Show(window);
			}
		}
		//Массив прямоугольников
		if (array_rectangles_show)
		{
			if (extra_menu == 0)
			{
				ChangeDimensions_array_rectangles_text.m_setFillColor(209, 255, 26);
				ChangeDimensions_array_rectangles_text.Show(window);
			}
			for (int i{}; i < array_rectangles_size; i++)
			{
				array_rectangles[i]->Show(window);
			}
		}
		//Массив отрезков
		if (array_linesegments_show)
		{
			if (extra_menu == 0)
			{
				ChangeDimensions_array_linesegments_text.m_setFillColor(209, 255, 26);
				ChangeDimensions_array_linesegments_text.Show(window);
			}
			for (int i{}; i < array_linesegments_size; i++)
			{
				array_linesegments[i]->Show(window);
			}
		}

		BG_exit.Show(window);
		exit_text.Show(window);
		window.display();
	}
	return 0;
}