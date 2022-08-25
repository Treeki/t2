#include "T2WordDefArray.h"
#include "UT2Utils.h"

#include <LHandleStream.h>
#include <LStream.h>
#include <UException.h>

T2WordDefArray *T2WordDefArray::MakeWordDefArray() {
	T2WordDefArray *result = 0;

	Handle res = ::Get1IndResource('WoDf', 1);
	if (res) {
		::DetachResource(res);
		LHandleStream stream(res);
		result = new T2WordDefArray(stream);
		#line 29
		ThrowIfNil_(result);
	}

	return result;
}

T2WordDefArray::T2WordDefArray(LStream &stream) {
	Init();
	stream >> mWordCount;

	mWords = new T2WordDef[mWordCount];
	#line 49
	ThrowIfNil_(mWords);

	try {
		for (UInt32 i = 0; i < mWordCount; i++) {
			mWords[i].Read(stream);
		}
	} catch (ExceptionCode code) {
		delete this;
		#line 61
		Throw_(code);
	}
}

void T2WordDefArray::Init() {
	mWords = 0;
}

T2WordDefArray::~T2WordDefArray() {
	delete[] mWords;
}

void T2WordDefArray::GetWords(Uchar a, Uchar b, Uchar c, Uchar d, Str63 &str) const {
	Ptr flagArray = mWordCount ? ::NewPtrClear(mWordCount) : 0;
	str[0] = 0;

	if (flagArray) {
		Int16 i = 0;
		while (str[0] == 0 && i < mWordCount) {
			UInt32 index = UT2Utils::Randomize(mWordCount);
			if (!flagArray[index]) {
				flagArray[index] = true;
				mWords[index].GetWords(a, b, c, d, str);
			} else {
				for (i = 0; i < mWordCount; i++) {
					if (!flagArray[i])
						break;
				}
			}
		}

		::DisposePtr(flagArray);
	}
}
