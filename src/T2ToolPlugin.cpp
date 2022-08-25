#include "T2GWorld.h"
#include "T2HaveOutViewObject.h"
#include "T2ToolDef.h"
#include "T2ToolPlugin.h"
#include "T2WorldDef.h"
#include "UT2Coordinate.h"

#include <LStream.h>

T2ToolPlugin::T2ToolPlugin(UInt32 id, const FSSpec &spec)
	: CProgramPlugin(id, spec)
{
	mDefIdleProc = 0;
	mClickProc = 0;
	mConstrainMouseProc = 0;
	mAreaCheckProc = 0;
	mAreaCheck2Proc = 0;
	mDoBuildProc = 0;
	mBuildFinishProc = 0;
	mBuildOptionProc = 0;
	mDestructProc = 0;
	mDestructFinishProc = 0;
	mGetDestructPartProc = 0;
	mMakeCursorProc = 0;
	mGetInfoSetupProc = 0;
	mGetInfoOKProc = 0;
	mGetInfoCancelProc = 0;
	mGetInfoListenProc = 0;
	mIsAbleDragMakingProc = 0;
	mLoadExtraDataProc = 0;
	mSaveExtraDataProc = 0;
	mCalcMentenanceCostProc = 0;
}

T2ToolPlugin::~T2ToolPlugin() {
}

UInt32 T2ToolPlugin::GetSubPluginType() {
	if (mTemplatePlugin)
		return ((T2ToolDef *) mTemplatePlugin)->GetSubPluginType();
	else
		return 0;
}

OSErr T2ToolPlugin::LoadAllTemplatePlugin(T2WorldDef *, Int16, T2TemplatePluginDB *) {
	return 32000;
}

void T2ToolPlugin::DefIdleProc(T2TowerDoc *doc) {
	if (mDefIdleProc)
		mDefIdleProc(this, doc);
}

Boolean T2ToolPlugin::ClickProc(T2TowerDoc *doc, Int16 &s, Point pt, Rect *rect, Boolean flag) {
	if (mClickProc) {
		return mClickProc(this, doc, s, pt, rect, flag);
	} else if (mTemplatePlugin) {
		UT2Coordinate::MakeCenterRect(
			*rect, pt,
			((T2ToolDef *) mTemplatePlugin)->mWidth,
			((T2ToolDef *) mTemplatePlugin)->mHeight
			);
		return true;
	} else {
		return false;
	}
}

void T2ToolPlugin::ConstrainMouseProc(Rect *rectA, Rect *rectB) {
	if (mConstrainMouseProc)
		mConstrainMouseProc(this, rectA, rectB);
}

Int32 T2ToolPlugin::AreaCheckProc(T2TowerDoc *doc, Rect *rectA, Rect *rectB, T2Equip *equip) {
	Int32 result = -1;
	if (mAreaCheckProc)
		result = mAreaCheckProc(this, doc, rectA, rectB, equip);
	return result;
}

Int32 T2ToolPlugin::AreaCheck2Proc(T2TowerDoc *doc, Rect &rect, UInt32 var, Boolean flag) {
	Int32 result = 1;
	if (mAreaCheck2Proc)
		result = mAreaCheck2Proc(this, doc, rect, var, flag);
	return result;
}

Int32 T2ToolPlugin::DoBuildProc(T2TowerDoc *doc, T2ToolDef *toolDef, Rect *rect) {
	Int32 result = 0;
	if (mDoBuildProc)
		result = mDoBuildProc(this, doc, toolDef, rect);
	return result;
}

void T2ToolPlugin::BuildFinishProc(T2TowerDoc *doc, T2HaveOutViewObject *obj) {
	if (mBuildFinishProc)
		mBuildFinishProc(this, doc, obj);
}

void T2ToolPlugin::BuildOptionProc(T2TowerDoc *doc, T2Equip *equip) {
	if (mBuildOptionProc)
		mBuildOptionProc(this, doc, equip);
}

Int32 T2ToolPlugin::DestructProc(T2TowerDoc *doc, T2HaveOutViewObject *obj, Point pt, Rect *rect) {
	Int32 result = 0;
	if (mDestructProc)
		result = mDestructProc(this, doc, obj, pt, rect);
	return result;
}

void T2ToolPlugin::DestructFinishProc(T2TowerDoc *doc, T2HaveOutViewObject *obj) {
	if (mDestructFinishProc)
		mDestructFinishProc(this, doc, obj);
}

Int32 T2ToolPlugin::GetDestructPartProc(Int16 var, Point ptA, Point ptB, T2Equip *equip) {
	Int32 result = -1;
	if (mGetDestructPartProc)
		result = mGetDestructPartProc(this, var, ptA, ptB, equip);
	return result;
}

