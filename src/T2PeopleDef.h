#pragma once

#include "T2MatterDef.h"

class T2People;
class T2PeopleInfoDialog;
class T2TowerDoc;

class T2PeopleDef : public T2MatterDef {
public:
	T2PeopleDef(UInt32 id, LStream *stream, CProgramPlugin *programPlugin);
	~T2PeopleDef();

	void GetName(LString &str);
	Boolean GetInfoSetupProc(T2TowerDoc *doc, T2People *people, T2PeopleInfoDialog *dialog);
	Boolean GetInfoOKProc(T2TowerDoc *doc, T2People *people, T2PeopleInfoDialog *dialog);
	Int32 DrawData(Int32 pos);

	Int16 mSMax;
	Int16 mSBlueLimit;
	Int16 mSYellowLimit;

	Int16 GetStressMax() const { return mSMax; }
	Int16 GetStressBlueLimit() const { return mSBlueLimit; }
	Int16 GetStressYellowLimit() const { return mSYellowLimit; }
};
