#pragma once

#include <LPeriodical.h>

#include "T2Document.h"

class BkgndInfo;
class CFilePluginList;
class CPluginInfoArray;
class LString;
class LStr255;
struct SMouseDownEvent;
class T2Application;
class T2BufferedFileStream;
class T2DateTime;
class T2FloorInfo;
class T2GWorld;
class T2MatterArrayList;
class T2Mover;
class T2MoverDef;
class T2MoviePluginList;
class T2MWDispatchButton;
class T2Name;
class T2NameList;
class T2OutObj;
class T2OutObjDef;
class T2PaletteAnime;
class T2People;
class T2PeopleArrayList;
class T2PluginDialog;
class T2Pool;
class T2RegistedTenantDB;
class T2Settlement;
class T2SoundPlayer;
class T2Sprite;
class T2TemplatePluginDB;
class T2TemplatePluginList;
class T2Tenant;
class T2TenantDef;
class T2ToolDef;
class T2ToolDefDB;
class T2TrafficInfo;
class T2TowerMainView;
class T2TowerMessage;
class T2WorldDef;
class T2WorldPlugin;

struct DragMask {
};

class T2TowerDoc : public T2Document, public LPeriodical {
public:
	T2TowerDoc(T2Application *app, FSSpec *ignored, T2WorldPlugin *worldPlugin);
	void Initialize();
	~T2TowerDoc();
	void InitDocumentForPlugins(T2WorldPlugin *worldPlugin);
	void InitDocument();
	Boolean CheckFinger(T2MoverDef *moverDef, Point pt, Boolean flag);
	void DoMessage(Point pt, LStr255 str);
	void DoMessage(Point pt, ResIDT strID);
	Boolean IsToiletFlagOn() const;
	Boolean IsColdFlagOn() const;
	Boolean IsRectInView(const Rect &rect);
	void LoadSecretItem(Int16 item);
	Int32 Get1stCinemaDate();
	void Set1stCinemaDate(Int32 date);
	Boolean Start();
	Boolean Pause();
	void Step();
	void DrawSpeedChanged();
	void SetDrawSpeed(Int16 speed);
	Boolean SetElevTransparent(Boolean value);
	Boolean SetVolatile(Boolean value);
	void AdjustNextSimulationTime();
	void UnloadPlugins();
	Int32 GetCategoryCount();
	Int32 GetUsingToolDefList(Int32 index) const; // probably a ptr?
	Int32 GetToolDefListByCategory(Int16 category); // probably a ptr?

	static T2TowerDoc *GetCurrentT2TowerDoc();

