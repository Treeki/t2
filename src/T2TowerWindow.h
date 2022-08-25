#pragma once

#include "T2MainWindow.h"

class T2TowerWindow : public T2MainWindow {
public:
	T2TowerWindow(LStream *inStream);
	void InitTowerWindow(T2TowerDoc *towerDoc);
	void DoSetStandardSize(SDimension16 size);
	void DoSetZoom(Boolean flag);
	void ActivateSelf();
	void DeactivateSelf();
};
