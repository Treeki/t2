#pragma once

#include <Types.h>
#include <PP_Types.h>

struct BkgndInfo {
	int vRange, hRange, dim3;
	UInt32 *arrays[1];
};

class UT2BkgndInfo {
public:
	static BkgndInfo *SetupBkgndInfo(UInt32, UInt32, UInt32);
	static void DisposeBkgndInfo(BkgndInfo *&ptrRef);
	static UInt32 GetBkgndInfo(BkgndInfo *inBkgndInfoPtr, Int32 inV, Int32 inH);
	static void UnitToBkgndRect(const Rect &inRect, Rect &outRect);
	static void BkgndToUnitRect(const Rect &inRect, Rect &outRect);
	static void GetOffBkgndRect(Int16 offset, Rect &rect);
	static void ReplaceID(const BkgndInfo *info, UInt32 a, Int32 b);
};
