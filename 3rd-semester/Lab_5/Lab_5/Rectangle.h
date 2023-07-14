#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "class_TRectangle.h"

void doOffsetRect(TRectangle* f_ptr_obj_rect);

void doOffsetArrayRectangles(TRectangle** array_rectangles, int array_rectangles_size);
void doUserMoveArrayRectanglesW(TRectangle** array_rectangles, int array_rectangles_size);
void doUserMoveArrayRectanglesA(TRectangle** array_rectangles, int array_rectangles_size);
void doUserMoveArrayRectanglesS(TRectangle** array_rectangles, int array_rectangles_size);
void doUserMoveArrayRectanglesD(TRectangle** array_rectangles, int array_rectangles_size);
void array_rectangles_ChangeDimensions(TRectangle** array_rectangles, int array_rectangles_size, int dLength, int dWidth);
void doRotateArrayRects(TRectangle** array_rectangles, int array_rectangles_size);

#endif /* RECTANGLE_H_ */