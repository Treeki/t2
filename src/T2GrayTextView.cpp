#include "T2GrayTextView.h"

#include <UDrawingState.h>

T2GrayTextView::T2GrayTextView(LStream *inStream)
	: LTextEdit(inStream)
{
}

void T2GrayTextView::DrawSelf() {
	Rect frameRect;
	CalcLocalFrameRect(frameRect);

	GrafPtr savePort = (*mTextEditH)->inPort;
	(*mTextEditH)->inPort = UQDGlobals::GetCurrentPort();
	::TEUpdate(&frameRect, mTextEditH);
	(*mTextEditH)->inPort = savePort;
}
