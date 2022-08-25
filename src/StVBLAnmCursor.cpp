#include "StVBLAnmCursor.h"
#include "UT2Cursor.h"
#include <MacMemory.h>
#include <CursorCtl.h>
#include <MixedMode.h>
#include <Resources.h>
#include <UCursor.h>
#include <UException.h>

StVBLAnmCursor *StVBLAnmCursor::sCurrentCursor;

StVBLAnmCursor::StVBLAnmCursor(ResIDT resID, Int32 whatever) {
	mWhatever = whatever;
	mResource = ::GetResource('acur', resID);

	if (mResource != NULL) {
		::DetachResource(mResource);
		#line 35
		ThrowIfResError_();
		::MoveHHi(mResource);
		#line 37
		ThrowIfMemError_();
		::HLock(mResource);
		#line 39
		ThrowIfMemError_();

		Index() = 0;

		for (int index = 0; index < GetN(); index++) {
			Handle &handle = CursorHandle(index);
			handle = (Handle) ::GetCCursor(GetCursorResID(index));

			if (handle != NULL) {
				::MoveHHi(handle);
				#line 47
				ThrowIfMemError_();
				::HLock(handle);
				#line 49
				ThrowIfMemError_();
			}
		}
	}

	Start();
}

StVBLAnmCursor::~StVBLAnmCursor() {
	Stop();

	if (mResource != NULL) {
		for (int index = 0; index < GetN(); index++) {
			Handle &handle = CursorHandle(index);
			::HUnlock(handle);
			#line 65
			ThrowIfMemError_();
			::DisposeCCursor((CCrsrHandle) handle);
		}

		::HUnlock(mResource);
		#line 69 // nice
		ThrowIfMemError_();
		::DisposeHandle(mResource);
		ThrowIfMemError_();

		mResource = NULL;
	}
}

void StVBLAnmCursor::SetCursor() {
	if (mResource != NULL) {
		if (Index() < GetN()) {
			UT2Cursor::SetCCursor((CCrsrHandle) CursorHandle(Index()));
			#line 82
			ThrowIfOSErr_(::QDError());
		}
	}
}

void StVBLAnmCursor::TickByVBL(VBLTaskPtr task) {
	if (&mVBLTask == task && mResource != NULL) {
		Index() = (Index() + 1) % GetN();
		SetCursor();
		mVBLTask.vblCount = mWhatever;
	}
}

void StVBLAnmCursor::Tick() {
	if (mResource != NULL && mWhatever < 0) {
		Int32 ticks = ::TickCount();
		if (m8 < ticks) {
			Index() = (Index() + 1) % GetN();
			SetCursor();
			m8 = ticks - mWhatever;
		}
	}
}

Handle &StVBLAnmCursor::CursorHandle(Int16 index) {
	return *(Handle *) (*mResource + (index * 4 + 4));
}

ResIDT StVBLAnmCursor::GetCursorResID(Int16 index) const {
	return *(ResIDT *) (*mResource + (index * 4 + 4));
}

Int16 &StVBLAnmCursor::Index() {
	return (*((Acur **)mResource))->index;
}

Int16 StVBLAnmCursor::GetN() const {
	return (*((Acur **)mResource))->n;
}

void StVBLAnmCursor::Start() {
	OSErr err;

	Index() = 0;
	SetCursor();
	sCurrentCursor = this;

	if (mWhatever > 0) {
		mVBLTask.qLink = NULL;
		mVBLTask.qType = 1; // TODO find out what constant this is?
		mVBLTask.vblAddr = NewVBLProc(VBLAnimate);
		mVBLTask.vblCount = mWhatever;
		mVBLTask.vblPhase = 0;
		#line 155
		ThrowIfOSErr_(err = ::VInstall((QElemPtr) &mVBLTask));
	} else if (mWhatever < 0) {
		m8 = ::TickCount() - mWhatever;
	}
}

void StVBLAnmCursor::Stop() {
	if (mWhatever > 0) {
		OSErr err = ::VRemove((QElemPtr) &mVBLTask);
		#line 167
		ThrowIfOSErr_(err);
	}

	sCurrentCursor = NULL;
	UCursor::SetTheCursor(0);
}

void StVBLAnmCursor::VBLAnimate(VBLTaskPtr task) {
	if (sCurrentCursor != NULL) {
		sCurrentCursor->TickByVBL(task);
	}
}
