#include "CScrollerBorderAttachment.h"
#include <LStream.h>
#include <UDrawingState.h>

CScrollerBorderAttachment::CScrollerBorderAttachment(LStream *inStream)
	: LBorderAttachment(inStream) {

	inStream->ReadData(&m30, sizeof(m30));
	inStream->ReadData(&m31, sizeof(m31));
}

/*CScrollerBorderAttachment *CScrollerBorderAttachment::CreateCScrollerBorderAttachmentStream(LStream *inStream) {
	return new CScrollerBorderAttachment(inStream);
}*/

void CScrollerBorderAttachment::ExecuteSelf(MessageT inMessage, void *ioParam) {
	StColorPenState state;
	Rect *rect = (Rect *) ioParam;

	::SetPenState(&mPenState);
	::RGBForeColor(&mBackColor);

	if (m30 && m31) {
		::FrameRect(rect);
	} else {
		::MoveTo(rect->right - 2, rect->top);
		::LineTo(rect->left, rect->top);
		::LineTo(rect->left, rect->bottom - 2);

		if (!m30 && !m31) {
			::RGBForeColor(&mForeColor);
			::MoveTo(rect->right - 1, rect->top);
			::LineTo(rect->right - 1, rect->bottom - 1);
			::LineTo(rect->left, rect->bottom - 1);
		} else if (m30) {
			::MoveTo(rect->right - 1, rect->bottom - 18);
			::LineTo(rect->right - 1, rect->top);
			::RGBForeColor(&mForeColor);
			::MoveTo(rect->left, rect->bottom - 1);
			::LineTo(rect->right - 1, rect->bottom - 1);
			::LineTo(rect->right - 1, rect->bottom - 17);
		} else {
			::MoveTo(rect->right - 18, rect->bottom - 1);
			::LineTo(rect->left, rect->bottom - 1);
			::RGBForeColor(&mForeColor);
			::MoveTo(rect->right - 1, rect->top);
			::LineTo(rect->right - 1, rect->bottom - 1);
			::LineTo(rect->right - 17, rect->bottom - 1);
		}
	}
}
