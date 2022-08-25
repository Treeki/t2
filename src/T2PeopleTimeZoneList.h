#pragma once

#include <LArray.h>

class LStream;
class T2PeopleType;
class T2PeopleTypeArray;
class T2PoolDefDemandElem;
class T2TenantMemberDef;

class T2PeopleTimeZoneList : public LArray {
public:
	T2PeopleTimeZoneList(UInt8 someCount, UInt32 var);
	T2PeopleTimeZoneList(LStream &stream);
	void Add(T2PeopleType *peopleType, T2PoolDefDemandElem *inDemandElem);
	~T2PeopleTimeZoneList();
protected:
	void Add(T2PeopleTypeArray *array);
public:
	void Init(UInt16 a, float f);
	void IncHour(float f);
protected:
	T2PeopleTypeArray *GetItem(Int8 index) const;
	T2PeopleTypeArray *CurrentItem() const;
public:
	Boolean Find(T2TenantMemberDef *tmDef, Int32 var, Byte flags, Boolean otherFlag) const;
	Boolean Call(T2TenantMemberDef *tmDef, Int32 var, Byte flags, T2PeopleType &peopleType);
	void DispatchRestore(T2PeopleType &peopleType);
	void DispatchAdd(T2PeopleType *peopleType);
	void Write(LStream &stream) const;

	Boolean IsFixed() const { return mIsFixed; }
protected:
	// Int32 GetNumOfTimeZone() const { ... }

	Boolean mIsFixed;
	Int8 mMaxHour;
	Int8 mCurrent;
	Int8 mHour;
};
