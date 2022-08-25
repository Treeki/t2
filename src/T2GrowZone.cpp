#include "T2GrowZone.h"
#include "T2TowerDoc.h"

T2TowerDoc *T2GrowZone::sTowerDoc;

void T2GrowZone::SetTowerDoc(T2TowerDoc *doc) {
	sTowerDoc = doc;
}

T2GrowZone::T2GrowZone(Size inReserveSize)
	: LGrowZone(inReserveSize)
{
}

T2GrowZone::~T2GrowZone() {
}

void T2GrowZone::SpendTime(const EventRecord &event) {
	if (mLocalReserve == 0 || *mLocalReserve == 0) {
		if (::MaxBlock() > mReserveSize + 2048) {
			if (mLocalReserve == 0) {
				mLocalReserve = ::NewHandle(mReserveSize);
			} else {
				::ReallocateHandle(mLocalReserve, mReserveSize);
			}

			if (::MemError() == noErr)
				mGiveWarning = false;
		}
	}

	if (mGiveWarning) {
		if (sTowerDoc) {
			sTowerDoc->DoEmergency();
		} else {
			if (::GetResource('ALRT', 0xCC))
				::CautionAlert(0xCC, 0);
		}
		mGiveWarning = false;
	}
}
