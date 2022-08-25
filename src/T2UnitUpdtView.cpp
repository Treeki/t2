#include "T2UnitUpdtView.h"

T2UnitUpdtView::T2UnitUpdtView(LStream *inStream)
	: LView(inStream)
{
	::SetRect(&mRect1, 0, 0, 0, 0);
	ClearUpdateRect();
}

T2UnitUpdtView::~T2UnitUpdtView() {
}

void T2UnitUpdtView::Invalidate(Boolean flag) {
	mRect3 = mRect1;
	if (flag)
		mRect2 = mRect1;
}

void T2UnitUpdtView::InvalUnitRect(const Rect &rect, Boolean flag) {
	Rect sect;
	::SectRect(&rect, &mRect1, &sect);
	if (!::EmptyRect(&sect)) {
		if (flag) {
			if (::EmptyRect(&mRect2))
				mRect2 = sect;
			else
				::UnionRect(&sect, &mRect2, &mRect2);
		}

		if (::EmptyRect(&mRect3))
			mRect3 = sect;
		else
			::UnionRect(&sect, &mRect3, &mRect3);
	}
}

void T2UnitUpdtView::ClearUpdateRect() {
	::SetRect(&mRect2, 0, 0, 0, 0);
	::SetRect(&mRect3, 0, 0, 0, 0);
}