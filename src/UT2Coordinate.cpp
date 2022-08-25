#include "UT2Coordinate.h"
#include <Quickdraw.h>

void UT2Coordinate::UnitToQD(Int32 &y, Int32 &x, Int32 factor) {
	y *= UnitVSize(factor);
	x <<= 3 - factor;
}

void UT2Coordinate::UnitToQD(Point &point, Int32 factor, UInt32 flag) {
	point.v *= UnitVSize(factor);
	point.h <<= 3 - factor;
	if (!flag)
		point.v += CalcRoofThick(factor);
}

void UT2Coordinate::UnitToQD(Rect &rect, Int32 factor, UInt32 flag) {
	rect.top *= UnitVSize(factor);
	rect.left <<= 3 - factor;
	rect.bottom *= UnitVSize(factor);
	rect.right <<= 3 - factor;
	if (!flag) {
		rect.top += CalcRoofThick(factor);
		rect.bottom -= CalcFloorThick(factor);
	}
}

void UT2Coordinate::UnitToQD(const Rect &inRect, Rect &outRect, Int32 factor, UInt32 flag) {
	outRect.top = inRect.top * UnitVSize(factor);
	outRect.left = inRect.left << (3 - factor);
	outRect.bottom = inRect.bottom * UnitVSize(factor);
	outRect.right = inRect.right << (3 - factor);
	if (!flag) {
		outRect.top += CalcRoofThick(factor);
		outRect.bottom -= CalcFloorThick(factor);
	}
}

void UT2Coordinate::UnitToQDRoof(const Rect &inRect, Rect &outRect, Int32 factor) {
	outRect.top = inRect.top * UnitVSize(factor);
	outRect.left = inRect.left << (3 - factor);
	outRect.bottom = outRect.top + CalcRoofThick(factor);
	outRect.right = inRect.right << (3 - factor);
}

void UT2Coordinate::UnitToQDFloor(const Rect &inRect, Rect &outRect, Int32 factor) {
	outRect.left = inRect.left << (3 - factor);
	outRect.bottom = inRect.bottom * UnitVSize(factor);
	outRect.right = inRect.right << (3 - factor);
	outRect.top = outRect.bottom - CalcFloorThick(factor);
}

void UT2Coordinate::UnitToOffRect(const Rect &inRect, Rect &outRect, Int32 factor, Boolean flag) {
	UnitToQD(inRect, outRect, 0, flag);
	::OffsetRect(&outRect, 0, -outRect.top);

	int bottom = outRect.bottom;
	::OffsetRect(&outRect, 0, bottom * factor);
}

void UT2Coordinate::QDToUnit(Int32 &y, Int32 &x, Int32 factor) {
	y /= UnitVSize(factor);
	x >>= 3 - factor;
}

void UT2Coordinate::QDToUnit(Point &point, Int32 factor) {
	point.v /= UnitVSize(factor);
	point.h >>= 3 - factor;
}

void UT2Coordinate::QDToUnit(SDimension16 &dim, Int32 factor) {
	dim.height /= UnitVSize(factor);
	dim.width >>= 3 - factor;
}

void UT2Coordinate::QDToUnit(Rect &rect, Int32 factor) {
	Rect rectOrig = rect;

	rect.top /= UnitVSize(factor);
	rect.left >>= 3 - factor;
	rect.bottom /= UnitVSize(factor);
	rect.right >>= 3 - factor;

	if ((rectOrig.bottom % UnitVSize(factor)) != 0)
		rect.bottom++;
	if ((rectOrig.right % UnitHSize(factor)) != 0)
		rect.right++;
}

void UT2Coordinate::QDToUnit(const Rect &inRect, Rect &outRect, Int32 factor) {
	outRect.top = inRect.top / UnitVSize(factor);
	outRect.left = inRect.left >> (3 - factor);
	outRect.bottom = inRect.bottom / UnitVSize(factor);
	outRect.right = inRect.right >> (3 - factor);

	if ((inRect.bottom % UnitVSize(factor)) != 0)
		outRect.bottom++;
	if ((inRect.right % UnitHSize(factor)) != 0)
		outRect.right++;
}

void UT2Coordinate::NoRoofQDToUnit(const Rect &inRect, Rect &outRect, Int32 factor) {
	outRect.top = inRect.top / UnitVSize(factor);
	outRect.left = inRect.left >> (3 - factor);
	outRect.bottom = (inRect.bottom + CalcRoofThick(factor) + CalcFloorThick(factor)) / UnitVSize(factor);
	outRect.right = inRect.right >> (3 - factor);
}

void UT2Coordinate::BkgndToQD(Int32 &y, Int32 &x, Int32 factor) {
	y *= BkgndVSize(factor);
	x <<= 6 - factor;
}

