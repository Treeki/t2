#include <math.h>
#include <LStream.h>
#include <LString.h>
#include <UDrawingState.h>
#include <UDrawingUtils.h>
#include <UGAColorRamp.h>
#include <UTextTraits.h>
#include "CPieChartView.h"
#include "URect.h"

CPieChartView *CPieChartView::CreateCPieChartViewStream(LStream *inStream) {
	return new CPieChartView(inStream);
}

CPieChartView::CPieChartView(LStream *inStream)
	: LPane(inStream)
{
	mPie = 0;
	inStream->ReadData(&mTextTraits, sizeof(mTextTraits));
	inStream->ReadData(&mBorderWidth, sizeof(mBorderWidth));
}

CPieChartView::~CPieChartView() {
}

void CPieChartView::DrawSelf() {
	Rect theFrameRect;
	if (!CalcLocalFrameRect(theFrameRect))
		return;

 #line 42
	Assert_(URect::Width(theFrameRect) == URect::Height(theFrameRect));

	StColorPenState colorPenState;
	StColorPenState::Normalize();

	RGBColor *foreColor, *backColor;
	foreColor = (IsActive() && IsEnabled()) ? &UGAColorRamp::GetBlackColor() : &UGAColorRamp::GetColor(colorRamp_Gray10);
	backColor = (IsActive() && IsEnabled()) ? &UGAColorRamp::GetColor(colorRamp_Gray1) : &UGAColorRamp::GetColor(colorRamp_Gray2);

	::RGBBackColor(backColor);
	::EraseOval(&theFrameRect);

	Rect insideRect = theFrameRect;
	::InsetRect(&insideRect, mBorderWidth, mBorderWidth);

	if (mPie != NULL && mPie->totalValue != 0) {
		UInt32 angle = 0;
		UInt32 valueTotal = 0;

		for (Int32 i = 0; i < mPie->sliceCount; i++) {
			if (mPie->slices[i].value != 0) {
				valueTotal += mPie->slices[i].value;
				UInt32 nextAngle = (valueTotal * 360) / mPie->totalValue;
				Int16 arcAngle = nextAngle - angle;
				::RGBForeColor(&mPie->slices[i].color);
				::PaintArc(&insideRect, angle, arcAngle);
				angle = nextAngle;
			}
		}

		UInt16 oldTextTraits = UTextTraits::SetPortTextTraits(mTextTraits);
		::RGBForeColor(foreColor);

		FontInfo fontInfo;
		::GetFontInfo(&fontInfo);
		Int16 maxWidth = ::StringWidth("\p100%");
		Int16 maxHeight = fontInfo.ascent + fontInfo.descent + fontInfo.leading;

		Int16 xOffset = (URect::Width(insideRect) - maxWidth) / 2;
		Point spanHalf;
		spanHalf.h = (insideRect.left + insideRect.right) / 2;
		spanHalf.v = (insideRect.top + insideRect.bottom) / 2;

		angle = 0;
		valueTotal = 0;

		for (Int32 i = 0; i < mPie->sliceCount; i++) {
			if (mPie->slices[i].value != 0) {
				valueTotal += mPie->slices[i].value;
				UInt32 endAngle = (valueTotal * 360) / mPie->totalValue;

				Int16 halfAngle = ((Int16) angle + (Int16) endAngle) / 2;

				LStr255 numberString = (Int32) ((mPie->slices[i].value * 100) / mPie->totalValue);
				numberString.Append('%');

				Point pt;
				pt.h = (xOffset * ::sin((3.14159265358979 * halfAngle) / 180.0)) + spanHalf.h;
				pt.v = -((xOffset * ::cos((3.14159265358979 * halfAngle) / 180.0)) - spanHalf.v);

				Rect textRect;
				::SetRect(&textRect, pt.h - (maxWidth / 2), pt.v - (maxHeight / 2), pt.h + (maxWidth / 2), pt.v + (maxHeight / 2));
				UTextDrawing::DrawWithJustification(
					(Ptr) &numberString[1],
					numberString.Length(),
					textRect,
					1
				);

				angle = endAngle;
			}
		}
	}

	::RGBForeColor(foreColor);
	::FrameOval(&insideRect);
}

void CPieChartView::CutPie(const Pie *pie) {
	mPie = pie;
	Refresh();
}
