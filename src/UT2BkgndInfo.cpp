#include "UT2BkgndInfo.h"
#include <MacMemory.h>
#include <UDebugging.h>

BkgndInfo *UT2BkgndInfo::SetupBkgndInfo(UInt32 a, UInt32 b, UInt32 c) {
	BkgndInfo *info = nil;
	int vRange = a >> 1;
	int hRange = b >> 3;
	int lastRange = c >> 1;

	if (vRange > 0 && hRange > 0) {
		info = (BkgndInfo *) ::NewPtrClear(sizeof(BkgndInfo) + sizeof(void *) * (vRange - 1));
		info->vRange = vRange;
		info->hRange = hRange;
		info->dim3 = lastRange;

		for (int i = 0; i < vRange && info; i++) {
			info->arrays[i] = (UInt32 *) ::NewPtrClear(sizeof(UInt32) * hRange);
			if (!info->arrays[i])
				DisposeBkgndInfo(info);
		}
	}

	return info;
}

void UT2BkgndInfo::DisposeBkgndInfo(BkgndInfo *&ptrRef) {
	if (ptrRef) {
		for (int i = 0; i < ptrRef->vRange; i++) {
			if (ptrRef->arrays[i])
				::DisposePtr((Ptr) ptrRef->arrays[i]);
		}

		::DisposePtr((Ptr) ptrRef);
		ptrRef = nil;
	}
}

UInt32 UT2BkgndInfo::GetBkgndInfo(BkgndInfo *inBkgndInfoPtr, Int32 inV, Int32 inH) {
	#line 86
	Assert_(inBkgndInfoPtr != 0);
	Assert_((inV >= 0) && (inV < inBkgndInfoPtr->vRange));
	Assert_((inH >= 0) && (inH < inBkgndInfoPtr->hRange));

	if (!inBkgndInfoPtr)
		return 0;
	if (inV < 0 || inV >= inBkgndInfoPtr->vRange)
		return 0;
	if (inH < 0 || inH >= inBkgndInfoPtr->hRange)
		return 0;

	UInt32 value = inBkgndInfoPtr->arrays[inV][inH];
	value &= 0xFFFF;
	UInt32 value_ = value;
	return value_;
}

void UT2BkgndInfo::UnitToBkgndRect(const Rect &inRect, Rect &outRect) {
	outRect.top = inRect.top / 2;
	outRect.left = inRect.left / 8;
	outRect.bottom = inRect.bottom / 2;
	outRect.right = inRect.right / 8;

	if ((inRect.bottom % 2) != 0)
		outRect.bottom++;
	if ((inRect.right % 8) != 0)
		outRect.right++;
}

void UT2BkgndInfo::BkgndToUnitRect(const Rect &inRect, Rect &outRect) {
	outRect.top = inRect.top << 1;
	outRect.left = inRect.left << 3;
	outRect.bottom = inRect.bottom << 1;
	outRect.right = inRect.right << 3;
}

void UT2BkgndInfo::GetOffBkgndRect(Int16 offset, Rect &rect) {
	::SetRect(&rect, 0, 0, 8, 2);
	::OffsetRect(&rect, 0, offset * 2);
}

void UT2BkgndInfo::ReplaceID(const BkgndInfo *info, UInt32 a, Int32 b) {
	for (UInt32 v = 0; v < info->vRange; v++) {
		for (UInt32 h = 0; h < info->hRange; h++) {
			UInt32 *p = &info->arrays[v][h];
			if ((*p & 0xFFFF) >= a)
				*p += b;
		}
	}
}
