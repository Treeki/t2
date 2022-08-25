#include "T2WordDef.h"

#include <LStream.h>

T2WordDef::T2WordDef() {
}

void T2WordDef::Read(LStream &stream) {
	stream >> m4;
	stream >> m5;
	stream >> m6;
	stream >> m7;

	for (UInt32 i = 0; i < 64; i++) {
		unsigned char c;
		stream >> c;
		m8[i] = c;
	}
}

T2WordDef::~T2WordDef() {
}

void T2WordDef::GetWords(Uchar a, Uchar b, Uchar c, Uchar d, Str63 &str) const {
	if ((m4 & (1 << a)) && (m5 & (1 << b)) && (m6 == c) && (m7 == d)) {
		for (UInt32 i = 0; i <= m8[0]; i++) {
			str[i] = m8[i];
		}
	}
}
