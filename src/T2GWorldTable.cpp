#include "T2GWorld.h"
#include "T2GWorldTable.h"

#include <LStream.h>
#include <UDrawingState.h>

T2GWorldTable::T2GWorldTable(LStream *inStream)
	: ABGWorldTable(inStream)
{
	for (int i = 0; i < 3; i++) {
		mGWorlds[i] = 0;

		ResIDT id;
		(*inStream) >> id;
		if (id != -1) {
			mGWorlds[i] = new T2GWorld(id, 8, 0, 0, 0);
		}
	}

	(*inStream) >> mInitialCell.row;
	(*inStream) >> mInitialCell.col;
}

T2GWorldTable::~T2GWorldTable() {
	for (int i = 0; i < 3; i++) {
		if (mGWorlds[i])
			delete mGWorlds[i];
	}
}

void T2GWorldTable::FinishCreateSelf() {
	LPane::FinishCreateSelf();

	if (mInitialCell.row != 0xFFFFFFFF && mInitialCell.col != 0xFFFFFFFF) {
		mSelectedCell = mInitialCell;
	}
}

void T2GWorldTable::DrawCellSelf(const TableCellT &cell, Int32 var) {
	if (mGWorlds[var]) {
		Rect cellFrame;
		if (FetchLocalCellFrame(cell, cellFrame)) {
			StColorPenState state;
			state.Normalize();

			Rect rect2 = cellFrame;
			mGWorlds[var]->CopyImage(UQDGlobals::GetCurrentPort(), cellFrame, cellFrame, 0, 0);
		}
	}
}
