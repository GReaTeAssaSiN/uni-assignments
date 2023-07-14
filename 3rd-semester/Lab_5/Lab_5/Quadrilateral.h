#ifndef QUADRILATERAL_H_
#define QUADRILATERAL_H_

#include "class_TQuadrilateral.h"

void doOffsetQuadrilateral(TQuadrilateral* f_ptr_obj_quadrilateral);
void doOffsetArrayQuadrilaterals(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size);
void doUserMoveArrayQuadrilateralsW(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size);
void doUserMoveArrayQuadrilateralsA(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size);
void doUserMoveArrayQuadrilateralsS(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size);
void doUserMoveArrayQuadrilateralsD(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size);
void array_quadrilaterals_DimensionsIncrease(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size);
void array_quadrilaterals_DimensionsDecrease(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size);

#endif /* QUADRILATERAL_H_ */