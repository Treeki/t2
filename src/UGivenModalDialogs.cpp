#include "UGivenModalDialogs.h"
#include <LPeriodical.h>
#include <LUndoer.h>
#include <PP_Messages.h>
#include <UReanimator.h>

StGivenDialogHandler::StGivenDialogHandler(LWindow *dialog, ResIDT resID)
	: LCommander(dialog->GetSuperCommander())
{
	mDialog = dialog;
	#line 39
	SignalIf_(mDialog == nil);

	if (mDialog)
		UReanimator::LinkListenerToControls(this, mDialog, resID);

	try {
		mDialog->AddAttachment(new LUndoer);
	} catch (...) {

	}

	mMessage = 0;
	mSleepTime = 6;
}

StGivenDialogHandler::~StGivenDialogHandler() {

}

MessageT StGivenDialogHandler::DoDialog() {
	EventRecord record;

	if (IsOnDuty()) {
		::OSEventAvail(0, &record);
		AdjustCursor(record);
	}

	SetUpdateCommandStatus(false);
	mMessage = 0;
	Boolean hasEvent = ::WaitNextEvent(everyEvent, &record, mSleepTime, mMouseRgn);
	if (LEventDispatcher::ExecuteAttachments(810, &record)) {
		if (hasEvent) {
			DispatchEvent(record);
		} else {
			UseIdleTime(record);
		}
	}

	LPeriodical::DevoteTimeToRepeaters(record);

	if (IsOnDuty() && GetUpdateCommandStatus()) {
		UpdateMenus();
	}

	return mMessage;
}

Boolean StGivenDialogHandler::AllowSubRemoval(LCommander *inSub) {
	Boolean result = true;

	if (inSub == dynamic_cast<LCommander *>(mDialog)) {
		mDialog->Hide();
		result = false;
		mMessage = msg_Cancel;
	}

	return result;
}

void StGivenDialogHandler::FindCommandStatus(CommandT inCommand, Boolean &outEnabled, Boolean &outUsesMark, Char16 &outMark, Str255 outName) {
	outEnabled = false;
	if (inCommand == cmd_About)
		outEnabled = true;
}

void StGivenDialogHandler::ListenToMessage(MessageT inMessage, void *ioParam) {
	mMessage = inMessage;
}

Boolean UGivenModalDialogs::ProcessDialog(LWindow *dialog, short param) {
	StGivenDialogHandler handler(dialog, param);
	LWindow *theDialog = handler.GetDialog();

	theDialog->Show();

	Boolean result = false;
	for (;;) {
		MessageT msg = handler.DoDialog();
		if (msg == msg_Cancel) {
			break;
		}
		if (msg == msg_OK) {
			result = true;
			break;
		}
	}

	theDialog->Hide();
	return result;
}
