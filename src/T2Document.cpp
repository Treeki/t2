#include "T2Document.h"

T2Document::T2Document(LCommander *inSuper, FSSpec *ignored, Int32 unk)
	: LSingleDoc(inSuper)
{
	m5C = unk;
}

T2Document::~T2Document() {
}
