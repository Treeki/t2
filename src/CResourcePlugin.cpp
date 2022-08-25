#include "CResourcePlugin.h"

CResourcePlugin::CResourcePlugin(UInt32 id, const FSSpec &spec)
	: CFilePlugin(id, spec)
{
	mHandle = NULL;
}

CResourcePlugin::~CResourcePlugin() {
	if (mHandle != NULL)
		::DisposeHandle(mHandle);
}

OSErr CResourcePlugin::LoadSelf() {
	OSErr err = noErr;
	return err;
}

OSErr CResourcePlugin::UnloadSelf() {
	OSErr err = noErr;
	return err;
}
