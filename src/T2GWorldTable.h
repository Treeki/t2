#pragma once

#include "ABGWorldTable.h"

class T2GWorld;

class T2GWorldTable : public ABGWorldTable {
public:
	T2GWorldTable(LStream *inStream);
	~T2GWorldTable();
	void FinishCreateSelf();
	void DrawCellSelf(const TableCellT &cell, Int32 var);

protected:
	T2GWorld *mGWorlds[3];
	TableCellT mInitialCell;
};
