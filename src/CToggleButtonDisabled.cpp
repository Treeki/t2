#include "CToggleButtonDisabled.h"
#include <LStream.h>

CToggleButtonDisabled *CToggleButtonDisabled::CreateCToggleButtonDisabledStream(LStream *inStream) {
	return new CToggleButtonDisabled(inStream);
}

CToggleButtonDisabled::CToggleButtonDisabled(LStream *inStream)
	: LToggleButton(inStream)
{
	inStream->ReadData(&mDisabledID, sizeof(mDisabledID));
}

void CToggleButtonDisabled::DrawSelf() {
	if (mEnabled != triState_On) {
		DrawGraphic(mDisabledID);
	} else {
		LToggleButton::DrawSelf();
	}
}

void CToggleButtonDisabled::DisableSelf() {
	FocusDraw();
	DrawSelf();
}

void CToggleButtonDisabled::EnableSelf() {
	FocusDraw();
	DrawSelf();
}
