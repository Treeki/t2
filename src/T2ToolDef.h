#pragma once

#include "T2TemplatePlugin.h"

class LDialogBox;
class LStream;
class T2DateTime;
class T2Equip;
class T2GWorld;
class T2HaveOutViewObject;
class T2TowerDoc;
class T2WorldDef;

enum {
	kMaxValiation = 4
};

class T2ToolDef : public T2TemplatePlugin {
public:
	T2ToolDef(UInt32 id, LStream *stream, T2WorldDef *worldDef, CProgramPlugin *programPlugin);
	void Initialize();
	~T2ToolDef();

	virtual Boolean IsMover() { return false; }
	virtual Boolean IsTenant() { return false; }
	virtual Boolean IsOutObj() { return false; }

	Int32 GetSortKey();
	void GetCategoryName(LStr255 &str);
	void GetToolName(LString &str, Int16 index);
	void GetName(LString &str, Int16 index);
	Int32 GetOutMoney(UInt32 index) const;
	void _SetOutMoney(UInt32 index, Int32 money);
	T2GWorld *GetOffscreen(UInt32 index) const;
	T2GWorld *GetCategoryHelpGWorld(T2WorldDef *worldDef);
	T2GWorld *GetToolHelpGWorld(T2WorldDef *worldDef, Int16 index);
	void DefIdleProc(T2TowerDoc *towerDoc);
	virtual void DrawProc(T2HaveOutViewObject *haveOutViewObject, const Rect &rect, T2TowerDoc *towerDoc);
	virtual Int32 IdleProc(T2HaveOutViewObject *haveOutViewObject, T2TowerDoc *towerDoc);
	virtual Boolean ClickProc(T2TowerDoc *towerDoc, Int16 &var, Point pt, Rect *rect, Boolean flag);
	Int32 AreaCheck(T2TowerDoc *towerDoc, Rect &rect, UInt32 var, Boolean flag);
	Int32 DoBuildProc(T2TowerDoc *towerDoc, Rect *rect);
	void BuildFinishProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject);
	void BuildOptionProc(T2TowerDoc *towerDoc, T2Equip *equip);
	virtual Int32 CalcPayment(T2TowerDoc *doc, Rect &rect, UInt32 index);
	Int32 GetConsumptionPower(UInt32 index);
	Int32 MakeCursorProc(T2WorldDef *worldDef, T2GWorld **world, Int16 var);
	virtual Int32 DestructProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject, Point pt, Rect &rect);
	virtual void DestructFinishProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject);
	virtual Int32 GetInfoSetupProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject, LDialogBox *dialog);
	virtual Int32 GetInfoOKProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject, LDialogBox *dialog);
	virtual Int32 GetInfoCancelProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject, LDialogBox *dialog);
	virtual Int32 GetInfoListenProc(T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject, LDialogBox *dialog, MessageT message, void *ioParam);
	Int16 IsAbleDragMaking(Int16 index);
	Int32 CalcMentenanceCostProc(const T2HaveOutViewObject *haveOutViewObject) const;
	void LoadExtraData(LStream &stream, T2TowerDoc *towerDoc, T2HaveOutViewObject *haveOutViewObject);
	void SaveExtraData(LStream &stream, T2HaveOutViewObject *haveOutViewObject);
	Int32 CalcSoundID(Int16 index) const;
	virtual Int32 DrawData(Int32 pos);
	virtual Int16 DrawAttribute(Int16 pos);

	Int16 GetToolNo() const { return mToolNo; }
	Int16 GetCategory() const { return mCategoryNo; }
	Int16 GetToolType() const { return mToolType; }
	Boolean IsSetAttribute(UInt32 attr) const {
		return (mAttribute & attr) ? true : false;
	}
	UInt32 GetSubPluginType() const { return mSubPluginType; }
	UInt32 GetAttribute() const { return mAttribute; }
	void DoStartUse() { mCurBuildCount++; }
	void DoEndUse() { mCurBuildCount--; }

	Int16 mToolType;
	Int16 mWidth;
	Int16 mHeight;
	Int16 mLevel;
	UInt32 mAttribute;
	Str63 mCategoryCommentString;
	Str63 mCategoryName;
	Int16 mCategoryNo;
	Int16 mToolNo;
	Int16 mAfterCategoryNo;
	Int16 mAfterToolNo;
	UInt32 mSubPluginType;
	T2GWorld *mCategoryIcon;
	ResIDT mCategoryHelpResID;
	Int16 mValiationCount;
	Int16 mB4;
	Str63 mPriceString[kMaxValiation];
	Str63 mOutMoneyString[kMaxValiation];
	Str63 mCommentString[kMaxValiation];
	Str63 mToolName[kMaxValiation];
	Str63 mName[kMaxValiation];
	Int32 mPrice[kMaxValiation];
	Int32 mOutMoney[kMaxValiation];
	T2GWorld *mToolIcon[kMaxValiation];
	T2GWorld *mOffscreen[kMaxValiation];
	ResIDT mToolHelpResID[kMaxValiation];
	Int16 mConsumptionPower[kMaxValiation];
	Int32 mCurBuildCount;
	ResIDT mOffscreenResIDs[kMaxValiation];
	Boolean mOffscreenExists[kMaxValiation];
	void *m618;
	T2DateTime *mToolQuietUntil;
	T2DateTime *mCategoryQuietUntil;
};
