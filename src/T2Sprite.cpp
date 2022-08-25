#include "T2GWorld.h"
#include "T2Sprite.h"
#include "T2SpriteObj.h"
#include "T2TowerDoc.h"
#include "T2TowerMainView.h"
#include "UT2Coordinate.h"

#include <LArrayIterator.h>
#include <UDrawingState.h>
#include <UException.h>
#include <URegions.h>

T2Sprite::T2Sprite(T2TowerDoc *doc)
	: LArray(sizeof(T2SpriteObj *))
	, mDocument(doc)
	, mArray()
{
	#line 44
	Assert_(mDocument != 0);
}

T2Sprite::~T2Sprite() {
	LArrayIterator iter(*this);
	T2SpriteObj *spriteObj;

	while (iter.Next(&spriteObj)) {
		delete spriteObj;
	}
}

Int32 T2Sprite::NewSprite(T2ImageObj *imageObj, UInt32 ulongParam, ELayer layer, Boolean flag) {
	Int32 index;
	for (index = 1; FindObj(index) != 0; index++) {}

	T2ImageSpriteObj *spriteObj = new T2ImageSpriteObj(index, layer, imageObj, ulongParam);
	spriteObj->SetObject();

	InsertItemsAt(1, index_Last, &spriteObj);
	if (flag)
		mArray.InsertItemsAt(1, index_Last, &spriteObj);

	return index;
}

Int32 T2Sprite::AddSpriteObj(T2SpriteObj *spriteObj, ELayer layer, Boolean flag) {
	Int16 index = 0;

	if (spriteObj) {
		for (index = 1; FindObj(index) != 0; index++) {}

		spriteObj->mIndex = index;
		spriteObj->mLayer = layer;

		InsertItemsAt(1, index_Last, &spriteObj);
		if (flag)
			mArray.InsertItemsAt(1, index_Last, &spriteObj);
	}

	return index;
}

void T2Sprite::DeleteSprite(Int32 index) {
	LArrayIterator iter(*this);
	T2SpriteObj *spriteObj;

	while (iter.Next(&spriteObj)) {
		if (spriteObj->mIndex == index) {
			AddUpdateRect(spriteObj, EDrawOrErase_1);

			mArray.Remove(&spriteObj);
			Remove(&spriteObj, sizeof(T2SpriteObj *));

			delete spriteObj;
			break;
		}
	}
}

T2SpriteObj *T2Sprite::FindObj(Int32 index) {
	LArrayIterator iter(*this);
	T2SpriteObj *spriteObj;

	while (iter.Next(&spriteObj)) {
		if (spriteObj->mIndex == index)
			return spriteObj;
	}

	return 0;
}

void T2Sprite::ShowSprite(Int32 index, Boolean flag) {
	T2SpriteObj *spriteObj = FindObj(index);
	spriteObj->mIsVisible = flag;
	AddUpdateRect(spriteObj, flag ? EDrawOrErase_0 : EDrawOrErase_1);
}

void T2Sprite::ChangePattern(Int32 index, UInt32 pattern) {
	T2SpriteObj *spriteObj = FindObj(index);
	if (spriteObj) {
		spriteObj->ChangePattern(pattern);
		if (spriteObj->mIsVisible)
			AddUpdateRect(spriteObj, EDrawOrErase_0);
	}
}

void T2Sprite::MoveSprite(Int32 index, Point pt) {
	T2SpriteObj *spriteObj = FindObj(index);
	if (spriteObj && !::EqualPt(spriteObj->mCurrPosition, pt)) {
		if (spriteObj->mIsVisible)
			AddUpdateRect(spriteObj, EDrawOrErase_1);
		spriteObj->mPrevPosition = spriteObj->mCurrPosition;
		spriteObj->mCurrPosition = pt;
		if (spriteObj->mIsVisible)
			AddUpdateRect(spriteObj, EDrawOrErase_0);
	}
}

void T2Sprite::DrawLayer(T2GWorld *gworld, ELayer layer, Int16 var) {
	LArrayIterator iter(*this);
	T2SpriteObj *spriteObj;

	while (iter.Next(&spriteObj)) {
		if (spriteObj->mLayer == layer && spriteObj->mIsVisible) {
			T2ImageSpriteObj *imageSpriteObj = (T2ImageSpriteObj *) spriteObj;
			Rect rect = imageSpriteObj->GetRect(var);
			::OffsetRect(&rect, imageSpriteObj->mCurrPosition.h, imageSpriteObj->mCurrPosition.v);
			UT2Coordinate::ZoomOut(rect, var);

			StRegion region;
			::GetClip(region);

			Rect tmp;
			if (::SectRect(&(*(RgnHandle(region)))->rgnBBox, &rect, &tmp)) {
				StClipRgnState state;
				state.ClipToIntersection(rect);
				spriteObj->Draw(gworld, rect);
			}
		}
	}
}

void T2Sprite::UpdateSprite(Int32 index) {
	T2SpriteObj *spriteObj = FindObj(index);
	if (spriteObj)
		AddUpdateRect(spriteObj, EDrawOrErase_0);
}

void T2Sprite::AddUpdateRect(T2SpriteObj *spriteObj, EDrawOrErase drawOrErase) {
	Rect rect = spriteObj->GetRect(GetDocument());

	::OffsetRect(&rect, spriteObj->mCurrPosition.h, spriteObj->mCurrPosition.v);
	UT2Coordinate::ZoomOut(rect, GetDocument()->GetZoomLevel());

	mDocument->GetMainView()->AddSpriteUpdateRect(rect, spriteObj->mLayer == ELayer_1, drawOrErase == EDrawOrErase_0);
}

void T2Sprite::SetSpriteGWorld(Int32 index, T2GWorld *gworld) {
	T2SpriteObj *spriteObj = FindObj(index);
	if (spriteObj) {
		spriteObj->SetGWorld(gworld);
		AddUpdateRect(spriteObj, EDrawOrErase_0);
	}
}

Point T2Sprite::GetSpritePosition(Int32 index, Rect &rect) {
	static const Point zero = { 0, 0 };
	Point result = zero;

	T2SpriteObj *spriteObj = FindObj(index);
	if (spriteObj) {
		(void)rect; // mess with register allocation

		rect = spriteObj->GetRect(GetDocument());
		::OffsetRect(&rect, spriteObj->mCurrPosition.h, spriteObj->mCurrPosition.v);
		result = spriteObj->mCurrPosition;
	}

	return result;
}

void T2Sprite::Idle() {
	LArrayIterator iter(mArray);
	T2SpriteObj *spriteObj = 0;

	while (iter.Next(&spriteObj)) {
		if (spriteObj->Idle(mDocument))
			AddUpdateRect(spriteObj, EDrawOrErase_0);
	}
}
