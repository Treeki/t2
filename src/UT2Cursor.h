#pragma once

#include <CursorCtl.h>
#include <Quickdraw.h>

class UT2Cursor {
public:
	static CCrsrHandle GetCCursor() { return sCurrentCCursorH; }
	static void SetCCursor(CCrsrHandle handle);
	static void InvalCCursor();

protected:
	static CCrsrHandle sCurrentCCursorH;
};
