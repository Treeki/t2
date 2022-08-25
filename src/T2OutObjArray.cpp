#include "T2OutObjArray.h"

T2OutObjArray::T2OutObjArray(UInt32 startID)
	: T2ObjectArray(startID)
{
	for (UInt32 i = 0; i < 64; i++)
		mArray[i].mToolType = mStartID + i;
}

T2OutObjArray::~T2OutObjArray() {
}

T2OutObj *T2OutObjArray::FindUnusedOutObj() const {
	for (Int32 i = 0; i < 64; i++) {
		if (!mArray[i].IsUsed())
			return (T2OutObj *) &mArray[i];
	}
	return 0;
}

void T2OutObjArray::DispatchIdle(T2TowerDoc *doc, Int32) {
	for (Int32 i = 0; i < 64; i++) {
		if (mArray[i].IsUsed())
			mArray[i].Idle(doc);
	}
}

Int32 T2OutObjArray::CalcMentenanceCost(T2TowerDoc *doc) const {
	Int32 total = 0;
	const T2OutObj *obj = &mArray[0];
	for (UInt32 i = 0; i < 64; i++, obj++) {
		if (obj->IsUsed())
			total += obj->CalcMentenanceCost(doc);
	}
	return total;
}

void T2OutObjArray::Read(LStream &stream, T2TowerDoc *doc) {
	for (Int32 i = 0; i < 64; i++) {
		mArray[i].Load(stream, doc);
	}
}

void T2OutObjArray::Write(LStream &stream) {
	for (Int32 i = 0; i < 64; i++) {
		mArray[i].Save(stream);
	}
}
