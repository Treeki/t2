#pragma once

#include "ABGWorldTable.h"
#include "LScrollerPictButton.h"

class T2GWorld;
class T2PluginToolTable;
class T2ToolTable;
class T2TowerDoc;

class T2CategoryTable : public ABGWorldTable {
public:
	T2CategoryTable(LStream *inStream);
	~T2CategoryTable();

	Int16 GetCurrentCategory();
	Int16 CellToCategoryNo(const TableCellT &cell);
	Boolean CategoryNoToCell(Int16 category, TableCellT &cell) const;
	void SelectCell(const TableCellT &cell);
	void DrawCellSelf(const TableCellT &cell, Int32 var);
	void InitCategoryTable(T2TowerDoc *doc);
	void ClearTable();
	void SetCaption(Int16 category);
	void ClearCaption();
	void ClearSelectedCell();
	void SetupScrollerButton(LPictButton *upBtn, LPictButton *downBtn);
	T2GWorld *SetupHelp();
	Boolean IsCellEnabled(const TableCellT &cell);
	void EnableCategory(Int16 category, Boolean status);
	void ClickCell(const TableCellT &cell, const SMouseDownEvent &event);

protected:
	T2ToolTable *mToolTable;
	T2PluginToolTable *mPluginToolTable;
	Boolean mA0;
	LScrollerPictButton mScrollerPictButton;
	int mE4;
};
