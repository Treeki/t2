#include "T2Equip.h"
#include "T2GWorld.h"
#include "T2PeopleDef.h"
#include "T2SilhouetteDef.h"
#include "T2TemplatePluginDB.h"
#include "T2TowerDoc.h"
#include "T2TowerMainView.h"
#include "T2WorldDef.h"
#include "T2WorldPlugin.h"
#include "URect.h"
#include "UT2BkgndInfo.h"
#include "UT2Coordinate.h"

#include <LHandleStream.h>

struct WorldAttr {
	ResIDT mainPictureID;
	ResIDT cityEditorPictureID;
	Int16 m4, m6, m8, mA;
	Int32 mC, m10, m14;
	Str63 mStr;
};

T2WorldPlugin::T2WorldPlugin(UInt32 id, const FSSpec &spec)
	: CProgramPlugin(id, spec)
{
	m90 = 0;
	m94 = 0;
	mInitFloorInfoProc = 0;
	mInitBkgndInfoProc = 0;
	mInitDocumentProc = 0;
	mCloseDocumentProc = 0;
	mWriteStatisticsProc = 0;
	mReadStatisticsProc = 0;
	mChangeFastSEProc = 0;
	mChangeSEProc = 0;
	mChangeSkyColorProc = 0;
	mAdjustSkyStateProc = 0;
	mDrawRoofAndFloorProc = 0;
	mDrawBuildProc = 0;
	mDrawSideObjectProc = 0;
	mDrawMWDispatchProc = 0;
	mDrawCraneProc = 0;
	mCalcCranePosProc = 0;
	mClearCranePosProc = 0;
	mIsHolidayProc = 0;
	mIsRainyDayProc = 0;
	mDayChangedProc = 0;
	mViewModeChangedProc = 0;
	mCheckTreasureProc = 0;
	mShowPopulationDialogProc = 0;
	mCheckGameLevelProc = 0;
	mGraphSetupProc = 0;
	mGraphListenProc = 0;
	mSettlementSetupProc = 0;
	mSettlementSetupProc = 0;
	mXEventInitProc = 0;
	mXEventDestructProc = 0;
	mXEventStartProc = 0;
	mXEventReStartProc = 0;
	mXEventExecProc = 0;
	mXEventStopProc = 0;
	mXEventIsBeginTimeProc = 0;
	mXEventIsBeginDayProc = 0;
	mXEventWriteProc = 0;
	mXEventReadProc = 0;

	ExceptionCode code = mFile->OpenResourceFork(1);
	WorldAttr **attrH = (WorldAttr **) ::Get1Resource('WAtr', 128);
	if (attrH) {
		mMainPictureID = (*attrH)->mainPictureID;
		mCityEditorPictureID = (*attrH)->cityEditorPictureID;
		mAttr4 = (*attrH)->m4;

		if (mMainPictureID) {
			mMainPicture = new T2GWorld(mMainPictureID, 8, 0, 0, 0);
		} else {
			mMainPicture = 0;
		}

		mAttr6 = (*attrH)->m6;
		mAttr8 = (*attrH)->m8;
		mAttrA = (*attrH)->mA;
		mAttrC = (*attrH)->mC;
		mAttr10 = (*attrH)->m10;
		mAttr14 = (*attrH)->m14;
		mAttrString = (*attrH)->mStr;

		::ReleaseResource((Handle) attrH);
	}
	mFile->CloseResourceFork();

	mCheckGameLevelProc = 0;
}

T2WorldPlugin::~T2WorldPlugin() {
	if (mMainPicture)
		delete mMainPicture;
}

OSErr T2WorldPlugin::LoadAllTemplatePlugin(T2WorldDef *, Int16, T2TemplatePluginDB *db) {
	OSErr err = mFile->OpenResourceFork(1);

	LoadT2PeopleDef(db);
	LoadT2SilhouetteDef(db);

	mFile->CloseResourceFork();
	return noErr;
}

T2WorldDef *T2WorldPlugin::LoadT2WorldDef() {
	T2WorldDef *def = 0;

	OSErr err = mFile->OpenResourceFork(1);
	Int16 resCount = ::Count1Resources('WdDf');
	Handle res = ::Get1IndResource('WdDf', 1);
	if (res) {
		::DetachResource(res);

		try {
			LHandleStream stream(res);
			def = new T2WorldDef('WdDf', &stream, this);
			#line 201
			ThrowIfNil_(def);
		} catch (ExceptionCode code) {
			mFile->CloseResourceFork();
			#line 206
			Throw_(code);
		}

		mTemplatePlugin = def;
	}

	mFile->CloseResourceFork();
	return def;
}

