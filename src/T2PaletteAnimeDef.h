#pragma once

#include <PP_Types.h>
#include <Palettes.h>

class LStream;

class T2PaletteAnimeDef {
public:
	T2PaletteAnimeDef(LStream *stream);
	virtual ~T2PaletteAnimeDef();

	void Init();
	CTabHandle MakeTowerCTab() const;
	void ForeColor(Int16 idx) const;
	CTabHandle MakeInterCTab() const;
	PaletteHandle MakeDayLightPalette() const;
	PaletteHandle MakeMainWindowPalette() const;
	void SetPaletteEntry(PaletteHandle pal, UInt32 startIndex, UInt32 count, Int16 usage) const;
	void ChangeSE(PaletteHandle pal, Int16 var) const;

	CTabHandle GetCTabH() const { return mCTab; }

	ResIDT mTowerCTabResID;
	ResIDT mPalette1ResID;
	ResIDT mInterCTabResID;
	ResIDT mDayLightPaletteResID;
	ResIDT mPalette2ResID;
	Int16 mEntries;
	Int16 mAnimatedColorCount;
	Int16 mAnimatedColorStartIndex;
	Int16 mRefractionColorCount;
	Int16 mSkyColorCount;
	Int16 mSEMaxCycles;
	Int16 mSECycleColorCount;
	Int16 mSECycleInterval;
	CTabHandle mCTab;
	PaletteHandle mPalette1;
	PaletteHandle mPalette2;
};
