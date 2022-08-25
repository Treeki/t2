#include "T2GWorld.h"
#include "T2ImageObj.h"
#include "URect.h"

#include <UDrawingState.h>
#include <UException.h>

T2ImageObj::T2ImageObj(T2GWorld *gworld, Int32 objCount, ImgObjDef *objDefs, UInt32 ulongParam, Boolean ownsGWorld) {
	mGWorld = gworld;
	mObjCount = objCount;
	mTempGWorld3 = 0;
	mTempGWorld2 = 0;
	mTempGWorld1 = 0;

	URect::SetEmpty(mRect);
	m20 = -1;

	if (mObjCount > 0) {
		mObj = new ImgObjDef[mObjCount];
		for (Int32 i = 0; i < mObjCount; i++) {
			mObj[i] = objDefs[i];
		}
	}

	mUlongParam = ulongParam;
	mOwnsGWorld = ownsGWorld;
}

T2ImageObj::~T2ImageObj() {
	if (mGWorld && mOwnsGWorld)
		delete mGWorld;
	if (mObj)
		delete[] mObj;
	if (mTempGWorld3)
		delete mTempGWorld3;
	if (mTempGWorld2)
		delete mTempGWorld2;
	if (mTempGWorld1)
		delete mTempGWorld1;
}

Int32 T2ImageObj::FindObject(UInt32 id) {
	if (!mObjCount)
		return -1;

	for (Int32 i = 0; i < mObjCount; i++) {
		if (id == mObj[i].id)
			return i;
	}

	return -1;
}

Boolean T2ImageObj::GetObjectArea(Int32 index, Rect &rect) const {
	(void)this; // trick the compiler into ranking 'this' above 'rect'

	if (!this->mObjCount)
		return false;

	if (index >= 0 && index < mObjCount) {
		rect = mObj[index].rect;
		if (!(mUlongParam & 2))
			::OffsetRect(&rect, -rect.left, -rect.top);
		return true;
	} else {
		return false;
	}
}

void T2ImageObj::DrawObject(T2GWorld *destWorld, int index, const Rect &rect) {
	if (index < 0 || index >= mObjCount)
		return;

	Rect srcRect = mObj[index].rect;
	Rect dstRect = rect;
	#line 155
	ThrowIfNot_(mGWorld->LockGWorld());

	if (mUlongParam & 1) {
		SetUpForHalftone();
		#line 158
		ThrowIfNot_(mTempGWorld2->LockGWorld());
		#line 159
		ThrowIfNot_(mTempGWorld1->LockGWorld());

		Rect interimRect;
		::SetRect(&interimRect, 0, 0, URect::Width(dstRect), URect::Height(dstRect));
		if (index != m20 || !::EqualRect(&interimRect, &mRect)) {
			mGWorld->CopyOffImage(mTempGWorld2, srcRect, interimRect, 0, 0);
			mTempGWorld2->CopyMaskOffImage(mTempGWorld3, mTempGWorld1, interimRect, interimRect, interimRect);
			m20 = index;
			mRect = interimRect;
		}
		mTempGWorld1->CopyOffImage(destWorld, interimRect, dstRect, 0x24, 0);
		mTempGWorld2->UnlockGWorld();
		mTempGWorld1->UnlockGWorld();
	} else {
		mGWorld->CopyOffImage(destWorld, srcRect, dstRect, 0x24, 0);
	}

	mGWorld->UnlockGWorld();
}

void T2ImageObj::SetUpForHalftone() {
	Point pt;
	::SetPt(&pt, 0, 0);

	if (mObjCount == 0)
		return;
	if (mTempGWorld1 != 0)
		return;

	for (Int32 i = 0; i < mObjCount; i++) {
		if (mUlongParam & 1) {
			pt.v = (pt.v > URect::Height(mObj[i].rect)) ? pt.v : URect::Height(mObj[i].rect);
			pt.h = (pt.h > URect::Width(mObj[i].rect)) ? pt.h : URect::Width(mObj[i].rect);
		}
	}

	if (pt.v > 0 && pt.h > 0) {
		PixMapHandle pmh = ::GetGWorldPixMap(mGWorld->GetGWorld());
		if (pmh) {
			CTabHandle ctab = (*pmh)->pmTable;
			Rect rect;
			::SetRect(&rect, 0, 0, pt.h, pt.v);

			mTempGWorld3 = new T2GWorld(rect, 1, 0, 0, 0);
			#line 208
			ThrowIfNil_(mTempGWorld3);

			mTempGWorld2 = new T2GWorld(rect, 8, ctab, 0, 0);
			#line 210
			ThrowIfNil_(mTempGWorld2);

			mTempGWorld1 = new T2GWorld(rect, 8, ctab, 0, 0);
			#line 212
			ThrowIfNil_(mTempGWorld1);

			if (mTempGWorld3->BeginDrawing()) {
				::FillRect(&rect, &UQDGlobals::GetQDGlobals()->gray);
				mTempGWorld3->EndDrawing();
			}
		}
	}
}
