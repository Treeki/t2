#pragma once

#include <PP_Types.h>
#include "T2DayParamDef.h"
#include "T2DumpObj.h"
#include "T2PlaceParamDef.h"

class T2TenantMemberDef;
class T2TowerDoc;

class T2TenantMemberTableDef : public T2DumpObj {
public:
	T2TenantMemberTableDef(LStream &stream, float f);
	void Initialize();
	T2DayParamDef *MakeDayParamDef(ResIDT resID);
	T2PlaceParamDef *MakePlaceParamDef(ResIDT resID);
	~T2TenantMemberTableDef();
	Byte GetEconoType() const;
	Boolean IsCheckOnlyFirstEconoType() const;
	T2TenantMemberDef *GetElem(Int32 index) const;
	Boolean IsCollectFromPool(T2TowerDoc *towerDoc) const;
	Boolean IsCollectFromTenant() const;
	Boolean IsCollectFromFloor() const;
	Int16 GetScore(T2PlaceParamDef::EPlace place) const;
	Int32 DrawData(Int32 pos);

	UInt32 GetNumOfElem() const { return mNumOfElem; }
	Byte GetSpecialFlag() const { return mSpecialFlag; }

	Int8 mEconoType;
	Byte mSpecialFlag;
	T2DayParamDef *mDayParamDef;
	T2PlaceParamDef *mPlaceParamDef;
	UInt32 mNumOfElem;
	T2TenantMemberDef *mTenantMemberDef;
};
