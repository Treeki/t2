#include "T2DateTime.h"
#include "T2GWorld.h"
#include "T2ToolDef.h"
#include "T2ToolPlugin.h"
#include "T2WorldDef.h"
#include "UDebugUtils.h"

#include <LStream.h>
#include <UException.h>

T2ToolDef::T2ToolDef(UInt32 id, LStream *stream, T2WorldDef *worldDef, CProgramPlugin *programPlugin)
	: T2TemplatePlugin(id, stream, programPlugin)
{
	Initialize();

	(*stream) >> mToolType;
	(*stream) >> mWidth;
	(*stream) >> mHeight;
	(*stream) >> mLevel;
	(*stream) >> mAttribute;
	for (UInt8 i = 0; i < 64; i++) {
		Byte b;
		(*stream) >> b;
		mCategoryCommentString[i] = b;
	}
	for (UInt8 i = 0; i < 64; i++) {
		Byte b;
		(*stream) >> b;
		mCategoryName[i] = b;
	}
	(*stream) >> mCategoryNo;
	(*stream) >> mToolNo;
	(*stream) >> mAfterCategoryNo;
	(*stream) >> mAfterToolNo;
	(*stream) >> mSubPluginType;

	ResIDT id1;
	(*stream) >> id1;
	if (id1 != 0)
		mCategoryIcon = new T2GWorld(id1, 8, worldDef->mCTabH, 0, 0);

	(*stream) >> mCategoryHelpResID;
	(*stream) >> mValiationCount;
	#line 67
	Assert_(mValiationCount <= kMaxValiation);

	for (Int16 i = 0; i < mValiationCount; i++) {
		Byte j;
		for (j = 0; j < 64; j++) {
			Byte b;
			(*stream) >> b;
			mPriceString[i][j] = b;
		}
		for (j = 0; j < 64; j++) {
			Byte b;
			(*stream) >> b;
			mOutMoneyString[i][j] = b;
		}
		for (j = 0; j < 64; j++) {
			Byte b;
			(*stream) >> b;
			mCommentString[i][j] = b;
		}
		for (j = 0; j < 64; j++) {
			Byte b;
			(*stream) >> b;
			mToolName[i][j] = b;
		}
		for (j = 0; j < 64; j++) {
			Byte b;
			(*stream) >> b;
			mName[i][j] = b;
		}

		(*stream) >> mPrice[i];
		(*stream) >> mOutMoney[i];
		ResIDT id2;
		(*stream) >> id2;
		(*stream) >> mOffscreenResIDs[i];

		if (IsSetAttribute(0x2000) && i == 1 && mOffscreenResIDs[i] > 0) {
			mOffscreenResIDs[i] += worldDef->m15C - 1;
		}

		if (id2 != 0) {
			mB4 += 1;
			Rect rect = { 0, 0, 52, 26 };
			mToolIcon[i] = new T2GWorld(rect, 8, worldDef->mCTabH, 0, 0);
			if (mToolIcon[i]->BeginDrawing()) {
				Handle pic = ::Get1Resource('PICT', id2);
				if (pic) {
					::DrawPicture((PicHandle) pic, &rect);
					::ReleaseResource(pic);
				}
				mToolIcon[i]->EndDrawing();
			}
		}

		if (mOffscreenResIDs[i] != 0) {
			mOffscreen[i] = new T2GWorld(mOffscreenResIDs[i], 8, worldDef->mCTabH, 0, 0);
			mOffscreenExists[i] = true;
		}

		(*stream) >> mToolHelpResID[i];
		(*stream) >> mConsumptionPower[i];
	}

	mToolQuietUntil = 0;
	mCategoryQuietUntil = 0;
}

void T2ToolDef::Initialize() {
	mCategoryIcon = 0;
	mB4 = 0;
	m608 = 0;
	m618 = 0;
	for (UInt32 i = 0; i < kMaxValiation; i++) {
		mToolIcon[i] = 0;
		mOffscreen[i] = 0;
		mOffscreenExists[i] = false;
	}
}

T2ToolDef::~T2ToolDef() {
	if (mCategoryIcon)
		delete mCategoryIcon;

	for (Int16 i = 0; i < mValiationCount; i++) {
		if (mToolIcon[i])
			delete mToolIcon[i];
		if (mOffscreen[i])
			delete mOffscreen[i];
	}

	if (mToolQuietUntil)
		delete mToolQuietUntil;
}

Int32 T2ToolDef::GetSortKey() {
	Int32 result = mCategoryNo * 0x10000;
	result += mToolNo;
	return result;
}

void T2ToolDef::GetCategoryName(LStr255 &str) {
	str = LStr255(mCategoryName);
}

void T2ToolDef::GetToolName(LString &str, Int16 index) {
	str = LStr255(mToolName[index]);
}

void T2ToolDef::GetName(LString &str, Int16 index) {
	str = LStr255(mName[index]);
}

Int32 T2ToolDef::GetOutMoney(UInt32 index) const {
	Int32 result = 0;
	if (index < kMaxValiation)
		result = mOutMoney[index];
	return result;
}

