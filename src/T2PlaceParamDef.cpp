#include "T2PlaceParamDef.h"

#include <LStream.h>

T2PlaceParamDef::T2PlaceParamDef(LStream &stream) {
	float divisor = 100.0f;

	for (UInt32 i = 0; i < 3; i++) {
		stream >> mEntries[i].percent;
		stream >> mEntries[i].score;
		mEntries[i].rate = mEntries[i].percent / divisor;
	}
}

T2PlaceParamDef::~T2PlaceParamDef() {
}
