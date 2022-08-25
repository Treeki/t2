#include "T2ColdTableDef.h"

#include <LStream.h>

T2ColdTableDef::T2ColdTableDef(LStream &stream) {
	stream >> m4;
	for (UInt32 i = 0; i < 12; i++)
		stream >> m8[i];
}

T2ColdTableDef::~T2ColdTableDef() {
}

Byte T2ColdTableDef::GetDenomi(UInt32 a, UInt32 b) const {
	Byte result = 0;
	UInt32 index = b - 1;

	if (a >= m4 && index < 12)
		result = m8[index];

	return result;
}
