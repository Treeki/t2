#include "CDefRsrcPlugin.h"

CDefRsrcPlugin::CDefRsrcPlugin(UInt32 id, LStream *stream)
	: CPlugin(id)
{
}

CDefRsrcPlugin::~CDefRsrcPlugin() {
}

UInt32 CDefRsrcPlugin::GetPluginStyle() {
	return 'rplg';
}
