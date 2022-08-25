#include "T2CategoryTable.h"
#include "T2GWorld.h"
#include "T2PluginToolTable.h"
#include "T2TowerDoc.h"

#include <UException.h>

T2CategoryTable::T2CategoryTable(LStream *inStream)
	: ABGWorldTable(inStream)
{
	mToolTable = 0;
	mPluginToolTable = 0;
	mE4 = 0;
	mA0 = 0;
}

T2CategoryTable::~T2CategoryTable() {
}

Int16 T2CategoryTable::GetCurrentCategory() {
	if (mA0)
		return CellToCategoryNo(mSelectedCell);
	else
		return 0;
}

Int16 T2CategoryTable::CellToCategoryNo(const TableCellT &cell) {
	Int16 result = -1;

	T2TowerDoc *doc = T2TowerDoc::GetCurrentT2TowerDoc();
	if (doc) {
		Int16 categoryCount = doc->GetCategoryCount();
		result = cell.row + (cell.col - 1) * mRows;
		if (result > categoryCount)
			result = -1;
	}

	return result;
}

Boolean T2CategoryTable::CategoryNoToCell(Int16 category, TableCellT &cell) const {
	Boolean result = false;

	TableCellT w;
	w.row = ((category - 1) % mRows) + 1;
	w.col = ((category - 1) / mRows) + 1;

	if (w.col != 0 && w.col <= mCols) {
		result = true;
		cell = w;
	}

	return result;
}

void T2CategoryTable::SelectCell(const TableCellT &cell) {
	// TODO, requires: T2ToolDefList, T2ToolWindow, T2ToolTable, T2PluginToolTable
}

void T2CategoryTable::DrawCellSelf(const TableCellT &cell, Int32 var) {
	if (var == 0 && !IsCellEnabled(cell))
		var = 2;

	Rect cellFrame;
	if (FetchLocalCellFrame(cell, cellFrame)) {
		Int16 category = CellToCategoryNo(cell);
		if (category != -1) {
			T2TowerDoc *doc = T2TowerDoc::GetCurrentT2TowerDoc();
			if (doc) {
				T2GWorld *world = doc->GetCategoryIcon(category);
				if (world) {
					static const Rect defaultRect = { 0, 0, 26, 26 };

					Rect r = defaultRect;
					for (int i = 0; i < var; i++) {
						::OffsetRect(&r, 0, 26);
					}

					world->CopyImage(GetMacPort(), r, cellFrame, 0, 0);
				}
			}
		}
	}
}

void T2CategoryTable::InitCategoryTable(T2TowerDoc *theDoc) {
	T2TowerDoc *doc;

	RemoveCols(mCols, 0);

	doc = theDoc;
	if (!doc)
		doc = T2TowerDoc::GetCurrentT2TowerDoc();

	if (doc) {
		int categoryCount = doc->GetCategoryCount();
		int toAdd = ((categoryCount - 1) / mRows) + 1;
		InsertCols(toAdd, 0, 0);
	}

	Refresh();
	mScrollerPictButton.RefreshButton();

	if (mPluginToolTable && IsValidCell(mSelectedCell)) {
		Int16 selected = CellToCategoryNo(mSelectedCell);
		if (selected != -1) {
			SetCaption(selected);
			mPluginToolTable->SelectChange(selected, 0);
		}
	}
}

void T2CategoryTable::ClearTable() {
	mA0 = 0;
	FocusDraw();
	UnhiliteCell(mSelectedCell);
	ClearSelectedCell();
	ClearCaption();
}

void T2CategoryTable::SetCaption(Int16 category) {
	// TODO
}

void T2CategoryTable::ClearCaption() {
	// TODO
}

void T2CategoryTable::ClearSelectedCell() {
	mSelectedCell.row = 0;
	mSelectedCell.col = 0;
}

void T2CategoryTable::SetupScrollerButton(LPictButton *upBtn, LPictButton *downBtn) {
	mScrollerPictButton.Setup(
		EScrollType_Horizontal,
		this,
		upBtn, 10000, 10001, 10002, EButtonState_Disabled,
		downBtn, 10010, 10011, 10012, EButtonState_Disabled
	);
}

T2GWorld *T2CategoryTable::SetupHelp() {
	T2GWorld *result = 0;
	Int16 category = CellToCategoryNo(mSelectedCell);

	if (category != -1) {
		T2TowerDoc *doc = T2TowerDoc::GetCurrentT2TowerDoc();
		if (doc) {
			result = doc->GetCategoryHelp(category);
		}
	}

	return result;
}

Boolean T2CategoryTable::IsCellEnabled(const TableCellT &cell) {
	#line 500
	Assert_(mCellData == 0 || mCellData->GetItemSize(1) == (1));

	Boolean result = true;

	if (mCellData) {
		Boolean status = true;
		GetCellData(cell, &status);
		result = status;
	}

	return result;
}

void T2CategoryTable::EnableCategory(Int16 category, Boolean status) {
	#line 515
	Assert_(mCellData == 0 || mCellData->GetItemSize(1) == (1));

	TableCellT cell;
	if (CategoryNoToCell(category, cell)) {
		Boolean data = status;
		SetCellData(cell, &data);

		Rect cellFrame;
		if (FetchLocalCellFrame(cell, cellFrame)) {
			LocalToPortPoint(topLeft(cellFrame));
			LocalToPortPoint(botRight(cellFrame));
			InvalPortRect(&cellFrame);
		}
	}
}

void T2CategoryTable::ClickCell(const TableCellT &cell, const SMouseDownEvent &event) {
	if (IsCellEnabled(cell))
		LTable::ClickCell(cell, event);
}

