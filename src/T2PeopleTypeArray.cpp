#include "T2PeopleType.h"
#include "T2PeopleTypeArray.h"
#include "T2TenantMemberDef.h"

#include <LArrayIterator.h>
#include <LStream.h>
#include <UException.h>

T2PeopleTypeArray::T2PeopleTypeArray(UInt32 var)
	: LArray(sizeof(T2PeopleType))
{
	m28 = var;
	InitSearchLimit(1.0f);
}

T2PeopleTypeArray::T2PeopleTypeArray(LStream &stream)
	: LArray(sizeof(T2PeopleType))
{
	Read(stream);
}

void T2PeopleTypeArray::Add(T2PeopleType *peopleType, T2PoolTimeZoneDef *tzDef, UInt32 count) {
	// TODO: T2PoolTimeZoneDef
}

T2PeopleTypeArray::~T2PeopleTypeArray() {
}

void T2PeopleTypeArray::Add(T2PeopleType *peopleType, UInt32 count, ArrayIndexT index) {
	InsertItemsAt(count, index, peopleType);
}

void T2PeopleTypeArray::AdjustLife() {
	for (ArrayIndexT i = m30; i >= m2C; i--) {
		T2PeopleType peopleType;
		if (FetchItemAt(i, &peopleType)) {
			peopleType.DecreaseLife();
			if (peopleType.HasLife()) {
				AssignItemsAt(1, i, &peopleType);
			} else {
				RemoveItemsAt(1, i);
			}
		}
	}
}

void T2PeopleTypeArray::InitSearchLimit(float limit) {
	m2C = 1;
	m30 = GetCount();
	if (m28 == 0) {
		float l = limit;
		m30 = m30 * l;
	}
}

Boolean T2PeopleTypeArray::Find(T2TenantMemberDef *tmDef, Int32 var, Byte flags, Boolean otherFlag) const {
	Boolean result = false;
	T2PeopleType peopleType;

	UInt32 numOfPeople = tmDef->GetNumOfPeople();
	Int32 i;
	UInt32 r30 = 0;
	Int32 r27 = var;
	if (numOfPeople > 1 && m28 != 0)
		numOfPeople = 1;

	i = m2C;
	while (!result && i <= m30) {
		if (FetchItemAt(i, &peopleType)) {
			if (peopleType.Check(tmDef, r27, flags)) {
				r30++;
				if (r30 >= numOfPeople)
					result = true;
				else if (r30 == 1 && otherFlag)
					r27 = -1;
			}
		}
		i++;
	}

	return result;
}

Boolean T2PeopleTypeArray::Call(T2TenantMemberDef *tmDef, Int32 var, Byte flags, T2PeopleType &peopleType) {
	Boolean result = false;
	T2PeopleType iterPT;

	Int32 i = m2C;
	while (!result && i <= m30) {
		if (FetchItemAt(i, &iterPT)) {
			if (iterPT.Check(tmDef, var, flags)) {
				result = true;
				peopleType = iterPT;
				if (m28 == 0) {
					RemoveItemsAt(1, i);
					m30--;
				}
			}
		}
		i++;
	}

	return result;
}

void T2PeopleTypeArray::Restore(T2PeopleType &peopleType) {
	peopleType.RecoverLife();
	InsertItemsAt(1, index_First, &peopleType);
	m2C++;
	m30++;
}

void T2PeopleTypeArray::Read(LStream &stream) {
	Int32 amount;
	stream >> amount;

	T2PeopleType peopleType;
	for (Int32 i = 0; i < amount; i++) {
		peopleType.Read(stream);
		Add(&peopleType, 1, index_Last);
	}

	stream >> m28;
	stream >> m2C;
	stream >> m30;
}

void T2PeopleTypeArray::Write(LStream &stream) const {
	stream << mItemCount;

	LArrayIterator iter(*this);
	T2PeopleType peopleType;
	while (iter.Next(&peopleType)) {
		peopleType.Write(stream);
	}

	stream << m28;
	stream << m2C;
	stream << m30;
}
