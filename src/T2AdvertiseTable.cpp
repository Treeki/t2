#include "CFilePluginList.h"
#include "T2AdvertisePlugin.h"
#include "T2AdvertiseTable.h"

#include <LArrayIterator.h>
#include <LString.h>
#include <UDrawingState.h>

T2AdvertiseTable::T2AdvertiseTable(LStream *inStream)
	: T2VerticalTable(inStream)
{
	m98 = true;
}

void T2AdvertiseTable::Add(T2AdvertisePlugin *plugin, Boolean select) {
	TableIndexT index = mRows;
	InsertRows(1, index, &plugin);

	if (mCols == 1)
		InsertCols(1, mCols, 0);

	SetMark(mRows, select);
	if (select) {
		TableCellT cell;
		cell.row = mRows;
		cell.col = 1;
		SelectCell(cell);
	}
}

void T2AdvertiseTable::Add(CFilePluginList *list) {
	OSType wantedType = GetUserCon();

	LArrayIterator iter(*list);
	T2AdvertisePlugin *plugin;

	while (iter.Next(&plugin)) {
		if (wantedType == plugin->GetSubType() && !plugin->IsTieupFinish())
			Add(plugin, false);
	}
}

void T2AdvertiseTable::DrawCell(const TableCellT &cell) {
	Rect cellFrame;
	if (FetchLocalCellFrame(cell, cellFrame) && cell.col == 1) {
		T2AdvertisePlugin *plugin;
		GetCellData(cell, &plugin);
		if (plugin) {
			OSType uc = GetUserCon();

			StTextState state;
			::TextFont(1);
			::TextSize(12);

			::MoveTo(cellFrame.left + 4, cellFrame.bottom - 5);
			if (uc == 'CFPI') {
				if (IsMark(cell.row))
					::DrawChar(shadow | italic);
				::MoveTo(cellFrame.left + 20, cellFrame.bottom - 5);
			}

			LStr255 str;
			plugin->GetTitle(str);
			::DrawString(str);
		}
	}
}

void T2AdvertiseTable::ClickCell(const TableCellT &cell, const SMouseDownEvent &event) {
	LTable::ClickCell(cell, event);
	if (IsValidCell(mSelectedCell) && mSelectedCell.col == 1) {
		T2AdvertisePlugin *plugin;
		GetCellData(mSelectedCell, &plugin);
		if (plugin) {
			BroadcastMessage(-mPaneID, plugin);
		}
	}
}

Boolean T2AdvertiseTable::IsMark(UInt32 index) {
	void *markData = 0;
	TableCellT cell;
	cell.row = index;
	cell.col = 2;
	GetCellData(cell, &markData);
	return (markData != 0);
}

void T2AdvertiseTable::SetMark(UInt32 index, Boolean mark) {
	void *markData = mark ? this : 0;

	TableCellT cell;
	cell.row = index;
	cell.col = 2;
	SetCellData(cell, &markData);
	Refresh();
}
