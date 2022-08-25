#include "T2ActiveScroller.h"

T2ActiveScroller *T2ActiveScroller::CreateT2ActiveScrollerStream(LStream *inStream) {
	return new T2ActiveScroller(inStream);
}

T2ActiveScroller::T2ActiveScroller(LStream *inStream)
	: LActiveScroller(inStream)
{
}
