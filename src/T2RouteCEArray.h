#pragma once

#include "T2CrossEquipArray.h"

class T2RouteCEArray : public T2CrossEquipArray {
public:
	T2RouteCEArray();
	~T2RouteCEArray();

	void Insert(UInt16 after, UInt16 value);
	UInt16 GetSameID(T2RouteCEArray *other);
	Boolean HasCrossEquip() const;
	FourCharCode GetCEClassID();
};
