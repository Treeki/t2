#pragma once

#include <PP_Types.h>
#include <Retrace.h>

struct StVBLAnmCursor {
	StVBLAnmCursor(ResIDT resID, Int32 whatever);
	~StVBLAnmCursor();

	void SetCursor();
	void TickByVBL(VBLTaskPtr task);
	void Tick();
	Handle &CursorHandle(Int16 index);
	ResIDT GetCursorResID(Int16 index) const;
	Int16 &Index();
	Int16 GetN() const;
	void Start();
	void Stop();

	Handle mResource;
	Int32 mWhatever;
	Int32 m8;
	VBLTask mVBLTask;

	static StVBLAnmCursor *sCurrentCursor;
	static void VBLAnimate(VBLTaskPtr task);
};
