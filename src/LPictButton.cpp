#include "LPictButton.h"

LPictButton::LPictButton(LStream *inStream)
	: LPicture(inStream)
{
	mPicIDs[0] = 0;
	mPicIDs[1] = 0;
	mPicIDs[2] = 0;
	mButtonState = EButtonState_Disabled;
}

LPictButton::~LPictButton() {
}

void LPictButton::Setup(Int16 a, Int16 b, Int16 c, EButtonState buttonState) {
	mPicIDs[0] = a;
	mPicIDs[1] = b;
	mPicIDs[2] = c;
	mButtonState = buttonState;
}

void LPictButton::ChangeStatus(EButtonState state) {
	if (mButtonState != state) {
		mButtonState = state;
		SetPictureID(mPicIDs[(int) state]);
		Refresh();
	}
}

void LPictButton::Click(SMouseDownEvent &event) {
	if (mButtonState == EButtonState_Normal)
		BroadcastMessage(812, this);
	LView::Click(event);
}
