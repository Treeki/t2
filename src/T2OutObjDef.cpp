#include "T2OutObjDef.h"
#include "UDebugUtils.h"

#include <LString.h>

T2OutObjDef::T2OutObjDef(UInt32 id, LStream *stream, T2WorldDef *worldDef, T2OutObjPlugin *outObjPlugin)
	: T2ToolDef(id, stream, worldDef, outObjPlugin)
{
	mTenantDef = 0;
	mLoaded = true;
}

T2OutObjDef::~T2OutObjDef() {
}

Int32 T2OutObjDef::DrawData(Int32 pos) {
	LStr255 tmp;
	Int16 p = T2ToolDef::DrawData(pos);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\p================================");

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmTenantDef : ");
	UDebugUtils::HexString(&mTenantDef, tmp);
	::DrawString(tmp);

	return p;
}

Boolean T2OutObjDef::IsOutObj() {
	return true;
}
