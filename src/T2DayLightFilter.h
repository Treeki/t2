#pragma once

#include <PP_Types.h>
#include <Quickdraw.h>

class T2DayLightFilter {
public:
	T2DayLightFilter();
	virtual ~T2DayLightFilter();

	void SetTime(Int16 a, Int16 b);
	void RefractionColor(RGBColor *clr);
	void CalcDayLightColor(RGBColor *clr);
	void SkyColor(RGBColor *clr);

protected:
	RGBColor mColor;
	Int16 mTime;
};
