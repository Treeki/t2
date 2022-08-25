#include "CSpinButtons.h"
#include <LCommander.h>
#include <LStream.h>
#include <UReanimator.h>
#include <URegions.h>

CSpinButtons *CSpinButtons::CreateCSpinButtonsStream(LStream *inStream) {
	return new CSpinButtons(inStream);
}
CSpinButtons::CSpinButtons(LStream *inStream)
	: LView(inStream)
	, LListener()
	, LBroadcaster()
	, mCaption(NULL)
	, mUp(NULL)
	, mDown(NULL)
{
	inStream->ReadData(&mValueMessage, sizeof(mValueMessage));
	inStream->ReadData(&mValue, sizeof(mValue));
	inStream->ReadData(&mMinValue, sizeof(mMinValue));
	inStream->ReadData(&mMaxValue, sizeof(mMaxValue));
	inStream->ReadData(&mResourceID, sizeof(mResourceID));
	mString = mValue;
}

CSpinButtons::~CSpinButtons() {
}

void CSpinButtons::FinishCreateSelf() {
	LView::FinishCreateSelf();

	if (mResourceID != 0) {
		LView *view = UReanimator::CreateView(mResourceID, this, LCommander::GetDefaultCommander());
		#line 46
		ThrowIfNULL_(view);
	}

	mCaption = dynamic_cast<LCaption *>(FindPaneByID('spcp'));
	mUp = dynamic_cast<LButton *>(FindPaneByID('spup'));
	mDown = dynamic_cast<LButton *>(FindPaneByID('spdn'));

	#line 51
	ThrowIfNULL_(mUp);
	#line 52
	ThrowIfNULL_(mDown);

	if (mCaption)
		mCaption->SetValue(mString);

	mUp->AddListener(this);
	mUp->SetValueMessage('spdn');

	mDown->AddListener(this);
	mDown->SetValueMessage('spup');

	SetMinValue(0);
	SetMaxValue(30);
	SetValue(10);
}

void CSpinButtons::ListenToMessage(MessageT inMessage, void *ioParam) {
	switch (inMessage) {
		case 'spdn':
			if (mValue < mMaxValue) {
				mValue++;
				mString = mValue;
				if (mCaption != NULL) {
					mCaption->SetValue(mString);

					Rect rect;
					if (CalcPortFrameRect(rect)) {
						StRegion region(rect);
						mCaption->Draw(region);
					}
				}
				BroadcastValueMessage();
			}
			break;
		case 'spup':
			if (mMinValue < mValue) {
				mValue--;
				mString = mValue;
				if (mCaption != NULL) {
					mCaption->SetValue(mString);

					Rect rect;
					if (CalcPortFrameRect(rect)) {
						StRegion region(rect);
						mCaption->Draw(region);
					}
				}
				BroadcastValueMessage();
			}
			break;
	}
}

MessageT CSpinButtons::GetValueMessage() const {
	return mValueMessage;
}

void CSpinButtons::SetValueMessage(MessageT valueMessage) {
	mValueMessage = valueMessage;
}

void CSpinButtons::SetMinValue(Int32 minValue) {
	mMinValue = minValue;
}

void CSpinButtons::SetMaxValue(Int32 maxValue) {
	mMaxValue = maxValue;
}

void CSpinButtons::SetValue(Int32 value) {
	mValue = value;
	mString = mValue;
	if (mCaption != NULL) {
		mCaption->SetValue(mString);

		Rect rect;
		if (CalcPortFrameRect(rect)) {
			StRegion region(rect);
			mCaption->Draw(region);
		}
	}
}

Int32 CSpinButtons::GetValue() const {
	return mValue;
}

void CSpinButtons::BroadcastValueMessage() {
	if (mValueMessage != 0) {
		Int32 data = mValue;
		BroadcastMessage(mValueMessage, &data);
	}
}
