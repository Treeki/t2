#pragma once

#include "CPlugin.h"
#include <LStream.h>

class CDefRsrcPlugin : public CPlugin {
public:
	CDefRsrcPlugin(UInt32 id, LStream *stream);
	virtual ~CDefRsrcPlugin();

	UInt32 GetPluginStyle();
};

