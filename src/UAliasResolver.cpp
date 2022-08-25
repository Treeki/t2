#include "UAliasResolver.h"
#include <Aliases.h>
#include <Resources.h>

Boolean UAliasResolver::IsAlias(const FSSpec &spec) {
	Boolean result = false;
	OSErr err;
	FInfo info;

	err = ::FSpGetFInfo(&spec, &info);
	if (err == noErr) {
		if (info.fdFlags & kIsAlias)
			result = true;
	}

	return result;
}

OSErr UAliasResolver::Resolve(FSSpec &spec) {
	OSErr result = -1;

	short oldResFile = ::CurResFile();
	short newResFile = ::FSpOpenResFile(&spec, 0);
	if (::ResError() == noErr) {
		Boolean wasChanged;
		::UseResFile(newResFile);
		result = ::ResolveAlias(&spec, (AliasHandle) ::Get1IndResource(rAliasType, 1), &spec, &wasChanged);
		if (wasChanged)
			::UpdateResFile(newResFile);
		::CloseResFile(newResFile);
		::UseResFile(oldResFile);
	}

	return result;
}

