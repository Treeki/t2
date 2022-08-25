#pragma once

#include <LTable.h>

class T2VerticalTable : public LTable {
public:
	T2VerticalTable(LStream *inStream);
	void Clear();
	Boolean FocusDraw(LPane *inSubPane);
	void DrawSelf();

protected:
	Boolean m98;
};
