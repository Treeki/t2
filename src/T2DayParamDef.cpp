#include "T2DayParamDef.h"

#include <LStream.h>

T2DayParamDef::T2DayParamDef(LStream &stream) {
	float divisor = 100.0f;

	for (UInt32 i = 0; i < 2; i++) {
		for (UInt32 j = 0; j < 2; j++) {
			stream >> mEntries[i][j].percent;
			mEntries[i][j].rate = mEntries[i][j].percent / divisor;
		}
	}
}

T2DayParamDef::~T2DayParamDef() {
}
