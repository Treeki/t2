#include "T2CityEditorPicture.h"
#include "T2GWorld.h"
#include "T2WorldPlugin.h"

#include <LFile.h>

T2CityEditorPicture::T2CityEditorPicture(LStream *inStream)
	: LPane(inStream)
{
	mGWorld = 0;
}

T2CityEditorPicture::~T2CityEditorPicture() {
	if (mGWorld)
		delete mGWorld;
}

void T2CityEditorPicture::SetPicture(T2WorldPlugin *plugin) {
	if (mGWorld)
		delete mGWorld;
	mGWorld = 0;

	LFile *file = plugin->mFile;
	file->OpenResourceFork(1);

	Handle pic = ::Get1Resource('PICT', plugin->mCityEditorPictureID);
	if (pic) {
		mGWorld = new T2GWorld((PicHandle) pic, 8, 0, 0, 0);
		::ReleaseResource(pic);
	}

	file->CloseResourceFork();

	Rect frameRect;
	CalcPortFrameRect(frameRect);
	InvalPortRect(&frameRect);
}

void T2CityEditorPicture::DrawSelf() {
	if (mGWorld) {
		Rect imgRect, frameRect;
		mGWorld->GetBounds(imgRect);
		CalcLocalFrameRect(frameRect);

		mGWorld->CopyImage(GetMacPort(), imgRect, frameRect, 0, 0);
	}
}
