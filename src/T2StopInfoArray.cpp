#include "T2StopInfoArray.h"

#include <LStream.h>

T2StopInfoArray::T2StopInfoArray()
	: LArray(1)
{
}

T2StopInfoArray::~T2StopInfoArray() {
}

void T2StopInfoArray::Init(Int16 v) {
	Expand(EEquipPos_2, v);
}

void T2StopInfoArray::AllClear() {
	RemoveItemsAt(mItemCount, index_First);
}

void T2StopInfoArray::Expand(EEquipPos equipPos, Int16 v) {
	Int32 pos;
	if (equipPos == EEquipPos_2) {
		pos = index_Last;
	} else if (equipPos == EEquipPos_3) {
		pos = index_First;
	} else {
		return;
		return;
	}

	if (v > 0) {
		int max = v * 2;
		Int8 empty = 0;
		for (int i = 0; i < max; i++) {
			InsertItemsAt(1, pos, &empty);
		}
	} else {
		int max = -v * 2;
		for (int i = 0; i < max; i++) {
			RemoveItemsAt(1, pos);
		}
	}
}

Boolean T2StopInfoArray::IsStopPos(Int16 a, Int16 b) const {
	return GetStopAt(a, b) > 0;
}

Boolean T2StopInfoArray::IsOnStopPos(Int16 a, Int16 b) const {
	return (GetStopAt(a, b) & 2) > 0;
}

Boolean T2StopInfoArray::IsOffStopPos(Int16 a, Int16 b) const {
	return (GetStopAt(a, b) & 1) > 0;
}

void T2StopInfoArray::SetOnStop(Int16 a, Int16 b) {
	Int8 value = GetStopAt(a, b) | 2;
	SetStopAt(a, b, value);
}

void T2StopInfoArray::SetOffStop(Int16 a, Int16 b) {
	Int8 value = GetStopAt(a, b) | 1;
	SetStopAt(a, b, value);
}

void T2StopInfoArray::ClearOnStop(Int16 a, Int16 b) {
	Int8 value = GetStopAt(a, b) & 1;
	SetStopAt(a, b, value);
}

void T2StopInfoArray::ClearOffStop(Int16 a, Int16 b) {
	Int8 value = GetStopAt(a, b) & 2;
	SetStopAt(a, b, value);
}

Int8 T2StopInfoArray::GetStopAt(Int16 a, Int16 b) const {
	Int8 v = 0;
	FetchItemAt(GetIndex(a, b), &v);
	return v;
}

void T2StopInfoArray::SetStopAt(Int16 a, Int16 b, Int8 value) {
	AssignItemsAt(1, GetIndex(a, b), &value);
}

Int32 T2StopInfoArray::GetIndex(Int16 a, Int16 b) const {
	Int32 index = 1;
	index += a * 2;
	if (b == 1)
		index++;
	return index;
}

T2StopInfoArray *T2StopInfoArray::ReadStopInfoArray(LStream &stream) {
	T2StopInfoArray *array = 0;

	OSType type;
	stream >> type;
	if (type == 'SIfA')
		array = new T2StopInfoArray;
	if (array)
		array->Read(stream);

	return array;
}

void T2StopInfoArray::WriteStopInfoArray(T2StopInfoArray *array, LStream &stream) {
	OSType type;
	if (array == 0) {
		type = 'xSIA';
		stream << type;
	} else {
		type = 'SIfA';
		stream << type;
		array->Write(stream);
	}
}

void T2StopInfoArray::Read(LStream &stream) {
	stream >> mItemSize;
	stream >> mItemCount;
	stream >> mDataStored;
	stream >> mDataAllocated;
	stream >> mItemsH;
}

void T2StopInfoArray::Write(LStream &stream) {
	stream << mItemSize;
	stream << mItemCount;
	stream << mDataStored;
	stream << mDataAllocated;
	stream << mItemsH;
}
