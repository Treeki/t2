#pragma once

#include "T2HaveOutViewObject.h"

class T2OutObjDef;

class T2OutObj : public T2HaveOutViewObject {
public:
	T2OutObj();
	~T2OutObj();

	Int32 InitOutObj(T2OutObjDef *def, const Rect &rect, UInt32 valiation);
	void StartBuild(T2TowerDoc *doc);
	Int32 DoDestruct(T2TowerDoc *doc, Int16 s, Point ptA, Point ptB, Rect &rect);
	Int32 Destruct(T2TowerDoc *doc, Rect &rect);
	void GetOutObjArea(Rect &rect) const;
	void Draw(T2TowerDoc *doc, const Rect &rect);
	UInt32 Idle(T2TowerDoc *doc);
	void LoadSelf(LStream &stream, T2TowerDoc *doc);
	void SaveSelf(LStream &stream);

	UInt16 mToolType;
	Rect mOutObjArea;
	Int16 mDefIndex;
};
