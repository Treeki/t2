#pragma once

#include "T2EquipPlugin.h"

class CFilePluginList;
class CResourcePlugin;
class T2People;
class T2Tenant;
class T2TenantPlugin;

//typedef void (*DrawOutViewProcT)(T2EquipPlugin *, T2TowerDoc *, T2Equip *, Rect &rect);
//typedef Int32 (*GetInfoDialogIDProcT)(T2EquipPlugin *, T2TowerDoc *, T2Equip *);
//typedef Int32 (*GetInfoProcT)(T2EquipPlugin *, T2TowerDoc *, T2Equip *);
//typedef Int32 (*EmergencyProcT)(T2EquipPlugin *, T2TowerDoc *, T2Equip *);
//typedef Int32 (*BurntDownProcT)(T2EquipPlugin *, T2TowerDoc *, T2Equip *);
typedef void (*BuildStartProcT)(T2TenantPlugin *, T2TowerDoc *, T2Tenant *);
typedef void (*EnterTenantProcT)(T2TenantPlugin *, T2TowerDoc *, T2Tenant *, T2People *);
typedef void (*LeaveTenantProcT)(T2TenantPlugin *, T2TowerDoc *, T2Tenant *, T2People *);
typedef Boolean (*GetQTMovieNameProcT)(T2TenantPlugin *, T2TowerDoc *, T2Tenant *, StringPtr);
typedef Boolean (*IsWithinSearchRangeProcT)(const T2TenantPlugin *, const T2TowerDoc *, const T2Tenant *, const T2Tenant *);

class T2TenantPlugin : public T2EquipPlugin {
public:
	T2TenantPlugin(UInt32 id, const FSSpec &spec);
	~T2TenantPlugin();

	void BuildStartProc(T2TowerDoc *doc, T2Tenant *tenant);
	Int32 TestLoadAllDefRsrcPlugin();
	OSErr LoadAllTemplatePlugin(T2WorldDef *worldDef, Int16 mask, T2TemplatePluginDB *);
	UInt32 GetSubPluginType();
	void Add(CResourcePlugin *plugin);
	void LoadT2TenantDef(T2WorldDef *worldDef);
	void LoadT2PeopleDef(T2TemplatePluginDB *db);
	void LoadT2SilhouetteDef(T2TemplatePluginDB *db);
	Int32 GetClickPartProc(T2TowerDoc *doc, T2Equip *equip, Point pt, Int16 *s);
	Int32 AreaCheck2Proc(T2TowerDoc *doc, Rect &rect, UInt32 var, Boolean flag);
	Int32 DestructProc(T2TowerDoc *doc, T2HaveOutViewObject *obj, Point pt, Rect *rect);
	void DestructFinishProc(T2TowerDoc *doc, T2HaveOutViewObject *obj);
	Int32 IdleProc(T2TowerDoc *doc, T2HaveOutViewObject *obj);
	Int32 CalcMentenanceCostProc(const T2HaveOutViewObject *obj) const;
	void EnterTenant(T2TowerDoc *doc, T2Tenant *tenant, T2People *people);
	void LeaveTenant(T2TowerDoc *doc, T2Tenant *tenant, T2People *people);
	Boolean GetQTMovieNameProc(T2TowerDoc *doc, T2Tenant *tenant, LString &str);
	Int32 EmergencyProc(T2TowerDoc *doc, T2Equip *equip);
	Boolean HasSearchRangeProc() const;
	Boolean IsWithinSearchRangeProc(const T2TowerDoc *doc, const T2Tenant *tenantA, const T2Tenant *tenantB) const;

	BuildStartProcT mBuildStartProc;
	void *mFC;
	void *m100;
	EnterTenantProcT mEnterTenantProc;
	LeaveTenantProcT mLeaveTenantProc;
	GetQTMovieNameProcT mGetQTMovieNameProc;
	IsWithinSearchRangeProcT mIsWithinSearchRangeProc;
	void *m114;
	void *m118;
	void *m11C;
	CFilePluginList *m120;
};
