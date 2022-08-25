#include "T2PoolDef.h"
#include "T2WorldPlugin.h"

#include <LStream.h>
#include <UException.h>


T2PoolTimeZoneDef::T2PoolTimeZoneDef(LStream &stream) {
	Initialize();
	stream >> mNumOfElems;

	mPeopleElems = new T2PoolTimeZoneDef_Inner[mNumOfElems];
	#line 22
	ThrowIfNil_(mPeopleElems);

	try {
		UInt32 theSum = 0;
		for (UInt32 i = 0; i < mNumOfElems; i++) {
			stream >> mPeopleElems[i].m0;
			stream >> mPeopleElems[i].m1;
			stream >> mPeopleElems[i].m2;
			stream >> mPeopleElems[i].mRate;
			#line 32
			Assert_(mPeopleElems[ i ].mRate <= 100);
			Assert_(mPeopleElems[ i ].mRate % 5 == 0);
			mPeopleElems[i].m4 = (mPeopleElems[i].mRate * 20) / 100;
			theSum += mPeopleElems[i].m4;
		}

		#line 38
		Assert_(theSum <= kPoolUnitSize);
	} catch (ExceptionCode code) {
		delete this;
		#line 43
		Throw_(code);
	}
}

void T2PoolTimeZoneDef::Initialize() {
	mNumOfElems = 0;
	mPeopleElems = 0;
}

T2PoolTimeZoneDef::~T2PoolTimeZoneDef() {
	delete mPeopleElems;
}

T2PoolTimeZoneDef_Inner *T2PoolTimeZoneDef::GetPeopleElem(UInt32 index) const {
	T2PoolTimeZoneDef_Inner *result = 0;
	if (index < mNumOfElems)
		result = &mPeopleElems[index];
	return result;
}


T2PoolDefDemandElem::T2PoolDefDemandElem() {
	mNumOfElems = 0;
	mElems = 0;
}

void T2PoolDefDemandElem::Initialize(LStream &stream) {
	stream >> mNumOfElems;
	#line 121
	Assert_(mNumOfElems <= kMaxTimeZone);

	mElems = new T2PoolDefDemandElem_Inner[mNumOfElems];
	#line 123
	ThrowIfNil_(mElems);

	try {
		for (UInt32 i = 0; i < mNumOfElems; i++) {
			stream >> mElems[i].a;
			stream >> mElems[i].b;
		}
	} catch (ExceptionCode code) {
		delete this;
		#line 135
		Throw_(code);
	}
}

T2PoolDefDemandElem::~T2PoolDefDemandElem() {
	delete mElems;
}

T2PoolDefDemandElem_Inner *T2PoolDefDemandElem::GetTimeZoneInfo(UInt32 index) const {
	T2PoolDefDemandElem_Inner *result = 0;
	if (index < mNumOfElems)
		result = &mElems[index];
	return result;
}


T2PoolGradeDef::T2PoolGradeDef(LStream &stream) {
	Initialize();
	stream >> mNumOfElems;
	#line 186
	Assert_(mNumOfElems <= kMaxDemand);

	mElems = new T2PoolDefDemandElem[mNumOfElems];
	#line 188
	ThrowIfNil_(mElems);

	try {
		for (UInt32 i = 0; i < mNumOfElems; i++) {
			mElems[i].Initialize(stream);
		}
	} catch (ExceptionCode code) {
		delete this;
		#line 199
		Throw_(code);
	}
}

void T2PoolGradeDef::Initialize() {
	mNumOfElems = 0;
	mElems = 0;
}

T2PoolGradeDef::~T2PoolGradeDef() {
	delete[] mElems;
}

T2PoolDefDemandElem *T2PoolGradeDef::GetDemandElem(UInt32 index) const {
	T2PoolDefDemandElem *result = 0;
	if (index < mNumOfElems)
		result = &mElems[index];
	return result;
}


T2PoolDef::T2PoolDef(LStream &stream, T2WorldPlugin *worldPlugin) {
	Initialize();
	mWorldPlugin = worldPlugin;

	stream >> m8;
	for (UInt32 i = 0; i < 5; i++)
		stream >> mGradeDefResID[i];
	stream >> m14;
	stream >> mNumOfDemand;

	#line 274
	Assert_(mNumOfDemand <= kMaxDemand);

	mDemand = new T2PoolDef_Inner[mNumOfDemand];
	#line 276
	ThrowIfNil_(mDemand);

	try {
		for (UInt32 i = 0; i < mNumOfDemand; i++) {
			stream >> mDemand[i].a;
			stream >> mDemand[i].b;
		}
	} catch (ExceptionCode code) {
		delete this;
		#line 288
		Throw_(code);
	}
}

void T2PoolDef::Initialize() {
	mWorldPlugin = 0;
	m14 = 0;
	mNumOfDemand = 0;
	m8 = 0;
	for (UInt32 i = 0; i < 5; i++) {
		mGradeDefResID[i] = 0;
	}
	mDemand = 0;
}

T2PoolDef::~T2PoolDef() {
	delete[] mDemand;
}

OSErr T2PoolDef::OpenResourceFork(Int16 permission) {
	return mWorldPlugin->OpenResourceFork(permission);
}

void T2PoolDef::CloseResourceFork() {
	mWorldPlugin->CloseResourceFork();
}

T2PoolDef_Inner *T2PoolDef::GetDemandInfo(UInt32 index) const {
	T2PoolDef_Inner *result = 0;;
	if (index < mNumOfDemand)
		result = &mDemand[index];
	return result;
}

ResIDT T2PoolDef::GetGradeDefResID(UInt32 index) const {
	ResIDT result = 0;
	UInt32 index0 = index - 1;
	if (index0 < 5)
		result = mGradeDefResID[index0];
	return result;
}