Int32 T2ToolPlugin::GetInfoSetupProc(T2TowerDoc *doc, T2HaveOutViewObject *obj, LDialogBox *dialog) {
	if (mGetInfoSetupProc)
		return mGetInfoSetupProc(this, doc, obj, dialog);
	else
		return -1;
}

Int32 T2ToolPlugin::GetInfoOKProc(T2TowerDoc *doc, T2HaveOutViewObject *obj, LDialogBox *dialog) {
	if (mGetInfoOKProc)
		return mGetInfoOKProc(this, doc, obj, dialog);
	else
		return -1;
}

Int32 T2ToolPlugin::GetInfoCancelProc(T2TowerDoc *doc, T2HaveOutViewObject *obj, LDialogBox *dialog) {
	if (mGetInfoCancelProc)
		return mGetInfoCancelProc(this, doc, obj, dialog);
	else
		return -1;
}

Int32 T2ToolPlugin::GetInfoListenProc(T2TowerDoc *doc, T2HaveOutViewObject *obj, LDialogBox *dialog, MessageT message, void *ioParam) {
	if (mGetInfoListenProc)
		return mGetInfoListenProc(this, doc, obj, dialog, message, ioParam);
	else
		return 0;
}

Int16 T2ToolPlugin::IsAbleDragMakingProc(T2ToolDef *toolDef, Int16 which) {
	Boolean result;
	if (mIsAbleDragMakingProc)
		result = mIsAbleDragMakingProc(this, which);
	else
		result = toolDef->IsSetAttribute(0x80);
	return result;
}

Int32 T2ToolPlugin::CalcMentenanceCostProc(const T2HaveOutViewObject *obj) const {
	Int32 result = 0;
	if (mCalcMentenanceCostProc) {
		result = mCalcMentenanceCostProc(this, obj);
	} else {
		T2ToolDef *def = (T2ToolDef *) mTemplatePlugin;
		if (def && def->IsSetAttribute(0x100)) {
			result = def->GetOutMoney(obj->GetValiation());
		}
	}
	return result;
}

void T2ToolPlugin::LoadExtraData(LStream &stream, T2TowerDoc *doc, T2HaveOutViewObject *obj) {
	if (mLoadExtraDataProc) {
		mLoadExtraDataProc(this, stream, doc, obj);
	} else {
		Int32 size;
		stream >> size;

		if (size > 0) {
			for (Int32 i = 0; i < size; i++) {
				Byte b;
				stream >> b;
			}
		}
	}
}

void T2ToolPlugin::SaveExtraData(LStream &stream, T2HaveOutViewObject *obj) {
	if (mSaveExtraDataProc) {
		mSaveExtraDataProc(this, stream, obj);
	} else {
		Int32 size = 0;
		stream << size;
	}
}

CPluginInfo *T2ToolPlugin::GetPluginInfo() {
	CPluginInfo *info = CFilePlugin::GetPluginInfo();
	if (info) {
		T2ToolDef *def = (T2ToolDef *) mTemplatePlugin;
		Boolean flag = false;
		if (def)
			flag = def->mCurBuildCount > 0;
		info->_14C = flag;
	}

	return info;
}

Int32 T2ToolPlugin::MakeCursorProc(T2WorldDef *worldDef, T2GWorld **gworld, Int16 var) {
	*gworld = 0;

	Int32 result;
	(void)result; // mess with the register allocator
	if (mMakeCursorProc) {
		result = mMakeCursorProc(this, worldDef, gworld, var);
	} else {
		result = DefMakeCursorProc(worldDef, gworld, var);
	}
	return result;
}

Int32 T2ToolPlugin::DefMakeCursorProc(T2WorldDef *worldDef, T2GWorld **gworld, Int16 var) {
	*gworld = 0;
	if (!mTemplatePlugin)
		return -1;

	T2ToolDef *toolDef = (T2ToolDef *) mTemplatePlugin;
	Rect unitRect, qdRect, boundsRect;

	UT2Coordinate::MakeRect(unitRect, toolDef->mWidth, toolDef->mHeight);
	UT2Coordinate::UnitToQD(unitRect, qdRect, 0, 0);
	::SetRect(&boundsRect, 0, 0, qdRect.right - qdRect.left, qdRect.bottom - qdRect.top);

	T2GWorld *world = new T2GWorld(boundsRect, 8, worldDef->mCTabH, 0, 0);
	toolDef->mOffscreen[var]->CopyOffImage(world, boundsRect, boundsRect, 0, 0);
	*gworld = world;
	return 0;
}
