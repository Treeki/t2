#include "CLink.h"

CLink::CLink() {
	mNext = NULL;
	mPrev = NULL;
}

CLink::CLink(CLink *link) {
	mNext = NULL;
	mPrev = link;
	if (link)
		link->mNext = this;
}

CLink::~CLink() {
}

void CLink::InsertAt(CLink *link) {
	if (mNext == NULL) {
		mNext = link;
		if (link)
			link->mPrev = this;
	} else {
		CLink *saveNext = mNext;
		mNext = link;
		saveNext->mPrev = link;
		link->mNext = saveNext;
	}
}

void CLink::Remove() {
	CLink *oldPrev = mPrev;
	CLink *oldNext = mNext;
	mPrev = mNext = NULL;
	if (oldPrev)
		oldPrev->mNext = oldNext;
	if (oldNext)
		oldNext->mPrev = oldPrev;
}

int CLink::Count() const {
	int count = 1;
	CLink *iter = mNext;

	while (iter) {
		count++;
		iter = iter->mNext;
	}

	return count;
}
