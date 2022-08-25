#pragma once

#include "T2ObjectArray.h"
#include "T2OutObj.h"

class T2OutObjArray : public T2ObjectArray {
public:
	T2OutObjArray(UInt32 startID);
	~T2OutObjArray();

	T2OutObj *FindUnusedOutObj() const;

	void DispatchIdle(T2TowerDoc *doc, Int32 i);
	Int32 CalcMentenanceCost(T2TowerDoc *doc) const;
	void Read(LStream &stream, T2TowerDoc *doc);
	void Write(LStream &stream);

	T2OutObj mArray[64];
};
