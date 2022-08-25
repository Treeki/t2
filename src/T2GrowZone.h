#pragma once

#include <LGrowZone.h>

class T2TowerDoc;

class T2GrowZone : public LGrowZone {
public:
	static void SetTowerDoc(T2TowerDoc *doc);
	T2GrowZone(Size inReserveSize);
	~T2GrowZone();
	void SpendTime(const EventRecord &event);

protected:
	static T2TowerDoc *sTowerDoc;
};
