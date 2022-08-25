#include "T2GWorld.h"
#include "T2PaletteAnime.h"
#include "T2People.h"
#include "T2PeopleArrayList.h"
#include "T2PeopleDef.h"
#include "T2Request.h"
#include "T2ReturnStack.h"
#include "T2SilhouetteDef.h"
#include "T2TemplatePluginList.h"
#include "T2TenantMemberDef.h"
#include "T2TowerDoc.h"
#include "T2WordDefArray.h"
#include "URect.h"
#include "UT2Coordinate.h"
#include "UT2Utils.h"

#include <LStream.h>
#include <LString.h>
#include <UDrawingState.h>
#include <UException.h>

T2People::T2People() {
	Initialize();
	try {
		mPeopleType = new T2PeopleType;
		#line 62
		ThrowIfNil_(mPeopleType);
	} catch (ExceptionCode code) {
		delete this;
		#line 67
		Throw_(code);
	}
}

void T2People::Initialize() {
	mSpecialFlag = 0;
	mWalk = false;
	mAttribute = 0;
	mStress = 0;
	m54 = 0;
	mEstimate = 0;
	mStatus = 0;
	mColor = 1;
	mFiller = 0;
	mPrevTenantType = 0;
	mPeopleType = 0;
	mStyle = 0;
	for (UInt32 i = 0; i < 3; i++) {
		mSilhouetteDef[i] = 0;
	}
}

T2People::~T2People() {
	if (mPeopleType)
		delete mPeopleType;
}

void T2People::SetUsed(Boolean value) {
	if (!value) {
		if (IsFavorite()) {
			#line 137
			Assert_(T2TowerDoc::GetCurrentT2TowerDoc() != 0);
			Assert_(T2TowerDoc::GetCurrentT2TowerDoc()->mNameDB != 0);
			T2TowerDoc::GetCurrentT2TowerDoc()->RemoveFavoritePeople(this, true);
		} else if (IsNamed()) {
			#line 143
			Assert_(T2TowerDoc::GetCurrentT2TowerDoc() != 0);
			Assert_(T2TowerDoc::GetCurrentT2TowerDoc()->mNameDB != 0);
			// TODO: T2NameList
		}
	}

	T2Matter::SetUsed(value);
}

void T2People::Initialize(T2PeopleDef *peopleDef, T2PeopleType *peopleType) {
	T2Matter::Initialize(peopleDef);

	mSpecialFlag = 0;
	mAttribute = peopleDef->GetAttribute();
	mStress = 0;
	m54 = 0;
	mEstimate = 300;
	mStatus = 0;
	mColor = 1;
	mFiller = 0;
	mPrevTenantType = 0;
	*mPeopleType = *peopleType;
	mStyle = 0;
	SetSilhouetteDef(0, peopleDef->GetSilhouetteDef());
	SetSilhouetteDef(1, 0);
	SetSilhouetteDef(2, 0);
}

Boolean T2People::IsMale() const {
	Boolean result = true;
	if (mPeopleType)
		result = mPeopleType->IsMale();
	return result;
}

Boolean T2People::IsGeneral() const {
	return (mHomeTenant == 1 || mHomeTenant == 2) && (mWorkTenant == 1 || mWorkTenant == 2);
}

Boolean T2People::IsSpecialColor() const {
	return mColor >= 11;
}

void T2People::ChangeStyle(Int32 style) {
	if (style != mStyle && style >= 0 && style <= 2) {
		mStyle = style;
		ChangeSilhouette();
	}
}

Int16 T2People::GetWidth() const {
	Int32 result = 1;
	T2SilhouetteDef *silhouetteDef = mSilhouetteDef[mStyle];
	if (silhouetteDef)
		result = silhouetteDef->GetWidth();
	return result;
}

