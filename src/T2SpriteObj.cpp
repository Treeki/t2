#include "T2GWorld.h"
#include "T2SpriteObj.h"
#include "UT2Coordinate.h"

T2SpriteObj::T2SpriteObj(Int16 index, T2Sprite::ELayer layer) {
	mIndex = index;
	mLayer = layer;
	mIsVisible = false;
	mPrevPosition.v = 0;
	mPrevPosition.h = 0;
	mCurrPosition.v = 0;
	mCurrPosition.h = 0;
	mRect.left = 0;
	mRect.top = 0;
	mRect.right = 0;
	mRect.bottom = 0;
}

T2SpriteObj::T2SpriteObj(Rect rect) {
	mIndex = 0;
	mLayer = T2Sprite::ELayer_0;
	mIsVisible = false;
	mRect = rect;
	mPrevPosition.v = 0;
	mPrevPosition.h = 0;
	mCurrPosition.v = 0;
	mCurrPosition.h = 0;
}

T2SpriteObj::~T2SpriteObj() {
}

Boolean T2SpriteObj::GetSpriteUpdateArea(Int32 var, Rect &rect) {
	if (::EqualPt(mPrevPosition, mCurrPosition))
		return false;

	Rect currRect = GetRect(var);
	::OffsetRect(&currRect, mCurrPosition.h, mCurrPosition.v);

	Rect prevRect = GetRect(var);
	::OffsetRect(&prevRect, mPrevPosition.h, mPrevPosition.v);

	::UnionRect(&currRect, &prevRect, &rect);
	mPrevPosition = mCurrPosition;
	return true;
}

Rect T2SpriteObj::GetRect(Int32) const {
	return mRect;
}

Boolean T2SpriteObj::Idle(T2TowerDoc *) {
	return false;
}

void T2SpriteObj::SetObject() {
}

void T2SpriteObj::Draw(T2GWorld *, Rect) const {
}

void T2SpriteObj::SetGWorld(T2GWorld *) {
}

void T2SpriteObj::ChangePattern(UInt32) {
}




T2ImageSpriteObj::T2ImageSpriteObj(Int16 index, T2Sprite::ELayer layer, T2ImageObj *imageObj, UInt32 var)
	: T2SpriteObj(index, layer)
{
	mPattern = var;
	mImageObj = imageObj;
}

T2ImageSpriteObj::~T2ImageSpriteObj() {
	delete mImageObj;
}

Rect T2ImageSpriteObj::GetRect(Int32 var) const {
	Rect r = mRect;
	if (mImageObj->mUlongParam & 4)
		UT2Coordinate::ZoomIn(r, var);
	return r;
}

void T2ImageSpriteObj::SetObject() {
	Int32 obj = mImageObj->FindObject(mPattern);
	mImageObj->GetObjectArea(obj, mRect);
}

void T2ImageSpriteObj::Draw(T2GWorld *gworld, Rect rect) const {
	Int32 obj = mImageObj->FindObject(mPattern);
	mImageObj->DrawObject(gworld, obj, rect);
}

void T2ImageSpriteObj::SetGWorld(T2GWorld *gworld) {
	if (mImageObj) {
		mImageObj->mGWorld = gworld;
		if (gworld) {
			gworld->GetBounds(mImageObj->mObj[0].rect);
			SetObject();
		}
	}
}

void T2ImageSpriteObj::ChangePattern(UInt32 pattern) {
	mPattern = pattern;
	SetObject();
}

