#include "UDebugUtils.h"

void UDebugUtils::HexString(const void *data, LStr255 &str) {
	int outPos = 3;
	str.Assign("\p0x");

	const unsigned char *input = (const unsigned char *) data;
	for (int i = 0; i < 4; i++) {
		unsigned char byte = input[i];
		unsigned char hi = byte >> 4;
		unsigned char lo = byte & 0xF;
		if (hi > 9)
			str[outPos] = ('A' - 10) + hi;
		else
			str[outPos] = '0' + hi;
		if (lo > 9)
			str[outPos + 1] = ('A' - 10) + lo;
		else
			str[outPos + 1] = '0' + lo;
		outPos += 2;
	}

	str[0] = outPos - 1;
}

void UDebugUtils::BitString(const void *data, LStr255 &str) {
	int outPos = 3;
	unsigned char mask = 0x80;
	str.Assign("\p0b");

	const unsigned char *input = (const unsigned char *) data;
	for (int i = 0; i < 4; i++) {
		unsigned char byte = input[i];
		if (byte == 0) {
			for (int j = 0; j < 8; j++) {
				str[outPos + j] = '0';
			}
			outPos += 8;
		} else {
			for (int j = 0; j < 8; j++) {
				if (byte & (mask >> j)) {
					str[outPos] = '1';
				} else {
					str[outPos] = '0';
				}
				outPos++;
			}
		}
	}

	str[0] = outPos - 1;
}

void UDebugUtils::RectString(const Rect &rect, LStr255 &str) {
	LStr255 tmp;

	str = (Int32) rect.left;
	str.Append("\p, ");

	tmp = (Int32) rect.top;
	str.Append(tmp);
	str.Append("\p, ");

	tmp = (Int32) rect.right;
	str.Append(tmp);
	str.Append("\p, ");

	tmp = (Int32) rect.bottom;
	str.Append(tmp);
}

void UDebugUtils::HVString(const Rect &rect, LStr255 &str) {
	LStr255 tmp;

	str.Assign("\p(h=");

	tmp = (Int32) (rect.right - rect.left);
	str.Append(tmp);

	str.Append("\p, v=");

	tmp = (Int32) (rect.bottom - rect.top);
	str.Append(tmp);

	str.Append("\p)");
}
