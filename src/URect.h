#pragma once

#include <Quickdraw.h>

class URect {
public:
	static inline short Width(const Rect &rect) {
		return rect.right - rect.left;
	}

	static inline short Height(const Rect &rect) {
		return rect.bottom - rect.top;
	}

	// assumed name, might not actually exist
	static inline void MoveToZero(Rect &rect) {
		::OffsetRect(&rect, -rect.left, -rect.top);
	}

	// TODO
	static void SetEmpty(Rect &rect);
	static void Center(const Rect &input, Rect &output, Boolean flag);
};
