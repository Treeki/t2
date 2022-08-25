#include "T2ReturnStack.h"

#include <LStream.h>

T2ReturnStack::T2ReturnStack() {
	Init();
}

T2ReturnStack::~T2ReturnStack() {
}

void T2ReturnStack::Init() {
	for (Int32 i = 0; i < 3; i++) {
		mEntries[i].tenant = 0;
		mEntries[i].time = 0;
	}
	mCount = 0;
}

Boolean T2ReturnStack::Current(UInt16 &tenant, UInt16 &time) {
	if (mCount > 0) {
		tenant = mEntries[0].tenant;
		time = mEntries[0].time;
		return true;
	}
	return false;
}

Boolean T2ReturnStack::Push(UInt16 tenant, UInt16 time) {
	if (mCount < 3) {
		for (Int32 i = mCount - 1; i >= 0; i--) {
			mEntries[i + 1] = mEntries[i];
		}
		mCount++;
		mEntries[0].tenant = tenant;
		mEntries[0].time = time;
		return true;
	} else {
		return false;
	}
}

Boolean T2ReturnStack::Pop(UInt16 &tenant, UInt16 &time) {
	if (mCount > 0) {
		tenant = mEntries[0].tenant;
		time = mEntries[0].time;
		for (Int32 i = 1; i < mCount; i++) {
			mEntries[i - 1] = mEntries[i];
		}
		mCount--;
		return true;
	} else {
		return false;
	}
}

Boolean T2ReturnStack::IsSetTime() const {
	Boolean result = false;
	if (mCount > 0 && mEntries[0].time != 0)
		result = true;
	return result;
}

UInt16 T2ReturnStack::GetTenant() const {
	UInt16 result = 0;
	if (mCount > 0)
		result = mEntries[0].tenant;
	return result;
}

UInt16 T2ReturnStack::GetTime() const {
	UInt16 result = 0;
	if (mCount > 0)
		result = mEntries[0].time;
	return result;
}

void T2ReturnStack::SetTime(UInt16 time) {
	if (mCount > 0)
		mEntries[0].time = time;
}

void T2ReturnStack::DayChanged() {
	for (UInt32 i = 0; i < mCount; i++) {
		if (mEntries[i].time >= 1440) {
			mEntries[i].time -= 1440;
		} else if (mEntries[i].time > 1438) {
			mEntries[i].time = 0;
		}
	}
}

Boolean T2ReturnStack::Remove(UInt16 tenant) {
	Boolean result = false;

	for (Int32 i = 0; i < mCount; i++) {
		if (mEntries[i].tenant == tenant) {
			for (Int32 j = i + 1; j < mCount; j++) {
				mEntries[j - 1] = mEntries[j];
			}
			i--;
			mCount--;
			result |= true;
		}
	}

	return result;
}

void T2ReturnStack::Peek(Int32 index, UInt16 &tenant, UInt16 &time) {
	tenant = mEntries[index].tenant;
	time = mEntries[index].time;
}

void T2ReturnStack::Poke(Int32 index, UInt16 tenant, UInt16 time) {
	mEntries[index].tenant = tenant;
	mEntries[index].time = time;
}

void T2ReturnStack::Read(LStream &stream) {
	stream >> mCount;
	for (Int32 i = 0; i < mCount; i++) {
		stream >> mEntries[i].tenant;
		stream >> mEntries[i].time;
	}
}

void T2ReturnStack::Write(LStream &stream) {
	stream << mCount;
	for (Int32 i = 0; i < mCount; i++) {
		stream << mEntries[i].tenant;
		stream << mEntries[i].time;
	}
}
