#include "UPoint.h"

void UPoint::MappingInRect(Point &pt, const Rect &rect) {
	pt.h = (pt.h < rect.right) ? pt.h : (rect.right - 1);
	pt.h = (pt.h >= rect.left) ? pt.h : rect.left;
	pt.v = (pt.v < rect.bottom) ? pt.v : (rect.bottom - 1);
	pt.v = (pt.v >= rect.top) ? pt.v : rect.top;
}
