#pragma once

#include "T2ToolDef.h"
#include "T2OutObjPlugin.h"

class T2TenantDef;

class T2OutObjDef : public T2ToolDef {
public:
	T2OutObjDef(UInt32 id, LStream *stream, T2WorldDef *worldDef, T2OutObjPlugin *outObjPlugin);
	~T2OutObjDef();
	Int32 DrawData(Int32 pos);
	Boolean IsOutObj();

	T2TenantDef *mTenantDef;
};
