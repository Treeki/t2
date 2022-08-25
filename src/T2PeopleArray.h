#pragma once

#include "T2ObjectArray.h"
#include "T2People.h"

class T2PeopleArray : public T2ObjectArray {
public:
	T2PeopleArray(UInt32 startID);
	T2People *FindPeople(UInt32 id);
	void ResolveLink(T2PeopleArrayList *list);
	T2People *FindUnusedPeople();
	void DispatchIdle(T2TowerDoc *doc, Int32 var);
	void DrawSearchedPerson(T2TowerDoc *doc);
	void SetWalkPeople(Int16 var);
	void DayChanged();
	void TenantRemoved(UInt16 var);
	void AddStress(Int16 var);
	void BreakoutEmergency(T2TowerDoc *doc);
	void Read(LStream &stream, T2TowerDoc *doc);
	void Write(LStream &stream);

	T2People mPeople[256];
};
