#pragma once

#include "T2PaletteAnimeDef.h"

class LWindow;
class T2DateTime;
class T2DayLightFilter;
class T2WeatherFilter;
class T2WorldDef;
class T2WorldPlugin;

class T2PaletteAnime {
public:
	T2PaletteAnime(T2WorldDef *worldDef, LWindow *window, T2DateTime *dateTime);
	void Init();
	void SetMainWindowPalette();
	void AdjustWindowColor(T2DateTime *dateTime);
	virtual ~T2PaletteAnime();
	Boolean IsSETime();
	void ChangeSE();
	void RotateDayLightPalette(UInt16 start, UInt16 count) const;
	void RotatePalette(PaletteHandle pal, UInt16 start, UInt16 count) const;
	void AdjustSkyState(T2DateTime *dateTime);
	Boolean IsChangeSkyTime();
	void ChangeSkyColor();
	void MinuteChanged(T2DateTime *dateTime);
	void DoAnimatePalette();
	void ForeColor(Int16 idx);
	void ReplaceDayLightPalette(ResIDT resID);
	void GetRGBColor(Int16 idx, RGBColor &clr) const;

	T2WorldDef *GetWorldDef() const { return mWorldDef; }
	T2WorldPlugin *GetWorldPlugin() const { return mWorldPlugin; }
	T2PaletteAnimeDef *GetPaletteAnimeDef() const { return mPaletteAnimeDef; }

	T2WorldDef *mWorldDef;
	T2WorldPlugin *mWorldPlugin;
	T2PaletteAnimeDef *mPaletteAnimeDef;
	LWindow *mWindow;

	Int16 mAnimatedColorCount;
	Int16 mAnimatedColorStartIndex;
	PaletteHandle mModifiedPalette;
	CTabHandle mInterCTab;
	PaletteHandle mDayLightPalette;
	Boolean mHasPluginFastSE;
	Boolean mHasPluginSE;
	Boolean mHasPluginSkyState;
	Boolean mHasPluginSkyColor;
	Boolean mPaletteUpdated;

	Int16 m2A;
	Int16 mSkyChangeCountdown;
	Int16 mRefractionColorCount;
	Int16 mSkyColorCount;
	Int16 mSETimeCounter;
	Int16 mSEMaxCycles;
	Int16 mSECycleIndex;
	Int16 mSECycleInterval;
	UInt32 mSETimeNextTick;

	T2DayLightFilter *mDayLightFilter;
	T2WeatherFilter *mWeatherFilter;
};
