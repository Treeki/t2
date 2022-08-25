#pragma once

#include "T2Object.h"

class T2DrawableObject : public T2Object {
public:
	T2DrawableObject();
	virtual ~T2DrawableObject();

	virtual void Draw(T2TowerDoc *doc, const Rect &rect);
	virtual void DrawSelf(T2TowerDoc *doc, const Rect &rect);
};
