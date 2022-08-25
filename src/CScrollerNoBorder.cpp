#include "CScrollerNoBorder.h"
#include <LStdControl.h>
#include <LStream.h>
#include <UDrawingState.h>

CScrollerNoBorder::CScrollerNoBorder(LStream *inStream)
	: LScroller(inStream)
{
}

/*CScrollerNoBorder *CScrollerNoBorder::CreateCScrollerNoBorderStream(LStream *inStream) {
	return new CScrollerNoBorder(inStream);
}*/

void CScrollerNoBorder::DrawSelf() {
	Rect theFrameRect;
	CalcLocalFrameRect(theFrameRect);

	::PenNormal();
	ApplyForeAndBackColors();

	if (mVerticalBar) {
		::MoveTo(theFrameRect.right - 16, theFrameRect.top);
		::LineTo(theFrameRect.right - 16, theFrameRect.bottom - 1);
	}
	if (mHorizontalBar) {
		::MoveTo(theFrameRect.left, theFrameRect.bottom - 16);
		::LineTo(theFrameRect.right - 1, theFrameRect.bottom - 16);
	}

	if (!IsActive()) {
		if (mVerticalBar) {
			mVerticalBar->CalcPortFrameRect(theFrameRect);
			PortToLocalPoint(topLeft(theFrameRect));
			PortToLocalPoint(botRight(theFrameRect));
			::FrameRect(&theFrameRect);
			::InsetRect(&theFrameRect, 1, 1);
			::EraseRect(&theFrameRect);
		}
		if (mHorizontalBar) {
			mHorizontalBar->CalcPortFrameRect(theFrameRect);
			PortToLocalPoint(topLeft(theFrameRect));
			PortToLocalPoint(botRight(theFrameRect));
			::FrameRect(&theFrameRect);
			::InsetRect(&theFrameRect, 1, 1);
			::EraseRect(&theFrameRect);
		}
	}
}
