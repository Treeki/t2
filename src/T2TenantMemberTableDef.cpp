#include "T2DateTime.h"
#include "T2PaletteAnime.h"
#include "T2TenantMemberDef.h"
#include "T2TenantMemberTableDef.h"
#include "T2TowerDoc.h"
#include "UDebugUtils.h"
#include "UT2Utils.h"

#include <LHandleStream.h>
#include <LStream.h>
#include <LString.h>
#include <UException.h>

T2TenantMemberTableDef::T2TenantMemberTableDef(LStream &stream, float f) {
	Initialize();

	stream >> mEconoType;
	stream >> mSpecialFlag;

	ResIDT dayResID;
	stream >> dayResID;
	if (dayResID > 0)
		mDayParamDef = MakeDayParamDef(dayResID);

	try {
		ResIDT placeResID;
		stream >> placeResID;
		if (placeResID > 0)
			mPlaceParamDef = MakePlaceParamDef(placeResID);

		stream >> mNumOfElem;
		if (mNumOfElem) {
			mTenantMemberDef = new T2TenantMemberDef[mNumOfElem];
			#line 56
			ThrowIfNil_(mTenantMemberDef);

			for (UInt32 i = 0; i < mNumOfElem; i++) {
				mTenantMemberDef[i].Initialize(stream, f);
			}
		}
	} catch (ExceptionCode code) {
		delete this;
		#line 67
		Throw_(code);
	}
}

void T2TenantMemberTableDef::Initialize() {
	mEconoType = 0;
	mSpecialFlag = 0;
	mDayParamDef = 0;
	mPlaceParamDef = 0;
	mNumOfElem = 0;
	mTenantMemberDef = 0;
}

T2DayParamDef *T2TenantMemberTableDef::MakeDayParamDef(ResIDT resID) {
	Handle res = ::Get1Resource('DpDf', resID);
	#line 105
	ThrowIfNil_(res);

	::DetachResource(res);
	LHandleStream stream(res);
	T2DayParamDef *def = new T2DayParamDef(stream);
	#line 109
	ThrowIfNil_(def);
	return def;
}

T2PlaceParamDef *T2TenantMemberTableDef::MakePlaceParamDef(ResIDT resID) {
	Handle res = ::Get1Resource('PpDf', resID);
	#line 127
	ThrowIfNil_(res);

	::DetachResource(res);
	LHandleStream stream(res);
	T2PlaceParamDef *def = new T2PlaceParamDef(stream);
	#line 131
	ThrowIfNil_(def);
	return def;
}

T2TenantMemberTableDef::~T2TenantMemberTableDef() {
	delete mDayParamDef;
	delete mPlaceParamDef;
	delete[] mTenantMemberDef;
}

Byte T2TenantMemberTableDef::GetEconoType() const {
	Byte result = mEconoType;
	if (mEconoType != -1)
		result &= ~0x10;
	return result;
}

Boolean T2TenantMemberTableDef::IsCheckOnlyFirstEconoType() const {
	Boolean result = false;
	if (mEconoType != -1)
		result = (mEconoType & 0x10) != 0;
	return result;
}

T2TenantMemberDef *T2TenantMemberTableDef::GetElem(Int32 index) const {
	T2TenantMemberDef *result = 0;
	if (index >= 0 && index < mNumOfElem)
		result = &mTenantMemberDef[index];
	return result;
}

Boolean T2TenantMemberTableDef::IsCollectFromPool(T2TowerDoc *towerDoc) const {
	Boolean result = true;

	if (mPlaceParamDef && UT2Utils::Float2Int(mPlaceParamDef->GetRate(T2PlaceParamDef::Place0)) == 0)
		result = false;

	if (result && mDayParamDef) {
		UInt32 r27 = 0;
		UInt32 r26 = 0;
		if (towerDoc->GetSomeDateTime()->IsHoliday(towerDoc))
			r27 = 1;
		T2PaletteAnime *paletteAnime = towerDoc->GetPaletteAnime();
		Boolean r30 = true;
		if (paletteAnime->m2A == 3 || paletteAnime->m2A == 4)
			r30 = false;
		if (!r30)
			r26 = 1;
		if (UT2Utils::Float2Int(mDayParamDef->GetRate(r27, r26)) == 0)
			result = false;
	}

	return result;
}

Boolean T2TenantMemberTableDef::IsCollectFromTenant() const {
	Boolean result = false;

	if (mPlaceParamDef && UT2Utils::Float2Int(mPlaceParamDef->GetRate(T2PlaceParamDef::Place1)) != 0)
		result = true;

	return result;
}

Boolean T2TenantMemberTableDef::IsCollectFromFloor() const {
	Boolean result = false;

	if (mPlaceParamDef && UT2Utils::Float2Int(mPlaceParamDef->GetRate(T2PlaceParamDef::Place2)) != 0)
		result = true;

	return result;
}

Int16 T2TenantMemberTableDef::GetScore(T2PlaceParamDef::EPlace place) const {
	Int16 result = 0;

	if (mPlaceParamDef)
		result = mPlaceParamDef->GetScore(place);
	else if (place == T2PlaceParamDef::Place0)
		result = 1000;

	return result;
}

Int32 T2TenantMemberTableDef::DrawData(Int32 pos) {
	Int16 p = pos;
	LStr255 tmp;

	p += 16;
	::MoveTo(10, p);
	::DrawString("\p================================");

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmEconoType : ");
	tmp = (Int32) mEconoType;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmSpecialFlag : ");
	tmp = (Int32) mSpecialFlag;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmDayParamDef : ");
	UDebugUtils::HexString(&mDayParamDef, tmp);
	::DrawString(tmp);

	if (mDayParamDef)
		p = mDayParamDef->DrawData(p);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmPlaceParamDef : ");
	UDebugUtils::HexString(&mPlaceParamDef, tmp);
	::DrawString(tmp);

	if (mPlaceParamDef)
		p = mPlaceParamDef->DrawData(p);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmNumOfElem : ");
	tmp = (Int32) mNumOfElem;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmTenantMemberDef : ");
	UDebugUtils::HexString(&mTenantMemberDef, tmp);
	::DrawString(tmp);

	for (UInt32 i = 0; i < mNumOfElem; i++) {
		p += 16;
		::MoveTo(10, p);
		::DrawString("\p[");
		tmp = (Int32) i;
		::DrawString(tmp);
		::DrawString("\p] : ");

		p = mTenantMemberDef[i].DrawData(p);
	}

	return p;
}
