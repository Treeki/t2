#pragma once

#include "CFilePlugin.h"

class CResourcePlugin : public CFilePlugin {
public:
	CResourcePlugin(UInt32 id, const FSSpec &spec);
	~CResourcePlugin();
	OSErr LoadSelf();
	OSErr UnloadSelf();

	UInt32 GetPluginStyle() { return 'rsrc'; }

protected:
	Handle mHandle;
};

