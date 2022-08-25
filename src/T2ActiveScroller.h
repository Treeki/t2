#pragma once

#include <LActiveScroller.h>

class T2ActiveScroller : public LActiveScroller {
public:
	enum { class_ID = 'T2as' };

	T2ActiveScroller(LStream *inStream);

	static T2ActiveScroller *CreateT2ActiveScrollerStream(LStream *inStream);
};
