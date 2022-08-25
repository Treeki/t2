#pragma once

#include "T2UnitUpdtView.h"

class T2GWorld;
class T2ToolDef;
class T2TowerDoc;

class T2TowerMainView : public T2UnitUpdtView {
public:
	T2TowerMainView(LStream *stream);
	~T2TowerMainView();
	void InitT2TowerMainView(T2TowerDoc *doc, Int32 a, Int32 b);
	void AdjustCursorSelf(Point pt, const EventRecord &event);
	void DrawSelf();
	void AddSpriteUpdateRect(const Rect &rect, Boolean flag1, Boolean flag2);
	void DrawSimulation();
	void DrawSimulationOffscreen();
	void CopySimulationImage(const Rect &rect);
	void ScrollImageBy(Int32 h, Int32 v, Boolean refresh);
	void ScrollBits(Int32 h, Int32 v);
	void Click(SMouseDownEvent &event);
	void ClickSelf(const SMouseDownEvent &event);
	Int32 LimitCheckLeftDelta(Int32 value);
	Int32 LimitCheckTopDelta(Int32 value);
	void AdjustWorldBounds();
	void DoHandScroll();
	void DoZoom(const SMouseDownEvent &event);
	void DoZoomNormal(const Rect &rect);
	void SetClipURect();
	void ResizeFrameBy(Int16 width, Int16 height, Boolean refresh);
	void ReconcileFrameAndImage(Boolean refresh);
	void InvalUnitView();
	Boolean IsScrollToPt(Point pt, Int16 var);
	UInt32 PointAreaCheck(Point pt);
	void CenterOnView(Rect rect);
	void PointByArrow(const Rect &rect, Boolean flag, Int16 var);
	void CheckIfHideArrow();
	void HideArrow();
	Boolean IsPauseByArrow() const;
	void DisposeCursors();
	void TrackingCursor(const EventRecord &event);
	void HideCursor();
	void SimulateDragBuild(Point pt, Rect &rect);
	void FrameCursor();
	void DoEmergency();

	T2TowerDoc *mTowerDoc;
	Rect m98;
	T2GWorld *mGWorld;
	Point mClickLocation;
	Rect mSpriteUpdateRect;
	T2ToolDef *mToolDef;
	UInt8 mB4;
	UInt8 mB5;
	UInt16 mB6;
	UInt16 mB8;
	T2GWorld *mCursorGWorld;
	Int32 mCursorSpriteIndex;
	Rect mC4;
	Int16 mCC;
	Int32 mArrowSpriteIndex;
	Boolean mD4;
	UInt32 mArrowPauseUntilTicks;
	Boolean mDC;
	Boolean mEmergencyFlag;
};
