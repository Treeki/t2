#pragma once

#include <LPane.h>

class UT2Coordinate {
public:
	static Int32 UnitVSize(Int32 factor) { return 36 >> factor; }
	static Int32 UnitHSize(Int32 factor) { return 8 >> factor; }
	static Int32 BkgndVSize(Int32 factor) { return 72 >> factor; }
	static Int32 BkgndHSize(Int32 factor) { return 64 >> factor; }
	static Int32 CalcRoofThick(Int32 factor) { return 8 >> factor; }
	static Int32 CalcFloorThick(Int32 factor) { return 4 >> factor; }
	static void QDToOff(Point &point, Int32 factor) {
		point.v <<= factor;
		point.h <<= factor;
	}

	static void UnitToQD(Int32 &y, Int32 &x, Int32 factor);
	static void UnitToQD(Point &point, Int32 factor, UInt32 flag);
	static void UnitToQD(Rect &rect, Int32 factor, UInt32 flag);
	static void UnitToQD(const Rect &inRect, Rect &outRect, Int32 factor, UInt32 flag);
	static void UnitToQDRoof(const Rect &inRect, Rect &outRect, Int32 factor);
	static void UnitToQDFloor(const Rect &inRect, Rect &outRect, Int32 factor);
	static void UnitToOffRect(const Rect &inRect, Rect &outRect, Int32 factor, Boolean flag);

	static void QDToUnit(Int32 &y, Int32 &x, Int32 factor);
	static void QDToUnit(Point &point, Int32 factor);
	static void QDToUnit(SDimension16 &dim, Int32 factor);
	static void QDToUnit(Rect &rect, Int32 factor);
	static void QDToUnit(const Rect &inRect, Rect &outRect, Int32 factor);
	static void NoRoofQDToUnit(const Rect &inRect, Rect &outRect, Int32 factor);

	static void BkgndToQD(Int32 &y, Int32 &x, Int32 factor);
	static void BkgndToQD(Point &point, Int32 factor);
	static void BkgndToQD(Rect &rect, Int32 factor);
	static void BkgndToQD(const Rect &inRect, Rect &outRect, Int32 factor);

	static void QDToBkgnd(Int32 &y, Int32 &x, Int32 factor);
	static void QDToBkgnd(Point &point, Int32 factor);
	static void QDToBkgnd(SDimension16 &dim, Int32 factor);
	static void QDToBkgnd(Rect &rect, Int32 factor);
	static void QDToBkgnd(const Rect &inRect, Rect &outRect, Int32 factor);

	static void UnitToBkgnd(const Rect &inRect, Rect &outRect);

	static void BkgndToUnit(const Rect &inRect, Rect &outRect);

	static void MakeRect(Rect &rect, const Point &pt, const SDimension16 &dim);
	static void MakeRect(Rect &rect, const Point &pt, Int32 width, Int32 height);
	static void MakeRect(Rect &rect, Int32 width, Int32 height);

	static void MakeCenterRect(Rect &rect, const Point &pt, Int32 width, Int32 height);

	static void AddRect(Rect &rect, const Rect &other);
	static void SubRect(Rect &rect, const Rect &other);

	static void ZoomOut(Rect &rect, Int32 factor);
	static void ZoomIn(Rect &rect, Int32 factor);
};
