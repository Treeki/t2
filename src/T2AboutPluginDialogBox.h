#pragma once

#include <LDialogBox.h>

class T2AboutPluginDialogBox : public LDialogBox {
public:
	enum { class_ID = 'Tapd' };

	T2AboutPluginDialogBox(LStream *inStream);
	~T2AboutPluginDialogBox();

	static T2AboutPluginDialogBox *CreateT2AboutPluginDialogBoxStream(LStream *inStream);

protected:
	UInt32 m138;

	virtual void FinishCreateSelf();
	virtual void ListenToMessage(MessageT inMessage, void *ioParam);
};
