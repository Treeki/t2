#include "T2PeopleTimeZoneList.h"
#include "T2PeopleType.h"
#include "T2PeopleTypeArray.h"
#include "T2PoolDefDemandElem.h"
#include "T2PoolTimeZoneDef.h"

#include <LArrayIterator.h>
#include <LHandleStream.h>
#include <LStream.h>
#include <UException.h>

T2PeopleTimeZoneList::T2PeopleTimeZoneList(UInt8 someCount, UInt32 var)
	: LArray(sizeof(T2PeopleTypeArray *))
{
	mIsFixed = var;
	mMaxHour = 0;
	mCurrent = 0;
	mHour = 0;

	try {
		for (UInt32 i = 0; i < someCount; i++) {
			T2PeopleTypeArray *array = new T2PeopleTypeArray(var);
			#line 37
			ThrowIfNil_(array);
			Add(array);
		}
	} catch (ExceptionCode code) {
		delete this;
		#line 44
		Throw_(code);
	}

	mMaxHour = 24 / someCount;
}

T2PeopleTimeZoneList::T2PeopleTimeZoneList(LStream &stream)
	: LArray(sizeof(T2PeopleTypeArray *))
{
	UInt32 count;
	stream >> count;
	stream >> mIsFixed;
	stream >> mMaxHour;
	stream >> mCurrent;
	stream >> mHour;

	for (UInt32 i = 0; i < count; i++) {
		T2PeopleTypeArray *array = new T2PeopleTypeArray(stream);
		Add(array);
	}
}

void T2PeopleTimeZoneList::Add(T2PeopleType *peopleType, T2PoolDefDemandElem *inDemandElem) {
	#line 91
	Assert_(mItemCount == inDemandElem->GetNumOfElems());

	LArrayIterator iter(*this);
	UInt32 index = 0;
	T2PeopleTypeArray *array;
	while (iter.Next(&array)) {
		peopleType->SetTimeZoneType(index);
		T2PoolDefDemandElem_Inner *theTimeZoneInfo = inDemandElem->GetTimeZoneInfo(index);
		#line 100
		Assert_(theTimeZoneInfo != 0);

		if (theTimeZoneInfo->a > 0) {
			Handle res = ::Get1Resource('PzDf', theTimeZoneInfo->a);
			if (res) {
				::DetachResource(res);
				LHandleStream stream(res);
				T2PoolTimeZoneDef *tzDef = new T2PoolTimeZoneDef(stream);
				#line 111
				ThrowIfNil_(tzDef);
				try {
					array->Add(peopleType, tzDef, theTimeZoneInfo->b);
				} catch (ExceptionCode code) {
					delete tzDef;
					#line 120
					Throw_(code);
				}
				delete tzDef;
			}
		}

		index++;
	}
}

T2PeopleTimeZoneList::~T2PeopleTimeZoneList() {
	LArrayIterator iter(*this);
	T2PeopleTypeArray *array;

	while (iter.Next(&array)) {
		delete array;
	}
}

void T2PeopleTimeZoneList::Add(T2PeopleTypeArray *array) {
	InsertItemsAt(1, index_Last, &array);
}

void T2PeopleTimeZoneList::Init(UInt16 a, float f) {
	mCurrent = a / mMaxHour;
	mHour = a % mMaxHour;

	LArrayIterator iter(*this);
	T2PeopleTypeArray *array;

	while (iter.Next(&array)) {
		array->InitSearchLimit(f);
	}
}

void T2PeopleTimeZoneList::IncHour(float f) {
	mHour++;
	if (mHour >= mMaxHour) {
		T2PeopleTypeArray *array = CurrentItem();
		if (array)
			array->AdjustLife();

		mHour = 0;
		mCurrent++;
		if (mCurrent >= mItemCount)
			mCurrent = 0;

		T2PeopleTypeArray *array2 = CurrentItem();
		if (array2)
			array2->InitSearchLimit(f);
	}
}

T2PeopleTypeArray *T2PeopleTimeZoneList::GetItem(Int8 index) const {
	ArrayIndexT i = index + 1;
	T2PeopleTypeArray *array;
	if (!FetchItemAt(i, &array))
		array = 0;
	return array;
}

T2PeopleTypeArray *T2PeopleTimeZoneList::CurrentItem() const {
	return GetItem(mCurrent);
}

Boolean T2PeopleTimeZoneList::Find(T2TenantMemberDef *tmDef, Int32 var, Byte flags, Boolean otherFlag) const {
	T2PeopleTypeArray *array = CurrentItem();
	return array->Find(tmDef, var, flags, otherFlag);
}

Boolean T2PeopleTimeZoneList::Call(T2TenantMemberDef *tmDef, Int32 var, Byte flags, T2PeopleType &peopleType) {
	T2PeopleTypeArray *array = CurrentItem();
	return array->Call(tmDef, var, flags, peopleType);
}

void T2PeopleTimeZoneList::DispatchRestore(T2PeopleType &peopleType) {
	T2PeopleTypeArray *array = GetItem(peopleType.GetTimeZoneType());
	if (array)
		array->Restore(peopleType);
}

void T2PeopleTimeZoneList::DispatchAdd(T2PeopleType *peopleType) {
	T2PeopleTypeArray *array = GetItem(peopleType->GetTimeZoneType());
	if (array)
		array->Add(peopleType, 1, index_Last);
}

void T2PeopleTimeZoneList::Write(LStream &stream) const {
	stream << mItemCount;
	stream << mIsFixed;
	stream << mMaxHour;
	stream << mCurrent;
	stream << mHour;

	for (UInt32 i = 0; i < mItemCount; i++) {
		T2PeopleTypeArray *array = GetItem(i);
		if (array)
			array->Write(stream);
	}
}
