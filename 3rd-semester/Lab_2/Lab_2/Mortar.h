#ifndef MORTAR_H_
#define MORTAR_H_

#include "class_mortar.h"

void doOffsetMortar(Mortar* f_ptr_obj_ring);

void doOffsetArrayMortars(Mortar** array_mortars, int array_mortars_size);
void doUserMoveArrayMortarsW(Mortar** array_mortars, int array_mortars_size);
void doUserMoveArrayMortarsA(Mortar** array_mortars, int array_mortars_size);
void doUserMoveArrayMortarsS(Mortar** array_mortars, int array_mortars_size);
void doUserMoveArrayMortarsD(Mortar** array_mortars, int array_mortars_size);
void array_mortars_DimensionsIncrease(Mortar** array_mortars, int array_mortars_size);
void array_mortars_DimensionsDecrease(Mortar** array_mortars, int array_mortars_size);

#endif MORTAR_H_