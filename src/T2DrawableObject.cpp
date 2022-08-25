#include "T2DrawableObject.h"

T2DrawableObject::T2DrawableObject() {
}

T2DrawableObject::~T2DrawableObject() {
}

void T2DrawableObject::Draw(T2TowerDoc *doc, const Rect &rect) {
	DrawSelf(doc, rect);
}

void T2DrawableObject::DrawSelf(T2TowerDoc *doc, const Rect &rect) {
}
