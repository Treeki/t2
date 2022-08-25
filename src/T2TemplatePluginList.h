#pragma once

#include <LArray.h>
#include "T2TemplatePlugin.h"

class T2MoverDef;
class T2OutObjDef;
class T2PeopleDef;
class T2SilhouetteDef;
class T2TenantDef;
class T2ToolDef;
class T2TowerDoc;

class T2TemplatePluginList : public LArray {
public:
	T2TemplatePluginList(UInt32 id);
	~T2TemplatePluginList();

	void AllClear();
	void Regist(T2TemplatePlugin *plugin);
	void Add(T2TemplatePlugin *plugin);
	UInt32 GetItemCount();
	UInt32 CalcCategoryCount();
	T2TemplatePlugin *GetItemAt(long index);
	T2ToolDef *FindFloor();
	T2ToolDef *FindTenantDef(Int16 which);
	T2ToolDef *FindMoverDef(Int16 which);
	T2OutObjDef *FindOutObjDef(Int16 which);
	T2PeopleDef *FindPeopleDef(Int16 which);
	T2SilhouetteDef *FindSilhouette(Int16 which);
	void DispatchIdle(T2TowerDoc *doc);

	UInt32 GetID() { return mId; }

	UInt32 mId;
};
