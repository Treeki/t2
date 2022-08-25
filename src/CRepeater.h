#pragma once

#include <LButton.h>

class CRepeater : public LButton {
public:
	enum { class_ID = 'rept' };

	static CRepeater *CreateCRepeaterStream(LStream *inStream);

	CRepeater(LStream *inStream);
	~CRepeater();
	Boolean TrackHotSpot(Int16 inHotSpot, Point inPoint, Int16 inModifiers);

protected:
	short m_startTicks, m_repeatTicks;
};
