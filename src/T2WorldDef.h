#pragma once

#include "T2TemplatePlugin.h"

class BkgndInfo;
class T2ColdTableDef;
class T2Equip;
class T2FloorInfo;
class T2GWorld;
class T2HaveOutViewObject;
class T2MWDispatchButton;
class T2PaletteAnimeDef;
class T2PoolDef;
class T2SeasonParamDef;
class T2SlideGWorldView;
class T2Tenant;
class T2ToolDef;
class T2TowerDoc;
class T2TowerEvent;
class T2WordDefArray;
class T2WorldPlugin;

struct GradeDef { // assumed name
	UInt32 m0;
	UInt32 m4;
	Int16 m8;
	Int16 mA;
	Int16 mC;
	Int16 mE;
};

class T2WorldDef : public T2TemplatePlugin {
public:
	T2WorldDef(UInt32 id, LStream *stream, T2WorldPlugin *worldPlugin);

	void Initialize();
	T2PaletteAnimeDef *MakePaletteAnimeDef();
	T2PoolDef *MakePoolDef();
	T2SeasonParamDef *MakeSeasonParamDef();
	T2ColdTableDef *MakeColdTableDef();
	~T2WorldDef();
	void InitTowerEvent(T2TowerDoc *doc);
	void WriteTowerEvent(LStream &stream);
	void ReadTowerEvent(LStream &stream);
	void StopEvent();
	T2TowerEvent *GetTowerEvent();

	// retype me
	void *GetFireBurning();
	void *GetMetroRailway();
	void *GetBlackOut();
	Boolean IsBlackOut();
	void SetLatestBuild(T2HaveOutViewObject *obj, Boolean flag);
	void SetLatestBuild(T2ToolDef *toolDef, Boolean flag);
	void *GetTowerVision();
	void *GetRubble();
	void *GetReggae();

	void GetName(LString &str);
	Boolean IsDustOn(UInt32 var) const;
	Byte GetToiletDenomi(UInt32 var) const;
	Byte GetColdDenomi(UInt32 var1, UInt32 var2) const;
	Int32 ExchangeMoney(Int32 money);
	void DrawBkgnd(UInt16 pos, const Rect &rect, T2TowerDoc *doc);
	void DrawBkgnd(const Rect &rect, T2TowerDoc *doc);
	void DrawRoofAndFloor(T2TowerDoc *doc, const Rect &rect, Boolean flag);
	void DrawBuild(T2TowerDoc *doc, T2Equip *equip);
	void DrawSideObject(T2TowerDoc *doc, const Point &pt, Boolean flag);
	void DrawCrane(T2TowerDoc *doc, const Rect &rect);
	void DrawRubble(T2TowerDoc *doc, T2Tenant *tenant);
	void DrawMark(T2GWorld *gworld, const Rect &rect, Int32 factor, UInt32 ul);
	void InitializeFloorInfo(T2FloorInfo *floorInfo);
	void InitializeBkgndInfo(BkgndInfo *bkgndInfo);
	Boolean SetupGradeUpAnimation(T2SlideGWorldView *slideGWorldView, Int16 grade);
	void GetGradeUpMessage(Int16 grade, LStr255 &str);
	void InitializeDocument(T2TowerDoc *doc);
	Boolean IdleProc(T2TowerDoc *doc);
	Int32 CheckGameLevelProc(T2TowerDoc *doc);
	Boolean TenantAreaCheck(T2TowerDoc *doc, Rect &rect, Boolean flag);
	void SetupOffscreen();
	void DisposeOffscreen();
	T2GWorld *NewMsgWindowOffscreen();
	void DrawMWDispatch(T2MWDispatchButton *button, T2TowerDoc *doc);
	void DayChanged(T2TowerDoc *doc);
	void ViewModeChanged(T2TowerDoc *doc, Int16 mode);
	void ReplaceSkyOffscreen(ResIDT resID);
	Int32 DrawData(Int32 pos);
	Int32 GetSortKey();

	T2WorldPlugin *GetWorldPlugin() const {
		return (T2WorldPlugin *) mProgramPlugin;
	}
	T2PaletteAnimeDef *GetPaletteAnimeDef() const {
		return mPaletteAnimeDef;
	}

	Int16 mWorldType;
	Int16 mGroundLine;
	Point mInitPos;
	Int16 m1C;
	Int16 m1E;
	Int16 m20;
	Int16 m22;
	Int16 mBGVUnit;
	Int16 mBGHUnit;
	Int16 mSkyVSize;
	Int16 mSkyHSize;
	Int16 m2C;
	Int16 mNumOfGradeDef;
	GradeDef mGradeDef[8];
	ResIDT mOffSkyResID;
	ResIDT mOffBackObjResID;
	ResIDT mOffSideObjResID[2];
	ResIDT mOffBuildPrcResID;
	ResIDT mOffOptionResID;
	ResIDT mMysteryResIDBC;
	ResIDT mBE;
	ResIDT mMysteryResIDC0;
	ResIDT mMysteryResIDArrayC2[5];
	Byte mCC[20];
	Byte gapToEC[0xEC - 0xE0];
	CTabHandle mCTabH;
	T2GWorld *mOffSky;
	T2GWorld *mOffBackObj;
	T2GWorld *mOffSideObj[2];
	T2GWorld *mOffBuildPrc;
	T2GWorld *mOffOption;
	T2GWorld *mMysteryGWorldBC;
	T2GWorld *mMysteryGWorldC0;
	Int16 mMysteryGWorldC0_Height;
	Int16 mMysteryGWorldC0_Width;
	T2GWorld *mMysteryGWorldArrayC2[5];
	T2PoolDef *mPoolDef;
	Int32 m12C[4];
	Int32 m13C[4];
	T2WordDefArray *mWordDefArray;
	Int16 m150;
	Int16 m152;
	Rect mBuildArea;
	Int16 m15C;
	Int16 m15E;
	Int16 m160;
	ResIDT mMysteryResID162;
	T2PaletteAnimeDef *mPaletteAnimeDef;
	T2SeasonParamDef *mSeasonParamDef;
	T2GWorld *mMysteryGWorld162;
	Byte mDustOnThreshold;
	Byte mToiletVar1;
	Byte mToiletVar2;
	T2ColdTableDef *mColdTableDef;
	Int16 m178;
	T2TowerEvent *mTowerEvent;
	UInt32 m180[8];
};
