#pragma once

#include <LSingleDoc.h>

class T2Document : public LSingleDoc {
public:
	T2Document(LCommander *inSuper, FSSpec *ignored, Int32 unk);
	~T2Document();

protected:
	Int32 m5C;
};
