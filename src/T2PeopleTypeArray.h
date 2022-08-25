#pragma once

#include <LArray.h>

class LStream;
class T2PeopleType;
class T2PoolTimeZoneDef;
class T2TenantMemberDef;

class T2PeopleTypeArray : public LArray {
public:
	T2PeopleTypeArray(UInt32 var);
	T2PeopleTypeArray(LStream &stream);
	void Add(T2PeopleType *peopleType, T2PoolTimeZoneDef *tzDef, UInt32 count);
	~T2PeopleTypeArray();
	void Add(T2PeopleType *peopleType, UInt32 count, ArrayIndexT index);
	void AdjustLife();
	void InitSearchLimit(float limit);
	Boolean Find(T2TenantMemberDef *tmDef, Int32 var, Byte flags, Boolean otherFlag) const;
	Boolean Call(T2TenantMemberDef *tmDef, Int32 var, Byte flags, T2PeopleType &peopleType);
	void Restore(T2PeopleType &peopleType);
	void Read(LStream &stream);
	void Write(LStream &stream) const;

	UInt32 m28;
	Int32 m2C;
	Int32 m30;
};
