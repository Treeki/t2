#include "T2ColdTableDef.h"
#include "T2GWorld.h"
#include "T2HaveOutViewObject.h"
#include "T2PaletteAnimeDef.h"
#include "T2PoolDef.h"
#include "T2SeasonParamDef.h"
#include "T2TowerEvent.h"
#include "T2WordDefArray.h"
#include "T2WorldDef.h"
#include "T2WorldPlugin.h"
#include "UDebugUtils.h"
#include "URect.h"
#include "UT2Coordinate.h"

#include <string.h>
#include <LHandleStream.h>
#include <LStream.h>
#include <UException.h>

T2WorldDef::T2WorldDef(UInt32 id, LStream *stream, T2WorldPlugin *worldPlugin)
	: T2TemplatePlugin(id, stream, worldPlugin)
{
	#line 53
	ThrowIfNil_(worldPlugin);
	Initialize();

	(*stream) >> mWorldType;
	(*stream) >> m150;
	(*stream) >> m152;
	(*stream) >> mGroundLine;
	(*stream) >> mBuildArea;

	#line 60
	Assert_(!::EmptyRect( &mBuildArea ));
	Assert_(mBuildArea.top >= 0);
	Assert_(mBuildArea.left >= 0);

	(*stream) >> mInitPos;
	(*stream) >> m1C;
	(*stream) >> m1E;
	(*stream) >> m20;
	(*stream) >> m22;
	(*stream) >> m15C;
	(*stream) >> m15E;
	(*stream) >> m2C;
	(*stream) >> m160;
	(*stream) >> mNumOfGradeDef;

	for (Int32 i = 0; i < 8; i++) {
		if (i < mNumOfGradeDef) {
			(*stream) >> mGradeDef[i].m0;
			(*stream) >> mGradeDef[i].m4;
			(*stream) >> mGradeDef[i].m8;
			(*stream) >> mGradeDef[i].mA;
			(*stream) >> mGradeDef[i].mC;
			(*stream) >> mGradeDef[i].mE;
		} else {
			mGradeDef[i].m0 = 0;
			mGradeDef[i].m4 = 0;
			mGradeDef[i].m8 = 0;
			mGradeDef[i].mA = 0;
			mGradeDef[i].mC = 0;
			mGradeDef[i].mE = 0;
		}
	}

	(*stream) >> mBGVUnit;
	(*stream) >> mBGHUnit;
	(*stream) >> mSkyVSize;
	(*stream) >> mSkyHSize;
	(*stream) >> mOffSkyResID;
	(*stream) >> mOffBackObjResID;
	for (Int32 i = 0; i < 2; i++) {
		(*stream) >> mOffSideObjResID[i];
		if (mOffSideObjResID[i])
			mOffSideObjResID[i] += m15E;
	}
	(*stream) >> mOffBuildPrcResID;
	(*stream) >> mOffOptionResID;
	(*stream) >> mMysteryResID162;
	(*stream) >> mMysteryResIDBC;
	(*stream) >> mBE;
	(*stream) >> mMysteryResIDC0;
	mMysteryGWorldC0_Width = mMysteryGWorldC0_Height = 0;
	for (Int32 i = 0; i < 5; i++) {
		(*stream) >> mMysteryResIDArrayC2[i];
	}
	for (UInt8 i = 0; i < 32; i++) {
		Byte b;
		(*stream) >> b;
		mCC[i] = b;
	}
	(*stream) >> mDustOnThreshold;
	(*stream) >> mToiletVar1;
	(*stream) >> mToiletVar2;
	(*stream) >> m178;

	memset(&m180, 0, sizeof(m180));
	Int16 count;
	(*stream) >> count;
	for (Int32 i = 0; i < count; i++) {
		UInt32 value;
		(*stream) >> value;
		if (i < 8)
			m180[i] = value;
	}

	try {
		mPaletteAnimeDef = MakePaletteAnimeDef();
		#line 161
		ThrowIfNil_(mPaletteAnimeDef);
		mCTabH = GetPaletteAnimeDef()->GetCTabH();
		SetupOffscreen();

		mPoolDef = MakePoolDef();
		#line 167
		ThrowIfNil_(mPoolDef);

		mSeasonParamDef = MakeSeasonParamDef();
		mColdTableDef = MakeColdTableDef();
		mTowerEvent = new T2TowerEvent(this);
		#line 172
		ThrowIfNil_(mTowerEvent);
		mWordDefArray = T2WordDefArray::MakeWordDefArray();

		mLoaded = true;
	} catch (ExceptionCode code) {
		delete this;
		#line 180
		Throw_(code);
	}
}

