#pragma once

#include <LTextEdit.h>

class T2GrayTextView : public LTextEdit {
public:
	T2GrayTextView(LStream *inStream);
	void DrawSelf();
};
