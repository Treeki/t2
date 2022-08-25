#include "CPlugin.h"

CPlugin::CPlugin(UInt32 id) {
	mId = id;
	mLoaded = false;
}

CPlugin::~CPlugin() {
}

void CPlugin::GetName(LString &str) {
}

void CPlugin::GetInfoString(LString &str) {
}

UInt32 CPlugin::GetPluginStyle() {
	return 'plug';
}
