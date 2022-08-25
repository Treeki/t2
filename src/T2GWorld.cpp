#include "StGWorldLocker.h"
#include "T2GWorld.h"
#include "URect.h"

#include <QDOffscreen.h>
#include <Resources.h>
#include <UDrawingState.h>
#include <UException.h>

T2GWorld::T2GWorld(ResIDT picID, Int16 depth, CTabHandle ctab, GDHandle gd, GWorldFlags flags) {
	::GetGWorld(&mGrafPtr, &mGDHandle);

	PicHandle pic = (PicHandle) ::GetResource('PICT', picID);
	#line 30
	ThrowIfNil_(pic);

	mBounds = (*pic)->picFrame;
	mGWorld = 0;

	Rect bounds = mBounds;
	if (!depth) {
		::LocalToGlobal((PointPtr) &bounds.top);
		::LocalToGlobal((PointPtr) &bounds.bottom);
	}

	OSErr err = ::NewGWorld((GWorldPtr *) &mGWorld, depth, &bounds, ctab, gd, flags);
	#line 47
	ThrowIfOSErr_(err);
	ThrowIfNil_(mGWorld);

	::SetGWorld((GWorldPtr) mGWorld, 0);
	::SetOrigin(mBounds.left, mBounds.top);
	::LockPixels(::GetGWorldPixMap((GWorldPtr) mGWorld));
	::DrawPicture(pic, &mBounds);
	::UnlockPixels(::GetGWorldPixMap((GWorldPtr) mGWorld));
	::SetGWorld(mGrafPtr, mGDHandle);
	::ReleaseResource((Handle) pic);
}

T2GWorld::T2GWorld(PicHandle pic, Int16 depth, CTabHandle ctab, GDHandle gd, GWorldFlags flags) {
	::GetGWorld(&mGrafPtr, &mGDHandle);

	mBounds = (*pic)->picFrame;
	mGWorld = 0;

	Rect bounds = mBounds;
	if (!depth) {
		::LocalToGlobal((PointPtr) &bounds.top);
		::LocalToGlobal((PointPtr) &bounds.bottom);
	}

	OSErr err = ::NewGWorld((GWorldPtr *) &mGWorld, depth, &bounds, ctab, gd, flags);
	#line 92
	ThrowIfOSErr_(err);
	ThrowIfNil_(mGWorld);

	::SetGWorld((GWorldPtr) mGWorld, 0);
	::SetOrigin(mBounds.left, mBounds.top);
	::LockPixels(::GetGWorldPixMap((GWorldPtr) mGWorld));
	::DrawPicture(pic, &mBounds);
	::UnlockPixels(::GetGWorldPixMap((GWorldPtr) mGWorld));
	::SetGWorld(mGrafPtr, mGDHandle);
}

T2GWorld::T2GWorld(const Rect &rect, Int16 depth, CTabHandle ctab, GDHandle gd, GWorldFlags flags) {
	::GetGWorld(&mGrafPtr, &mGDHandle);

	mBounds = rect;
	mGWorld = 0;

	Rect bounds = rect;
	if (!depth) {
		::LocalToGlobal((PointPtr) &bounds.top);
		::LocalToGlobal((PointPtr) &bounds.bottom);
	}

	OSErr err = ::NewGWorld((GWorldPtr *) &mGWorld, depth, &bounds, ctab, gd, flags);
	#line 136
	ThrowIfOSErr_(err);
	ThrowIfNil_(mGWorld);

	::SetGWorld((GWorldPtr) mGWorld, 0);
	::SetOrigin(mBounds.left, mBounds.top);
	::LockPixels(::GetGWorldPixMap((GWorldPtr) mGWorld));
	::EraseRect(&mBounds);
	::UnlockPixels(::GetGWorldPixMap((GWorldPtr) mGWorld));
	::SetGWorld(mGrafPtr, mGDHandle);
}

T2GWorld::~T2GWorld() {
	if (mGWorld)
		::DisposeGWorld((GWorldPtr) mGWorld);
}

Boolean T2GWorld::BeginDrawing() {
	::GetGWorld(&mGrafPtr, &mGDHandle);
	::SetGWorld((GWorldPtr) mGWorld, 0);
	return ::LockPixels(::GetGWorldPixMap((GWorldPtr) mGWorld));
}

void T2GWorld::EndDrawing() {
	::UnlockPixels(::GetGWorldPixMap((GWorldPtr) mGWorld));
	::SetGWorld(mGrafPtr, mGDHandle);
}

void T2GWorld::CopyImage(GrafPtr graf, const Rect &src, const Rect &dst, Int16 mode, RgnHandle maskRgn) {
	::CopyBits(&mGWorld->portBits, &graf->portBits, &src, &dst, mode, maskRgn);
}