	void ClearDocumentForPlugins();
	CFilePluginList *GetTenantPlugins();
	CFilePluginList *GetMoverPlugins();
	void SpendTime(const EventRecord &event);
	void IdleSimulation();
	void IdleWorld();
	void AttemptClose(Boolean flag);
	Boolean AttemptQuitSelf(Int32 saveOption);
	Boolean ObeyCommand(CommandT command, void *ioParam);
	void FindCommandStatus(CommandT inCommand, Boolean &outEnabled, Boolean &outUsesMark, Char16 &outMark, Str255 outName);
	void DbgFloorInfo(const SMouseDownEvent &event);
	void DoPayTool(Int32 a, Int16 b, T2ToolDef *toolDef);
	void DoPayTool(Int32 a, Int16 b, T2ToolDef *toolDef, const LString &str, Int16 c, Int16 d);
	void DoPay(Int32 a, Int16 b);
	void UpdateFundsInfo();
	Int32 GetCurrentFunds() const;
	void DoDestruct(const SMouseDownEvent &event);
	void DoGetInfo(const SMouseDownEvent &event);
	void DoInterview(Point pt);
	void DoFingerTool(const SMouseDownEvent &event);
	void DoFingerMachine(T2MoverDef *moverDef, T2Mover *mover, Point pt, Int16 a);
	void DoSearchRangeTool(const SMouseDownEvent &event);
	void SetSearchRangeFrom(T2Tenant *tenant);
	void DoClickByTenantTool(const SMouseDownEvent &event, T2TenantDef *tenantDef, UInt32 a);
	void DoDragByTenantTool(Rect rect, Int16 &s);
	void DoReleaseByTenantTool(Rect rect);
	void DoClickByMoverTool(const SMouseDownEvent &event, T2MoverDef *moverDef, UInt32 a);
	void DoClickByOutObjTool(const SMouseDownEvent &event, T2OutObjDef *outObjDef, UInt32 a);
	Boolean OutsideAreaCheck(T2Tenant *tenant, Boolean showErr);
	Boolean DestructTenant(Point ptA, Point ptB, T2Tenant *tenant, Boolean soundFlag);
	Boolean DestructMover(Point ptA, Point ptB, T2Mover *mover);
	Boolean DestructOutObj(Point ptA, Point ptB, T2OutObj *outObj);
	Boolean BuildTenant(Rect rect, Int16 a, Boolean flag);
	void TenantAdded(T2Tenant *tenant);
	void TenantRemoved(T2Tenant *tenant);
	Boolean BuildMover(const Rect &rect, T2MoverDef *moverDef);
	Boolean AddModule(const Rect &rect, T2MoverDef *moverDef);
	void BuildOutObj(const Rect &rect, T2OutObjDef *outObjDef);
	void SelectPlugins(Int16 a, Boolean flag);
	void FinalEventOccur();
	Int32 CheckGameLevel();
	GrafPtr GetMacPort();
	void UpdateAllTenant();
	void DrawBkgnd(const Rect &rect);
	void DrawBuilding(const Rect &rect1, const Rect &rect2);
	void DrawOutView(const Rect &rect);
	void DrawInView(const Rect &rect1, const Rect &rect2);
	void DrawTenantOutViewAll(const Rect &rect);
	void DrawTenantAll(const Rect &rect1, const Rect &rect2);
	void DrawRequestAll(const Rect &rect);
	void DrawMoverAll(const Rect &rect);
	void DrawTenantAllWithBG(const Rect &rect);
	void DrawSideObject(Point ptA, Point ptB, const Rect &rect);
	void DrawTenantAllWithoutBG(const Rect &rect);
	void DrawMWDispatch(T2MWDispatchButton *button);
	void DrawOutObject(const Rect &rect);
	void InvalClock();
	void InvalCalender();
	void InvalFunds();
	void InvalPopulation();
	void InvalMessage();
	void InvalByPaneID(Int32 id);
	Boolean DoGetInfoTenant(const SMouseDownEvent &event, T2Tenant *tenant);
	Boolean DoGetInfoMover(const SMouseDownEvent &event, T2Mover *mover);
	Boolean DoGetInfoPeople(const SMouseDownEvent &event, T2People *people);
	Boolean DoGetInfotheOutObj(const SMouseDownEvent &event, T2OutObj *outObj);
	void DoFind(T2Name *name);
	void DoRenumberTenant();
	Int16 GetNextTenantNumber(Int16 num);
	void CalcDragMask(Rect &rect, Boolean flag);
	void CalcDragMaskPoint(Rect &rect, Int32 &l, DragMask *dragMask, Int16 a, Boolean showErr);
	Boolean CheckTenantArea(Rect &rect, Boolean showErr, Boolean anotherFlag);
	T2Tenant *AssignNewTenant(T2TenantDef *tenantDef, Rect &rect, UInt32 ul);
	void CheckBuildQueue();
	Boolean CheckFillFloor(Rect &rect, UInt32 &ul1, UInt32 &ul2);
	void FillFloor(Rect rect);
	Int32 GetFloorVariation() const;
	Boolean IsSkyBridge(T2TenantDef *tenantDef);
	void BreakoutEmergency();
	void DoAESave(FSSpec &spec, OSType type);
	void DoSave();
	void OpenFile(FSSpec &spec);
	CPluginInfoArray *MakeLackPluginArray(T2BufferedFileStream *stream);
	Boolean CheckMustPlugin(LArray *array);
	Boolean CheckLackPlugin(LArray *array);
	void NewDocument();
	void ReadPool(LStream &stream);
	T2GWorld *GetCategoryIcon(Int16 category);
	Boolean GetCategoryName(Int16 category, LStr255 &str);
	T2GWorld *GetCategoryHelp(Int16 category);
	void SetWalkRate(Int16 walkRate);
	void SetViewMode(Int16 viewMode);
	Boolean FindToolStatus(Int16 what) const;
	Boolean FindCategoryStatus(Int16 category) const;
	CPluginInfoArray *MakePluginInfoArray();
	void _MakePluginInfoArray(CPluginInfoArray *pia, LArray *array);
	Boolean PluginCheck(LArray *array);
	void CalcCraneUpdateRect(Rect &rect);
	void DisplayGraphWindow();
	void SetWorldStatistics(void *stats);
	void DisplaySettlementWindow();
	void AddFavoritePeople(T2People *people);
	void AddFavoriteTenant(T2Tenant *tenant);
	void RemoveFavoriteName(T2Name *name, Boolean flag);
	void RemoveFavoritePeople(const LString &str, Boolean flag);
	void RemoveFavoriteTenant(const LString &str, Boolean flag);
	void RemoveFavoritePeople(T2People *people, Boolean flag);
	void RemoveFavoriteTenant(T2Tenant *tenant, Boolean flag);
	void OpenRemoveFavoritePeopleDialog();
	void OpenRemoveFavoriteTenantDialog();
	void UpdateFavoriteMenus(Boolean flag);
	void RecreateFavoriteMenus();
	void RequestPluginDialog(T2PluginDialog *dialog);
	void DoPluginDialog(void *param);
	Boolean IsFloatingInitialVisible(CommandT command);
	void DoEmergency();

