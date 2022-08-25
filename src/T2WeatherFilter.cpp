#include "T2WeatherFilter.h"

#include <Events.h>
#include <stdlib.h>

T2WeatherFilter::T2WeatherFilter() {
	mCurrentWeather = EWeatherCode_0;
	mPhase = 2;
	SetWeather(EWeatherCode_0);
}

T2WeatherFilter::~T2WeatherFilter() {
}

void T2WeatherFilter::SetWeather(EWeatherCode code) {
	mLastChange = ::TickCount();
	mTimeSinceLastChange = mLastChange;
	mNextWeather = code;
	mLightningTime = (UInt32) -1;
}

void T2WeatherFilter::ColorFilter(RGBColor *clr) {
	if (mCurrentWeather == EWeatherCode_1)
		RainyFilter(mTimeSinceLastChange, clr);
	else if (mCurrentWeather == EWeatherCode_2)
		SnowyFilter(mTimeSinceLastChange, clr);
	else
		ClearFilter(mTimeSinceLastChange, clr);
}

void T2WeatherFilter::ClearFilter(UInt32 time, RGBColor *clr) {
	if (mPhase != 1 && mPhase != 2 && mPhase != 3) {
	}
}

void T2WeatherFilter::RainyFilter(UInt32 time, RGBColor *clr) {
	if (mLightningTime <= time && time <= (mLightningTime + 200)) {
		RGBColor c;
		c.red = 240;
		c.green = 240;
		c.blue = 128;
		ColorBlend(40, clr, &c);
	} else {
		RGBColor c;
		c.red = (clr->red * 500) / 1000u;
		c.green = (clr->green * 500) / 1000u;
		c.blue = (clr->blue * 600) / 1000u;
		ColorFade(time, clr, &c);
	}
}

void T2WeatherFilter::SnowyFilter(UInt32 time, RGBColor *clr) {
	RGBColor c;
	c.red = ((clr->red + (((0xFFFF - clr->red) * 500) / 1000u)) * 800) / 1000u;
	c.green = ((clr->green + (((0xFFFF - clr->green) * 500) / 1000)) * 800) / 1000u;
	c.blue = ((clr->blue + (((0xFFFF - clr->blue) * 500) / 1000)) * 800) / 1000u;
	ColorFade(time, clr, &c);
}

void T2WeatherFilter::ColorFade(UInt32 time, RGBColor *a, RGBColor *b) {
	if (mPhase == 1 && time <= 2500) {
		a->red = ((a->red * (2500 - time)) + (b->red * time)) / 2500;
		a->green = ((a->green * (2500 - time)) + (b->green * time)) / 2500;
		a->blue = ((a->blue * (2500 - time)) + (b->blue * time)) / 2500;
	} else if (mPhase == 3 && time <= 2500) {
		a->red = ((b->red * (2500 - time)) + (a->red * time)) / 2500;
		a->green = ((b->green * (2500 - time)) + (a->green * time)) / 2500;
		a->blue = ((b->blue * (2500 - time)) + (a->blue * time)) / 2500;
	} else {
		*a = *b;
	}
}

void T2WeatherFilter::SkyColorFilter(RGBColor *clr) {
	if (mCurrentWeather == EWeatherCode_1)
		RainySkyFilter(mTimeSinceLastChange, clr);
	else if (mCurrentWeather == EWeatherCode_2)
		SnowySkyFilter(mTimeSinceLastChange, clr);
	else
		ClearSkyFilter(mTimeSinceLastChange, clr);
}

void T2WeatherFilter::ClearSkyFilter(UInt32 time, RGBColor *clr) {
	if (mPhase != 1 && mPhase != 2 && mPhase != 3) {
	}
}

void T2WeatherFilter::RainySkyFilter(UInt32 time, RGBColor *clr) {
	if (time >= 1800 && time <= 1900) {
		RGBColor c;
		c.red = 240;
		c.green = 240;
		c.blue = 128;
		ColorBlend(15, clr, &c);
		mLightningTime = 8000 + (rand() % 15000);
	} else if (mLightningTime <= time && time <= (mLightningTime + 200)) {
		RGBColor c;
		c.red = 240;
		c.green = 240;
		c.blue = 128;
		ColorBlend(30, clr, &c);
		mLightningTime += 8000 + (rand() % 15000);
	} else {
		UInt32 z = (clr->red * 33 + clr->green * 42 + clr->blue * 25) / 100u;
		RGBColor c;
		c.red = (z * 128) / 0xFFFF;
		c.green = (z * 128) / 0xFFFF;
		c.blue = (z * 140) / 0xFFFF;
		ColorFade(time, clr, &c);
	}
}

void T2WeatherFilter::SnowySkyFilter(UInt32 time, RGBColor *clr) {
	UInt32 z = (clr->red * 33 + clr->green * 42 + clr->blue * 25) / 100u;
	RGBColor c;
	UInt32 r = 80 + ((z * 180) / 0xFFFF);
	UInt32 g = 80 + ((z * 180) / 0xFFFF);
	UInt32 b = 80 + ((z * 180) / 0xFFFF);
	c.red = ((UInt16) r <= 0xFFFF) ? r : 0xFFFF;
	c.green = ((UInt16) g <= 0xFFFF) ? g : 0xFFFF;
	c.blue = ((UInt16) b <= 0xFFFF) ? b : 0xFFFF;
	ColorFade(time, clr, &c);
}

void T2WeatherFilter::ColorBlend(Int16 ratio, RGBColor *a, RGBColor *b) {
	a->red = ((a->red * (100 - ratio)) + (b->red * ratio)) / 100u;
	a->green = ((a->green * (100 - ratio)) + (b->green * ratio)) / 100u;
	a->blue = ((a->blue * (100 - ratio)) + (b->blue * ratio)) / 100u;
}

void T2WeatherFilter::Tick() {
	mTimeSinceLastChange = ::TickCount() - mLastChange;
	if (mPhase == 2 && mCurrentWeather != mNextWeather) {
		mPhase = 3;
		mLastChange = ::TickCount();
	}
	if (mPhase == 1 && (mTimeSinceLastChange >= 2500 || mCurrentWeather == EWeatherCode_0)) {
		mPhase = 2;
		mLastChange = ::TickCount();
	}
	if (mPhase == 3 && (mTimeSinceLastChange >= 2500 || mCurrentWeather == EWeatherCode_0)) {
		mPhase = 1;
		mCurrentWeather = mNextWeather;
		mLastChange = ::TickCount();
	}
}
