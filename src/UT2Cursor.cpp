#include "UT2Cursor.h"

CCrsrHandle UT2Cursor::sCurrentCCursorH;

void UT2Cursor::SetCCursor(CCrsrHandle handle) {
	if (handle != 0 && handle != GetCCursor()) {
		sCurrentCCursorH = handle;
		::SetCCursor(GetCCursor());
	}
}

void UT2Cursor::InvalCCursor() {
	sCurrentCCursorH = 0;
}
