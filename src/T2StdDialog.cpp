#include "T2StdDialog.h"
#include "T2TowerDoc.h"
#include "T2TowerMainView.h"
#include <PP_Messages.h>

T2StdDialog::T2StdDialog() {
	m138 = 1;
	m139 = 0;
}

T2StdDialog::T2StdDialog(LStream *inStream)
	: LDialogBox(inStream)
{
	m138 = 1;
	m139 = 0;
}

T2StdDialog::~T2StdDialog() {
}

void T2StdDialog::Show() {
	if (!IsVisible() && GetDocument() && m138) {
		m139 = GetDocument()->Pause() && !GetDocument()->GetMainView()->IsPauseByArrow();
		GetDocument()->GetMainView()->HideArrow();
	}
	LWindow::Show();
}

void T2StdDialog::FindCommandStatus(CommandT inCommand, Boolean &outEnabled, Boolean &outUsesMark, Char16 &outMark, Str255 outName) {
	switch (inCommand) {
		case cmd_About:
		case cmd_Undo:
		case cmd_Cut:
		case cmd_Copy:
		case cmd_Paste:
		case cmd_Clear:
		case cmd_SelectAll:
			LWindow::FindCommandStatus(inCommand, outEnabled, outUsesMark, outMark, outName);
			break;
		default:
			outEnabled = false;
			break;
	}
}

void T2StdDialog::ListenToMessage(MessageT inMessage, void *ioParam) {
	switch (inMessage) {
		case msg_OK:
			DoMessageOK();
			break;
		case msg_Cancel:
			DoMessageCancel();
			break;
		default:
			LDialogBox::ListenToMessage(inMessage, ioParam);
			break;
	}
}

void T2StdDialog::DoMessageOK() {
	if (GetDocument() && m138 && !m139) {
		GetDocument()->Start();
	}

	DoClose();
}

void T2StdDialog::DoMessageCancel() {
	if (GetDocument() && m138 && !m139) {
		GetDocument()->Start();
	}

	DoClose();
}

void T2StdDialog::SetPauseState(Boolean state) {
	if (!IsVisible())
		m138 = state;
}

T2TowerDoc *T2StdDialog::GetDocument() const {
	return dynamic_cast<T2TowerDoc *>(mSuperCommander);
}
