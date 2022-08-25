#pragma once

#include "T2EquipDef.h"

class T2People;
class T2PeopleAnimeDef;
class T2SubPlugin;
class T2Tenant;
class T2TenantMemberTableDef;
class T2TenantPlugin;

// TODO: DECOMPILE ALL OF ME!

class T2TenantDef : public T2EquipDef {
public:
	T2TenantDef(UInt32 id, LStream *stream, T2WorldDef *worldDef, T2TenantPlugin *tenantPlugin);
	void Init();
	T2PeopleAnimeDef *MakePeopleAnimeDef(ResIDT resID);
	~T2TenantDef();
	void CalcFloorOffRect(Rect &rect, Int16 a, Int16 b, Boolean flag) const;
	void GetName(LString &str);
	Boolean GetQTMovieName(T2Tenant *tenant, LString &str);
	void EnterTenant(T2TowerDoc *doc, T2Tenant *tenant, T2People *people);
	void LeaveTenant(T2TowerDoc *doc, T2Tenant *tenant, T2People *people);
	Int32 DrawData(Int32 pos);
	Int16 DrawAttribute(Int16 pos);
	Boolean HasSearchRangeProc() const;
	Boolean IsWithinSearchRange(const T2TowerDoc *doc, const T2Tenant *tenantA, const T2Tenant *tenantB) const;
	Int32 CalcPayment(T2TowerDoc *doc, Rect &rect, UInt32 index);
	void BuildStartProc(T2TowerDoc *doc, T2Tenant *tenant);
	void SetCustomerTable(T2SubPlugin *subPlugin);
	T2TenantMemberTableDef *MakeCustomerTableDef(Handle handle);
	float CalcNumOfCustomerUnit();
	Boolean IsTenant() { return true; }
	Boolean IsFloor() { return IsSetAttribute(0x2000); }
	Boolean IsValiableLength() { return IsSetAttribute(0x4000); }
	Boolean IsHome() { return IsSetAttribute(0x8000); }
	Boolean IsConcat() { return IsSetAttribute(0x20000); }
	Boolean IsPeopleAnime() { return IsSetAttribute(0x800000); }
	Int16 GetEntranceV() { return mEntranceV; }
	Int16 GetEntranceH() { return mEntranceH; }
	Int16 GetExitV() { return mExitV; }
	Int16 GetExitH() { return mExitH; }
	UInt8 GetNumOfPattern() const { return mNumOfPattern; }
	UInt8 GetNumOfKind() { return mNumOfKind; }
	Int16 GetBelongCapacity() const { return mBelongCapacity; }
	// GetRegistID?
	// GetDownFlag?
	Int16 GetSenseOfNoise() const { return mSenseOfNoise; }
	T2PeopleAnimeDef *GetPeopleAnimeDef() const { return mPeopleAnimeDef; }
	T2TenantMemberTableDef *GetEmployeeTableDef() const { return mEmployeeTableDef; }
	T2TenantMemberTableDef *GetCustomerTableDef() const { return mCustomerTableDef; }

	Int32 mMaxBuildType;
	Int16 mEntranceV;
	Int16 mEntranceH;
	Int16 mExitV;
	Int16 mExitH;
	Int16 mOpenTime;
	Int16 mCloseTime;
	Int16 mBindTime;
	Str63 mQTMovie;
	Int16 m6C6;
	Int16 m6C8;
	UInt8 m6CA;
	UInt8 m6CB;
	UInt8 mNumOfKind;
	UInt8 mNumOfPattern;
	Int16 mBelongCapacity;
	Int16 mSenseOfNoise;
	T2TenantMemberTableDef *mEmployeeTableDef;
	T2TenantMemberTableDef *mCustomerTableDef;
	T2PeopleAnimeDef *mPeopleAnimeDef;
};
