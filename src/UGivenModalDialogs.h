#pragma once

#include <LCommander.h>
#include <LEventDispatcher.h>
#include <LListener.h>
#include <LWindow.h>

class StGivenDialogHandler : public LEventDispatcher, public LCommander, public LListener {
public:
	StGivenDialogHandler(LWindow *dialog, ResIDT resID);
	~StGivenDialogHandler();

	LWindow *GetDialog() { return mDialog; }

	virtual MessageT DoDialog();
	virtual Boolean AllowSubRemoval(LCommander *inSub);
	virtual void FindCommandStatus(CommandT inCommand, Boolean &outEnabled, Boolean &outUsesMark, Char16 &outMark, Str255 outName);
	virtual void ListenToMessage(MessageT inMessage, void *ioParam);

protected:
	LWindow *mDialog;
	MessageT mMessage;
	Int32 mSleepTime;
};

class UGivenModalDialogs {
public:
	static Boolean ProcessDialog(LWindow *dialog, short param);
};
