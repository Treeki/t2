#pragma once

#include "T2DumpObj.h"

#include <LString.h>

class LStream;

class T2TenantMemberDef : public T2DumpObj {
public:
	T2TenantMemberDef();
	~T2TenantMemberDef();
	void Initialize(LStream &stream, float f);
	Int32 DrawData(Int32 pos);

	Int8 GetDemandType() const { return mDemandType; }
	Int8 GetStartSilhouetteType() const { return mStartSilhouetteType; }
	Int8 GetEndSilhouetteType() const { return mEndSilhouetteType; }
	Int8 GetOptionType() const { return mOptionType; }
	UInt32 GetNumOfPeople() const { return mNumOfPeople; }
	void SetNumOfPeople(UInt32 v) { mNumOfPeople = v; }
	float GetRate() const { return mRate; }
	void SetRate(float v) { mRate = v; }
	void GetName(LStr255 &s) const { s = mName; }
	UInt8 GetPercent() const { return mPercent; }
	void SetPercent(UInt8 v) { mPercent = v; }

	Str15 mName;
	Int8 mDemandType;
	Int8 mStartSilhouetteType;
	Int8 mEndSilhouetteType;
	Int8 mOptionType;
	UInt8 mPercent;
	UInt32 mNumOfPeople;
	float mRate;
};