Int32 T2People::GetRouteType() const {
	Int32 result = 0;

	if (!IsSetSpecialFlag(0x80)) {
		T2SilhouetteDef *silhouetteDef = mSilhouetteDef[mStyle];
		if (silhouetteDef)
			result = silhouetteDef->GetRouteType();
	} else {
		result = -1;
	}

	return result;
}

Boolean T2People::CalcWaitPersonArea(T2FloorInfo *floorInfo, Rect &rect) {
	// TODO: T2FloorInfo, T2Request
}

void T2People::CalcWalkingSilhouetteArea(Rect &rect) const {
	Point pt = GetCurPosition();
	rect.top = pt.v;
	rect.left = pt.h;
	rect.bottom = pt.v + 1;
	rect.right = pt.h + 2;

	if (mWalkStyle == 0 && GetWidth() < 2) {
		if (mDirection == 0)
			rect.left++;
		else
			rect.right--;
	}
}

UInt16 T2People::GetCurTenantID() const {
	UInt16 result = 0;
	if (mStatus == 11)
		result = mCurrEquipID;
	return result;
}

void T2People::ClearSpecialFlag(UInt8 flag) {
	mSpecialFlag &= ~flag;
	if ((flag & 4) > 0)
		ClearColor();
}

void T2People::SetSpecialFlag(UInt8 flag) {
	mSpecialFlag |= flag;
	if ((flag & 4) > 0)
		mColor = 17;
}

UInt32 T2People::Idle(T2TowerDoc *doc) {
	switch (mStatus) {
		// TODO
	}
}

void T2People::IdleWaitMover(T2TowerDoc *doc) {
	// TODO T2FloorInfo, etc
}

void T2People::MoveToTowerEntrance(T2TowerDoc *doc) {
	Boolean flag = true;
	switch (mPeopleType->GetTransportType()) {
		case 0:
		case 1:
			MoveToLobby(doc);
			break;
		case 2:
			flag = MoveToParking(doc);
			break;
		case 3:
			flag = MoveToSubway(doc);
			break;
		case 4:
			flag = MoveToShip(doc);
			break;
		case 5:
			break;
	}

	if (!flag) {
		IncEstimate(-100);
		MoveToLobby(doc);
	}
}

void T2People::MoveToLobby(T2TowerDoc *doc) {
	// TODO: T2FloorInfo, T2Tenant
}

Boolean T2People::MoveToParking(T2TowerDoc *doc) {
	// TODO: T2RegistedTenantDB, T2Tenant
}

Boolean T2People::MoveToSubway(T2TowerDoc *doc) {
	// TODO: T2TowerEvent, T2MetroRailway, T2Transport
}

Boolean T2People::MoveToShip(T2TowerDoc *doc) {
	// TODO: T2TowerEvent, T2Transport
}

void T2People::MoveByEStair(T2TowerDoc *doc) {
	// TODO: T2FloorInfo, T2Tenant
}

void T2People::SolveNoRoute(T2TowerDoc *doc) {
	// TODO: T2FloorInfo
}

Boolean T2People::FindRoute(T2TowerDoc *doc) {
	// TODO: T2FloorInfo
}

void T2People::JumpToDestination(T2TowerDoc *doc) {
	// TODO: T2FloorInfo
}

void T2People::GoOutTower(T2TowerDoc *doc) {
	// TODO: T2FloorInfo, T2Pool
}

void T2People::IdleSearchedPerson(T2TowerDoc *doc) {
	// TODO: T2FloorInfo, T2Tenant
}

Boolean T2People::WalkSearchedPersonRight(T2TowerDoc *doc) {
	// TODO: T2FloorInfo
}

Boolean T2People::WalkSearchedPersonLeft(T2TowerDoc *doc) {
	// TODO: T2FloorInfo
}