	// note: GetWorldPlugin() is mWorldDef->programPlugin according to asserts
	// need to double check this...!

	T2DateTime *GetSomeDateTime() const { return someDateTime; }
	T2Application *GetApplication() const { return mApplication; }
	T2WorldPlugin *GetWorldPlugin() const { return mWorldPlugin; }
	T2WorldDef *GetWorldDef() const { return mWorldDef; }
	T2TowerMainView *GetMainView() const { return mTowerMainView; }
	T2PaletteAnime *GetPaletteAnime() const { return mPaletteAnime; }
	T2Pool *GetPool() const { return mPool; }

	Int16 GetZoomLevel() const { return mZoomLevel; }
	void SetZoomLevel(Int16 v) { mZoomLevel = v; }

	Boolean Get88() const { return m88; }

//protected:
	T2Application *mApplication;
	T2WorldPlugin *mWorldPlugin;
	T2WorldDef *mWorldDef;
	Int32 m78;
	Int16 mZoomLevel;
	Int16 m7E;
	T2Settlement *mSettlement;
	Int32 m84;
	Boolean m88;
	Int16 mDrawSpeed;
	Int16 m8C;
	Int16 mIdleCounter;
	Int16 mViewMode;
	T2DateTime *someDateTime;
	T2FloorInfo *mFloorInfo;
	BkgndInfo *mBkgndInfo;
	CFilePluginList *mTenantPluginsListOther;
	CFilePluginList *mMoverPluginsListOther;
	T2MoviePluginList *mMoviePluginsListOther;
	CFilePluginList *mHePluginsListOther;
	CFilePluginList *mOoPluginsListOther;
	CFilePluginList *mAdPluginsListOther;
	T2TemplatePluginList *mTenantTemplates;
	T2TemplatePluginList *mMoverTemplates;
	T2TemplatePluginList *mOOTemplates;
	T2TemplatePluginList *mC4;
	T2TemplatePluginList *mPPTemplates;
	T2TemplatePluginList *mSITemplates;
	T2TemplatePluginDB *mTemplatePluginDB;
	T2MatterArrayList *mMatterArrayList;
	T2PeopleArrayList *mPeopleArrayList;
	void *mDC;
	T2PaletteAnime *mPaletteAnime;
	void *E4;
	T2NameList *mNameDB;
	void *mEC;
	void *mF0;
	T2Sprite *mSprite;
	T2SoundPlayer *mSoundPlayer;
	void *mFC;
	void *m100;
	void *m104;
	T2TowerMessage *mTowerMessage;
	T2Tenant *mSearchRangeFrom;
	Boolean mVolatile;
	Boolean mElevTransparent;
	Boolean mIsDustOn;
	UInt8 mToiletDenomi;
	UInt8 mColdDenomi;
	Int32 m118;
	Int16 mWalkRate;
	T2TowerMainView *mTowerMainView;
	CFilePluginList *mTenantPlugins;
	CFilePluginList *mMoverPlugins;
	CFilePluginList *mMoPlugins;
	CFilePluginList *mHePlugins;
	CFilePluginList *mOoPlugins;
	CFilePluginList *mAdPlugins;
	T2RegistedTenantDB *mRegistedTenantDB;
	void *m140;
	T2Pool *mPool;
	T2TrafficInfo *mTrafficInfo;
	void *m14C;
	void *m150;
	UInt32 mTickCountAtStart;
	void *m158;
	LStr255 *mSomeStr255;
	T2TenantDef *mSkyBridgeMaybe;
	void *m164;
	void *m168;
	void *m16C;
	LArray *mObjectQueue;
	void *m174;
	void *m178;
	T2ToolDefDB *mToolDefDB;
	void *mWorldStatistics;
	void *m184;
	void *m188;
	void *m18C;
	void *m190;
	Int32 m1stCinemaDate;
	void *m198;
	void *m19C;
	void *m1A0;
};
