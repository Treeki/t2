#include "T2CalendarWindow.h"

Boolean T2CalendarWindow::sIsPositionSet;
T2CalendarWindow *T2CalendarWindow::sT2CalendarWindow;

T2CalendarWindow::T2CalendarWindow(LStream *inStream)
	: T2FloatingWindow(inStream)
{
	SetShowHideCommand(1004);
	sT2CalendarWindow = this;
}

T2CalendarWindow::~T2CalendarWindow() {
	sT2CalendarWindow = 0;
}

void T2CalendarWindow::SetPosition(Int16 h, Int16 v) {
	if (sT2CalendarWindow) {
		if (!sIsPositionSet) {
			sT2CalendarWindow->MoveWindowTo(h, v);
		}
		sIsPositionSet = true;
	}
}

void T2CalendarWindow::ResetPosition() {
	sIsPositionSet = false;
}