Boolean T2People::IsReachDestination(Int32 var) {
	Boolean result = false;
	Int16 theWalkWidth = 16;

	if (mDirection != 1) {
		if ((mCurPosition.h + theWalkWidth) >= mCurrDestPos.h) {
			theWalkWidth = mCurrDestPos.h - mCurPosition.h;
			result = true;
		}
		mCurPosition.h += theWalkWidth;
	} else {
		if ((mCurPosition.h - theWalkWidth) <= mCurrDestPos.h) {
			theWalkWidth = mCurPosition.h - mCurrDestPos.h;
			result = true;
		}
		mCurPosition.h -= theWalkWidth;
	}

	#line 1212
	Assert_(theWalkWidth >= 0);

	if (mCurPosition.v != var)
		IncStress(theWalkWidth / 4);

	return result;
}

Boolean T2People::IsRegistRequest(T2TowerDoc *doc) {
	// TODO: T2FloorInfo, T2Request
}

void T2People::ChangeStatus(Int16 status) {
	SetStatus(status);
	ChangeSilhouette();
}

void T2People::ChangeSilhouette() {
	switch (mStatus) {
		case 7:
			mWalkStyle = 1;
			break;
		case 9:
			mWalkStyle = 2;
			break;
		default:
			mWalkStyle = 0;
			break;
	}

	SetSilhouette();
}

void T2People::SetSilhouette() {
	T2SilhouetteDef *silhouetteDef = mSilhouetteDef[mStyle];
	if (silhouetteDef) {
		mRgn = silhouetteDef->GetSilhouette((mDirection != -1) ? mDirection : 0, mWalkStyle);
	} else {
		mRgn = 0;
	}
}

void T2People::ChangeWalkStyle(Int8 walkStyle) {
	mWalkStyle = walkStyle;
	SetSilhouette();
}

RgnHandle T2People::GetSilhouetteRgnH(UInt32 a, UInt32 b) {
	RgnHandle result = 0;
	T2SilhouetteDef *silhouetteDef = mSilhouetteDef[mStyle];
	if (silhouetteDef)
		result = silhouetteDef->GetSilhouette(a, b);
	return result;
}

void T2People::SetAnimePattern(Int16 a, Int16 b, Int16 c, Int16 d) {
	if (b > 1)
		mFiller = a + UT2Utils::Randomize(b);
	else
		mFiller = a;

	if (d > 1)
		mCurPosition.h = c + UT2Utils::Randomize(d);
	else
		mCurPosition.h = c;
}

Boolean T2People::StopOnHisWay(T2TenantMemberDef *tmDef, Int32 l1, Int32 l2, Rect rect, Int16 s1, Int16 s2, UInt16 us1, UInt16 us2) {
	Boolean result = false;
	Boolean anotherFlag = false;
	if (l2 < 0) {
		l2 *= -1;
		anotherFlag = true;
	}

	if (mCurPosition.h > (rect.left - l2) && mCurPosition.h < (rect.right + l2)) {
		if (anotherFlag || CalcFreeTime(us2) > s1) {
			if (mPrevTenantType != s2) {
				#line 1421
				Assert_(mPeopleType != 0);
				if (mPeopleType->CheckWithDemand(tmDef, l1) && SetDestinationToReturn()) {
					SetDestination(us1, us2);
					ChangeStatus(3);
					result = true;
				}
			}
		}
	}

	return result;
}

Boolean T2People::CalledInTenant(T2TenantMemberDef *tmDef, Int32 l, Int16 s1, Int16 s2, UInt16 us1, UInt16 us2) {
	Boolean result = false;

	if (CalcFreeTime(us2) > s1 && mPrevTenantType != s2) {
		#line 1463
		Assert_(mPeopleType != 0);
		if (mPeopleType->CheckWithDemand(tmDef, l)) {
			SetDestination(us1, us2);
			result = true;
		}
	}

	return result;
}

Int16 T2People::CalcFreeTime(UInt16 var) {
	Int16 result = 0;

	if (IsSetDestination()) {
		if (mStartTime > var)
			result = mStartTime - var;
	} else if (IsSetReturn()) {
		if (GetReturnTime() > var)
			result = GetReturnTime() - var;
	} else {
		result = 10000;
	}

	return result;
}

