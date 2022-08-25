#include "T2RouteCEArray.h"

#include <LArrayIterator.h>

T2RouteCEArray::T2RouteCEArray() {
}

T2RouteCEArray::~T2RouteCEArray() {
}

void T2RouteCEArray::Insert(UInt16 after, UInt16 value) {
	if (after) {
		ArrayIndexT curIndex = FetchIndexOf(&after);
		if (curIndex != index_Bad) {
			InsertItemsAt(1, curIndex + 1, &value);
		} else {
			InsertItemsAt(1, index_First, &value);
		}
	} else {
		InsertItemsAt(1, index_First, &value);
	}
}

UInt16 T2RouteCEArray::GetSameID(T2RouteCEArray *other) {
	UInt16 result = 0;
	LArrayIterator iterA(*this);
	UInt16 idA;
	while (iterA.Next(&idA)) {
		LArrayIterator iterB(*other);
		UInt16 idB;
		while (iterB.Next(&idB)) {
			if (idA == idB) {
				result = idA;
				break;
			}
		}
	}

	return result;
}

Boolean T2RouteCEArray::HasCrossEquip() const {
	return mItemCount != 0;
}

FourCharCode T2RouteCEArray::GetCEClassID() {
	return 'RCEA';
}
