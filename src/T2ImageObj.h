#pragma once

#include <PP_Types.h>

class T2GWorld;

struct ImgObjDef {
	UInt32 id;
	Rect rect;
};

class T2ImageObj {
public:
	UInt32 mUlongParam;
	T2GWorld *mGWorld;
	Int32 mObjCount;
	ImgObjDef *mObj;
	T2GWorld *mTempGWorld3;
	Rect mRect;
	T2GWorld *mTempGWorld1;
	Int16 m20;
	T2GWorld *mTempGWorld2;
	Boolean mOwnsGWorld;

	T2ImageObj(T2GWorld *gworld, Int32 objCount, ImgObjDef *objDefs, UInt32 ulongParam, Boolean ownsGWorld);
	virtual ~T2ImageObj();
	Int32 FindObject(UInt32 id);
	Boolean GetObjectArea(Int32 index, Rect &rect) const;
	void DrawObject(T2GWorld *destWorld, int index, const Rect &rect);
	void SetUpForHalftone();
};
