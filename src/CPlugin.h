#pragma once

#include <LString.h>

class CPlugin {
protected:
	UInt32 mId;
	Boolean mLoaded;

public:
	CPlugin(UInt32 id);
	virtual ~CPlugin();

	UInt32 GetID() { return mId; }
	virtual UInt32 GetPluginStyle();
	virtual void GetName(LString &str);
	virtual void GetInfoString(LString &str);
};
