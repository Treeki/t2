#include "CLinkIterator.h"

CLinkIterator::CLinkIterator(CLink *link) {
	mStart = link;
	mCurrent = 0;
}

CLinkIterator::~CLinkIterator() {
}

Boolean CLinkIterator::Current(CLink **link) {
	if (mCurrent != NULL) {
		*link = mCurrent;
		return true;
	}

	return false;
}

Boolean CLinkIterator::Prev(CLink **link) {
	if (mCurrent != NULL) {
		mCurrent = mCurrent->mPrev;
		return Current(link);
	} else {
		return false;
	}
}

Boolean CLinkIterator::Next(CLink **link) {
	if (mCurrent != NULL) {
		mCurrent = mCurrent->mNext;
		return Current(link);
	} else {
		mCurrent = mStart;
		return Current(link);
	}
}
