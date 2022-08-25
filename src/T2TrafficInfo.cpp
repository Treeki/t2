#include "T2TowerMainView.h"
#include "T2TrafficInfo.h"
#include "URect.h"

#include <LStream.h>
#include <UException.h>

T2TrafficInfo::T2TrafficInfo(Rect rect, UInt16 a, UInt16 b, UInt16 c, UInt16 unitSize) {
	mUnitSize = unitSize;
	#line 26
	Assert_(mUnitSize != 0);

	if (mUnitSize == 0)
		mUnitSize = 4;

	m6 = a;
	m8 = b;
	mA = c;
	mRect = rect;
	m14 = URect::Height(rect);
	m16 = URect::Width(rect) / mUnitSize;
	mData = new Data[m16 * m14];
	#line 38
	ThrowIfNil_(mData);

	UInt32 count = m16 * m14;
	Data *data = mData;
	for (UInt32 i = 0; i < count; i++, data++) {
		data->a = 0;
		data->b = 0;
	}
}

T2TrafficInfo::~T2TrafficInfo() {
	if (mData)
		delete[] mData;
}

void T2TrafficInfo::Pass(Point ptA, Point ptB, Int16 value) {
	Point ptA2, ptB2;

	if (ptA.h < ptB.h) {
		ptA2 = ptA;
		ptB2 = ptB;
		ptB2.v = ptA.v;
	} else {
		ptA2 = ptB;
		ptA2.v = ptA.v;
		ptB2 = ptA;
	}

	Data *unitA = GetUnit(ptA2);
	Data *unitB = GetUnit(ptB2);
	if (unitA && unitB) {
		for (Data *unit = unitA; unit <= unitB; unit++) {
			unit->a += value;
		}
	}
}

void T2TrafficInfo::HourChanged(T2TowerDoc *towerDoc) {
	// TODO T2FloorInfo
}

UInt32 T2TrafficInfo::CalcRange(UInt16 value) const {
	UInt32 result = 3;

	if (value < m6)
		result = 0;
	else if (value < m8)
		result = 1;
	else if (value < mA)
		result = 2;

	return result;
}

void T2TrafficInfo::CalcUnitArea(UInt32 a, Rect &rect) const {
	static const Point zero = { 0, 0 };

	Point pt = zero;
	pt.v = a / m16;
	pt.h = mUnitSize * (a % m16);

	::SetRect(&rect, pt.h, pt.v, pt.h + mUnitSize, pt.v + 1);
	::OffsetRect(&rect, mRect.left, mRect.top);
}

Int32 T2TrafficInfo::GetRange(Point pt) const {
	Int32 result = 0;

	Data *unit = GetUnit(pt);
	if (unit)
		result = unit->c;

	return result;
}

T2TrafficInfo::Data *T2TrafficInfo::GetUnit(Point pt) const {
	Data *result = 0;

	if (mData) {
		Int32 index = CalcUnitIndex(pt);
		if (index > 0)
			result = &mData[index];
	}

	return result;
}

Int32 T2TrafficInfo::CalcUnitIndex(Point pt) const {
	Int32 result = -1;

	if (::PtInRect(pt, &mRect)) {
		static const Point zero = { 0, 0 };

		Point pt2 = zero;
		pt2.v = pt.v - mRect.top;
		pt2.h = (pt.h - mRect.left) / mUnitSize;
		result = pt2.h + (m16 * pt2.v);
	}

	return result;
}

void T2TrafficInfo::Read(LStream &stream) {
	UInt32 count = m16 * m14;
	Data *data = mData;
	for (UInt32 i = 0; i < count; i++, data++) {
		stream >> data->a;
		stream >> data->b;
		data->c = CalcRange(data->b);
	}
}

void T2TrafficInfo::Write(LStream &stream) const {
	UInt32 count = m16 * m14;
	Data *data = mData;
	for (UInt32 i = 0; i < count; i++, data++) {
		stream << data->a;
		stream << data->b;
	}
}
