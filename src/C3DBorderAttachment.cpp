#include "C3DBorderAttachment.h"
#include <LStream.h>
#include <UDrawingState.h>

C3DBorderAttachment::C3DBorderAttachment(LStream *inStream)
	: LBorderAttachment(inStream) {

	inStream->ReadData(&mInverted, sizeof mInverted);
	inStream->ReadData(&mBorderWidth, sizeof mBorderWidth);
}

/*C3DBorderAttachment *C3DBorderAttachment::CreateC3DBorderAttachmentStream(LStream *inStream) {
	return new C3DBorderAttachment(inStream);
}*/

void C3DBorderAttachment::ExecuteSelf(MessageT inMessage, void *ioParam) {
	StColorPenState state;
	Rect *rect = (Rect *) ioParam;

	::SetPenState(&mPenState);

	RGBColor fore = {0xFFFF, 0xFFFF, 0xFFFF};
	::RGBForeColor(&fore);
	::InsetRect(rect, 1, 1);
	::PaintRect(rect);
	::InsetRect(rect, -1, -1);

	for (short i = -mBorderWidth; i < 0; i++) {
		if (mInverted)
			::RGBForeColor(&mForeColor);
		else
			::RGBForeColor(&mBackColor);

		::MoveTo(rect->right + i - 1, rect->top - i);
		::Line(-((rect->right - rect->left) + i + i - 1), 0);
		::Line(0, (rect->bottom - rect->top) + i + i - 1);

		if (mInverted)
			::RGBForeColor(&mBackColor);
		else
			::RGBForeColor(&mForeColor);

		::MoveTo(rect->left - i, rect->bottom + i - 1);
		::Line((rect->right - rect->left) + i + i - 1, 0);
		::Line(0, -((rect->bottom - rect->top) + i + i - 1));
	}
}
