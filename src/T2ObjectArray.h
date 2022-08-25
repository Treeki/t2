#pragma once

#include "T2Object.h"

class T2TowerDoc;

class T2ObjectArray {
public:
	UInt16 mStartID;

	T2ObjectArray(UInt16 startID);
	virtual ~T2ObjectArray();
	virtual T2Object *GetIndexObject(Int32 i);
	virtual T2Object *FindUnusedObject();
	virtual void DispatchIdle(T2TowerDoc *doc, Int32 i);

	UInt16 GetStartID() { return mStartID; }
};
