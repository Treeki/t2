#include "T2PeopleDemandList.h"
#include "T2PeopleTimeZoneList.h"
#include "T2PeopleType.h"
#include "T2PoolDef.h"
#include "T2SeasonParamDef.h"
#include "T2TenantMemberDef.h"
#include "UT2Utils.h"

#include <LArrayIterator.h>
#include <LStream.h>
#include <UException.h>

T2PeopleDemandList::T2PeopleDemandList(T2PoolDef *poolDef, T2SeasonParamDef *seasonParamDef)
	: LArray(sizeof(T2PeopleTimeZoneList *))
{
	mSeasonParamDef = seasonParamDef;

	try {
		UInt32 numOfDemand = poolDef->GetNumOfDemand();
		for (UInt32 i = 0; i < numOfDemand; i++) {
			T2PoolDef_Inner *demand = poolDef->GetDemandInfo(i);
			#line 67
			ThrowIfNil_(demand);

			T2PeopleTimeZoneList *list = new T2PeopleTimeZoneList(demand->b, demand->a);
			#line 71
			ThrowIfNil_(list);

			Add(list);
		}
	} catch (ExceptionCode code) {
		delete this;
		#line 78
		Throw_(code);
	}
}

T2PeopleDemandList::T2PeopleDemandList(LStream &stream, T2SeasonParamDef *seasonParamDef)
	: LArray(sizeof(T2PeopleTimeZoneList *))
{
	mSeasonParamDef = seasonParamDef;

	UInt32 count;
	stream >> count;

	for (UInt32 i = 0; i < count; i++) {
		T2PeopleTimeZoneList *list = new T2PeopleTimeZoneList(stream);
		Add(list);
	}
}

void T2PeopleDemandList::Add(T2PoolGradeDef *inGradeDef) {
	#line 145
	Assert_(mItemCount == inGradeDef->GetNumOfElems());

	LArrayIterator iter(*this);
	Int32 index = 0;
	T2PeopleTimeZoneList *list;
	T2PeopleType peopleType;

	while (iter.Next(&list)) {
		peopleType.SetDemandType(index);
		T2PoolDefDemandElem *theDemandElem = inGradeDef->GetDemandElem(index);
		Assert_(theDemandElem != 0);
		list->Add(&peopleType, theDemandElem);
		index++;
	}
}

T2PeopleDemandList::~T2PeopleDemandList() {
	LArrayIterator iter(*this);
	T2PeopleTimeZoneList *list;
	while (iter.Next(&list)) {
		delete list;
	}
}

void T2PeopleDemandList::Add(T2PeopleTimeZoneList *list) {
	InsertItemsAt(1, index_Last, &list);
}

void T2PeopleDemandList::Init(UInt16 a, UInt16 b) {
	float f31 = 0.0f;
	if (mSeasonParamDef)
		f31 = mSeasonParamDef->GetSomething(a - 1);

	LArrayIterator iter(*this);
	T2PeopleTimeZoneList *list;
	while (iter.Next(&list)) {
		list->Init(b, f31);
	}
}

void T2PeopleDemandList::IncHour(UInt16 a) {
	float f31 = 1.0f;
	if (mSeasonParamDef)
		f31 = mSeasonParamDef->GetSomething(a - 1);

	LArrayIterator iter(*this);
	T2PeopleTimeZoneList *list;
	while (iter.Next(&list)) {
		list->IncHour(f31);
	}
}

T2PeopleTimeZoneList *T2PeopleDemandList::GetItem(Int8 index) const {
	T2PeopleTimeZoneList *list;
	Int32 index1 = index + 1;
	if (!FetchItemAt(index1, &list))
		list = 0;
	return list;
}

Boolean T2PeopleDemandList::Find(T2TenantMemberDef *tmDef, Int32 var, Byte flags, Boolean otherFlag) const {
	Boolean result = false;

	T2PeopleTimeZoneList *list = GetItem(tmDef->GetDemandType());
	if (list)
		result = list->Find(tmDef, var, flags, otherFlag);

	return result;
}

Boolean T2PeopleDemandList::Call(T2TenantMemberDef *tmDef, Int32 var, Byte flags, T2PeopleType &peopleType) const {
	Boolean result = false;

	Int32 demandType = tmDef->GetDemandType();
	if (demandType != -1) {
		T2PeopleTimeZoneList *list = GetItem(demandType);
		if (list)
			result = list->Call(tmDef, var, flags, peopleType);
	} else {
		UInt32 varB = UT2Utils::Randomize(mItemCount) + 1;
		for (UInt32 varA = 0; !result && varA < mItemCount; varA++, varB++) {
			if (varB > mItemCount)
				varB = 1;
			T2PeopleTimeZoneList *list = GetItem(varB);
			if (list && !list->IsFixed())
				result = list->Call(tmDef, var, flags, peopleType);
		}
	}

	return result;
}

void T2PeopleDemandList::DispatchRestore(T2PeopleType &peopleType) {
	T2PeopleTimeZoneList *list = GetItem(peopleType.GetDemandType());
	if (list)
		list->DispatchRestore(peopleType);
}

void T2PeopleDemandList::DispatchAdd(T2PeopleType *peopleType) {
	T2PeopleTimeZoneList *list = GetItem(peopleType->GetDemandType());
	if (list)
		list->DispatchAdd(peopleType);
}

void T2PeopleDemandList::Write(LStream &stream) const {
	stream << mItemCount;
	for (UInt32 i = 0; i < mItemCount; i++) {
		T2PeopleTimeZoneList *list = GetItem(i);
		if (list)
			list->Write(stream);
	}
}
