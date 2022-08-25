#pragma once

#include <PP_Types.h>

class LStream;

class T2ColdTableDef {
public:
	T2ColdTableDef(LStream &stream);
	virtual ~T2ColdTableDef();
	Byte GetDenomi(UInt32 a, UInt32 b) const;

protected:
	UInt32 m4;
	Byte m8[12];
};
