#pragma once

#include <PP_Types.h>

class LStream;

class T2WordDef {
public:
	T2WordDef();
	void Read(LStream &stream);
	virtual ~T2WordDef();
	void GetWords(Uchar a, Uchar b, Uchar c, Uchar d, Str63 &str) const;

	unsigned char m4, m5, m6, m7, m8[64];
};
