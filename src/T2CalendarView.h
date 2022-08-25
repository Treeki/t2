#pragma once

#include <LPane.h>

class T2CalendarView : public LPane {
public:
	T2CalendarView(LStream *inStream);
	~T2CalendarView();
	void DrawSelf();

	static T2CalendarView *sCalendarView;
	static void UpdateCalendarView();
};
