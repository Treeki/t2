#pragma once

#include <LArray.h>

class LStream;
class T2PeopleTimeZoneList;
class T2PeopleType;
class T2PoolDef;
class T2PoolGradeDef;
class T2SeasonParamDef;
class T2TenantMemberDef;

class T2PeopleDemandList : public LArray {
public:
	T2PeopleDemandList(T2PoolDef *poolDef, T2SeasonParamDef *seasonParamDef);
	T2PeopleDemandList(LStream &stream, T2SeasonParamDef *seasonParamDef);
	void Add(T2PoolGradeDef *inGradeDef);
	~T2PeopleDemandList();
	void Add(T2PeopleTimeZoneList *list);
	void Init(UInt16 a, UInt16 b);
	void IncHour(UInt16 a);
	T2PeopleTimeZoneList *GetItem(Int8 index) const;
	Boolean Find(T2TenantMemberDef *tmDef, Int32 var, Byte flags, Boolean otherFlag) const;
	Boolean Call(T2TenantMemberDef *tmDef, Int32 var, Byte flags, T2PeopleType &peopleType) const;
	void DispatchRestore(T2PeopleType &peopleType);
	void DispatchAdd(T2PeopleType *peopleType);
	void Write(LStream &stream) const;

	T2SeasonParamDef *mSeasonParamDef;
};
