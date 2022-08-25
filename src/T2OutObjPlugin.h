#pragma once

#include "T2ToolPlugin.h"

class CFilePluginList;
class CResourcePlugin;

class T2OutObjPlugin : public T2ToolPlugin {
public:
	T2OutObjPlugin(UInt32 id, const FSSpec &spec);
	~T2OutObjPlugin();

	CFilePluginList *GetSubPluginList();
	OSErr LoadAllTemplatePlugin(T2WorldDef *, Int16, T2TemplatePluginDB *);
	void Add(CResourcePlugin *plugin);
	void LoadT2OutObjDef(T2WorldDef *worldDef);
	Int32 AreaCheck2Proc(T2TowerDoc *doc, Rect &rect, UInt32 var, Boolean flag);
	Int32 DestructProc(T2TowerDoc *doc, T2HaveOutViewObject *obj, Point pt, Rect *rect);

	CFilePluginList *mSubPluginList;
};
