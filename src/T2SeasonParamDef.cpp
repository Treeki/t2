#include "T2SeasonParamDef.h"

#include <LStream.h>

T2SeasonParamDef::T2SeasonParamDef(LStream &stream) {
	float divisor = 100.0f;
	for (UInt32 i = 0; i < 12; i++) {
		stream >> mEntries[i].a;
		mEntries[i].b = mEntries[i].a / divisor;
	}
}

T2SeasonParamDef::~T2SeasonParamDef() {
}
