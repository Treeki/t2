#include "T2Slider.h"
#include <LControlImp.h>

T2Slider::T2Slider(LStream *inStream)
	: LControlPane(inStream)
{
	Int16 value = mValue;
	MakeControlImp('T2si', inStream);
	mValue = value;

	InitSlider();
}

void T2Slider::InitSlider() {
	if (mValue < mMinValue)
		mValue = mMinValue;
	else if (mValue > mMaxValue)
		mValue = mMaxValue;

	mControlImp->SetValue(mValue);
}

T2Slider::~T2Slider() {
}

void T2Slider::DoTrackAction(Int16 s, Int32 value) {
	LControl::SetValue(value);
}
