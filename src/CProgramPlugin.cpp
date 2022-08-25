#include "CDefRsrcPlugin.h"
#include "CProgramPlugin.h"
#include "UPluginLoader.h"

#include <LString.h>
#include <MixedMode.h>
#include <UException.h>

// TODO find me
struct ParsedCfrgEntry {
	UInt32 codeType, updateLevel, currentVersion, oldDefVersion, stackSize;
	Int16 libDir, fragType, fragLoc;
	UInt32 offset, length;
	Str255 name;
};
struct ParsedCfrg {
	UInt32 version;
	Int32 numberOfFrags;
	ParsedCfrgEntry entries[1];
};

extern "C" void Parse_cfrg(Handle, ParsedCfrg **);

CProgramPlugin::CProgramPlugin(UInt32 id, const FSSpec &spec)
	: CFilePlugin(id, spec)
{
	mLoadMode = 0;
	mProcRelated = 0;
	mToolResource = 0;
	mToolFragmentConnId = 0;
	mTemplatePlugin = 0;
	mToolFragmentMainAddr = 0;
	mUnloadProc = 0;
	mIdleProc = 0;
	mDrawProc = 0;
	mDrawGhostProc = 0;
	GetLoaderInfo();
}

CProgramPlugin::~CProgramPlugin() {
	if (mTemplatePlugin)
		delete mTemplatePlugin;
}

void CProgramPlugin::GetInfoString(LString &str) {
	LStr255 tmp = mId;
	LStr255 inRsrc = "InRsrc ";
	LStr255 inData = "InData ";
	LStr255 inUnknown = "InUnknown ";
	LStr255 loaded = "Loaded";
	LStr255 notLoaded = "NotLoaded";

	str = tmp;
	GetName(tmp);
	str.Append(tmp);

	if (mLoadMode == 2)
		str.Append(inRsrc);
	else if (mLoadMode == 3)
		str.Append(inData);
	else
		str.Append(inUnknown);

	if (mUnloadProc)
		str.Append(loaded);
	else
		str.Append(notLoaded);
}

OSErr CProgramPlugin::OpenResourceFork(Int16 permissions) {
	#line 125
	ThrowIfNil_(mFile);

	return mFile->OpenResourceFork(permissions);
}

void CProgramPlugin::CloseResourceFork() {
	#line 139
	ThrowIfNil_(mFile);

	mFile->CloseResourceFork();
}

Handle CProgramPlugin::GetSound(ResIDT id) {
	OpenResourceFork(1);
	Handle res = ::Get1Resource('snd ', id);
	if (res)
		::DetachResource(res);
	CloseResourceFork();
	return res;
}

OSErr CProgramPlugin::LoadSelf() {
	OSErr err = noErr;

	switch (mLoadMode) {
		case 2:
			err = LoadFromResource();
			break;
		case 3:
			err = LoadViaCFM();
			break;
	}

	if (err == noErr)
		err = InitializeTool();

	return err;
}

OSErr CProgramPlugin::UnloadSelf() {
	OSErr err = noErr;

	if (mUnloadProc)
		mUnloadProc(this);

	if (UPluginLoader::sHasCFM && mToolFragmentConnId) {
		CFragConnectionID connID = mToolFragmentConnId;
		err = ::CloseConnection(&connID);
	}

	if (mLoadMode == 2)
		::DisposeHandle(mToolResource);

	mUnloadProc = 0;
	mToolFragmentConnId = 0;
	mToolResource = 0;

	return err;
}

void CProgramPlugin::DrawProc(T2HaveOutViewObject *obj, const Rect &rect, T2TowerDoc *doc) {
	if (mDrawProc)
		mDrawProc(this, doc, obj, rect);
}

void CProgramPlugin::DrawGhostProc(T2Equip *equip, T2GWorld *gworld) {
	if (mDrawGhostProc)
		mDrawGhostProc(this, equip, gworld);
}

Int32 CProgramPlugin::IdleProc(T2TowerDoc *doc, T2HaveOutViewObject *obj) {
	Int32 result = -1;

	if (mIdleProc)
		result = mIdleProc(this, doc, obj);

	return result;
}

