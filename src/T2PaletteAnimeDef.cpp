#include "T2PaletteAnimeDef.h"

#include <LStream.h>
#include <UException.h>

T2PaletteAnimeDef::T2PaletteAnimeDef(LStream *stream) {
	Init();

	try {
		(*stream) >> mTowerCTabResID;
		(*stream) >> mPalette1ResID;
		(*stream) >> mInterCTabResID;
		(*stream) >> mDayLightPaletteResID;
		(*stream) >> mPalette2ResID;
		(*stream) >> mEntries;
		(*stream) >> mAnimatedColorCount;
		(*stream) >> mAnimatedColorStartIndex;
		(*stream) >> mRefractionColorCount;
		(*stream) >> mSkyColorCount;
		(*stream) >> mSEMaxCycles;
		(*stream) >> mSECycleColorCount;
		(*stream) >> mSECycleInterval;

		mCTab = MakeTowerCTab();
		#line 39
		ThrowIfNil_(mCTab);

		mPalette1 = ::GetNewPalette(mPalette1ResID);
		#line 43
		ThrowIfNil_(mPalette1);

		mPalette2 = ::GetNewPalette(mPalette2ResID);
		#line 47
		ThrowIfNil_(mPalette2);
	} catch (ExceptionCode code) {
		delete this;
		#line 52
		Throw_(code);
	}
}

void T2PaletteAnimeDef::Init() {
	mTowerCTabResID = 0;
	mPalette1 = 0;
	mPalette2 = 0;
}

CTabHandle T2PaletteAnimeDef::MakeTowerCTab() const {
	CTabHandle ctab = ::GetCTable(mTowerCTabResID);
	if (ctab)
		(*ctab)->ctFlags |= 0x4000;
	return ctab;
}

T2PaletteAnimeDef::~T2PaletteAnimeDef() {
	if (mCTab)
		::DisposeCTable(mCTab);
	if (mPalette1)
		::DisposePalette(mPalette1);
	if (mPalette2)
		::DisposePalette(mPalette2);
}

void T2PaletteAnimeDef::ForeColor(Int16 idx) const {
	RGBColor c;
	::GetEntryColor(mPalette1, idx, &c);
	::RGBForeColor(&c);
}

CTabHandle T2PaletteAnimeDef::MakeInterCTab() const {
	return ::GetCTable(mInterCTabResID);
}

PaletteHandle T2PaletteAnimeDef::MakeDayLightPalette() const {
	return ::GetNewPalette(mDayLightPaletteResID);
}

PaletteHandle T2PaletteAnimeDef::MakeMainWindowPalette() const {
	PaletteHandle pal = ::NewPalette(mEntries, mCTab, 2, 0);
	if (pal)
		SetPaletteEntry(pal, mAnimatedColorStartIndex, mAnimatedColorCount, pmAnimated | pmExplicit);
	return pal;
}

void T2PaletteAnimeDef::SetPaletteEntry(PaletteHandle pal, UInt32 startIndex, UInt32 count, Int16 usage) const {
	UInt32 endIndex = startIndex + count;
	for (UInt32 i = startIndex; i < endIndex; i++) {
		::SetEntryUsage(pal, i, usage, 0);
	}
}

void T2PaletteAnimeDef::ChangeSE(PaletteHandle pal, Int16 var) const {
	::CopyPalette(
		mPalette2,
		pal,
		mSECycleColorCount * var,
		mRefractionColorCount + mSkyColorCount,
		mSECycleColorCount
	);
}