void T2GWorld::CopyOffImage(T2GWorld *dstWorld, const Rect &src, const Rect &dst, Int16 mode, RgnHandle maskRgn) {
	StGWorldLocker locker(this);
	::CopyBits(&mGWorld->portBits, &dstWorld->mGWorld->portBits, &src, &dst, mode, maskRgn);
}

void T2GWorld::CopyMaskOffImage(T2GWorld *maskWorld, T2GWorld *dstWorld, const Rect &src, const Rect &mask, const Rect &dst) {
	StGWorldLocker locker(this);
	::CopyMask(&mGWorld->portBits, &maskWorld->mGWorld->portBits, &dstWorld->mGWorld->portBits, &src, &mask, &dst);
}

void T2GWorld::CopyOffImageLoop(T2GWorld *dstWorld, short factor, const Rect &src, const Rect &dst, Int16 mode, RgnHandle maskRgn) {
	StGWorldLocker locker(this);

	short srcWidth = src.right - src.left;
	short dstWidth = dst.right - dst.left;

	Rect workSrc = src;
	Rect workDst = dst;

	if (((workDst.left << factor) % srcWidth) != 0) {
		workSrc.left = (workDst.left << factor) % srcWidth;
		if ((dstWidth << factor) < (srcWidth - workSrc.left))
			workSrc.right = workSrc.left + (dstWidth << factor);
		else
			workDst.right = workDst.left + ((srcWidth - workSrc.left) >> factor);
		workDst.right = workDst.left + ((workSrc.right - workSrc.left) >> factor);

		CopyOffImage(dstWorld, workSrc, workDst, mode, maskRgn);
		dstWidth -= (workDst.right - workDst.left);
		workDst.left = workDst.right;
	}

	workSrc = src;

	while ((dstWidth << factor) >= srcWidth) {
		workDst.right = workDst.left + (srcWidth >> factor);
		CopyOffImage(dstWorld, workSrc, workDst, mode, maskRgn);
		dstWidth -= (srcWidth >> factor);
		workDst.left = workDst.right;
	}

	if (dstWidth > 0) {
		workSrc.right = workSrc.left + (dstWidth << factor);
		workDst.right = workDst.left + dstWidth;
		CopyOffImage(dstWorld, workSrc, workDst, mode, maskRgn);
	}
}

void T2GWorld::ScrollBits(const Rect &rect, Int32 hOffset, Int32 vOffset) {
	Rect src = rect;

	if (vOffset != 0) {
		if (vOffset > 0)
			src.top += vOffset;
		else
			src.bottom += vOffset;
	}

	if (hOffset != 0) {
		if (hOffset > 0)
			src.left += hOffset;
		else
			src.right += hOffset;
	}

	Rect dst = src;
	::OffsetRect(&dst, -hOffset, -vOffset);

	BeginDrawing();
	::CopyBits(&mGWorld->portBits, &mGWorld->portBits, &src, &dst, 0, 0);
	EndDrawing();
}

RgnHandle T2GWorld::MakeRgn() {
	StGWorldLocker locker(this);

	RgnHandle rgn = ::NewRgn();
	OSErr err = ::BitMapToRegion(rgn, &mGWorld->portBits);
	if (err != noErr) {
		::DisposeRgn(rgn);
		rgn = 0;
	}
	return rgn;
}

void T2GWorld::SetBounds(const Rect &newBounds) {
	mBounds = newBounds;

	::GetGWorld(&mGrafPtr, &mGDHandle);
	::SetGWorld((GWorldPtr) mGWorld, 0);
	::SetOrigin(mBounds.left, mBounds.top);
	::SetGWorld(mGrafPtr, mGDHandle);
}

Boolean T2GWorld::LockGWorld() {
	return ::LockPixels(::GetGWorldPixMap((GWorldPtr) mGWorld));
}

void T2GWorld::UnlockGWorld() {
	::UnlockPixels(::GetGWorldPixMap((GWorldPtr) mGWorld));
}

void T2GWorld::DrawFocusRect(const Rect &rect, Int16 what) {
	StColorPenState penState;
	StColorPenState::Normalize();

	static const unsigned char pattern[16] = {
		0x0F, 0x87, 0xC3, 0xE1, 0xF0, 0x78, 0x3C, 0x1E,
		0x0F, 0x87, 0xC3, 0xE1, 0xF0, 0x78, 0x3C, 0x1E
	};

	::PenSize(2, 2);
	::ForeColor(blackColor);
	::BackColor(whiteColor);
	::PenPat((const Pattern *) &pattern[what % 8]);
	::FrameRect(&rect);
}