void T2ToolDef::_SetOutMoney(UInt32 index, Int32 money) {
	if (index < kMaxValiation)
		mOutMoney[index] = money;
}

T2GWorld *T2ToolDef::GetOffscreen(UInt32 index) const {
	T2GWorld *result = 0;
	if (mOffscreenExists[index])
		result = mOffscreen[index];
	return result;
}

T2GWorld *T2ToolDef::GetCategoryHelpGWorld(T2WorldDef *worldDef) {
	return new T2GWorld(mCategoryHelpResID, 8, worldDef->mCTabH, 0, 0);
}

T2GWorld *T2ToolDef::GetToolHelpGWorld(T2WorldDef *worldDef, Int16 index) {
	return new T2GWorld(mToolHelpResID[index], 8, worldDef->mCTabH, 0, 0);
}

void T2ToolDef::DefIdleProc(T2TowerDoc *towerDoc) {
	if (mProgramPlugin)
		((T2ToolPlugin *) mProgramPlugin)->DefIdleProc(towerDoc);
}

void T2ToolDef::DrawProc(T2HaveOutViewObject *haveOutViewObject, const Rect &rect, T2TowerDoc *towerDoc) {
	if (mProgramPlugin)
		((T2ToolPlugin *) mProgramPlugin)->DrawProc(haveOutViewObject, rect, towerDoc);
}

Int32 T2ToolDef::IdleProc(T2HaveOutViewObject *haveOutViewObject, T2TowerDoc *towerDoc) {
	Int32 result = -1;

	if (mProgramPlugin)
		result = ((T2ToolPlugin *) mProgramPlugin)->IdleProc(towerDoc, haveOutViewObject);

	return result;
}

Boolean T2ToolDef::ClickProc(T2TowerDoc *towerDoc, Int16 &var, Point pt, Rect *rect, Boolean flag) {
	if (mProgramPlugin)
		return ((T2ToolPlugin *) mProgramPlugin)->ClickProc(towerDoc, var, pt, rect, flag);
	else
		return 0;
}

Int32 T2ToolDef::AreaCheck(T2TowerDoc *towerDoc, Rect &rect, UInt32 var, Boolean flag) {
	Int32 result = 0;

	if (mProgramPlugin)
		result = ((T2ToolPlugin *) mProgramPlugin)->AreaCheck2Proc(towerDoc, rect, var, flag);

	return result;
}

Int32 T2ToolDef::DoBuildProc(T2TowerDoc *towerDoc, Rect *rect) {
	Int32 result = 0;

	if (mProgramPlugin)
		result = ((T2ToolPlugin *) mProgramPlugin)->DoBuildProc(towerDoc, this, rect);

	return result;
}

void T2ToolDef::BuildFinishProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject) {
	if (mProgramPlugin)
		((T2ToolPlugin *) mProgramPlugin)->BuildFinishProc(towerDoc, haveOutViewObject);
}

void T2ToolDef::BuildOptionProc(T2TowerDoc *towerDoc, T2Equip *equip) {
	if (mProgramPlugin)
		((T2ToolPlugin *) mProgramPlugin)->BuildOptionProc(towerDoc, equip);
}

Int32 T2ToolDef::CalcPayment(T2TowerDoc *doc, Rect &rect, UInt32 index) {
	return mPrice[index];
}

Int32 T2ToolDef::GetConsumptionPower(UInt32 index) {
	return mConsumptionPower[index];
}

Int32 T2ToolDef::MakeCursorProc(T2WorldDef *worldDef, T2GWorld **world, Int16 var) {
	Int32 result = -1;

	if (mProgramPlugin)
		result = ((T2ToolPlugin *) mProgramPlugin)->MakeCursorProc(worldDef, world, var);

	return result;
}

Int32 T2ToolDef::DestructProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject, Point pt, Rect &rect) {
	if (mProgramPlugin)
		return ((T2ToolPlugin *) mProgramPlugin)->DestructProc(towerDoc, haveOutViewObject, pt, &rect);
	else
		return 0;
}

void T2ToolDef::DestructFinishProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject) {
	if (mProgramPlugin)
		((T2ToolPlugin *) mProgramPlugin)->DestructFinishProc(towerDoc, haveOutViewObject);
}

Int32 T2ToolDef::GetInfoSetupProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject, LDialogBox *dialog) {
	if (mProgramPlugin)
		return ((T2ToolPlugin *) mProgramPlugin)->GetInfoSetupProc(towerDoc, haveOutViewObject, dialog);
	else
		return -1;
}

Int32 T2ToolDef::GetInfoOKProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject, LDialogBox *dialog) {
	if (mProgramPlugin)
		return ((T2ToolPlugin *) mProgramPlugin)->GetInfoOKProc(towerDoc, haveOutViewObject, dialog);
	else
		return -1;
}

