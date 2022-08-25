#include "T2DateTime.h"
#include "T2DayLightFilter.h"
#include "T2PaletteAnime.h"
#include "T2WeatherFilter.h"
#include "T2WorldDef.h"
#include "T2WorldPlugin.h"

#include <LStream.h>
#include <LWindow.h>
#include <UException.h>

T2PaletteAnime::T2PaletteAnime(T2WorldDef *worldDef, LWindow *window, T2DateTime *dateTime) {
	Init();

	mWorldDef = worldDef;
	#line 31
	ThrowIfNil_(mWorldDef);

	T2WorldDef *wd = mWorldDef;
	mWorldPlugin = (T2WorldPlugin *) wd->mProgramPlugin;
	#line 33
	ThrowIfNil_(mWorldPlugin);

	mPaletteAnimeDef = worldDef->mPaletteAnimeDef;
	#line 35
	ThrowIfNil_(mPaletteAnimeDef);

	mWindow = window;
	T2PaletteAnimeDef *def1 = mPaletteAnimeDef;
	mAnimatedColorCount = def1->mAnimatedColorCount;
	T2PaletteAnimeDef *def2 = mPaletteAnimeDef;
	mAnimatedColorStartIndex = def2->mAnimatedColorStartIndex;
	T2PaletteAnimeDef *def3 = mPaletteAnimeDef;
	mRefractionColorCount = def3->mRefractionColorCount;
	T2PaletteAnimeDef *def4 = mPaletteAnimeDef;
	mSkyColorCount = def4->mSkyColorCount;
	T2PaletteAnimeDef *def5 = mPaletteAnimeDef;
	mSEMaxCycles = def5->mSEMaxCycles;
	T2PaletteAnimeDef *def6 = mPaletteAnimeDef;
	mSECycleInterval = def6->mSECycleInterval;

	T2WorldDef *wd2 = (T2WorldDef *) mWorldDef;
	T2WorldPlugin *wp2 = (T2WorldPlugin *) wd2->mProgramPlugin;
	#line 45
	ThrowIfNil_(wp2);

	mHasPluginFastSE = (wp2->mChangeFastSEProc != 0);
	mHasPluginSE = (wp2->mChangeSEProc != 0);
	mHasPluginSkyState = (wp2->mAdjustSkyStateProc != 0);
	mHasPluginSkyColor = (wp2->mChangeSkyColorProc != 0);

	wp2->mFile->OpenResourceFork(1);

	try {
		mInterCTab = mPaletteAnimeDef->MakeInterCTab();
		#line 58
		ThrowIfNil_(mInterCTab);

		mModifiedPalette = ::NewPalette(mAnimatedColorCount, mInterCTab, pmTolerant, 0);
		#line 62
		ThrowIfNil_(mModifiedPalette);

		mDayLightPalette = mPaletteAnimeDef->MakeDayLightPalette();
		#line 66
		ThrowIfNil_(mDayLightPalette);

		wp2->mFile->CloseResourceFork();

		mDayLightFilter = new T2DayLightFilter;
		mWeatherFilter = new T2WeatherFilter;

		SetMainWindowPalette();
		AdjustWindowColor(dateTime);

	} catch (ExceptionCode code) {
		wp2->mFile->CloseResourceFork();
		delete this;
		#line 83
		Throw_(code);
	}
}

void T2PaletteAnime::Init() {
	mWorldDef = 0;
	mWorldPlugin = 0;
	mPaletteAnimeDef = 0;
	mWindow = 0;
	mAnimatedColorCount = 0;
	mAnimatedColorStartIndex = 0;
	mModifiedPalette = 0;
	mInterCTab = 0;
	mDayLightPalette = 0;
	mHasPluginFastSE = false;
	mHasPluginSE = false;
	mHasPluginSkyState = false;
	mHasPluginSkyColor = false;
	mPaletteUpdated = false;
	m2A = 0;
	mSkyChangeCountdown = 0;
	mSETimeCounter = 0;
	mSEMaxCycles = 0;
	mSECycleIndex = 0;
	mSECycleInterval = 0;
	mSETimeNextTick = 0;
	mDayLightFilter = 0;
	mWeatherFilter = 0;
}

void T2PaletteAnime::SetMainWindowPalette() {
	PaletteHandle pal = mPaletteAnimeDef->MakeMainWindowPalette();
	#line 134
	ThrowIfNil_(pal);

	::SetPalette(mWindow->GetMacPort(), pal, true);
}

void T2PaletteAnime::AdjustWindowColor(T2DateTime *dateTime) {
	AdjustSkyState(dateTime);
	ChangeSkyColor();
	ChangeSE();
	DoAnimatePalette();
}

T2PaletteAnime::~T2PaletteAnime() {
	if (mModifiedPalette)
		::DisposePalette(mModifiedPalette);
	if (mInterCTab)
		::DisposeCTable(mInterCTab);
	if (mDayLightPalette)
		::DisposePalette(mDayLightPalette);
	if (mDayLightFilter)
		delete mDayLightFilter;
	if (mWeatherFilter)
		delete mWeatherFilter;
}

