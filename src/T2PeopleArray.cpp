#include "T2PeopleArray.h"
#include "T2TowerDoc.h"

T2PeopleArray::T2PeopleArray(UInt32 startID)
	: T2ObjectArray(startID)
{
	for (UInt32 i = 0; i < 256; i++) {
		mPeople[i].mMatterID = mStartID + i;
	}
}

T2People *T2PeopleArray::FindPeople(UInt32 id) {
	UInt32 firstID = mPeople[0].GetPeopleID();
	if (firstID > id || (firstID + 256) < id) {
		return 0;
	} else {
		for (UInt32 i = 0; i < 256; i++) {
			if (id == mPeople[i].GetPeopleID())
				return &mPeople[i];
		}
		return 0;
	}
}

void T2PeopleArray::ResolveLink(T2PeopleArrayList *list) {
	for (UInt32 i = 0; i < 256; i++) {
		if (mPeople[i].IsUsed())
			mPeople[i].ResolveLink(list);
	}
}

T2People *T2PeopleArray::FindUnusedPeople() {
	T2People *result = 0;

	for (UInt32 i = 0; i < 256; i++) {
		if (!mPeople[i].IsUsed()) {
			result = &mPeople[i];
			break;
		}
	}

	return result;
}

void T2PeopleArray::DispatchIdle(T2TowerDoc *doc, Int32 var) {
	for (UInt32 i = var; i < 256; i += 8) {
		if (mPeople[i].mUsed)
			mPeople[i].Idle(doc);
	}

	Int32 walkRate = doc->mWalkRate;
	for (UInt32 i = 0; i < 256; i++) {
		if (mPeople[i].mUsed) {
			if (mPeople[i].IsSetSpecialFlag(0x20) || (walkRate > 0 && (i % walkRate) == 0)) {
				mPeople[i].IdleSearchedPerson(doc);
			}
		}
	}
}

void T2PeopleArray::DrawSearchedPerson(T2TowerDoc *doc) {
	for (UInt32 i = 0; i < 256; i++) {
		if (mPeople[i].IsUsed() && mPeople[i].IsWalk()) {
			mPeople[i].DrawSearchedPerson(doc);
		}
	}
}

void T2PeopleArray::SetWalkPeople(Int16 var) {
	for (UInt32 i = 0; i < 256; i++) {
		mPeople[i].SetWalk(false);
	}

	if (var != -1) {
		for (UInt32 i = 0; i < 256; i += var) {
			mPeople[i].SetWalk(true);
		}
	}
}

void T2PeopleArray::DayChanged() {
	for (UInt32 i = 0; i < 256; i++) {
		if (mPeople[i].IsUsed())
			mPeople[i].DayChanged();
	}
}

void T2PeopleArray::TenantRemoved(UInt16 var) {
	for (UInt32 i = 0; i < 256; i++) {
		if (mPeople[i].IsUsed())
			mPeople[i].TenantRemoved(var);
	}
}

void T2PeopleArray::AddStress(Int16 var) {
	for (UInt32 i = 0; i < 256; i++) {
		if (mPeople[i].IsUsed())
			mPeople[i].IncStress(var);
	}
}

void T2PeopleArray::BreakoutEmergency(T2TowerDoc *doc) {
	for (UInt32 i = 0; i < 256; i++) {
		T2People *people = &mPeople[i];
		if (people->IsUsed())
			people->BreakoutEmergency(doc);
	}
}

void T2PeopleArray::Read(LStream &stream, T2TowerDoc *doc) {
	for (UInt32 i = 0; i < 256; i++) {
		mPeople[i].Load(stream, doc);
	}
}

void T2PeopleArray::Write(LStream &stream) {
	for (UInt32 i = 0; i < 256; i++) {
		mPeople[i].Save(stream);
	}
}
