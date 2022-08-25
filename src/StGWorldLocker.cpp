#include "StGWorldLocker.h"
#include <QDOffscreen.h>
#include <UDebugging.h>

StGWorldLocker::StGWorldLocker(T2GWorld *world) {
	mT2GWorld = world;
	#line 24
	Assert_(mT2GWorld != 0);
	::LockPixels(::GetGWorldPixMap(mT2GWorld->GetGWorld()));
}

StGWorldLocker::~StGWorldLocker() {
	::UnlockPixels(::GetGWorldPixMap(mT2GWorld->GetGWorld()));
}
