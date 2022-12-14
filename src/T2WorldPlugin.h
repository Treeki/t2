#pragma once

#include "CProgramPlugin.h"

class BkgndInfo;
class LDialogBox;
class LFile;
class LStream;
class LWindow;
class T2DateTime;
class T2Equip;
class T2FloorInfo;
class T2GWorld;
class T2MWDispatchButton;
class T2PaletteAnime;
class T2TowerDoc;
class T2TreasureStatus;
class T2WorldDef;
class T2WorldPlugin;
class T2XEvent;

typedef void (*InitFloorInfoProcT)(T2WorldPlugin *, T2WorldDef *, T2FloorInfo *);
typedef void (*InitBkgndInfoProcT)(T2WorldPlugin *, T2WorldDef *, BkgndInfo *);
typedef void (*InitDocumentProcT)(T2WorldPlugin *, T2WorldDef *, T2TowerDoc *);
typedef void (*CloseDocumentProcT)(T2WorldPlugin *, T2WorldDef *, T2TowerDoc *);
typedef void (*WriteStatisticsProcT)(T2WorldPlugin *, T2WorldDef *, T2TowerDoc *, LStream &);
typedef void (*ReadStatisticsProcT)(T2WorldPlugin *, T2WorldDef *, T2TowerDoc *, LStream &);
typedef Boolean (*ChangeFastSEProcT)(T2WorldPlugin *, T2WorldDef *, T2PaletteAnime *);
typedef void (*ChangeSEProcT)(T2WorldPlugin *, T2WorldDef *, T2PaletteAnime *);
typedef Boolean (*ChangeSkyColorProcT)(T2WorldPlugin *, T2WorldDef *, T2PaletteAnime *);
typedef void (*DrawRoofAndFloorProcT)(T2WorldPlugin *, T2TowerDoc *, const Rect &, Boolean);
typedef void (*DrawBuildProcT)(T2WorldPlugin *, T2TowerDoc *, T2Equip *);
typedef void (*DrawSideObjectProcT)(T2WorldPlugin *, T2TowerDoc *, Point, Boolean);
typedef void (*DrawMWDispatchProcT)(T2WorldPlugin *, T2MWDispatchButton *, T2TowerDoc *);
typedef void (*DrawCraneProcT)(T2WorldPlugin *, T2TowerDoc *, const Rect &);
typedef void (*CalcCranePosProcT)(T2WorldPlugin *, T2TowerDoc *);
typedef void (*ClearCranePosProcT)(T2WorldPlugin *, T2TowerDoc *);
typedef Boolean (*IsHolidayProcT)(T2WorldPlugin *, T2DateTime *);
typedef Boolean (*IsRainyDayProcT)(T2WorldPlugin *, T2DateTime *);
typedef void (*AdjustSkyStateProcT)(T2WorldPlugin *, T2WorldDef *, T2PaletteAnime *, T2DateTime *);
typedef void (*DayChangedProcT)(T2WorldPlugin *, T2TowerDoc *);
typedef void (*ViewModeChangedProcT)(T2WorldPlugin *, T2TowerDoc *, Int16);
typedef Boolean (*CheckTreasureProcT)(T2WorldPlugin *, T2TowerDoc *, T2TreasureStatus *);
typedef void (*ShowPopulationDialogProcT)(T2WorldPlugin *, T2TowerDoc *);
typedef Int32 (*CheckGameLevelProcT)(T2WorldPlugin *, T2WorldDef *, T2TowerDoc *);
typedef void (*GraphSetupProcT)(T2WorldPlugin *, T2TowerDoc *, LDialogBox *);
typedef void (*GraphListenProcT)(T2WorldPlugin *, T2TowerDoc *, LDialogBox *, MessageT, void *);
typedef void (*SettlementSetupProcT)(T2WorldPlugin *, T2TowerDoc *, LDialogBox *);
typedef Int32 (*XEventInitProcT)(T2WorldPlugin *, T2XEvent *, LStream *);
typedef Int32 (*XEventDestructProcT)(T2WorldPlugin *, T2XEvent *);
typedef Int32 (*XEventStartProcT)(T2WorldPlugin *, T2TowerDoc *, T2XEvent *);
typedef Int32 (*XEventReStartProcT)(T2WorldPlugin *, T2TowerDoc *, T2XEvent *);
typedef Int32 (*XEventExecProcT)(T2WorldPlugin *, T2TowerDoc *, T2XEvent *);
typedef Int32 (*XEventStopProcT)(T2WorldPlugin *, T2TowerDoc *, T2XEvent *);
typedef Int32 (*XEventIsBeginTimeProcT)(T2WorldPlugin *, T2TowerDoc *, T2XEvent *, UInt32);
typedef Int32 (*XEventIsBeginDayProcT)(T2WorldPlugin *, T2TowerDoc *, T2XEvent *, Int16);
typedef Int32 (*XEventWriteProcT)(T2WorldPlugin *, T2XEvent *, LStream &stream);
typedef Int32 (*XEventReadProcT)(T2WorldPlugin *, T2XEvent *, LStream &stream);
typedef Int32 (*XEventDlgHookProcT)(T2WorldPlugin *, T2TowerDoc *, T2XEvent *, LWindow *, Int32);

