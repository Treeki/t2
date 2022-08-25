#pragma once

#include <UAttachments.h>

class CScrollerBorderAttachment : public LBorderAttachment {
public:
	enum { class_ID = 'scba' };

	CScrollerBorderAttachment(LStream *inStream);

	static CScrollerBorderAttachment *CreateCScrollerBorderAttachmentStream(LStream *inStream) {
		return new CScrollerBorderAttachment(inStream);
	}

protected:
	virtual void ExecuteSelf(MessageT inMessage, void *ioParam);

	Boolean m30, m31;
};