Boolean T2PaletteAnime::IsSETime() {
	Boolean result = false;
	UInt32 ticks = ::TickCount();

	if (mSETimeNextTick <= ticks) {
		mSETimeNextTick = ticks + 2;
		mSETimeCounter++;
		if (mSETimeCounter >= 60)
			mSETimeCounter = 0;
		result = true;
	}

	return result;
}

void T2PaletteAnime::ChangeSE() {
	if (mHasPluginFastSE)
		mPaletteUpdated = mWorldPlugin->ChangeFastSEProc(mWorldDef, this);

	if ((mSETimeCounter % mSECycleInterval) == 0) {
		mSECycleIndex++;
		if (mSECycleIndex >= mSEMaxCycles)
			mSECycleIndex = 0;

		mPaletteAnimeDef->ChangeSE(mModifiedPalette, mSECycleIndex);
		if (mHasPluginSE)
			mWorldPlugin->ChangeSEProc(mWorldDef, this);
		mPaletteUpdated = true;
	}
}

void T2PaletteAnime::RotateDayLightPalette(UInt16 start, UInt16 count) const {
	RotatePalette(mDayLightPalette, start, count);
	RotatePalette(mModifiedPalette, start, count);
}

void T2PaletteAnime::RotatePalette(PaletteHandle pal, UInt16 start, UInt16 count) const {
	RGBColor clr, clr2;
	::GetEntryColor(pal, start, &clr);

	for (Int32 i = start + 1; i < (start + count); i++) {
		::GetEntryColor(pal, i, &clr2);
		::SetEntryColor(pal, i - 1, &clr2);
	}

	::SetEntryColor(pal, start + count - 1, &clr);
}

void T2PaletteAnime::AdjustSkyState(T2DateTime *dateTime) {
	if (mHasPluginSkyState)
		mWorldPlugin->AdjustSkyStateProc(mWorldDef, this, dateTime);
	else
		mDayLightFilter->SetTime(0, (dateTime->mHourMinute * 1000) / 1440u);
}

Boolean T2PaletteAnime::IsChangeSkyTime() {
	Boolean result = false;

	if (mSkyChangeCountdown > 0) {
		mSkyChangeCountdown--;
		if ((mSkyChangeCountdown % 6u) == 0)
			result = true;
	}

	return result;
}

void T2PaletteAnime::ChangeSkyColor() {
	if (mHasPluginSkyColor) {
		mPaletteUpdated = mWorldPlugin->ChangeSkyColorProc(mWorldDef, this);
	} else {
		for (UInt32 i = 0; i < mRefractionColorCount; i++) {
			RGBColor clr;
			::GetEntryColor(mDayLightPalette, i, &clr);
			mDayLightFilter->RefractionColor(&clr);
			::SetEntryColor(mModifiedPalette, i, &clr);
		}
		for (UInt32 i = 0; i < mSkyColorCount; i++) {
			RGBColor clr;
			::GetEntryColor(mDayLightPalette, i + mRefractionColorCount, &clr);
			mDayLightFilter->SkyColor(&clr);
			::SetEntryColor(mModifiedPalette, i + mRefractionColorCount, &clr);
		}
		mPaletteUpdated = true;
	}
}

void T2PaletteAnime::MinuteChanged(T2DateTime *dateTime) {
	UInt32 minute = dateTime->GetMinutes();
	if (mHasPluginSkyColor) {
		if (minute == 1)
			AdjustSkyState(dateTime);
		if (IsChangeSkyTime())
			ChangeSkyColor();
	} else {
		if ((minute % 6) == 0) {
			AdjustSkyState(dateTime);
			ChangeSkyColor();
		}
	}
}

void T2PaletteAnime::DoAnimatePalette() {
	if (mPaletteUpdated) {
		::Palette2CTab(mModifiedPalette, mInterCTab);
		::AnimatePalette(mWindow->GetMacPort(), mInterCTab, 0, mAnimatedColorStartIndex, mAnimatedColorCount);
		mPaletteUpdated = false;
	}
}

void T2PaletteAnime::ForeColor(Int16 idx) {
	mPaletteAnimeDef->ForeColor(idx);
}

void T2PaletteAnime::ReplaceDayLightPalette(ResIDT resID) {
	GetWorldDef()->GetWorldPlugin()->GetFile()->OpenResourceFork(1);

	PaletteHandle pal = ::GetNewPalette(resID);
	if (pal) {
		if (mDayLightPalette)
			::DisposePalette(mDayLightPalette);
		mDayLightPalette = pal;
	}

	GetWorldDef()->GetWorldPlugin()->GetFile()->CloseResourceFork();
}

void T2PaletteAnime::GetRGBColor(Int16 idx, RGBColor &clr) const {
	T2PaletteAnimeDef *def = GetPaletteAnimeDef();
	::GetEntryColor(def->mPalette1, idx, &clr);
}
