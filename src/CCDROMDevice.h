#pragma once

#include <LString.h>

class CCDROMDevice {
public:
	CCDROMDevice();
	virtual ~CCDROMDevice();

	void Release();
	void SetVolumeName(LStr255);
	void GetVolumeName(LStr255 &);
	OSErr AudioStop();
	OSErr AudioPause();
	OSErr AudioPlay(Int16 track);
	void InitCDPB();
	Int16 BCD2Dec(Int16);
	Int16 Dec2BCD(Int16);
	Boolean WhereCDVol();
	Boolean IsPlaying();
	OSErr GetAudioStuff(Byte &, Byte &, Byte &, Byte &, Byte &, Byte &);
	OSErr ReadTOC();
	OSErr AudioTrackSearch(Int16 track);

protected:
	LStr255 mVolumeName;
	Boolean mStatus;
	short mCRefNum, mVRefNum;
	CntrlParam mParamBlock;
	short mTocParam1, mTocParam2;
	short mCurrTrack;
};
