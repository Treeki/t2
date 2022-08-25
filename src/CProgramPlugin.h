#pragma once

#include "CFilePlugin.h"

#include <CodeFragments.h>

class CDefRsrcPlugin;
class CProgramPlugin;
class T2Equip;
class T2GWorld;
class T2HaveOutViewObject;
class T2TemplatePluginDB;
class T2TowerDoc;
class T2WorldDef;

typedef OSErr (*LoadProcT)(CProgramPlugin *);
typedef void (*UnloadProcT)(CProgramPlugin *);
typedef void (*DrawProcT)(CProgramPlugin *, T2TowerDoc *, T2HaveOutViewObject *, const Rect &);
typedef void (*DrawGhostProcT)(CProgramPlugin *, T2Equip *, T2GWorld *);
typedef Int32 (*IdleProcT)(CProgramPlugin *, T2TowerDoc *, T2HaveOutViewObject *);

class CProgramPlugin : public CFilePlugin {
public:
	CProgramPlugin(UInt32 id, const FSSpec &spec);
	~CProgramPlugin();
	void GetInfoString(LString &str);
	OSErr OpenResourceFork(Int16 permissions);
	void CloseResourceFork();
	Handle GetSound(ResIDT id);
	OSErr LoadSelf();
	OSErr UnloadSelf();

	virtual OSErr LoadAllTemplatePlugin(T2WorldDef *, Int16, T2TemplatePluginDB *) = 0;
	virtual void DrawProc(T2HaveOutViewObject *obj, const Rect &rect, T2TowerDoc *doc);
	void DrawGhostProc(T2Equip *equip, T2GWorld *gworld);
	virtual Int32 IdleProc(T2TowerDoc *doc, T2HaveOutViewObject *obj);

	void GetLoaderInfo();
	OSErr LoadFromResource();
	OSErr LoadViaCFM();
	OSErr InitializeTool();
	UInt32 GetPluginStyle();

	Boolean HasDrawProc() const { return mDrawProc != 0; }

// protected:
	CDefRsrcPlugin *mTemplatePlugin;
	UnloadProcT mUnloadProc;
	IdleProcT mIdleProc;
	DrawProcT mDrawProc;
	DrawGhostProcT mDrawGhostProc;
	Int16 mLoadMode;
	Int16 mProcRelated;
	Handle mToolResource;
	CFragConnectionID mToolFragmentConnId;
	Ptr mToolFragmentMainAddr;
};
