#pragma once

#include "T2ToolDef.h"

class T2Equip;
class T2EquipPlugin;
class T2GWorld;
class T2WordDefArray;

class T2EquipDef : public T2ToolDef {
public:
	enum EOffscreenKind {
		EOffscreenKind_0
	};

	T2EquipDef(UInt32 id, LStream *stream, T2WorldDef *worldDef, T2EquipPlugin *equipPlugin);
	void Init();
	~T2EquipDef();
	Int32 GetInMoney(UInt32 index) const;
	void ChangeOffscreen(EOffscreenKind offscreenKind);
	Boolean HasDrawOutViewProc() const;
	virtual void DrawGhostProc(T2Equip *equip, T2GWorld *gworld);
	virtual void DrawOutViewProc(T2Equip *equip, const Rect &rect, T2TowerDoc *doc);
	virtual ResIDT GetInfoDialogIDProc(T2TowerDoc *doc, T2Equip *equip);
	virtual Int32 GetInfoProc(T2TowerDoc *doc, T2Equip *equip);
	virtual void ConstrainMouseProc(Rect *rectA, Rect *rectB);
	virtual Int32 GetDestructPartProc(Int16 var, Point ptA, Point ptB, T2Equip *equip);
	Int32 GetClickPartProc(T2TowerDoc *doc, T2Equip *equip, Point pt, Int16 *s);
	Int32 MakeCursorProc(T2WorldDef *worldDef, T2GWorld **gworld, Int16 var);
	Int32 EmergencyProc(T2TowerDoc *doc, T2Equip *equip);
	Int32 BurntDownProc(T2TowerDoc *doc, T2Equip *equip);
	Int32 DrawData(Int32 pos);
	Int16 DrawAttribute(Int16 pos);

	Int16 GetEquipType() const { return mToolType; }
	Int16 GetCapacity() const { return mCapacity; }
	UInt32 GetAttribute() const { return mAttribute; }
	Int16 GetNumOfInMoney() const { return mNumOfInMoney; }
	RgnHandle GetMask(Int32 i) const { return mMask[i]; }

	Int16 mCapacity;
	Int16 mStress;
	RgnHandle mMask[kMaxValiation];
	ResIDT mOffOptionResIDs[kMaxValiation];
	T2GWorld *mOffOption[kMaxValiation];
	Int16 mOutSpan;
	Int16 mInSpan;
	Int16 mInitInMoney;
	T2WordDefArray *mWordDefArray;
	Int16 mNumOfInMoney;
	Int32 mInMoney[4];
	EOffscreenKind mOffscreenKind;
};
