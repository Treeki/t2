#pragma once

#include <LArray.h>

class LStream;

class T2IOAbleValueArray : public LArray {
public:
	T2IOAbleValueArray(Uint32 itemSize);
	~T2IOAbleValueArray();

	virtual void Read(LStream &stream);
	virtual void Write(LStream &stream);
};