void T2WorldDef::Initialize() {
	mCTabH = 0;
	mOffSky = 0;
	mOffBackObj = 0;
	for (UInt32 i = 0; i < 2; i++) {
		mOffSideObj[i] = 0;
	}
	mOffBuildPrc = 0;
	mOffOption = 0;
	mMysteryGWorld162 = 0;
	mMysteryGWorldBC = 0;
	mMysteryGWorldC0 = 0;
	for (UInt32 i = 0; i < 5; i++) {
		mMysteryGWorldArrayC2[i] = 0;
	}
	mPoolDef = 0;
	for (Int32 i = 0; i < 4; i++) {
		m12C[i] = -1;
		m13C[i] = 0;
	}
	mPaletteAnimeDef = 0;
	mSeasonParamDef = 0;
	mTowerEvent = 0;
	mColdTableDef = 0;
	mWordDefArray = 0;
}

T2PaletteAnimeDef *T2WorldDef::MakePaletteAnimeDef() {
	T2PaletteAnimeDef *result = 0;
	Handle res = ::Get1IndResource('PtDf', 1);
	if (res) {
		::DetachResource(res);

		LHandleStream *stream = new LHandleStream(res);
		if (stream) {
			result = new T2PaletteAnimeDef(stream);
			delete stream;
		}
	}
	return result;
}

T2PoolDef *T2WorldDef::MakePoolDef() {
	Handle res = ::Get1IndResource('PlDf', 1);
	#line 269
	ThrowIfNil_(res);

	::DetachResource(res);
	LHandleStream stream(res);
	return new T2PoolDef(stream, (T2WorldPlugin *) mProgramPlugin);
}

T2SeasonParamDef *T2WorldDef::MakeSeasonParamDef() {
	T2SeasonParamDef *result = 0;

	Handle res = ::Get1IndResource('SpDf', 1);
	if (res) {
		::DetachResource(res);
		LHandleStream stream(res);
		result = new T2SeasonParamDef(stream);
		#line 293
		ThrowIfNil_(result);
	}

	return result;
}

T2ColdTableDef *T2WorldDef::MakeColdTableDef() {
	T2ColdTableDef *result = 0;

	Handle res = ::Get1IndResource('CoDf', 1);
	if (res) {
		::DetachResource(res);
		LHandleStream stream(res);
		result = new T2ColdTableDef(stream);
		#line 316
		ThrowIfNil_(result);
	}

	return result;
}

T2WorldDef::~T2WorldDef() {
	DisposeOffscreen();
	delete mPaletteAnimeDef;
	delete mSeasonParamDef;
	delete mColdTableDef;
	if (mPoolDef)
		delete mPoolDef;
	delete mTowerEvent;
	if (mWordDefArray)
		delete mWordDefArray;
}

void T2WorldDef::InitTowerEvent(T2TowerDoc *doc) {
	if (mTowerEvent)
		mTowerEvent->InitTowerEvent(doc);
}

void T2WorldDef::WriteTowerEvent(LStream &stream) {
	if (mTowerEvent)
		mTowerEvent->Write(stream);
}

void T2WorldDef::ReadTowerEvent(LStream &stream) {
	if (mTowerEvent)
		mTowerEvent->Read(stream);
}

void T2WorldDef::StopEvent() {
	if (mTowerEvent)
		mTowerEvent->StopEvent();
}

T2TowerEvent *T2WorldDef::GetTowerEvent() {
	return mTowerEvent;
}

void *T2WorldDef::GetFireBurning() {
	return mTowerEvent ? mTowerEvent->GetFireBurning() : 0;
}

void *T2WorldDef::GetMetroRailway() {
	return mTowerEvent ? mTowerEvent->GetMetroRailway() : 0;
}

void *T2WorldDef::GetBlackOut() {
	return mTowerEvent ? mTowerEvent->GetBlackOut() : 0;
}

Boolean T2WorldDef::IsBlackOut() {
	return mTowerEvent ? mTowerEvent->IsBlackOut() : false;
}

void T2WorldDef::SetLatestBuild(T2HaveOutViewObject *obj, Boolean flag) {
	if (mTowerEvent) {
		T2ToolDef *toolDef = obj->GetToolDef();
		mTowerEvent->SetLatestBuild(obj, toolDef, flag);
	}
}

