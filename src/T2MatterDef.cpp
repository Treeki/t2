#include "T2MatterDef.h"
#include "T2TemplatePluginList.h"
#include "UDebugUtils.h"

#include <LStream.h>
#include <UException.h>

T2MatterDef::T2MatterDef(UInt32 id, LStream *stream, CProgramPlugin *programPlugin)
	: T2TemplatePlugin(id, stream, programPlugin)
{
	(*stream) >> mMatterType;
	(*stream) >> mAttribute;
	(*stream) >> mSilhouetteType;
	mSilhouetteDef = 0;
	mLoaded = true;
}

T2MatterDef::~T2MatterDef() {
}

void T2MatterDef::GetName(LString &str) {
	str = (Int32) mMatterType;
}

void T2MatterDef::AssignSilhouette(T2TemplatePluginList *list) {
	T2SilhouetteDef *theSilhouetteDef = list->FindSilhouette(mSilhouetteType);
	#line 104
	Assert_(theSilhouetteDef != 0);
	mSilhouetteDef = theSilhouetteDef;
}

Int32 T2MatterDef::DrawData(Int32 pos) {
	LStr255 str;
	Int16 p = pos;

	::MoveTo(10, p);
	::DrawString("\p================================");

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmMatterType : ");
	str = (Int32) mMatterType;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmAttribute : ");
	str = (Int32) mAttribute;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmSilhouetteType : ");
	str = (Int32) mSilhouetteType;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmSilhouetteDef : ");
	UDebugUtils::HexString(&mSilhouetteDef, str);
	::DrawString(str);

	return p;
}
