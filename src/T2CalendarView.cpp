#include "T2CalendarView.h"
#include "T2DateTime.h"
#include "T2TowerDoc.h"
#include <LString.h>
#include <UException.h>
#include <UDrawingUtils.h>

T2CalendarView *T2CalendarView::sCalendarView;

T2CalendarView::T2CalendarView(LStream *inStream)
	: LPane(inStream)
{
	sCalendarView = this;
}

T2CalendarView::~T2CalendarView() {
	sCalendarView = 0;
}

void T2CalendarView::DrawSelf() {
	T2TowerDoc *theDoc = T2TowerDoc::GetCurrentT2TowerDoc();
	#line 59
	Assert_(theDoc != 0);

	T2DateTime time2 = *theDoc->someDateTime;
	T2DateTime time1 = time2;

	RGBColor clr;

	LStr255 str;

	::TextSize(10);
	::TextFace(0);
	::TextFont(1);
	::TextMode(1);

	Rect rect;
	rect.top = 5;
	rect.bottom = 17;

	static const RGBColor CLR_WHITE = { 0xFFFF, 0xFFFF, 0xFFFF };
	static const RGBColor CLR_BLACK = { 0, 0, 0 };

	for (Int32 i = 0; i < 5; i++) {
		time1.mYear = time2.mYear + i;
		str.Assign(i + time2.mYear);
		rect.left = 38;
		rect.right = 61;

		clr = CLR_BLACK;
		::RGBForeColor(&clr);

		UTextDrawing::DrawWithJustification((Ptr) &str[1], str.Length(), rect, -1);

		for (Int32 j = 1; j <= 12; j++) {
			time1.mDay = j - 1;
			str = j;
			rect.left = (j * 21) + 44;
			rect.right = (j * 21) + 60;
			if (time1.mYear == time2.mYear && time1.mDay == time2.mDay) {
				clr.red = 0;
				clr.green = 0;
				clr.blue = 0xFFFF;
				::RGBForeColor(&clr);

				if (time1.IsHoliday(theDoc)) {
					clr = CLR_BLACK;
				} else {
					clr = CLR_WHITE;
				}
			} else {
				clr = CLR_WHITE;
				::RGBForeColor(&clr);

				if (time1.IsHoliday(theDoc)) {
					clr.red = 0xFF00;
					clr.green = 0x6600;
					clr.blue = 0x6600;
				} else {
					clr = CLR_BLACK;
				}
			}

			rect.top += 2;
			rect.bottom += 1;
			::PaintRect(&rect);
			::RGBForeColor(&clr);
			rect.top -= 2;
			rect.bottom -= 1;

			UTextDrawing::DrawWithJustification((Ptr) &str[1], str.Length(), rect, -1);
		}

		::OffsetRect(&rect, 0, 12);
	}
}

void T2CalendarView::UpdateCalendarView() {
	if (sCalendarView)
		sCalendarView->Refresh();
}
