#pragma once

#include <LFile.h>
#include "CPlugin.h"
#include "CPluginInfo.h"

struct PLUGIN_ATTR {
	UInt32 u4_a, u4_b, u4_c;
	Int16 u2_a, u2_b, u2_c, u2_d;
	Str63 name;
};

class CFilePlugin : public CPlugin {
public:
	CFilePlugin(UInt32 id, const FSSpec &spec);
	~CFilePlugin();

	virtual CPluginInfo *GetPluginInfo();
	virtual OSErr LoadSelf();
	virtual OSErr UnloadSelf();

	void GetName(LString &str);
	void SetFile(const FSSpec &spec);
	void SetFile(LFile *file);
	OSErr Load();
	OSErr Unload();

	LFile *GetFile() {
		return mFile;
	}
	UInt32 GetStrangeID() {
		return u4_a;
	}
	UInt32 GetStrangeMask() {
		return u4_b;
	}

	UInt32 u4_b, u4_c;
	Int16 u2_a;
	UInt32 unkC;
	Int16 u2_b, u2_c, u2_d;
	Str63 mName;
	LFile *mFile;
	UInt32 u4_a;
};
