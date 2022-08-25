#pragma once

#include "T2DrawableObject.h"

class T2FloorInfo;
class T2People;

class T2Request : public T2DrawableObject {
public:
	T2Request();
	~T2Request();

	void InitRequest(T2FloorInfo *floorInfo, UInt16 moverID, Point headPosition, Int16 upDown);
	void RemoveRequest(T2TowerDoc *doc);
	void RemoveContents(T2FloorInfo *floorInfo);
	void SetUsed(Boolean value);
	void StopRemoved(T2TowerDoc *doc, Int16 a);
	void CalcArea(Rect &rect);
	void CalcOnArea(Rect &rect);
	void CalcOffArea(Rect &rect);
	void CalcPrevArea(Rect &rect);
	Boolean CalcPersonArea(T2People *people, Rect &rect);
	Boolean CalcIncQueueArea(Rect &rect) const;
	Boolean Regist(T2TowerDoc *doc, T2People *people);
	Int32 Enter(CLink *link);
	Int32 Leave(CLink *link);
	T2People *LeaveFirst();
	void ChangeOffPPLStatus(T2FloorInfo *floorInfo, T2People *people);
	void AddOnPeople(T2People *people);
	T2People *RemoveOnPeople();
	void AddOffPeople(T2People *people);
	T2People *RemoveOffPeople();
	UInt32 Idle(T2TowerDoc *doc);
	void DrawFinished();
	void Draw(T2TowerDoc *doc, const Rect &rect);
	void DrawUp(T2TowerDoc *doc, const Rect &rect);
	void DrawDown(T2TowerDoc *doc, const Rect &rect);
	T2People *FindPeople(Int32 var) const;
	T2People *FindUpPeople(Int32 var) const;
	T2People *FindDownPeople(Int32 var) const;
	void BreakoutEmergency(T2TowerDoc *doc);
	void LoadSelf(LStream &stream, T2TowerDoc *doc);
	void SaveSelf(LStream &stream);

	UInt16 mRequestID;
	UInt16 mMoverID;
	Point mHeadPosition;
	Boolean mUpDown;
	Int8 mModuleIndex;
	Int16 mDrawWidth;
	Int16 m18;
	Int16 m1A;
	T2People *mOnPeople;
	T2People *mOffPeople;
	T2People *m24;
	T2People *m28;
	Boolean m2C;
	Boolean mPeopleRemoved;
	Int16 mNumOfContent;
};
