#pragma once

#include "T2RouteCEArray.h"

class T2FloorCEArray : public T2RouteCEArray {
public:
	T2FloorCEArray();
	~T2FloorCEArray();

	FourCharCode GetCEClassID();
};
