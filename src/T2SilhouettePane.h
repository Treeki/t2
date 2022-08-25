#pragma once

#include <LPane.h>

class T2SilhouettePane : public LPane {
public:
	T2SilhouettePane(LStream *stream);
	~T2SilhouettePane();
	void SetSilhouette(RgnHandle region);
	void DrawSelf();

protected:
	RgnHandle mRegion;
	UInt16 m2C, m2E;
	Boolean mColorProvided;
	RGBColor mColor;
};
