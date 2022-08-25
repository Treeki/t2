#include "UPluginLoader.h"
#include "UAliasResolver.h"
#include <Gestalt.h>
#include <LArrayIterator.h>
#include <UEnvironment.h>

CFilePluginDB UPluginLoader::sFilePluginDB;
FSSpec UPluginLoader::sPluginFolderFSSpec;
long UPluginLoader::sPluginFolderDirID;
short UPluginLoader::sPluginFolderVol;
Boolean UPluginLoader::sHasMixedMode;
Boolean UPluginLoader::sHasCFM;

Boolean UPluginLoader::InitPluginLoader(const Byte *a, const Byte *b) {
	OSErr err;
	Boolean ok = false;

	sHasCFM = UEnvironment::HasGestaltAttribute(gestaltCFMAttr, gestaltCFMPresent);
	sHasMixedMode = true;

	long dirID;
	err = ::HGetVol(NULL, &sPluginFolderVol, &dirID);
	if (err != noErr)
		return false;

	err = GetFolderDirID(dirID, b);
	if (err == noErr) {
		err = ::FSMakeFSSpec(sPluginFolderVol, sPluginFolderDirID, NULL, &sPluginFolderFSSpec);
		if (err == noErr) {
			ok = true;
		}
	}

	return ok;
}

int UPluginLoader::MakeAllFilePlugin(Func1Type func1, void *opaquePtr, Func2Type func2) {
	OSErr err;
	int pluginCount = 0;

	if (sPluginFolderVol == 0 || sPluginFolderDirID == 0 || func1 == NULL || func2 == NULL)
		return 0;

	CInfoPBPtr fileInfo = (CInfoPBPtr) ::NewPtrClear(sizeof(CInfoPBRec));
	err = ::MemError();
	if (err != noErr)
		return 0;

	char emptyName[32];
	emptyName[0] = 0;
	fileInfo->hFileInfo.ioNamePtr = (StringPtr) emptyName;
	fileInfo->hFileInfo.ioVRefNum = sPluginFolderVol;

	int dirIndex = 1;
	do {
		fileInfo->hFileInfo.ioFDirIndex = dirIndex;
		fileInfo->hFileInfo.ioDirID = sPluginFolderDirID;
		fileInfo->hFileInfo.ioACUser = 0;

		err = ::PBGetCatInfoSync(fileInfo);
		if (err == 0 && (fileInfo->hFileInfo.ioFlAttrib & ioDirMask) == 0) {
			if (func1(fileInfo, opaquePtr)) {
				FSSpec spec;
				::FSMakeFSSpec(sPluginFolderVol, sPluginFolderDirID, fileInfo->hFileInfo.ioNamePtr, &spec);

				if (UAliasResolver::IsAlias(spec))
					err = UAliasResolver::Resolve(spec);

				CFilePlugin *plugin = func2(fileInfo->hFileInfo.ioFlFndrInfo.fdType, spec);
				if (plugin != NULL) {
					pluginCount++;
					sFilePluginDB.Add(plugin);
				}
			}
		}

		dirIndex++;
	} while (err == noErr);

	::DisposePtr((Ptr) fileInfo);

	return pluginCount;
}

void UPluginLoader::DisposeAllFilePlugin() {
	LArrayIterator rootIter(sFilePluginDB);
	LArray *array;

	while (rootIter.Next(&array)) {
		if (array != NULL) {
			LArrayIterator subIter(*array);
			CFilePlugin *plugin;

			while (subIter.Next(&plugin)) {
				if (plugin != NULL)
					delete plugin;
			}

			delete array;
		}
	}
}

CFilePluginList *UPluginLoader::GetFilePluginList(UInt32 id) {
	return sFilePluginDB.GetFilePluginList(id);
}

CFilePluginList *UPluginLoader::MakeFilePluginList(CFilePlugin *plugin, UInt32 id) {
	UInt32 mask = plugin->GetStrangeMask();
	CFilePluginList *newList = NULL;
	CFilePluginList *list = sFilePluginDB.GetFilePluginList(id);

	if (list != NULL) {
		newList = new CFilePluginList(id);
		#line 222
		ThrowIfNULL_(newList);

		LArrayIterator iter(*list);
		CFilePlugin *iterPlugin;
		UInt32 iterID;

		while (iter.Next(&iterPlugin)) {
			iterID = iterPlugin->GetStrangeMask();;
			if ((mask & iterID) != 0)
				newList->Add(iterPlugin);
		}
	}

	return newList;
}

OSErr UPluginLoader::GetFolderDirID(long &dirID, ConstStringPtr name) {
	CInfoPBPtr fileInfo = (CInfoPBPtr) ::NewPtrClear(sizeof(CInfoPBRec));
	OSErr error = ::MemError();

	if (error != noErr)
		return error;

	fileInfo->hFileInfo.ioNamePtr = (StringPtr) name;
	fileInfo->hFileInfo.ioVRefNum = sPluginFolderVol;
	fileInfo->hFileInfo.ioFDirIndex = 0;
	fileInfo->hFileInfo.ioDirID = dirID;

	error = ::PBGetCatInfoSync(fileInfo);
	if (error == 0) {
		if (fileInfo->hFileInfo.ioFlAttrib & ioDirMask) {
			sPluginFolderDirID = fileInfo->hFileInfo.ioDirID;
			dirID = fileInfo->hFileInfo.ioDirID;
		} else {
			error = dirNFErr;
		}
	}

	::DisposePtr((Ptr) fileInfo);

	return error;
}
