#pragma once

#include "T2SubPlugin.h"

class T2GWorld;

class T2AdvertisePlugin : public T2SubPlugin {
public:
	T2AdvertisePlugin(UInt32 id, const FSSpec &spec);
	~T2AdvertisePlugin();
	void LoadRsrcFromStream(LStream &stream);
	UInt32 UnfoldPluginSelf(T2WorldDef *worldDef);
	OSType GetSubType();
	UInt16 GetDay();
	Int16 GetMoney();
	void GetPath(LStr255 &str);
	T2GWorld *GetScreen();
	OSType GetRsrcType();

	OSType mSubType;
	ResIDT mScreenResID;
	Int16 mC6;
	UInt16 mDay;
	Int16 mMoney;
	Str255 mPath;
	T2GWorld *mScreen;
};
