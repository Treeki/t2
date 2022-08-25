#pragma once

#include <LTable.h>

class ABGWorldTable : public LTable {
public:
	ABGWorldTable(LStream *inStream);

	void DrawCell(const TableCellT &cell);
	void HiliteCell(const TableCellT &cell);
	void UnhiliteCell(const TableCellT &cell);

	virtual void DrawCellSelf(const TableCellT &cell, Int32 var) = 0;
};
