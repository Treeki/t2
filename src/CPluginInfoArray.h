#pragma once

#include <LArray.h>
#include "CPluginInfoComparator.h"

class CPluginInfoArray : public LArray {
protected:
	Boolean _28;

public:
	CPluginInfoArray(Boolean flag);
	~CPluginInfoArray();
	int GetUsedCount();
};
