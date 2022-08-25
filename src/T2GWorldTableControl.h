#pragma once

#include "T2GWorldTable.h"

#include <LBroadcaster.h>

class T2GWorldTableControl : public T2GWorldTable, public LBroadcaster {
public:
	T2GWorldTableControl(LStream *inStream);
	~T2GWorldTableControl();
	void BroadcastValueMessage();
	MessageT GetValueMessage() const;
	void SetValueMessage(MessageT message);
	void SelectCell(const TableCellT &cell);

protected:
	MessageT mValueMessage;
};