Int32 T2ToolDef::GetInfoCancelProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject, LDialogBox *dialog) {
	if (mProgramPlugin)
		return ((T2ToolPlugin *) mProgramPlugin)->GetInfoCancelProc(towerDoc, haveOutViewObject, dialog);
	else
		return -1;
}

Int32 T2ToolDef::GetInfoListenProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject, LDialogBox *dialog, MessageT message, void *ioParam) {
	if (mProgramPlugin)
		return ((T2ToolPlugin *) mProgramPlugin)->GetInfoListenProc(towerDoc, haveOutViewObject, dialog, message, ioParam);
	else
		return 0;
}

Int16 T2ToolDef::IsAbleDragMaking(Int16 index) {
	return mProgramPlugin ? ((T2ToolPlugin *) mProgramPlugin)->IsAbleDragMakingProc(this, index) : 0;
}

Int32 T2ToolDef::CalcMentenanceCostProc(const T2HaveOutViewObject *haveOutViewObject) const {
	Int32 result = 0;

	if (mProgramPlugin)
		result = ((T2ToolPlugin *) mProgramPlugin)->CalcMentenanceCostProc(haveOutViewObject);

	return result;
}

void T2ToolDef::LoadExtraData(LStream &stream, T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject) {
	if (mProgramPlugin)
		((T2ToolPlugin *) mProgramPlugin)->LoadExtraData(stream, towerDoc, haveOutViewObject);
}

void T2ToolDef::SaveExtraData(LStream &stream, T2HaveOutViewObject *haveOutViewObject) {
	if (mProgramPlugin)
		((T2ToolPlugin *) mProgramPlugin)->SaveExtraData(stream, haveOutViewObject);
}


Int32 T2ToolDef::CalcSoundID(Int16 index) const {
	return (mToolType << 16) + index;
}

Int32 T2ToolDef::DrawData(Int32 pos) {
	LStr255 tmp;

	Int16 p = pos;
	::MoveTo(10, p);
	::DrawString("\p================================");

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmToolType : ");
	tmp = (Int32) mToolType;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmWidth : ");
	tmp = (Int32) mWidth;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmHeight : ");
	tmp = (Int32) mHeight;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\p========== Attribute ===========");
	p = DrawAttribute(p);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\p================================");

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmLevel : ");
	tmp = (Int32) mLevel;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmCategoryCommentString : ");
	::DrawString(mCategoryCommentString);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmCategoryName : ");
	::DrawString(mCategoryName);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmCategoryNo : ");
	tmp = (Int32) mCategoryNo;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmToolNo : ");
	tmp = (Int32) mToolNo;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pSortKey : ");
	tmp = (Int32) GetSortKey();
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmAfterCategoryNo : ");
	tmp = (Int32) mAfterCategoryNo;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmAfterToolNo : ");
	tmp = (Int32) mAfterToolNo;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmValiationCount : ");
	tmp = (Int32) mValiationCount;
	::DrawString(tmp);

	for (Int32 i = 0; i < mValiationCount; i++) {
		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmPriceString[");
		tmp = (Int32) i;
		::DrawString(tmp);
		::DrawString("\p] : ");
		::DrawString(mPriceString[i]);

		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmOutMoneyString[");
		tmp = (Int32) i;
		::DrawString(tmp);
		::DrawString("\p] : ");
		::DrawString(mOutMoneyString[i]);

		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmCommentString[");
		tmp = (Int32) i;
		::DrawString(tmp);
		::DrawString("\p] : ");
		::DrawString(mCommentString[i]);

		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmToolName[");
		tmp = (Int32) i;
		::DrawString(tmp);
		::DrawString("\p] : ");
		::DrawString(mToolName[i]);

		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmPrice[");
		tmp = (Int32) i;
		::DrawString(tmp);
		::DrawString("\p] : ");
		tmp = (Int32) mPrice[i];
		::DrawString(tmp);

		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmOutMoney[");
		tmp = (Int32) i;
		::DrawString(tmp);
		::DrawString("\p] : ");
		tmp = (Int32) mOutMoney[i];
		::DrawString(tmp);

		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmToolIcon[");
		tmp = (Int32) i;
		::DrawString(tmp);
		::DrawString("\p] : ");
		UDebugUtils::HexString(&mToolIcon[i], tmp);
		::DrawString(tmp);
		p = DrawGWorld(mToolIcon[i], p);


		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmOffscreen[");
		tmp = (Int32) i;
		::DrawString(tmp);
		::DrawString("\p] : ");
		UDebugUtils::HexString(&mOffscreen[i], tmp);
		::DrawString(tmp);
		p = DrawGWorld(mOffscreen[i], p);
	}

	p += 16;
	return p;
}

Int16 T2ToolDef::DrawAttribute(Int16 pos) {
	Int16 p = pos;
	LStr255 tmp;

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmAttribute : ");
	UDebugUtils::HexString(&mAttribute, tmp);
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\p(");
	UDebugUtils::BitString(&mAttribute, tmp);
	::DrawString(tmp);
	::DrawString("\p)");

	p += 16;

	return p;
}
