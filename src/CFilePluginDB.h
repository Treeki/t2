#pragma once

#include <LArray.h>
#include "CFilePluginList.h"

class CFilePluginDB : public LArray {
public:
	CFilePluginDB();
	~CFilePluginDB();

	void Add(CFilePlugin *plugin);
	CFilePluginList *GetFilePluginList(UInt32 id);
};
