#pragma once

#include <PP_Types.h>
#include <Quickdraw.h>
#include <QDOffscreen.h>

class T2GWorld {
public:
	T2GWorld(ResIDT picID, Int16 depth, CTabHandle ctab, GDHandle gd, GWorldFlags flags);
	T2GWorld(PicHandle pic, Int16 depth, CTabHandle ctab, GDHandle gd, GWorldFlags flags);
	T2GWorld(const Rect &rect, Int16 depth, CTabHandle ctab, GDHandle gd, GWorldFlags flags);
	virtual ~T2GWorld();

	Boolean BeginDrawing();
	void EndDrawing();
	void CopyImage(GrafPtr graf, const Rect &src, const Rect &dst, Int16 mode, RgnHandle maskRgn);
	void CopyOffImage(T2GWorld *dstWorld, const Rect &src, const Rect &dst, Int16 mode = 0, RgnHandle maskRgn = 0);
	void CopyMaskOffImage(T2GWorld *maskWorld, T2GWorld *dstWorld, const Rect &src, const Rect &mask, const Rect &dst);
	void CopyOffImageLoop(T2GWorld *dstWorld, short factor, const Rect &src, const Rect &dst, Int16 mode, RgnHandle maskRgn);
	void ScrollBits(const Rect &rect, Int32 hOffset, Int32 vOffset);
	RgnHandle MakeRgn();
	void GetBounds(Rect &b) { b = mBounds; }
	void SetBounds(const Rect &newBounds);
	Boolean LockGWorld();
	void UnlockGWorld();
	void DrawFocusRect(const Rect &rect, Int16 what);

	// maybe wrong?
	GWorldPtr GetGWorld() const { return (GWorldPtr) mGWorld; }

protected:
	GrafPtr mGWorld;
	Rect mBounds;
	CGrafPtr mGrafPtr;
	GDHandle mGDHandle;
};
