#pragma once

#include "T2VerticalTable.h"

#include <LBroadcaster.h>

class CFilePluginList;
class T2AdvertisePlugin;

class T2AdvertiseTable : public T2VerticalTable, public LBroadcaster {
public:
	T2AdvertiseTable(LStream *inStream);
	void Add(T2AdvertisePlugin *plugin, Boolean select);
	void Add(CFilePluginList *list);
	void DrawCell(const TableCellT &cell);
	void ClickCell(const TableCellT &cell, const SMouseDownEvent &event);
	Boolean IsMark(UInt32 index);
	void SetMark(UInt32 index, Boolean mark);
};