Boolean T2People::IsGoToPool() const {
	return (mDstTenant <= 2) && (mDstTenant >= 1);
}

void T2People::Return() {
	if (!SetReturnToDestination())
		SetDestination(mHomeTenant, 0);
	if (mStatus == 10)
		ChangeStatus(3);
}

void T2People::SetDestinationToOutOfTower(T2TowerDoc *doc) {
	// TODO: T2RegistedTenantDB
}

void T2People::ChangeDestination(UInt16 a, UInt16 b) {
	if (mStatus == 10 || mStatus == 12)
		ChangeStatus(3);
	SetDestination(a, b);
}

Int16 T2People::CalcCurrEstimate() const {
	Int16 result;

	if (m54) {
		if (mStatus != 11 && mStatus != 1)
			result = ((300 - mStress) + (mEstimate * m54)) / (m54 + 1);
		else
			result = ((mEstimate * m54) - mStress) / m54;
	} else {
		result = mEstimate - mStress;
	}

	if (result < 1)
		result = 1;
	return result;
}

void T2People::IncEstimate(Int32 var) {
	mEstimate += var;

	if (mEstimate < 1)
		mEstimate = 1;
	else if (mEstimate > 300)
		mEstimate = 300;
}

void T2People::UpdateEstimation() {
	mEstimate = CalcCurrEstimate();
	mStress = 0;

	if (mStatus != 11 && (int) m54 < 4)
		m54++;

	StressChanged();
}

Int16 T2People::GetAverageStress() const {
	return 300 - CalcCurrEstimate();
}

void T2People::IncStress(Int16 var) {
	mStress += var;
	if (mStress > 300)
		mStress = 300;
	else if (mStress < 0)
		mStress = 0;

	StressChanged();
}

Boolean T2People::StressChanged() {
	Boolean result = false;

	if (!IsSpecialColor()) {
		T2PeopleDef *peopleDef = (T2PeopleDef *) GetMatterDef();
		if (!peopleDef)
			return false;

		Int16 clr;
		if (mStress < peopleDef->GetStressBlueLimit())
			clr = 1;
		else if (mStress < peopleDef->GetStressYellowLimit())
			clr = 7;
		else if (mStress < peopleDef->GetStressMax() - 10)
			clr = 9;
		else
			clr = 9;

		if (mColor != clr) {
			mColor = clr;
			result = true;
		}
	}

	return result;
}

Boolean T2People::IsVIP() const {
	return mColor == 14;
}

Boolean T2People::IsNamed() const {
	return mColor == 13;
}

void T2People::SetColor(Int16 color) {
	if (color > mColor)
		mColor = color;
}

void T2People::ClearColor() {
	if (mColor < 11) {
		mColor = 1;
	} else if (!IsVIP()) {
		if (IsSetSpecialFlag(0x60))
			mColor = 11;
		else
			mColor = 1;

		if (IsFavorite())
			mColor = (mColor > 14) ? mColor : 14;

		if (IsSetSpecialFlag(4))
			mColor = (mColor > 17) ? mColor : 17;

		if (mColor == 1)
			StressChanged();
	}
}

void T2People::SetFavorite(Boolean value) {
	T2Object::SetFavorite(value);

	if (value)
		SetColor(13);
	else
		ClearColor();
}

Boolean T2People::VIPEstimation() {
	Boolean result = false;

	if (IsVIP())
		result = CalcCurrEstimate() > 200;

	return result;
}

Boolean T2People::SearchToilet(T2TowerDoc *doc) {
	// TODO: T2RegistedTenantDB
}

void T2People::DrawSearchedPerson(T2TowerDoc *doc) {
	switch (mStatus) {
		case 3:
		case 4:
		case 5:
		case 10:
		case 12:
		case 13:
		case 14:
		case 15:
			StColorState state;
			Rect rect;
			rect.top = mCurPosition.v;
			rect.left = mCurPosition.h;
			Draw(doc, rect);
			break;
	}
}

