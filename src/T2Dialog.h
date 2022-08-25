#pragma once

#include <LDialogBox.h>

class T2Object;

class T2Dialog : public LDialogBox {
public:
	T2Dialog(LStream *inStream);
	~T2Dialog();

	virtual int GetDialogType() { return 0; }
	virtual void SetT2Object(T2Object *obj);
	virtual void ListenToMessage(MessageT inMessage, void *ioParam);

protected:
	T2Object *mT2Object;
	int m13C;
};

class T2SubDialog : public T2Dialog {
public:
	T2SubDialog(LStream *inStream);
	~T2SubDialog();

	virtual void SetT2Object(T2Object *obj);
	virtual void ListenToMessage(MessageT inMessage, void *ioParam);
};
