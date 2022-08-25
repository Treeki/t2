#pragma once

#include <PP_Types.h>

class LStream;
class T2TowerDoc;

class T2TrafficInfo {
public:
	struct Data {
		UInt16 a, b;
		Int16 c;
	};

	T2TrafficInfo(Rect rect, UInt16 a, UInt16 b, UInt16 c, UInt16 unitSize);
	virtual ~T2TrafficInfo();
	void Pass(Point ptA, Point ptB, Int16 value);
	void HourChanged(T2TowerDoc *towerDoc);
	UInt32 CalcRange(UInt16 value) const;
	void CalcUnitArea(UInt32 a, Rect &rect) const;
	Int32 GetRange(Point pt) const;
	Data *GetUnit(Point pt) const;
	Int32 CalcUnitIndex(Point pt) const;
	void Read(LStream &stream);
	void Write(LStream &stream) const;

	UInt16 mUnitSize;
	UInt16 m6;
	UInt16 m8;
	UInt16 mA;
	Rect mRect;
	UInt16 m14;
	UInt16 m16;
	Data *mData;
};
