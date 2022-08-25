#pragma once

#include <LBroadcaster.h>
#include <LTable.h>
#include "CFilePluginList.h"

class T2PluginTable : public LTable, public LBroadcaster {
public:
	enum { class_ID = 'T2pt' };

	T2PluginTable(LStream *inStream);
	~T2PluginTable();

	void Add(CFilePluginList *list);
	void SelectCell(const TableCellT &inCell);

	static T2PluginTable *CreateT2PluginTableStream(LStream *inStream);

protected:
	void DrawCell(const TableCellT &inCell);
};
