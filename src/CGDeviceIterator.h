#pragma once

#include "CGDevice.h"

class CGDeviceIterator {
public:
	CGDeviceIterator();
	virtual ~CGDeviceIterator();

	void Reset();
	GDHandle Current();
	Boolean Next(GDHandle &handle);

protected:
	GDHandle mCurrent;
};

