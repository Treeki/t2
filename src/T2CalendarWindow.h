#pragma once

#include "T2FloatingWindow.h"

class T2CalendarWindow : public T2FloatingWindow {
public:
	T2CalendarWindow(LStream *inStream);
	~T2CalendarWindow();

	static void SetPosition(Int16 h, Int16 v);
	static void ResetPosition();

	static Boolean sIsPositionSet;
	static T2CalendarWindow *sT2CalendarWindow;
};
