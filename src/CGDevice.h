#pragma once

#include <Quickdraw.h>

class CGDevice {
public:
	CGDevice(GDHandle device);
	virtual ~CGDevice();

	int GetDepth();
	Boolean HasDepth(short depth, short flags);
	void SetDepth(short depth, Boolean flag);
	Boolean IsColor();
	void Restore();
	void Save();

	GDHandle mDevice;
	Byte mIsDepthSet;
	short mDepth;
	Byte mFlags;
};
