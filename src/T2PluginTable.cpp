#include "T2PluginTable.h"
#include <Icons.h>
#include <LArrayIterator.h>
#include <UDrawingUtils.h>
#include <UGAColorRamp.h>
#include <UTextTraits.h>

T2PluginTable *T2PluginTable::CreateT2PluginTableStream(LStream *inStream) {
	return new T2PluginTable(inStream);
}

T2PluginTable::T2PluginTable(LStream *inStream)
	: LTable(inStream)
{
}

T2PluginTable::~T2PluginTable() {
}

void T2PluginTable::Add(CFilePluginList *list) {
	TableIndexT index = mRows;

	if (list) {
		LArrayIterator iter(*list);
		CFilePlugin *plugin;
		while (iter.Next(&plugin)) {
			InsertRows(1, index, &plugin);
			index++;
		}
	}
}

void T2PluginTable::SelectCell(const TableCellT &inCell) {
	LTable::SelectCell(inCell);

	if (IsValidCell(mSelectedCell)) {
		CFilePlugin *plugin;
		GetCellData(mSelectedCell, &plugin);
		if (plugin != 0) {
			BroadcastMessage(1400, plugin);
		}
	}
}

void T2PluginTable::DrawCell(const TableCellT &inCell) {
	Rect cellFrame;
	if (!FetchLocalCellFrame(inCell, cellFrame))
		return;

	void *pluginPtr;
	CFilePlugin *plugin1;
	UInt32 pluginID;
	CFilePlugin *plugin2;

	Rect iconRect = cellFrame;
	iconRect.bottom = iconRect.top + 16;
	iconRect.left += 4;
	iconRect.right = iconRect.left + 16;

	GetCellData(inCell, &pluginPtr);
	if (!pluginPtr)
		return;

	short iconID;
	plugin2 = (CFilePlugin *) pluginPtr;
	pluginID = plugin2->mId;
	switch (pluginID) {
		case 'WdPI': iconID = 4041; break;
		case 'TnPI': iconID = 4042; break;
		case 'MvPI': iconID = 4043; break;
		case 'MoPI': iconID = 4045; break;
		case 'HePI': iconID = 4046; break;
		case 'SpPI': iconID = 4044; break;
		default: iconID = 4047;
	}

	::PlotIconID(&iconRect, 0, 0, iconID);

	LStr255 str;
	StTextState textState;
	((CFilePlugin *) pluginPtr)->GetName(str);

	::TextFont(1);
	::TextSize(9);

	::MoveTo(cellFrame.left + 26, cellFrame.bottom - 5);
	::DrawString(str);

	::MoveTo(cellFrame.left + 156, cellFrame.bottom - 5);
	plugin1 = (CFilePlugin *) pluginPtr;
	if (plugin1->mLoaded)
		str.Assign(1400, 1);
	else
		str.Assign(1400, 2);
	::DrawString(str);
}
