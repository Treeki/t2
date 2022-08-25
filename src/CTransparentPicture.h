#pragma once

#include <LPicture.h>

class CTransparentPicture : public LPicture {
public:
	enum { class_ID = 'trpc' };

	CTransparentPicture(LStream *inStream);

	static CTransparentPicture *CreateCTransparentPictureStream(LStream *inStream);

protected:
	virtual void DrawSelf();
};
