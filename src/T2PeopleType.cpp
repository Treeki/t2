#include "T2PeopleType.h"
#include "T2TenantMemberDef.h"
#include "UT2Utils.h"

#include <LStream.h>

T2PeopleType::T2PeopleType() {
	mAttribute = 0;
	mSilhouetteType = 0;
	mEconoType = 0;
	mTransportType = 0;
	mLife = 0;
}

T2PeopleType::~T2PeopleType() {
}

void T2PeopleType::SetDemandType(Int8 type) {
	mAttribute &= ~7;
	mAttribute |= (type & 7);
}

void T2PeopleType::SetTimeZoneType(Int8 type) {
	mAttribute &= 7;
	mAttribute |= ((type << 3) & 0xF8);
}

Int8 T2PeopleType::GetDemandType() const {
	return mAttribute & 7;
}

Int8 T2PeopleType::GetTimeZoneType() const {
	return (mAttribute & 0xF8) >> 3;
}

void T2PeopleType::RecoverLife() {
	if (!IsImmortal())
		mLife = 12;
}

void T2PeopleType::Duplicate(T2PeopleType &dest) const {
	dest = *this;
	dest.mLife = 1;

	Int32 econo = UT2Utils::Randomize(3) + mEconoType - 1;
	if (econo <= 0)
		econo = 1;
	else if (econo >= 7)
		econo = 6;
	dest.mEconoType = econo;
}

Boolean T2PeopleType::Check(T2TenantMemberDef *def, Int32 var, Byte flags) const {
	Boolean result = (flags & (1 << mTransportType)) != 0;

	if (result)
		result = CheckSilhouetteType(def);
	if (result)
		result = CheckSilhouetteOptionType(def->GetOptionType());
	if (result && var > -1) {
		if (mEconoType < var || mEconoType >= (var + 3))
			result = false;
	}

	return result;
}

Boolean T2PeopleType::CheckWithDemand(T2TenantMemberDef *def, Int32 var) const {
	return (CheckDemandType(def->GetDemandType()) && Check(def, var, 0xFF));
}

Boolean T2PeopleType::CheckDemandType(Int8 demandType) const {
	Boolean result = true;

	if (demandType != -1 && GetDemandType() != demandType)
		result = false;

	return result;
}

Boolean T2PeopleType::CheckSilhouetteType(T2TenantMemberDef *def) const {
	Boolean result = true;
	Int16 start = def->GetStartSilhouetteType();

	if (start < -1) {
		switch (start) {
			case -3:
				if (mSilhouetteType < 8 || mSilhouetteType >= 16)
					result = false;
				break;
			case -4:
				if (mSilhouetteType < 16 || mSilhouetteType >= 24)
					result = false;
				break;
			case -5:
				if (mSilhouetteType < 24 || mSilhouetteType >= 56)
					result = false;
				break;
			case -6:
				if (mSilhouetteType < 30 || mSilhouetteType >= 51)
					result = false;
				break;
		}
	} else if (start > -1) {
		if (mSilhouetteType < start) {
			result = false;
		} else {
			Int16 end = def->GetEndSilhouetteType();
			if (mSilhouetteType > end)
				result = false;
		}
	}

	return result;
}

Boolean T2PeopleType::CheckSilhouetteOptionType(Int16 var) const {
	Boolean result = true;

	if (var > -1) {
		if (var & 1) {
			if ((mSilhouetteType % 2) != 0)
				result = false;
		} else if (var & 2) {
			if ((mSilhouetteType % 2) == 0)
				result = false;
		}

		if (var & 4) {
			if (((mSilhouetteType / 4) % 2) != 0)
				result = false;
		} else if (var & 8) {
			if (((mSilhouetteType / 4) % 2) == 0)
				result = false;
		}
	}

	return result;
}

void T2PeopleType::Read(LStream &stream) {
	stream >> mAttribute;
	stream >> mSilhouetteType;
	stream >> mEconoType;
	stream >> mTransportType;
	stream >> mLife;
}

void T2PeopleType::Write(LStream &stream) const {
	stream << mAttribute;
	stream << mSilhouetteType;
	stream << mEconoType;
	stream << mTransportType;
	stream << mLife;
}
