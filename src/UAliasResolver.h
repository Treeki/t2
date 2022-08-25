#pragma once

#include <Files.h>

class UAliasResolver {
public:
	static Boolean IsAlias(const FSSpec &spec);
	static OSErr Resolve(FSSpec &spec);
};
