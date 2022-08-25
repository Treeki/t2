#pragma once

#include <LArray.h>

class T2GWorld;
class T2ImageObj;
class T2SpriteObj;
class T2TowerDoc;

class T2Sprite : public LArray {
public:
	enum ELayer {
		ELayer_0,
		ELayer_1,
		ELayer_2,
		ELayer_3,
		ELayer_4,
		ELayer_5,
		ELayer_6
	};

	enum EDrawOrErase {
		EDrawOrErase_0,
		EDrawOrErase_1
	};

	T2Sprite(T2TowerDoc *doc);
	~T2Sprite();
	Int32 NewSprite(T2ImageObj *imageObj, UInt32 ulongParam, ELayer layer, Boolean flag);
	Int32 AddSpriteObj(T2SpriteObj *spriteObj, ELayer layer, Boolean flag);
	void DeleteSprite(Int32 index);
	T2SpriteObj *FindObj(Int32 index);
	void ShowSprite(Int32 index, Boolean flag);
	void ChangePattern(Int32 index, UInt32 pattern);
	void MoveSprite(Int32 index, Point pt);
	void DrawLayer(T2GWorld *gworld, ELayer layer, Int16 var);
	void UpdateSprite(Int32 index);
	void AddUpdateRect(T2SpriteObj *spriteObj, EDrawOrErase drawOrErase);
	void SetSpriteGWorld(Int32 index, T2GWorld *gworld);
	Point GetSpritePosition(Int32 index, Rect &rect);
	void Idle();

	T2TowerDoc *GetDocument() const { return mDocument; }

	T2TowerDoc *mDocument;
	LArray mArray;
};