void T2People::Draw(T2TowerDoc *doc, const Rect &rect) {
	T2PaletteAnime *paletteAnime = doc->GetPaletteAnime();
	if (paletteAnime)
		paletteAnime->ForeColor(mColor);

	Int32 zoomLevel = doc->GetZoomLevel();
	if (zoomLevel > 0) {
		static const Rect nullRect = { 0, 0, 0, 0 };
		Rect r = nullRect;
		r.top = rect.top;
		r.left = rect.left;
		r.bottom = rect.top + 1;
		r.right = rect.left + 2;
		if (mDirection == 0)
			r.left += 1;
		else if (mDirection == 1)
			r.right -= 1;
		UT2Coordinate::UnitToQD(r, zoomLevel, 0);
		r.top += (Int16) (r.bottom - r.top) >> 2;
		r.left += (Int16) (r.right - r.left) >> 2;
		::PaintRect(&r);
	} else if (mRgn) {
		Int32 v = rect.top;
		Int32 h = rect.left;
		UT2Coordinate::UnitToQD(v, h, 0);
		::OffsetRgn(mRgn, h, v);
		::PaintRgn(mRgn);
		::OffsetRgn(mRgn, -h, -v);
	}
}

void T2People::Draw(T2GWorld *w1, T2GWorld *w2, Int16 s) {
	if (mFiller != -1) {
		Rect srcRect, dstRect;
		Rect dstUnit, srcUnit;

		::SetRect(&srcUnit, 0, 0, 2, 1);
		dstUnit = srcUnit;

		UT2Coordinate::UnitToOffRect(srcUnit, srcRect, mFiller, false);
		::OffsetRect(&dstUnit, mCurPosition.h, mCurPosition.v);
		UT2Coordinate::UnitToQD(dstUnit, dstRect, s, 0);
		w1->CopyOffImage(w2, srcRect, dstRect, 36);
	}
}

void T2People::DrawAt(T2GWorld *w1, T2GWorld *w2, Point pt) {
	if (mFiller >= 0) {
		Rect srcRect, dstRect;
		Rect dstUnit, srcUnit;

		::SetRect(&srcUnit, 0, 0, 2, 1);
		dstUnit = srcUnit;

		UT2Coordinate::UnitToOffRect(srcUnit, srcRect, mFiller, false);
		::OffsetRect(&dstUnit, mCurPosition.h - pt.h, mCurPosition.v - pt.v);
		UT2Coordinate::UnitToQD(dstUnit, dstRect, 0, 0);
		::OffsetRect(&dstRect, 0, -8);
		w1->CopyOffImage(w2, srcRect, dstRect, 36);
	}
}

void T2People::Duplicate(T2TowerDoc *inTowerDoc) {
	#line 2072
	Assert_(inTowerDoc != 0);
	// TODO: T2Pool
}

void T2People::Remove(T2TowerDoc *inTowerDoc, UInt16 tenant) {
	Boolean flag = false;
	if (mHomeTenant == tenant) {
		mHomeTenant = 1;
		flag = true;
	}
	if (mWorkTenant == tenant) {
		mWorkTenant = 1;
		flag = true;
	}

	if (flag && IsGeneral() && mStatus == 1) {
		#line 2113
		Assert_(inTowerDoc != 0);
		// TODO: T2Pool
	}
}

void T2People::TenantRemoved(UInt16 tenant) {
	if (RemoveReturn(tenant))
		IncEstimate(-200);

	if (tenant == GetDestination()) {
		Return();
		IncEstimate(-100);
	}
}

void T2People::Interview(T2TowerDoc *doc) {
	// TODO: T2FloorInfo
}

Boolean T2People::GetInterviewWords(T2TowerDoc *doc, Str63 &str) {
	// TODO: T2FloorInfo, T2Tenant
}