void UT2Coordinate::BkgndToQD(Point &point, Int32 factor) {
	point.v *= BkgndVSize(factor);
	point.h <<= 6 - factor;
}

void UT2Coordinate::BkgndToQD(Rect &rect, Int32 factor) {
	rect.top *= BkgndVSize(factor);
	rect.left <<= 6 - factor;
	rect.bottom *= BkgndVSize(factor);
	rect.right <<= 6 - factor;
}

void UT2Coordinate::BkgndToQD(const Rect &inRect, Rect &outRect, Int32 factor) {
	outRect.top = (short) inRect.top * BkgndVSize(factor);
	outRect.left = inRect.left << (6 - factor);
	outRect.bottom = (short) inRect.bottom * BkgndVSize(factor);
	outRect.right = inRect.right << (6 - factor);
}

void UT2Coordinate::QDToBkgnd(Int32 &y, Int32 &x, Int32 factor) {
	y /= BkgndVSize(factor);
	x >>= 6 - factor;
}

void UT2Coordinate::QDToBkgnd(Point &point, Int32 factor) {
	point.v /= BkgndVSize(factor);
	point.h >>= 6 - factor;
}

void UT2Coordinate::QDToBkgnd(SDimension16 &dim, Int32 factor) {
	dim.height /= BkgndVSize(factor);
	dim.width >>= 6 - factor;
}

void UT2Coordinate::QDToBkgnd(Rect &rect, Int32 factor) {
	rect.top /= BkgndVSize(factor);
	rect.left >>= 6 - factor;
	rect.bottom /= BkgndVSize(factor);
	rect.right >>= 6 - factor;
}

void UT2Coordinate::QDToBkgnd(const Rect &inRect, Rect &outRect, Int32 factor) {
	outRect.top = inRect.top / BkgndVSize(factor);
	outRect.left = inRect.left >> (6 - factor);
	outRect.bottom = inRect.bottom / BkgndVSize(factor);
	outRect.right = inRect.right >> (6 - factor);
}

void UT2Coordinate::UnitToBkgnd(const Rect &inRect, Rect &outRect) {
	outRect.top = inRect.top >> 1;
	outRect.left = inRect.left >> 3;
	outRect.bottom = inRect.bottom >> 1;
	outRect.right = inRect.right >> 3;

	if (inRect.bottom & 1)
		outRect.bottom++;
	if (inRect.right & 7)
		outRect.right++;
}

void UT2Coordinate::BkgndToUnit(const Rect &inRect, Rect &outRect) {
	outRect.top = inRect.top * 2;
	outRect.left = inRect.left * 8;
	outRect.bottom = inRect.bottom * 2;
	outRect.right = inRect.right * 8;
}

void UT2Coordinate::MakeRect(Rect &rect, const Point &pt, const SDimension16 &dim) {
	rect.top = pt.v;
	rect.left = pt.h;
	rect.bottom = rect.top + dim.height;
	rect.right = rect.left + dim.width;
}

void UT2Coordinate::MakeRect(Rect &rect, const Point &pt, Int32 width, Int32 height) {
	rect.top = pt.v;
	rect.left = pt.h;
	rect.bottom = rect.top + height;
	rect.right = rect.left + width;
}

void UT2Coordinate::MakeRect(Rect &rect, Int32 width, Int32 height) {
	rect.top = 0;
	rect.left = 0;
	rect.bottom = height;
	rect.right = width;
}

void UT2Coordinate::MakeCenterRect(Rect &rect, const Point &pt, Int32 width, Int32 height) {
	Int32 halfWidth = width >> 1;
	Int32 halfHeight = height >> 1;
	rect.top = pt.v - halfHeight;
	rect.left = pt.h - halfWidth;
	rect.bottom = rect.top + height;
	rect.right = rect.left + width;
}

void UT2Coordinate::AddRect(Rect &rect, const Rect &other) {
	rect.top += other.top;
	rect.left += other.left;
	rect.bottom += other.bottom;
	rect.right += other.right;
}

void UT2Coordinate::SubRect(Rect &rect, const Rect &other) {
	rect.top -= other.top;
	rect.left -= other.left;
	rect.bottom -= other.bottom;
	rect.right -= other.right;
}

void UT2Coordinate::ZoomOut(Rect &rect, Int32 factor) {
	rect.top >>= factor;
	rect.left >>= factor;
	rect.bottom >>= factor;
	rect.right >>= factor;
}

void UT2Coordinate::ZoomIn(Rect &rect, Int32 factor) {
	rect.top <<= factor;
	rect.left <<= factor;
	rect.bottom <<= factor;
	rect.right <<= factor;
}
