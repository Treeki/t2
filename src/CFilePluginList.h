#pragma once

#include <LArray.h>
#include "CFilePlugin.h"

class CFilePluginList : public LArray {
public:
	CFilePluginList(UInt32 id);
	~CFilePluginList();

	void AllClear();
	void Add(CFilePlugin *plugin);
	UInt32 GetItemCount();
	CFilePlugin *GetItemAt(long index);
	CFilePlugin *GetItem(UInt32 id);

	UInt32 GetID() { return mId; }

	UInt32 mId;
};
