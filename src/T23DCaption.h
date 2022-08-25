#pragma once

#include <LCaption.h>

class T23DCaption : public LCaption {
public:
	enum { class_ID = '3DCp' };

	T23DCaption(LStream *inStream);

	static T23DCaption *CreateT23DCaptionStream(LStream *inStream);

protected:
	virtual void DrawSelf();

	short mInverted;
};
