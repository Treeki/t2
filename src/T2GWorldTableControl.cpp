#include "T2GWorldTableControl.h"

#include <LStream.h>

T2GWorldTableControl::T2GWorldTableControl(LStream *inStream)
	: T2GWorldTable(inStream)
{
	inStream->ReadData(&mValueMessage, sizeof(mValueMessage));
}

T2GWorldTableControl::~T2GWorldTableControl() {
}

void T2GWorldTableControl::BroadcastValueMessage() {
	if (mValueMessage != 0) {
		TableCellT cell = mSelectedCell;
		BroadcastMessage(mValueMessage, &cell);
	}
}

MessageT T2GWorldTableControl::GetValueMessage() const {
	return mValueMessage;
}

void T2GWorldTableControl::SetValueMessage(MessageT message) {
	mValueMessage = message;
}

void T2GWorldTableControl::SelectCell(const TableCellT &cell) {
	if (!EqualCell(cell, mSelectedCell)) {
		LTable::SelectCell(cell);
		BroadcastValueMessage();
	}
}
