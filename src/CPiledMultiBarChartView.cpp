#include <LStream.h>
#include <UDrawingState.h>
#include <UDrawingUtils.h>
#include <UGAColorRamp.h>
#include <string.h>
#include "CPiledMultiBarChartView.h"

CPiledMultiBarChartView *CPiledMultiBarChartView::CreateCPiledMultiBarChartViewStream(LStream *inStream) {
	return new CPiledMultiBarChartView(inStream);
}

CPiledMultiBarChartView::CPiledMultiBarChartView(LStream *inStream)
	: LPane(inStream)
{
	mPixelPerValue = 1;
	mColorOfPiles = NULL;
	mGraphData = NULL;

	inStream->ReadData(&mSkipDrawing, sizeof(mSkipDrawing));
	inStream->ReadData(&mPiles, sizeof(mPiles));
	inStream->ReadData(&mBars, sizeof(mBars));
	inStream->ReadData(&mBarWidth, sizeof(mBarWidth));
	inStream->ReadData(&mXOffset, sizeof(mXOffset));
	inStream->ReadData(&mBarInterval, sizeof(mBarInterval));
#line 36
	Assert_(mPiles > 0 && mBars > 0 && mBarWidth > 0 && mBarInterval >= 0);
	inStream->ReadData(&mLines, sizeof(mLines));
	inStream->ReadData(&mLineInterval, sizeof(mLineInterval));
	inStream->ReadData(&mLineLength, sizeof(mLineLength));
}

CPiledMultiBarChartView::~CPiledMultiBarChartView() {
	if (mColorOfPiles != NULL)
		delete mColorOfPiles;
}

void CPiledMultiBarChartView::SetGraphData(const GraphData *graphData) {
	mGraphData = graphData;
	Refresh();
}

void CPiledMultiBarChartView::SetPixelPerValue(Int32 value, Boolean refresh) {
	mPixelPerValue = value;
	if (refresh)
		Refresh();
}

inline short _min(short a, short b) {
	return (a < b) ? a : b;
}

void CPiledMultiBarChartView::SetColorOfPiles(short count, const RGBColor *colors, Boolean refresh) {
	if (colors != NULL) {
		if (mColorOfPiles == NULL) {
			mColorOfPiles = new RGBColor[mPiles];
			#line 78
			ThrowIfNULL_(mColorOfPiles);
		}
		memset(mColorOfPiles, 0, mPiles * 4);

		::BlockMove(
			colors,
			mColorOfPiles,
			_min(count, mPiles) * sizeof(RGBColor)
		);

		if (refresh)
			Refresh();
	}
}

void CPiledMultiBarChartView::DrawSelf() {
	Rect theFrameRect;
	if (!CalcLocalFrameRect(theFrameRect))
		return;

	StColorPenState colorPenState;
	StColorPenState::Normalize();

	RGBColor *foreColor = (IsActive() && IsEnabled()) ? &UGAColorRamp::GetBlackColor() : &UGAColorRamp::GetColor(colorRamp_Gray10);

	::RGBForeColor(foreColor);
	::MoveTo(theFrameRect.left, theFrameRect.top);
	::LineTo(theFrameRect.left, theFrameRect.bottom - 1);
	::LineTo(theFrameRect.right - 1, theFrameRect.bottom - 1);

	Boolean drawBars = (mGraphData != NULL) && (mColorOfPiles != NULL) && (mPixelPerValue != 0);
	Boolean drawLines = (mLines > 0) && (mLineInterval > 0) && (mLineLength > 0);

	if (!mSkipDrawing) {
		if (drawLines) {
			int y = theFrameRect.bottom - 1;
			for (int i = 0; i < mLines; i++) {
				y -= mLineInterval;
				::MoveTo(theFrameRect.left, y);
				::LineTo(theFrameRect.left + mLineLength, y);
			}
		}

		if (drawBars) {
			Int16 bars = _min(mBars, mGraphData->bars);
			Int16 xPosition = mXOffset;

			for (int barIndex = 0; barIndex < bars; barIndex++) {
				Int16 yPosition = 0;
				Int16 piles = _min(mPiles, mGraphData->piles);

				for (int pileIndex = 0; pileIndex < piles; pileIndex++) {
					Int16 rawValue = mGraphData->data[pileIndex + barIndex * mGraphData->piles];
					Int16 value = rawValue / mPixelPerValue;
					if (value > 0) {
						Rect pileRect;
						::SetRect(&pileRect, xPosition, -(yPosition + value), xPosition + mBarWidth, -yPosition);
						::OffsetRect(&pileRect, theFrameRect.left, theFrameRect.bottom);
						yPosition += value;

						::RGBForeColor(foreColor);
						::FrameRect(&pileRect);
						::InsetRect(&pileRect, 1, 1);
						::RGBForeColor(&mColorOfPiles[pileIndex]);
						::PaintRect(&pileRect);
					}
				}

				xPosition += mBarInterval;
			}
		}
	}
}
