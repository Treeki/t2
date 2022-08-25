#include "T2MovieParamArray.h"
#include <LArrayIterator.h>

struct MovieParam {
	UInt32 id;
	Int32 param;
};

T2MovieParamArray::T2MovieParamArray()
	: LArray(sizeof(MovieParam))
{
}

T2MovieParamArray::~T2MovieParamArray() {
}

Boolean T2MovieParamArray::Regist(UInt32 id, Int32 param) {
	LArrayIterator iter(*this);
	MovieParam entry;

	while (iter.Next(&entry)) {
		if (entry.id == id)
			return false;
	}

	entry.id = id;
	entry.param = param;
	InsertItemsAt(1, index_Last, &entry);
	return true;
}

Int32 T2MovieParamArray::GetParam(UInt32 id) {
	LArrayIterator iter(*this);
	MovieParam entry;

	while (iter.Next(&entry)) {
		if (entry.id == id)
			return entry.param;
	}

	return 0;
}

T2MovieParamArray *T2MovieParamArray::ReadMovieParamArray(LStream &stream) {
	T2MovieParamArray *array = NULL;

	FourCharCode magic;
	stream >> magic;
	if (magic == 'mvPA')
		array = new T2MovieParamArray;

	if (array)
		array->Read(stream);

	return array;
}

void T2MovieParamArray::WriteMovieParamArray(T2MovieParamArray *array, LStream &stream) {
	FourCharCode magic;

	if (array == NULL) {
		magic = 'xmPA';
		stream << magic;
	} else {
		magic = 'mvPA';
		stream << magic;
		array->Write(stream);
	}
}

void T2MovieParamArray::Read(LStream &stream) {
	stream >> mItemSize;
	stream >> mItemCount;
	stream >> mDataStored;
	stream >> mDataAllocated;
	stream >> mItemsH;
}

void T2MovieParamArray::Write(LStream &stream) {
	stream << mItemSize;
	stream << mItemCount;
	stream << mDataStored;
	stream << mDataAllocated;
	stream << mItemsH;
}
