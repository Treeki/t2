#pragma once

#include "T2IOAbleValueArray.h"

class T2CrossEquipArray : public T2IOAbleValueArray {
public:
	T2CrossEquipArray();
	~T2CrossEquipArray();

	void AllClear();
	void ReplaceID(UInt16 a, UInt16 b);
	void Union(T2CrossEquipArray *other);
	static T2CrossEquipArray *ReadCEArray(LStream &stream);
	static void WriteCEArray(T2CrossEquipArray *array, LStream &stream);

	virtual FourCharCode GetCEClassID() { return '_CEA'; }
};
