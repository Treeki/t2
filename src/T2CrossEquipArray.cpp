#include "T2CrossEquipArray.h"
#include "T2FloorCEArray.h"
#include "T2MoverCEArray.h"
#include "T2RouteCEArray.h"
#include "T2TenantCEArray.h"

#include <LArrayIterator.h>
#include <LStream.h>

T2CrossEquipArray::T2CrossEquipArray()
	: T2IOAbleValueArray(sizeof(UInt16))
{
}

T2CrossEquipArray::~T2CrossEquipArray() {
}

void T2CrossEquipArray::AllClear() {
	RemoveItemsAt(mItemCount, index_First);
}

void T2CrossEquipArray::ReplaceID(UInt16 a, UInt16 b) {
	ArrayIndexT index = FetchIndexOf(&a);
	if (index != index_Bad) {
		AssignItemsAt(1, index, &b);
	}
}

void T2CrossEquipArray::Union(T2CrossEquipArray *other) {
	LArrayIterator iter(*other);
	UInt16 id;
	while (iter.Next(&id)) {
		InsertItemsAt(1, index_Last, &id);
	}
}

T2CrossEquipArray *T2CrossEquipArray::ReadCEArray(LStream &stream) {
	T2CrossEquipArray *array = 0;
	FourCharCode type;
	stream >> type;

	switch (type) {
		case '_CEA':
			array = new T2CrossEquipArray;
			break;
		case 'TCEA':
			array = new T2TenantCEArray;
			break;
		case 'RCEA':
			array = new T2RouteCEArray;
			break;
		case 'FCEA':
			array = new T2FloorCEArray;
			break;
		case 'MCEA':
			array = new T2MoverCEArray;
			break;
	}

	if (array)
		array->Read(stream);
	return array;
}

void T2CrossEquipArray::WriteCEArray(T2CrossEquipArray *array, LStream &stream) {
	if (array == 0) {
		FourCharCode type = 'xCEA';
		stream << type;
	} else {
		FourCharCode type = array->GetCEClassID();
		stream << type;
		array->Write(stream);
	}
}
