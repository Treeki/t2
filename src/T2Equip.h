#pragma once

#include "T2HaveOutViewObject.h"

class LString;
class T2CrossEquipArray;
class T2EquipDef;
class T2GetInfoDialog;
class T2RouteCEArray;

class T2Equip : public T2HaveOutViewObject {
public:
	T2Equip();
	~T2Equip();
	void InitEquip(T2EquipDef *def, const Rect &rect, UInt32 valiation);
	void SetUsed(Boolean value);
	Int32 DaysSinceBuilt(const T2TowerDoc *doc) const;
	Boolean HasMask() const;
	void SetEquipArea(const Rect &rect);
	Int32 GetOutMoney() const;
	Int32 GetInMoney() const;
	Int32 GetClickPart(T2TowerDoc *doc, Point pt, Int16 *s);
	void InsertCEID(Int16 a, Int16 b);
	void RemoveCEID(Int16 a);
	void ReplaceCEID(UInt16 a, UInt16 b);
	ResIDT GetInfoDialogID(T2TowerDoc *doc);
	void SetupDialog(T2GetInfoDialog *dialog);
	Boolean DialogOK(T2GetInfoDialog *dialog);
	Boolean DialogCancel(T2GetInfoDialog *dialog);
	void RememberDialog(T2GetInfoDialog *dialog);
	void LoadSelf(LStream &stream, T2TowerDoc *doc);
	void SaveSelf(LStream &stream);
	void ForgetDialog();

	virtual Boolean IsNeedDraw();
	virtual void GetTypicalName(LString &str) const;
	virtual void StartBuild(T2TowerDoc *doc) = 0;
	virtual Boolean IsBuildFinish() = 0;
	virtual Int32 DoDestruct(T2TowerDoc *doc, Int16 s, Point ptA, Point ptB, Rect &rect);

	UInt32 GetAttribute() const { return mAttribute; }
	Boolean IsSetAttribute(UInt32 a) { return (mAttribute & a) != 0; }
	Boolean IsMover() const { return IsSetAttribute(2); }
	Boolean IsNormalMenteCost() const { return IsSetAttribute(0x100); }
	UInt16 GetEquipID() const { return mEquipID; }
	void SetEquipDef(T2EquipDef *d) { T2HaveOutViewObject::SetToolDef(d); }
	void GetEquipArea(Rect &r) const { r = mEquipArea; }
	Int16 GetAreaWidth() const { return mEquipArea.right - mEquipArea.left; }
	Int16 GetAreaHeight() const { return mEquipArea.bottom - mEquipArea.top; }
	Int16 GetEquipType() const { return mEquipType; }
	Int16 GetCapacity() const { return mCapacity; }
	Int16 GetInMoneyIndex() const { return mInMoneyIndex; }
	Int32 GetBuildDay() const { return mBuildDay; }
	virtual void SetDrawMode(Int16 drawMode) {
		if (mDrawMode != drawMode)
			mDrawMode = drawMode;
	}
	virtual void ClearDrawMode();
	Int16 GetDrawMode() const { return mDrawMode; }
	T2CrossEquipArray *GetCEArray() const { return mCEArray; }
	T2EquipDef *GetEquipDef() const { return (T2EquipDef *) mToolDef; }
	void SetInMoneyIndex(Int16 v) { mInMoneyIndex = v; }
	Byte GetPatIndex() const { return mPatIndex; }
	void SetPatIndex(Byte v) { mPatIndex = v; }

	UInt16 mEquipID;
	Rect mEquipArea;
	Int16 mEquipType;
	Int16 mDrawMode;
	Byte mPatIndex;
	Int16 mCapacity;
	Int16 m2A;
	Int16 m2C;
	Int32 mBuildDay;
	UInt32 mAttribute;
	T2RouteCEArray *mCEArray;
	T2GetInfoDialog *mDialog;
	Int16 mInMoneyIndex;
};
