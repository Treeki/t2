#include "T2DateTime.h"
#include "T2Equip.h"
#include "T2EquipDef.h"
#include "T2RouteCEArray.h"
#include "T2TowerDoc.h"

#include <LStream.h>

T2Equip::T2Equip() {
	mEquipID = 0;
	::SetRect(&mEquipArea, 0, 0, 0, 0);
	mEquipType = 0;
	mDrawMode = 0;
	mPatIndex = 0;
	mCapacity = 0;
	m2A = 0;
	mInMoneyIndex = 0;
	m2C = 0;
	mBuildDay = 0;
	mAttribute = 0;
	mCEArray = 0;
	mDialog = 0;
}

T2Equip::~T2Equip() {
	if (mCEArray)
		delete mCEArray;
	//if (mDialog)
	//	delete mDialog;
}

void T2Equip::InitEquip(T2EquipDef *def, const Rect &rect, UInt32 valiation) {
	if (def) {
		mEquipType = def->GetEquipType();
		mCapacity = def->GetCapacity();
		mAttribute = def->GetAttribute();
		mToolDef = def;
	}

	mValiation = valiation;
	mEquipArea = rect;
	mDrawMode = 0;
	m2A = 0;
	m2C = 0;
	mPatIndex = 0;

	T2TowerDoc *doc = T2TowerDoc::GetCurrentT2TowerDoc();
	if (doc) {
		mBuildDay = doc->someDateTime->CalcTotalDays();
	} else {
		mBuildDay = 0;
	}

	mInMoneyIndex = (GetEquipDef()->GetNumOfInMoney() > 1) ? (GetEquipDef()->GetNumOfInMoney() / 2) : 0;
	SetUsed(true);
}

void T2Equip::GetTypicalName(LString &str) const {
	T2EquipDef *def = GetEquipDef();
	if (def)
		def->GetName(str, GetValiation());
	else
		str = "\p";
}

void T2Equip::SetUsed(Boolean value) {
	if (!value && mCEArray) {
		delete mCEArray;
		mCEArray = 0;
	}
	T2HaveOutViewObject::SetUsed(value);
}

Int32 T2Equip::DaysSinceBuilt(const T2TowerDoc *doc) const {
	return doc->someDateTime->CalcLapseDays(mBuildDay);
}

Boolean T2Equip::HasMask() const {
	Boolean result = false;

	if (mToolDef && GetEquipDef()->GetMask(GetValiation()) != 0)
		result = true;

	return result;
}

void T2Equip::SetEquipArea(const Rect &rect) {
	mEquipArea = rect;
}

Int32 T2Equip::GetOutMoney() const {
	Int32 result = 0;
	if (mToolDef)
		result = GetEquipDef()->GetOutMoney(0);
	return result;
}

Int32 T2Equip::GetInMoney() const {
	Int32 result = 0;
	if (mToolDef)
		result = GetEquipDef()->GetInMoney(mInMoneyIndex);
	return result;
}

Int32 T2Equip::GetClickPart(T2TowerDoc *doc, Point pt, Int16 *s) {
	Int32 result = 0;
	if (mToolDef)
		result = GetEquipDef()->GetClickPartProc(doc, this, pt, s);
	return result;
}

Int32 T2Equip::DoDestruct(T2TowerDoc *, Int16, Point, Point, Rect &) {
	if (mCEArray) {
		delete mCEArray;
		mCEArray = 0;
	}
	return 0;
}

void T2Equip::InsertCEID(Int16 a, Int16 b) {
	if (mCEArray) {
		mCEArray->Insert(a, b);
	}
}

void T2Equip::RemoveCEID(Int16 a) {
	if (mCEArray) {
		mCEArray->Remove(&a);
	}
}

void T2Equip::ReplaceCEID(UInt16 a, UInt16 b) {
	if (mCEArray) {
		mCEArray->ReplaceID(a, b);
	}
}

ResIDT T2Equip::GetInfoDialogID(T2TowerDoc *doc) {
	return mToolDef ? GetEquipDef()->GetInfoDialogIDProc(doc, this) : 0;
}

void T2Equip::SetupDialog(T2GetInfoDialog *dialog) {
	if (mToolDef) {
		// TODO T2GetInfoDialog
	}
}

Boolean T2Equip::DialogOK(T2GetInfoDialog *dialog) {
	Boolean result = false;

	if (mToolDef) {
		// TODO T2GetInfoDialog
	}

	return result;
}

Boolean T2Equip::DialogCancel(T2GetInfoDialog *dialog) {
	Boolean result = false;

	if (mToolDef) {
		// TODO T2GetInfoDialog
	}

	return result;
}

void T2Equip::RememberDialog(T2GetInfoDialog *dialog) {
	mDialog = dialog;
}

void T2Equip::LoadSelf(LStream &stream, T2TowerDoc *doc) {
	T2Object::LoadSelf(stream, doc);
	if (IsUsed()) {
		stream >> mEquipID;
		stream >> mEquipArea;
		stream >> mEquipType;
		stream >> mDrawMode;
		stream >> mPatIndex;
		stream >> m2A;
		stream >> mInMoneyIndex;
		stream >> m2C;
		stream >> mBuildDay;
		mCEArray = (T2RouteCEArray *) T2CrossEquipArray::ReadCEArray(stream);
		stream >> mValiation;
	}
}

void T2Equip::SaveSelf(LStream &stream) {
	T2Object::SaveSelf(stream);
	if (IsUsed()) {
		stream << mEquipID;
		stream << mEquipArea;
		stream << mEquipType;
		stream << mDrawMode;
		stream << mPatIndex;
		stream << m2A;
		stream << mInMoneyIndex;
		stream << m2C;
		stream << mBuildDay;
		T2CrossEquipArray::WriteCEArray(mCEArray, stream);
		stream << mValiation;
	}
}

Boolean T2Equip::IsNeedDraw() {
	return true;
}

void T2Equip::ClearDrawMode() {
	mDrawMode = 0;
}

void T2Equip::ForgetDialog() {
	mDialog = 0;
}
