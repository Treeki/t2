#include "CTransparentPicture.h"
#include <UDrawingState.h>
#include <UDrawingUtils.h>
#include <UGWorld.h>

CTransparentPicture *CTransparentPicture::CreateCTransparentPictureStream(LStream *inStream) {
	return new CTransparentPicture(inStream);
}

CTransparentPicture::CTransparentPicture(LStream *inStream)
	: LPicture(inStream)
{
}

void CTransparentPicture::DrawSelf() {
	PicHandle pic = ::GetPicture(mPICTid);
	if (pic) {
		SDimension32 imageSize;
		GetImageSize(imageSize);

		Rect srcRect = (*pic)->picFrame;
		Rect dstRect;
		dstRect.left = 0;
		dstRect.top = 0;
		dstRect.right = imageSize.width;
		dstRect.bottom = imageSize.height;

		LGWorld *world = new LGWorld(srcRect);
		if (world && world->BeginDrawing()) {
			StColorPenState state;
			::DrawPicture(pic, &srcRect);
			world->EndDrawing();

			StColorPenState::Normalize();

			world->CopyImage(UQDGlobals::GetCurrentPort(), dstRect, transparent);
		}
		delete world;
	}
}