void T2WorldDef::SetLatestBuild(T2ToolDef *toolDef, Boolean flag) {
	mTowerEvent->SetLatestBuild(0, toolDef, flag);
}

void *T2WorldDef::GetTowerVision() {
	return mTowerEvent ? mTowerEvent->GetTowerVision() : 0;
}

void *T2WorldDef::GetRubble() {
	return mTowerEvent ? mTowerEvent->GetRubble() : 0;
}

void *T2WorldDef::GetReggae() {
	return mTowerEvent ? mTowerEvent->GetReggae() : 0;
}

void T2WorldDef::GetName(LString &str) {
	str = (Int32) mWorldType;
}

Boolean T2WorldDef::IsDustOn(UInt32 var) const {
	return (mDustOnThreshold && var >= mDustOnThreshold);
}

Byte T2WorldDef::GetToiletDenomi(UInt32 var) const {
	Byte result = 0;
	if (mToiletVar1 && var >= mToiletVar1)
		result = mToiletVar2;
	return result;
}

Byte T2WorldDef::GetColdDenomi(UInt32 var1, UInt32 var2) const {
	Byte result = 0;
	if (mColdTableDef)
		result = mColdTableDef->GetDenomi(var1, var2);
	return result;
}

Int32 T2WorldDef::ExchangeMoney(Int32 money) {
	if (mProgramPlugin) {
		T2WorldPlugin *worldPlugin = (T2WorldPlugin *) mProgramPlugin;
		if (worldPlugin->mAttr10 == 1 && worldPlugin->mAttr14 == 1)
			return money;
		else
			return (money / worldPlugin->mAttr14) * worldPlugin->mAttr10;
	} else {
		return money;
	}
}

void T2WorldDef::DrawBkgnd(UInt16 pos, const Rect &rect, T2TowerDoc *doc) {
	// TODO requires TowerMainView, TowerDoc
}

void T2WorldDef::DrawBkgnd(const Rect &rect, T2TowerDoc *doc) {
	// TODO requires TowerMainView, TowerDoc
}

void T2WorldDef::DrawRoofAndFloor(T2TowerDoc *doc, const Rect &rect, Boolean flag) {
	if (mProgramPlugin)
		((T2WorldPlugin *) mProgramPlugin)->DrawRoofAndFloor(doc, rect, flag);
}

void T2WorldDef::DrawBuild(T2TowerDoc *doc, T2Equip *equip) {
	if (mProgramPlugin)
		((T2WorldPlugin *) mProgramPlugin)->DrawBuild(doc, equip);
}

void T2WorldDef::DrawSideObject(T2TowerDoc *doc, const Point &pt, Boolean flag) {
	if (mProgramPlugin)
		((T2WorldPlugin *) mProgramPlugin)->DrawSideObject(doc, pt, flag);
}

void T2WorldDef::DrawCrane(T2TowerDoc *doc, const Rect &rect) {
	if (mProgramPlugin)
		((T2WorldPlugin *) mProgramPlugin)->DrawCrane(doc, rect);
}

void T2WorldDef::DrawRubble(T2TowerDoc *doc, T2Tenant *tenant) {
	if (mTowerEvent)
		mTowerEvent->DrawRubble(doc, tenant);
}

void T2WorldDef::DrawMark(T2GWorld *gworld, const Rect &rect, Int32 factor, UInt32 ul) {
	if (mMysteryGWorld162) {
		Rect offRect, unitRect;

		Rect qdRect = { 0, 0, 1, 3 };
		unitRect = qdRect;

		UT2Coordinate::UnitToQD(qdRect, factor, false);
		UT2Coordinate::UnitToOffRect(unitRect, offRect, ul, false);
		URect::Center(rect, qdRect, false);

		mMysteryGWorld162->CopyOffImage(gworld, offRect, qdRect, 0x24, 0);
	}
}

void T2WorldDef::InitializeFloorInfo(T2FloorInfo *floorInfo) {
	((T2WorldPlugin *) mProgramPlugin)->InitFloorInfoProc(this, floorInfo);
}

void T2WorldDef::InitializeBkgndInfo(BkgndInfo *bkgndInfo) {
	((T2WorldPlugin *) mProgramPlugin)->InitBkgndInfoProc(this, bkgndInfo);
}

Boolean T2WorldDef::SetupGradeUpAnimation(T2SlideGWorldView *slideGWorldView, Int16 grade) {
	// TODO T2SlideGWorldView
	return false;
}

