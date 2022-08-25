#include "T2Dialog.h"
#include "T2Object.h"

#include <PP_Messages.h>

T2Dialog::T2Dialog(LStream *inStream)
	: LDialogBox(inStream)
{
	mT2Object = 0;
	m13C = 0;
}

T2Dialog::~T2Dialog() {
}

void T2Dialog::SetT2Object(T2Object *obj) {
	// TODO
	mT2Object = obj;
	// TODO
}

void T2Dialog::ListenToMessage(MessageT inMessage, void *ioParam) {
	switch (inMessage) {
		case msg_OK:
			if (mT2Object) {
				// TODO
			}
		case msg_Cancel:
			DoClose();
			break;
		default:
			LDialogBox::ListenToMessage(inMessage, ioParam);
	}
}



T2SubDialog::T2SubDialog(LStream *inStream)
	: T2Dialog(inStream)
{
}

T2SubDialog::~T2SubDialog() {
}

void T2SubDialog::SetT2Object(T2Object *obj) {
	mT2Object = obj;
	// TODO
}

void T2SubDialog::ListenToMessage(MessageT inMessage, void *ioParam) {
	// TODO
	T2Dialog::ListenToMessage(inMessage, ioParam);
}
