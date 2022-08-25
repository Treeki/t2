#pragma once

#include "T2DrawableObject.h"

class CResourcePlugin;
class T2ToolDef;

class T2HaveOutViewObject : public T2DrawableObject {
public:
	T2HaveOutViewObject();
	~T2HaveOutViewObject();
	Int32 GetRefCon();
	void SetRefCon(Int32 v);
	CResourcePlugin *GetSubPlugin() const;
	void SetSubPlugin(CResourcePlugin *plugin);
	T2ToolDef *GetToolDef() const;
	void SetToolDef(T2ToolDef *toolDef);
	virtual void DrawOutView(T2TowerDoc *doc, const Rect &rect);
	void SetUsed(Boolean value);
	void InitLoaded();
	Int32 CalcMentenanceCost(T2TowerDoc *doc) const;

	UInt32 GetValiation() const { return mValiation; }

	T2ToolDef *mToolDef;
	Int32 mRefCon;
	CResourcePlugin *mSubPlugin;
	UInt32 mValiation;
};
