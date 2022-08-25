#include "T2HaveOutViewObject.h"
#include "T2ToolDef.h"
#include "T2TowerDoc.h"

#include <UException.h>

T2HaveOutViewObject::T2HaveOutViewObject() {
	mToolDef = 0;
	mRefCon = 0;
	mSubPlugin = 0;
	mValiation = 0;
}

T2HaveOutViewObject::~T2HaveOutViewObject() {
}

Int32 T2HaveOutViewObject::GetRefCon() {
	return mRefCon;
}

void T2HaveOutViewObject::SetRefCon(Int32 v) {
	mRefCon = v;
}

CResourcePlugin *T2HaveOutViewObject::GetSubPlugin() const {
	return mSubPlugin;
}

void T2HaveOutViewObject::SetSubPlugin(CResourcePlugin *plugin) {
	mSubPlugin = plugin;
}

T2ToolDef *T2HaveOutViewObject::GetToolDef() const {
	return mToolDef;
}

void T2HaveOutViewObject::SetToolDef(T2ToolDef *toolDef) {
	mToolDef = toolDef;
}

void T2HaveOutViewObject::DrawOutView(T2TowerDoc *, const Rect &) {
}

void T2HaveOutViewObject::SetUsed(Boolean value) {
	T2Object::SetUsed(value);
	if (GetToolDef()) {
		if (value)
			GetToolDef()->DoStartUse();
		else
			GetToolDef()->DoEndUse();
	}
}

void T2HaveOutViewObject::InitLoaded() {
	T2Object::InitLoaded();
	if (IsUsed() && GetToolDef())
		GetToolDef()->DoStartUse();
}

Int32 T2HaveOutViewObject::CalcMentenanceCost(T2TowerDoc *doc) const {
	#line 140
	Assert_(mToolDef != 0);

	Int32 cost = mToolDef->CalcMentenanceCostProc(this);
	doc->DoPayTool(cost, 0, mToolDef);
	return cost;
}
