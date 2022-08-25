#pragma once

#include <LBroadcaster.h>
#include <LButton.h>
#include <LCaption.h>
#include <LListener.h>
#include <LString.h>
#include <LView.h>

class CSpinButtons : public LView, public LListener, public LBroadcaster {
public:
	enum { class_ID = 'spbt' };

	CSpinButtons(LStream *inStream);
	~CSpinButtons();

	MessageT GetValueMessage() const;
	void SetValueMessage(MessageT valueMessage);
	void SetMinValue(Int32 minValue);
	void SetMaxValue(Int32 maxValue);
	void SetValue(Int32 value);
	Int32 GetValue() const;
	void BroadcastValueMessage();

	static CSpinButtons *CreateCSpinButtonsStream(LStream *inStream);

protected:
	virtual void FinishCreateSelf();
	virtual void ListenToMessage(MessageT inMessage, void *ioParam);

	ResIDT mResourceID;
	LCaption *mCaption;
	LButton *mUp, *mDown;
	Int32 mValue, mMinValue, mMaxValue;
	LStr255 mString;
	MessageT mValueMessage;
};