Boolean T2People::IsMaru() const {
	return (mMatterDef && mMatterDef->mMatterType == 4);
}

Boolean T2People::IsReggae() const {
	return (mMatterDef && mMatterDef->mMatterType == 5);
}

void T2People::BreakoutEmergency(T2TowerDoc *inTowerDoc) {
	#line 2334
	Assert_(mReturnStack != 0);

	mReturnStack->Init();
	switch (mStatus) {
		case 5:
		case 10:
			ChangeStatus(3);
		case 2:
		case 3:
		case 4:
		case 8:
			SetSpecialFlag(0x80);
			SetDestination(1, 0);
			break;
		case 1:
			if (IsGeneral()) {
				#line 2356
				Assert_(inTowerDoc->GetPool() != 0);
				// TODO: T2Pool
			}
			break;
	}
}

void T2People::LoadSelf(LStream &stream, T2TowerDoc *doc) {
	UInt32 trash;
	stream >> trash;

	T2Matter::LoadSelf(stream, doc);
	if (IsUsed()) {
		stream >> mSpecialFlag;
		stream >> mWalk;
		stream >> mStress;
		stream >> m54;
		stream >> mEstimate;
		stream >> mColor;
		stream >> mFiller;
		stream >> mPrevTenantType;
		stream >> mStyle;

		FourCharCode code;
		stream >> code;
		if (code == 'PTYP') {
			mPeopleType->Read(stream);
			mMatterDef = doc->mPPTemplates->FindPeopleDef(mPeopleType->GetSilhouetteType());
			#line 2399
			ThrowIfNil_(mMatterDef);
			mAttribute = mMatterDef->GetAttribute();
		}

		for (UInt32 i = 0; i < 3; i++) {
			Int16 id;
			stream >> id;
			if (id)
				mSilhouetteDef[i] = doc->mSITemplates->FindSilhouette(id);
			else
				mSilhouetteDef[i] = 0;
		}

		UInt32 trash2;
		stream >> trash2;

		UInt32 link;
		stream >> link;
		if (link)
			mNext = (CLink *) link;
		stream >> link;
		if (link)
			mPrev = (CLink *) link;

		ChangeSilhouette();
	}
}

void T2People::SaveSelf(LStream &stream) {
	FourCharCode code = '<PP>';
	stream << code;

	T2Matter::SaveSelf(stream);

	if (IsUsed()) {
		stream << mSpecialFlag;
		stream << mWalk;
		stream << mStress;
		stream << m54;
		stream << mEstimate;
		stream << mColor;
		stream << mFiller;
		stream << mPrevTenantType;
		stream << mStyle;

		T2People *p;
		FourCharCode ptCode = mPeopleType ? 'PTYP' : 'xPTP';
		stream << ptCode;
		if (ptCode == 'PTYP')
			mPeopleType->Write(stream);

		for (UInt32 i = 0; i < 3; i++) {
			Int16 id = 0;
			if (mSilhouetteDef[i])
				id = mSilhouetteDef[i]->GetSilhouetteType();
			stream << id;
		}

		FourCharCode code2 = 'pLk>';
		stream << code2;
		UInt32 nullID = 0;
		if (mNext) {
			p = (T2People *) mNext;
			stream << p->GetPeopleID();
		} else {
			stream << nullID;
		}
		if (mPrev) {
			p = (T2People *) mPrev;
			stream << p->GetPeopleID();
		} else {
			stream << nullID;
		}
	}
}

void T2People::ResolveLink(T2PeopleArrayList *list) {
	if (mNext != 0) {
		T2People *p = list->FindPeople((UInt32) mNext);
		mNext = p;
	}
	if (mPrev != 0) {
		T2People *p = list->FindPeople((UInt32) mPrev);
		mPrev = p;
	}
}

void T2People::GetName(LString &str) {
	mSilhouetteDef[mStyle]->GetName(str);
}
