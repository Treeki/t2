#pragma once

#include <LString.h>

class UT2Utils {
public:
	static UInt32 Randomize(UInt32 bound);
	static Int32 Float2Int(Float32 f);
	static void GetRoomNumberString(Int32 num, LString &str);
	static void GetHourMinute(Int16 time, Int16 &hour, Int16 &minute);
	static void GetMonetaryString(Int32 value, LString &str);
};
