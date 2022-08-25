#pragma once

#include "T2DumpObj.h"
#include <PP_Types.h>

class LStream;

class T2PlaceParamDef : public T2DumpObj {
public:
	enum EPlace {
		Place0,
		Place1,
		Place2
	};

	T2PlaceParamDef(LStream &stream);
	~T2PlaceParamDef();

	struct Entry {
		UInt16 percent;
		Int16 score;
		float rate;
	};

	Entry mEntries[3];

	UInt16 GetPercent(EPlace place) const { return mEntries[(int) place].percent; }
	Int16 GetScore(EPlace place) const { return mEntries[(int) place].score; }
	float GetRate(EPlace place) const { return mEntries[(int) place].rate; }
};
