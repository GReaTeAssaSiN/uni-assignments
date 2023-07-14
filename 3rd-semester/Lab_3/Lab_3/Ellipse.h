#ifndef ELLIPSE_H_
#define ELLIPSE_H_

#include "class_TEllipse.h"

void doOffsetEllipse(TEllipse* f_ptr_obj_ellipse);

void doOffsetArrayEllipses(TEllipse** array_ellipses, int array_ellipses_size);
void doUserMoveArrayEllipsesW(TEllipse** array_ellipses, int array_ellipses_size);
void doUserMoveArrayEllipsesA(TEllipse** array_ellipses, int array_ellipses_size);
void doUserMoveArrayEllipsesS(TEllipse** array_ellipses, int array_ellipses_size);
void doUserMoveArrayEllipsesD(TEllipse** array_ellipses, int array_ellipses_size);
void array_ellipses_SemiMajorAxisIncrease(TEllipse** array_ellipses, int array_ellipses_size);
void array_ellipses_SemiMajorAxisDecrease(TEllipse** array_ellipses, int array_ellipses_size);
void array_ellipses_SemiMinorAxisIncrease(TEllipse** array_ellipses, int array_ellipses_size);
void array_ellipses_SemiMinorAxisDecrease(TEllipse** array_ellipses, int array_ellipses_size);
void array_ellipses_Rotate(TEllipse** array_ellipses, int array_ellipses_size);

#endif /* ELLIPSE_H_ */