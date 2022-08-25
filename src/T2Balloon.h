#pragma once

#include <PP_Types.h>

class LString;
class T2GWorld;
class T2TowerDoc;
class UT2Balloon;

class T2Balloon {
public:
	enum EOrientation {
		TopRight,
		TopLeft,
		BottomRight,
		BottomLeft
	};

	T2Balloon(T2TowerDoc *towerDoc, Point pt, const LString &str, Int32 time);
	~T2Balloon();
	void DrawBalloon(T2GWorld *gworld, const LString &str, EOrientation orientation);
	static void DrawBalloonTopRight(Rect rect, Rect &textRect);
	static void DrawBalloonBottomRight(Rect rect, Rect &textRect);
	static void DrawBalloonBottomLeft(Rect rect, Rect &textRect);
	static void DrawBalloonTopLeft(Rect rect, Rect &textRect);
	static EOrientation MakeRect(Point pt, Rect inRect, const LString &str, Rect &outRect);
	static Int32 CalcCR(const LString &str, Int16 &outMaxWidth);
	Boolean MouseInRect();
	void SetResumeArea(const Rect &rect);

	friend class UT2Balloon;

	UInt32 GetShowUntil() const { return mShowUntil; }

protected:
	T2TowerDoc *mTowerDoc;
	Int32 mSpriteIndex;
	UInt32 mShowUntil;
	Boolean mDidPauseDoc;
	Rect mResumeArea;
};

class UT2Balloon {
public:
	static void DoBalloon(T2TowerDoc *towerDoc, Point pt, const LString &str, Int32 time);
	static void DoBalloon(T2TowerDoc *towerDoc, const Rect &rect, const LString &str, Int32 time);
	static void Pick(T2TowerDoc *towerDoc, Boolean flag);
	static void SetBalloonOn(T2TowerDoc *towerDoc, Boolean on);
	static Boolean IsBalloonOn(T2TowerDoc *towerDoc);
};
