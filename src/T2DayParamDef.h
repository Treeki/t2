#pragma once

#include "T2DumpObj.h"
#include <PP_Types.h>

class LStream;

class T2DayParamDef : public T2DumpObj {
public:
	T2DayParamDef(LStream &stream);
	~T2DayParamDef();

	struct Entry {
		UInt32 percent;
		float rate;
	};

	Entry mEntries[2][2];

	UInt32 GetPercent(UInt32 day, UInt32 whether) const { return mEntries[day][whether].percent; }
	float GetRate(UInt32 day, UInt32 whether) const { return mEntries[day][whether].rate; }
};
