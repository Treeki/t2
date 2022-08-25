#pragma once

#include <Types.h>

class CLink {
	friend class CLinkIterator;

protected:
	CLink *mNext, *mPrev;

public:
	CLink();
	CLink(CLink *link);
	virtual ~CLink();

	void InsertAt(CLink *link);
	void Remove();
	int Count() const;

	CLink *GetNext() { return mNext; }
	CLink *GetPrev() { return mPrev; }
	void SetNext(CLink *link) { mNext = link; }
	void SetPrev(CLink *link) { mPrev = link; }
};
