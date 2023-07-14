#include <cstdlib> //��� ������� rand() � srand()
#include <ctime> //��� ������� time()
#include "myfuncs.h"
#include "constants.h"
#include "user_buttons.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Linesegment.h"
#include "Ring.h"
#include "Mortar.h"

//����
float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}

//������� ������ ���������
int menu_processing(sf::RenderWindow& window, Circle*& f_ptr_obj_circle, Rectangle*& f_ptr_obj_rect, Linesegment*& f_ptr_obj_linesegment, Ring*& f_ptr_obj_ring, Mortar*& f_ptr_obj_mortar,
	int& array_circles_size, Circle**& array_circles,
	int& array_rectangles_size, Rectangle**& array_rectangles,
	int& array_linesegments_size, Linesegment**& array_linesegments,
	int& array_rings_size, Ring**& array_rings,
	int& array_mortars_size, Mortar**& array_mortars)
{
	/*�������� ���� ����*/
	//����
	Rect_BG_buttons BG_general(0, 0, 700, 895, 5);
	BG_general.m_setFillColor(5, 90, 1);
	//IMAGE
	User_texts image_text("Comic_Sans_MS.TTF", " I  M  A  G  E ", 870, 0, 70);
	//������ ����
	Rect_BG_buttons BG_menu(5, 5, 695, 85, 5);
	User_texts menu_text("Comic_Sans_MS.TTF", " M   E   N   U ", 20, 0, 70);
	//������ �������
	Rect_BG_buttons BG_submenu_obj(5, 360, 695, 80, 5);
	User_texts submenu_obj_text("Comic_Sans_MS.TTF", "S U B M E N U", 20, 360, 65);
	//������ �������� �������� ��������� �� 15 �����
	Rect_BG_buttons BG_create_15_objs(500, 360, 200, 80, 5);
	User_texts create_15_objs_text("Comic_Sans_MS.TTF", "create_15_objs", 505, 380, 23);


	/*������ ����*/
	//������ CREATE
	Rect_BG_buttons BG_create(5, 96, 200, 120, 5);
	User_texts create_text("Comic_Sans_MS.TTF", "C R E A T E", 15, 135, 30);
	//������ MOVE AND CHANGE
	Rect_BG_buttons BG_move_and_change(5, 229, 200, 120, 5);
	User_texts move_and_change_text("Comic_Sans_MS.TTF", " M  O  V  E\n\t  and   \nC H A N G E", 15, 230, 30);
	//������ EXIT
	Rect_BG_buttons BG_exit(5, 840, 160, 50, 5);
	User_texts exit_text("Comic_Sans_MS.TTF", "E X I T", 25, 850, 30);

	/*EXTRAMENU == 0*/

	/*������ ������� CREATE*/
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
	
	/*������ ������� CREATE->create array of graphics primitives*/
	//Create->create arrays of graphics primitives->array of circles
	Rect_BG_buttons BG_create_array_circles(5, 460, 175, 40, 5);
	User_texts create_array_circles_text("Comic_Sans_MS.TTF", "array of circles", 10, 467, 20);
	//Create->create arrays of graphics primitives->array of rectangles
	Rect_BG_buttons BG_create_array_rectangles(195, 460, 210, 40, 5);
	User_texts create_array_rectangles_text("Comic_Sans_MS.TTF", "array of rectangles", 195, 467, 20);
	//Create->create arrays of graphics primitives->array of linesegments
	Rect_BG_buttons BG_create_array_linesegments(420, 460, 240, 40, 5);
	User_texts create_array_linesegments_text("Comic_Sans_MS.TTF", "array of linesegments", 420, 467, 20);

	/*�������� ����������*/
	//������� ���� ��������� �������: MOVE AND CHANGE->obj_circle
	Rect_BG_buttons BG_obj_circle(220, 229, 140, 40, 5);
	User_texts obj_circle_text("Comic_Sans_MS.TTF", "  obj_circle", 225, 238, 21);
	//�������� ��������� ������� �� x � �� y �� ��������� [-50;50]:obj_circle-> circle_random_move
	Rect_BG_buttons BG_RandomMove_obj_circle(5, 455, 230, 40, 5);
	User_texts RandomMove_obj_circle_text("Comic_Sans_MS.TTF", "circle_random_move", 10, 460, 20);
	//�������� �� �������� WASD ���������: obj_circle -> circle_user_move
	Rect_BG_buttons BG_UserMove_obj_circle(250, 455, 230, 40, 5);
	User_texts UserMove_obj_circle_text("Comic_Sans_MS.TTF", "circle_user_move", 270, 460, 20);
	//��������� ��� ��������� ������: obj_circle -> circle_change_radius:\n(q) - increase\n(e) - decrease
	Rect_BG_buttons BG_ChangeRadius_obj_circle(5, 510, 300, 80, 5);
	User_texts ChangeRadius_obj_circle_text("Comic_Sans_MS.TTF", "circle_change_radius:\n(q) - increase\n(e) - decrease", 10, 510, 18);
	//������� ������: obj_circle -> delete
	Rect_BG_buttons BG_delete_obj_circle(495, 455, 160, 40, 5);
	User_texts delete_obj_circle_text("Comic_Sans_MS.TTF", "delete", 530, 460, 25);

	/*�������� ��������������*/
	//������� ���� ��������� �������: MOVE AND CHANGE->obj_rectangle
	Rect_BG_buttons BG_obj_rect(375, 229, 160, 40, 5);
	User_texts obj_rect_text("Comic_Sans_MS.TTF", "obj_rectangle", 380, 238, 21);
	Rect_BG_buttons BG_RandomMove_obj_rect(5, 455, 230, 40, 5);
	//�������� ��������� ������� �� x � �� y �� ��������� [-50;50]:obj_rectangle-> rect_random_move
	User_texts RandomMove_obj_rect_text("Comic_Sans_MS.TTF", "rect_random_move", 10, 460, 20);
	//�������� �� �������� WASD ���������: obj_rectangle -> rect_user_move
	Rect_BG_buttons BG_UserMove_obj_rect(250, 455, 230, 40, 5);
	User_texts UserMove_obj_rect_text("Comic_Sans_MS.TTF", "rect_user_move", 270, 460, 20);
	//��������� ��� ��������� ������: obj_rectangle -> rectangle_change_dimensions:\n(z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width
	Rect_BG_buttons BG_ChangeWidthLength_obj_rectangle(5, 510, 300, 160, 5);
	User_texts ChangeWidthLength_obj_rectangle_text("Comic_Sans_MS.TTF",
		"rectangle_change_dimensions:\n(z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width", 10, 510, 18);
	//������� ������: obj_rectangle -> delete
	Rect_BG_buttons BG_delete_obj_rectangle(495, 455, 160, 40, 5);
	User_texts delete_obj_rectangle_text("Comic_Sans_MS.TTF", "delete", 530, 460, 25);


	/*�������� �������*/
	//������� ���� ��������� �������: MOVE AND CHANGE->obj_linesegment
	Rect_BG_buttons BG_obj_linesegment(220, 280, 185, 40, 5);
	User_texts obj_linesegment_text("Comic_Sans_MS.TTF", "obj_linesegment", 225, 290, 21);
	//�������� ��������� ������� �� x � �� y �� ��������� [-50;50]:obj_linesegment-> line_random_move
	Rect_BG_buttons BG_RandomMove_obj_linesegment(5, 455, 230, 40, 5);
	User_texts RandomMove_obj_linesegment_text("Comic_Sans_MS.TTF", "line_random_move", 10, 460, 20);
	//�������� �� �������� WASD ���������: obj_linesegment -> line_user_move
	Rect_BG_buttons BG_UserMove_obj_linesegment(250, 455, 230, 40, 5);
	User_texts UserMove_obj_linesegment_text("Comic_Sans_MS.TTF", "line_user_move", 270, 460, 20);
	//��������� ��� ��������� ����� �������, ��������� �������: obj_linesegment -> linesegment_change_length:\n(f) - increase\n(g) - decrease\n(h) - rotate
	Rect_BG_buttons BG_ChangeDimensions_obj_linesegment(5, 510, 300, 160, 5);
	User_texts ChangeDimensions_obj_linesegment_text("Comic_Sans_MS.TTF",
		"linesegment_change_length:\n(b) - increase\n(n) - decrease\nlinesegment_change_rotate:\n(f) - rotate clockwise\n(g) - rotate counterclockwise", 10, 510, 18);
	//������� ������: obj_linesegment -> delete
	Rect_BG_buttons BG_delete_obj_linesegment(495, 455, 160, 40, 5);
	User_texts delete_obj_linesegment_text("Comic_Sans_MS.TTF", "delete", 530, 460, 25);

	/*�������� ������� �����������*/
	//�������� �������� ��������� ������� �� x � �� y �� ��������� [-50;50]:array_of_circles -> random move(circles)
	Rect_BG_buttons BG_RandomMove_array_circles(5, 520, 175, 40, 5);
	User_texts RandomMove_array_circles_text("Comic_Sans_MS.TTF", "random move(circles)", 10, 530, 15);
	//�������� �� �������� WASD ���������: array of circles -> user move(circles) 
	Rect_BG_buttons BG_UserMove_array_circles(5, 580, 175, 40, 5);
	User_texts UserMove_array_circles_text("Comic_Sans_MS.TTF", "user move(circles)", 10, 590, 17);
	//������� ��������� �������: array of circles -> delete_last circle
	Rect_BG_buttons BG_delete_last_elem_array_circles(5, 640, 175, 40, 5);
	User_texts delete_last_elem_array_circles_text("Comic_Sans_MS.TTF", "delete_last circle", 10, 650, 17);
	//������� ��� ��������: array of circles -> delete all circles
	Rect_BG_buttons BG_delete_all_circles(5, 700, 175, 40, 5);
	User_texts delete_all_circles_text("Comic_Sans_MS.TTF", "delete all circles", 10, 710, 17);
	//���������� ��� ���������� �������: array of circles -> (q) - increase radius\n(e) - decrease radius
	User_texts ChangeRadius_array_circles_text("Comic_Sans_MS.TTF", "(q) - increase radius\n(e) - decrease radius", 5, 760, 15);

	/*�������� ������� ���������������*/
	//�������� �������� ��������� ������� �� x � �� y �� ��������� [-50;50]:array_of_rectangles -> random move(rectangles)
	Rect_BG_buttons BG_RandomMove_array_rectangles(195, 520, 210, 40, 5);
	User_texts RandomMove_array_rectangles_text("Comic_Sans_MS.TTF", "random move(rectangles)", 200, 530, 15);
	//�������� �� �������� WASD ���������: array of rectangles -> user move(rectangles) 
	Rect_BG_buttons BG_UserMove_array_rectangles(195, 580, 210, 40, 5);
	User_texts UserMove_array_rectangles_text("Comic_Sans_MS.TTF", "user move(reactangles)", 200, 590, 17);
	//������� ��������� �������: array of rectangles -> delete_last rectangle
	Rect_BG_buttons BG_delete_last_elem_array_rectangles(195, 640, 210, 40, 5);
	User_texts delete_last_elem_array_rectangles_text("Comic_Sans_MS.TTF", "delete_last rectangle", 200, 650, 17);
	//������� ��� ��������: array of rectangles -> delete all rectangles
	Rect_BG_buttons BG_delete_all_rectangles(195, 700, 210, 40, 5);
	User_texts delete_all_rectangles_text("Comic_Sans_MS.TTF", "delete all rectangles", 200, 710, 17);
	//��������� ������� ��������� ������� ���������������: array of rectangles -> (z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width
	User_texts ChangeDimensions_array_rectangles_text("Comic_Sans_MS.TTF",
		"(z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width", 200, 760, 15);

	/*�������� ������� ��������*/
	//�������� �������� ��������� ������� �� x � �� y �� ��������� [-50;50]: array_of_linesegments -> random move(linesegments)
	Rect_BG_buttons BG_RandomMove_array_linesegments(420, 520, 240, 40, 5);
	User_texts RandomMove_array_linesegments_text("Comic_Sans_MS.TTF", "random move(linesegments)", 425, 530, 15);
	//�������� �� �������� WASD ���������: array of linesegments -> user move(linesegments)
	Rect_BG_buttons BG_UserMove_array_linesegments(420, 580, 240, 40, 5);
	User_texts UserMove_array_linesegments_text("Comic_Sans_MS.TTF", "user move(linesegments)", 425, 590, 17);
	//������� ��������� �������: array of linesegments -> delete_last linesegment
	Rect_BG_buttons BG_delete_last_elem_array_linesegments(420, 640, 240, 40, 5);
	User_texts delete_last_elem_array_linesegments_text("Comic_Sans_MS.TTF", "delete_last linesegment", 425, 650, 17);
	//������� ��� ��������: array of linesegments -> delete all linesegments
	Rect_BG_buttons BG_delete_all_linesegments(420, 700, 240, 40, 5);
	User_texts delete_all_linesegments_text("Comic_Sans_MS.TTF", "delete all linesegments", 425, 710, 17);
	//��������� ������� ��������� ������� ���������������: array of rectangles -> (z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width
	User_texts ChangeDimensions_array_linesegments_text("Comic_Sans_MS.TTF",
		"linesegment_change_length:\n(b) - increase\n(n) - decrease\nlinesegment_change_rotate:\n(f) - rotate clockwise\n(g) - rotate counterclockwise", 425, 760, 15);

	//������� �� ��������� ��� ���������� �������� ����������� ���������� � ����������� ����������
	Rect_BG_buttons BG_next(600, 5, 100, 85, 5);
	User_texts next_text("Comic_Sans_MS.TTF", "NEXT", 605, 30, 30);
	Rect_BG_buttons BG_back(495, 5, 100, 85, 5);
	User_texts back_text("Comic_Sans_MS.TTF", "BACK", 500, 30, 30);

	/*EXTRAMENU == 1*/

	//CREATE->ring
	Rect_BG_buttons BG_ring(220, 97, 140, 40, 5);
	User_texts ring_text("Comic_Sans_MS.TTF", "r  i  n  g", 240, 100, 25);
	//CREATE->mortar
	Rect_BG_buttons BG_mortar(375, 97, 140, 40, 5);
	User_texts mortar_text("Comic_Sans_MS.TTF", "mortar", 390, 100, 25);
	//CREATE->create arrays of complex objects
	Rect_BG_buttons BG_create_arrays_of_complex_objects(220, 160, 473, 40, 5);
	User_texts create_arrays_of_complex_objects_text("Comic_Sans_MS.TTF", "create arrays of complex objects", 231, 165, 25);

	/*������ ������� CREATE->create array of complex objects*/
	//Create->create arrays of complex objects->array of rings
	Rect_BG_buttons BG_create_array_rings(5, 460, 175, 40, 5);
	User_texts create_array_rings_text("Comic_Sans_MS.TTF", "array of rings", 10, 467, 20);
	//Create->create arrays of complex objects->array of mortars
	Rect_BG_buttons BG_create_array_mortars(195, 460, 210, 40, 5);
	User_texts create_array_mortars_text("Comic_Sans_MS.TTF", "array of mortars", 195, 467, 20);

	/*�������� ������*/
	//������� ���� ��������� �������: MOVE AND CHANGE->obj_ring
	Rect_BG_buttons BG_obj_ring(220, 229, 140, 40, 5);
	User_texts obj_ring_text("Comic_Sans_MS.TTF", "  obj_ring", 225, 238, 21);
	//�������� ��������� ������� �� x � �� y �� ��������� [-50;50]:obj_ring-> ring_random_move
	Rect_BG_buttons BG_RandomMove_obj_ring(5, 455, 230, 40, 5);
	User_texts RandomMove_obj_ring_text("Comic_Sans_MS.TTF", "ring_random_move", 10, 460, 20);
	//�������� �� �������� WASD ���������: obj_ring -> ring_user_move
	Rect_BG_buttons BG_UserMove_obj_ring(250, 455, 230, 40, 5);
	User_texts UserMove_obj_ring_text("Comic_Sans_MS.TTF", "ring_user_move", 270, 460, 20);
	//��������� ��� ��������� ������: obj_ring -> ring_change_radius:\n(q) - increase\n(e) - decrease
	Rect_BG_buttons BG_ChangeDimensions_obj_ring(5, 510, 300, 80, 5);
	User_texts ChangeDimensions_obj_ring_text("Comic_Sans_MS.TTF", "ring_change_dimensions:\n(q) - increase\n(e) - decrease", 10, 510, 18);
	//������� ������: obj_ring -> delete
	Rect_BG_buttons BG_delete_obj_ring(495, 455, 160, 40, 5);
	User_texts delete_obj_ring_text("Comic_Sans_MS.TTF", "delete", 530, 460, 25);

	/*�������� �������*/
	//������� ���� ��������� �������: MOVE AND CHANGE->obj_mortar
	Rect_BG_buttons BG_obj_mortar(375, 229, 160, 40, 5);
	User_texts obj_mortar_text("Comic_Sans_MS.TTF", "obj_mortar", 380, 238, 21);
	Rect_BG_buttons BG_RandomMove_obj_mortar(5, 455, 230, 40, 5);
	//�������� ��������� ������� �� x � �� y �� ��������� [-50;50]:obj_mortar-> mortar_random_move
	User_texts RandomMove_obj_mortar_text("Comic_Sans_MS.TTF", "mortar_random_move", 8, 460, 20);
	//�������� �� �������� WASD ���������: obj_mortar -> mortar_user_move
	Rect_BG_buttons BG_UserMove_obj_mortar(250, 455, 230, 40, 5);
	User_texts UserMove_obj_mortar_text("Comic_Sans_MS.TTF", "mortar_user_move", 270, 460, 20);
	//��������� ��� ��������� �������: obj_mortar -> mortar_change_dimensions:\n(q) - increase\n(e) - decrease
	Rect_BG_buttons BG_ChangeDimensions_obj_mortar(5, 510, 300, 160, 5);
	User_texts ChangeDimensions_obj_mortar_text("Comic_Sans_MS.TTF",
		"mortar_change_dimensions:\n(z) - increase dimensions\n(x) - decrease dimensions", 10, 510, 18);
	//������� ������: obj_mortar -> delete
	Rect_BG_buttons BG_delete_obj_mortar(495, 455, 160, 40, 5);
	User_texts delete_obj_mortar_text("Comic_Sans_MS.TTF", "delete", 530, 460, 25);

	/*�������� ������� �����*/
	//�������� �������� ��������� ������� �� x � �� y �� ��������� [-50;50]:array_of_rings -> random move(rings)
	Rect_BG_buttons BG_RandomMove_array_rings(5, 520, 175, 40, 5);
	User_texts RandomMove_array_rings_text("Comic_Sans_MS.TTF", "random move(rings)", 10, 530, 15);
	//�������� �� �������� WASD ���������: array of rings -> user move(rings) 
	Rect_BG_buttons BG_UserMove_array_rings(5, 580, 175, 40, 5);
	User_texts UserMove_array_rings_text("Comic_Sans_MS.TTF", "user move(rings)", 10, 590, 17);
	//������� ��������� �������: array of rings -> delete_last ring
	Rect_BG_buttons BG_delete_last_elem_array_rings(5, 640, 175, 40, 5);
	User_texts delete_last_elem_array_rings_text("Comic_Sans_MS.TTF", "delete_last ring", 10, 650, 17);
	//������� ��� ��������: array of circles -> delete all circles
	Rect_BG_buttons BG_delete_all_rings(5, 700, 175, 40, 5);
	User_texts delete_all_rings_text("Comic_Sans_MS.TTF", "delete all rings", 10, 710, 17);
	//���������� ��� ���������� �������: array of rings -> (q) - increase dimensions\n(e) - decrease dimensions
	User_texts ChangeDimensions_array_rings_text("Comic_Sans_MS.TTF", "(q) - increase dimensions\n(e) - decrease dimensions", 5, 760, 15);

	/*�������� ������� ������*/
	//�������� �������� ��������� ������� �� x � �� y �� ��������� [-50;50]:array_of_mortars -> random move(mortars)
	Rect_BG_buttons BG_RandomMove_array_mortars(195, 520, 210, 40, 5);
	User_texts RandomMove_array_mortars_text("Comic_Sans_MS.TTF", "random move(mortars)", 200, 530, 15);
	//�������� �� �������� WASD ���������: array of mortars -> user move(mortars) 
	Rect_BG_buttons BG_UserMove_array_mortars(195, 580, 210, 40, 5);
	User_texts UserMove_array_mortars_text("Comic_Sans_MS.TTF", "user move(mortars)", 200, 590, 17);
	//������� ��������� �������: array of mortars -> delete_last mortar
	Rect_BG_buttons BG_delete_last_elem_array_mortars(195, 640, 210, 40, 5);
	User_texts delete_last_elem_array_mortars_text("Comic_Sans_MS.TTF", "delete_last mortar", 200, 650, 17);
	//������� ��� ��������: array of rectangles -> delete all rectangles
	Rect_BG_buttons BG_delete_all_mortars(195, 700, 210, 40, 5);
	User_texts delete_all_mortars_text("Comic_Sans_MS.TTF", "delete all mortars", 200, 710, 17);
	//��������� ������� ��������� ������� ������: array of mortars -> (z) - increase dimensions\n(x) - decrease dimensions
	User_texts ChangeDimensions_array_mortars_text("Comic_Sans_MS.TTF",
		"(z) - increase dimensions\n(x) - decrease dimensions", 220, 760, 15);

	//�������� ���� � ������������ ������� (��������� ������������������ ��������� ����� �� ���������)
	srand(static_cast<unsigned int>(time(0)));

	//����������� �������� ���� ����� ��������������� ����
	int extra_menu{ 0 };
	//���� ������ ������� ������: CREATE, MOVE_AND_CHANGE (��� ������ extra_menu)
	bool menu_create_0{ false }, menu_move_and_change_0{ false }, menu_create_1{ false }, menu_move_and_change_1{ false };
	//��������� �������
	//���� ������ ������� ������ CREATE ->: circle, rectangle, linesegmen, ring
	bool circle_show{ false }, rect_show{ false }, linesegment_show{ false }, ring_show{ false }, mortar_show{false};
	//���� ������ ������� ������ MOVE AND CHANGE ->: obj_circle, obj_rectangle, obj_;inesegment, obj_ring, obj_mortar
	bool submenu_obj_circle{ false }, submenu_obj_rect{ false }, submenu_obj_linesegment{ false }, submenu_obj_ring{ false }, submenu_obj_mortar{false};
	//���� ������ ������� ������ obj_circle -> circle_random_move, obj_rectangle -> rect_user_move, obj_linesegment -> line_user_move, obj_ring -> ring_user_move,
	//obj_mortar -> mortar_user_move
	bool circle_user_move{ false }, rect_user_move{ false }, linesegment_user_move{ false }, ring_user_move{ false }, mortar_user_move{false};
	//���� ������ ������� ������ � obj_circle, obj_rectangle, obj_linesegment, obj_ring, obj_mortar ��������� ��������
	bool circle_change_radius{ false }, rectangle_change_dimensions{ false }, linesegment_change_dimensions{ false }, ring_change_dimensions{ false },
		mortar_change_dimensions{false};
	//�������
	//����� ������� ������ CREATE -> create arrays of graphics primitives, create_15_objs
	bool submenu_create_arrays_0{ false }, create_15_objs{ false }, submenu_create_arrays_1{ false };
	//�������� ������/���������� ��������� ������� � ������� ����� ����������
	int mass_or_single{ ONE_OBJ };
	//����� ������� ������ create arrays of graphics primitives ->: array of circles, array of rectangles, array of linesegments, array of mortars
	bool array_circles_show{ false }, array_rectangles_show{ false }, array_linesegments_show{ false }, array_rings_show{ false }, array_mortars_show{ false };
	//����� ������� ������ array of circles -> user move(circles), array of rectangles -> user move(rectangles), array of rings -> user move(rings),
	//array of mortars -> user move(mortars)
	bool array_circles_user_move{ false }, array_rectangles_user_move{ false }, array_linesegments_user_move{ false }, array_rings_user_move{ false },
		array_mortars_user_move{ false };

	while (window.isOpen())
	{
		/*���������� ��������� ������ ��������� �������� �� ����*/
		//����
		//����� IMAGE
		image_text.m_setFillColor(111, 206, 253);
		//������ CREATE
		BG_create.m_setDefaultColor();
		create_text.m_setDefaultColor();
		//������ MOVE AND CHANGE
		BG_move_and_change.m_setDefaultColor();
		move_and_change_text.m_setDefaultColor();
		//������ EXIT
		BG_exit.m_setDefaultColor();
		exit_text.m_setDefaultColor();
		//������ NEXT
		BG_next.m_setDefaultColor();
		next_text.m_setDefaultColor();
		//������ BACK
		BG_back.m_setDefaultColor();
		back_text.m_setDefaultColor();

		//�������
		BG_submenu_obj.m_setFillColor(34, 177, 76);

		//������� CREATE_0
		//CREATE -> circle
		BG_circle.m_setFillColor(195, 195, 195); //�.�. � ������ �������������� ���� - ��� � MENU � IMAGE
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

		//������� CREATE_1
		//CREATE -> ring
		BG_ring.m_setFillColor(195, 195, 195);
		ring_text.m_setDefaultColor();
		//CREATE -> mortar
		BG_mortar.m_setFillColor(195, 195, 195);
		mortar_text.m_setDefaultColor();
		//CREATE -> create arrays of complex objects
		BG_create_arrays_of_complex_objects.m_setFillColor(195, 195, 195);
		create_arrays_of_complex_objects_text.m_setDefaultColor();
		//create arrays of complex objects -> array of rings
		BG_create_array_rings.m_setFillColor(195, 195, 195);
		create_array_rings_text.m_setDefaultColor();
		//create arrays of complex objects -> array of mortars
		BG_create_array_mortars.m_setFillColor(195, 195, 195);
		create_array_mortars_text.m_setDefaultColor();

		//������ ����������
		//MOVE AND CHANGE -> obj_circle
		BG_obj_circle.m_setFillColor(195, 195, 195);
		obj_circle_text.m_setDefaultColor();
		//obj_circle -> circle_random_move
		BG_RandomMove_obj_circle.m_setDefaultColor();
		RandomMove_obj_circle_text.m_setDefaultColor();
		//obj_circle -> delete
		BG_delete_obj_circle.m_setDefaultColor();
		delete_obj_circle_text.m_setDefaultColor();

		//������ ��������������
		//MOVE AND CHANGE -> obj_rectangle
		BG_obj_rect.m_setFillColor(195, 195, 195);
		obj_rect_text.m_setDefaultColor();
		//obj_rectangle -> rect_random_move
		BG_RandomMove_obj_rect.m_setDefaultColor();
		RandomMove_obj_rect_text.m_setDefaultColor();
		BG_delete_obj_rectangle.m_setDefaultColor();
		delete_obj_rectangle_text.m_setDefaultColor();

		//������ �������
		//MOVE_AND_CHANGE -> obj_linesegment
		BG_obj_linesegment.m_setFillColor(195, 195, 195);
		obj_linesegment_text.m_setDefaultColor();
		//obj_linesegment -> line_random_move
		BG_RandomMove_obj_linesegment.m_setDefaultColor();
		RandomMove_obj_linesegment_text.m_setDefaultColor();
		//obj_linesegment -> delete
		BG_delete_obj_linesegment.m_setDefaultColor();
		delete_obj_linesegment_text.m_setDefaultColor();

		//������ ������
		//MOVE AND CHANGE -> obj_ring
		BG_obj_ring.m_setFillColor(195, 195, 195);
		obj_ring_text.m_setDefaultColor();
		//obj_ring -> ring_random_move
		BG_RandomMove_obj_ring.m_setDefaultColor();
		RandomMove_obj_ring_text.m_setDefaultColor();
		//obj_ring -> delete
		BG_delete_obj_ring.m_setDefaultColor();
		delete_obj_ring_text.m_setDefaultColor();

		//����� �������
		//MOVE AND CHANGE -> obj_mortar
		BG_obj_mortar.m_setFillColor(195, 195, 195);
		obj_mortar_text.m_setDefaultColor();
		//obj_mortar -> mortar_random_move
		BG_RandomMove_obj_mortar.m_setDefaultColor();
		RandomMove_obj_mortar_text.m_setDefaultColor();
		//obj_mortar -> delete
		BG_delete_obj_mortar.m_setDefaultColor();
		delete_obj_mortar_text.m_setDefaultColor();

		//������ �����������
		//array of circles -> random move(circles)
		BG_RandomMove_array_circles.m_setFillColor(195, 195, 195);
		RandomMove_array_circles_text.m_setDefaultColor();
		//array of circles -> delete_last circle
		BG_delete_last_elem_array_circles.m_setFillColor(195, 195, 195);
		delete_last_elem_array_circles_text.m_setDefaultColor();
		//array of circles -> delete all circles
		BG_delete_all_circles.m_setFillColor(195, 195, 195);
		delete_all_circles_text.m_setDefaultColor();

		//������ ���������������
		//array of rectangles -> random move(rectangles)
		BG_RandomMove_array_rectangles.m_setFillColor(195, 195, 195);
		RandomMove_array_rectangles_text.m_setDefaultColor();
		//array of rectangles -> delete_last rectangle
		BG_delete_last_elem_array_rectangles.m_setFillColor(195, 195, 195);
		delete_last_elem_array_rectangles_text.m_setDefaultColor();
		//array of rectangles -> delete all rectangles
		BG_delete_all_rectangles.m_setFillColor(195, 195, 195);
		delete_all_rectangles_text.m_setDefaultColor();

		//������ ��������
		//array of linesegments -> random move(linesegments)
		BG_RandomMove_array_linesegments.m_setFillColor(195, 195, 195);
		RandomMove_array_linesegments_text.m_setDefaultColor();
		//array of linesegments -> delete_lest_linesegment
		BG_delete_last_elem_array_linesegments.m_setFillColor(195, 195, 195);
		delete_last_elem_array_linesegments_text.m_setDefaultColor();
		//array of linesegments -> delete all linesegments
		BG_delete_all_linesegments.m_setFillColor(195, 195, 195);
		delete_all_linesegments_text.m_setDefaultColor();

		//������ �����
		//array of rings -> random move(rings)
		BG_RandomMove_array_rings.m_setFillColor(195, 195, 195);
		RandomMove_array_rings_text.m_setDefaultColor();
		//array of rings -> delete_last ring
		BG_delete_last_elem_array_rings.m_setFillColor(195, 195, 195);
		delete_last_elem_array_rings_text.m_setDefaultColor();
		//array of rings -> delete all rings;
		BG_delete_all_rings.m_setFillColor(195, 195, 195);
		delete_all_rings_text.m_setDefaultColor();

		//������ ������
		//array of mortars -> random move(mortars)
		BG_RandomMove_array_mortars.m_setFillColor(195, 195, 195);
		RandomMove_array_mortars_text.m_setDefaultColor();
		//array of mortars -> delete_last mortar
		BG_delete_last_elem_array_mortars.m_setFillColor(195, 195, 195);
		delete_last_elem_array_mortars_text.m_setDefaultColor();
		//array of mortars -> delete all mortars;
		BG_delete_all_mortars.m_setFillColor(195, 195, 195);
		delete_all_mortars_text.m_setDefaultColor();

		/*���������� ��������� ������ ��������� �������� �� ���� (��� ������������ �������)*/
		//������ ����������
		//������ ������ obj_circle -> circle_user_move
		if (!circle_user_move)
		{
			BG_UserMove_obj_circle.m_setDefaultColor();
			UserMove_obj_circle_text.m_setDefaultColor();
		}
		//������ ������ obj_circle -> circle_change_radius:\n(q) - increase\n(e) - decrease
		if (!circle_change_radius)
		{
			BG_ChangeRadius_obj_circle.m_setDefaultColor();
			ChangeRadius_obj_circle_text.m_setDefaultColor();
		}

		//������ ��������������
		//������ ������ obj_rectangle -> rect_user_move
		if (!rect_user_move)
		{
			BG_UserMove_obj_rect.m_setDefaultColor();
			UserMove_obj_rect_text.m_setDefaultColor();
		}
		//������ ������ obj_rectangle -> rectangle_change_dimensions:\n(z) - increase length\n(x) - decrease length\n(c) - increase width\n(v) - decrease width
		if (!rectangle_change_dimensions)
		{
			BG_ChangeWidthLength_obj_rectangle.m_setDefaultColor();
			ChangeWidthLength_obj_rectangle_text.m_setDefaultColor();
		}

		//������ �������
		if (!linesegment_user_move)
		{
			BG_UserMove_obj_linesegment.m_setDefaultColor();
			UserMove_obj_linesegment_text.m_setDefaultColor();
		}
		//������ ������ obj_linesegment -> linesegment_change_length:\n(f) - increase\n(g) - decrease\n(h) - rotate
		if (!linesegment_change_dimensions)
		{
			BG_ChangeDimensions_obj_linesegment.m_setDefaultColor();
			ChangeDimensions_obj_linesegment_text.m_setDefaultColor();
		}

		//������ ������
		//������ ������ obj_ring -> ring_user_move
		if (!ring_user_move)
		{
			BG_UserMove_obj_ring.m_setDefaultColor();
			UserMove_obj_ring_text.m_setDefaultColor();
		}
		//������ ������ obj_ring -> ring_change_radius:\n(q) - increase\n(e) - decrease
		if (!ring_change_dimensions)
		{
			BG_ChangeDimensions_obj_ring.m_setDefaultColor();
			ChangeDimensions_obj_ring_text.m_setDefaultColor();
		}

		//������ �������
		//������ ������ obj_mortar -> mortar_user_move
		if (!mortar_user_move)
		{
			BG_UserMove_obj_mortar.m_setDefaultColor();
			UserMove_obj_mortar_text.m_setDefaultColor();
		}
		//������ ������ obj_mortar -> mortar_change_dimensions:\n(z) - increase dimensions\n(x) - decrease dimensions
		if (!mortar_change_dimensions)
		{
			BG_ChangeDimensions_obj_mortar.m_setDefaultColor();
			ChangeDimensions_obj_mortar_text.m_setDefaultColor();
		}

		/*������ �������� ������*/
		if (!create_15_objs)
		{
			BG_create_15_objs.m_setDefaultColor();
			create_15_objs_text.m_setDefaultColor();
		}
		//������ �����������
		//������ ������ array of circle -> user move(circles)
		if (!array_circles_user_move)
		{
			BG_UserMove_array_circles.m_setFillColor(195, 195, 195);
			UserMove_array_circles_text.m_setDefaultColor();
		}
		//������ ���������������
		if (!array_rectangles_user_move)
		{
			BG_UserMove_array_rectangles.m_setFillColor(195, 195, 195);
			UserMove_array_rectangles_text.m_setDefaultColor();
		}
		//������ ��������
		if (!array_linesegments_user_move)
		{
			BG_UserMove_array_linesegments.m_setFillColor(195, 195, 195);
			UserMove_array_linesegments_text.m_setDefaultColor();
		}
		//������ �����
		if (!array_rings_user_move)
		{
			BG_UserMove_array_rings.m_setFillColor(195, 195, 195);
			UserMove_array_rings_text.m_setDefaultColor();
		}
		//������ ������
		if (!array_mortars_user_move)
		{
			BG_UserMove_array_mortars.m_setFillColor(195, 195, 195);
			UserMove_array_mortars_text.m_setDefaultColor();
		}

		/*������� ���������� ��� ��������� ������� �� ������*/
		//������ ����: NEXT, BACK, CREATE, MOVE AND CHANGE, EXIT
		bool stage_next{ false }, stage_back{ false }, stage_create_0{ false }, stage_move_and_change_0{ false }, stage_create_1{ false }, stage_move_and_change_1{ false },
			stage_exit{ false };
		//������ ����������
		bool stage_circle_create{ false }; //������ CREATE -> circle
		bool stage_obj_circle{ false };//������ MOVE AND CHANGE -> obj_circle
		//������ obj_circle ->: circle_random_move, circle_user_move, circle_change_radius, delete
		bool stage_circle_random_move{ false }, stage_circle_user_move{ false }, stage_circle_change_radius{ false }, stage_delete_obj_circle{ false };

		//������ ��������������
		bool stage_rect_create{ false };//������ CREATE -> rectangle
		bool stage_obj_rect{ false };//MOVE AND CHANGE -> obj_rectangle
		//������ obj_rectangle ->: rect_random_move, rect_user_move, rectangle_change_dimensions, delete
		bool stage_rect_random_move{ false }, stage_rect_user_move{ false }, stage_rect_change_dimensions{ false }, stage_delete_obj_rect{ false };

		//������ �������
		bool stage_linesegment_create{ false };//������ CREATE -> linesegment
		bool stage_obj_linesegment{ false };//������ MOVE AND CHANGE -> obj_linesegment
		//������ obj_linesegment ->: line_random_move, line_user_move, linesegment_change_dimensions, delete
		bool stage_linesegment_random_move{ false }, stage_linesegment_user_move{ false }, stage_linesegment_change_dimensions{ false }, stage_delete_obj_linesegment{ false };

		//������ ������
		bool stage_ring_create{ false };//������ CREATE -> ring
		bool stage_obj_ring{ false };//������ MOVE AND CHANGE -> obj_ring
		//������ obj_ring ->: ring_random_move, ring_user_move, ring_change_dimensions, delete
		bool stage_ring_random_move{ false }, stage_ring_user_move{ false }, stage_ring_change_dimensions{ false }, stage_delete_obj_ring{ false };

		//������ ������
		bool stage_mortar_create{ false };//������ CREATE -> mortar
		bool stage_obj_mortar{ false };//������ MOVE AND CHANGE -> obj_mortar
		//������ obj_mortar ->: mortar_random_move, mortar_user_move, mortar_change_dimensions, delete
		bool stage_mortar_random_move{ false }, stage_mortar_user_move{ false }, stage_mortar_change_dimensions{ false }, stage_delete_obj_mortar{ false };

		//�������
		//������ CREATE -> create arrays of graphics primitives, create arrays of complex objects
		bool stage_create_arrays_of_graphic_primitives{false}, stage_create_arrays_of_complex_objects{false};
		bool stage_create_15_objs{ false };//������ create arrays of graphics primitives -> create_15_objs
		//������ arrays of graphics primitives ->: array of circles, array of rectangles, array of linesegments, array of rings, array of mortars
		bool stage_create_array_circles{ false }, stage_create_array_rectangles(false), stage_create_array_linesegments{ false }, stage_create_array_rings{ false },
			stage_create_array_mortars{ false };
		//������ �����������. ������ array of circles ->: random move(circles), user move (circles), delete_last circle, delete all circles
		bool stage_RandomMove_array_circles{ false }, stage_user_move_array_circles{ false }, stage_delete_last_elem_array_circles{ false },
			stage_delete_all_circles{ false };
		//������ ���������������. ������ array of rectangles ->: random move(rectangles), user move(rectangles), delete_last rectangle, delete all rectangles
		bool stage_RandomMove_array_rectangles{ false }, stage_user_move_array_rectangles{ false }, stage_delete_last_elem_array_rectangles{ false },
			stage_delete_all_rectangles{ false };
		//������ ��������. ������ array of linesegments ->: random move(linesegments), user move(linesegments), delete_last linesegment, delete all linesegments
		bool stage_RandomMove_array_linesegments{ false }, stage_user_move_array_linesegments{ false }, stage_delete_last_elem_array_linesegments{ false },
			stage_delete_all_linesegments{ false };
		//������ �����. ������ array of rings ->: random move(rings), user move(rings), delete_last ring, delete all rings
		bool stage_RandomMove_array_rings{ false }, stage_user_move_array_rings{ false }, stage_delete_last_elem_array_rings{ false }, stage_delete_all_rings{ false };
		//������ ������. ������ array of mortar ->: random move(mortars), user move(mortars), delete_last mortar, delete all mortars
		bool stage_RandomMove_array_mortars{ false }, stage_user_move_array_mortars{ false }, stage_delete_last_elem_array_mortars{ false }, stage_delete_all_mortars{ false };

		/*����������� ������ ��� ��������� ������� ���� (� ���������� �������� ��������������� ����������*/
		//����
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
			else
				stage_create_1 = true;
		}

		if (sf::IntRect(5, 229, 200, 120).contains(sf::Mouse::getPosition(window)))//MOVE AND CHANGE
		{
			BG_move_and_change.m_setActiveColor();
			move_and_change_text.m_setActiveColor();
			if (extra_menu == 0)
				stage_move_and_change_0 = true;
			else
				stage_move_and_change_1 = true;
		}
		if (sf::IntRect(5, 840, 160, 50).contains(sf::Mouse::getPosition(window)))//EXIT
		{
			BG_exit.m_setActiveColor();
			exit_text.m_setActiveColor();
			stage_exit = true;
		}

		if (extra_menu == 0)
		{
			//������ ����������
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

			//������ ��������������
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

			//������ �������
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

			//�������
			if (sf::IntRect(220, 160, 473, 40).contains(sf::Mouse::getPosition(window)) && menu_create_0)//CREATE -> create arrays of gparhics primitives
			{
				BG_create_arrays_of_graphic_primitives.m_setActiveColor();
				create_arrays_of_graphic_primitives_text.m_setActiveColor();
				stage_create_arrays_of_graphic_primitives = true;
			}

			//�������� �� 15 ���� ���������� �� ������� ������
			if (sf::IntRect(500, 360, 200, 80).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_0 && menu_create_0)
			{
				BG_create_15_objs.m_setActiveColor();
				create_15_objs_text.m_setActiveColor();
				stage_create_15_objs = true;
			}
			//������ �����������
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

			//������ ���������������
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

			//������ ��������
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
		else
		{
			//������ ������
			if (sf::IntRect(220, 97, 140, 40).contains(sf::Mouse::getPosition(window)) && menu_create_1)//CREATE -> ring
			{
				BG_ring.m_setActiveColor();
				ring_text.m_setActiveColor();
				stage_ring_create = true;
			}

			if (sf::IntRect(220, 229, 140, 40).contains(sf::Mouse::getPosition(window)) && menu_move_and_change_1)//MOVE AND CHANGE -> obj_ring
			{
				BG_obj_ring.m_setActiveColor();
				obj_ring_text.m_setActiveColor();
				stage_obj_ring = true;
			}

			if (sf::IntRect(5, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_ring && menu_move_and_change_1)//obj_ring -> ring_random_move
			{
				BG_RandomMove_obj_ring.m_setActiveColor();
				RandomMove_obj_ring_text.m_setActiveColor();
				stage_ring_random_move = true;
			}

			if (sf::IntRect(250, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_ring && menu_move_and_change_1)//obj_ring -> ring_user_move
			{
				BG_UserMove_obj_ring.m_setActiveColor();
				UserMove_obj_ring_text.m_setActiveColor();
				stage_ring_user_move = true;
			}

			if (sf::IntRect(5, 510, 300, 80).contains(sf::Mouse::getPosition(window)) && submenu_obj_ring && menu_move_and_change_1)//obj_ring -> ring_change_radius:\n(q) - increase\n(e) - decrease
			{
				BG_ChangeDimensions_obj_ring.m_setActiveColor();
				ChangeDimensions_obj_ring_text.m_setActiveColor();
				stage_ring_change_dimensions = true;
			}
			if (sf::IntRect(495, 455, 160, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_ring && menu_move_and_change_1)//obj_ring -> delete
			{
				BG_delete_obj_ring.m_setActiveColor();
				delete_obj_ring_text.m_setActiveColor();
				stage_delete_obj_ring = true;
			}

			//������ �������
			if (sf::IntRect(375, 97, 140, 40).contains(sf::Mouse::getPosition(window)) && menu_create_1)//CREATE -> mortar
			{
				BG_mortar.m_setActiveColor();
				mortar_text.m_setActiveColor();
				stage_mortar_create = true;
			}
			if (sf::IntRect(375, 229, 160, 40).contains(sf::Mouse::getPosition(window)) && menu_move_and_change_1)//MOVE AND CHANGE -> obj_mortar
			{
				BG_obj_mortar.m_setActiveColor();
				obj_mortar_text.m_setActiveColor();
				stage_obj_mortar = true;
			}

			if (sf::IntRect(5, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_mortar && menu_move_and_change_1)//obj_mortar -> mortar_random_move
			{
				BG_RandomMove_obj_mortar.m_setActiveColor();
				RandomMove_obj_mortar_text.m_setActiveColor();
				stage_mortar_random_move = true;
			}

			if (sf::IntRect(250, 455, 230, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_mortar && menu_move_and_change_1)//obj_mortar -> mortar_user_move
			{
				BG_UserMove_obj_mortar.m_setActiveColor();
				UserMove_obj_mortar_text.m_setActiveColor();
				stage_mortar_user_move = true;
			}

			if (sf::IntRect(5, 510, 300, 160).contains(sf::Mouse::getPosition(window)) && submenu_obj_mortar && menu_move_and_change_1)//obj_mortar -> mortar_change_dimensions
			{
				BG_ChangeDimensions_obj_mortar.m_setActiveColor();
				ChangeDimensions_obj_mortar_text.m_setActiveColor();
				stage_mortar_change_dimensions = true;
			}
			if (sf::IntRect(495, 455, 160, 40).contains(sf::Mouse::getPosition(window)) && submenu_obj_mortar && menu_move_and_change_1)//obj_mortar -> delete
			{
				BG_delete_obj_mortar.m_setActiveColor();
				delete_obj_mortar_text.m_setActiveColor();
				stage_delete_obj_mortar = true;
			}

			//�������
			if (sf::IntRect(220, 160, 473, 40).contains(sf::Mouse::getPosition(window)) && menu_create_1)//CREATE -> create arrays of complex objects
			{
				BG_create_arrays_of_complex_objects.m_setActiveColor();
				create_arrays_of_complex_objects_text.m_setActiveColor();
				stage_create_arrays_of_complex_objects = true;
			}

			//�������� �� 15 ���� ���������� �� ������� ������
			if (sf::IntRect(500, 360, 200, 80).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)
			{
				BG_create_15_objs.m_setActiveColor();
				create_15_objs_text.m_setActiveColor();
				stage_create_15_objs = true;
			}

			//������ �����
			if (sf::IntRect(5, 460, 175, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//create arrays of complex objects -> array of rings
			{
				BG_create_array_rings.m_setActiveColor();
				create_array_rings_text.m_setActiveColor();
				stage_create_array_rings = true;
			}

			if (sf::IntRect(5, 520, 175, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//array of rings -> random move(rings)
			{
				BG_RandomMove_array_rings.m_setActiveColor();
				RandomMove_array_rings_text.m_setActiveColor();
				stage_RandomMove_array_rings = true;
			}
			if (sf::IntRect(5, 580, 175, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//array of rings -> user move(rings)
			{
				BG_UserMove_array_rings.m_setActiveColor();
				UserMove_array_rings_text.m_setActiveColor();
				stage_user_move_array_rings = true;
			}
			if (sf::IntRect(5, 640, 175, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//array of rings -> delete_last ring
			{
				BG_delete_last_elem_array_rings.m_setActiveColor();
				delete_last_elem_array_rings_text.m_setActiveColor();
				stage_delete_last_elem_array_rings = true;
			}
			if (sf::IntRect(5, 700, 175, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//array of rings -> delete all rings
			{
				BG_delete_all_rings.m_setActiveColor();
				delete_all_rings_text.m_setActiveColor();
				stage_delete_all_rings = true;
			}

			//������ ������
			if (sf::IntRect(195, 460, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//create arrays of complex objects -> array of mortars
			{
				BG_create_array_mortars.m_setActiveColor();
				create_array_mortars_text.m_setActiveColor();
				stage_create_array_mortars = true;
			}

			if (sf::IntRect(195, 520, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//array of mortars -> random move(mortar)
			{
				BG_RandomMove_array_mortars.m_setActiveColor();
				RandomMove_array_mortars_text.m_setActiveColor();
				stage_RandomMove_array_mortars = true;
			}

			if (sf::IntRect(195, 580, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//array of mortars -> user move(mortars)
			{
				BG_UserMove_array_mortars.m_setActiveColor();
				UserMove_array_mortars_text.m_setActiveColor();
				stage_user_move_array_mortars = true;
			}

			if (sf::IntRect(195, 640, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//array of mortars -> delete_last mortar
			{
				BG_delete_last_elem_array_mortars.m_setActiveColor();
				delete_last_elem_array_mortars_text.m_setActiveColor();
				stage_delete_last_elem_array_mortars = true;
			}

			if (sf::IntRect(195, 700, 210, 40).contains(sf::Mouse::getPosition(window)) && submenu_create_arrays_1 && menu_create_1)//array of mortars -> delete all mortars
			{
				BG_delete_all_mortars.m_setActiveColor();
				delete_all_mortars_text.m_setActiveColor();
				stage_delete_all_mortars = true;
			}
		}

		sf::Event event_menu_click;
		while (window.pollEvent(event_menu_click))
		{
			//�������� ���� �� "�������"
			if (event_menu_click.type == sf::Event::Closed)
				window.close();
			//���������� ������� ����� OnCreate (��������� ������ �� �������, �.�. ������ � ��������� ������)
			if (event_menu_click.type == event_menu_click.MouseButtonReleased && event_menu_click.mouseButton.button == sf::Mouse::Left)
			{
				//������ ������ NEXT
				if (stage_next)
					extra_menu = 1;
				if (stage_back)
					extra_menu = 0;
				//������ ������ CREATE
				if (stage_create_0)
					menu_create_0 = !menu_create_0;
				if (stage_create_1)
					menu_create_1 = !menu_create_1;
				//������ ������ MOVE AND CHANGE
				if (stage_move_and_change_0)
					menu_move_and_change_0 = !menu_move_and_change_0;
				if (stage_move_and_change_1)
					menu_move_and_change_1 = !menu_move_and_change_1;

				/*��������� �������*/
				//������ ����������
				//������ ������ CREATE -> circle
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
						float x_circle{ getRandomNumber(715, 1490) };
						float y_circle{ getRandomNumber(105, 890) };
						f_ptr_obj_circle->Free(f_ptr_obj_circle);
						f_ptr_obj_circle = new Circle({x_circle, y_circle}, radius_circle);
						f_ptr_obj_circle->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_circle->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_circle->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
					}
				}
				if (circle_show)
				{
					//������ ������ MOVE AND CHANGE -> obj_circle
					if (stage_obj_circle)
					{
						submenu_obj_circle = !submenu_obj_circle;
						submenu_obj_rect = false;
						submenu_obj_linesegment = false;
						submenu_create_arrays_0 = false;
					}
					//������ ������ circle -> circle_random_move
					if (stage_circle_random_move)
						doOffsetCircle(f_ptr_obj_circle);
					//������ ������ obj_circle -> circle_user_move
					if (stage_circle_user_move)
					{
						circle_user_move = !circle_user_move;
						rect_user_move = false;
						linesegment_user_move = false;
						array_rectangles_user_move = false;
						array_linesegments_user_move = false;
						ring_user_move = false;
						array_rings_user_move = false;
						mortar_user_move = false;
						array_mortars_user_move = false;
					}
					//������ ������ ��������� ������� obj_circle -> �������� ������
					if (stage_circle_change_radius)
						circle_change_radius = !circle_change_radius;
					//������ ������ �������� ������� ���������� obj_circle -> delete
					if (stage_delete_obj_circle)
					{
						f_ptr_obj_circle->Free(f_ptr_obj_circle);
						circle_show = false;
						submenu_obj_circle = false;
						circle_user_move = false;
						circle_change_radius = false;
					}
				}

				//������ ��������������
				//������ ������ CREATE -> rectangle
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
						float x_rect{ getRandomNumber(710, 1450) };
						float y_rect{ getRandomNumber(100, 875) };
						f_ptr_obj_rect->Free(f_ptr_obj_rect);
						f_ptr_obj_rect = new Rectangle({ x_rect, y_rect }, length_rect, width_rect);
						f_ptr_obj_rect->setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_rect->setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_rect->setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
					}
				}
				if (rect_show)
				{
					//������ ������ MOVE AND CHANGE -> obj_rectangle
					if (stage_obj_rect)
					{
						submenu_obj_rect = !submenu_obj_rect;
						submenu_obj_circle = false;
						submenu_obj_linesegment = false;
						submenu_create_arrays_0 = false;
					}
					//������ ������ obj_rectangle -> rect_random_move
					if (stage_rect_random_move)
						doOffsetRect(f_ptr_obj_rect);
					//������ ������ obj_rectangle -> rect_user_move
					if (stage_rect_user_move)
					{
						rect_user_move = !rect_user_move;
						circle_user_move = false;
						linesegment_user_move = false;
						array_circles_user_move = false;
						array_linesegments_user_move = false;
						ring_user_move = false;
						array_rings_user_move = false;
						mortar_user_move = false;
						array_mortars_user_move = false;
					}
					//������ ������ ��������� �������� obj_rectangle -> �������� �������
					if (stage_rect_change_dimensions)
						rectangle_change_dimensions = !rectangle_change_dimensions;
					//������ ������ �������� ������� ������������� obj_rectangle -> delete
					if (stage_delete_obj_rect)
					{
						f_ptr_obj_rect->Free(f_ptr_obj_rect);
						rect_show = false;
						submenu_obj_rect = false;
						rect_user_move = false;
						rectangle_change_dimensions = false;
					}
				}

				//������ �������
				//������ ������ CREATE -> linesegment
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
						float x_linesegment{getRandomNumber(705, 1500)};
						float y_linesegment{getRandomNumber(95, 900)};
						f_ptr_obj_linesegment->Free(f_ptr_obj_linesegment);
						f_ptr_obj_linesegment = new Linesegment({ x_linesegment, y_linesegment }, length_linesegment, degree_linesegment);
						f_ptr_obj_linesegment->setColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_linesegment->setVisibility(static_cast<int>(getRandomNumber(150, 255)));
					}
				}
				if (linesegment_show)
				{
					//������ ������ CREATE -> obj_linesegment
					if (stage_obj_linesegment)
					{
						submenu_obj_linesegment = !submenu_obj_linesegment;
						submenu_obj_circle = false;
						submenu_obj_rect = false;
						submenu_create_arrays_0 = false;
					}
					//������ ������ obj_linesegment -> line_random_move
					if (stage_linesegment_random_move)
						doOffsetlinesegment(f_ptr_obj_linesegment);
					//������ ������ obj_linesegment -> line_user_move
					if (stage_linesegment_user_move)
					{
						linesegment_user_move = !linesegment_user_move;
						circle_user_move = false;
						rect_user_move = false;
						array_circles_user_move = false;
						array_rectangles_user_move = false;
						ring_user_move = false;
						array_rings_user_move = false;
						mortar_user_move = false;
						array_mortars_user_move = false;
					}
					//������ ������ obj_linesegment -> linesegment_change_dimensions
					if (stage_linesegment_change_dimensions)
						linesegment_change_dimensions = !linesegment_change_dimensions;
					//������ ������ obj_linesegment -> delete
					if (stage_delete_obj_linesegment)
					{
						f_ptr_obj_linesegment->Free(f_ptr_obj_linesegment);
						linesegment_show = false;
						submenu_obj_linesegment = false;
						linesegment_user_move = false;
						linesegment_change_dimensions = false;
					}
				}

				//������ ������
				//������ ������ CREATE -> ring
				if (stage_ring_create)
				{
					ring_show = true;
					if (f_ptr_obj_ring == nullptr)
					{
						f_ptr_obj_ring = new Ring();
					}
					else
					{
						float x_ring{ getRandomNumber(760, 1445) };
						float y_ring{ getRandomNumber(150, 845) };
						float radius_circle_outer{ getRandomNumber(60, 150) };
						float radius_circle_inner{ getRandomNumber(30, radius_circle_outer - 10) };
						delete f_ptr_obj_ring;
						f_ptr_obj_ring = nullptr;
						Circle circle_outer({x_ring, y_ring}, radius_circle_outer);
						Circle circle_inner({ x_ring, y_ring }, radius_circle_inner);
						f_ptr_obj_ring = new Ring(circle_outer, circle_inner);
						f_ptr_obj_ring->getCircleOuter().setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_ring->getCircleOuter().setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_ring->getCircleOuter().setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_ring->getCircleInner().setFillColor(67, 136, 169);
						f_ptr_obj_ring->getCircleInner().setVisibility(255);
						f_ptr_obj_ring->getCircleInner().setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
					}
				}
				if (ring_show)
				{
					//������ ������ MOVE AND CHANGE -> obj_ring
					if (stage_obj_ring)
					{
						submenu_obj_ring = !submenu_obj_ring;
						submenu_obj_mortar = false;
						submenu_create_arrays_1 = false;
					}
					//������ ������ ring -> ring_random_move
					if (stage_ring_random_move)
						doOffsetRing(f_ptr_obj_ring);
					//������ ������ obj_ring -> ring_user_move
					if (stage_ring_user_move)
					{
						ring_user_move = !ring_user_move;
						circle_user_move = false;
						array_circles_user_move = false;
						rect_user_move = false;
						array_rectangles_user_move = false;
						linesegment_user_move = false;
						array_linesegments_user_move = false;
						mortar_user_move = false;
						array_mortars_user_move = false;
					}
					//������ ������ ��������� �������� obj_ring -> �������� �������
					if (stage_ring_change_dimensions)
						ring_change_dimensions = !ring_change_dimensions;
					//������ ������ �������� ������� ������ obj_ring -> delete
					if (stage_delete_obj_ring)
					{
						delete f_ptr_obj_ring;
						f_ptr_obj_ring = nullptr;
						ring_show = false;
						submenu_obj_ring = false;
						ring_user_move = false;
						ring_change_dimensions = false;
					}
				}

				//������ �������
				//������ ������ CREATE -> mortar
				if (stage_mortar_create)
				{
					mortar_show = true;
					if (f_ptr_obj_mortar == nullptr)
					{
						f_ptr_obj_mortar = new Mortar();
					}
					else
					{
						float length_body{ getRandomNumber(50, 100) };
						float width_body{ getRandomNumber(100, 150) };
						float degree_fire{ getRandomNumber(225, 315) };
						float length_fire{ getRandomNumber(50, length_body) };
						float radius_wheel{ length_body / 2 };
						float x_mortar{ getRandomNumber(710, 1495 - length_body) };
						float y_mortar{ getRandomNumber(100, 900 - radius_wheel - width_body) };
						delete f_ptr_obj_mortar;
						f_ptr_obj_mortar = nullptr;
						Rectangle body_part{ {x_mortar, y_mortar}, length_body, width_body };
						Circle wheel_part{ {x_mortar + radius_wheel, y_mortar + width_body}, radius_wheel };
						Linesegment fire_part{ {x_mortar + length_body / 2, y_mortar - 5}, length_fire, degree_fire };
						f_ptr_obj_mortar = new Mortar(body_part, wheel_part, fire_part);
						//������� ���� �������
						f_ptr_obj_mortar->getRectangleObj().setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_mortar->getRectangleObj().setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_mortar->getRectangleObj().setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						//������� ������ �������
						f_ptr_obj_mortar->getCircleObj().setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_mortar->getCircleObj().setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_mortar->getCircleObj().setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						//������� �������� �������
						f_ptr_obj_mortar->getLineObj().setColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						f_ptr_obj_mortar->getLineObj().setVisibility(static_cast<int>(getRandomNumber(150, 255)));
					}
				}
				if (mortar_show)
				{
					//������ ������ MOVE AND CHANGE -> obj_mortar
					if (stage_obj_mortar)
					{
						submenu_obj_mortar = !submenu_obj_mortar;
						submenu_obj_ring = false;
						submenu_create_arrays_1 = false;
					}
					//������ ������ mortar -> mortar_random_move
					if (stage_mortar_random_move)
						doOffsetMortar(f_ptr_obj_mortar);
					//������ ������ obj_mortar -> mortar_user_move
					if (stage_mortar_user_move)
					{
						mortar_user_move = !mortar_user_move;
						circle_user_move = false;
						array_circles_user_move = false;
						rect_user_move = false;
						array_rectangles_user_move = false;
						linesegment_user_move = false;
						array_linesegments_user_move = false;
						ring_user_move = false;
						array_rings_user_move = false;
					}
					//������ ������ ��������� �������� obj_mortar -> �������� �������
					if (stage_mortar_change_dimensions)
						mortar_change_dimensions = !mortar_change_dimensions;
					//������ ������ �������� ������� ������ obj_mortar -> delete
					if (stage_delete_obj_mortar)
					{
						delete f_ptr_obj_mortar;
						f_ptr_obj_mortar = nullptr;
						mortar_show = false;
						submenu_obj_mortar = false;
						mortar_user_move = false;
						mortar_change_dimensions = false;
					}
				}

				/*������� ����������� ����������*/
				//������ ������ CREATE -> create arrays of graphics primitives
				if (stage_create_arrays_of_graphic_primitives)
				{
					submenu_create_arrays_0 = !submenu_create_arrays_0;
					submenu_obj_circle = false;
					submenu_obj_rect = false;
					submenu_obj_linesegment = false;
				}
				
				if (stage_create_arrays_of_complex_objects)
				{
					submenu_create_arrays_1 = !submenu_create_arrays_1;
					submenu_obj_ring = false;
					submenu_obj_mortar = false;
				}

				if (stage_create_15_objs)
				{
					create_15_objs = !create_15_objs;
					if (create_15_objs)
						mass_or_single = SEVERAL_OBJS;
					else
						mass_or_single = ONE_OBJ;
				}
				//������ �����������
				//������ ������ create arrays of graphics primitives -> array of circles
				if (stage_create_array_circles)
				{
					array_circles_show = true;
					for (int i{}; i < mass_or_single; i++)
					{
						Circle* ptr_new_elem_array_circles{ nullptr };
						float radius_circle{ getRandomNumber(10,100) };
						float x_circle{ getRandomNumber(715, 1490) };
						float y_circle{ getRandomNumber(105, 890) };
						ptr_new_elem_array_circles = new Circle({ x_circle, y_circle }, radius_circle);
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
						ring_user_move = false;
						array_rings_user_move = false;
						mortar_user_move = false;
						array_mortars_user_move = false;
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

				//������ ���������������
				//������ ������ create arrays of graphics primitives -> array of rectangles
				if (stage_create_array_rectangles)
				{
					array_rectangles_show = true;
					for (int i{}; i < mass_or_single; i++)
					{
						Rectangle* ptr_new_elem_array_rectangles{ nullptr };
						float length_rect{ getRandomNumber(50, 300) };
						float width_rect{ getRandomNumber(25, 150) };
						float x_rect{ getRandomNumber(710, 1450) };
						float y_rect{ getRandomNumber(100, 875) };
						ptr_new_elem_array_rectangles = new Rectangle({ x_rect, y_rect }, length_rect, width_rect);
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
						ring_user_move = false;
						array_rings_user_move = false;
						mortar_user_move = false;
						array_mortars_user_move = false;
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

				//������ ��������
				//������ ������ create arrays of graphics primitives -> array of linesegments
				if (stage_create_array_linesegments)
				{
					array_linesegments_show = true;
					for (int i{}; i < mass_or_single; i++)
					{
						Linesegment* ptr_new_elem_array_linesegments{ nullptr };
						float length_linesegment{ getRandomNumber(100, 300) };
						float degree_linesegment{ getRandomNumber(0, 360) };
						degree_linesegment = static_cast<int>(degree_linesegment);
						float x_linesegment{ getRandomNumber(705, 1500) };
						float y_linesegment{ getRandomNumber(95, 900) };
						ptr_new_elem_array_linesegments = new Linesegment({ x_linesegment, y_linesegment }, length_linesegment, degree_linesegment);
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
						ring_user_move = false;
						array_rings_user_move = false;
						mortar_user_move = false;
						array_mortars_user_move = false;
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

				//������ �����
				//������ ������ create arrays of complex objects -> array of rings
				if (stage_create_array_rings)
				{
					array_rings_show = true;
					for (int i{}; i < mass_or_single; i++)
					{
						Ring* ptr_new_elem_array_rings{ nullptr };
						float x_ring{ getRandomNumber(760, 1445) };
						float y_ring{ getRandomNumber(150, 845) };
						float radius_ring_outer{ getRandomNumber(60, 150) };
						float radius_ring_inner{ getRandomNumber(30, radius_ring_outer - 10) };
						Circle circle_outer({ x_ring, y_ring }, radius_ring_outer);
						Circle circle_inner({ x_ring, y_ring }, radius_ring_inner);
						ptr_new_elem_array_rings = new Ring(circle_outer, circle_inner);
						ptr_new_elem_array_rings->getCircleOuter().setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_rings->getCircleOuter().setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_rings->getCircleOuter().setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_rings->getCircleInner().setFillColor(67, 136, 169);
						ptr_new_elem_array_rings->getCircleInner().setVisibility(255);
						ptr_new_elem_array_rings->getCircleInner().setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						push_back_shapes<Ring>(array_rings, array_rings_size, ptr_new_elem_array_rings);
					}
				}
				if (array_rings_show)
				{
					if (stage_RandomMove_array_rings)
						doOffsetArrayRings(array_rings, array_rings_size);
					if (stage_user_move_array_rings)
					{
						array_rings_user_move = !array_rings_user_move;
						circle_user_move = false;
						array_circles_user_move = false;
						rect_user_move = false;
						array_rectangles_user_move = false;
						linesegment_user_move = false;
						array_linesegments_user_move = false;
						mortar_user_move = false;
						array_mortars_user_move = false;
					}
					if (stage_delete_last_elem_array_rings && (array_rings_size > 0))
					{
						pop_back_complex_shapes<Ring>(array_rings, array_rings_size);
						if (array_rings_size == 0)
						{
							array_rings_show = false;
							array_rings_user_move = false;
						}
					}
					if (stage_delete_all_rings)
					{
						int array_rings_size_temp{ array_rings_size };
						for (int i{}; i < array_rings_size_temp; i++)
							pop_back_complex_shapes<Ring>(array_rings, array_rings_size);
						array_rings_show = false;
						array_rings_user_move = false;
					}
				}

				//������ ������
				//������ ������ create arrays of complex objects -> array of mortars
				if (stage_create_array_mortars)
				{
					array_mortars_show = true;
					for (int i{}; i < mass_or_single; i++)
					{
						Mortar* ptr_new_elem_array_mortars{ nullptr };
						float length_body{ getRandomNumber(50, 100) };
						float width_body{ getRandomNumber(100, 150) };
						float degree_fire{ getRandomNumber(225, 315) };
						float length_fire{ getRandomNumber(50, length_body/2) };
						float radius_wheel{ length_body / 2 };
						float x_mortar{ getRandomNumber(710, 1495 - length_body) };
						float y_mortar{ getRandomNumber(100, 900 - radius_wheel - width_body) };
						Rectangle body_part{ {x_mortar, y_mortar}, length_body, width_body };
						Circle wheel_part{ {x_mortar + radius_wheel, y_mortar + width_body}, radius_wheel };
						Linesegment fire_part{ {x_mortar + length_body / 2, y_mortar - 5}, length_fire, degree_fire };
						ptr_new_elem_array_mortars = new Mortar(body_part, wheel_part, fire_part);
						//������� ���� �������
						ptr_new_elem_array_mortars->getRectangleObj().setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_mortars->getRectangleObj().setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_mortars->getRectangleObj().setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						//������� ������ �������
						ptr_new_elem_array_mortars->getCircleObj().setFillColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_mortars->getCircleObj().setVisibility(static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_mortars->getCircleObj().setOutColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						//������� �������� �������
						ptr_new_elem_array_mortars->getLineObj().setColor(static_cast<int>(getRandomNumber(0, 255)), static_cast<int>(getRandomNumber(0, 255)),
							static_cast<int>(getRandomNumber(0, 255)));
						ptr_new_elem_array_mortars->getLineObj().setVisibility(static_cast<int>(getRandomNumber(150, 255)));
						push_back_shapes<Mortar>(array_mortars, array_mortars_size, ptr_new_elem_array_mortars);
					}
				}
				if (array_mortars_show)
				{
					if (stage_RandomMove_array_mortars)
						doOffsetArrayMortars(array_mortars, array_mortars_size);
					if (stage_user_move_array_mortars)
					{
						array_mortars_user_move = !array_mortars_user_move;
						circle_user_move = false;
						array_circles_user_move = false;
						rect_user_move = false;
						array_rectangles_user_move = false;
						linesegment_user_move = false;
						array_linesegments_user_move = false;
						ring_user_move = false;
						array_rings_user_move = false;
					}
					if (stage_delete_last_elem_array_mortars && (array_mortars_size > 0))
					{
						pop_back_complex_shapes<Mortar>(array_mortars, array_mortars_size);
						if (array_mortars_size == 0)
						{
							array_mortars_show = false;
							array_mortars_user_move = false;
						}
					}
					if (stage_delete_all_mortars)
					{
						int array_mortars_size_temp{ array_mortars_size };
						for (int i{}; i < array_mortars_size_temp; i++)
							pop_back_complex_shapes<Mortar>(array_mortars, array_mortars_size);
						array_mortars_show = false;
						array_mortars_user_move = false;
					}
				}

				if (!submenu_create_arrays_0 && !submenu_create_arrays_1)
				{
					create_15_objs = false;
					mass_or_single = ONE_OBJ;
				}
				//������ ������ EXIT
				if (stage_exit)
					window.close();
			}
			else if (event_menu_click.type == sf::Event::KeyPressed)
			{
				/*���������������� �������� ���������� ���������*/
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

				if (ring_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W && (f_ptr_obj_ring->getCircleOuter().get_y_coordinate_base_point() -
						f_ptr_obj_ring->getCircleOuter().getRadius() >= 105))
					{
						f_ptr_obj_ring->MoveTo(0, -10);
					}
					if (event_menu_click.key.code == sf::Keyboard::A && (f_ptr_obj_ring->getCircleOuter().get_x_coordinate_base_point() -
						f_ptr_obj_ring->getCircleOuter().getRadius() >= 715))
					{
						f_ptr_obj_ring->MoveTo(-10, 0);
					}
					if (event_menu_click.key.code == sf::Keyboard::S && (f_ptr_obj_ring->getCircleOuter().get_y_coordinate_base_point() +
						f_ptr_obj_ring->getCircleOuter().getRadius() <= 890))
					{
						f_ptr_obj_ring->MoveTo(0, 10);
					}
					if (event_menu_click.key.code == sf::Keyboard::D && (f_ptr_obj_ring->getCircleOuter().get_x_coordinate_base_point() +
						f_ptr_obj_ring->getCircleOuter().getRadius() <= 1490))
					{
						f_ptr_obj_ring->MoveTo(10, 0);
					}
				}
				if (mortar_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W && (f_ptr_obj_mortar->getLineObj().get_y_coordinate_base_point() +
						sin(f_ptr_obj_mortar->getLineObj().getDegree() * PI/ 180 ) * f_ptr_obj_mortar->getLineObj().getLength() >= 110))
					{
						f_ptr_obj_mortar->MoveTo(0, -10);
					}
					if (event_menu_click.key.code == sf::Keyboard::A && (f_ptr_obj_mortar->getCircleObj().get_x_coordinate_base_point() -
						f_ptr_obj_mortar->getCircleObj().getRadius() >= 720))
					{
						f_ptr_obj_mortar->MoveTo(-10, 0);
					}
					if (event_menu_click.key.code == sf::Keyboard::S && (f_ptr_obj_mortar->getCircleObj().get_y_coordinate_base_point() +
						f_ptr_obj_mortar->getCircleObj().getRadius() <= 885))
					{
						f_ptr_obj_mortar->MoveTo(0, 10);
					}
					if (event_menu_click.key.code == sf::Keyboard::D && (f_ptr_obj_mortar->getCircleObj().get_x_coordinate_base_point() +
						f_ptr_obj_mortar->getCircleObj().getRadius() <= 1485))
					{
						f_ptr_obj_mortar->MoveTo(10, 0);
					}
				}

				if (extra_menu == 0)
				{
					/*��������� ������� ������� �����*/
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

					/*��������� �������� ������� ��������������*/
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

					/*��������� �������� � ������� ������� �������*/
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
				}

				if (extra_menu == 1)
				{
					/*��������� �������� ������� ������*/
					if (ring_change_dimensions)
					{
						if (event_menu_click.key.code == sf::Keyboard::Q
							&& (f_ptr_obj_ring->getCircleOuter().get_y_coordinate_base_point() + f_ptr_obj_ring->getCircleOuter().getRadius() + 2 <= 895)
							&& (f_ptr_obj_ring->getCircleOuter().get_x_coordinate_base_point() + f_ptr_obj_ring->getCircleOuter().getRadius() + 2 <= 1495)
							&& (f_ptr_obj_ring->getCircleOuter().get_y_coordinate_base_point() - f_ptr_obj_ring->getCircleOuter().getRadius() - 2 >= 100)
							&& (f_ptr_obj_ring->getCircleOuter().get_x_coordinate_base_point() - f_ptr_obj_ring->getCircleOuter().getRadius() - 2 >= 710))
						{
							f_ptr_obj_ring->getCircleOuter().changeRadius(2);
							f_ptr_obj_ring->getCircleInner().changeRadius(2);
						}
						if (event_menu_click.key.code == sf::Keyboard::E && (f_ptr_obj_ring->getCircleInner().getRadius() >= 10))
						{
							f_ptr_obj_ring->getCircleOuter().changeRadius(-2);
							f_ptr_obj_ring->getCircleInner().changeRadius(-2);
						}
					}
					/*��������� �������� ������� �������*/
					if (mortar_change_dimensions)
					{
						if (event_menu_click.key.code == sf::Keyboard::Z
							&& (f_ptr_obj_mortar->getCircleObj().get_x_coordinate_base_point() - f_ptr_obj_mortar->getCircleObj().getRadius() - 1 >= 710)
							&& (f_ptr_obj_mortar->getCircleObj().get_x_coordinate_base_point() + f_ptr_obj_mortar->getCircleObj().getRadius() + 1 <= 1495)
							&& (f_ptr_obj_mortar->getCircleObj().get_y_coordinate_base_point() + f_ptr_obj_mortar->getCircleObj().getRadius() + 1 <= 895)
							&& (f_ptr_obj_mortar->getLineObj().get_y_coordinate_base_point() - 1 + 
								(f_ptr_obj_mortar->getLineObj().getLength() + 1) * sin(f_ptr_obj_mortar->getLineObj().getDegree() * PI/ 180) >= 100))
						{
							f_ptr_obj_mortar->getRectangleObj().changeDimensions(2, 2);
							f_ptr_obj_mortar->getRectangleObj().MoveTo(-1, -1);
							f_ptr_obj_mortar->getCircleObj().changeRadius(1);
							f_ptr_obj_mortar->getCircleObj().MoveTo(0, 1);
							f_ptr_obj_mortar->getLineObj().changeLength(1.5);
							f_ptr_obj_mortar->getLineObj().MoveTo(0, -1);
						}
						if (event_menu_click.key.code == sf::Keyboard::X && (f_ptr_obj_mortar->getCircleObj().getRadius() >= 25)
							&& (f_ptr_obj_mortar->getLineObj().getLength() >= 50))
						{
							f_ptr_obj_mortar->getRectangleObj().changeDimensions(-2, -2);
							f_ptr_obj_mortar->getRectangleObj().MoveTo(1, 1);
							f_ptr_obj_mortar->getCircleObj().changeRadius(-1);
							f_ptr_obj_mortar->getCircleObj().MoveTo(0, -1);
							f_ptr_obj_mortar->getLineObj().changeLength(-1.5);
							f_ptr_obj_mortar->getLineObj().MoveTo(0, 1);
						}
					}
				}

				/*������ ��������*/
				//������ ������
				//���������������� �������� ���������
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

				//������ ���������������
				//���������������� �������� ���������
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

				//������ ��������
				//���������������� �������� ���������
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

				//������ �����
				//���������������� �������� ���������
				if (array_rings_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W)
						doUserMoveArrayRingsW(array_rings, array_rings_size);
					if (event_menu_click.key.code == sf::Keyboard::A)
						doUserMoveArrayRingsA(array_rings, array_rings_size);
					if (event_menu_click.key.code == sf::Keyboard::S)
						doUserMoveArrayRingsS(array_rings, array_rings_size);
					if (event_menu_click.key.code == sf::Keyboard::D)
						doUserMoveArrayRingsD(array_rings, array_rings_size);
				}

				//������ ������
				//���������������� �������� ���������
				if (array_mortars_user_move)
				{
					if (event_menu_click.key.code == sf::Keyboard::W)
						doUserMoveArrayMortarsW(array_mortars, array_mortars_size);
					if (event_menu_click.key.code == sf::Keyboard::A)
						doUserMoveArrayMortarsA(array_mortars, array_mortars_size);
					if (event_menu_click.key.code == sf::Keyboard::S)
						doUserMoveArrayMortarsS(array_mortars, array_mortars_size);
					if (event_menu_click.key.code == sf::Keyboard::D)
						doUserMoveArrayMortarsD(array_mortars, array_mortars_size);
				}

				if (extra_menu == 0)
				{
					//��������� ������� ��������� ������� ������
					if (array_circles_show)
					{
						if (event_menu_click.key.code == sf::Keyboard::Q)
							array_circles_RadiusIncrease(array_circles, array_circles_size);
						if (event_menu_click.key.code == sf::Keyboard::E)
							array_circles_RadiusDecrease(array_circles, array_circles_size);
					}

					//��������� �������� ��������� ������� ���������������
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

					//��������� �������� ��������� � ������� ��������� ������� ��������
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
					//��������� �������� ��������� ������� �����
					if (array_rings_show)
					{
						if (event_menu_click.key.code == sf::Keyboard::Q)
							array_rings_DimensionsIncrease(array_rings, array_rings_size);
						if (event_menu_click.key.code == sf::Keyboard::E)
							array_rings_DimensionsDecrease(array_rings, array_rings_size);
					}

					//��������� �������� ��������� ������� ������
					if (array_mortars_show)
					{
						if (event_menu_click.key.code == sf::Keyboard::Z)
							array_mortars_DimensionsIncrease(array_mortars, array_mortars_size);
						if (event_menu_click.key.code == sf::Keyboard::X)
							array_mortars_DimensionsDecrease(array_mortars, array_mortars_size);
					}
				}
			}
		}

		window.clear(sf::Color(67, 136, 169));

		/*��������� ����*/
		BG_general.Show(window);
		BG_menu.Show(window);
		image_text.Show(window);
		menu_text.Show(window);
		BG_create.Show(window);
		create_text.Show(window);
		BG_move_and_change.Show(window);
		move_and_change_text.Show(window);
		if (extra_menu == 0)
		{
			BG_next.Show(window);
			next_text.Show(window);
		}
		if (extra_menu == 1)
		{
			BG_back.Show(window);
			back_text.Show(window);
		}

		//������� CREATE_0
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

			//������ ������ CREATE -> create arrays of graphics primitives
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

				/*������� ��������*/
				//����� �� ���� ������ �������� �� 15 ����. ����������
				BG_create_15_objs.Show(window);
				create_15_objs_text.Show(window);
				//������ �����������
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
				//������ ���������������
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
				//������ ��������
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
		//������� CREATE_1
		else if (menu_create_1 && extra_menu == 1)
		{
			BG_ring.Show(window);
			ring_text.Show(window);
			BG_mortar.Show(window);
			mortar_text.Show(window);
			BG_create_arrays_of_complex_objects.Show(window);
			create_arrays_of_complex_objects_text.Show(window);

			//������ ������ CREATE -> create arrays of complex objects
			if (submenu_create_arrays_1)
			{
				BG_submenu_obj.m_setFillColor(4, 32, 159);
				BG_submenu_obj.Show(window);
				submenu_obj_text.Show(window);

				BG_create_array_rings.Show(window);
				create_array_rings_text.Show(window);
				BG_create_array_mortars.Show(window);
				create_array_mortars_text.Show(window);

				/*������� ��������*/
				//����� �� ���� ������ �������� �� 15 ����. ����������
				BG_create_15_objs.Show(window);
				create_15_objs_text.Show(window);
				//������ �����
				if (array_rings_show)
				{
					BG_RandomMove_array_rings.Show(window);
					RandomMove_array_rings_text.Show(window);

					BG_UserMove_array_rings.Show(window);
					UserMove_array_rings_text.Show(window);

					BG_delete_last_elem_array_rings.Show(window);
					delete_last_elem_array_rings_text.Show(window);

					BG_delete_all_rings.Show(window);
					delete_all_rings_text.Show(window);
				}
				//������ ������
				if (array_mortars_show)
				{
					BG_RandomMove_array_mortars.Show(window);
					RandomMove_array_mortars_text.Show(window);

					BG_UserMove_array_mortars.Show(window);
					UserMove_array_mortars_text.Show(window);

					BG_delete_last_elem_array_mortars.Show(window);
					delete_last_elem_array_mortars_text.Show(window);

					BG_delete_all_mortars.Show(window);
					delete_all_mortars_text.Show(window);
				}
			}
		}

		//������� MOVE AND CHANGE
		if (menu_move_and_change_0 && extra_menu == 0)
		{
			//������ ������ �����
			if (circle_show)
			{
				BG_obj_circle.Show(window);
				obj_circle_text.Show(window);

				//������ ������ MOVE AND CHANGE -> obj_circle
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
			//������ ������ ��������������
			if (rect_show)
			{
				BG_obj_rect.Show(window);
				obj_rect_text.Show(window);

				//������ ������ MOVE AND CHANGE -> obj_rectangle
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
			//������ ������ �������
			if (linesegment_show)
			{
				BG_obj_linesegment.Show(window);
				obj_linesegment_text.Show(window);

				//������ ������ MOVE AND CHANGE -> obj_linesegment
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

		if (menu_move_and_change_1 && extra_menu == 1)
		{
			//������ ������ ������
			if (ring_show)
			{
				BG_obj_ring.Show(window);
				obj_ring_text.Show(window);

				//������ ������ MOVE AND CHANGE -> obj_ring
				if (submenu_obj_ring)
				{
					BG_submenu_obj.Show(window);
					submenu_obj_text.Show(window);

					BG_RandomMove_obj_ring.Show(window);
					RandomMove_obj_ring_text.Show(window);

					BG_UserMove_obj_ring.Show(window);
					UserMove_obj_ring_text.Show(window);

					BG_ChangeDimensions_obj_ring.Show(window);
					ChangeDimensions_obj_ring_text.Show(window);

					BG_delete_obj_ring.Show(window);
					delete_obj_ring_text.Show(window);
				}
			}
			//������ ������ �������
			if (mortar_show)
			{
				BG_obj_mortar.Show(window);
				obj_mortar_text.Show(window);

				//������ ������ MOVE AND CHANGE -> obj_mortar
				if (submenu_obj_mortar)
				{
					BG_submenu_obj.Show(window);
					submenu_obj_text.Show(window);

					BG_RandomMove_obj_mortar.Show(window);
					RandomMove_obj_mortar_text.Show(window);

					BG_UserMove_obj_mortar.Show(window);
					UserMove_obj_mortar_text.Show(window);

					BG_ChangeDimensions_obj_mortar.Show(window);
					ChangeDimensions_obj_mortar_text.Show(window);

					BG_delete_obj_mortar.Show(window);
					delete_obj_mortar_text.Show(window);
				}
			}
		}

		/*��������� �������*/
		//����� �������� ����������, �������������� � �������
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
		if (ring_show)
		{
			f_ptr_obj_ring->Show(window);
		}
		if (mortar_show)
		{
			f_ptr_obj_mortar->Show(window);
		}

		/*������� ��������*/
		//������ �����������
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
		//������ ���������������
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
		//������ ��������
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
		//������ �����
		if (array_rings_show)
		{
			if (extra_menu == 1)
			{
				ChangeDimensions_array_rings_text.m_setFillColor(209, 255, 26);
				ChangeDimensions_array_rings_text.Show(window);
			}
			for (int i{}; i < array_rings_size; i++)
			{
				array_rings[i]->Show(window);
			}
		}
		//������ ������
		if (array_mortars_show)
		{
			if (extra_menu == 1)
			{
				ChangeDimensions_array_mortars_text.m_setFillColor(209, 255, 26);
				ChangeDimensions_array_mortars_text.Show(window);
			}
			for (int i{}; i < array_mortars_size; i++)
			{
				array_mortars[i]->Show(window);
			}
		}

		BG_exit.Show(window);
		exit_text.Show(window);
		window.display();
	}
	return 0;
}