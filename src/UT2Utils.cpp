#include "UT2Utils.h"
#include <Quickdraw.h>

UInt32 UT2Utils::Randomize(UInt32 bound) {
	UInt32 result = 0;

	if (bound > 1) {
		int n = ::Random();
		if (n < 0)
			n *= -1;
		result = (n * bound) >> 15;
	}

	return result;
}

Int32 UT2Utils::Float2Int(Float32 f) {
	UInt32 result = 0;

	if (f > 0.0f) {
		result = f;
		UInt32 delta = 10.0f * (f - result);

		if (delta != 0 && Randomize(10) < delta) {
			result++;
		}
	}

	return result;
}

void UT2Utils::GetRoomNumberString(Int32 num, LString &str) {
	str = num;
	if (str[1] == '-')
		str[1] = 'B';
}

void UT2Utils::GetHourMinute(Int16 time, Int16 &hour, Int16 &minute) {
	hour = time / 60;
	minute = time % 60;
}

void UT2Utils::GetMonetaryString(Int32 value, LString &str) {
	Boolean isNegative = (value < 0);
	if (value < 0)
		value = -value;

	str.Assign(value);

	int length = str.Length();
	if (length > 3) {
		int offset = length % 3;
		int groups = length / 3;
		if (offset == 0) {
			offset += 3;
			groups--;
		}

		for (int i = groups - 1; i >= 0; i--) {
			str.Insert(',', offset + i * 3 + 1);
		}
	}

	if (isNegative)
		str.Insert('-', 0);
}
