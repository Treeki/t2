#pragma once

#include "CDefRsrcPlugin.h"
#include "T2DumpObj.h"

class CProgramPlugin;
class T2GWorld;
class T2Object;

class T2TemplatePlugin : public CDefRsrcPlugin, public T2DumpObj {
public:
	T2TemplatePlugin(UInt32 id, LStream *stream, CProgramPlugin *programPlugin);
	~T2TemplatePlugin();

	OSErr OpenResourceFork(Int16 permissions);
	void CloseResourceFork();
	Boolean HasDrawProc() const;

	virtual Int32 GetSortKey();
	virtual Int16 InitObject(T2Object *obj);
	virtual Int32 DrawGWorld(T2GWorld *gworld, Int16 var);
	virtual void DrawRect(const Rect &rect);
	virtual void DrawPoint(const Point &point);

	CProgramPlugin *mProgramPlugin;
};
