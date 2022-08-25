#pragma once

#include <LGAControlImp.h>

class T2GWorld;

class T2SliderImp : public LGAControlImp {
public:
	T2SliderImp(LControlPane *pane);
	T2SliderImp(LStream *inStream);
	~T2SliderImp();

	void Init(LControlPane *pane, LStream *stream);
	void Init(LControlPane *pane, Int16 inControlKind, ConstStringPtr inTitle, ResIDT inTextTraitsID, Int32 inRefCon);
	void DrawSelf();
	// B4
	virtual void DrawIndicatorTrack(Int16 depth);
	// B8
	virtual void DrawIndicator(Int16 depth, const Rect &rect, bool flag);
	void EraseIndicator(Int16 depth, const Rect &rect);
	void MoveIndicator(Int16 oldPos, Int16 newPos, bool flag);
	Int16 FindHotSpot(Point inPoint) const;
	Boolean PointInHotSpot(Point inPoint, Int16 inHotSpot) const;
	Boolean TrackHotSpot(Int16 inHotSpot, Point inPoint, Int16 inModifiers);
	void SetValue(Int32 value);
	// BC
	virtual void CalcIndicatorRect(Rect &rect, Int16 pos) const;
	// C0
	virtual void CalcTrackRect(Rect &rect) const;
	void FindIndicatorLimits(Int16 &indMin, Int16 &indMax) const;
	Int32 PositionToValue(Int16 pos) const;
	Int16 ValueToPosition(Int32 value) const;

protected:
	T2GWorld *mWorld1;
	T2GWorld *mWorld2;
	Rect mRect;
};
