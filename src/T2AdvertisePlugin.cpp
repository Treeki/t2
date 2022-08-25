#include "T2AdvertisePlugin.h"
#include "T2GWorld.h"
#include "T2WorldDef.h"

#include <LStream.h>
#include <LString.h>
#include <MacMemory.h>

T2AdvertisePlugin::T2AdvertisePlugin(UInt32 id, const FSSpec &spec)
	: T2SubPlugin(id, spec)
{
	mScreenResID = 0;
	for (Int32 i = 0; i < 256; i++)
		mPath[i] = 0;
	mScreen = 0;
	mC6 = 0;
	mDay = 0;
	mMoney = 0;
	mSubType = 0;
}

T2AdvertisePlugin::~T2AdvertisePlugin() {
	if (mScreen)
		delete mScreen;
}

void T2AdvertisePlugin::LoadRsrcFromStream(LStream &stream) {
	T2SubPlugin::LoadRsrcFromStream(stream);
	stream >> mSubType;
	stream >> mScreenResID;
	stream >> mC6;
	stream >> mDay;
	stream >> mMoney;
	stream >> mPath[0];
	for (Int16 i = 1; i <= mPath[0]; i++)
		stream >> mPath[i];
}

UInt32 T2AdvertisePlugin::UnfoldPluginSelf(T2WorldDef *worldDef) {
	if (mScreenResID != 0)
		mScreen = new T2GWorld(mScreenResID, 8, worldDef->mCTabH, 0, 0);
	return 0;
}

UInt32 T2AdvertisePlugin::GetSubType() {
	return mSubType;
}

UInt16 T2AdvertisePlugin::GetDay() {
	return mDay;
}

Int16 T2AdvertisePlugin::GetMoney() {
	return mMoney;
}

void T2AdvertisePlugin::GetPath(LStr255 &str) {
	::BlockMove(mPath, str, mPath[0] + 1);
}

T2GWorld *T2AdvertisePlugin::GetScreen() {
	return mScreen;
}

OSType T2AdvertisePlugin::GetRsrcType() {
	return 'AdDf';
}
