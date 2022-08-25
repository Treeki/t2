#pragma once

#include <PP_Types.h>

class LStream;

class T2SeasonParamDef {
public:
	T2SeasonParamDef(LStream &stream);
	virtual ~T2SeasonParamDef();

	struct Entry {
		UInt32 a;
		Float32 b;
	};
	Entry mEntries[12];

	float GetSomething(UInt32 index) const {
		float result = 0.0f;
		if (index < 12)
			result = mEntries[index].b;
		return result;
	}
};
