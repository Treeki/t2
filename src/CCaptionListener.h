#pragma once

#include <LGACaption.h>
#include <LListener.h>

class CCaptionListener : public LGACaption, public LListener {
public:
	CCaptionListener(LStream *inStream);

	virtual void ListenToMessage(MessageT inMessage, void *ioParam);

	static CCaptionListener *CreateCCaptionListenerStream(LStream *inStream) {
		return new CCaptionListener(inStream);
	}

protected:
	MessageT mMessage;
};
