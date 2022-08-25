#include "T2OutObjArray.h"
#include "T2OutObjArrayList.h"

#include <LArrayIterator.h>
#include <LStream.h>

T2OutObjArrayList::T2OutObjArrayList()
	: LArray(sizeof(T2OutObjArrayList *))
{
	T2OutObjArray *array = new T2OutObjArray(1000);
	Add(array);
}

T2OutObjArrayList::~T2OutObjArrayList() {
	LArrayIterator iter(*this);
	T2OutObjArray *array;
	while (iter.Next(&array)) {
		delete array;
	}
}

void T2OutObjArrayList::Add(T2OutObjArray *array) {
	InsertItemsAt(1, index_Last, &array);
}

T2OutObjArray *T2OutObjArrayList::GetItemAt(Int32 index) {
	T2OutObjArray *array;
	if (FetchItemAt(index, &array))
		return array;
	else
		return 0;
}

T2OutObj *T2OutObjArrayList::FindUnusedOutObj() {
	LArrayIterator iter(*this);
	UInt16 index = 1;
	T2OutObjArray *array;

	while (iter.Next(&array)) {
		T2OutObj *obj = array->FindUnusedOutObj();
		if (obj)
			return obj;

		index = array->mStartID;
	}

	array = new T2OutObjArray(index + 64);
	if (array) {
		Add(array);
		return array->FindUnusedOutObj();
	}

	return 0;
}

void T2OutObjArrayList::DispatchIdle(T2TowerDoc *doc) {
	LArrayIterator iter(*this);
	T2OutObjArray *array;
	while (iter.Next(&array)) {
		array->DispatchIdle(doc, 0);
	}
}

T2OutObj *T2OutObjArrayList::GetIndOutObj(UInt16 index) {
	UInt32 whichElement, group;
	group = index / 64;
	whichElement = index % 64;

	T2OutObjArray *array = GetItemAt(group + 1);
	if (array)
		return &array->mArray[whichElement];
	else
		return 0;
}

T2OutObj *T2OutObjArrayList::GetOutObjByID(UInt16 index) {
	if (index == 0)
		return 0;

	return GetIndOutObj(index - 1000);
}

Int32 T2OutObjArrayList::CalcMentenanceCost(T2TowerDoc *doc) const {
	Int32 total = 0;
	LArrayIterator iter(*this);
	T2OutObjArray *array;
	while (iter.Next(&array)) {
		total += array->CalcMentenanceCost(doc);
	}
	return total;
}

void T2OutObjArrayList::Read(LStream &stream, T2TowerDoc *doc) {
	UInt32 count;
	stream >> count;

	RemoveItemsAt(mItemCount, index_First);
	UInt16 startID = 1000;

	for (UInt32 i = 0; i < count; i++) {
		T2OutObjArray *array;
		array = new T2OutObjArray(startID);
		array->Read(stream, doc);
		Add(array);
		startID += 0x40;
	}
}

void T2OutObjArrayList::Write(LStream &stream) {
	UInt32 count = mItemCount;
	stream << count;

	LArrayIterator iter(*this);
	T2OutObjArray *array;
	while (iter.Next(&array)) {
		array->Write(stream);
	}
}
