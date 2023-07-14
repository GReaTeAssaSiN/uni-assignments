#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "class_rectangle.h"

void doOffsetRect(Rectangle* f_ptr_obj_rect);

void push_back_rectangles(Rectangle**& array_rectangles, int& array_rectangles_size, Rectangle* ptr_new_obj_rectangle);
void pop_back_rectangles(Rectangle**& array_rectangles, int& array_rectangles_size);
void doOffsetArrayRectangles(Rectangle** array_rectangles, int array_rectangles_size);
void doUserMoveArrayRectanglesW(Rectangle** array_rectangles, int array_rectangles_size);
void doUserMoveArrayRectanglesA(Rectangle** array_rectangles, int array_rectangles_size);
void doUserMoveArrayRectanglesS(Rectangle** array_rectangles, int array_rectangles_size);
void doUserMoveArrayRectanglesD(Rectangle** array_rectangles, int array_rectangles_size);
void array_rectangles_ChangeDimensions(Rectangle** array_rectangles, int array_rectangles_size, int dLength, int dWidth);

#endif RECTANGLE_H_