void T2WorldPlugin::InitFloorInfoProc(T2WorldDef *inWorldDef, T2FloorInfo *inFloorInfo) {
	// TODO
}

void T2WorldPlugin::InitBkgndInfoProc(T2WorldDef *inWorldDef, BkgndInfo *inBkgndInfoPtr) {
	#line 281
	Assert_(inWorldDef != 0);
	Assert_(inBkgndInfoPtr != 0);

	mFile->OpenResourceFork(1);

	if (::Count1Resources('BInf') > 0) {
		Handle res = ::Get1IndResource('BInf', 1);
		if (res) {
			::DetachResource(res);
			LHandleStream stream(res);

			Int32 vRange, hRange, dim3;
			stream >> vRange;
			stream >> hRange;
			#line 297
			Assert_((inBkgndInfoPtr->vRange == vRange) && (inBkgndInfoPtr->hRange == hRange));
			stream >> dim3;

			for (Int32 h = 0; h < hRange; h++) {
				for (Int32 v = 0; v < vRange; v++) {
					UInt32 *array = inBkgndInfoPtr->arrays[v];
					UInt32 value;
					stream >> value;
					array[h] = value;
				}
			}
		}
	}

	mFile->CloseResourceFork();

	if (mInitBkgndInfoProc)
		mInitBkgndInfoProc(this, inWorldDef, inBkgndInfoPtr);
}

void T2WorldPlugin::InitDocumentProc(T2WorldDef *inWorldDef, T2TowerDoc *inDoc) {
	if (mInitDocumentProc)
		mInitDocumentProc(this, inWorldDef, inDoc);
}

void T2WorldPlugin::CloseDocumentProc(T2WorldDef *inWorldDef, T2TowerDoc *inDoc) {
	if (mCloseDocumentProc)
		mCloseDocumentProc(this, inWorldDef, inDoc);
}

void T2WorldPlugin::WriteStatisticsProc(T2WorldDef *inWorldDef, T2TowerDoc *inDoc, LStream &stream) {
	if (mWriteStatisticsProc)
		mWriteStatisticsProc(this, inWorldDef, inDoc, stream);
}

void T2WorldPlugin::ReadStatisticsProc(T2WorldDef *inWorldDef, T2TowerDoc *inDoc, LStream &stream) {
	if (mReadStatisticsProc)
		mReadStatisticsProc(this, inWorldDef, inDoc, stream);
}

Boolean T2WorldPlugin::ChangeSkyColorProc(T2WorldDef *inWorldDef, T2PaletteAnime *anime) {
	return mChangeSkyColorProc(this, inWorldDef, anime);
}

Boolean T2WorldPlugin::ChangeFastSEProc(T2WorldDef *inWorldDef, T2PaletteAnime *anime) {
	return mChangeFastSEProc(this, inWorldDef, anime);
}

void T2WorldPlugin::ChangeSEProc(T2WorldDef *inWorldDef, T2PaletteAnime *anime) {
	mChangeSEProc(this, inWorldDef, anime);
}

void T2WorldPlugin::AdjustSkyStateProc(T2WorldDef *inWorldDef, T2PaletteAnime *anime, T2DateTime *dateTime) {
	mAdjustSkyStateProc(this, inWorldDef, anime, dateTime);
}

void T2WorldPlugin::LoadT2PeopleDef(T2TemplatePluginDB *db) {
	Int16 count = ::Count1Resources('PPDf');
	for (Int16 i = 1; i <= count; i++) {
		Handle res = ::Get1IndResource('PPDf', i);
		if (res) {
			::DetachResource(res);
			LHandleStream *stream;
			stream = new LHandleStream(res);
			T2PeopleDef *def = new T2PeopleDef('PPDf', stream, this);
			delete stream;
			db->Regist(def);
		}
	}
}

void T2WorldPlugin::LoadT2SilhouetteDef(T2TemplatePluginDB *db) {
	Int16 count = ::Count1Resources('SlDf');
	for (Int16 i = 1; i <= count; i++) {
		Handle res = ::Get1IndResource('SlDf', i);
		if (res) {
			::DetachResource(res);
			LHandleStream *stream;
			stream = new LHandleStream(res);
			T2SilhouetteDef *def = new T2SilhouetteDef('SlDf', stream);
			delete stream;
			db->Regist(def);
		}
	}
}

