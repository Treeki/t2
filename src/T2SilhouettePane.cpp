#include "T2SilhouettePane.h"
#include "URect.h"

#include <LStream.h>
#include <UDrawingState.h>
#include <UGAColorRamp.h>
#include <URegions.h>

T2SilhouettePane::T2SilhouettePane(LStream *stream)
	: LPane(stream)
{
	mRegion = ::NewRgn();
	mColorProvided = false;
	stream->ReadData(&m2C, sizeof(m2C));
	stream->ReadData(&m2E, sizeof(m2E));
}

T2SilhouettePane::~T2SilhouettePane() {
	if (mRegion)
		::DisposeRgn(mRegion);
}

void T2SilhouettePane::SetSilhouette(RgnHandle region) {
	if (region) {
		::CopyRgn(region, mRegion);
		Rect rect = (*mRegion)->rgnBBox;
		::OffsetRgn(mRegion, -rect.left, -rect.top);
	}
}

void T2SilhouettePane::DrawSelf() {
	Rect frameRect;
	if (mRegion && CalcLocalFrameRect(frameRect)) {
		StColorPenState state;
		state.Normalize();

		RGBColor *clr;
		if (mColorProvided) {
			clr = &mColor;
		} else {
			clr = (IsActive() && IsEnabled()) ? &UGAColorRamp::GetBlackColor() : &UGAColorRamp::GetColor(colorRamp_Gray10);
		}

		::RGBForeColor(clr);

		Rect outerRect = frameRect;
		Rect srcRect = (*mRegion)->rgnBBox;
		Rect dstRect = srcRect;

		dstRect.bottom *= m2C;
		dstRect.right *= m2C;

		StRegion rgn(mRegion);
		::MapRgn(rgn, &srcRect, &dstRect);
		::OffsetRgn(rgn,
			frameRect.left + ((URect::Width(outerRect) - URect::Width(dstRect)) / 2),
			frameRect.top + ((URect::Height(outerRect) - URect::Height(dstRect)) / 2)
		);
		::PaintRgn(rgn);
	}
}