void CProgramPlugin::GetLoaderInfo() {
	OSErr code = noErr;
	OSErr tmpErr;

	try {
		tmpErr = mFile->OpenResourceFork(1);

		Handle res = ::Get1IndResource('TOOL', 1);
		if (res) {
			mLoadMode = 2;
			mProcRelated = 0;
		}

		if (UPluginLoader::sHasCFM) {
			ParsedCfrg **cfrgH = (ParsedCfrg **) ::NewHandleClear(300);
			#line 319
			ThrowIfMemError_();

			res = ::Get1Resource('cfrg', 0);
			#line 322
			ThrowIfResError_();

			Parse_cfrg(res, cfrgH);

			if ((*cfrgH)->entries[0].codeType == 'pwpc')
				mProcRelated = 1;
			else
				mProcRelated = 0;

			Int16 fragLoc = (*cfrgH)->entries[0].fragLoc;
			if (fragLoc == 1)
				mLoadMode = 3;
			else if (fragLoc == 0)
				mLoadMode = 2;

			::DisposeHandle((Handle) cfrgH);
		}
	} catch (ExceptionCode e) {
		code = e;
	}

	mFile->CloseResourceFork();

	#line 347
	ThrowIfOSErr_(code);
}

OSErr CProgramPlugin::LoadFromResource() {
	OSErr err = noErr; // r25
	ResIDT resID = (mProcRelated == 1) ? 1 : 0; // r22
	OSErr tmpErr;
	Str255 errMsg;
	CFragConnectionID connID;
	Ptr mainAddr;

	try {
		tmpErr = mFile->OpenResourceFork(0);
		#line 373
		ThrowIfResError_();

		Handle tool = ::Get1Resource('TOOL', resID); // r23
		#line 376
		ThrowIfResError_();

		::DetachResource(tool);
		::MoveHHi(tool);
		::HLock(tool);

		if (mProcRelated == 1) {
			LStr255 name;
			GetName(name);

			err = ::GetMemFragment(*tool, 0, name, kPrivateCFragCopy, &connID, &mainAddr, errMsg);
			#line 387
			ThrowIfOSErr_(err);
		} else {
			connID = 0;
			mainAddr = *tool;
		}

		mToolResource = tool;
		mToolFragmentConnId = connID;
		mLoadMode = 2;
		mToolFragmentMainAddr = mainAddr;
	} catch (ExceptionCode code) {
		err = code;
	}

	mFile->CloseResourceFork();
	return err;
}

OSErr CProgramPlugin::LoadViaCFM() {
	OSErr err = noErr; // r26

	Str255 errMsg;
	CFragConnectionID connID;
	Ptr mainAddr;

	try {
		if (!UPluginLoader::sHasCFM)
			#line 424
			ThrowIfOSErr_(2);

		FSSpec spec;
		mFile->GetSpecifier(spec);

		err = ::GetDiskFragment(&spec, 0, 0, spec.name, kPrivateCFragCopy, &connID, &mainAddr, errMsg);
		#line 429
		ThrowIfOSErr_(err);

		mToolResource = 0;
		mToolFragmentConnId = connID;
		mLoadMode = 3;
		mToolFragmentMainAddr = mainAddr;
	} catch (ExceptionCode code) {
		err = code;
	}

	return err;
}

OSErr CProgramPlugin::InitializeTool() {
	OSErr err = noErr;

	if (mToolFragmentMainAddr == 0)
		return 0;

	if (mProcRelated == 1) {
		err = ((LoadProcT) mToolFragmentMainAddr)(this);
	} else if (!UPluginLoader::sHasMixedMode) {
		err = 3;
	} else {
		UniversalProcPtr proc = NewRoutineDescriptor((ProcPtr) mToolFragmentMainAddr, 0xE1, mProcRelated);
		if (proc) {
			err = ((LoadProcT) proc)(this);
			DisposeRoutineDescriptor(proc);
		}
	}

	return err;
}

UInt32 CProgramPlugin::GetPluginStyle() {
	return 'prog';
}