class T2WorldPlugin : public CProgramPlugin {
public:
	T2WorldPlugin(UInt32 id, const FSSpec &spec);
	~T2WorldPlugin();
	OSErr LoadAllTemplatePlugin(T2WorldDef *, Int16, T2TemplatePluginDB *);
	T2WorldDef *LoadT2WorldDef();

	void InitFloorInfoProc(T2WorldDef *inWorldDef, T2FloorInfo *inFloorInfo);
	void InitBkgndInfoProc(T2WorldDef *inWorldDef, BkgndInfo *inBkgndInfoPtr);
	void InitDocumentProc(T2WorldDef *inWorldDef, T2TowerDoc *inDoc);
	void CloseDocumentProc(T2WorldDef *inWorldDef, T2TowerDoc *inDoc);
	void WriteStatisticsProc(T2WorldDef *inWorldDef, T2TowerDoc *inDoc, LStream &stream);
	void ReadStatisticsProc(T2WorldDef *inWorldDef, T2TowerDoc *inDoc, LStream &stream);
	Boolean ChangeSkyColorProc(T2WorldDef *inWorldDef, T2PaletteAnime *anime);
	Boolean ChangeFastSEProc(T2WorldDef *inWorldDef, T2PaletteAnime *anime);
	void ChangeSEProc(T2WorldDef *inWorldDef, T2PaletteAnime *anime);
	void AdjustSkyStateProc(T2WorldDef *inWorldDef, T2PaletteAnime *anime, T2DateTime *dateTime);
	void LoadT2PeopleDef(T2TemplatePluginDB *db);
	void LoadT2SilhouetteDef(T2TemplatePluginDB *db);
	void DayChanged(T2TowerDoc *doc);
	void ViewModeChanged(T2TowerDoc *doc, Int16 mode);
	void DrawMWDispatch(T2MWDispatchButton *button, T2TowerDoc *doc);
	void DrawRoofAndFloor(T2TowerDoc *doc, const Rect &rect, Boolean flag);
	void DrawBuild(T2TowerDoc *doc, T2Equip *equip);
	void DrawBuildMan(T2GWorld *, T2GWorld *, Rect, Int16, Int16);
	void DrawSideObject(T2TowerDoc *doc, const Point &pt, Boolean flag);
	void DrawCrane(T2TowerDoc *doc, const Rect &rect);
	void CalcCranePos(T2TowerDoc *doc);
	void ClearCranePos(T2TowerDoc *doc);
	Boolean IsHoliday(T2DateTime *dateTime);
	Boolean IsRainyDay(T2DateTime *dateTime);
	Int32 CheckGameLevel(T2WorldDef *def, T2TowerDoc *doc);
	void GraphSetup(T2TowerDoc *doc, LDialogBox *dialog);
	void GraphListen(T2TowerDoc *doc, LDialogBox *dialog, MessageT message, void *ioParam);
	void SettlementSetup(T2TowerDoc *doc, LDialogBox *dialog);
	Boolean CheckTreasure(T2TowerDoc *doc, T2TreasureStatus *status);
	void ShowPopulationDialog(T2TowerDoc *doc);
	Int32 XEventInit(T2XEvent *event, LStream *stream);
	Int32 XEventDestruct(T2XEvent *event);
	Int32 XEventStart(T2XEvent *event, T2TowerDoc *doc);
	Int32 XEventReStart(T2XEvent *event, T2TowerDoc *doc);
	Int32 XEventExec(T2XEvent *event, T2TowerDoc *doc);
	Int32 XEventStop(T2XEvent *event, T2TowerDoc *doc);
	Int32 XEventIsBeginTime(T2XEvent *event, T2TowerDoc *doc, UInt32 time);
	Int32 XEventIsBeginDay(T2XEvent *event, T2TowerDoc *doc, Int16 day);
	Int32 XEventWrite(T2XEvent *event, LStream &stream);
	Int32 XEventRead(T2XEvent *event, LStream &stream);
	Int32 XEventDlgHook(T2XEvent *event, T2TowerDoc *doc, LWindow *window, Int32 var);

