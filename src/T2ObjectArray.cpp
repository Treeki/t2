#include "T2ObjectArray.h"

T2ObjectArray::T2ObjectArray(UInt16 startID) {
	mStartID = startID;
}

T2ObjectArray::~T2ObjectArray() {
}

T2Object *T2ObjectArray::GetIndexObject(Int32) {
	return 0;
}

T2Object *T2ObjectArray::FindUnusedObject() {
	return 0;
}

void T2ObjectArray::DispatchIdle(T2TowerDoc *doc, Int32 i) {
}
