#pragma once

#include "T2ImageObj.h"
#include "T2Sprite.h"
#include "T2TowerDoc.h"

class T2SpriteObj {
public:
	Int32 mIndex;
	T2Sprite::ELayer mLayer;
	Point mPrevPosition;
	Point mCurrPosition;
	Boolean mIsVisible;
	Rect mRect;

	T2SpriteObj(Int16 index, T2Sprite::ELayer layer);
	T2SpriteObj(Rect rect);
	virtual ~T2SpriteObj();
	Boolean GetSpriteUpdateArea(Int32 var, Rect &rect);
	virtual Rect GetRect(Int32 var) const;
	virtual Boolean Idle(T2TowerDoc *doc);
	virtual void ChangePattern(UInt32 pattern);
	virtual void SetObject();
	virtual void Draw(T2GWorld *gworld, Rect rect) const;
	virtual void SetGWorld(T2GWorld *gworld);

	Rect GetRect(T2TowerDoc *doc) const {
		Int32 zoom = doc->GetZoomLevel();
		return GetRect(zoom);
	}
};

class T2ImageSpriteObj : public T2SpriteObj {
public:
	T2ImageSpriteObj(Int16 index, T2Sprite::ELayer layer, T2ImageObj *imageObj, UInt32 var);
	~T2ImageSpriteObj();
	Boolean GetSpriteUpdateArea(Int32 var, Rect &rect);
	Rect GetRect(Int32 var) const;
	void SetObject();
	void Draw(T2GWorld *gworld, Rect rect) const;
	void SetGWorld(T2GWorld *gworld);
	void ChangePattern(UInt32 pattern);

	UInt32 mPattern;
	T2ImageObj *mImageObj;
};
