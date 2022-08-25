#pragma once

#include "CProgramPlugin.h"

class LDialogBox;
class T2Equip;
class T2GWorld;
class T2HaveOutViewObject;
class T2ToolDef;
class T2ToolPlugin;

typedef void (*DefIdleProcT)(T2ToolPlugin *, T2TowerDoc *);
typedef Boolean (*ClickProcT)(T2ToolPlugin *, T2TowerDoc *, Int16 &, Point, Rect *, Boolean);
typedef void (*ConstrainMouseProcT)(T2ToolPlugin *, Rect *, Rect *);
typedef Int32 (*AreaCheckProcT)(T2ToolPlugin *, T2TowerDoc *, Rect *, Rect *, T2Equip *);
typedef Int32 (*AreaCheck2ProcT)(T2ToolPlugin *, T2TowerDoc *, Rect &, UInt32, Boolean);
typedef Int32 (*DoBuildProcT)(T2ToolPlugin *, T2TowerDoc *, T2ToolDef *, Rect *);
typedef void (*BuildFinishProcT)(T2ToolPlugin *, T2TowerDoc *, T2HaveOutViewObject *);
typedef void (*BuildOptionProcT)(T2ToolPlugin *, T2TowerDoc *, T2Equip *);
typedef Int32 (*DestructProcT)(T2ToolPlugin *, T2TowerDoc *, T2HaveOutViewObject *, Point, Rect *);
typedef void (*DestructFinishProcT)(T2ToolPlugin *, T2TowerDoc *, T2HaveOutViewObject *);
typedef Int32 (*GetDestructPartProcT)(T2ToolPlugin *, Int16, Point, Point, T2Equip *);
typedef Int32 (*MakeCursorProcT)(T2ToolPlugin *, T2WorldDef *, T2GWorld **, Int16);
typedef Int32 (*GetInfoSetupProcT)(T2ToolPlugin *, T2TowerDoc *, T2HaveOutViewObject *, LDialogBox *);
typedef Int32 (*GetInfoOKProcT)(T2ToolPlugin *, T2TowerDoc *, T2HaveOutViewObject *, LDialogBox *);
typedef Int32 (*GetInfoCancelProcT)(T2ToolPlugin *, T2TowerDoc *, T2HaveOutViewObject *, LDialogBox *);
typedef Int32 (*GetInfoListenProcT)(T2ToolPlugin *, T2TowerDoc *, T2HaveOutViewObject *, LDialogBox *, MessageT, void *);
typedef Int16 (*IsAbleDragMakingProcT)(T2ToolPlugin *, Int16);
typedef void (*LoadExtraDataProcT)(T2ToolPlugin *, LStream &, T2TowerDoc *, T2HaveOutViewObject *);
typedef void (*SaveExtraDataProcT)(T2ToolPlugin *, LStream &, T2HaveOutViewObject *);
typedef Int32 (*CalcMentenanceCostProcT)(const T2ToolPlugin *, const T2HaveOutViewObject *);

class T2ToolPlugin : public CProgramPlugin {
public:
	T2ToolPlugin(UInt32 id, const FSSpec &spec);
	~T2ToolPlugin();

	virtual UInt32 GetSubPluginType();
	OSErr LoadAllTemplatePlugin(T2WorldDef *, Int16, T2TemplatePluginDB *);
	void DefIdleProc(T2TowerDoc *doc);
	Boolean ClickProc(T2TowerDoc *doc, Int16 &s, Point pt, Rect *rect, Boolean flag);
	virtual void ConstrainMouseProc(Rect *rectA, Rect *rectB);
	virtual Int32 AreaCheckProc(T2TowerDoc *doc, Rect *rectA, Rect *rectB, T2Equip *equip);
	virtual Int32 AreaCheck2Proc(T2TowerDoc *doc, Rect &rect, UInt32 var, Boolean flag);
	Int32 DoBuildProc(T2TowerDoc *doc, T2ToolDef *toolDef, Rect *rect);
	virtual void BuildFinishProc(T2TowerDoc *doc, T2HaveOutViewObject *obj);
	virtual void BuildOptionProc(T2TowerDoc *doc, T2Equip *equip);
	virtual Int32 DestructProc(T2TowerDoc *doc, T2HaveOutViewObject *obj, Point pt, Rect *rect);
	virtual Int32 GetDestructPartProc(Int16 var, Point ptA, Point ptB, T2Equip *equip);
	virtual void DestructFinishProc(T2TowerDoc *doc, T2HaveOutViewObject *obj);
	virtual Int32 GetInfoSetupProc(T2TowerDoc *doc, T2HaveOutViewObject *obj, LDialogBox *dialog);
	virtual Int32 GetInfoOKProc(T2TowerDoc *doc, T2HaveOutViewObject *obj, LDialogBox *dialog);
	virtual Int32 GetInfoCancelProc(T2TowerDoc *doc, T2HaveOutViewObject *obj, LDialogBox *dialog);
	virtual Int32 GetInfoListenProc(T2TowerDoc *doc, T2HaveOutViewObject *obj, LDialogBox *dialog, MessageT message, void *ioParam);
	Int16 IsAbleDragMakingProc(T2ToolDef *toolDef, Int16 which);
	virtual Int32 CalcMentenanceCostProc(const T2HaveOutViewObject *obj) const;
	void LoadExtraData(LStream &stream, T2TowerDoc *doc, T2HaveOutViewObject *obj);
	void SaveExtraData(LStream &stream, T2HaveOutViewObject *obj);
	CPluginInfo *GetPluginInfo();
	Int32 MakeCursorProc(T2WorldDef *worldDef, T2GWorld **gworld, Int16 var);
	Int32 DefMakeCursorProc(T2WorldDef *worldDef, T2GWorld **gworld, Int16 var);

	DefIdleProcT mDefIdleProc;
	ClickProcT mClickProc;
	ConstrainMouseProcT mConstrainMouseProc;
	AreaCheckProcT mAreaCheckProc;
	AreaCheck2ProcT mAreaCheck2Proc;
	DoBuildProcT mDoBuildProc;
	BuildFinishProcT mBuildFinishProc;
	BuildOptionProcT mBuildOptionProc;
	DestructProcT mDestructProc;
	DestructFinishProcT mDestructFinishProc;
	GetDestructPartProcT mGetDestructPartProc;
	MakeCursorProcT mMakeCursorProc;
	GetInfoSetupProcT mGetInfoSetupProc;
	GetInfoOKProcT mGetInfoOKProc;
	GetInfoCancelProcT mGetInfoCancelProc;
	GetInfoListenProcT mGetInfoListenProc;
	IsAbleDragMakingProcT mIsAbleDragMakingProc;
	LoadExtraDataProcT mLoadExtraDataProc;
	SaveExtraDataProcT mSaveExtraDataProc;
	CalcMentenanceCostProcT mCalcMentenanceCostProc;
};
