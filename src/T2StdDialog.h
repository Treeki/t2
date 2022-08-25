#pragma once

#include <LDialogBox.h>

class T2TowerDoc;

class T2StdDialog : public LDialogBox {
public:
	T2StdDialog();
	T2StdDialog(LStream *inStream);
	~T2StdDialog();

	virtual void Show();
	virtual void FindCommandStatus(CommandT inCommand, Boolean &outEnabled, Boolean &outUsesMark, Char16 &outMark, Str255 outName);
	virtual void ListenToMessage(MessageT inMessage, void *ioParam);
	virtual void DoMessageOK();
	virtual void DoMessageCancel();

	void SetPauseState(Boolean state);
	T2TowerDoc *GetDocument() const;

	Boolean m138;
	Boolean m139;
};
