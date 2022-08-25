#pragma once

#include <LScroller.h>

class CScrollerNoBorder : public LScroller {
public:
	enum { class_ID = 'scnb' };

	CScrollerNoBorder(LStream *inStream);

	static CScrollerNoBorder *CreateCScrollerNoBorderStream(LStream *inStream) {
		return new CScrollerNoBorder(inStream);
	}

	virtual void DrawSelf();
};
