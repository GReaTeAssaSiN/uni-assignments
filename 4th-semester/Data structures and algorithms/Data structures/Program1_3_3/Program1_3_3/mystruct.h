#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_

#include "constants.h"

struct List
{
	int Elems[size + 1]{};
	int Refs[size + 1]{};
	int count{};
};

#endif /* MYSTRUCT_H_*/