void T2WorldPlugin::DayChanged(T2TowerDoc *doc) {
	if (mDayChangedProc)
		mDayChangedProc(this, doc);
}

void T2WorldPlugin::ViewModeChanged(T2TowerDoc *doc, Int16 mode) {
	if (mViewModeChangedProc)
		mViewModeChangedProc(this, doc, mode);
}

void T2WorldPlugin::DrawMWDispatch(T2MWDispatchButton *button, T2TowerDoc *doc) {
	if (mDrawMWDispatchProc)
		mDrawMWDispatchProc(this, button, doc);
}

void T2WorldPlugin::DrawRoofAndFloor(T2TowerDoc *doc, const Rect &rect, Boolean flag) {
	if (mDrawRoofAndFloorProc == 0) {
		T2WorldDef *worldDef = doc->mWorldDef;
		T2GWorld *dstWorld = doc->GetMainView()->mGWorld;
		T2GWorld *srcWorld = worldDef->mOffBuildPrc;
		if (dstWorld && srcWorld) {
			Int16 zoomLevel = doc->GetZoomLevel();
			Rect srcRect, dstRect;
			srcWorld->GetBounds(srcRect);

			if (!flag) {
				UT2Coordinate::UnitToQDRoof(rect, dstRect, zoomLevel);
				srcRect.top = 72;
				srcRect.bottom = 80;
				srcWorld->CopyOffImageLoop(dstWorld, zoomLevel, srcRect, dstRect, 0, 0);
			}

			UT2Coordinate::UnitToQDFloor(rect, dstRect, zoomLevel);
			srcRect.top = 80;
			srcRect.bottom = 84;
			srcWorld->CopyOffImageLoop(dstWorld, zoomLevel, srcRect, dstRect, 0, 0);
		}
	} else {
		mDrawRoofAndFloorProc(this, doc, rect, flag);
	}
}

void T2WorldPlugin::DrawBuild(T2TowerDoc *doc, T2Equip *equip) {
	if (mDrawBuildProc) {
		mDrawBuildProc(this, doc, equip);
		return;
	}

	T2WorldDef *worldDef = (T2WorldDef *) mTemplatePlugin;
	if (!worldDef || !worldDef->mOffBuildPrc || !equip)
		return;

	Boolean r24 = equip->GetStatus() > 1;
	char r28 = r24 ? 36 : 0;
	T2GWorld *srcWorld = worldDef->mOffBuildPrc;
	T2GWorld *dstWorld = doc->GetMainView()->mGWorld;
	Int16 zoomLevel = doc->GetZoomLevel();

	// THIS IS A MESS
	/*Rect equipArea, manRect, dstRect2, srcRect, tmpRect, dstRect1;
	equipArea = equip->mEquipArea;

	UT2Coordinate::MakeRect(manRect, topLeft(equipArea), equipArea.right - equipArea.left, 1);
	UT2Coordinate::UnitToQD(manRect, dstRect2, zoomLevel, 1);

	Int16 r21 = (manRect.left + 2) % 2;
	::SetRect(&srcRect, 0, 0, )*/
}

void T2WorldPlugin::DrawBuildMan(T2GWorld *w1, T2GWorld *w2, Rect rect, Int16 a, Int16 b) {
	if (w1) {
		Int16 r31 = a % 6;
		Int16 r30 = a % (URect::Width(rect) - 1);

		Rect srcUnitRect, dstUnitRect;
		Rect srcRect, dstRect;

		::SetRect(&srcUnitRect, 0, 0, 2, 1);
		dstUnitRect = srcUnitRect;

		UT2Coordinate::UnitToOffRect(srcUnitRect, srcRect, r31, false);
		::OffsetRect(&dstUnitRect, rect.left + r30, rect.top);
		UT2Coordinate::UnitToQD(dstUnitRect, dstRect, b, false);
		w1->CopyOffImage(w2, srcRect, dstRect, 0x24, 0);
	}
}

void T2WorldPlugin::DrawSideObject(T2TowerDoc *doc, const Point &pt, Boolean flag) {
	if (mDrawSideObjectProc)
		mDrawSideObjectProc(this, doc, pt, flag);
}

void T2WorldPlugin::DrawCrane(T2TowerDoc *doc, const Rect &rect) {
	if (mDrawCraneProc)
		mDrawCraneProc(this, doc, rect);
}

void T2WorldPlugin::CalcCranePos(T2TowerDoc *doc) {
	if (mCalcCranePosProc)
		mCalcCranePosProc(this, doc);
}

