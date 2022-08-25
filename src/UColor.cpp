#include "UColor.h"

void UColor::MakeDark(RGBColor &clr, UInt16 factor) {
	if (clr.red < factor)
		clr.red = 0;
	else
		clr.red -= factor;

	if (clr.green < factor)
		clr.green = 0;
	else
		clr.green -= factor;

	if (clr.blue < factor)
		clr.blue = 0;
	else
		clr.blue -= factor;
}
