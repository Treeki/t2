#pragma once

#include <LArray.h>
#include "T2TemplatePluginList.h"

class T2TemplatePluginDB : public LArray {
public:
	T2TemplatePluginDB();
	~T2TemplatePluginDB();

	void Regist(T2TemplatePlugin *plugin);
	void Add(T2TemplatePluginList *list);
	T2TemplatePluginList *GetTemplatePluginList(UInt32 id);
	T2TemplatePlugin *FindFloor();
};
