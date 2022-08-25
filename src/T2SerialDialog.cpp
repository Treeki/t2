#include "T2SerialDialog.h"
#include <LPane.h>
#include <LString.h>
#include <UException.h>

T2SerialDialog::T2SerialDialog(LStream *inStream)
	: T2StdDialog(inStream)
{
	for (int i = 0; i < 16; i++)
		mSerial[i] = 0;
	for (int i = 0; i < 4; i++)
		mSField[i] = 0;
}

T2SerialDialog::~T2SerialDialog() {
}

void T2SerialDialog::FinishCreateSelf() {
	LDialogBox::FinishCreateSelf();

	for (int i = 0; i < 4; i++) {
		mSField[i] = FindPaneByID(11 + i);
		#line 62
		Assert_(mSField[i] != 0);
	}
}

void T2SerialDialog::GetSerial(char *p) {
	for (int i = 0; i < 16; i++)
		p[i] = mSerial[i];
	p[16] = 0;
}

void T2SerialDialog::MakeSerial() {
	int out = 0;
	for (int in = 0; in < 4; in++) {
		LStr255 s;
		mSField[in]->GetDescriptor(s);
		for (int c = 1; c < 5; c++) {
			mSerial[out] = s[c];
			out++;
		}
	}
}

void T2SerialDialog::DoMessageOK() {
	T2StdDialog::DoMessageOK();
	MakeSerial();
}
