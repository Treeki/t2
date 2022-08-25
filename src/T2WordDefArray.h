#pragma once

#include "T2WordDef.h"

class LStream;

class T2WordDefArray {
public:
	static T2WordDefArray *MakeWordDefArray();

	T2WordDefArray(LStream &stream);
	void Init();
	virtual ~T2WordDefArray();
	void GetWords(Uchar a, Uchar b, Uchar c, Uchar d, Str63 &str) const;

protected:
	UInt32 mWordCount;
	T2WordDef *mWords;
};
