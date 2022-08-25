#pragma once

#include "T2RouteCEArray.h"

class T2MoverCEArray : public T2RouteCEArray {
public:
	T2MoverCEArray();
	~T2MoverCEArray();

	FourCharCode GetCEClassID();
};
