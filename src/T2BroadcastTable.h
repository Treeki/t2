#pragma once

#include <LBroadcaster.h>
#include <LTable.h>

class T2BroadcastTable : public LTable, public LBroadcaster {
public:
	T2BroadcastTable(LStream *inStream);
};
