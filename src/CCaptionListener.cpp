#include "CCaptionListener.h"
#include <LStream.h>

CCaptionListener::CCaptionListener(LStream *inStream)
	: LGACaption(inStream)
	, LListener()
{
	(*inStream) >> mMessage;
}

/*CCaptionListener *CCaptionListener::CreateCCaptionListenerStream(LStream *inStream) {
	return new CCaptionListener(inStream);
}*/

void CCaptionListener::ListenToMessage(MessageT inMessage, void *ioParam) {
	if (inMessage == mMessage) {
		LStr255 str;
		str = *((Int32 *) ioParam);
		SetDescriptor(str);
	}
}
