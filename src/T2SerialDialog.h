#pragma once

#include "T2StdDialog.h"

class T2SerialDialog : public T2StdDialog {
public:
	T2SerialDialog(LStream *inStream);
	~T2SerialDialog();

	void FinishCreateSelf();
	void GetSerial(char *p);
	void MakeSerial();
	void DoMessageOK();

protected:
	LPane *mSField[4];
	char mSerial[16];
};
