#pragma once

#include "T2CrossEquipArray.h"

class T2TenantCEArray : public T2CrossEquipArray {
public:
	T2TenantCEArray();
	~T2TenantCEArray();

	UInt16 GetFloorID(Int32 index);
	void SetFloorID(UInt16 id);
	FourCharCode GetCEClassID();
};
