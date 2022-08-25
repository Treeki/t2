#include "ABGWorldTable.h"

ABGWorldTable::ABGWorldTable(LStream *inStream)
	: LTable(inStream)
{
}

void ABGWorldTable::DrawCell(const TableCellT &cell) {
	if (EqualCell(cell, mSelectedCell))
		DrawCellSelf(cell, 1);
	else
		DrawCellSelf(cell, 0);
}

void ABGWorldTable::HiliteCell(const TableCellT &cell) {
	DrawCellSelf(cell, 1);
}

void ABGWorldTable::UnhiliteCell(const TableCellT &cell) {
	DrawCellSelf(cell, 0);
}
