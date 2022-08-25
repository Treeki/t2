#include "T2EquipPlugin.h"

T2EquipPlugin::T2EquipPlugin(UInt32 id, const FSSpec &spec)
	: T2ToolPlugin(id, spec)
{
	mDrawOutViewProc = 0;
	mGetInfoDialogIDProc = 0;
	mGetInfoProc = 0;
	mEC = 0;
	mCalcMentenanceCostProc = 0;
	mEmergencyProc = 0;
	mBurntDownProc = 0;
}

T2EquipPlugin::~T2EquipPlugin() {
}

void T2EquipPlugin::DrawOutViewProc(T2Equip *equip, const Rect &rect, T2TowerDoc *doc) {
	if (mDrawOutViewProc) {
		Rect rectCopy = rect;
		mDrawOutViewProc(this, doc, equip, rectCopy);
	}
}

Int32 T2EquipPlugin::GetInfoDialogIDProc(T2TowerDoc *doc, T2Equip *equip) {
	return mGetInfoDialogIDProc ? mGetInfoDialogIDProc(this, doc, equip) : 7000;
}

Int32 T2EquipPlugin::GetInfoProc(T2TowerDoc *doc, T2Equip *equip) {
	if (mGetInfoProc)
		return mGetInfoProc(this, doc, equip);
	else
		return -1;
}

Int32 T2EquipPlugin::GetClickPartProc(T2TowerDoc *doc, T2Equip *equip, Point pt, Int16 *s) {
	return 0;
}

Int32 T2EquipPlugin::EmergencyProc(T2TowerDoc *doc, T2Equip *equip) {
	Int32 result = 0;

	if (mEmergencyProc)
		result = mEmergencyProc(this, doc, equip);

	return result;
}

Int32 T2EquipPlugin::BurntDownProc(T2TowerDoc *doc, T2Equip *equip) {
	Int32 result = 0;

	if (mBurntDownProc)
		result = mBurntDownProc(this, doc, equip);

	return result;
}
