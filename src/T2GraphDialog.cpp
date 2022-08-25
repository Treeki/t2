#include "T2GraphDialog.h"
#include "T2TowerDoc.h"
#include "T2WorldPlugin.h"

#include <LFile.h>
#include <UException.h>

T2GraphDialog::T2GraphDialog(LStream *inStream)
	: T2StdDialog(inStream)
{
	mOldResFile = 0;
	mFile = 0;
}

T2GraphDialog::~T2GraphDialog() {
	if (mFile) {
		mFile->CloseResourceFork();
		::UseResFile(mOldResFile);
	}
}

void T2GraphDialog::ListenToMessage(MessageT message, void *ioParam) {
	T2TowerDoc *theDoc = GetDocument();
	#line 40
	Assert_(theDoc != 0);
	Assert_(theDoc->mWorldPlugin != 0);

	theDoc->mWorldPlugin->GraphListen(theDoc, this, message, ioParam);
	T2StdDialog::ListenToMessage(message, ioParam);
}

void T2GraphDialog::Setup(LFile *file, Int16 oldResFile) {
	mFile = file;
	mOldResFile = oldResFile;
}
