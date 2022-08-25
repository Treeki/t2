#pragma once

#include <LComparator.h>
#include "CPluginInfo.h"

class CPluginInfoComparator : public LComparator {
public:
	Int32 Compare(const void *inItemOne, const void *inItemTwo, Uint32 inSizeOne, Uint32 inSizeTwo) const;
	Boolean IsEqualTo(const void *inItemOne, const void *inItemTwo, Uint32 inSizeOne, Uint32 inSizeTwo) const;
	Int32 CompareToKey(const void *inItem, Uint32 inSize, const void *inKey) const;
	~CPluginInfoComparator();

	static CPluginInfoComparator *GetComparator();

protected:
	static CPluginInfoComparator *sCPluginInfoComparator;
};
