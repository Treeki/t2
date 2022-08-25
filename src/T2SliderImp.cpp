#include "T2GWorld.h"
#include "T2SliderImp.h"
#include "UT2Coordinate.h"
#include "URect.h"

#include <LControlPane.h>
#include <LStream.h>
#include <UDrawingUtils.h>
#include <UException.h>

T2SliderImp::T2SliderImp(LControlPane *pane)
	: LGAControlImp(pane)
{
	mWorld1 = 0;
	mWorld2 = 0;
	UT2Coordinate::MakeRect(mRect, 0, 0);
}

T2SliderImp::T2SliderImp(LStream *inStream)
	: LGAControlImp(inStream)
{
	mWorld1 = 0;
	mWorld2 = 0;
	UT2Coordinate::MakeRect(mRect, 0, 0);
}

T2SliderImp::~T2SliderImp() {
	delete mWorld1;
	delete mWorld2;
}

void T2SliderImp::Init(LControlPane *pane, LStream *stream) {
	mControlPane = pane;
	UT2Coordinate::MakeRect(mRect, 0, 0);

	ResIDT picID1;
	ResIDT picID2;
	(*stream) >> picID1;
	(*stream) >> picID2;
	(*stream) >> mRect;

	mWorld1 = new T2GWorld(picID1, 8, 0, 0, 0);
	mWorld2 = new T2GWorld(picID2, 8, 0, 0, 0);
	#line 90
	ThrowIfNil_(mWorld1);
	ThrowIfNil_(mWorld2);
}

void T2SliderImp::Init(LControlPane *pane, Int16 inControlKind, ConstStringPtr inTitle, ResIDT inTextTraitsID, Int32 inRefCon) {
	mControlPane = pane;
}

void T2SliderImp::DrawSelf() {
	Rect rect;
	CalcLocalFrameRect(rect);

	StColorDrawLoop loop(rect);
	Int16 depth;
	while (loop.NextDepth(depth)) {
		DrawIndicatorTrack(depth);

		Rect indRect;
		CalcIndicatorRect(indRect, ValueToPosition(mControlPane->GetValue()));
		DrawIndicator(depth, indRect, false);
	}
}

void T2SliderImp::DrawIndicatorTrack(Int16 depth) {
	StColorPenState::Normalize();

	Rect dstRect;
	if (CalcLocalFrameRect(dstRect) && mWorld1) {
		Rect srcRect;
		mWorld1->GetBounds(srcRect);
		mWorld1->CopyImage(mControlPane->GetMacPort(), srcRect, dstRect, 0, 0);
	}
}

void T2SliderImp::DrawIndicator(Int16 depth, const Rect &rect, bool flag) {
	short unused[1];
	unused[0] = -1;

	StColorPenState::Normalize();

	if (mWorld2) {
		Rect srcRect;
		mWorld2->GetBounds(srcRect);
		mWorld2->CopyImage(mControlPane->GetMacPort(), srcRect, rect, 0x24, 0);
	}
}

void T2SliderImp::EraseIndicator(Int16 depth, const Rect &rect) {
	DrawIndicatorTrack(depth);
}

void T2SliderImp::MoveIndicator(Int16 oldPos, Int16 newPos, bool flag) {
	Rect frameRect;
	CalcLocalFrameRect(frameRect);

	StColorDrawLoop loop(frameRect);
	Int16 depth;
	while (loop.NextDepth(depth)) {
		Rect newRect;
		CalcIndicatorRect(newRect, newPos);
		if (oldPos != newPos) {
			Rect oldRect;
			CalcIndicatorRect(oldRect, oldPos);

			StClipRgnState clip;
			clip.ClipToIntersection(oldRect);
			clip.DiffWithCurrent(newRect);
			EraseIndicator(depth, oldRect);
		}

		DrawIndicator(depth, newRect, flag);
	}
}

Int16 T2SliderImp::FindHotSpot(Point inPoint) const {
	return (PointInHotSpot(inPoint, 129) ? 129 : 0) & 0xFF;
}

Boolean T2SliderImp::PointInHotSpot(Point inPoint, Int16 inHotSpot) const {
	Boolean result = false;

	if (inHotSpot == 129) {
		Rect bounds;
		CalcIndicatorRect(bounds, ValueToPosition(mControlPane->GetValue()));
		result = ::PtInRect(inPoint, &bounds);
	}

	return result;
}

