#include "T2PeopleDef.h"
#include "T2TowerDoc.h"

#include <LStream.h>
#include <UException.h>

T2PeopleDef::T2PeopleDef(UInt32 id, LStream *stream, CProgramPlugin *programPlugin)
	: T2MatterDef(id, stream, programPlugin)
{
	(*stream) >> mSMax;
	(*stream) >> mSBlueLimit;
	(*stream) >> mSYellowLimit;
}

T2PeopleDef::~T2PeopleDef() {
}

void T2PeopleDef::GetName(LString &str) {
	str = (Int32) mMatterType;
}

Boolean T2PeopleDef::GetInfoSetupProc(T2TowerDoc *doc, T2People *people, T2PeopleInfoDialog *dialog) {
	// TODO: waiting on T2NameList, T2Name, T2People, T2ReturnStack, T2PeopleInfoDialog
	return false;
}

Boolean T2PeopleDef::GetInfoOKProc(T2TowerDoc *doc, T2People *people, T2PeopleInfoDialog *dialog) {
	// TODO: waiting on T2NameList, T2Name, T2People, T2ReturnStack, T2PeopleInfoDialog
	return false;
}

Int32 T2PeopleDef::DrawData(Int32 pos) {
	LStr255 str;
	Int16 p = T2MatterDef::DrawData(pos);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\p================================");

	p += 16;
	::MoveTo(10, p);
	::DrawString("\p======== for Stress ============");

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmSMax : ");
	str = (Int32) mSMax;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmSBlueLimit : ");
	str = (Int32) mSBlueLimit;
	::DrawString(str);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmSYellowLimit : ");
	str = (Int32) mSYellowLimit;
	::DrawString(str);

	return p;
}