void T2WorldDef::GetGradeUpMessage(Int16 grade, LStr255 &str) {
	OpenResourceFork(1);
	str.Assign(1201, grade - 1);
	CloseResourceFork();
}

void T2WorldDef::InitializeDocument(T2TowerDoc *doc) {
	((T2WorldPlugin *) mProgramPlugin)->InitDocumentProc(this, doc);
}

Boolean T2WorldDef::IdleProc(T2TowerDoc *doc) {
	((T2WorldPlugin *) mProgramPlugin)->IdleProc(doc, 0);
	if (mTowerEvent)
		return mTowerEvent->Idle(doc);
	else
		return false;
}

Int32 T2WorldDef::CheckGameLevelProc(T2TowerDoc *doc) {
	return ((T2WorldPlugin *) mProgramPlugin)->CheckGameLevel(this, doc);
}

Boolean T2WorldDef::TenantAreaCheck(T2TowerDoc *doc, Rect &rect, Boolean flag) {
	// TODO: requires T2FloorInfo, T2TowerMessage
	return false;
}

void T2WorldDef::SetupOffscreen() {
	if (mOffSkyResID) {
		mOffSky = new T2GWorld(mOffSkyResID, 8, mCTabH, 0, 0);
		#line 912
		ThrowIfNil_(mOffSky);
	}

	if (mOffBackObjResID) {
		mOffBackObj = new T2GWorld(mOffBackObjResID, 8, mCTabH, 0, 0);
		ThrowIfNil_(mOffBackObj);
	}

	for (Int32 i = 0; i < 2; i++) {
		if (mOffSideObjResID[i]) {
			mOffSideObj[i] = new T2GWorld(mOffSideObjResID[i], 8, mCTabH, 0, 0);
			#line 924
			ThrowIfNil_(mOffSideObj[i]);
		}
	}

	if (mOffBuildPrcResID) {
		mOffBuildPrc = new T2GWorld(mOffBuildPrcResID, 8, mCTabH, 0, 0);
		#line 930
		ThrowIfNil_(mOffBuildPrc);
	}

	if (mOffOptionResID) {
		mOffOption = new T2GWorld(mOffOptionResID, 8, mCTabH, 0, 0);
		#line 935
		ThrowIfNil_(mOffOption);
	}

	if (mMysteryResID162) {
		mMysteryGWorld162 = new T2GWorld(mMysteryResID162, 8, mCTabH, 0, 0);
		#line 941
		ThrowIfNil_(mMysteryGWorld162);
	}

	if (mMysteryResIDBC) {
		mMysteryGWorldBC = new T2GWorld(mMysteryResIDBC, 8, mCTabH, 0, 0);
		#line 947
		ThrowIfNil_(mMysteryGWorldBC);
	}

	if (mMysteryResIDC0) {
		mMysteryGWorldC0 = new T2GWorld(mMysteryResIDC0, 8, mCTabH, 0, 0);
		#line 951
		ThrowIfNil_(mMysteryGWorldC0);

		Rect bounds;
		mMysteryGWorldC0->GetBounds(bounds);
		UT2Coordinate::QDToUnit(bounds, 0);
		mMysteryGWorldC0_Width = URect::Width(bounds);
		mMysteryGWorldC0_Height = URect::Height(bounds);
	}

	for (Int32 i = 0; i < 5; i++) {
		if (mMysteryResIDArrayC2[i]) {
			mMysteryGWorldArrayC2[i] = new T2GWorld(mMysteryResIDArrayC2[i], 8, mCTabH, 0, 0);
			#line 961
			ThrowIfNil_(mMysteryGWorldArrayC2[i]);
		}
	}
}

void T2WorldDef::DisposeOffscreen() {
	if (mOffSky)
		delete mOffSky;
	if (mOffBackObj)
		delete mOffBackObj;
	for (Int32 i = 0; i < 2; i++) {
		if (mOffSideObj[i])
			delete mOffSideObj[i];
	}
	if (mOffBuildPrc)
		delete mOffBuildPrc;
	if (mOffOption)
		delete mOffOption;
	delete mMysteryGWorld162;
	if (mMysteryGWorldBC)
		delete mMysteryGWorldBC;
}

T2GWorld *T2WorldDef::NewMsgWindowOffscreen() {
	mProgramPlugin->GetFile()->OpenResourceFork(1);
	T2GWorld *world = new T2GWorld(mBE, 8, mCTabH, 0, 0);
	mProgramPlugin->GetFile()->CloseResourceFork();
	return world;
}