Boolean T2SliderImp::TrackHotSpot(Int16 inHotSpot, Point inPoint, Int16 inModifiers) {
	StColorPenState cps;

	Int16 startPos = ValueToPosition(mControlPane->GetValue());
	MoveIndicator(startPos, startPos, false);
	mPushed = true;

	Rect indRect;
	CalcIndicatorRect(indRect, startPos);

	Int16 indMin, indMax;
	FindIndicatorLimits(indMin, indMax);

	Rect trackRect;
	CalcTrackRect(trackRect);
	::InsetRect(&trackRect, -20, -20);

	Int16 currentPos = startPos;
	while (::StillDown()) {
		Point mousePt;
		::GetMouse(&mousePt);
		Int16 prevPos = currentPos;
		currentPos = startPos;

		if (::PtInRect(mousePt, &trackRect)) {
			currentPos += (mousePt.h - inPoint.h);
			if (currentPos < indMin)
				currentPos = indMin;
			else if (currentPos > indMax)
				currentPos = indMax;
		}

		currentPos = ValueToPosition(PositionToValue(currentPos));

		if (currentPos != prevPos) {
			MoveIndicator(prevPos, currentPos, false);
			mControlPane->SetValue(PositionToValue(currentPos));
			mControlPane->FocusDraw();
		}
	}

	mPushed = false;
	mControlPane->FocusDraw();

	if (currentPos != startPos) {
		MoveIndicator(currentPos, ValueToPosition(PositionToValue(currentPos)), false);
		mControlPane->SetValue(PositionToValue(currentPos));
	} else {
		MoveIndicator(startPos, startPos, false);
	}

	return false;
}

void T2SliderImp::SetValue(Int32 value) {
	Int32 oldValue = mControlPane->GetValue();
	if (!IsPushed() && value != oldValue) {
		mControlPane->FocusDraw();
		MoveIndicator(ValueToPosition(oldValue), ValueToPosition(value), false);
	}
}

void T2SliderImp::CalcIndicatorRect(Rect &rect, Int16 pos) const {
	Rect trackRect;
	CalcTrackRect(trackRect);

	Rect imgRect;
	mWorld2->GetBounds(imgRect);

	rect.left = pos;
	rect.right = pos + URect::Width(imgRect);
	rect.top = trackRect.top - (URect::Height(imgRect) - URect::Height(trackRect)) / 2;
	rect.bottom = rect.top + URect::Height(imgRect);
}

void T2SliderImp::CalcTrackRect(Rect &rect) const {
	Rect frameRect;
	CalcLocalFrameRect(frameRect);

	rect = mRect;
	::OffsetRect(&rect, frameRect.left, frameRect.top);
}

void T2SliderImp::FindIndicatorLimits(Int16 &indMin, Int16 &indMax) const {
	Rect trackRect;
	CalcTrackRect(trackRect);

	Rect imgRect;
	mWorld2->GetBounds(imgRect);

	indMin = trackRect.left;
	indMax = trackRect.right - (imgRect.right - imgRect.left);
}

Int32 T2SliderImp::PositionToValue(Int16 pos) const {
	Int16 indMin, indMax;
	FindIndicatorLimits(indMin, indMax);

	Int32 minValue = mControlPane->GetMinValue();
	Int32 maxValue = mControlPane->GetMaxValue();
	Int32 value = minValue;

	if (pos == indMax) {
		value = maxValue;
	} else if (pos != indMin) {
		double div = ((double)(maxValue - minValue) / (double)(indMax - indMin));
		value = 0.5 + ((div * (pos - indMin)) + minValue);
	}

	if (value > maxValue)
		value = maxValue;
	else if (value < minValue)
		value = minValue;

	return value;
}

Int16 T2SliderImp::ValueToPosition(Int32 value) const {
	Int16 indMin, indMax;
	FindIndicatorLimits(indMin, indMax);

	Int32 minValue = mControlPane->GetMinValue();
	Int32 maxValue = mControlPane->GetMaxValue();
	Int32 pos = indMin;

	if (value >= maxValue) {
		pos = indMax;
	} else if (value > minValue) {
		double div = (double)(indMax - indMin) / (double)(maxValue - minValue);
		pos = (div * (value - minValue)) + indMin;
	}

	return pos;
}
