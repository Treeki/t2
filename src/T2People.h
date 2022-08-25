#pragma once

#include "CLink.h"
#include "T2Matter.h"
#include "T2PeopleType.h"

#include <Quickdraw.h>

class LString;
class T2FloorInfo;
class T2GWorld;
class T2PeopleArrayList;
class T2PeopleDef;
class T2SilhouetteDef;
class T2TenantMemberDef;

class T2People : public CLink, public T2Matter {
public:
	T2People();
	void Initialize();
	~T2People();
	void SetUsed(Boolean value);
	void Initialize(T2PeopleDef *peopleDef, T2PeopleType *peopleType);
	Boolean IsMale() const;
	Boolean IsGeneral() const;
	Boolean IsSpecialColor() const;
	void ChangeStyle(Int32 style);
	Int16 GetWidth() const;
	Int32 GetRouteType() const;
	Boolean CalcWaitPersonArea(T2FloorInfo *floorInfo, Rect &rect);
	void CalcWalkingSilhouetteArea(Rect &rect) const;
	UInt16 GetCurTenantID() const;
	void ClearSpecialFlag(UInt8 flag);
	void SetSpecialFlag(UInt8 flag);
	UInt32 Idle(T2TowerDoc *doc);
	void IdleWaitMover(T2TowerDoc *doc);
	void MoveToTowerEntrance(T2TowerDoc *doc);
	void MoveToLobby(T2TowerDoc *doc);
	Boolean MoveToParking(T2TowerDoc *doc);
	Boolean MoveToSubway(T2TowerDoc *doc);
	Boolean MoveToShip(T2TowerDoc *doc);
	void MoveByEStair(T2TowerDoc *doc);
	void SolveNoRoute(T2TowerDoc *doc);
	Boolean FindRoute(T2TowerDoc *doc);
	void JumpToDestination(T2TowerDoc *doc);
	void GoOutTower(T2TowerDoc *doc);
	void IdleSearchedPerson(T2TowerDoc *doc);
	Boolean WalkSearchedPersonRight(T2TowerDoc *doc);
	Boolean WalkSearchedPersonLeft(T2TowerDoc *doc);
	Boolean IsReachDestination(Int32 var);
	Boolean IsRegistRequest(T2TowerDoc *doc);
	void ChangeStatus(Int16 status);
	void ChangeSilhouette();
	void SetSilhouette();
	void ChangeWalkStyle(Int8 walkStyle);
	RgnHandle GetSilhouetteRgnH(UInt32 a, UInt32 b);
	void SetAnimePattern(Int16 a, Int16 b, Int16 c, Int16 d);
	Boolean StopOnHisWay(T2TenantMemberDef *tmDef, Int32 l1, Int32 l2, Rect rect, Int16 s1, Int16 s2, UInt16 us1, UInt16 us2);
	Boolean CalledInTenant(T2TenantMemberDef *tmDef, Int32 l, Int16 s1, Int16 s2, UInt16 us1, UInt16 us2);
	Int16 CalcFreeTime(UInt16 var);
	Boolean IsGoToPool() const;
	void Return();
	void SetDestinationToOutOfTower(T2TowerDoc *doc);
	void ChangeDestination(UInt16 a, UInt16 b);
	Int16 CalcCurrEstimate() const;
	void IncEstimate(Int32 var);
	void UpdateEstimation();
	Int16 GetAverageStress() const;
	void IncStress(Int16 var);
	Boolean StressChanged();
	Boolean IsVIP() const;
	Boolean IsNamed() const;
	void SetColor(Int16 color);
	void ClearColor();
	void SetFavorite(Boolean value);
	Boolean VIPEstimation();
	Boolean SearchToilet(T2TowerDoc *doc);
	void DrawSearchedPerson(T2TowerDoc *doc);
	void Draw(T2TowerDoc *doc, const Rect &rect);
	void Draw(T2GWorld *w1, T2GWorld *w2, Int16 s);
	void DrawAt(T2GWorld *w1, T2GWorld *w2, Point pt);
	void Duplicate(T2TowerDoc *doc);
	void Remove(T2TowerDoc *inTowerDoc, UInt16 tenant);
	void TenantRemoved(UInt16 tenant);
	void Interview(T2TowerDoc *doc);
	Boolean GetInterviewWords(T2TowerDoc *doc, Str63 &str);
	Boolean IsMaru() const;
	Boolean IsReggae() const;
	void BreakoutEmergency(T2TowerDoc *doc);
	void LoadSelf(LStream &stream, T2TowerDoc *doc);
	void SaveSelf(LStream &stream);
	void ResolveLink(T2PeopleArrayList *list);
	void GetName(LString &str);

	UInt32 GetPeopleID() { return GetMatterID(); }
	T2PeopleType *GetPeopleType() const { return mPeopleType; }
	Int8 GetEconoType() const { return mPeopleType->GetEconoType(); }
	Boolean IsFatSilhouette() const { return (mAttribute & 2) != 0; }
	Boolean IsInTower() const {
		return (mStatus != 1) && (mStatus != 16) && (mStatus != 0);
	}
	Int16 GetColor() const { return mColor; }
	Boolean IsSetSpecialFlag(UInt8 flag) const { return (mSpecialFlag & flag) == flag; }
	void SetToSleep() { mFiller = -1; }
	Boolean IsSleep() const { return mFiller == -1; }
	Boolean IsWalk() const { return mWalk || IsSetSpecialFlag(0x20); }
	void SetWalk(Boolean v) { mWalk = v; }
	void SetFiller(Int16 v) { mFiller = v; }
	void SetStyle(Int32 v) { mStyle = v; }
	Int32 GetStyle() const { return mStyle; }
	void SetSilhouetteDef(Int32 index, T2SilhouetteDef *def) { mSilhouetteDef[index] = def; }
	void SetPeopleType(T2PeopleType *peopleType) {
		*mPeopleType = *peopleType;
	}
	void SetPrevTenantType(Int16 v) { mPrevTenantType = v; }
	Int16 GetPrevTenantType() const { return mPrevTenantType; }
	void InitStress() { mStress = 0; }
	Int16 GetStress() const { return mStress; }
	Int16 GetEstimate() const { return mEstimate; }

	Int8 GetAge() const {
		Int8 result = 0;
		if (mPeopleType)
			result = mPeopleType->GetAge();
		return result;
	}
	Int8 GetSex() const {
		Int8 result = 1;
		if (mPeopleType)
			result = mPeopleType->IsMale() == 0;
		return result;
	}

	UInt16 mAttribute;
	Int16 mColor;
	Int16 mFiller;
	Int16 mPrevTenantType;
	Boolean mWalk;
	UInt8 mSpecialFlag;
	Int16 mStress;
	UInt16 m54;
	Int16 mEstimate;
	T2PeopleType *mPeopleType;
	Int32 mStyle;
	T2SilhouetteDef *mSilhouetteDef[3];
};
