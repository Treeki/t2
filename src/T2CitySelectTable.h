#pragma once

#include <LBroadcaster.h>
#include <LTable.h>

class CFilePluginList;
class T2GWorld;

class T2CitySelectTable : public LTable, public LBroadcaster {
public:
	T2CitySelectTable(LStream *inStream);
	~T2CitySelectTable();
	void Add(CFilePluginList *list);
	Boolean FetchLocalCellFrame(const TableCellT &cell, Rect &rect);
	void DrawSelf();
	void DrawCell(const TableCellT &cell);
	void SelectCell(const TableCellT &cell);
	void HiliteCell(const TableCellT &cell);
	void UnhiliteCell(const TableCellT &cell);

	static void CalcIconRect(const Rect &inRect, Rect &outRect);
	static void GetCellPICTFrame(T2GWorld *gworld, Rect &rect);

	void DrawButton(const TableCellT &cell, Boolean selected);
	void DrawButtonShadow(Rect rect, Boolean selected) const;

protected:
	MessageT mClickMessage;
	MessageT mDoubleClickMessage;
};
