#pragma once

#include "CLink.h"

class CLinkIterator {
protected:
	CLink *mStart, *mCurrent;

public:
	CLinkIterator(CLink *link);
	virtual ~CLinkIterator();

	Boolean Current(CLink **link);
	Boolean Prev(CLink **link);
	Boolean Next(CLink **link);
};
