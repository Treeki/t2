#pragma once

#include <UAttachments.h>

class C3DBorderAttachment : public LBorderAttachment {
public:
	enum { class_ID = '3dba' };

	C3DBorderAttachment(LStream *inStream);

	//static C3DBorderAttachment *CreateC3DBorderAttachmentStream(LStream *inStream);
	static C3DBorderAttachment *CreateC3DBorderAttachmentStream(LStream *inStream) {
		return new C3DBorderAttachment(inStream);
	}

protected:
	virtual void ExecuteSelf(MessageT inMessage, void *ioParam);

	Boolean mInverted;
	Int16 mBorderWidth;
};
