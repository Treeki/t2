#pragma once

#include <PP_Types.h>
#include <Quickdraw.h>

class T2WeatherFilter {
public:
	enum EWeatherCode {
		EWeatherCode_0,
		EWeatherCode_1,
		EWeatherCode_2,
		EWeatherCode_3
	};

	EWeatherCode mCurrentWeather;
	EWeatherCode mNextWeather;
	Int16 mPhase;

	T2WeatherFilter();
	virtual ~T2WeatherFilter();

	void SetWeather(EWeatherCode code);
	void ColorFilter(RGBColor *clr);
	void ClearFilter(UInt32 time, RGBColor *clr);
	void RainyFilter(UInt32 time, RGBColor *clr);
	void SnowyFilter(UInt32 time, RGBColor *clr);
	void ColorFade(UInt32 time, RGBColor *a, RGBColor *b);
	void SkyColorFilter(RGBColor *clr);
	void ClearSkyFilter(UInt32 time, RGBColor *clr);
	void RainySkyFilter(UInt32 time, RGBColor *clr);
	void SnowySkyFilter(UInt32 time, RGBColor *clr);
	void ColorBlend(Int16 ratio, RGBColor *a, RGBColor *b);
	void Tick();

	UInt32 mLightningTime;
	UInt32 mLastChange;
	UInt32 mTimeSinceLastChange;
};
