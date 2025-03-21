#include <cstdlib> //для функций rand() и srand()
#include <ctime> //для функции time()
#include "myfuncs.h"
#include "user_buttons.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Linesegment.h"
#include "Ellipse.h"
#include "Rhomb.h"
#include "TTrapeze.h"
#include "Quadrilateral.h"

//ГПСЧ
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}

//Оновная работа программы
int menu_processing(sf::RenderWindow& window, TCircle*& f_ptr_obj_circle, TRectangle*& f_ptr_obj_rect, TLinesegment*& f_ptr_obj_linesegment, TEllipse*& f_ptr_obj_ellipse,
	TRhomb*& f_ptr_obj_rhomb, TTrapeze*& f_ptr_obj_trapeze, TQuadrilateral*& f_ptr_obj_quadrilateral,
	int& array_circles_size, TCircle**& array_circles,
	int& array_rectangles_size, TRectangle**& array_rectangles,
	int& array_linesegments_size, TLinesegment**& array_linesegments,
	int& array_ellipses_size, TEllipse**& array_ellipses,
	int& array_rhombs_size, TRhomb**& array_rhombs,
	int& array_trapezes_size, TTrapeze**& array_trapezes,
	int& array_quadrilaterals_size, TQuadrilateral**& array_quadrilaterals)
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

	/*EXTRAMENU == 0*/

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
	Rect_BG_buttons BG_create_arrays_of_graphic_primitives(220, 160, 473, 40, 5);
	User_texts create_arrays_of_graphic_primitives_text("Comic_Sans_MS.TTF", "create arrays of graphics primitives", 231, 165, 25);

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
	//Движение по клавишам WASD окружности: obj_circle -> circle_user_move
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
	//Сдвинуть случайным образом по x и по y из диапазона [-50;50]:obj_rectangle-> rect_random_move
	Rect_BG_buttons BG_RandomMove_obj_rect(5, 455, 230, 40, 5);
	User_texts RandomMove_obj_rect_text("Comic_Sans_MS.TTF", "rect_random_move", 10, 460, 20);
	//Движение по клавишам WASD прямоугольника: obj_rectangle -> rect_user_move
	Rect_BG_buttons BG_UserMove_obj_rect(250, 455, 230, 40, 5);
	User_texts UserMove_obj_rect_text("Comic_Sans_MS.TTF", "rect_user_move", 270, 460, 20);
	//Изменение размеров: obj_rectangle -> rectangle_change_dimensions:\n(z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width
	Rect_BG_buttons BG_ChangeWidthLength_obj_rectangle(5, 510, 300, 160, 5);
	User_texts ChangeWidthLength_obj_rectangle_text("Comic_Sans_MS.TTF",
		"rectangle_change_dimensions:\n(z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width\n(r) - rotate 90 degrees", 10, 510, 18);
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
	//Движение по клавишам WASD отрезка: obj_linesegment -> line_user_move
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
		"(z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width\n(r) - rotate 90 degrees", 200, 760, 15);

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
	//Изменение размера элементов массива отрезков: array of linesegments -> linesegment_change_length:\n(b) - increase\n(n) - decrease\nlinesegment_change_rotate:\n(f) - rotate clockwise\n(g) - rotate counterclockwise
	User_texts ChangeDimensions_array_linesegments_text("Comic_Sans_MS.TTF",
		"linesegment_change_length:\n(b) - increase\n(n) - decrease\nlinesegment_change_rotate:\n(f) - rotate clockwise\n(g) - rotate counterclockwise", 425, 760, 15);

	//Переход на следующую или предыдущую страницу графических примитивов с последующей обработкой
	Rect_BG_buttons BG_next(600, 5, 100, 85, 5);
	User_texts next_text("Comic_Sans_MS.TTF", "NEXT", 605, 30, 30);
	Rect_BG_buttons BG_back(495, 5, 100, 85, 5);
	User_texts back_text("Comic_Sans_MS.TTF", "BACK", 500, 30, 30);

	/*EXTRAMENU == 1*/

	//CREATE->ellipse
	Rect_BG_buttons BG_ellipse(220, 97, 140, 40, 5);
	User_texts ellipse_text("Comic_Sans_MS.TTF", "ellipse", 240, 100, 25);
	//CREATE->rhomb
	Rect_BG_buttons BG_rhomb(375, 97, 140, 40, 5);
	User_texts rhomb_text("Comic_Sans_MS.TTF", "rhomb", 390, 100, 25);
	//CREATE->trapeze
	Rect_BG_buttons BG_trapeze(529, 97, 165, 40, 5);
	User_texts trapeze_text("Comic_Sans_MS.TTF", "trapeze", 540, 100, 25);
	//CREATE->create arrays of hereditary objects
	Rect_BG_buttons BG_create_arrays_of_hereditary_objects(220, 160, 473, 40, 5);
	User_texts create_arrays_of_hereditary_objects_text("Comic_Sans_MS.TTF", "create arrays of hereditary objects", 231, 165, 25);

	/*КНОПКИ ПОДМЕНЮ CREATE->create array of hereditary objects*/
	//Create->create arrays of hereditary objects->array of ellipses
	Rect_BG_buttons BG_create_array_ellipses(5, 460, 180, 40, 5);
	User_texts create_array_ellipses_text("Comic_Sans_MS.TTF", "array of ellipses", 10, 467, 20);
	//Create->create arrays of hereditary objects->array of rhombs
	Rect_BG_buttons BG_create_array_rhombs(197, 460, 210, 40, 5);
	User_texts create_array_rhombs_text("Comic_Sans_MS.TTF", "array of rhombs", 199, 467, 20);
	//Create->create arrays of hereditary objects->array of trapezes
	Rect_BG_buttons BG_create_array_trapezes(420, 460, 240, 40, 5);
	User_texts create_array_trapezes_text("Comic_Sans_MS.TTF", "array of trapezes", 420, 467, 20);

	/*СВОЙСТВА ЭЛЛИПСА*/
	//Открыть меню обработки свойств: MOVE AND CHANGE->obj_ellipse
	Rect_BG_buttons BG_obj_ellipse(220, 229, 140, 40, 5);
	User_texts obj_ellipse_text("Comic_Sans_MS.TTF", "obj_ellipse", 225, 238, 21);
	//Сдвинуть случайным образом по x и по y из диапазона [-50;50]:obj_ellipse-> ellipse_random_move
	Rect_BG_buttons BG_RandomMove_obj_ellipse(5, 455, 230, 40, 5);
	User_texts RandomMove_obj_ellipse_text("Comic_Sans_MS.TTF", "ellipse_random_move", 10, 460, 20);
	//Движение по клавишам WASD эллипса: obj_ellipse -> ellipse_user_move
	Rect_BG_buttons BG_UserMove_obj_ellipse(250, 455, 230, 40, 5);
	User_texts UserMove_obj_ellipse_text("Comic_Sans_MS.TTF", "ellipse_user_move", 270, 460, 20);
	//Увеличить или уменьшить полуоси: obj_ellipse -> ellipse_change_semi_axises:\n(q) - increase semi_major_axis\n(e) - decrease_semi_major_axis
	//\n(z) - increase semi_minor_axis\n(c) - decrease_Semi_minor_axis
	Rect_BG_buttons BG_ChangeDimensions_obj_ellipse(5, 510, 320, 160, 5);
	User_texts ChangeDimensions_obj_ellipse_text("Comic_Sans_MS.TTF",
		"ellipse_change_semi_axises:\n(q) - increase semi_major_axis\n(e) - decrease_semi_major_axis\n(z) - increase semi_minor_axis\n(c) - decrease_Semi_minor_axis\n(x) - rotate 90 degrees", 10, 520, 18);
	//Удалить объект: obj_ellipse -> delete
	Rect_BG_buttons BG_delete_obj_ellipse(495, 455, 160, 40, 5);
	User_texts delete_obj_ellipse_text("Comic_Sans_MS.TTF", "delete", 530, 460, 25);

	/*СВОЙСТВА РОМБА*/
	//Открыть меню обработки свойств: MOVE AND CHANGE->obj_rhomb
	Rect_BG_buttons BG_obj_rhomb(375, 229, 160, 40, 5);
	User_texts obj_rhomb_text("Comic_Sans_MS.TTF", "obj_rhomb", 380, 238, 21);
	//Сдвинуть случайным образом по x и по y из диапазона [-50;50]:obj_rhomb-> rhomb_random_move
	Rect_BG_buttons BG_RandomMove_obj_rhomb(5, 455, 230, 40, 5);
	User_texts RandomMove_obj_rhomb_text("Comic_Sans_MS.TTF", "rhomb_random_move", 10, 460, 20);
	//Движение по клавишам WASD ромба: obj_rhomb -> rhomb_user_move
	Rect_BG_buttons BG_UserMove_obj_rhomb(250, 455, 230, 40, 5);
	User_texts UserMove_obj_rhomb_text("Comic_Sans_MS.TTF", "rhomb_user_move", 270, 460, 20);
	//Увеличить или уменьшить размеры и поворт: obj_rhomb -> изменение размеров и поворот  
	Rect_BG_buttons BG_ChangeDimensions_obj_rhomb(5, 510, 300, 160, 5);
	User_texts ChangeDimensions_obj_rhomb_text("Comic_Sans_MS.TTF",
		"rhomb_change_dimensions:\n(r) - increase length\n(t) - decrease length\n(v) - increase degree\n(b) - decrease degree", 10, 510, 18);
	//Удалить объект: obj_rhomb->delete
	Rect_BG_buttons BG_delete_obj_rhomb(495, 455, 160, 40, 5);
	User_texts delete_obj_rhomb_text("Comic_Sans_MS.TTF", "delete", 530, 460, 25);

	/*СВОЙСТВА ТРАПЕЦИИ*/
	//Открыть меню обработки свойств: MOVE AND CHANGE->obj_trapeze
	Rect_BG_buttons BG_obj_trapeze(220, 280, 185, 40, 5);
	User_texts obj_trapeze_text("Comic_Sans_MS.TTF", "obj_trapeze", 225, 290, 21);
	//Сдвинуть случайным образом по x и по y из диапазона [-50;50]:obj_trapeze-> trapeze_random_move
	Rect_BG_buttons BG_RandomMove_obj_trapeze(5, 455, 230, 40, 5);
	User_texts RandomMove_obj_trapeze_text("Comic_Sans_MS.TTF", "trapeze_random_move", 10, 460, 18);
	//Движение по клавишам WASD трапеции: obj_trapeze -> trapeze_user_move
	Rect_BG_buttons BG_UserMove_obj_trapeze(250, 455, 230, 40, 5);
	User_texts UserMove_obj_trapeze_text("Comic_Sans_MS.TTF", "trapeze_user_move", 270, 460, 20);
	//Увеличить или уменьшить длину трапеции, повернуть трапецию: obj_trapeze -> ....
	Rect_BG_buttons BG_ChangeDimensions_obj_trapeze(5, 510, 300, 180, 5);
	User_texts ChangeDimensions_obj_trapeze_text("Comic_Sans_MS.TTF",
		"trapeze_change_dimensions:\n(y) - increase_TopBase\n(u) - decrease_TopBase\n(g) - increase_height\n(h) - decrease_height\n(n) - increase_BottomBase\n(m) - decrease_BottomBase", 10, 510, 18);
	//Удалить объект: obj_trapeze -> delete
	Rect_BG_buttons BG_delete_obj_trapeze(495, 455, 160, 40, 5);
	User_texts delete_obj_trapeze_text("Comic_Sans_MS.TTF", "delete", 530, 460, 25);

	/*СВОЙСТВА МАССИВА ЭЛЛИПСОВ*/
	//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]:array_of_ellipses -> random move(ellipses)
	Rect_BG_buttons BG_RandomMove_array_ellipses(5, 520, 180, 40, 5);
	User_texts RandomMove_array_ellipses_text("Comic_Sans_MS.TTF", "random move(ellipses)", 10, 530, 15);
	//Движение по клавишам WASD элементов: array of ellipses -> user move(ellipses) 
	Rect_BG_buttons BG_UserMove_array_ellipses(5, 580, 180, 40, 5);
	User_texts UserMove_array_ellipses_text("Comic_Sans_MS.TTF", "user move(ellipses)", 10, 590, 17);
	//Удалить последний элемент: array of ellipses -> delete_last ellipse
	Rect_BG_buttons BG_delete_last_elem_array_ellipses(5, 640, 180, 40, 5);
	User_texts delete_last_elem_array_ellipses_text("Comic_Sans_MS.TTF", "delete_last ellipse", 10, 650, 17);
	//Удалить все элементы: array of ellipses -> delete all ellipses
	Rect_BG_buttons BG_delete_all_ellipses(5, 700, 180, 40, 5);
	User_texts delete_all_ellipses_text("Comic_Sans_MS.TTF", "delete all ellipses", 10, 710, 17);
	//Увеличение или уменьшение размера: array of ellipses -> \n(q) - increase_semi_major_axis\n(e) - decrease_semi_major_axis
	//\n(z) - increase_semi_minor_axis\n(c) - decrease_Semi_minor_axis
	User_texts ChangeDimensions_array_ellipses_text("Comic_Sans_MS.TTF",
		"\n(q) - increase_semi_major_axis\n(e) - decrease_semi_major_axis\n(z) - increase_semi_minor_axis\n(c) - decrease_semi_minor_axis\n(x) - rotate 90 degrees", 5, 735, 12);

	/*СВОЙСТВА МАССИВА РОМБОВ*/
	//Смещение
	Rect_BG_buttons BG_RandomMove_array_rhombs(197, 520, 210, 40, 5);
	User_texts RandomMove_array_rhombs_text("Comic_Sans_MS.TTF", "random move(rhombs)", 204, 530, 15);
	//Пользовательское движение
	Rect_BG_buttons BG_UserMove_array_rhombs(197, 580, 210, 40, 5);
	User_texts UserMove_array_rhombs_text("Comic_Sans_MS.TTF", "user move(rhombs)", 204, 590, 17);
	//Удаление последнего элемента
	Rect_BG_buttons BG_delete_last_elem_array_rhombs(197, 640, 210, 40, 5);
	User_texts delete_last_elem_array_rhombs_text("Comic_Sans_MS.TTF", "delete_last rhomb", 204, 650, 17);
	//Удаление всех элементов
	Rect_BG_buttons BG_delete_all_rhombs(197, 700, 210, 40, 5);
	User_texts delete_all_rhombs_text("Comic_Sans_MS.TTF", "delete all rhombs", 204, 710, 17);
	//Изменение размеров и поворт
	User_texts ChangeDimensions_array_rhombs_text("Comic_Sans_MS.TTF",
		"(r) - increase length\n(t) - decrease length\n(v) - increase degree\n(b) - decrease degree", 230, 750, 14);

	/*СВОЙСТВА МАССИВА ТРАПЕЦИЙ*/
	//Смещение
	Rect_BG_buttons BG_RandomMove_array_trapezes(420, 520, 240, 40, 5);
	User_texts RandomMove_array_trapezes_text("Comic_Sans_MS.TTF", "random move(trapezes)", 425, 530, 15);
	//Пользовательское движение
	Rect_BG_buttons BG_UserMove_array_trapezes(420, 580, 240, 40, 5);
	User_texts UserMove_array_trapezes_text("Comic_Sans_MS.TTF", "user move(trapezes)", 425, 590, 17);
	//Удалить последний элемент
	Rect_BG_buttons BG_delete_last_elem_array_trapezes(420, 640, 240, 40, 5);
	User_texts delete_last_elem_array_trapezes_text("Comic_Sans_MS.TTF", "delete_last trapeze", 425, 650, 17);
	//Удалить все элементы
	Rect_BG_buttons BG_delete_all_trapezes(420, 700, 240, 40, 5);
	User_texts delete_all_trapezes_text("Comic_Sans_MS.TTF", "delete all trapezes", 425, 710, 17);
	//Изменение размера элементов массива и поворот
	User_texts ChangeDimensions_array_trapezes_text("Comic_Sans_MS.TTF",
		"(y) - increase_TopBase\n(u) - decrease_TopBase\n(g) - increase_height\n(h) - decrease_height\n(n) - increase_BottomBase\n(m) - decrease_BottomBase", 425, 750, 14);

	/*EXTRAMENU == 2*/

	/*КНОПКИ ПОДМЕНЮ CREATE*/
	//CREATE->quadnrilateral
	Rect_BG_buttons BG_quadrilateral(220, 97, 180, 40, 5);
	User_texts quadrilateral_text("Comic_Sans_MS.TTF", "quadrilateral", 225, 100, 25);
	//CREATE->create arrays of convex polygons
	Rect_BG_buttons BG_create_arrays_of_convex_polygons(220, 160, 473, 40, 5);
	User_texts create_arrays_of_convex_polygons_text("Comic_Sans_MS.TTF", "create arrays of convex polygons", 231, 165, 25);

	/*КНОПКИ ПОДМЕНЮ CREATE->create array of convex polygons*/
	//Create->create arrays of convex polygons->array of quadrilaterals
	Rect_BG_buttons BG_create_array_quadrilaterals(5, 460, 245, 40, 5);
	User_texts create_array_quadrilaterals_text("Comic_Sans_MS.TTF", "array of quadrilaterals", 10, 467, 19);

	/*СВОЙСТВА ЧЕТЫРЕХУГОЛЬНИКА*/
	//Открыть меню обработки свойств: MOVE AND CHANGE->obj_quadrilateral
	Rect_BG_buttons BG_obj_quadrilateral(220, 229, 140, 40, 5);
	User_texts obj_quadrilateral_text("Comic_Sans_MS.TTF", "obj_quadrilateral", 220, 238, 14);
	//Сдвинуть случайным образом по x и по y из диапазона [-50;50]:obj_quadrilateral->quadrilateral_random_move
	Rect_BG_buttons BG_RandomMove_obj_quadrilateral(5, 455, 230, 40, 5);
	User_texts RandomMove_obj_quadrilateral_text("Comic_Sans_MS.TTF", "quadrilateral_random_move", 10, 465, 14);
	//Движение по клавишам WASD элементов: obj_quadrilateral -> quadrilateral_user_move
	Rect_BG_buttons BG_UserMove_obj_quadrilateral(250, 455, 230, 40, 5);
	User_texts UserMove_obj_quadrilateral_text("Comic_Sans_MS.TTF", "quadrilateral_user_move", 270, 465, 14);
	//Увеличить или уменьшить размер: obj_quadrilateral -> quadrilateral_change_dimensions:\n(r) - increase\n(v) - decrease
	Rect_BG_buttons BG_ChangeDimensions_obj_quadrilateral(5, 510, 300, 80, 5);
	User_texts ChangeDimensions_obj_quadrilateral_text("Comic_Sans_MS.TTF", "quadrilateral_change_dimesnions:\n(r) - increase\n(v) - decrease", 10, 515, 14);
	//Удалить объект: obj_quadrilateral -> delete
	Rect_BG_buttons BG_delete_obj_quadrilateral(495, 455, 160, 40, 5);
	User_texts delete_obj_quadrilateral_text("Comic_Sans_MS.TTF", "delete", 530, 460, 25);

	/*СВОЙСТВА МАССИВА ЧЕТЫРЕХУГОЛЬНИКОВ*/
	//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]:array_of_quadrilaterals -> random move(quadrilaterals)
	Rect_BG_buttons BG_RandomMove_array_quadrilaterals(5, 520, 245, 40, 5);
	User_texts RandomMove_array_quadrilaterals_text("Comic_Sans_MS.TTF", "random move(quadrilaterals)", 10, 530, 15);
	//Движение по клавишам WASD элементов: array of quadrilaterals -> user move(quadrilaterals) 
	Rect_BG_buttons BG_UserMove_array_quadrilaterals(5, 580, 245, 40, 5);
	User_texts UserMove_array_quadrilaterals_text("Comic_Sans_MS.TTF", "user move(quadrilaterals)", 10, 590, 17);
	//Удалить последний элемент: array of quadrilaterals -> delete_last quadrilateral
	Rect_BG_buttons BG_delete_last_elem_array_quadrilaterals(5, 640, 245, 40, 5);
	User_texts delete_last_elem_array_quadrilaterals_text("Comic_Sans_MS.TTF", "delete_last quadrilateral", 10, 650, 17);
	//Удалить все элементы: array of quadrilaterals -> delete all quadrilaterals
	Rect_BG_buttons BG_delete_all_quadrilaterals(5, 700, 245, 40, 5);
	User_texts delete_all_quadrilaterals_text("Comic_Sans_MS.TTF", "delete all quadrilaterals", 10, 710, 17);
	//Увеличение или уменьшение радиуса: array of quadrilaterals ->\n(r) - increase dimensions\n(v) - decrease dimensions
	User_texts ChangeDimensions_array_quadrilaterals_text("Comic_Sans_MS.TTF", "(r) - increase dimensions\n(v) - decrease dimensions", 5, 760, 15);

	//Привзяка ГПСЧ к календарному времени (случайные последовательности случайных чисел из диапазона)
	srand(static_cast<unsigned int>(time(0)));

	//Организация перехода окна между дополнительными меню
	int extra_menu{ 0 };
	//Учет явного нажатия кнопок: CREATE, MOVE_AND_CHANGE (для разных extra_menu)
	bool menu_create_0{ false }, menu_move_and_change_0{ false }, menu_create_1{ false }, menu_move_and_change_1{ false }, menu_create_2{ false }, menu_move_and_change_2{ false };
	//ЕДИНИЧНЫЕ ОБЪЕКТЫ
	//Учет явного нажатия кнопок CREATE ->: circle, rectangle, linesegment, ellipse, quadrilateral и др
	bool circle_show{ false }, rect_show{ false }, linesegment_show{ false }, ellipse_show{ false }, quadrilateral_show{ false }, rhomb_show{ false }, trapeze_show{ false };
	//Учет явного нажатия кнопок MOVE AND CHANGE ->: obj_circle, obj_rectangle, obj_;inesegment, obj_ellipse, obj_quadrilateral и др
	bool submenu_obj_circle{ false }, submenu_obj_rect{ false }, submenu_obj_linesegment{ false }, submenu_obj_ellipse{ false }, submenu_obj_quadrilateral{ false }, submenu_obj_rhomb{ false }, submenu_obj_trapeze{ false };
	//Учет явного нажатия кнопок obj_circle -> circle_random_move, obj_rectangle -> rect_user_move, obj_linesegment -> line_user_move, obj_ellipse -> ellipse_user_move, obj_quadrilateral -> quadrilateral -> quadrilateral_user_move и т.д.
	bool circle_user_move{ false }, rect_user_move{ false }, linesegment_user_move{ false }, ellipse_user_move{ false }, quadrilateral_user_move{ false }, rhomb_user_move{ false }, trapeze_user_move{ false };
	//Учет явного нажатия кнопок у obj_circle, obj_rectangle, obj_linesegment, obj_ellipse изменения размеров, obj_quadrilateral и др
	bool circle_change_radius{ false }, rectangle_change_dimensions{ false }, linesegment_change_dimensions{ false }, ellipse_change_dimensions{ false }, quadrilateral_change_dimensions{ false },
		rhomb_change_dimensions{ false }, trapeze_change_dimensions{ false };
	//МАССИВЫ
	//Явное нажатие кнопки CREATE -> create arrays of graphics primitives, create_15_objs
	bool submenu_create_arrays_0{ false }, create_15_objs{ false }, submenu_create_arrays_1{ false }, submenu_create_arrays_2{ false };
	//Создание одного/нескольких элементов массива с помощью одной переменной
	int mass_or_single{ ONE_OBJ };
	//Явное нажатие кнопок create arrays of graphics primitives ->: array of circles, array of rectangles, array of linesegments, array of ellipses и др
	bool array_circles_show{ false }, array_rectangles_show{ false }, array_linesegments_show{ false }, array_ellipses_show{ false }, array_quadrilaterals_show{ false }, array_rhombs_show{ false }, array_trapezes_show{ false };
	//Явное нажатие кнопок array of circles -> user move(circles), array of rectangles -> user move(rectangles), array of ellipses -> user move(ellipses), array of quadrilaterals -> user move(quadrilaterals) и др
	bool array_circles_user_move{ false }, array_rectangles_user_move{ false }, array_linesegments_user_move{ false }, array_ellipses_user_move{ false }, array_quadrilaterals_user_move{ false },
		array_rhombs_user_move{ false }, array_trapezes_user_move{ false };

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

		//ПОДМЕНЮ CREATE_0
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
		BG_create_arrays_of_graphic_primitives.m_setFillColor(195, 195, 195);
		create_arrays_of_graphic_primitives_text.m_setDefaultColor();
		//create arrays of graphics primitives -> array of circles
		BG_create_array_circles.m_setFillColor(195, 195, 195);
		create_array_circles_text.m_setDefaultColor();
		//create arrays of graphics primitives -> array of rectangles
		BG_create_array_rectangles.m_setFillColor(195, 195, 195);
		create_array_rectangles_text.m_setDefaultColor();
		//create arrays of graphics primitives -> array of linesegments
		BG_create_array_linesegments.m_setFillColor(195, 195, 195);
		create_array_linesegments_text.m_setDefaultColor();

		//ПОДМЕНЮ CREATE_1
		//CREATE -> ellipse
		BG_ellipse.m_setFillColor(195, 195, 195);
		ellipse_text.m_setDefaultColor();
		BG_rhomb.m_setFillColor(195, 195, 195);
		rhomb_text.m_setDefaultColor();
		BG_trapeze.m_setFillColor(195, 195, 195);
		trapeze_text.m_setDefaultColor();
		//CREATE -> create arrays of hereditary objects
		BG_create_arrays_of_hereditary_objects.m_setFillColor(195, 195, 195);
		create_arrays_of_hereditary_objects_text.m_setDefaultColor();
		//create arrays of hereditary objects -> array of ellipses
		BG_create_array_ellipses.m_setFillColor(195, 195, 195);
		create_array_ellipses_text.m_setDefaultColor();
		BG_create_array_rhombs.m_setFillColor(195, 195, 195);
		create_array_rhombs_text.m_setDefaultColor();
		BG_create_array_trapezes.m_setFillColor(195, 195, 195);
		create_array_trapezes_text.m_setDefaultColor();

		//ПОДМЕНЮ CREATE_2
		//CREATE -> quadrilateral
		BG_quadrilateral.m_setFillColor(195, 195, 195);
		quadrilateral_text.m_setDefaultColor();
		//CREATE -> create arrays of convex polygons
		BG_create_arrays_of_convex_polygons.m_setFillColor(195, 195, 195);
		create_arrays_of_convex_polygons_text.m_setDefaultColor();
		//create arrays of convex poygons -> array of quadrilaterals
		BG_create_array_quadrilaterals.m_setFillColor(195, 195, 195);
		create_array_quadrilaterals_text.m_setDefaultColor();

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

		//ОБЪЕКТ ЭЛЛИПСА
		//MOVE AND CHANGE -> obj_ellipse
		BG_obj_ellipse.m_setFillColor(195, 195, 195);
		obj_ellipse_text.m_setDefaultColor();
		//obj_ellipse -> ellipse_random_move
		BG_RandomMove_obj_ellipse.m_setDefaultColor();
		RandomMove_obj_ellipse_text.m_setDefaultColor();
		//obj_ellipse -> delete
		BG_delete_obj_ellipse.m_setDefaultColor();
		delete_obj_ellipse_text.m_setDefaultColor();

		//ОБЪЕКТ РОМБА
		//MOVE AND CHANGE -> obj_rhomb
		BG_obj_rhomb.m_setFillColor(195, 195, 195);
		obj_rhomb_text.m_setDefaultColor();
		//obj_rhomb -> rhomb_random_move
		BG_RandomMove_obj_rhomb.m_setDefaultColor();
		RandomMove_obj_rhomb_text.m_setDefaultColor();
		//obj_rhomb -> delete
		BG_delete_obj_rhomb.m_setDefaultColor();
		delete_obj_rhomb_text.m_setDefaultColor();

		//ОБЪЕКТ ТРАПЕЦИИ
		//MOVE AND CHANGE -> obj_trapeze
		BG_obj_trapeze.m_setFillColor(195, 195, 195);
		obj_trapeze_text.m_setDefaultColor();
		//obj_trapeze -> trapeze_random_move
		BG_RandomMove_obj_trapeze.m_setDefaultColor();
		RandomMove_obj_trapeze_text.m_setDefaultColor();
		//obj_trapeze -> delete
		BG_delete_obj_trapeze.m_setDefaultColor();
		delete_obj_trapeze_text.m_setDefaultColor();

		//ОБЪЕКТ ЧЕТЫРЕХУГОЛЬНИКА
		//MOVE AND CHANGE -> obj_quadrilateral
		BG_obj_quadrilateral.m_setFillColor(195, 195, 195);
		obj_quadrilateral_text.m_setDefaultColor();
		//obj_quadrilateral -> quadrilateral_random_move
		BG_RandomMove_obj_quadrilateral.m_setDefaultColor();
		RandomMove_obj_quadrilateral_text.m_setDefaultColor();
		//obj_quadrilateral -> delete
		BG_delete_obj_quadrilateral.m_setDefaultColor();
		delete_obj_quadrilateral_text.m_setDefaultColor();

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

		//МАССИВ ЭЛЛИПСОВ
		//array of ellipses -> random move(ellipses)
		BG_RandomMove_array_ellipses.m_setFillColor(195, 195, 195);
		RandomMove_array_ellipses_text.m_setDefaultColor();
		//array of ellipses -> delete_last ellipses
		BG_delete_last_elem_array_ellipses.m_setFillColor(195, 195, 195);
		delete_last_elem_array_ellipses_text.m_setDefaultColor();
		//array of ellipses -> delete all ellipses;
		BG_delete_all_ellipses.m_setFillColor(195, 195, 195);
		delete_all_ellipses_text.m_setDefaultColor();

		//МАССИВ РОМБОВ
		//array of rhombs -> random move(rhombs)
		BG_RandomMove_array_rhombs.m_setFillColor(195, 195, 195);
		RandomMove_array_rhombs_text.m_setDefaultColor();
		//array of rhombs -> delete_last rhombs
		BG_delete_last_elem_array_rhombs.m_setFillColor(195, 195, 195);
		delete_last_elem_array_rhombs_text.m_setDefaultColor();
		//array of rhombs -> delete all rhombs;
		BG_delete_all_rhombs.m_setFillColor(195, 195, 195);
		delete_all_rhombs_text.m_setDefaultColor();

		//МАССИВ ТРАПЕЦИЙ
		//array of trapezes -> random move(trapezes)
		BG_RandomMove_array_trapezes.m_setFillColor(195, 195, 195);
		RandomMove_array_trapezes_text.m_setDefaultColor();
		//array of trapezes -> delete_last trapezes
		BG_delete_last_elem_array_trapezes.m_setFillColor(195, 195, 195);
		delete_last_elem_array_trapezes_text.m_setDefaultColor();
		//array of trapezes -> delete all trapezes;
		BG_delete_all_trapezes.m_setFillColor(195, 195, 195);
		delete_all_trapezes_text.m_setDefaultColor();

		//МАССИВ ЧЕТЫРЕХУГОЛЬНИКОВ
		//array of quadrilaterals -> random move(quadrilaterals)
		BG_RandomMove_array_quadrilaterals.m_setFillColor(195, 195, 195);
		RandomMove_array_quadrilaterals_text.m_setDefaultColor();
		//array of quadrilaterals -> delete_last quadrilateral
		BG_delete_last_elem_array_quadrilaterals.m_setFillColor(195, 195, 195);
		delete_last_elem_array_quadrilaterals_text.m_setDefaultColor();
		//array of quadrilaterals -> delete all quadrilaterals
		BG_delete_all_quadrilaterals.m_setFillColor(195, 195, 195);
		delete_all_quadrilaterals_text.m_setDefaultColor();

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

		//ОБЪЕКТ ЭЛЛИПСА
		//Нажата кнопка obj_ellipse -> ellipse_user_move
		if (!ellipse_user_move)
		{
			BG_UserMove_obj_ellipse.m_setDefaultColor();
			UserMove_obj_ellipse_text.m_setDefaultColor();
		}
		//Нажата кнопка obj_ellipse -> ellipse_change_semi_axis:..............
		if (!ellipse_change_dimensions)
		{
			BG_ChangeDimensions_obj_ellipse.m_setDefaultColor();
			ChangeDimensions_obj_ellipse_text.m_setDefaultColor();
		}

		//ОБЪЕКТ РОМБА
		if (!rhomb_user_move)
		{
			BG_UserMove_obj_rhomb.m_setDefaultColor();
			UserMove_obj_rhomb_text.m_setDefaultColor();
		}
		if (!rhomb_change_dimensions)
		{
			BG_ChangeDimensions_obj_rhomb.m_setDefaultColor();
			ChangeDimensions_obj_rhomb_text.m_setDefaultColor();
		}

		//ОБЪЕКТ ТРАПЕЦИИ
		if (!trapeze_user_move)
		{
			BG_UserMove_obj_trapeze.m_setDefaultColor();
			UserMove_obj_trapeze_text.m_setDefaultColor();
		}
		if (!trapeze_change_dimensions)
		{
			BG_ChangeDimensions_obj_trapeze.m_setDefaultColor();
			ChangeDimensions_obj_trapeze_text.m_setDefaultColor();
		}

		//ОБЪЕКТ ЧЕТЫРЕХУГОЛЬНИКА
		//Нажата кнопка obj_quadrilateral -> quadrilaterl_user_move
		if (!quadrilateral_user_move)
		{
			BG_UserMove_obj_quadrilateral.m_setDefaultColor();
			UserMove_obj_quadrilateral_text.m_setDefaultColor();
		}
		//Нажата кнопка obj_quadrilateral -> quadrilateral_change_dimensions
		if (!quadrilateral_change_dimensions)
		{
			BG_ChangeDimensions_obj_quadrilateral.m_setDefaultColor();
			ChangeDimensions_obj_quadrilateral_text.m_setDefaultColor();
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
		//МАССИВ ЭЛЛИПСОВ
		if (!array_ellipses_user_move)
		{
			BG_UserMove_array_ellipses.m_setFillColor(195, 195, 195);
			UserMove_array_ellipses_text.m_setDefaultColor();
		}
		//МАССИВ РОМБОВ
		if (!array_rhombs_user_move)
		{
			BG_UserMove_array_rhombs.m_setFillColor(195, 195, 195);
			UserMove_array_rhombs_text.m_setDefaultColor();
		}
		//МАССИВ ТРАПЕЦИЙ
		if (!array_trapezes_user_move)
		{
			BG_UserMove_array_trapezes.m_setFillColor(195, 195, 195);
			UserMove_array_trapezes_text.m_setDefaultColor();
		}
		//МАССИВ ЧЕТЫРЕХУГОЛЬНИКОВ
		if (!array_quadrilaterals_user_move)
		{
			BG_UserMove_array_quadrilaterals.m_setFillColor(195, 195, 195);
			UserMove_array_quadrilaterals_text.m_setDefaultColor();
		}

		/*БУЛЕВЫЕ ПЕРЕМЕННЫЕ ДЛЯ ПОЛОЖЕНИЯ КУРСОРА НА КНОПКЕ*/
		//Кнопки меню: NEXT, BACK, CREATE, MOVE AND CHANGE, EXIT
		bool stage_next{ false }, stage_back{ false }, stage_create_0{ false }, stage_move_and_change_0{ false }, stage_create_1{ false }, stage_move_and_change_1{ false },
			stage_create_2{ false }, stage_move_and_change_2{ false }, stage_exit{ false };
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

		//ОБЪЕКТ ЭЛЛИПСА
		bool stage_ellipse_create{ false };//Кнопка CREATE -> ellipse
		bool stage_obj_ellipse{ false };//Кнопка MOVE AND CHANGE -> obj_ellipse
		//Кнопки obj_ellipse ->: ellipse_random_move, ellipse_user_move, ellipse_change_dimensions, delete
		bool stage_ellipse_random_move{ false }, stage_ellipse_user_move{ false }, stage_ellipse_change_dimensions{ false }, stage_delete_obj_ellipse{ false };

		//ОБЪЕКТ РОМБА
		bool stage_rhomb_create{ false };
		bool stage_obj_rhomb{ false };
		bool stage_rhomb_random_move{ false }, stage_rhomb_user_move{ false }, stage_rhomb_change_dimensions{ false }, stage_delete_obj_rhomb{ false };

		//ОБЪЕКТ ТРАПЕЦИИ
		bool stage_trapeze_create{ false };
		bool stage_obj_trapeze{ false };
		bool stage_trapeze_random_move{ false }, stage_trapeze_user_move{ false }, stage_trapeze_change_dimensions{ false }, stage_delete_obj_trapeze{ false };

		//ОБЪЕКТ ЧЕТЫРЕХУГОЛЬНИКА
		bool stage_quadrilateral_create{ false };
		bool stage_obj_quadrilateral{ false };
		bool stage_quadrilateral_random_move{ false }, stage_quadrilateral_user_move{ false }, stage_quadrilateral_change_dimensions{ false }, stage_delete_obj_quadrilateral{ false };

		//МАССИВЫ
		//Кнопка CREATE -> create arrays of graphics primitives, create arrays of complex objects
		bool stage_create_arrays_of_graphic_primitives{ false }, stage_create_arrays_of_hereditary_objects{ false }, stage_create_arrays_of_convex_polygons{ false };
		bool stage_create_15_objs{ false };//Кнопка create arrays of graphics primitives -> create_15_objs
		//Кнопки arrays of graphics primitives ->: array of circles, array of rectangles, array of linesegments, array of rings, array of mortars
		bool stage_create_array_circles{ false }, stage_create_array_rectangles(false), stage_create_array_linesegments{ false }, stage_create_array_ellipses{ false },
			stage_create_array_rhombs{ false }, stage_create_array_trapezes{ false }, stage_create_array_quadrilaterals{ false };
		//МАССИВ ОКРУЖНОСТЕЙ. Кнопки array of circles ->: random move(circles), user move (circles), delete_last circle, delete all circles
		bool stage_RandomMove_array_circles{ false }, stage_user_move_array_circles{ false }, stage_delete_last_elem_array_circles{ false },
			stage_delete_all_circles{ false };
		//МАССИВ ПРЯМОУГОЛЬНИКОВ. Кнопки array of rectangles ->: random move(rectangles), user move(rectangles), delete_last rectangle, delete all rectangles
		bool stage_RandomMove_array_rectangles{ false }, stage_user_move_array_rectangles{ false }, stage_delete_last_elem_array_rectangles{ false },
			stage_delete_all_rectangles{ false };
		//МАССИВ ОТРЕЗКОВ. Кнопки array of linesegments ->: random move(linesegments), user move(linesegments), delete_last linesegment, delete all linesegments
		bool stage_RandomMove_array_linesegments{ false }, stage_user_move_array_linesegments{ false }, stage_delete_last_elem_array_linesegments{ false },
			stage_delete_all_linesegments{ false };
		//МАССИВ ЭЛЛИПСОВ. Кнопки array of ellipses ->: random move(ellipses), user move(ellipses), delete_last ellipse, delete all ellipses
		bool stage_RandomMove_array_ellipses{ false }, stage_user_move_array_ellipses{ false }, stage_delete_last_elem_array_ellipses{ false }, stage_delete_all_ellipses{ false };
		//МАССИВ РОМБОВ.
		bool stage_RandomMove_array_rhombs{ false }, stage_user_move_array_rhombs{ false }, stage_delete_last_elem_array_rhombs{ false }, stage_delete_all_rhombs{ false };
		//МАССИВ ТРАПЕЦИЙ
		bool stage_RandomMove_array_trapezes{ false }, stage_user_move_array_trapezes{ false }, stage_delete_last_elem_array_trapezes{ false }, stage_delete_all_trapezes{ false };
		//МАССИВ ЧЕТЫРЕХУГОЛЬНИКОВ.
		bool stage_RandomMove_array_quadrilaterals{ false }, stage_user_move_array_quadrilaterals{ false }, stage_delete_last_elem_array_quadrilaterals{ false }, stage_delete_all_quadrilaterals{ false };

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
			if (extra_menu == 0)
				stage_create_0 = true;
			else if (extra_menu == 1)
				stage_create_1 = true;
			else
				stage_create_2 = true;
		}

		if (sf::IntRect(5, 229, 200, 120).contains(sf::Mouse::getPosition(window)))//MOVE AND CHANGE
		{
			BG_move_and_change.m_setActiveColor();
			move_and_change_text.m_setActiveColor();
			if (extra_menu == 0)
				stage_move_and_change_0 = true;
			else if (extra_menu == 1)
				stage_move_and_change_1 = true;
			else
				stage_move_and_change_2 = true;
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

			if (sf::IntRect(5, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_circle && menu_move_and_change_0)//obj_circle -> circle_random_move
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

			if (sf::IntRect(5, 510, 300, 160).contains(sf::Mouse::getPosition(window)) && submenu_obj_rect && menu_move_and_change_0)//obj_rectangle -> rect_change_dimensions
			{
				BG_ChangeWidthLength_obj_rectangle.m_setActiveColor();
				ChangeWidthLength_obj_rectangle_text.m_setActiveColor();
				stage_rect_change_dimensions = true;
			}
			if (sf::IntRect(495, 455, 160, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_rect && menu_move_and_change_0)//obj_rectangle -> delete
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
				BG_create_arrays_of_graphic_primitives.m_setActiveColor();
				create_arrays_of_graphic_primitives_text.m_setActiveColor();
				stage_create_arrays_of_graphic_primitives = true;
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
		else if (extra_menu == 1)
		{
			//ОБЪЕКТ ЭЛЛИПСА
			if (sf::IntRect(220, 97, 140, 40).contains(sf::Mouse::getPosition(window)) && menu_create_1)//CREATE -> ellipse
			{
				BG_ellipse.m_setActiveColor();
				ellipse_text.m_setActiveColor();
				stage_ellipse_create = true;
			}

			if (sf::IntRect(220, 229, 140, 40).contains(sf::Mouse::getPosition(window)) && menu_move_and_change_1)//MOVE AND CHANGE -> obj_ellipse
			{
				BG_obj_ellipse.m_setActiveColor();
				obj_ellipse_text.m_setActiveColor();
				stage_obj_ellipse = true;
			}

			if (sf::IntRect(5, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_ellipse && menu_move_and_change_1)//obj_ellipse -> ellipse_random_move
			{
				BG_RandomMove_obj_ellipse.m_setActiveColor();
				RandomMove_obj_ellipse_text.m_setActiveColor();
				stage_ellipse_random_move = true;
			}

			if (sf::IntRect(250, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_ellipse && menu_move_and_change_1)//obj_ellipse -> ellipse_user_move
			{
				BG_UserMove_obj_ellipse.m_setActiveColor();
				UserMove_obj_ellipse_text.m_setActiveColor();
				stage_ellipse_user_move = true;
			}

			if (sf::IntRect(5, 510, 320, 160).contains(sf::Mouse::getPosition(window)) && submenu_obj_ellipse && menu_move_and_change_1)//obj_ellipse -> ellipse_change_semi_axises:............
			{
				BG_ChangeDimensions_obj_ellipse.m_setActiveColor();
				ChangeDimensions_obj_ellipse_text.m_setActiveColor();
				stage_ellipse_change_dimensions = true;
			}
			if (sf::IntRect(495, 455, 160, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_ellipse && menu_move_and_change_1)//obj_ellipse -> delete
			{
				BG_delete_obj_ellipse.m_setActiveColor();
				delete_obj_ellipse_text.m_setActiveColor();
				stage_delete_obj_ellipse = true;
			}

			//ОБЪЕКТ РОМБА
			if (sf::IntRect(375, 97, 140, 40).contains(sf::Mouse::getPosition(window)) && menu_create_1)
			{
				BG_rhomb.m_setActiveColor();
				rhomb_text.m_setActiveColor();
				stage_rhomb_create = true;
			}
			if (sf::IntRect(375, 229, 160, 40).contains(sf::Mouse::getPosition(window)) && menu_move_and_change_1)
			{
				BG_obj_rhomb.m_setActiveColor();
				obj_rhomb_text.m_setActiveColor();
				stage_obj_rhomb = true;
			}

			if (sf::IntRect(5, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_rhomb && menu_move_and_change_1)
			{
				BG_RandomMove_obj_rhomb.m_setActiveColor();
				RandomMove_obj_rhomb_text.m_setActiveColor();
				stage_rhomb_random_move = true;
			}

			if (sf::IntRect(250, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_rhomb && menu_move_and_change_1)
			{
				BG_UserMove_obj_rhomb.m_setActiveColor();
				UserMove_obj_rhomb_text.m_setActiveColor();
				stage_rhomb_user_move = true;
			}

			if (sf::IntRect(5, 510, 300, 160).contains(sf::Mouse::getPosition(window)) && submenu_obj_rhomb && menu_move_and_change_1)
			{
				BG_ChangeDimensions_obj_rhomb.m_setActiveColor();
				ChangeDimensions_obj_rhomb_text.m_setActiveColor();
				stage_rhomb_change_dimensions = true;
			}
			if (sf::IntRect(495, 455, 160, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_rhomb && menu_move_and_change_1)
			{
				BG_delete_obj_rhomb.m_setActiveColor();
				delete_obj_rhomb_text.m_setActiveColor();
				stage_delete_obj_rhomb = true;
			}

			//ОБЪЕКТ ТРАПЕЦИИ
			if (sf::IntRect(529, 97, 165, 40).contains(sf::Mouse::getPosition(window)) && menu_create_1)
			{
				BG_trapeze.m_setActiveColor();
				trapeze_text.m_setActiveColor();
				stage_trapeze_create = true;
			}
			if (sf::IntRect(220, 280, 185, 40).contains(sf::Mouse::getPosition(window)) && menu_move_and_change_1)
			{
				BG_obj_trapeze.m_setActiveColor();
				obj_trapeze_text.m_setActiveColor();
				stage_obj_trapeze = true;
			}

			if (sf::IntRect(5, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_trapeze && menu_move_and_change_1)
			{
				BG_RandomMove_obj_trapeze.m_setActiveColor();
				RandomMove_obj_trapeze_text.m_setActiveColor();
				stage_trapeze_random_move = true;
			}

			if (sf::IntRect(250, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_trapeze && menu_move_and_change_1)
			{
				BG_UserMove_obj_trapeze.m_setActiveColor();
				UserMove_obj_trapeze_text.m_setActiveColor();
				stage_trapeze_user_move = true;
			}

			if (sf::IntRect(495, 455, 160, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_trapeze && menu_move_and_change_1)
			{
				BG_delete_obj_trapeze.m_setActiveColor();
				delete_obj_trapeze_text.m_setActiveColor();
				stage_delete_obj_trapeze = true;
			}

			if (sf::IntRect(5, 510, 300, 180).contains(sf::Mouse::getPosition(window)) && submenu_obj_trapeze && menu_move_and_change_1)
			{
				BG_ChangeDimensions_obj_trapeze.m_setActiveColor();
				ChangeDimensions_obj_trapeze_text.m_setActiveColor();
				stage_trapeze_change_dimensions = true;
			}

			//МАССИВЫ
			if (sf::IntRect(220, 160, 473, 40).contains(sf::Mouse::getPosition(window)) && menu_create_1)//CREATE -> create arrays of complex objects
			{
				BG_create_arrays_of_hereditary_objects.m_setActiveColor();
				create_arrays_of_hereditary_objects_text.m_setActiveColor();
				stage_create_arrays_of_hereditary_objects = true;
			}

			//Создание по 15 штук примитивов за нажатие кнопки
			if (sf::IntRect(500, 360, 200, 80).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)
			{
				BG_create_15_objs.m_setActiveColor();
				create_15_objs_text.m_setActiveColor();
				stage_create_15_objs = true;
			}

			//МАССИВ ЭЛЛИПСОВ
			if (sf::IntRect(5, 460, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//create arrays of hereditary objects -> array of ellipses
			{
				BG_create_array_ellipses.m_setActiveColor();
				create_array_ellipses_text.m_setActiveColor();
				stage_create_array_ellipses = true;
			}

			if (sf::IntRect(5, 520, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//array of ellipses -> random move(ellipses)
			{
				BG_RandomMove_array_ellipses.m_setActiveColor();
				RandomMove_array_ellipses_text.m_setActiveColor();
				stage_RandomMove_array_ellipses = true;
			}
			if (sf::IntRect(5, 580, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//array of ellipses -> user move(ellipses)
			{
				BG_UserMove_array_ellipses.m_setActiveColor();
				UserMove_array_ellipses_text.m_setActiveColor();
				stage_user_move_array_ellipses = true;
			}
			if (sf::IntRect(5, 640, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//array of ellipses -> delete_last ellipse
			{
				BG_delete_last_elem_array_ellipses.m_setActiveColor();
				delete_last_elem_array_ellipses_text.m_setActiveColor();
				stage_delete_last_elem_array_ellipses = true;
			}
			if (sf::IntRect(5, 700, 180, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//array of ellipses -> delete all ellipses
			{
				BG_delete_all_ellipses.m_setActiveColor();
				delete_all_ellipses_text.m_setActiveColor();
				stage_delete_all_ellipses = true;
			}

			//МАССИВ РОМБОВ
			if (sf::IntRect(197, 460, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)
			{
				BG_create_array_rhombs.m_setActiveColor();
				create_array_rhombs_text.m_setActiveColor();
				stage_create_array_rhombs = true;
			}

			if (sf::IntRect(197, 520, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)
			{
				BG_RandomMove_array_rhombs.m_setActiveColor();
				RandomMove_array_rhombs_text.m_setActiveColor();
				stage_RandomMove_array_rhombs = true;
			}

			if (sf::IntRect(197, 580, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)
			{
				BG_UserMove_array_rhombs.m_setActiveColor();
				UserMove_array_rhombs_text.m_setActiveColor();
				stage_user_move_array_rhombs = true;
			}

			if (sf::IntRect(197, 640, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)
			{
				BG_delete_last_elem_array_rhombs.m_setActiveColor();
				delete_last_elem_array_rhombs_text.m_setActiveColor();
				stage_delete_last_elem_array_rhombs = true;
			}

			if (sf::IntRect(197, 700, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)
			{
				BG_delete_all_rhombs.m_setActiveColor();
				delete_all_rhombs_text.m_setActiveColor();
				stage_delete_all_rhombs = true;
			}

			//МАССИВ ТРАПЕЦИЙ
			if (sf::IntRect(420, 460, 240, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)
			{
				BG_create_array_trapezes.m_setActiveColor();
				create_array_trapezes_text.m_setActiveColor();
				stage_create_array_trapezes = true;
			}

			if (sf::IntRect(420, 520, 240, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)
			{
				BG_RandomMove_array_trapezes.m_setActiveColor();
				RandomMove_array_trapezes_text.m_setActiveColor();
				stage_RandomMove_array_trapezes = true;
			}

			if (sf::IntRect(420, 580, 240, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)
			{
				BG_UserMove_array_trapezes.m_setActiveColor();
				UserMove_array_trapezes_text.m_setActiveColor();
				stage_user_move_array_trapezes = true;
			}

			if (sf::IntRect(420, 640, 240, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)
			{
				BG_delete_last_elem_array_trapezes.m_setActiveColor();
				delete_last_elem_array_trapezes_text.m_setActiveColor();
				stage_delete_last_elem_array_trapezes = true;
			}

			if (sf::IntRect(420, 700, 240, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)
			{
				BG_delete_all_trapezes.m_setActiveColor();
				delete_all_trapezes_text.m_setActiveColor();
				stage_delete_all_trapezes = true;
			}
		}
		else
		{
			//ОБЪЕКТ ЧЕТЫРЕХУГОЛЬНИКА
			if (sf::IntRect(220, 97, 180, 40).contains(sf::Mouse::getPosition(window)) && menu_create_2)
			{
				BG_quadrilateral.m_setActiveColor();
				quadrilateral_text.m_setActiveColor();
				stage_quadrilateral_create = true;
			}

			if (sf::IntRect(220, 229, 140, 40).contains(sf::Mouse::getPosition(window)) && menu_move_and_change_2)
			{
				BG_obj_quadrilateral.m_setActiveColor();
				obj_quadrilateral_text.m_setActiveColor();
				stage_obj_quadrilateral = true;
			}

			if (sf::IntRect(5, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_quadrilateral && menu_move_and_change_2)
			{
				BG_RandomMove_obj_quadrilateral.m_setActiveColor();
				RandomMove_obj_quadrilateral_text.m_setActiveColor();
				stage_quadrilateral_random_move = true;
			}

			if (sf::IntRect(250, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_quadrilateral && menu_move_and_change_2)
			{
				BG_UserMove_obj_quadrilateral.m_setActiveColor();
				UserMove_obj_quadrilateral_text.m_setActiveColor();
				stage_quadrilateral_user_move = true;
			}

			if (sf::IntRect(5, 510, 320, 160).contains(sf::Mouse::getPosition(window)) && submenu_obj_quadrilateral && menu_move_and_change_2)
			{
				BG_ChangeDimensions_obj_quadrilateral.m_setActiveColor();
				ChangeDimensions_obj_quadrilateral_text.m_setActiveColor();
				stage_quadrilateral_change_dimensions = true;
			}
			if (sf::IntRect(495, 455, 160, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_quadrilateral && menu_move_and_change_2)
			{
				BG_delete_obj_quadrilateral.m_setActiveColor();
				delete_obj_quadrilateral_text.m_setActiveColor();
				stage_delete_obj_quadrilateral = true;
			}

			//МАССИВЫ
			if (sf::IntRect(220, 160, 473, 40).contains(sf::Mouse::getPosition(window)) && menu_create_2)
			{
				BG_create_arrays_of_convex_polygons.m_setActiveColor();
				create_arrays_of_convex_polygons_text.m_setActiveColor();
				stage_create_arrays_of_convex_polygons = true;
			}

			//Создание по 15 штук примитивов за нажатие кнопки
			if (sf::IntRect(500, 360, 200, 80).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_2 && menu_create_2)
			{
				BG_create_15_objs.m_setActiveColor();
				create_15_objs_text.m_setActiveColor();
				stage_create_15_objs = true;
			}

			//МАССИВ ЧЕТЫРЕХНУГОЛЬНИКОВ
			if (sf::IntRect(5, 460, 245, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_2 && menu_create_2)
			{
				BG_create_array_quadrilaterals.m_setActiveColor();
				create_array_quadrilaterals_text.m_setActiveColor();
				stage_create_array_quadrilaterals = true;
			}

			if (sf::IntRect(5, 520, 245, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_2 && menu_create_2)
			{
				BG_RandomMove_array_quadrilaterals.m_setActiveColor();
				RandomMove_array_quadrilaterals_text.m_setActiveColor();
				stage_RandomMove_array_quadrilaterals = true;
			}
			if (sf::IntRect(5, 580, 245, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_2 && menu_create_2)
			{
				BG_UserMove_array_quadrilaterals.m_setActiveColor();
				UserMove_array_quadrilaterals_text.m_setActiveColor();
				stage_user_move_array_quadrilaterals = true;
			}
			if (sf::IntRect(5, 640, 245, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_2 && menu_create_2)
			{
				BG_delete_last_elem_array_quadrilaterals.m_setActiveColor();
				delete_last_elem_array_quadrilaterals_text.m_setActiveColor();
				stage_delete_last_elem_array_quadrilaterals = true;
			}
			if (sf::IntRect(5, 700, 245, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_2 && menu_create_2)
			{
				BG_delete_all_quadrilaterals.m_setActiveColor();
				delete_all_quadrilaterals_text.m_setActiveColor();
				stage_delete_all_quadrilaterals = true;
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
				if (stage_next && extra_menu != 2)
					extra_menu++;
				if (stage_back && extra_menu != 0)
					extra_menu--;
				//Нажата кнопка CREATE
				if (stage_create_0)
					menu_create_0 = !menu_create_0;
				if (stage_create_1)
					menu_create_1 = !menu_create_1;
				if (stage_create_2)
					menu_create_2 = !menu_create_2;
				//Нажата кнопка MOVE AND CHANGE
				if (stage_move_and_change_0)
					menu_move_and_change_0 = !menu_move_and_change_0;
				if (stage_move_and_change_1)
					menu_move_and_change_1 = !menu_move_and_change_1;
				if (stage_move_and_change_2)
					menu_move_and_change_2 = !menu_move_and_change_2;

				/*ЕДИНИЧНЫЕ ОБЪЕКТЫ*/
				//ОБЪЕКТ ОКРУЖНОСТИ
				//Нажата кнопка CREATE -> circle
				if (stage_circle_create)
				{
					circle_show = true;
					if (f_ptr_obj_circle == nullptr)
					{
						f_ptr_obj_circle = new TCircle();
					}
					else
					{
						float radius_circle{ getRandomNumber(10,100) };
						float x_circle{ getRandomNumber(720, 1485) };
						float y_circle{ getRandomNumber(110, 885) };
						f_ptr_obj_circle->Free(f_ptr_obj_circle);
						f_ptr_obj_circle = new TCircle(x_circle, y_circle, radius_circle);
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
						ellipse_user_move = false;
						array_ellipses_user_move = false;
						rhomb_user_move = false;
						array_rhombs_user_move = false;
						trapeze_user_move = false;
						array_trapezes_user_move = false;
						quadrilateral_user_move = false;
						array_quadrilaterals_user_move = false;
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
						f_ptr_obj_rect = new TRectangle();
					}
					else
					{
						float length_rect{ getRandomNumber(50, 300) };
						float width_rect{ getRandomNumber(25, 150) };
						float x_rect{ getRandomNumber(710, 1445) };
						float y_rect{ getRandomNumber(100, 870) };
						f_ptr_obj_rect->Free(f_ptr_obj_rect);
						f_ptr_obj_rect = new TRectangle(x_rect, y_rect, length_rect, width_rect);
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
						ellipse_user_move = false;
						array_ellipses_user_move = false;
						rhomb_user_move = false;
						array_rhombs_user_move = false;
						trapeze_user_move = false;
						array_trapezes_user_move = false;
						quadrilateral_user_move = false;
						array_quadrilaterals_user_move = false;
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
						f_ptr_obj_linesegment = new TLinesegment();
					}
					else
					{
						float length_linesegment{ getRandomNumber(100, 300) };
						float degree_linesegment{ getRandomNumber(0, 360) };
						degree_linesegment = static_cast<float>(static_cast<int>(degree_linesegment));
						float x_linesegment{ getRandomNumber(710, 1495) };
						float y_linesegment{ getRandomNumber(100, 895) };
						f_ptr_obj_linesegment->Free(f_ptr_obj_linesegment);
						f_ptr_obj_linesegment = new TLinesegment(x_linesegment, y_linesegment, length_linesegment, degree_linesegment);
						f_ptr_obj_linesegment->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
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
						ellipse_user_move = false;
						array_ellipses_user_move = false;
						rhomb_user_move = false;
						array_rhombs_user_move = false;
						trapeze_user_move = false;
						array_trapezes_user_move = false;
						quadrilateral_user_move = false;
						array_quadrilaterals_user_move = false;
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

				//ОБЪЕКТ ЭЛЛИПСА
				//Нажата кнопка CREATE -> ellipse
				if (stage_ellipse_create)
				{
					ellipse_show = true;
					if (f_ptr_obj_ellipse == nullptr)
					{
						f_ptr_obj_ellipse = new TEllipse();
					}
					else
					{
						float x_ellipse{ getRandomNumber(770, 1435) };
						float y_ellipse{ getRandomNumber(130, 835) };
						float ellipse_semi_major_axis{ getRandomNumber(60, 150) };
						float ellipse_semi_minor_axis{ getRandomNumber(30, ellipse_semi_major_axis - 10) };
						f_ptr_obj_ellipse->Free(f_ptr_obj_ellipse);
						f_ptr_obj_ellipse = new TEllipse(x_ellipse, y_ellipse, ellipse_semi_major_axis, ellipse_semi_minor_axis);
						f_ptr_obj_ellipse->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_ellipse->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_ellipse->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
					}
				}
				if (ellipse_show)
				{
					//Нажата кнопка MOVE AND CHANGE -> obj_ellipse
					if (stage_obj_ellipse)
					{
						submenu_obj_ellipse = !submenu_obj_ellipse;
						submenu_obj_rhomb = false;
						submenu_obj_trapeze = false;
						submenu_create_arrays_1 = false;
					}
					//Нажата кнопка ellipse -> ellipse_random_move
					if (stage_ellipse_random_move)
						doOffsetEllipse(f_ptr_obj_ellipse);
					//Нажата кнопка obj_ellipse -> ellipse_user_move
					if (stage_ellipse_user_move)
					{
						ellipse_user_move = !ellipse_user_move;
						circle_user_move = false;
						array_circles_user_move = false;
						rect_user_move = false;
						array_rectangles_user_move = false;
						linesegment_user_move = false;
						array_linesegments_user_move = false;
						rhomb_user_move = false;
						array_rhombs_user_move = false;
						trapeze_user_move = false;
						array_trapezes_user_move = false;
						quadrilateral_user_move = false;
						array_quadrilaterals_user_move = false;
					}
					//Нажата кнопка изменения размеров obj_ellipse -> изменить размеры
					if (stage_ellipse_change_dimensions)
						ellipse_change_dimensions = !ellipse_change_dimensions;
					//Нажата кнопка удаления объекта эллипса obj_ellipse -> delete
					if (stage_delete_obj_ellipse)
					{
						delete f_ptr_obj_ellipse;
						f_ptr_obj_ellipse = nullptr;
						ellipse_show = false;
						submenu_obj_ellipse = false;
						ellipse_user_move = false;
						ellipse_change_dimensions = false;
					}
				}

				//ОБЪЕКТ РОМБА
				//Нажата кнопка CREATE -> rhomb
				if (stage_rhomb_create)
				{
					rhomb_show = true;
					if (f_ptr_obj_rhomb == nullptr)
					{
						f_ptr_obj_rhomb = new TRhomb();
					}
					else
					{
						float rhomb_length{ getRandomNumber(60, 150) };
						int rhomb_degree{ static_cast<int>(getRandomNumber(30, 60)) };
						float x_rhomb{ getRandomNumber(710, 1495 - 2 * rhomb_length * cos(rhomb_degree * PI / 180)) };
						float y_rhomb{ getRandomNumber(100 + rhomb_length * sin(rhomb_degree * PI / 180), 895 - rhomb_length * sin(rhomb_degree * PI / 180)) };
						f_ptr_obj_rhomb->Free(f_ptr_obj_rhomb);
						f_ptr_obj_rhomb = new TRhomb(x_rhomb, y_rhomb, rhomb_length, rhomb_degree);
						f_ptr_obj_rhomb->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_rhomb->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_rhomb->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
					}
				}
				if (rhomb_show)
				{
					//Нажата кнопка MOVE AND CHANGE -> obj_rhomb
					if (stage_obj_rhomb)
					{
						submenu_obj_rhomb = !submenu_obj_rhomb;
						submenu_obj_ellipse = false;
						submenu_obj_trapeze = false;
						submenu_create_arrays_1 = false;
					}
					//Нажата кнопка rhomb -> rhomb_random_move
					if (stage_rhomb_random_move)
						doOffsetRhomb(f_ptr_obj_rhomb);
					//Нажата кнопка obj_rhomb -> rhomb_user_move
					if (stage_rhomb_user_move)
					{
						rhomb_user_move = !rhomb_user_move;
						circle_user_move = false;
						array_circles_user_move = false;
						rect_user_move = false;
						array_rectangles_user_move = false;
						linesegment_user_move = false;
						array_linesegments_user_move = false;
						ellipse_user_move = false;
						array_ellipses_user_move = false;
						trapeze_user_move = false;
						array_trapezes_user_move = false;
						quadrilateral_user_move = false;
						array_quadrilaterals_user_move = false;
					}
					//Нажата кнопка изменения размеров obj_rhomb -> изменить размеры
					if (stage_rhomb_change_dimensions)
						rhomb_change_dimensions = !rhomb_change_dimensions;
					//Нажата кнопка удаления объекта эллипса obj_rhomb -> delete
					if (stage_delete_obj_rhomb)
					{
						delete f_ptr_obj_rhomb;
						f_ptr_obj_rhomb = nullptr;
						rhomb_show = false;
						submenu_obj_rhomb = false;
						rhomb_user_move = false;
						rhomb_change_dimensions = false;
					}
				}

				//ОБЪЕКТ ТРАПЕЦИИ
				//нажата кнопка CREATE -> trapeze
				if (stage_trapeze_create)
				{
					trapeze_show = true;
					if (f_ptr_obj_trapeze == nullptr)
					{
						f_ptr_obj_trapeze = new TTrapeze();
					}
					else
					{
						int degree{ static_cast<int>(getRandomNumber(30, 90)) };
						float height{ getRandomNumber(50, 80) };
						float bottom_base_length{ getRandomNumber(130, 300) };
						float top_base_length{ getRandomNumber(60, bottom_base_length - height / tan(degree * PI / 180)) };
						float x_trapeze{ getRandomNumber(710, 1495 - bottom_base_length) };
						float y_trapeze{ getRandomNumber(100 + height, 895) };
						f_ptr_obj_trapeze->Free(f_ptr_obj_trapeze);
						f_ptr_obj_trapeze = new TTrapeze(x_trapeze, y_trapeze, degree, bottom_base_length, top_base_length, height);
						f_ptr_obj_trapeze->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_trapeze->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_trapeze->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
					}
				}
				if (trapeze_show)
				{
					//Нажата кнопка MOVE AND CHANGE -> obj_trapeze
					if (stage_obj_trapeze)
					{
						submenu_obj_trapeze = !submenu_obj_trapeze;
						submenu_obj_ellipse = false;
						submenu_obj_rhomb = false;
						submenu_create_arrays_1 = false;
					}
					//Нажата кнопка trapeze -> trapeze_random_move
					if (stage_trapeze_random_move)
						doOffsetTrapeze(f_ptr_obj_trapeze);
					//Нажата кнопка obj_trapeze -> trapeze_user_move
					if (stage_trapeze_user_move)
					{
						trapeze_user_move = !trapeze_user_move;
						circle_user_move = false;
						array_circles_user_move = false;
						rect_user_move = false;
						array_rectangles_user_move = false;
						linesegment_user_move = false;
						array_linesegments_user_move = false;
						ellipse_user_move = false;
						array_ellipses_user_move = false;
						rhomb_user_move = false;
						array_rhombs_user_move = false;
						quadrilateral_user_move = false;
						array_quadrilaterals_user_move = false;
					}
					//Нажата кнопка изменения размеров obj_trapeze -> изменить размеры
					if (stage_trapeze_change_dimensions)
						trapeze_change_dimensions = !trapeze_change_dimensions;
					//Нажата кнопка удаления объекта трапеции obj_trapeze -> delete
					if (stage_delete_obj_trapeze)
					{
						delete f_ptr_obj_trapeze;
						f_ptr_obj_trapeze = nullptr;
						trapeze_show = false;
						submenu_obj_trapeze = false;
						trapeze_user_move = false;
						trapeze_change_dimensions = false;
					}
				}

				//ОБЪЕКТ ЧЕТЫРЕХУГОЛЬНИКА
				//Нажата кнопка CREATE -> quadrilateral
				if (stage_quadrilateral_create)
				{
					quadrilateral_show = true;
					if (f_ptr_obj_quadrilateral == nullptr)
					{
						f_ptr_obj_quadrilateral = new TQuadrilateral();
					}
					else
					{
						float corner_x1{ getRandomNumber(725, 1395) };
						float corner_x2{ getRandomNumber(corner_x1 + 50, corner_x1 + 100) };
						float corner_x3{ getRandomNumber(corner_x1 + 50, corner_x1 + 100) };
						float corner_x4{ getRandomNumber(corner_x1 - 25, corner_x3 - 50) };
						float corner_y1{ getRandomNumber(125, 770) };
						float corner_y2{ getRandomNumber(corner_y1 - 25, corner_y1 + 25) };
						float corner_y3{ getRandomNumber(corner_y2 + 50, corner_y2 + 100) };
						float corner_y4{ getRandomNumber(corner_y1 + 50, corner_y1 + 100) };
						f_ptr_obj_quadrilateral->Free(f_ptr_obj_quadrilateral);
						f_ptr_obj_quadrilateral = new TQuadrilateral(corner_x1, corner_y1, corner_x2, corner_y2, corner_x3, corner_y3, corner_x4, corner_y4);
						f_ptr_obj_quadrilateral->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_quadrilateral->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_quadrilateral->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
					}
				}
				if (quadrilateral_show)
				{
					//Нажата кнопка MOVE AND CHANGE -> obj_quadrilateral
					if (stage_obj_quadrilateral)
					{
						submenu_obj_quadrilateral = !submenu_obj_quadrilateral;
						submenu_create_arrays_2 = false;
					}
					//Нажата кнопка quadrilateral -> quadrilateral_random_move
					if (stage_quadrilateral_random_move)
						doOffsetQuadrilateral(f_ptr_obj_quadrilateral);
					//Нажата кнопка obj_quadrilateral -> quadrilateral_user_move
					if (stage_quadrilateral_user_move)
					{
						quadrilateral_user_move = !quadrilateral_user_move;
						circle_user_move = false;
						array_circles_user_move = false;
						rect_user_move = false;
						array_rectangles_user_move = false;
						linesegment_user_move = false;
						array_linesegments_user_move = false;
						ellipse_user_move = false;
						array_ellipses_user_move = false;
						rhomb_user_move = false;
						array_rhombs_user_move = false;
						trapeze_user_move = false;
						array_trapezes_user_move = false;
					}
					//Нажата кнопка изменения размеров obj_quadrilateral -> изменить размеры
					if (stage_quadrilateral_change_dimensions)
						quadrilateral_change_dimensions = !quadrilateral_change_dimensions;
					//Нажата кнопка удаления объекта четырехугольника obj_quadrilateral -> delete
					if (stage_delete_obj_quadrilateral)
					{
						delete f_ptr_obj_quadrilateral;
						f_ptr_obj_quadrilateral = nullptr;
						quadrilateral_show = false;
						submenu_obj_quadrilateral = false;
						quadrilateral_user_move = false;
						quadrilateral_change_dimensions = false;
					}
				}

				/*МАССИВЫ ГРАФИЧЕСКИХ ПРИМИТИВОВ*/
				//Нажата кнопка CREATE -> create arrays of graphics primitives
				if (stage_create_arrays_of_graphic_primitives)
				{
					submenu_create_arrays_0 = !submenu_create_arrays_0;
					submenu_obj_circle = false;
					submenu_obj_rect = false;
					submenu_obj_linesegment = false;
				}

				if (stage_create_arrays_of_hereditary_objects)
				{
					submenu_create_arrays_1 = !submenu_create_arrays_1;
					submenu_obj_ellipse = false;
					submenu_obj_rhomb = false;
					submenu_obj_trapeze = false;
				}

				if (stage_create_arrays_of_convex_polygons)
				{
					submenu_create_arrays_2 = !submenu_create_arrays_2;
					submenu_obj_quadrilateral = false;
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
						TCircle* ptr_new_elem_array_circles{ nullptr };
						float radius_circle{ getRandomNumber(10,100) };
						float x_circle{ getRandomNumber(720, 1485) };
						float y_circle{ getRandomNumber(110, 885) };
						ptr_new_elem_array_circles = new TCircle(x_circle, y_circle, radius_circle);
						ptr_new_elem_array_circles->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_circles->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_circles->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						push_back_shapes<TCircle>(array_circles, array_circles_size, ptr_new_elem_array_circles);
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
						ellipse_user_move = false;
						array_ellipses_user_move = false;
						rhomb_user_move = false;
						array_rhombs_user_move = false;
						trapeze_user_move = false;
						array_trapezes_user_move = false;
						quadrilateral_user_move = false;
						array_quadrilaterals_user_move = false;
					}
					if (stage_delete_last_elem_array_circles && (array_circles_size > 0))
					{
						pop_back_shapes<TCircle>(array_circles, array_circles_size);
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
							pop_back_shapes<TCircle>(array_circles, array_circles_size);
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
						TRectangle* ptr_new_elem_array_rectangles{ nullptr };
						float length_rect{ getRandomNumber(50, 300) };
						float width_rect{ getRandomNumber(25, 150) };
						float x_rect{ getRandomNumber(710, 1445) };
						float y_rect{ getRandomNumber(100, 870) };
						ptr_new_elem_array_rectangles = new TRectangle(x_rect, y_rect, length_rect, width_rect);
						ptr_new_elem_array_rectangles->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_rectangles->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_rectangles->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						push_back_shapes<TRectangle>(array_rectangles, array_rectangles_size, ptr_new_elem_array_rectangles);
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
						ellipse_user_move = false;
						array_ellipses_user_move = false;
						rhomb_user_move = false;
						array_rhombs_user_move = false;
						trapeze_user_move = false;
						array_trapezes_user_move = false;
						quadrilateral_user_move = false;
						array_quadrilaterals_user_move = false;
					}
					if (stage_delete_last_elem_array_rectangles && (array_rectangles_size > 0))
					{
						pop_back_shapes<TRectangle>(array_rectangles, array_rectangles_size);
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
							pop_back_shapes<TRectangle>(array_rectangles, array_rectangles_size);
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
						TLinesegment* ptr_new_elem_array_linesegments{ nullptr };
						float length_linesegment{ getRandomNumber(100, 300) };
						float degree_linesegment{ getRandomNumber(0, 360) };
						degree_linesegment = static_cast<float>(static_cast<int>(degree_linesegment));
						float x_linesegment{ getRandomNumber(710, 1495) };
						float y_linesegment{ getRandomNumber(100, 895) };
						ptr_new_elem_array_linesegments = new TLinesegment(x_linesegment, y_linesegment, length_linesegment, degree_linesegment);
						ptr_new_elem_array_linesegments->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_linesegments->setVisibility(static_cast<int>(getRandomNumber(150, 255)));
						push_back_shapes<TLinesegment>(array_linesegments, array_linesegments_size, ptr_new_elem_array_linesegments);
					}
				}
				if (array_linesegments_show)
				{
					if (stage_RandomMove_array_linesegments)
						for (int i{}; i < array_linesegments_size; i++)
							doOffsetArrayLinesegments(array_linesegments, i);
					if (stage_user_move_array_linesegments)
					{
						array_linesegments_user_move = !array_linesegments_user_move;
						circle_user_move = false;
						array_circles_user_move = false;
						rect_user_move = false;
						array_rectangles_user_move = false;
						ellipse_user_move = false;
						array_ellipses_user_move = false;
						rhomb_user_move = false;
						array_rhombs_user_move = false;
						trapeze_user_move = false;
						array_trapezes_user_move = false;
						quadrilateral_user_move = false;
						array_quadrilaterals_user_move = false;
					}
					if (stage_delete_last_elem_array_linesegments && (array_linesegments_size > 0))
					{
						pop_back_shapes<TLinesegment>(array_linesegments, array_linesegments_size);
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
							pop_back_shapes<TLinesegment>(array_linesegments, array_linesegments_size);
						array_linesegments_show = false;
						array_linesegments_user_move = false;
					}
				}

				//МАССИВ ЭЛЛИПСОВ
				//Нажата кнопка create arrays of heredatiry objects -> array of ellipses
				if (stage_create_array_ellipses)
				{
					array_ellipses_show = true;
					for (int i{}; i < mass_or_single; i++)
					{
						TEllipse* ptr_new_elem_array_ellipses{ nullptr };
						float x_ellipse{ getRandomNumber(770, 1435) };
						float y_ellipse{ getRandomNumber(130, 865) };
						float ellipse_semi_major_axis{ getRandomNumber(60, 150) };
						float ellipse_semi_minor_axis{ getRandomNumber(30, ellipse_semi_major_axis - 10) };
						ptr_new_elem_array_ellipses = new TEllipse(x_ellipse, y_ellipse, ellipse_semi_major_axis, ellipse_semi_minor_axis);
						ptr_new_elem_array_ellipses->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_ellipses->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_ellipses->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						push_back_shapes<TEllipse>(array_ellipses, array_ellipses_size, ptr_new_elem_array_ellipses);
					}
				}
				if (array_ellipses_show)
				{
					if (stage_RandomMove_array_ellipses)
						doOffsetArrayEllipses(array_ellipses, array_ellipses_size);
					if (stage_user_move_array_ellipses)
					{
						array_ellipses_user_move = !array_ellipses_user_move;
						circle_user_move = false;
						rect_user_move = false;
						linesegment_user_move = false;
						array_circles_user_move = false;
						array_rectangles_user_move = false;
						array_linesegments_user_move = false;
						rhomb_user_move = false;
						array_rhombs_user_move = false;
						trapeze_user_move = false;
						array_trapezes_user_move = false;
						quadrilateral_user_move = false;
						array_quadrilaterals_user_move = false;
					}
					if (stage_delete_last_elem_array_ellipses && (array_ellipses_size > 0))
					{
						pop_back_shapes<TEllipse>(array_ellipses, array_ellipses_size);
						if (array_ellipses_size == 0)
						{
							array_ellipses_show = false;
							array_ellipses_user_move = false;
						}
					}
					if (stage_delete_all_ellipses)
					{
						int array_ellipses_size_temp{ array_ellipses_size };
						for (int i{}; i < array_ellipses_size_temp; i++)
							pop_back_shapes<TEllipse>(array_ellipses, array_ellipses_size);
						array_ellipses_show = false;
						array_ellipses_user_move = false;
					}
				}

				//МАССИВ РОМБОВ
				//Нажата кнопка create arrays of heredatiry objects -> array of rhombs
				if (stage_create_array_rhombs)
				{
					array_rhombs_show = true;
					for (int i{}; i < mass_or_single; i++)
					{
						TRhomb* ptr_new_elem_array_rhombs{ nullptr };
						float rhomb_length{ getRandomNumber(60, 150) };
						int rhomb_degree{ static_cast<int>(getRandomNumber(30, 60)) };
						float x_rhomb{ getRandomNumber(710, 1495 - 2 * rhomb_length * cos(rhomb_degree * PI / 180)) };
						float y_rhomb{ getRandomNumber(100 + rhomb_length * sin(rhomb_degree * PI / 180), 895 - rhomb_length * sin(rhomb_degree * PI / 180)) };
						ptr_new_elem_array_rhombs = new TRhomb(x_rhomb, y_rhomb, rhomb_length, rhomb_degree);
						ptr_new_elem_array_rhombs->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_rhombs->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_rhombs->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						push_back_shapes<TRhomb>(array_rhombs, array_rhombs_size, ptr_new_elem_array_rhombs);
					}
				}
				if (array_rhombs_show)
				{
					if (stage_RandomMove_array_rhombs)
						doOffsetArrayRhombs(array_rhombs, array_rhombs_size);
					if (stage_user_move_array_rhombs)
					{
						array_rhombs_user_move = !array_rhombs_user_move;
						circle_user_move = false;
						rect_user_move = false;
						linesegment_user_move = false;
						array_circles_user_move = false;
						array_rectangles_user_move = false;
						array_linesegments_user_move = false;
						ellipse_user_move = false;
						array_ellipses_user_move = false;
						trapeze_user_move = false;
						array_trapezes_user_move = false;
						quadrilateral_user_move = false;
						array_quadrilaterals_user_move = false;
					}
					if (stage_delete_last_elem_array_rhombs && (array_rhombs_size > 0))
					{
						pop_back_shapes<TRhomb>(array_rhombs, array_rhombs_size);
						if (array_rhombs_size == 0)
						{
							array_rhombs_show = false;
							array_rhombs_user_move = false;
						}
					}
					if (stage_delete_all_rhombs)
					{
						int array_rhombs_size_temp{ array_rhombs_size };
						for (int i{}; i < array_rhombs_size_temp; i++)
							pop_back_shapes<TRhomb>(array_rhombs, array_rhombs_size);
						array_rhombs_show = false;
						array_rhombs_user_move = false;
					}
				}

				//МАССИВ ТРАПЕЦИЙ
				if (stage_create_array_trapezes)
				{
					array_trapezes_show = true;
					for (int i{}; i < mass_or_single; i++)
					{
						TTrapeze* ptr_new_elem_array_trapezes{ nullptr };
						int degree{ static_cast<int>(getRandomNumber(30, 90)) };
						float height{ getRandomNumber(50, 80) };
						float bottom_base_length{ getRandomNumber(130, 300) };
						float top_base_length{ getRandomNumber(60, bottom_base_length - height / tan(degree * PI / 180)) };
						float x_trapeze{ getRandomNumber(710, 1495 - bottom_base_length) };
						float y_trapeze{ getRandomNumber(100 + height, 895) };
						ptr_new_elem_array_trapezes = new TTrapeze(x_trapeze, y_trapeze, degree, bottom_base_length, top_base_length, height);
						ptr_new_elem_array_trapezes->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_trapezes->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_trapezes->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						push_back_shapes<TTrapeze>(array_trapezes, array_trapezes_size, ptr_new_elem_array_trapezes);
					}
				}
				if (array_trapezes_show)
				{
					if (stage_RandomMove_array_trapezes)
						doOffsetArrayTrapezes(array_trapezes, array_trapezes_size);
					if (stage_user_move_array_trapezes)
					{
						array_trapezes_user_move = !array_trapezes_user_move;
						circle_user_move = false;
						rect_user_move = false;
						linesegment_user_move = false;
						array_circles_user_move = false;
						array_rectangles_user_move = false;
						array_linesegments_user_move = false;
						ellipse_user_move = false;
						array_ellipses_user_move = false;
						rhomb_user_move = false;
						array_rhombs_user_move = false;
						quadrilateral_user_move = false;
						array_quadrilaterals_user_move = false;
					}
					if (stage_delete_last_elem_array_trapezes && (array_trapezes_size > 0))
					{
						pop_back_shapes<TTrapeze>(array_trapezes, array_trapezes_size);
						if (array_trapezes_size == 0)
						{
							array_trapezes_show = false;
							array_trapezes_user_move = false;
						}
					}
					if (stage_delete_all_trapezes)
					{
						int array_trapezes_size_temp{ array_trapezes_size };
						for (int i{}; i < array_trapezes_size_temp; i++)
							pop_back_shapes<TTrapeze>(array_trapezes, array_trapezes_size);
						array_trapezes_show = false;
						array_trapezes_user_move = false;
					}
				}

				//МАССИВ ЧЕТЫРЕХУГОЛЬНИКОВ
				if (stage_create_array_quadrilaterals)
				{
					array_quadrilaterals_show = true;
					for (int i{}; i < mass_or_single; i++)
					{
						TQuadrilateral* ptr_new_elem_array_quadrilateral{ nullptr };
						float corner_x1{ getRandomNumber(725, 1395) };
						float corner_x2{ getRandomNumber(corner_x1 + 50, corner_x1 + 100) };
						float corner_x3{ getRandomNumber(corner_x1 + 50, corner_x1 + 100) };
						float corner_x4{ getRandomNumber(corner_x1 - 25, corner_x3 - 50) };
						float corner_y1{ getRandomNumber(125, 770) };
						float corner_y2{ getRandomNumber(corner_y1 - 25, corner_y1 + 25) };
						float corner_y3{ getRandomNumber(corner_y2 + 50, corner_y2 + 100) };
						float corner_y4{ getRandomNumber(corner_y1 + 50, corner_y1 + 100) };
						ptr_new_elem_array_quadrilateral = new TQuadrilateral(corner_x1, corner_y1, corner_x2, corner_y2, corner_x3, corner_y3, corner_x4, corner_y4);
						ptr_new_elem_array_quadrilateral->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_quadrilateral->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_quadrilateral->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						push_back_shapes<TQuadrilateral>(array_quadrilaterals, array_quadrilaterals_size, ptr_new_elem_array_quadrilateral);
					}
				}
				if (array_quadrilaterals_show)
				{
					if (stage_RandomMove_array_quadrilaterals)
						doOffsetArrayQuadrilaterals(array_quadrilaterals, array_quadrilaterals_size);
					if (stage_user_move_array_quadrilaterals)
					{
						array_quadrilaterals_user_move = !array_quadrilaterals_user_move;
						circle_user_move = false;
						rect_user_move = false;
						linesegment_user_move = false;
						array_circles_user_move = false;
						array_rectangles_user_move = false;
						array_linesegments_user_move = false;
						ellipse_user_move = false;
						array_ellipses_user_move = false;
						rhomb_user_move = false;
						array_rhombs_user_move = false;
					}
					if (stage_delete_last_elem_array_quadrilaterals && (array_quadrilaterals_size > 0))
					{
						pop_back_shapes<TQuadrilateral>(array_quadrilaterals, array_quadrilaterals_size);
						if (array_quadrilaterals_size == 0)
						{
							array_quadrilaterals_show = false;
							array_quadrilaterals_user_move = false;
						}
					}
					if (stage_delete_all_quadrilaterals)
					{
						int array_quadrilaterals_size_temp{ array_quadrilaterals_size };
						for (int i{}; i < array_quadrilaterals_size_temp; i++)
							pop_back_shapes<TQuadrilateral>(array_quadrilaterals, array_quadrilaterals_size);
						array_quadrilaterals_show = false;
						array_quadrilaterals_user_move = false;
					}
				}

				if (!submenu_create_arrays_0 && !submenu_create_arrays_1 && !submenu_create_arrays_2)
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
					if (event_menu_click.key.code == sf::Keyboard::W && (f_ptr_obj_circle->getYPoint() - f_ptr_obj_circle->getRadius() - 10 >= 100))
						f_ptr_obj_circle->MoveTo(0, -10);
					if (event_menu_click.key.code == sf::Keyboard::A && (f_ptr_obj_circle->getXPoint() - f_ptr_obj_circle->getRadius() - 10 >= 710))
						f_ptr_obj_circle->MoveTo(-10, 0);
					if (event_menu_click.key.code == sf::Keyboard::S && (f_ptr_obj_circle->getYPoint() + f_ptr_obj_circle->getRadius() + 10 <= 895))
						f_ptr_obj_circle->MoveTo(0, 10);
					if (event_menu_click.key.code == sf::Keyboard::D && (f_ptr_obj_circle->getXPoint() + f_ptr_obj_circle->getRadius() + 10 <= 1495))
						f_ptr_obj_circle->MoveTo(10, 0);
				}

				if (rect_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W && (f_ptr_obj_rect->getYPoint() - 10 >= 100))
					{
						f_ptr_obj_rect->MoveTo(0, -10);
						f_ptr_obj_rect->changeBasePoints234(0, -10);
					}
					if (event_menu_click.key.code == sf::Keyboard::A && (f_ptr_obj_rect->getXPoint() - 10 >= 710))
					{
						f_ptr_obj_rect->MoveTo(-10, 0);
						f_ptr_obj_rect->changeBasePoints234(-10, 0);
					}
					if (event_menu_click.key.code == sf::Keyboard::S && (f_ptr_obj_rect->getYPoint() + f_ptr_obj_rect->getWidth() + 10 <= 895))
					{
						f_ptr_obj_rect->MoveTo(0, 10);
						f_ptr_obj_rect->changeBasePoints234(0, 10);
					}
					if (event_menu_click.key.code == sf::Keyboard::D && (f_ptr_obj_rect->getXPoint() + f_ptr_obj_rect->getLength() + 10 <= 1495))
					{
						f_ptr_obj_rect->MoveTo(10, 0);
						f_ptr_obj_rect->changeBasePoints234(10, 0);
					}
				}
				if (linesegment_user_move)
				{
					int degree_linesegment{ static_cast<int>(f_ptr_obj_linesegment->getDegree()) };
					float x_linesegment{ f_ptr_obj_linesegment->getXPoint() };
					float y_linesegment{ f_ptr_obj_linesegment->getYPoint() };
					float length_linesegment{ f_ptr_obj_linesegment->getLength() };
					float alpha_linesegment{ degree_linesegment * PI / 180 };
					if (event_menu_click.key.code == sf::Keyboard::W)
					{
						if (degree_linesegment % 360 >= 180 && degree_linesegment % 360 <= 360 || degree_linesegment % 360 >= -180 && degree_linesegment % 360 <= 0)
						{
							if ((y_linesegment + length_linesegment * sin(alpha_linesegment) - 10) >= 100)
								f_ptr_obj_linesegment->MoveTo(0, -10);
						}
						else if ((y_linesegment - 10) >= 100)
						{
							f_ptr_obj_linesegment->MoveTo(0, -10);
						}
					}
					if (event_menu_click.key.code == sf::Keyboard::A)
					{
						if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -90)
						{
							if ((x_linesegment + length_linesegment * cos(alpha_linesegment) - 10) >= 710)
								f_ptr_obj_linesegment->MoveTo(-10, 0);
						}
						else if ((x_linesegment - 10) >= 710)
						{
							f_ptr_obj_linesegment->MoveTo(-10, 0);
						}
					}
					if (event_menu_click.key.code == sf::Keyboard::S)
					{
						if (degree_linesegment % 360 >= 0 && degree_linesegment % 360 <= 180 || degree_linesegment % 360 >= -360 && degree_linesegment % 360 <= -180)
						{
							if ((y_linesegment + length_linesegment * sin(alpha_linesegment) + 10) <= 895)
								f_ptr_obj_linesegment->MoveTo(0, 10);
						}
						else if ((y_linesegment + 10) <= 895)
						{
							f_ptr_obj_linesegment->MoveTo(0, 10);
						}
					}
					if (event_menu_click.key.code == sf::Keyboard::D)
					{
						if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -90)
						{
							if ((x_linesegment + 10) <= 1495)
								f_ptr_obj_linesegment->MoveTo(10, 0);
						}
						else if ((x_linesegment + length_linesegment * cos(alpha_linesegment) + 10) <= 1495)
						{
							f_ptr_obj_linesegment->MoveTo(10, 0);
						}
					}
				}

				if (ellipse_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W && (f_ptr_obj_ellipse->getYPoint() - f_ptr_obj_ellipse->getSemiMinorAxis() - 10 >= 100))
						f_ptr_obj_ellipse->MoveTo(0, -10);
					if (event_menu_click.key.code == sf::Keyboard::A && (f_ptr_obj_ellipse->getXPoint() - f_ptr_obj_ellipse->getRadius() - 10 >= 710))
						f_ptr_obj_ellipse->MoveTo(-10, 0);
					if (event_menu_click.key.code == sf::Keyboard::S && (f_ptr_obj_ellipse->getYPoint() + f_ptr_obj_ellipse->getSemiMinorAxis() + 10 <= 895))
						f_ptr_obj_ellipse->MoveTo(0, 10);
					if (event_menu_click.key.code == sf::Keyboard::D && (f_ptr_obj_ellipse->getXPoint() + f_ptr_obj_ellipse->getRadius() + 10 <= 1495))
						f_ptr_obj_ellipse->MoveTo(10, 0);
				}

				if (rhomb_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W && (f_ptr_obj_rhomb->getY2Point() - 10 >= 100))
					{
						f_ptr_obj_rhomb->MoveTo(0, -10);
						f_ptr_obj_rhomb->changeBasePoints234(0, -10);
					}
					if (event_menu_click.key.code == sf::Keyboard::A && (f_ptr_obj_rhomb->getXPoint() - 10 >= 710))
					{
						f_ptr_obj_rhomb->MoveTo(-10, 0);
						f_ptr_obj_rhomb->changeBasePoints234(-10, 0);
					}
					if (event_menu_click.key.code == sf::Keyboard::S && (f_ptr_obj_rhomb->getY4Point() + 10 <= 895))
					{
						f_ptr_obj_rhomb->MoveTo(0, 10);
						f_ptr_obj_rhomb->changeBasePoints234(0, 10);
					}
					if (event_menu_click.key.code == sf::Keyboard::D && (f_ptr_obj_rhomb->getX3Point() + 10 <= 1495))
					{
						f_ptr_obj_rhomb->MoveTo(10, 0);
						f_ptr_obj_rhomb->changeBasePoints234(10, 0);
					}
				}

				if (trapeze_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W && (f_ptr_obj_trapeze->getY2Point() - 10 >= 100) && (f_ptr_obj_trapeze->getY3Point() - 10 >= 100))
					{
						f_ptr_obj_trapeze->MoveTo(0, -10);
						f_ptr_obj_trapeze->changeBasePoints234(0, -10);
					}
					if (event_menu_click.key.code == sf::Keyboard::A && (f_ptr_obj_trapeze->getXPoint() - 10 >= 710))
					{
						f_ptr_obj_trapeze->MoveTo(-10, 0);
						f_ptr_obj_trapeze->changeBasePoints234(-10, 0);
					}
					if (event_menu_click.key.code == sf::Keyboard::S && (f_ptr_obj_trapeze->getYPoint() + 10 <= 895) && (f_ptr_obj_trapeze->getY4Point() + 10 <= 895))
					{
						f_ptr_obj_trapeze->MoveTo(0, 10);
						f_ptr_obj_trapeze->changeBasePoints234(0, 10);
					}
					if (event_menu_click.key.code == sf::Keyboard::D && (f_ptr_obj_trapeze->getX4Point() + 10 <= 1495) && (f_ptr_obj_trapeze->getX3Point() + 10 <= 1495))
					{
						f_ptr_obj_trapeze->MoveTo(10, 0);
						f_ptr_obj_trapeze->changeBasePoints234(10, 0);
					}
				}

				if (quadrilateral_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W && (f_ptr_obj_quadrilateral->getYPoint() - 10 >= 100) && (f_ptr_obj_quadrilateral->getY2Point() - 10 >= 100))
					{
						f_ptr_obj_quadrilateral->MoveTo(0, -10);
						f_ptr_obj_quadrilateral->changeBasePoints234(0, -10);
					}
					if (event_menu_click.key.code == sf::Keyboard::A && (f_ptr_obj_quadrilateral->getXPoint() - 10 >= 710) && (f_ptr_obj_quadrilateral->getX4Point() - 10 >= 710))
					{
						f_ptr_obj_quadrilateral->MoveTo(-10, 0);
						f_ptr_obj_quadrilateral->changeBasePoints234(-10, 0);
					}
					if (event_menu_click.key.code == sf::Keyboard::S && (f_ptr_obj_quadrilateral->getY3Point() + 10 <= 895) && (f_ptr_obj_quadrilateral->getY4Point() + 10 <= 895))
					{
						f_ptr_obj_quadrilateral->MoveTo(0, 10);
						f_ptr_obj_quadrilateral->changeBasePoints234(0, 10);
					}
					if (event_menu_click.key.code == sf::Keyboard::D && (f_ptr_obj_quadrilateral->getX2Point() + 10 <= 1495) && (f_ptr_obj_quadrilateral->getX3Point() + 10 <= 1495))
					{
						f_ptr_obj_quadrilateral->MoveTo(10, 0);
						f_ptr_obj_quadrilateral->changeBasePoints234(10, 0);
					}
				}

				if (extra_menu == 0)
				{
					/*ИЗМЕНЕНИЕ РАДИУСА ОБЪЕКТА КРУГА*/
					if (circle_change_radius)
					{
						if (event_menu_click.key.code == sf::Keyboard::Q
							&& (f_ptr_obj_circle->getYPoint() + f_ptr_obj_circle->getRadius() + 2 <= 895)
							&& (f_ptr_obj_circle->getXPoint() + f_ptr_obj_circle->getRadius() + 2 <= 1495)
							&& (f_ptr_obj_circle->getYPoint() - f_ptr_obj_circle->getRadius() - 2 >= 100)
							&& (f_ptr_obj_circle->getXPoint() - f_ptr_obj_circle->getRadius() - 2 >= 710))
						{
							f_ptr_obj_circle->changeRadius(2);
						}
						if (event_menu_click.key.code == sf::Keyboard::E && (f_ptr_obj_circle->getRadius() >= 10))
							f_ptr_obj_circle->changeRadius(-2);
					}

					/*ИЗМЕНЕНИЕ РАЗМЕРОВ ОБЪЕКТА ПРЯМОУГОЛЬНИКА*/
					if (rectangle_change_dimensions)
					{
						if (event_menu_click.key.code == sf::Keyboard::Z && (f_ptr_obj_rect->getXPoint() + f_ptr_obj_rect->getLength() + 5 <= 1495))
							f_ptr_obj_rect->changeDimensions(5, 0);
						if (event_menu_click.key.code == sf::Keyboard::X && (f_ptr_obj_rect->getLength() >= 50))
							f_ptr_obj_rect->changeDimensions(-5, 0);
						if (event_menu_click.key.code == sf::Keyboard::C && (f_ptr_obj_rect->getYPoint() + f_ptr_obj_rect->getWidth() + 5 <= 895))
							f_ptr_obj_rect->changeDimensions(0, 5);
						if (event_menu_click.key.code == sf::Keyboard::V && (f_ptr_obj_rect->getWidth() >= 25))
							f_ptr_obj_rect->changeDimensions(0, -5);
						if (event_menu_click.key.code == sf::Keyboard::R)
						{
							if (f_ptr_obj_rect->getLength() > f_ptr_obj_rect->getWidth())
							{
								if ((f_ptr_obj_rect->getYPoint() - (f_ptr_obj_rect->getLength() - f_ptr_obj_rect->getWidth()) / 2 >= 100)
									&& (f_ptr_obj_rect->getYPoint() - (f_ptr_obj_rect->getLength() - f_ptr_obj_rect->getWidth()) / 2 + f_ptr_obj_rect->getLength() <= 895))
									f_ptr_obj_rect->rotateRect();
							}
							else
							{
								if ((f_ptr_obj_rect->getXPoint() - (f_ptr_obj_rect->getWidth() - f_ptr_obj_rect->getLength()) / 2 >= 710)
									&& (f_ptr_obj_rect->getXPoint() - (f_ptr_obj_rect->getWidth() - f_ptr_obj_rect->getLength()) / 2 + f_ptr_obj_rect->getWidth() <= 1495))
									f_ptr_obj_rect->rotateRect();
							}
						}
					}

					/*ИЗМЕНЕНИЕ РАЗМЕРОВ И ПОВОРОТ ОБЪЕКТА ОТРЕЗКА*/
					if (linesegment_change_dimensions)
					{
						int degree_linesegment{ static_cast<int>(f_ptr_obj_linesegment->getDegree()) };
						float x_linesegment{ f_ptr_obj_linesegment->getXPoint() };
						float y_linesegment{ f_ptr_obj_linesegment->getYPoint() };
						float length_linesegment{ f_ptr_obj_linesegment->getLength() };
						float alpha_linesegment{ degree_linesegment * PI / 180 };
						if (event_menu_click.key.code == sf::Keyboard::B)
						{
							if ((x_linesegment + length_linesegment * cos(alpha_linesegment) + 1) <= 1495 &&
								(x_linesegment + length_linesegment * cos(alpha_linesegment) + 1) >= 710 &&
								(y_linesegment + length_linesegment * sin(alpha_linesegment) + 1) <= 895 &&
								(y_linesegment + length_linesegment * sin(alpha_linesegment) + 1) >= 100)
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
							if ((x_linesegment + length_linesegment * cos(alpha_linesegment + PI / 180)) <= 1495 &&
								(x_linesegment + length_linesegment * cos(alpha_linesegment + PI / 180)) >= 710 &&
								(y_linesegment + length_linesegment * sin(alpha_linesegment + PI / 180)) <= 895 &&
								(y_linesegment + length_linesegment * sin(alpha_linesegment + PI / 180)) >= 100)
							{
								f_ptr_obj_linesegment->changeDegree(1);
							}
						}
						if (event_menu_click.key.code == sf::Keyboard::G)
						{
							if ((x_linesegment + length_linesegment * cos(alpha_linesegment - PI / 180)) <= 1495 &&
								(x_linesegment + length_linesegment * cos(alpha_linesegment - PI / 180)) >= 710 &&
								(y_linesegment + length_linesegment * sin(alpha_linesegment - PI / 180)) <= 895 &&
								(y_linesegment + length_linesegment * sin(alpha_linesegment - PI / 180)) >= 100)
							{
								f_ptr_obj_linesegment->changeDegree(-1);
							}
						}
					}
				}

				if (extra_menu == 1)
				{
					//ИЗМЕНЕНИЕ РАЗМЕРОВ И ПОВОРОТ ЭЛЛИПСА
					if (ellipse_change_dimensions)
					{
						if (event_menu_click.key.code == sf::Keyboard::Q
							&& (f_ptr_obj_ellipse->getXPoint() + f_ptr_obj_ellipse->getRadius() + 2 <= 1495)
							&& (f_ptr_obj_ellipse->getXPoint() - f_ptr_obj_ellipse->getRadius() - 2 >= 710))
						{
							f_ptr_obj_ellipse->changeRadius(2);
						}
						if (event_menu_click.key.code == sf::Keyboard::E && (f_ptr_obj_ellipse->getRadius() - 2 >= 50))
						{
							f_ptr_obj_ellipse->changeRadius(-2);
						}
						if (event_menu_click.key.code == sf::Keyboard::Z
							&& (f_ptr_obj_ellipse->getYPoint() + f_ptr_obj_ellipse->getSemiMinorAxis() + 2 <= 895)
							&& (f_ptr_obj_ellipse->getYPoint() - f_ptr_obj_ellipse->getSemiMinorAxis() - 2 >= 100))
						{
							f_ptr_obj_ellipse->changeSemiMinorAxis(2);
						}
						if (event_menu_click.key.code == sf::Keyboard::C && (f_ptr_obj_ellipse->getSemiMinorAxis() - 2 >= 25))
						{
							f_ptr_obj_ellipse->changeSemiMinorAxis(-2);
						}
						if ((event_menu_click.key.code == sf::Keyboard::X)
							&& (f_ptr_obj_ellipse->getXPoint() - f_ptr_obj_ellipse->getSemiMinorAxis() >= 710)
							&& (f_ptr_obj_ellipse->getXPoint() + f_ptr_obj_ellipse->getSemiMinorAxis() <= 1495)
							&& (f_ptr_obj_ellipse->getYPoint() - f_ptr_obj_ellipse->getRadius() >= 100)
							&& (f_ptr_obj_ellipse->getYPoint() + f_ptr_obj_ellipse->getRadius() <= 895))
						{
							f_ptr_obj_ellipse->rotateEllipse();
						}
					}
					//ИЗМЕНЕНИЕ РАЗМЕРОВ РОМБА
					if (rhomb_change_dimensions)
					{
						if (event_menu_click.key.code == sf::Keyboard::R
							&& (f_ptr_obj_rhomb->getY2Point() >= 100)
							&& (f_ptr_obj_rhomb->getY4Point() <= 900)
							&& (f_ptr_obj_rhomb->getX3Point() <= 1495))
						{
							f_ptr_obj_rhomb->changeLength(1);
						}
						if (event_menu_click.key.code == sf::Keyboard::T
							&& (f_ptr_obj_rhomb->getLength() - 1 >= 30))
						{
							f_ptr_obj_rhomb->changeLength(-1);
						}
						if (event_menu_click.key.code == sf::Keyboard::V
							&& (f_ptr_obj_rhomb->getDegree() + 1 <= 60)
							&& (f_ptr_obj_rhomb->getY2Point() >= 100)
							&& (f_ptr_obj_rhomb->getY4Point() <= 895))
						{
							f_ptr_obj_rhomb->changeDegree(1);
						}
						if (event_menu_click.key.code == sf::Keyboard::B
							&& (f_ptr_obj_rhomb->getDegree() - 1 >= 15)
							&& (f_ptr_obj_rhomb->getX3Point() <= 1495))
						{
							f_ptr_obj_rhomb->changeDegree(-1);
						}
					}

					//ИЗМЕНЕНИЕ РАЗМЕРОВ ТРАПЕЦИИ
					if (trapeze_change_dimensions)
					{
						if (event_menu_click.key.code == sf::Keyboard::Y && (f_ptr_obj_trapeze->getX3Point() <= f_ptr_obj_trapeze->getX4Point()))
							f_ptr_obj_trapeze->changeTopBase(1);
						if (event_menu_click.key.code == sf::Keyboard::U && (f_ptr_obj_trapeze->getX4Point() - f_ptr_obj_trapeze->getX3Point() - 1 <= 50))
							f_ptr_obj_trapeze->changeTopBase(-1);
						if (event_menu_click.key.code == sf::Keyboard::G && (f_ptr_obj_trapeze->getY2Point() - 1 >= 100) && (f_ptr_obj_trapeze->getYPoint() - f_ptr_obj_trapeze->getY2Point() + 1 <= 100))
							f_ptr_obj_trapeze->changeHeight(-1);
						if (event_menu_click.key.code == sf::Keyboard::H && (f_ptr_obj_trapeze->getYPoint() - f_ptr_obj_trapeze->getY2Point() - 1 >= 30))
							f_ptr_obj_trapeze->changeHeight(1);
						if (event_menu_click.key.code == sf::Keyboard::N && (f_ptr_obj_trapeze->getX4Point() + 1 <= 1495) && ((f_ptr_obj_trapeze->getX4Point() + 1) <= (f_ptr_obj_trapeze->getX3Point() + 60)))
							f_ptr_obj_trapeze->changeBottomBase(1);
						if (event_menu_click.key.code == sf::Keyboard::M && (f_ptr_obj_trapeze->getX4Point() - 1 >= f_ptr_obj_trapeze->getX3Point()))
							f_ptr_obj_trapeze->changeBottomBase(-1);
					}
				}

				if (extra_menu == 2)
				{
					//ИЗМЕНЕНИЕ РАЗМЕРОВ ЧЕТЫРЕХУГОЛЬНИКА
					if (quadrilateral_change_dimensions)
					{
						if (event_menu_click.key.code == sf::Keyboard::R &&
							(f_ptr_obj_quadrilateral->getXPoint() - 1) >= 710 &&
							(f_ptr_obj_quadrilateral->getYPoint() - 1) >= 100 &&
							(f_ptr_obj_quadrilateral->getX2Point() + 1) <= 1495 &&
							(f_ptr_obj_quadrilateral->getY2Point() - 1) >= 100 &&
							(f_ptr_obj_quadrilateral->getX3Point() + 1) <= 1495 &&
							(f_ptr_obj_quadrilateral->getY3Point() + 1) <= 895 &&
							(f_ptr_obj_quadrilateral->getX4Point() - 1) >= 710 &&
							(f_ptr_obj_quadrilateral->getY4Point() + 1) <= 895)
						{
							f_ptr_obj_quadrilateral->changeSize(1);
						}
						if (event_menu_click.key.code == sf::Keyboard::V && (f_ptr_obj_quadrilateral->getX2Point() - f_ptr_obj_quadrilateral->getXPoint() - 2 >= 50)
							&& (f_ptr_obj_quadrilateral->getY3Point() - f_ptr_obj_quadrilateral->getY2Point() - 2 >= 50))
						{
							f_ptr_obj_quadrilateral->changeSize(-1);
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

				//МАССИВ ЭЛЛИПСОВ
				//Пользовательское движение элементов
				if (array_ellipses_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W)
						doUserMoveArrayEllipsesW(array_ellipses, array_ellipses_size);
					if (event_menu_click.key.code == sf::Keyboard::A)
						doUserMoveArrayEllipsesA(array_ellipses, array_ellipses_size);
					if (event_menu_click.key.code == sf::Keyboard::S)
						doUserMoveArrayEllipsesS(array_ellipses, array_ellipses_size);
					if (event_menu_click.key.code == sf::Keyboard::D)
						doUserMoveArrayEllipsesD(array_ellipses, array_ellipses_size);
				}

				//МАССИВ РОМБОВ
				if (array_rhombs_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W)
						doUserMoveArrayRhombsW(array_rhombs, array_rhombs_size);
					if (event_menu_click.key.code == sf::Keyboard::A)
						doUserMoveArrayRhombsA(array_rhombs, array_rhombs_size);
					if (event_menu_click.key.code == sf::Keyboard::S)
						doUserMoveArrayRhombsS(array_rhombs, array_rhombs_size);
					if (event_menu_click.key.code == sf::Keyboard::D)
						doUserMoveArrayRhombsD(array_rhombs, array_rhombs_size);
				}

				//МАССИВ ТРАПЕЦИЙ
				if (array_trapezes_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W)
						doUserMoveArrayTrapezesW(array_trapezes, array_trapezes_size);
					if (event_menu_click.key.code == sf::Keyboard::A)
						doUserMoveArrayTrapezesA(array_trapezes, array_trapezes_size);
					if (event_menu_click.key.code == sf::Keyboard::S)
						doUserMoveArrayTrapezesS(array_trapezes, array_trapezes_size);
					if (event_menu_click.key.code == sf::Keyboard::D)
						doUserMoveArrayTrapezesD(array_trapezes, array_trapezes_size);
				}

				//МАССИВ ЧЕТЫРЕХУГОЛЬНИКОВ
				//Пользовательское движение элементов
				if (array_quadrilaterals_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W)
						doUserMoveArrayQuadrilateralsW(array_quadrilaterals, array_quadrilaterals_size);
					if (event_menu_click.key.code == sf::Keyboard::A)
						doUserMoveArrayQuadrilateralsA(array_quadrilaterals, array_quadrilaterals_size);
					if (event_menu_click.key.code == sf::Keyboard::S)
						doUserMoveArrayQuadrilateralsS(array_quadrilaterals, array_quadrilaterals_size);
					if (event_menu_click.key.code == sf::Keyboard::D)
						doUserMoveArrayQuadrilateralsD(array_quadrilaterals, array_quadrilaterals_size);
				}

				if (extra_menu == 0)
				{
					//Изменение радиуса элементов массива кругов
					if (array_circles_show)
					{
						if (event_menu_click.key.code == sf::Keyboard::Q)
							array_circles_RadiusIncrease(array_circles, array_circles_size);
						if (event_menu_click.key.code == sf::Keyboard::E)
							array_circles_RadiusDecrease(array_circles, array_circles_size);
					}

					//Изменение размеров элементов массива прямоугольников
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
						if (event_menu_click.key.code == sf::Keyboard::R)
							doRotateArrayRects(array_rectangles, array_rectangles_size);
					}

					//Изменение размеров элементов и поворот элементов массива отрезков
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

				if (extra_menu == 1)
				{
					//Изменение размеров элементов и поворот элементов массива эллипсов
					if (array_ellipses_show)
					{
						if (event_menu_click.key.code == sf::Keyboard::Q)
							array_ellipses_SemiMajorAxisIncrease(array_ellipses, array_ellipses_size);
						if (event_menu_click.key.code == sf::Keyboard::E)
							array_ellipses_SemiMajorAxisDecrease(array_ellipses, array_ellipses_size);
						if (event_menu_click.key.code == sf::Keyboard::Z)
							array_ellipses_SemiMinorAxisIncrease(array_ellipses, array_ellipses_size);
						if (event_menu_click.key.code == sf::Keyboard::C)
							array_ellipses_SemiMinorAxisDecrease(array_ellipses, array_ellipses_size);
						if (event_menu_click.key.code == sf::Keyboard::X)
							array_ellipses_Rotate(array_ellipses, array_ellipses_size);
					}
					//Изменение размеров элементов и поворот элементов массива ромбов
					if (array_rhombs_show)
					{
						if (event_menu_click.key.code == sf::Keyboard::R)
							array_rhombs_IncreaseLength(array_rhombs, array_rhombs_size);
						if (event_menu_click.key.code == sf::Keyboard::T)
							array_rhombs_DecreaseLength(array_rhombs, array_rhombs_size);
						if (event_menu_click.key.code == sf::Keyboard::V)
							array_rhombs_IncreaseDegree(array_rhombs, array_rhombs_size);
						if (event_menu_click.key.code == sf::Keyboard::B)
							array_rhombs_DecreaseDegree(array_rhombs, array_rhombs_size);
					}
					//Изменение размеров элементов массива трапеций
					if (array_trapezes_show)
					{
						if (event_menu_click.key.code == sf::Keyboard::Y)
							array_trapezes_IncreaseTopBase(array_trapezes, array_trapezes_size);
						if (event_menu_click.key.code == sf::Keyboard::U)
							array_trapezes_DecreaseTopBase(array_trapezes, array_trapezes_size);
						if (event_menu_click.key.code == sf::Keyboard::G)
							array_trapezes_IncreaseHeight(array_trapezes, array_trapezes_size);
						if (event_menu_click.key.code == sf::Keyboard::H)
							array_trapezes_DecreaseHeight(array_trapezes, array_trapezes_size);
						if (event_menu_click.key.code == sf::Keyboard::N)
							array_trapezes_IncreaseBottomBase(array_trapezes, array_trapezes_size);
						if (event_menu_click.key.code == sf::Keyboard::M)
							array_trapezes_DecreaseBottomBase(array_trapezes, array_trapezes_size);
					}
				}

				if (extra_menu == 2)
				{
					//Изменение размеров элементов массива четырёхугольников
					if (array_quadrilaterals_show)
					{
						if (event_menu_click.key.code == sf::Keyboard::R)
							array_quadrilaterals_DimensionsIncrease(array_quadrilaterals, array_quadrilaterals_size);
						if (event_menu_click.key.code == sf::Keyboard::V)
							array_quadrilaterals_DimensionsDecrease(array_quadrilaterals, array_quadrilaterals_size);
					}
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
		if (extra_menu == 0 || extra_menu == 1)
		{
			BG_next.Show(window);
			next_text.Show(window);
		}
		if (extra_menu == 1 || extra_menu == 2)
		{
			BG_back.Show(window);
			back_text.Show(window);
		}

		//Вкладка CREATE_0
		if (menu_create_0 && extra_menu == 0)
		{

			BG_circle.Show(window);
			circle_text.Show(window);
			BG_rect.Show(window);
			rect_text.Show(window);
			BG_linesegment.Show(window);
			linesegment_text.Show(window);
			BG_create_arrays_of_graphic_primitives.Show(window);
			create_arrays_of_graphic_primitives_text.Show(window);

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
				BG_create_15_objs.Show(window);
				create_15_objs_text.Show(window);
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
		//Вкладка CREATE_1
		else if (menu_create_1 && extra_menu == 1)
		{
			BG_ellipse.Show(window);
			ellipse_text.Show(window);
			BG_rhomb.Show(window);
			rhomb_text.Show(window);
			BG_trapeze.Show(window);
			trapeze_text.Show(window);
			BG_create_arrays_of_hereditary_objects.Show(window);
			create_arrays_of_hereditary_objects_text.Show(window);

			//Нажата кнопка CREATE -> create arrays of hereditary objects
			if (submenu_create_arrays_1)
			{
				BG_submenu_obj.m_setFillColor(4, 32, 159);
				BG_submenu_obj.Show(window);
				submenu_obj_text.Show(window);

				BG_create_array_ellipses.Show(window);
				create_array_ellipses_text.Show(window);
				BG_create_array_rhombs.Show(window);
				create_array_rhombs_text.Show(window);
				BG_create_array_trapezes.Show(window);
				create_array_trapezes_text.Show(window);

				/*МАССИВЫ ОБЪЕКТОВ*/
				//Вывод на окно кнопки создания по 15 граф. примитивов
				BG_create_15_objs.Show(window);
				create_15_objs_text.Show(window);
				//Массив эллипсов
				if (array_ellipses_show)
				{
					BG_RandomMove_array_ellipses.Show(window);
					RandomMove_array_ellipses_text.Show(window);

					BG_UserMove_array_ellipses.Show(window);
					UserMove_array_ellipses_text.Show(window);

					BG_delete_last_elem_array_ellipses.Show(window);
					delete_last_elem_array_ellipses_text.Show(window);

					BG_delete_all_ellipses.Show(window);
					delete_all_ellipses_text.Show(window);
				}
				//Массив ромбов
				if (array_rhombs_show)
				{
					BG_RandomMove_array_rhombs.Show(window);
					RandomMove_array_rhombs_text.Show(window);

					BG_UserMove_array_rhombs.Show(window);
					UserMove_array_rhombs_text.Show(window);

					BG_delete_last_elem_array_rhombs.Show(window);
					delete_last_elem_array_rhombs_text.Show(window);

					BG_delete_all_rhombs.Show(window);
					delete_all_rhombs_text.Show(window);
				}
				//Массив трапеций
				if (array_trapezes_show)
				{
					BG_RandomMove_array_trapezes.Show(window);
					RandomMove_array_trapezes_text.Show(window);

					BG_UserMove_array_trapezes.Show(window);
					UserMove_array_trapezes_text.Show(window);

					BG_delete_last_elem_array_trapezes.Show(window);
					delete_last_elem_array_trapezes_text.Show(window);

					BG_delete_all_trapezes.Show(window);
					delete_all_trapezes_text.Show(window);
				}
			}
		}
		//ВКЛАДКА CREATE_2
		else if (menu_create_2 && extra_menu == 2)
		{
			BG_quadrilateral.Show(window);
			quadrilateral_text.Show(window);
			BG_create_arrays_of_convex_polygons.Show(window);
			create_arrays_of_convex_polygons_text.Show(window);

			//Нажата кнопка CREATE -> create arrays of convex_polygons
			if (submenu_create_arrays_2)
			{
				BG_submenu_obj.m_setFillColor(4, 32, 159);
				BG_submenu_obj.Show(window);
				submenu_obj_text.Show(window);

				BG_create_array_quadrilaterals.Show(window);
				create_array_quadrilaterals_text.Show(window);

				/*МАССИВЫ ОБЪЕКТОВ*/
				//Вывод на окно кнопки создания по 15 граф. примитивов
				BG_create_15_objs.Show(window);
				create_15_objs_text.Show(window);
				//Массив четырехугольников
				if (array_quadrilaterals_show)
				{
					BG_RandomMove_array_quadrilaterals.Show(window);
					RandomMove_array_quadrilaterals_text.Show(window);

					BG_UserMove_array_quadrilaterals.Show(window);
					UserMove_array_quadrilaterals_text.Show(window);

					BG_delete_last_elem_array_quadrilaterals.Show(window);
					delete_last_elem_array_quadrilaterals_text.Show(window);

					BG_delete_all_quadrilaterals.Show(window);
					delete_all_quadrilaterals_text.Show(window);
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

		else if (menu_move_and_change_1 && extra_menu == 1)
		{
			//Создан объект эллипса
			if (ellipse_show)
			{
				BG_obj_ellipse.Show(window);
				obj_ellipse_text.Show(window);

				//Нажата кнопка MOVE AND CHANGE -> obj_ellipse
				if (submenu_obj_ellipse)
				{
					BG_submenu_obj.Show(window);
					submenu_obj_text.Show(window);

					BG_RandomMove_obj_ellipse.Show(window);
					RandomMove_obj_ellipse_text.Show(window);

					BG_UserMove_obj_ellipse.Show(window);
					UserMove_obj_ellipse_text.Show(window);

					BG_ChangeDimensions_obj_ellipse.Show(window);
					ChangeDimensions_obj_ellipse_text.Show(window);

					BG_delete_obj_ellipse.Show(window);
					delete_obj_ellipse_text.Show(window);
				}
			}
			//Создан объект ромба
			if (rhomb_show)
			{
				BG_obj_rhomb.Show(window);
				obj_rhomb_text.Show(window);

				//Нажата кнопка MOVE AND CHANGE -> obj_rhomb
				if (submenu_obj_rhomb)
				{
					BG_submenu_obj.Show(window);
					submenu_obj_text.Show(window);

					BG_RandomMove_obj_rhomb.Show(window);
					RandomMove_obj_rhomb_text.Show(window);

					BG_UserMove_obj_rhomb.Show(window);
					UserMove_obj_rhomb_text.Show(window);

					BG_ChangeDimensions_obj_rhomb.Show(window);
					ChangeDimensions_obj_rhomb_text.Show(window);

					BG_delete_obj_rhomb.Show(window);
					delete_obj_rhomb_text.Show(window);
				}
			}
			//Создан объект трапеции
			if (trapeze_show)
			{
				BG_obj_trapeze.Show(window);
				obj_trapeze_text.Show(window);

				//Нажата кнопка MOVE AND CHANGE -> obj_trapeze
				if (submenu_obj_trapeze)
				{
					BG_submenu_obj.Show(window);
					submenu_obj_text.Show(window);

					BG_RandomMove_obj_trapeze.Show(window);
					RandomMove_obj_trapeze_text.Show(window);

					BG_UserMove_obj_trapeze.Show(window);
					UserMove_obj_trapeze_text.Show(window);

					BG_ChangeDimensions_obj_trapeze.Show(window);
					ChangeDimensions_obj_trapeze_text.Show(window);

					BG_delete_obj_trapeze.Show(window);
					delete_obj_trapeze_text.Show(window);
				}
			}
		}

		else if (menu_move_and_change_2 && extra_menu == 2)
		{
			//Создан объект четырехугольника
			if (quadrilateral_show)
			{
				BG_obj_quadrilateral.Show(window);
				obj_quadrilateral_text.Show(window);

				//Нажата кнопка MOVE AND CHANGE -> obj_quadrilateral
				if (submenu_obj_quadrilateral)
				{
					BG_submenu_obj.Show(window);
					submenu_obj_text.Show(window);

					BG_RandomMove_obj_quadrilateral.Show(window);
					RandomMove_obj_quadrilateral_text.Show(window);

					BG_UserMove_obj_quadrilateral.Show(window);
					UserMove_obj_quadrilateral_text.Show(window);

					BG_ChangeDimensions_obj_quadrilateral.Show(window);
					ChangeDimensions_obj_quadrilateral_text.Show(window);

					BG_delete_obj_quadrilateral.Show(window);
					delete_obj_quadrilateral_text.Show(window);
				}
			}
		}

		/*ЕДИНИЧНЫЕ ОБЪЕКТЫ*/
		//Вывод объектов окружности, прямоугольника, отрезка и тд.
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
		if (ellipse_show)
		{
			f_ptr_obj_ellipse->Show(window);
		}
		if (rhomb_show)
		{
			f_ptr_obj_rhomb->Show(window);
		}
		if (trapeze_show)
		{
			f_ptr_obj_trapeze->Show(window);
		}
		if (quadrilateral_show)
		{
			f_ptr_obj_quadrilateral->Show(window);
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
		//Массив эллипсов
		if (array_ellipses_show)
		{
			if (extra_menu == 1)
			{
				ChangeDimensions_array_ellipses_text.m_setFillColor(209, 255, 26);
				ChangeDimensions_array_ellipses_text.Show(window);
			}
			for (int i{}; i < array_ellipses_size; i++)
			{
				array_ellipses[i]->Show(window);
			}
		}
		//Массив ромбов
		if (array_rhombs_show)
		{
			if (extra_menu == 1)
			{
				ChangeDimensions_array_rhombs_text.m_setFillColor(209, 255, 26);
				ChangeDimensions_array_rhombs_text.Show(window);
			}
			for (int i{}; i < array_rhombs_size; i++)
			{
				array_rhombs[i]->Show(window);
			}
		}
		//Массив трапеций
		if (array_trapezes_show)
		{
			if (extra_menu == 1)
			{
				ChangeDimensions_array_trapezes_text.m_setFillColor(209, 255, 26);
				ChangeDimensions_array_trapezes_text.Show(window);
			}
			for (int i{}; i < array_trapezes_size; i++)
			{
				array_trapezes[i]->Show(window);
			}
		}
		//Массив четырехугольников
		if (array_quadrilaterals_show)
		{
			if (extra_menu == 2)
			{
				ChangeDimensions_array_quadrilaterals_text.m_setFillColor(209, 255, 26);
				ChangeDimensions_array_quadrilaterals_text.Show(window);
			}
			for (int i{}; i < array_quadrilaterals_size; i++)
			{
				array_quadrilaterals[i]->Show(window);
			}
		}

		BG_exit.Show(window);
		exit_text.Show(window);
		window.display();
	}
	return 0;
}