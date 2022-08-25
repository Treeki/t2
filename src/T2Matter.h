#pragma once

#include "T2DrawableObject.h"

#include <Quickdraw.h>

class T2MatterDef;
class T2ReturnStack;

class T2Matter : public T2DrawableObject {
public:
	T2Matter();
	void Initialize();
	~T2Matter();
	void SetUsed(Boolean value);
	void Initialize(T2MatterDef *def);
	void FlipDirection();
	void SetDestination(UInt16 dstTenant, UInt16 startTime);
	void ClearDestination();
	Boolean IsStartTime(UInt16 v) const;
	Boolean IsSetReturn() const;
	Boolean IsSetReturnTime() const;
	UInt16 GetReturnTime() const;
	UInt16 GetReturn() const;
	Boolean SetReturn(UInt16 tenant, UInt16 time);
	void SetReturnTime(UInt16 time);
	Boolean PopReturn(UInt16 &tenant, UInt16 &time);
	Boolean SetReturnToDestination();
	Boolean SetDestinationToReturn();
	void DayChanged();
	Boolean RemoveReturn(UInt16 tenant);
	void LoadSelf(LStream &stream, T2TowerDoc *doc);
	void SaveSelf(LStream &stream);

	UInt32 GetMatterID() { return mMatterID; }
	T2MatterDef *GetMatterDef() const { return mMatterDef; }
	Boolean IsFront() { }
	Boolean IsLast() { }
	UInt16 GetWorkTenant() const { return mWorkTenant; }
	UInt16 GetHomeTenant() const { return mHomeTenant; }
	UInt16 GetCurrEquipID() const { return mCurrEquipID; }
	void SetWorkTenant(UInt16 t) { mWorkTenant = t; }
	void SetHomeTenant(UInt16 t) { mHomeTenant = t; }
	void SetCurrEquipID(UInt16 t) { mCurrEquipID = t; }
	UInt16 GetDstTenant() { return mDstTenant; }
	Point GetCurPosition() const { return mCurPosition; }
	void SetDirection(char d) { mDirection = d; }
	char GetDirection() const { return mDirection; }
	Byte GetWalkStyle() const { return mWalkStyle; }
	void MoveHTo(Int16 h) { mCurPosition.h = h; }
	void MoveVTo(Int16 v) { mCurPosition.v = v; }
	Point GetCurrDestPos() const { return mCurrDestPos; }
	void SetCurrDestPos(Point pt) { mCurrDestPos = pt; }
	Boolean InDestFloor() const { return mCurPosition.v == mCurrDestPos.v; }
	Boolean IsGoDown() const {
		return (mCurrDestPos.v != mCurPosition.v) && (mCurrDestPos.v < mCurPosition.v);
	}
	Boolean IsSetStartTime() const { return mStartTime > 0; }
	Boolean IsSetDestination() const { return mDstTenant != 0; }
	UInt16 GetDestination() const { return mDstTenant; }
	void SetStartTime(UInt16 t) { mStartTime = t; }

	UInt32 mMatterID;
	T2MatterDef *mMatterDef;
	RgnHandle mRgn;
	UInt16 mWorkTenant;
	UInt16 mHomeTenant;
	UInt16 mCurrEquipID;
	UInt16 mDstTenant;
	Point mCurPosition;
	Point mCurrDestPos;
	Int16 mStartTime;
	T2ReturnStack *mReturnStack;
	void *m2C, *m30;
	char mDirection;
	Int8 mWalkStyle;
};
