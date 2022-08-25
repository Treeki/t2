#pragma once

#include <LPicture.h>
#include <LBroadcaster.h>

enum EButtonState {
	EButtonState_Normal,
	EButtonState_Pushed,
	EButtonState_Disabled
};

class LPictButton : public LPicture, public LBroadcaster {
public:
	LPictButton(LStream *inStream);
	~LPictButton();
	void Setup(Int16 a, Int16 b, Int16 c, EButtonState buttonState);
	void ChangeStatus(EButtonState state);
	void Click(SMouseDownEvent &event);

protected:
	ResIDT mPicIDs[3];
	EButtonState mButtonState;
};
