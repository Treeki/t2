#include "CGDevice.h"
#include <Palettes.h>

CGDevice::CGDevice(GDHandle device) {
	mDevice = device;
	Save();
	mIsDepthSet = 0;
}

CGDevice::~CGDevice() {
	Restore();
}

int CGDevice::GetDepth() {
	PixMapHandle pmap = (*mDevice)->gdPMap;
	if (pmap == NULL)
		return 0;
	else
		return (*pmap)->pixelSize;
}

Boolean CGDevice::HasDepth(short depth, short flags) {
	return ::HasDepth(mDevice, depth, 1, flags) != 0;
}

void CGDevice::SetDepth(short depth, Boolean isColor) {
	short flags = isColor ? 1 : 0;

	if ((mDepth != depth || mFlags != isColor) && HasDepth(depth, flags)) {
		::SetDepth(mDevice, depth, 1, flags);
		mIsDepthSet = true;
	}
}

Boolean CGDevice::IsColor() {
	short attr = ::TestDeviceAttribute(mDevice, gdDevType);
	return attr != 0;
}

void CGDevice::Restore() {
	if (mIsDepthSet) {
		SetDepth(mDepth, mFlags);
	}
}

void CGDevice::Save() {
	mDepth = GetDepth();
	mFlags = IsColor();
}
