#include "T2DayLightFilter.h"

#include <math.h>

T2DayLightFilter::T2DayLightFilter() {
	mColor.red = 0;
	mColor.green = 0;
	mColor.blue = 0;
	mTime = 0;
}

T2DayLightFilter::~T2DayLightFilter() {
}

void T2DayLightFilter::SetTime(Int16 a, Int16 b) {
	double time;
	double base = (sin(2.0 * (3.141592 * (a / 1000.0))) * 8.0) + 500.0;
	double midpoint = 1000.0 - base;
	double low = midpoint / 2.0;
	double high = 1000.0 - (midpoint / 2.0);

	if (b < low) {
		time = -90.0 * cos((3.141592 * (b / (midpoint / 2.0))) / 2.0);
	} else if (b < high) {
		time = 90.0 * sin(3.141592 * ((b - low) / base));
	} else {
		time = -90.0 * sin((3.141592 * ((b - high) / (midpoint / 2.0))) / 2.0);
	}

	if (time < 0.0) {
		mTime = -(-time + 0.5);
	} else {
		mTime = time + 0.5;
	}

	if (mTime > 90)
		mTime = 90;
	if (mTime < -90)
		mTime = -90;

	while (mTime < 0) {
		mTime += 360;
	}
	while (mTime >= 360) {
		mTime -= 360;
	}

	CalcDayLightColor(&mColor);
}

void T2DayLightFilter::RefractionColor(RGBColor *clr) {
	clr->red = (((double) mColor.red) * ((double) clr->red)) / 65535.0;
	clr->green = (((double) mColor.green) * ((double) clr->green)) / 65535.0;
	clr->blue = (((double) mColor.blue) * ((double) clr->blue)) / 65535.0;
}

void T2DayLightFilter::CalcDayLightColor(RGBColor *clr) {
	double base = (0.5 * sin((3.141592 * mTime) / 180.0)) + 0.5;
	if (base < 0.0)
		base = 0.0;

	double outR = base;
	double outG = base;
	double outB = base;

	double tint1 = 1.1 * sin((3.141592 * mTime) / 180.0);
	if (tint1 > 1.0)
		tint1 = 1.0;
	else if (tint1 < 0.1)
		tint1 = 0.1;

	outG *= 1.0 - (0.8 * (1.0 - tint1));
	outB *= tint1;
	outR = 0.4 + outR;
	outG = 0.4 + outG;
	outB = 0.4 + outB;

	double tint2 = 0.2 + (0.35 * outR) + (0.45 * outG) + (0.2 * outB);
	if (tint2 > 1.0)
		tint2 = 1.0;

	outR *= tint2;
	outG *= 1.0 - (0.7 * (1.0 - tint2));

	if (1.0 < ((outR < 0.0) ? 0.0 : outR))
		outR = 1.0;
	else if (outR < 0.0)
		outR = 0.0;

	if (1.0 < ((outG < 0.0) ? 0.0 : outG))
		outG = 1.0;
	else if (outG < 0.0)
		outG = 0.0;

	if (1.0 < ((outB < 0.0) ? 0.0 : outB))
		outB = 1.0;
	else if (outB < 0.0)
		outB = 0.0;

	clr->red = outR * 65535.0;
	clr->green = outG * 65535.0;
	clr->blue = outB * 65535.0;
}

void T2DayLightFilter::SkyColor(RGBColor *clr) {
	double inR = mColor.red / 65535.0;
	double inG = mColor.green / 65535.0;
	double inB = mColor.blue / 65535.0;

	double outR = inR;
	double outG = inG;
	double outB = inB;

	outR *= (clr->red / 65535.0);
	outG *= (clr->green / 65535.0);
	outB *= (clr->blue / 65535.0);

	outR = (0.45 * outR) + (0.55 * inR);
	outG = (0.6 * outG) + (0.4 * inG);
	outB = (0.6 * outB) + (0.4 * inB);

	clr->red = 65535.0 * outR;
	clr->green = 65535.0 * outG;
	clr->blue = 65535.0 * outB;
}
