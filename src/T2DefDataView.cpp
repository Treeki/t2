#include "T2DefDataView.h"

#include <LString.h>

T2DefDataView::T2DefDataView(LStream *inStream)
	: LView(inStream)
{
	m7C = 0;
}

T2DefDataView::~T2DefDataView() {
}

void T2DefDataView::DrawSelf() {
	LStr255 str("\pNULL");
	::MoveTo(10, 16);

	if (!m7C) {
		::DrawString("\pNull");
	} else {
		// stuff I don't know yet...

		SDimension32 size;
		GetImageSize(size);
		// size.height = ... + 16;
		ResizeImageTo(size.width, size.height, false);
	}
}
