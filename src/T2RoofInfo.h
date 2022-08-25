#pragma once

#include <PP_Types.h>

class T2RoofInfo {
public:
	T2RoofInfo(Int16 left, Int16 top, Int16 right, Int16 bottom, Boolean flag);

	Rect mRect;
	Boolean mFlag;
};