void T2WorldDef::DrawMWDispatch(T2MWDispatchButton *button, T2TowerDoc *doc) {
	if (mProgramPlugin)
		((T2WorldPlugin *) mProgramPlugin)->DrawMWDispatch(button, doc);
}

void T2WorldDef::DayChanged(T2TowerDoc *doc) {
	if (mProgramPlugin)
		((T2WorldPlugin *) mProgramPlugin)->DayChanged(doc);
}

void T2WorldDef::ViewModeChanged(T2TowerDoc *doc, Int16 mode) {
	if (mProgramPlugin)
		((T2WorldPlugin *) mProgramPlugin)->ViewModeChanged(doc, mode);
	if (mTowerEvent)
		mTowerEvent->ViewModeChanged(doc, mode);
}

void T2WorldDef::ReplaceSkyOffscreen(ResIDT resID) {
	mProgramPlugin->GetFile()->OpenResourceFork(1);
	PicHandle pic = (PicHandle) ::Get1Resource('PICT', resID);
	if (pic && mOffSky) {
		Rect bounds = (*pic)->picFrame;
		mOffSky->BeginDrawing();
		::DrawPicture(pic, &bounds);
		mOffSky->EndDrawing();
		::ReleaseResource((Handle) pic);
	}
	mProgramPlugin->GetFile()->CloseResourceFork();
}

Int32 T2WorldDef::DrawData(Int32 pos) {
	LStr255 str;
	Int16 p = pos;

	::MoveTo(10, p);
	::DrawString("\p================================");

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmWorldType : ");
	str = (Int32) mWorldType;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmGroundLine : ");
	str = (Int32) mGroundLine;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmBuildArea : ");
	DrawRect(mBuildArea);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmInitPos : ");
	DrawPoint(mInitPos);

	p += 16;

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmNumOfGradeDef : ");
	str = (Int32) mNumOfGradeDef;
	::DrawString(str);

	for (Int32 i = 0; i < mNumOfGradeDef; i++) {
		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmGradeDef[");
		str = (Int32) i;
		::DrawString(str);
		::DrawString("\p] : ");
		str = (Int32) mGradeDef[i].m0;
		::DrawString(str);
		::DrawString("\p, ");
		str = (Int32) mGradeDef[i].m4;
		::DrawString(str);
	}

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmBGVUnit : ");
	str = (Int32) mBGVUnit;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmBGHUnit : ");
	str = (Int32) mBGHUnit;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmSkyVSize : ");
	str = (Int32) mSkyVSize;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmSkyHSize : ");
	str = (Int32) mSkyHSize;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmOffSkyResID : ");
	str = (Int32) mOffSkyResID;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmOffBackObjResID : ");
	str = (Int32) mOffBackObjResID;
	::DrawString(str);

	for (Int32 i = 0; i < 2; i++) {
		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmOffSideObjResID[");
		str = (Int32) i;
		::DrawString(str);
		::DrawString("\p] : ");
		str = (Int32) mOffSideObjResID[i];
		::DrawString(str);
	}

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmOffBuildPrcResID : ");
	str = (Int32) mOffBuildPrcResID;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmOffOptionResID : ");
	str = (Int32) mOffOptionResID;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmCTabH : ");
	UDebugUtils::HexString(&mCTabH, str);
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmOffSky : ");
	UDebugUtils::HexString(&mOffSky, str);
	::DrawString(str);
	p = DrawGWorld(mOffSky, p);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmOffBackObj : ");
	UDebugUtils::HexString(&mOffBackObj, str);
	::DrawString(str);
	p = DrawGWorld(mOffBackObj, p);

	for (Int32 i = 0; i < 2; i++) {
		p += 16;
		::MoveTo(10, p);
		::DrawString("\pmOffSideObj[");
		str = (Int32) i;
		::DrawString(str);
		::DrawString("\p] : ");
		UDebugUtils::HexString(&mOffSideObj[i], str);
		::DrawString(str);
		p = DrawGWorld(mOffSideObj[i], p);
	}

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmOffBuildPrc : ");
	UDebugUtils::HexString(&mOffBuildPrc, str);
	::DrawString(str);
	p = DrawGWorld(mOffBuildPrc, p);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmOffOption : ");
	UDebugUtils::HexString(&mOffOption, str);
	::DrawString(str);
	p = DrawGWorld(mOffOption, p);

	if (mPoolDef)
		p = mPoolDef->DrawData(p);

	return p;
}

Int32 T2WorldDef::GetSortKey() {
	return mWorldType;
}
