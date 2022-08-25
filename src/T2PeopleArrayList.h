#pragma once

#include <LArray.h>

#include "T2PeopleArray.h"

class T2PeopleArrayTable;

class T2PeopleArrayList : public LArray {
public:
	T2PeopleArrayList();
	~T2PeopleArrayList();

	void Add(T2PeopleArray *array);
	UInt32 GetItemCount();
	T2PeopleArray *GetItemAt(Int32 index);
	T2People *FindPeople(UInt32 id);
	T2People *FindUnusedPeople();
	void DispatchIdle(T2TowerDoc *doc);
	void DrawSearchedPerson(T2TowerDoc *doc);
	void SetWalkPeople(Int16 var);
	void DayChanged();
	void TenantRemoved(UInt16 var);
	void AddStress(Int16 var);
	void BreakoutEmergency(T2TowerDoc *doc);
	void Read(LStream &stream, T2TowerDoc *doc);
	void Write(LStream &stream);

	T2PeopleArrayTable *mPeopleArrayTable;
	Int32 mIdleCounter;
};
