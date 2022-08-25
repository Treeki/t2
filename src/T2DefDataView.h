#pragma once

#include <LView.h>

class T2DefDataView : public LView {
public:
	T2DefDataView(LStream *inStream);
	~T2DefDataView();

	void DrawSelf();

	int m7C;
};
