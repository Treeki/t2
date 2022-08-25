#pragma once

#include <LView.h>

class T2UnitUpdtView : public LView {
public:
	T2UnitUpdtView(LStream *inStream);
	~T2UnitUpdtView();

	void Invalidate(Boolean flag);
	void InvalUnitRect(const Rect &rect, Boolean flag);
	void ClearUpdateRect();

protected:
	Rect mRect1;
	Rect mRect2;
	Rect mRect3;
};
