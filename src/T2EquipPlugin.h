#pragma once

#include "T2ToolPlugin.h"

class T2EquipPlugin;

typedef void (*DrawOutViewProcT)(T2EquipPlugin *, T2TowerDoc *, T2Equip *, Rect &rect);
typedef Int32 (*GetInfoDialogIDProcT)(T2EquipPlugin *, T2TowerDoc *, T2Equip *);
typedef Int32 (*GetInfoProcT)(T2EquipPlugin *, T2TowerDoc *, T2Equip *);
typedef Int32 (*EmergencyProcT)(T2EquipPlugin *, T2TowerDoc *, T2Equip *);
typedef Int32 (*BurntDownProcT)(T2EquipPlugin *, T2TowerDoc *, T2Equip *);

class T2EquipPlugin : public T2ToolPlugin {
public:
	T2EquipPlugin(UInt32 id, const FSSpec &spec);
	~T2EquipPlugin();

	void DrawOutViewProc(T2Equip *equip, const Rect &rect, T2TowerDoc *doc);
	Int32 GetInfoDialogIDProc(T2TowerDoc *doc, T2Equip *equip);
	Int32 GetInfoProc(T2TowerDoc *doc, T2Equip *equip);
	virtual Int32 GetClickPartProc(T2TowerDoc *doc, T2Equip *equip, Point pt, Int16 *s);
	virtual Int32 EmergencyProc(T2TowerDoc *doc, T2Equip *equip);
	virtual Int32 BurntDownProc(T2TowerDoc *doc, T2Equip *equip);

	DrawOutViewProcT mDrawOutViewProc;
	GetInfoDialogIDProcT mGetInfoDialogIDProc;
	GetInfoProcT mGetInfoProc;
	void *mEC;
	EmergencyProcT mEmergencyProc;
	BurntDownProcT mBurntDownProc;
};
