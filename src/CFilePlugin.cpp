#include "CFilePlugin.h"

CFilePlugin::CFilePlugin(UInt32 id, const FSSpec &spec)
	: CPlugin(id)
{
	mFile = new LFile(spec);
	u4_a = 0;
	u4_b = 0;
	u4_c = 0;
	u2_a = 0;
	u2_b = 0;
	u2_c = 0;

#line 52
	Assert_(mFile != 0);

	Int16 refNum = mFile->OpenResourceFork(1);
	PLUGIN_ATTR **attr = (PLUGIN_ATTR **)::Get1Resource('Attr', 0x80);

	if (attr != NULL) {
		u4_a = (*attr)->u4_a;
		u4_b = (*attr)->u4_b;
		if ((*attr)->u4_c != '****')
			u4_c = (*attr)->u4_c;
		u2_a = (*attr)->u2_a;
		u2_b = (*attr)->u2_b;
		u2_c = (*attr)->u2_c;
		u2_d = (*attr)->u2_d;
		for (int i = 0; i < 64; i++)
			mName[i] = (*attr)->name[i];
	} else {
		LStr255 s = "\pAttribute not found";
		for (int i = 0; i < s.Length(); i++)
			mName[i] = s[i];
	}

	mFile->CloseResourceFork();
	unkC = 0;
}

CFilePlugin::~CFilePlugin() {
	Unload();

	if (mFile)
		delete mFile;
}

void CFilePlugin::SetFile(const FSSpec &spec) {
	if (mFile)
		delete mFile;
	mFile = new LFile(spec);
}

void CFilePlugin::SetFile(LFile *file) {
	if (mFile)
		delete mFile;
	mFile = file;
}

void CFilePlugin::GetName(LString &str) {
	if (mName[0] != 0) {
		str = mName;
	} else {
		if (mFile) {
			FSSpec spec;
			mFile->GetSpecifier(spec);
			str = spec.name;
		}
	}
}

CPluginInfo *CFilePlugin::GetPluginInfo() {
	FSSpec spec;
	mFile->GetSpecifier(spec);

	return new CPluginInfo(mId, u4_a, u2_c, u2_d, mName, spec.name, false);
}

OSErr CFilePlugin::Load() {
	OSErr err;

	if (mLoaded == 0) {
		err = LoadSelf();
		if (err == noErr)
			mLoaded = true;
		return err;
	} else {
		return noErr;
	}
}

OSErr CFilePlugin::Unload() {
	OSErr err;

	if (mLoaded != 0) {
		err = UnloadSelf();
		if (err == noErr)
			mLoaded = false;
		return err;
	} else {
		return noErr;
	}
}

OSErr CFilePlugin::LoadSelf() {
	return 0;
}

OSErr CFilePlugin::UnloadSelf() {
	return 0;
}
