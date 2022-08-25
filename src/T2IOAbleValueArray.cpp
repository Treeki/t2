#include "T2IOAbleValueArray.h"

#include "T2BufferedFileStream.h"
#include <LStream.h>

T2IOAbleValueArray::T2IOAbleValueArray(Uint32 itemSize)
	: LArray(itemSize)
{
}

T2IOAbleValueArray::~T2IOAbleValueArray() {
}

void T2IOAbleValueArray::Read(LStream &stream) {
	stream >> mItemSize;
	stream >> mItemCount;
	stream >> mDataStored;
	stream >> mDataAllocated;
	stream >> mIsSorted;
	stream >> mKeepSorted;

	if (mItemSize == 2) {
		static_cast<T2BufferedFileStream *>(&stream)->Read2ByteDataArrayHandle(mItemsH);
	} else if (mItemSize == 4) {
		static_cast<T2BufferedFileStream *>(&stream)->Read4ByteDataArrayHandle(mItemsH);
	} else {
		stream >> mItemsH;
	}
}

void T2IOAbleValueArray::Write(LStream &stream) {
	stream << mItemSize;
	stream << mItemCount;
	stream << mDataStored;
	stream << mDataAllocated;
	stream << mIsSorted;
	stream << mKeepSorted;

	if (mItemSize == 2) {
		static_cast<T2BufferedFileStream *>(&stream)->Write2ByteDataArrayHandle((Int16 **) mItemsH);
	} else if (mItemSize == 4) {
		static_cast<T2BufferedFileStream *>(&stream)->Write4ByteDataArrayHandle((Int32 **) mItemsH);
	} else {
		Handle h = mItemsH;
		stream << h;
	}
}
