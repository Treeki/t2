#pragma once

#include <LToggleButton.h>

class CToggleButtonDisabled : public LToggleButton {
public:
	enum { class_ID = 'tbtd' };

	CToggleButtonDisabled(LStream *inStream);

	static CToggleButtonDisabled *CreateCToggleButtonDisabledStream(LStream *inStream);

protected:
	virtual void DrawSelf();
	virtual void EnableSelf();
	virtual void DisableSelf();

	ResIDT mDisabledID;
};
