#pragma once

#include "CResourcePlugin.h"

class T2GlobalData;
class T2WordDefArray;
class T2WorldDef;

class T2SubPlugin : public CResourcePlugin {
public:
	T2SubPlugin(UInt32 id, const FSSpec &spec);
	~T2SubPlugin();

	void GetTitle(LString &str);
	UInt32 UnfoldPlugin(T2WorldDef *worldDef);
	OSErr LoadSelf();
	Handle DupCustomerTableDefRes();
	Boolean IsTieupFinish();

	// 0x24
	virtual OSType GetRsrcType() { return 0; }
	virtual void GlobalData(T2GlobalData *globalData);
	virtual UInt16 GetBindTime();
	virtual void LoadRsrcFromStream(LStream &stream);
	virtual UInt32 UnfoldPluginSelf(T2WorldDef *worldDef);

	Str63 mTitle;
	T2WordDefArray *mWordDefArray;
	UInt32 mDate;
	UInt16 mOpenTime;
	UInt16 mCloseTime;
	Handle mCustomerTableDefRes;
};
