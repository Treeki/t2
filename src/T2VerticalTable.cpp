#include "T2VerticalTable.h"

#include <UDrawingState.h>
#include <UGAColorRamp.h>

T2VerticalTable::T2VerticalTable(LStream *inStream)
	: LTable(inStream)
{
	m98 = false;
}

void T2VerticalTable::Clear() {
	RemoveRows(mRows, 1);
}

Boolean T2VerticalTable::FocusDraw(LPane *inSubPane) {
	Boolean result = LView::FocusDraw(inSubPane);
	if (m98) {
		::RGBForeColor(&UGAColorRamp::GetBlackColor());
		::RGBBackColor(&UGAColorRamp::GetWhiteColor());
	}
	return result;
}

void T2VerticalTable::DrawSelf() {
	StColorState state;

	if (m98) {
		Rect rect;
		CalcLocalFrameRect(rect);
		::RGBBackColor(&UGAColorRamp::GetWhiteColor());
		::EraseRect(&rect);
	}

	LTable::DrawSelf();
}
