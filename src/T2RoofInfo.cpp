#include "T2RoofInfo.h"
#include <Quickdraw.h>

T2RoofInfo::T2RoofInfo(Int16 left, Int16 top, Int16 right, Int16 bottom, Boolean flag) {
	::SetRect(&mRect, left, top, right, bottom);
	mFlag = flag;
}
