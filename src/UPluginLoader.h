#pragma once

#include "CFilePlugin.h"
#include "CFilePluginDB.h"

// PF P10CInfoPBRec Pv _ Uc
// Pv
// PF Ul RC6FSSpec _ P11CFilePlugin

class UPluginLoader {
public:
	typedef Boolean (*Func1Type) (CInfoPBPtr, void *);
	typedef CFilePlugin *(*Func2Type) (UInt32, const FSSpec &);

	static Boolean InitPluginLoader(const Byte *a, const Byte *b);
	static int MakeAllFilePlugin(Func1Type func1, void *opaquePtr, Func2Type func2);
	static void DisposeAllFilePlugin();
	static CFilePluginList *GetFilePluginList(UInt32 id);
	static CFilePluginList *MakeFilePluginList(CFilePlugin *plugin, UInt32 id);
	static OSErr GetFolderDirID(long &dirID, ConstStringPtr name);

	static CFilePluginDB sFilePluginDB;
	static FSSpec sPluginFolderFSSpec;
	static long sPluginFolderDirID;
	static short sPluginFolderVol;
	static Boolean sHasMixedMode;
	static Boolean sHasCFM;
};
