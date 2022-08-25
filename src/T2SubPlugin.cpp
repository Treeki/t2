#include "T2SubPlugin.h"
#include "T2WordDefArray.h"

#include <LHandleStream.h>
#include <LString.h>

T2SubPlugin::T2SubPlugin(UInt32 id, const FSSpec &spec)
	: CResourcePlugin(id, spec)
{
	for (Int32 i = 0; i < 64; i++)
		mTitle[i] = 0;

	mCustomerTableDefRes = 0;
	mDate = 0;
	mWordDefArray = 0;
	mOpenTime = 0;
	mCloseTime = 0;
}

T2SubPlugin::~T2SubPlugin() {
	if (mCustomerTableDefRes)
		::DisposeHandle(mCustomerTableDefRes);
	if (mWordDefArray)
		delete mWordDefArray;
}

void T2SubPlugin::GetTitle(LString &str) {
	LStr255 t(mTitle);
	str = t;
}

UInt32 T2SubPlugin::UnfoldPlugin(T2WorldDef *worldDef) {
	Int16 refNum = mFile->OpenResourceFork(1);
	UInt32 result = UnfoldPluginSelf(worldDef);
	mFile->CloseResourceFork();
	return result;
}

OSErr T2SubPlugin::LoadSelf() {
	Int16 refNum = mFile->OpenResourceFork(1);

	// UInt16 bindTime = GetBindTime();
	Int16 resCount = ::Count1Resources(GetRsrcType());
	Handle res = ::Get1IndResource(GetRsrcType(), 1);
	if (res) {
		::DetachResource(res);

		LHandleStream *stream;
		stream = new LHandleStream(res);
		LoadRsrcFromStream(*stream);
		delete stream;
	}

	mWordDefArray = T2WordDefArray::MakeWordDefArray();
	mFile->CloseResourceFork();

	return noErr;
}

void T2SubPlugin::LoadRsrcFromStream(LStream &stream) {
	for (Int16 i = 0; i < 64; i++)
		stream >> mTitle[i];

	stream >> mDate;

	if (mDate != 0) {
		DateTimeRec rec;

		rec.year = (mDate >> 28) & 0xF;
		rec.year *= 10;
		rec.year += (mDate >> 24) & 0xF;
		rec.year *= 10;
		rec.year += (mDate >> 20) & 0xF;
		rec.year *= 10;
		rec.year += (mDate >> 16) & 0xF;

		rec.month = (mDate >> 12) & 0xF;
		rec.month *= 10;
		rec.month += (mDate >> 8) & 0xF;

		rec.day = (mDate >> 4) & 0xF;
		rec.day *= 10;
		rec.day += (mDate & 0xF) + 1;

		rec.hour = rec.minute = rec.second = 0;

		::DateToSeconds(&rec, &mDate);
	}
}

UInt32 T2SubPlugin::UnfoldPluginSelf(T2WorldDef *worldDef) {
	return 0;
}

Handle T2SubPlugin::DupCustomerTableDefRes() {
	Handle h = mCustomerTableDefRes;
	return !::HandToHand(&h) ? h : 0;
}

Boolean T2SubPlugin::IsTieupFinish() {
	UInt32 check = 0;
	if (mDate != 0)
		::GetDateTime(&check);

	return check > mDate;
}

void T2SubPlugin::GlobalData(T2GlobalData *globalData) {
}

UInt16 T2SubPlugin::GetBindTime() {
	return 1;
}
