#pragma once

#include <LArray.h>
#include <LPeriodical.h>
#include <LString.h>

class CFilePlugin;
class LWindow;
class InfoBarMsgItem;
class T2Balloon;
class T2Equip;
class T2EquipDef;
class T2People;
class T2PluginSound;
class T2TowerDoc;

class T2TowerMessage : public LPeriodical {
public:
	T2TowerMessage(T2TowerDoc *towerDoc);
	~T2TowerMessage();
	void InfoBarMessage(const LString &str, Int16 a, Int16 b, T2PluginSound *pluginSound, CFilePlugin *filePlugin);
	void CancelInfoBarMessage(const LString &str);
	void PassiveInfoBarMessage(const LString &str, Int16 a);
	void SetInfoBarMsg(InfoBarMsgItem *item);
	void EquipBalloonMessage(const LString &str, T2Equip *equip);
	void PeopleBalloonMessage(const LString &str, T2People *people);
	void EquipBalloonMessage(const LString &str, Point pt);
	void BuildErr(const LString &str);
	void BuildErr(UInt32 a, T2EquipDef *equipDef);
	Boolean GetBuildErrString(UInt32 a, LString &str);
	void ClearBuildErr();
	void ObjectBalloonMessage(const LString &str, const Rect &rect);
	void InfoDialogMessage(const LString &str, PaneIDT paneID, Int16 timeout);
	void AleatMessage(const LString &str, ResIDT id);
	void SpendTime(const EventRecord &event);
	LWindow *FindFloatingWindow(Int16 var);

	T2TowerDoc *mTowerDoc;
	void *m8;
	Int16 mCurResFile;
	LArray *mArray;
	Boolean m14;
	T2Balloon *mBalloon;
};

class InfoBarMsgItem {
public:
	InfoBarMsgItem(const LString &str, Int16 a, Int16 b, T2PluginSound *pluginSound, CFilePlugin *filePlugin);
	~InfoBarMsgItem();

	LStr255 mString;
	Int16 m10C;
	UInt32 m110;
	Int16 m114;
	T2PluginSound *mPluginSound;
	CFilePlugin *mFilePlugin;
};
