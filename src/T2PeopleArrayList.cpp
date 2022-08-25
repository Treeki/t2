#include "T2PeopleArrayList.h"

#include <LArrayIterator.h>
#include <LStream.h>

T2PeopleArrayList::T2PeopleArrayList()
	: LArray(sizeof(T2PeopleArray *))
{
	mIdleCounter = 0;
	mPeopleArrayTable = 0;

	T2PeopleArray *array = new T2PeopleArray(1);
	Add(array);
}

T2PeopleArrayList::~T2PeopleArrayList() {
	// TODO: T2PeopleArrayTable

	LArrayIterator iter(*this);
	T2PeopleArray *array;
	while (iter.Next(&array)) {
		delete array;
	}
}

void T2PeopleArrayList::Add(T2PeopleArray *array) {
	InsertItemsAt(1, index_Last, &array);
	//if (mPeopleArrayTable)
	//	mPeopleArrayTable->Add(array);
}

UInt32 T2PeopleArrayList::GetItemCount() {
	return mItemCount;
}

T2PeopleArray *T2PeopleArrayList::GetItemAt(Int32 index) {
	T2PeopleArray *array;
	if (!FetchItemAt(index, &array))
		array = 0;
	return array;
}

T2People *T2PeopleArrayList::FindPeople(UInt32 id) {
	LArrayIterator iter(*this);
	T2PeopleArray *array;

	while (iter.Next(&array)) {
		T2People *people = array->FindPeople(id);
		if (people)
			return people;
	}

	return 0;
}

T2People *T2PeopleArrayList::FindUnusedPeople() {
	T2People *result = 0;

	LArrayIterator iter(*this);
	T2PeopleArray *array = 0;

	while (!result && iter.Next(&array)) {
		result = array->FindUnusedPeople();
	}

	if (!result) {
		UInt32 id = 1;
		if (array)
			id = array->GetStartID() + 256;
		array = new T2PeopleArray(id);
		if (array) {
			Add(array);
			result = array->FindUnusedPeople();
		}
	}

	return result;
}

void T2PeopleArrayList::DispatchIdle(T2TowerDoc *doc) {
	LArrayIterator iter(*this);
	T2PeopleArray *array;
	while (iter.Next(&array)) {
		array->DispatchIdle(doc, mIdleCounter);
	}

	mIdleCounter++;
	if (mIdleCounter >= 8)
		mIdleCounter = 0;
}

void T2PeopleArrayList::DrawSearchedPerson(T2TowerDoc *doc) {
	LArrayIterator iter(*this);
	T2PeopleArray *array;
	while (iter.Next(&array)) {
		array->DrawSearchedPerson(doc);
	}
}

void T2PeopleArrayList::SetWalkPeople(Int16 var) {
	LArrayIterator iter(*this);
	T2PeopleArray *array;
	while (iter.Next(&array)) {
		array->SetWalkPeople(var);
	}
}

void T2PeopleArrayList::DayChanged() {
	LArrayIterator iter(*this);
	T2PeopleArray *array;
	while (iter.Next(&array)) {
		array->DayChanged();
	}
}

void T2PeopleArrayList::TenantRemoved(UInt16 var) {
	LArrayIterator iter(*this);
	T2PeopleArray *array;
	while (iter.Next(&array)) {
		array->TenantRemoved(var);
	}
}

void T2PeopleArrayList::AddStress(Int16 var) {
	LArrayIterator iter(*this);
	T2PeopleArray *array;
	while (iter.Next(&array)) {
		array->AddStress(var);
	}
}

void T2PeopleArrayList::BreakoutEmergency(T2TowerDoc *doc) {
	LArrayIterator iter(*this);
	T2PeopleArray *array;
	while (iter.Next(&array)) {
		array->BreakoutEmergency(doc);
	}
}

void T2PeopleArrayList::Read(LStream &stream, T2TowerDoc *doc) {
	UInt32 amount;
	stream >> amount;

	RemoveItemsAt(mItemCount, index_First);

	T2PeopleArray *array;

	UInt32 startID = 1;
	for (UInt32 i = 0; i < amount; i++) {
		array = new T2PeopleArray(startID);
		array->Read(stream, doc);
		Add(array);
		startID += 256;
	}

	LArrayIterator iter(*this);
	while (iter.Next(&array)) {
		array->ResolveLink(this);
	}
}

void T2PeopleArrayList::Write(LStream &stream) {
	stream << mItemCount;

	T2PeopleArray *array;
	LArrayIterator iter(*this);

	while (iter.Next(&array)) {
		array->Write(stream);
	}
}