	T2GWorld *GetMainPicture() { return mMainPicture; }

	UInt16 m90;
	UInt32 m94;
	InitFloorInfoProcT mInitFloorInfoProc;
	InitBkgndInfoProcT mInitBkgndInfoProc;
	InitDocumentProcT mInitDocumentProc;
	CloseDocumentProcT mCloseDocumentProc;
	WriteStatisticsProcT mWriteStatisticsProc;
	ReadStatisticsProcT mReadStatisticsProc;
	ChangeFastSEProcT mChangeFastSEProc;
	ChangeSEProcT mChangeSEProc;
	ChangeSkyColorProcT mChangeSkyColorProc;
	AdjustSkyStateProcT mAdjustSkyStateProc;
	DrawRoofAndFloorProcT mDrawRoofAndFloorProc;
	DrawBuildProcT mDrawBuildProc;
	DrawSideObjectProcT mDrawSideObjectProc;
	DrawMWDispatchProcT mDrawMWDispatchProc;
	DrawCraneProcT mDrawCraneProc;
	CalcCranePosProcT mCalcCranePosProc;
	ClearCranePosProcT mClearCranePosProc;
	IsHolidayProcT mIsHolidayProc;
	IsRainyDayProcT mIsRainyDayProc;
	DayChangedProcT mDayChangedProc;
	ViewModeChangedProcT mViewModeChangedProc;
	CheckTreasureProcT mCheckTreasureProc;
	ShowPopulationDialogProcT mShowPopulationDialogProc;
	CheckGameLevelProcT mCheckGameLevelProc;
	GraphSetupProcT mGraphSetupProc;
	GraphListenProcT mGraphListenProc;
	SettlementSetupProcT mSettlementSetupProc;
	XEventInitProcT mXEventInitProc;
	XEventDestructProcT mXEventDestructProc;
	XEventStartProcT mXEventStartProc;
	XEventReStartProcT mXEventReStartProc;
	XEventExecProcT mXEventExecProc;
	XEventStopProcT mXEventStopProc;
	XEventIsBeginTimeProcT mXEventIsBeginTimeProc;
	XEventIsBeginDayProcT mXEventIsBeginDayProc;
	XEventWriteProcT mXEventWriteProc;
	XEventReadProcT mXEventReadProc;
	XEventDlgHookProcT mXEventDlgHook;
	UInt32 m130;
	UInt32 m134;
	ResIDT mMainPictureID;
	ResIDT mCityEditorPictureID;
	ResIDT mAttr4;
	T2GWorld *mMainPicture;
	Int16 mAttr6;
	Int16 mAttr8;
	Int16 mAttrA;
	Int32 mAttrC;
	Int32 mAttr10;
	Int32 mAttr14;
	LStr255 mAttrString;
};
