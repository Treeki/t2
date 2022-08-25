#pragma once

#include <PP_Types.h>

class LStream;
class T2TenantMemberDef;

class T2PeopleType {
public:
	T2PeopleType();
	~T2PeopleType();

	void SetDemandType(Int8 type);
	void SetTimeZoneType(Int8 type);
	Int8 GetDemandType() const;
	Int8 GetTimeZoneType() const;
	void RecoverLife();
	void Duplicate(T2PeopleType &dest) const;
	Boolean Check(T2TenantMemberDef *def, Int32 var, Byte flags) const;
	Boolean CheckWithDemand(T2TenantMemberDef *def, Int32 var) const;
	Boolean CheckDemandType(Int8 demandType) const;
	Boolean CheckSilhouetteType(T2TenantMemberDef *def) const;
	Boolean CheckSilhouetteOptionType(Int16 var) const;
	void Read(LStream &stream);
	void Write(LStream &stream) const;

	void SetSilhouetteType(Int8 t) { mSilhouetteType = t; }
	void SetEconoType(Int8 t) { mEconoType = t; }
	void SetTransportType(Int8 t) { mTransportType = t; }
	void SetLifeCount(Int8 l) { mLife = l; }
	Int8 GetSilhouetteType() const { return mSilhouetteType; }
	Int8 GetTransportType() const { return mTransportType; }
	Int8 GetAge() const { return mSilhouetteType >> 8; }
	Boolean IsMale() const { return (mSilhouetteType % 2) == 0; }
	Boolean IsImmortal() const { return mLife == 127; }
	Boolean HasLife() const { return mLife > 0; }
	void DecreaseLife() {
		if (!IsImmortal()) mLife--;
	}
	Int8 GetEconoType() const { return mEconoType; }

	Byte mAttribute;
	Int8 mSilhouetteType;
	Int8 mEconoType;
	Int8 mTransportType;
	Int8 mLife;
};
