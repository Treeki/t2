#include "CPicHandleView.h"

CPicHandleView *CPicHandleView::CreateCPicHandleViewStream(LStream *inStream) {
	return new CPicHandleView(inStream);
}

CPicHandleView::CPicHandleView(LStream *inStream)
	: LView(inStream)
{
	mHandle = NULL;
}

CPicHandleView::~CPicHandleView() {
	if (mHandle != NULL)
		::DisposeHandle((Handle) mHandle);
}

void CPicHandleView::SetPicHandle(PicHandle picture) {
	if (mHandle != NULL && mHandle != picture) {
		::DisposeHandle((Handle) mHandle);
	}

	mHandle = picture;

	if (picture != NULL) {
		Rect rect = (*picture)->picFrame;
		ResizeImageTo(rect.right - rect.left, rect.bottom - rect.top, false);
	}
}

void CPicHandleView::DrawSelf() {
	if (mHandle != NULL) {
		SDimension32 size;
		GetImageSize(size);

		Rect rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = size.width;
		rect.bottom = size.height;
		::DrawPicture(mHandle, &rect);
	}
}
