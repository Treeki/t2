#pragma once

#include <LControlPane.h>

class T2Slider : public LControlPane {
public:
	T2Slider(LStream *inStream);
	void InitSlider();
	~T2Slider();
	virtual void DoTrackAction(Int16 s, Int32 value);
};
