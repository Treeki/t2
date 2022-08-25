#include "CRepeater.h"
#include <URegions.h>

CRepeater *CRepeater::CreateCRepeaterStream(LStream *inStream) {
	return new CRepeater(inStream);
}

CRepeater::CRepeater(LStream *inStream)
	: LButton(inStream)
{
	m_startTicks = 30;
	m_repeatTicks = 5;
}

CRepeater::~CRepeater() {
}

Boolean CRepeater::TrackHotSpot(Int16 inHotSpot, Point inPoint, Int16 inModifiers) {
	Boolean currInside, prevInside;
	int tc, threshold;
	int startTickCount = ::TickCount();

	if (inHotSpot != 0) {
		tc = ::TickCount();
		HotSpotAction(inHotSpot, true, false);
		while (tc - startTickCount < m_startTicks) {
			tc = ::TickCount();
			if (!::StillDown()) {
				HotSpotResult(inHotSpot);
				return false;
			}
		}
	}

	currInside = true;
	prevInside = false;
	HotSpotAction(inHotSpot, currInside, prevInside);
	HotSpotResult(inHotSpot);

	StRegion region;
	::GetClip(region);

	threshold = ::TickCount() + m_repeatTicks;
	Point mousePoint = inPoint;

	while (::StillDown()) {
		::GetMouse(&mousePoint);
		prevInside = currInside;
		currInside = (PointInHotSpot(mousePoint, inHotSpot) && ::PtInRgn(mousePoint, region));
		if (threshold < ::TickCount()) {
			HotSpotResult(inHotSpot);
			threshold = m_repeatTicks + ::TickCount();
		}
	}

	EventRecord event;

	if (::GetOSEvent(mUpMask, &event)) {
		mousePoint = event.where;
		::GlobalToLocal(&mousePoint);

		prevInside = currInside;
		currInside = (PointInHotSpot(mousePoint, inHotSpot) && ::PtInRgn(mousePoint, region));

		HotSpotAction(inHotSpot, currInside, prevInside);
	}

	return currInside;
}
