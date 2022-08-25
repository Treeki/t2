#include "CCDROMDevice.h"
#include <Devices.h>

CCDROMDevice::CCDROMDevice() {
	mVolumeName = "\p";
	mStatus = false;
	mCRefNum = 0;
	mVRefNum = 0;
	mTocParam1 = 0;
	mTocParam2 = 0;
	mCurrTrack = 0;

	InitCDPB();
}

CCDROMDevice::~CCDROMDevice() {
	if (mStatus && IsPlaying())
		AudioStop();
}

void CCDROMDevice::Release() {
	if (mStatus && IsPlaying())
		AudioStop();

	mVolumeName = "\p";
	mStatus = false;
	mCRefNum = 0;
	mVRefNum = 0;
	mTocParam1 = 0;
	mTocParam2 = 0;
	mCurrTrack = 0;
	InitCDPB();
}

void CCDROMDevice::SetVolumeName(LStr255 str) {
	OSErr err;

	mVolumeName = str;

	if (mVolumeName[mVolumeName.Length()] != ':')
		mVolumeName.Append("\p:");

	if (WhereCDVol()) {
		err = ReadTOC();
		if (err != noErr) {
			mStatus = false;
		}
	}
}

void CCDROMDevice::GetVolumeName(LStr255 &str) {
	str = mVolumeName;
}

OSErr CCDROMDevice::AudioStop() {
	OSErr err;

	if (!mStatus) {
		return nsvErr;
	} else {
		if (mCurrTrack == 2)
			AudioTrackSearch(mTocParam2);

		InitCDPB();
		mParamBlock.csCode = 106;
		mParamBlock.csParam[0] = 2;
		mParamBlock.csParam[1] = 0;
		mParamBlock.csParam[2] = Dec2BCD(2);
		err = PBControlSync((ParmBlkPtr) &mParamBlock);
	}

	return err;
}

OSErr CCDROMDevice::AudioPause() {
	OSErr err;

	if (!mStatus) {
		return nsvErr;
	} else {
		short playing = IsPlaying() ? 1 : 0;

		InitCDPB();
		mParamBlock.csCode = 105;
		mParamBlock.csParam[0] = 0;
		mParamBlock.csParam[1] = playing;
		err = PBControlSync((ParmBlkPtr) &mParamBlock);
	}

	return err;
}

OSErr CCDROMDevice::AudioPlay(Int16 track) {
	OSErr err;

	if (!mStatus) {
		return nsvErr;
	} else {
		err = AudioTrackSearch(track);
		if (err == 0) {
			InitCDPB();
			mParamBlock.csCode = 104;
			mParamBlock.csParam[0] = 2;
			mParamBlock.csParam[1] = 0;
			mParamBlock.csParam[2] = Dec2BCD(track);
			mParamBlock.csParam[3] = -1;
			mParamBlock.csParam[4] = 9;
			err = PBControlSync((ParmBlkPtr) &mParamBlock);

			if (err == 0)
				mCurrTrack = track;
		}
	}

	return err;
}

void CCDROMDevice::InitCDPB() {
	mParamBlock.ioCompletion = NULL;
	mParamBlock.ioVRefNum = mVRefNum;
	mParamBlock.ioCRefNum = mCRefNum;
	mParamBlock.ioNamePtr = NULL;

	for (int i = 0; i < 11; i++)
		mParamBlock.csParam[i] = 0;
}

Int16 CCDROMDevice::BCD2Dec(Int16 num) {
	Int16 b = num & 0xFF;
	Int16 v = (b & 0xF) + (b >> 4) * 10;
	return v;
}

Int16 CCDROMDevice::Dec2BCD(Int16 num) {
	Int16 b = (num % 10) + ((num / 10) * 0x10);
	return b;
}

Boolean CCDROMDevice::WhereCDVol() {
	Boolean result = false;
	mStatus = false;

	HParamBlockRec block;
	block.volumeParam.ioCompletion = NULL;
	block.volumeParam.ioVolIndex = -1;
	block.volumeParam.ioNamePtr = mVolumeName;
	block.volumeParam.ioVRefNum = 0;

	OSErr err = PBHGetVInfoSync(&block);
	if (err == 0) {
		LStr255 str;
		DCtlHandle handle = GetDCtlEntry(block.volumeParam.ioVDRefNum);
		if (handle != NULL) {
			if ((*handle)->dCtlFlags & dRAMBased) {
				str = (StringPtr)( ((DRVRHeaderPtr)(*handle)->dCtlDriver)->drvrName );
			} else {
				str = (StringPtr)( (*(DRVRHeaderHandle)(*handle)->dCtlDriver)->drvrName );
			}

			if (EqualString(str, "\p.AppleCD", false, false) == true) {
				mCRefNum = block.volumeParam.ioVDRefNum;
				mVRefNum = block.volumeParam.ioVRefNum;
				mStatus = true;
				result = true;
			}
		}
	}

	return result;
}

Boolean CCDROMDevice::IsPlaying() {
	Boolean result = false;
	Byte a,b,c,d,e,f;

	OSErr err = GetAudioStuff(a, b, c, d, e, f);
	if (err == noErr) {
		result = a == 0;
	}

	return result;
}

OSErr CCDROMDevice::GetAudioStuff(Byte &a, Byte &b, Byte &c, Byte &d, Byte &e, Byte &f) {
	OSErr err;

	if (!mStatus) {
		return nsvErr;
	} else {
		InitCDPB();
		mParamBlock.csCode = 107;
		err = PBControlSync((ParmBlkPtr) &mParamBlock);
		if (err == 0) {
			a = ((Byte *) mParamBlock.csParam)[0];
			b = ((Byte *) mParamBlock.csParam)[1];
			c = ((Byte *) mParamBlock.csParam)[2];
			d = ((Byte *) mParamBlock.csParam)[3];
			e = ((Byte *) mParamBlock.csParam)[4];
			f = ((Byte *) mParamBlock.csParam)[5];
		}
	}

	return err;
}

OSErr CCDROMDevice::ReadTOC() {
	OSErr err;

	if (!mStatus) {
		return nsvErr;
	} else {
		InitCDPB();
		mParamBlock.csCode = 100;
		mParamBlock.csParam[0] = 1;

		err = PBControlSync((ParmBlkPtr) &mParamBlock);
		if (err == 0) {
			mTocParam1 = BCD2Dec(mParamBlock.csParam[0] >> 8);
			mTocParam2 = BCD2Dec(mParamBlock.csParam[0] & 0xFF);
		}
	}

	return err;
}

OSErr CCDROMDevice::AudioTrackSearch(Int16 track) {
	OSErr err;

	if (!mStatus) {
		return nsvErr;
	} else {
		InitCDPB();
		mParamBlock.csCode = 103;
		mParamBlock.csParam[0] = 2;
		mParamBlock.csParam[1] = 0;
		mParamBlock.csParam[2] = Dec2BCD(track);
		mParamBlock.csParam[3] = 0;
		mParamBlock.csParam[4] = 9;
		err = PBControlSync((ParmBlkPtr) &mParamBlock);
	}

	return err;
}
