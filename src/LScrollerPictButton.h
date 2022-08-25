#pragma once

#include <LListener.h>
#include "LPictButton.h"

enum EScrollType {
	EScrollType_Vertical,
	EScrollType_Horizontal
};

class LScrollerPictButton : public LListener {
public:
	LScrollerPictButton();
	~LScrollerPictButton();

	void Setup(
		EScrollType scrollType,
		LView *view,
		LPictButton *btn1,
		ResIDT btn1a, ResIDT btn1b, ResIDT btn1c,
		EButtonState btn1state,
		LPictButton *btn2,
		ResIDT btn2a, ResIDT btn2b, ResIDT btn2c,
		EButtonState btn2state
	);
	void Setup(EScrollType scrollType, LView *view, LPictButton *btn1, LPictButton *btn2);
	void Reset();
	void Disable();
	void ListenToMessage(MessageT message, void *param);
	void ClickUpButton();
	void ClickDownButton();
	void RefreshButton();
	void RefreshUpButton();
	void RefreshDownButton();

protected:
	EScrollType mScrollType;
	LView *mView;
	LPictButton *mBtn1, *mBtn2;
};
