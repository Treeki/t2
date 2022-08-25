#include "CProgramPlugin.h"
#include "T2EquipDef.h"
#include "T2EquipPlugin.h"
#include "T2GWorld.h"
#include "T2WordDefArray.h"
#include "T2WorldDef.h"
#include "UDebugUtils.h"

#include <LFile.h>
#include <LStream.h>
#include <LString.h>
#include <UException.h>

T2EquipDef::T2EquipDef(UInt32 id, LStream *stream, T2WorldDef *worldDef, T2EquipPlugin *equipPlugin)
	: T2ToolDef(id, stream, worldDef, equipPlugin)
{
	#line 32
	ThrowIfNil_(equipPlugin);

	Init();
	(*stream) >> mCapacity;
	(*stream) >> mStress;

	try {
		for (Int16 i = 0; i < mValiationCount; i++) {
			Int32 x = 0;
			if (IsSetAttribute(0x2000) && i == 1)
				x = worldDef->m15C - 1;

			ResIDT maskResID;
			(*stream) >> maskResID;
			if (maskResID != 0) {
				T2GWorld *world = new T2GWorld(maskResID, 1, 0, 0, 0);
				if (world) {
					mMask[i] = world->MakeRgn();
					delete world;
				}
			}

			(*stream) >> mOffOptionResIDs[i];
			Int16 offs;
			(*stream) >> offs;
			if (mOffOptionResIDs[i] != 0) {
				mOffOptionResIDs[i] += x * 10;
				mOffOptionResIDs[i] += worldDef->m15E;
			}
			if (offs != 0) {
				offs += x;
				mOffOption[i] = new T2GWorld(offs, 8, worldDef->mCTabH, 0, 0);
			}
		}

		(*stream) >> mOutSpan;
		(*stream) >> mInSpan;
		mInitInMoney = 0;
		(*stream) >> mNumOfInMoney;
		for (Int32 i = 0; i < mNumOfInMoney; i++) {
			if (i < 4) {
				(*stream) >> mInMoney[i];
			} else {
				Int32 tmp;
				(*stream) >> tmp;
			}
		}

		if (mNumOfInMoney > 4)
			mNumOfInMoney = 4;

		mWordDefArray = T2WordDefArray::MakeWordDefArray();
	} catch (ExceptionCode code) {
		delete this;
		#line 113
		Throw_(code);
	}
}

void T2EquipDef::Init() {
	for (UInt32 i = 0; i < 4; i++) {
		mMask[i] = 0;
		mOffOption[i] = 0;
	}

	mOffscreenKind = EOffscreenKind_0;
	mWordDefArray = 0;
}

T2EquipDef::~T2EquipDef() {
	for (Int16 i = 0; i < mValiationCount; i++) {
		if (mMask[i])
			::DisposeRgn(mMask[i]);
		if (mOffOption[i])
			delete mOffOption[i];
	}

	delete mWordDefArray;
}

Int32 T2EquipDef::GetInMoney(UInt32 index) const {
	Int32 result = 0;
	if (index < mNumOfInMoney)
		result = mInMoney[index];
	return result;
}

void T2EquipDef::ChangeOffscreen(EOffscreenKind offscreenKind) {
	if (mOffscreenKind == offscreenKind)
		return;

	mProgramPlugin->GetFile()->OpenResourceFork(1);
	ResIDT *resIDs = (offscreenKind == EOffscreenKind_0) ? mOffscreenResIDs : mOffOptionResIDs;

	for (UInt32 i = 0; i < mValiationCount; i++, resIDs++) {
		mOffscreenExists[i] = false;

		T2GWorld *world = mOffscreen[i];
		ResIDT resID = *resIDs;
		if (world != 0 && resID > 0) {
			Handle res = ::Get1Resource('PICT', resID);
			if (res) {
				Rect bounds = (*((PicHandle) res))->picFrame;
				world->BeginDrawing();
				::DrawPicture((PicHandle) res, &bounds);
				world->EndDrawing();
				::ReleaseResource(res);
				mOffscreenExists[i] = true;
			}
		}
	}

	mProgramPlugin->GetFile()->CloseResourceFork();
	mOffscreenKind = offscreenKind;
}

Boolean T2EquipDef::HasDrawOutViewProc() const {
	Boolean result = false;
	if (mProgramPlugin) {
		T2EquipPlugin *equipPlugin = (T2EquipPlugin *) mProgramPlugin;
		result = (equipPlugin->mDrawOutViewProc != 0);
	}
	return result;
}

