#pragma once

#include <LArray.h>

class LStream;
class T2GWorld;
class T2HaveOutViewObject;
class T2Tenant;
class T2ToolDef;
class T2TowerDoc;
class T2WorldDef;

class T2TowerEvent {
public:
	T2TowerEvent(T2WorldDef *worldDef);

	// todo
	void InitTowerEvent(T2TowerDoc *doc);
	void Write(LStream &stream);
	void Read(LStream &stream);
	void StopEvent();
	void *GetFireBurning();
	void *GetMetroRailway();
	void *GetBlackOut();
	Boolean IsBlackOut();
	void SetLatestBuild(T2HaveOutViewObject *obj, T2ToolDef *toolDef, Boolean flag);
	void *GetTowerVision();
	void *GetRubble();
	void *GetReggae();
	void DrawRubble(T2TowerDoc *doc, T2Tenant *tenant);
	Boolean Idle(T2TowerDoc *doc);
	void ViewModeChanged(T2TowerDoc *doc, Int16 mode);

	unsigned char gapToB0[0xB0];
};
