#include "CGDeviceIterator.h"

CGDeviceIterator::CGDeviceIterator() {
	Reset();
}

CGDeviceIterator::~CGDeviceIterator() {
}

void CGDeviceIterator::Reset() {
	mCurrent = NULL;
}

GDHandle CGDeviceIterator::Current() {
	return mCurrent;
}

Boolean CGDeviceIterator::Next(GDHandle &handle) {
	if (Current() == NULL) {
		mCurrent = ::GetMainDevice();
	} else {
		mCurrent = ::GetNextDevice(mCurrent);
	}

	handle = mCurrent;
	return mCurrent != NULL;
}
