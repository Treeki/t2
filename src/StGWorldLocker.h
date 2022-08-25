#pragma once

#include "T2GWorld.h"

class StGWorldLocker {
public:
	StGWorldLocker(T2GWorld *world);
	virtual ~StGWorldLocker();

protected:
	T2GWorld *mT2GWorld;
};
