#pragma once

#include <LWindow.h>

class T2TowerDoc;

class T2MainWindow : public LWindow {
public:
	T2MainWindow(LStream *inStream);

	T2TowerDoc *mTowerDoc;
};
