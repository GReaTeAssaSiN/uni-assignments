#ifndef RING_H_
#define RING_H_

#include "class_ring.h"

void doOffsetRing(Ring* f_ptr_obj_ring);

void doOffsetArrayRings(Ring** array_rings, int array_rings_size);
void doUserMoveArrayRingsW(Ring** array_rings, int array_rings_size);
void doUserMoveArrayRingsA(Ring** array_rings, int array_rings_size);
void doUserMoveArrayRingsS(Ring** array_rings, int array_rings_size);
void doUserMoveArrayRingsD(Ring** array_rings, int array_rings_size);
void array_rings_DimensionsIncrease(Ring** array_rings, int array_rings_size);
void array_rings_DimensionsDecrease(Ring** array_rings, int array_rings_size);

#endif /* RING_H_ */