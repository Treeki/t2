#pragma once

#include <LString.h>

class UDebugUtils {
public:
	static void HexString(const void *data, LStr255 &str);
	static void BitString(const void *data, LStr255 &str);
	static void RectString(const Rect &rect, LStr255 &str);
	static void HVString(const Rect &rect, LStr255 &str);
};
