#pragma once

#include <LView.h>
#include <Memory.h>

class CPicHandleView : public LView {
public:
	enum { class_ID = 'phvw' };

	static CPicHandleView *CreateCPicHandleViewStream(LStream *inStream);

	CPicHandleView(LStream *inStream);
	~CPicHandleView();
	void SetPicHandle(PicHandle picture);
	void DrawSelf();

protected:
	PicHandle mHandle;
};
