#include "T2UnitInfo.h"

T2UnitInfo::T2UnitInfo() {
	mMover = 0;
	mTenant = 0;
}

T2UnitInfo::~T2UnitInfo() {
}

Boolean T2UnitInfo::IsBuildable() const {
	return !(mMover & 0x8000);
}

Boolean T2UnitInfo::IsMoverID(UInt16 id) const {
	return (id != 0 && id < 1000);
}

Boolean T2UnitInfo::IsRequestID(UInt16 id) const {
	return (id >= 1000);
}

UInt16 T2UnitInfo::GetTenantID() const {
	UInt16 result = 0;
	if (mTenant != 0)
		result = mTenant & 0x7FFF;
	return result;
}

UInt16 T2UnitInfo::GetMoverID() const {
	UInt16 result = 0;
	if (mMover != 0) {
		result = mMover & 0x7FFF;
		if (!IsMoverID(result))
			result = 0;
	}
	return result;
}

UInt16 T2UnitInfo::GetRequestID() const {
	UInt16 result = 0;
	if (mMover != 0) {
		result = mMover & 0x7FFF;
		if (!IsRequestID(result))
			result = 0;
	}
	return result;
}

void T2UnitInfo::FillTenantID(UInt16 id) {
	mTenant &= 0x8000;
	mTenant += id;
}

void T2UnitInfo::FillMoverID(UInt16 id) {
	mMover &= 0x8000;
	mMover += id;
}

void T2UnitInfo::InitMask(LStream &stream) {
	Int16 value;
	stream >> value;

	if (value != 0) {
		mMover |= 0x8000;
	} else {
		mMover &= 0x7FFF;
	}
}

void T2UnitInfo::Read(LStream &stream) {
	stream >> mMover;
	stream >> mTenant;
}

void T2UnitInfo::Write(LStream &stream) {
	stream << mMover;
	stream << mTenant;
}