void T2EquipDef::DrawGhostProc(T2Equip *equip, T2GWorld *gworld) {
	if (mProgramPlugin)
		mProgramPlugin->DrawGhostProc(equip, gworld);
}

void T2EquipDef::DrawOutViewProc(T2Equip *equip, const Rect &rect, T2TowerDoc *doc) {
	if (mProgramPlugin)
		((T2EquipPlugin *) mProgramPlugin)->DrawOutViewProc(equip, rect, doc);
}

ResIDT T2EquipDef::GetInfoDialogIDProc(T2TowerDoc *doc, T2Equip *equip) {
	return mProgramPlugin ? (ResIDT) ((T2EquipPlugin *) mProgramPlugin)->GetInfoDialogIDProc(doc, equip) : 0;
}

Int32 T2EquipDef::GetInfoProc(T2TowerDoc *doc, T2Equip *equip) {
	if (mProgramPlugin)
		return ((T2EquipPlugin *) mProgramPlugin)->GetInfoProc(doc, equip);
	else
		return -1;
}

void T2EquipDef::ConstrainMouseProc(Rect *rectA, Rect *rectB) {
	if (mProgramPlugin)
		((T2EquipPlugin *) mProgramPlugin)->ConstrainMouseProc(rectA, rectB);
}

Int32 T2EquipDef::GetDestructPartProc(Int16 var, Point ptA, Point ptB, T2Equip *equip) {
	Int32 result = -1;
	if (mProgramPlugin)
		result = ((T2EquipPlugin *) mProgramPlugin)->GetDestructPartProc(var, ptA, ptB, equip);
	return result;
}

Int32 T2EquipDef::GetClickPartProc(T2TowerDoc *doc, T2Equip *equip, Point pt, Int16 *s) {
	Int32 result = -1;
	if (mProgramPlugin)
		result = ((T2EquipPlugin *) mProgramPlugin)->GetClickPartProc(doc, equip, pt, s);
	return result;
}

Int32 T2EquipDef::MakeCursorProc(T2WorldDef *worldDef, T2GWorld **gworld, Int16 var) {
	Int32 result = -1;
	if (mProgramPlugin)
		result = ((T2EquipPlugin *) mProgramPlugin)->MakeCursorProc(worldDef, gworld, var);
	return result;
}

Int32 T2EquipDef::EmergencyProc(T2TowerDoc *doc, T2Equip *equip) {
	Int32 result = 0;
	if (mProgramPlugin)
		result = ((T2EquipPlugin *) mProgramPlugin)->EmergencyProc(doc, equip);
	return result;
}

Int32 T2EquipDef::BurntDownProc(T2TowerDoc *doc, T2Equip *equip) {
	Int32 result = 0;
	if (mProgramPlugin)
		result = ((T2EquipPlugin *) mProgramPlugin)->BurntDownProc(doc, equip);
	return result;
}

Int32 T2EquipDef::DrawData(Int32 pos) {
	LStr255 tmp;
	Int16 p = T2ToolDef::DrawData(pos);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\p================================");

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmCapacity : ");
	tmp = (Int32) mCapacity;
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
	::DrawString("\pmStress : ");
	tmp = (Int32) mStress;
	::DrawString(tmp);

	for (Int32 i = 0; i < mValiationCount; i++) {
		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmMask[");
		tmp = (Int32) i;
		::DrawString(tmp);
		::DrawString("\p] : ");
		tmp = (Int32) mMask[i];
		::DrawString(tmp);

		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmOffOption[");
		tmp = (Int32) i;
		::DrawString(tmp);
		::DrawString("\p] : ");
		UDebugUtils::HexString(&mOffOption[i], tmp);
		::DrawString(tmp);
		p = DrawGWorld(mOffOption[i], p);
	}

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmOutSpan : ");
	tmp = (Int32) mOutSpan;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmInSpan : ");
	tmp = (Int32) mInSpan;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmNumOfInMoney : ");
	tmp = (Int32) mNumOfInMoney;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmInitInMoney : ");
	tmp = (Int32) mInitInMoney;
	::DrawString(tmp);

	for (Int32 i = 0; i < mNumOfInMoney; i++) {
		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmInMoney[");
		tmp = (Int32) i;
		::DrawString(tmp);
		::DrawString("\p] : ");
		tmp = (Int32) mInMoney[i];
		::DrawString(tmp);
	}

	return p;
}

Int16 T2EquipDef::DrawAttribute(Int16 pos) {
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
	::MoveTo(10, p);
	::DrawString("\pIsAbleDragMaking : ");
	if (IsAbleDragMaking(0))
		::DrawString("\ptrue");
	else
		::DrawString("\pfalse");

	return p;
}