void T2WorldPlugin::ClearCranePos(T2TowerDoc *doc) {
	if (mClearCranePosProc)
		mClearCranePosProc(this, doc);
}

Boolean T2WorldPlugin::IsHoliday(T2DateTime *dateTime) {
	if (mIsHolidayProc)
		return mIsHolidayProc(this, dateTime);
	else
		return true;
}

Boolean T2WorldPlugin::IsRainyDay(T2DateTime *dateTime) {
	if (mIsRainyDayProc)
		return mIsRainyDayProc(this, dateTime);
	else
		return false;
}

Int32 T2WorldPlugin::CheckGameLevel(T2WorldDef *def, T2TowerDoc *doc) {
	// TODO T2WorldDef, T2Pool
	return 0;
}

void T2WorldPlugin::GraphSetup(T2TowerDoc *doc, LDialogBox *dialog) {
	if (mGraphSetupProc)
		mGraphSetupProc(this, doc, dialog);
}

void T2WorldPlugin::GraphListen(T2TowerDoc *doc, LDialogBox *dialog, MessageT message, void *ioParam) {
	if (mGraphListenProc)
		mGraphListenProc(this, doc, dialog, message, ioParam);
}

void T2WorldPlugin::SettlementSetup(T2TowerDoc *doc, LDialogBox *dialog) {
	if (mSettlementSetupProc)
		mSettlementSetupProc(this, doc, dialog);
}

Boolean T2WorldPlugin::CheckTreasure(T2TowerDoc *doc, T2TreasureStatus *status) {
	if (mCheckTreasureProc)
		return mCheckTreasureProc(this, doc, status);
	else
		return false;
}

void T2WorldPlugin::ShowPopulationDialog(T2TowerDoc *doc) {
	if (mShowPopulationDialogProc)
		mShowPopulationDialogProc(this, doc);
}

Int32 T2WorldPlugin::XEventInit(T2XEvent *event, LStream *stream) {
	Int32 result = 0;
	if (mXEventInitProc)
		result = mXEventInitProc(this, event, stream);
	return result;
}

Int32 T2WorldPlugin::XEventDestruct(T2XEvent *event) {
	Int32 result = 0;
	if (mXEventDestructProc)
		result = mXEventDestructProc(this, event);
	return result;
}

Int32 T2WorldPlugin::XEventStart(T2XEvent *event, T2TowerDoc *doc) {
	Int32 result = 0;
	if (mXEventStartProc)
		result = mXEventStartProc(this, doc, event);
	return result;
}

Int32 T2WorldPlugin::XEventReStart(T2XEvent *event, T2TowerDoc *doc) {
	Int32 result = 0;
	if (mXEventReStartProc)
		result = mXEventReStartProc(this, doc, event);
	return result;
}

Int32 T2WorldPlugin::XEventExec(T2XEvent *event, T2TowerDoc *doc) {
	Int32 result = 0;
	if (mXEventExecProc)
		result = mXEventExecProc(this, doc, event);
	return result;
}

Int32 T2WorldPlugin::XEventStop(T2XEvent *event, T2TowerDoc *doc) {
	Int32 result = 0;
	if (mXEventStopProc)
		result = mXEventStopProc(this, doc, event);
	return result;
}

Int32 T2WorldPlugin::XEventIsBeginTime(T2XEvent *event, T2TowerDoc *doc, UInt32 time) {
	Int32 result = 0;
	if (mXEventIsBeginTimeProc)
		result = mXEventIsBeginTimeProc(this, doc, event, time);
	return result;
}

Int32 T2WorldPlugin::XEventIsBeginDay(T2XEvent *event, T2TowerDoc *doc, Int16 day) {
	Int32 result = 0;
	if (mXEventIsBeginDayProc)
		result = mXEventIsBeginDayProc(this, doc, event, day);
	return result;
}

Int32 T2WorldPlugin::XEventWrite(T2XEvent *event, LStream &stream) {
	Int32 result = 0;
	if (mXEventWriteProc)
		result = mXEventWriteProc(this, event, stream);
	return result;
}

Int32 T2WorldPlugin::XEventRead(T2XEvent *event, LStream &stream) {
	Int32 result = 0;
	if (mXEventReadProc)
		result = mXEventReadProc(this, event, stream);
	return result;
}

Int32 T2WorldPlugin::XEventDlgHook(T2XEvent *event, T2TowerDoc *doc, LWindow *window, Int32 var) {
	Int32 result = 0;
	if (mXEventDlgHook)
		result = mXEventDlgHook(this, doc, event, window, var);
	return result;
}
