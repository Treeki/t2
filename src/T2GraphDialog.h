#pragma once

#include "T2StdDialog.h"

class LFile;

class T2GraphDialog : public T2StdDialog {
public:
	T2GraphDialog(LStream *inStream);
	~T2GraphDialog();
	void ListenToMessage(MessageT message, void *ioParam);
	void Setup(LFile *file, Int16 oldResFile);

protected:
	Int16 mOldResFile;
	LFile *mFile;
};
