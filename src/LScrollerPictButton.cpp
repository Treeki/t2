#include "LScrollerPictButton.h"

LScrollerPictButton::LScrollerPictButton() {
	mView = 0;
	mBtn1 = 0;
	mBtn2 = 0;
}

LScrollerPictButton::~LScrollerPictButton() {
	if (mBtn1)
		mBtn1->RemoveListener(this);
	if (mBtn2)
		mBtn2->RemoveListener(this);
}

void LScrollerPictButton::Setup(
	EScrollType scrollType,
	LView *view,
	LPictButton *btn1,
	ResIDT btn1a, ResIDT btn1b, ResIDT btn1c,
	EButtonState btn1state,
	LPictButton *btn2,
	ResIDT btn2a, ResIDT btn2b, ResIDT btn2c,
	EButtonState btn2state
)
{
	btn1->Setup(btn1a, btn1b, btn1c, btn1state);
	btn2->Setup(btn2a, btn2b, btn2c, btn2state);
	Setup(scrollType, view, btn1, btn2);
}

void LScrollerPictButton::Setup(EScrollType scrollType, LView *view, LPictButton *btn1, LPictButton *btn2) {
	mScrollType = scrollType;
	mView = view;
	mBtn1 = btn1;
	mBtn2 = btn2;
	if (mBtn1)
		mBtn1->AddListener(this);
	if (mBtn2)
		mBtn2->AddListener(this);
}

void LScrollerPictButton::Reset() {
	if (mView) {
		SPoint32 frameLoc, imageLoc;
		mView->GetFrameLocation(frameLoc);
		mView->GetImageLocation(imageLoc);

		switch (mScrollType) {
			case EScrollType_Vertical:
				if (imageLoc.v < frameLoc.v)
					mView->ScrollPinnedImageBy(0, imageLoc.v - frameLoc.v, true);
				break;
			case EScrollType_Horizontal:
				if (imageLoc.h < frameLoc.h)
					mView->ScrollPinnedImageBy(imageLoc.h - frameLoc.h, 0, true);
				break;
		}

		RefreshButton();
	}
}

void LScrollerPictButton::Disable() {
	if (mBtn1)
		mBtn1->ChangeStatus(EButtonState_Disabled);
	if (mBtn2)
		mBtn2->ChangeStatus(EButtonState_Disabled);
}

void LScrollerPictButton::ListenToMessage(MessageT message, void *param) {
	if (message == 812) {
		if (param == mBtn1)
			ClickUpButton();
		else if (param == mBtn2)
			ClickDownButton();
	}
}

void LScrollerPictButton::ClickUpButton() {
	if (mBtn1) {
		mBtn1->ChangeStatus(EButtonState_Pushed);
		if (mView) {
			SPoint32 unit;
			mView->GetScrollUnit(unit);

			switch (mScrollType) {
				case EScrollType_Vertical:
					mView->ScrollPinnedImageBy(0, -unit.v, true);
					break;
				case EScrollType_Horizontal:
					mView->ScrollPinnedImageBy(-unit.h, 0, true);
					break;
			}
		}
		RefreshButton();
	}
}

void LScrollerPictButton::ClickDownButton() {
	if (mBtn2) {
		mBtn2->ChangeStatus(EButtonState_Pushed);
		if (mView) {
			SPoint32 unit;
			mView->GetScrollUnit(unit);

			switch (mScrollType) {
				case EScrollType_Vertical:
					mView->ScrollPinnedImageBy(0, unit.v, true);
					break;
				case EScrollType_Horizontal:
					mView->ScrollPinnedImageBy(unit.h, 0, true);
					break;
			}
		}
		RefreshButton();
	}
}

void LScrollerPictButton::RefreshButton() {
	RefreshUpButton();
	RefreshDownButton();
}

void LScrollerPictButton::RefreshUpButton() {
	if (mBtn1 && mView) {
		SPoint32 frameLoc, imageLoc;
		mView->GetFrameLocation(frameLoc);
		mView->GetImageLocation(imageLoc);

		switch (mScrollType) {
			case EScrollType_Vertical:
				if (imageLoc.v < frameLoc.v)
					mBtn1->ChangeStatus(EButtonState_Normal);
				else
					mBtn1->ChangeStatus(EButtonState_Disabled);
				break;
			case EScrollType_Horizontal:
				if (imageLoc.h < frameLoc.h)
					mBtn1->ChangeStatus(EButtonState_Normal);
				else
					mBtn1->ChangeStatus(EButtonState_Disabled);
				break;
		}
	}
}

void LScrollerPictButton::RefreshDownButton() {
	if (mBtn2 && mView) {
		SDimension16 frameSize;
		SPoint32 frameLoc;
		SDimension32 imageSize;
		SPoint32 imageLoc;
		mView->GetFrameSize(frameSize);
		mView->GetFrameLocation(frameLoc);
		mView->GetImageSize(imageSize);
		mView->GetImageLocation(imageLoc);

		switch (mScrollType) {
			case EScrollType_Vertical:
				if (((imageSize.height + imageLoc.v) - frameLoc.v) > frameSize.height)
					mBtn2->ChangeStatus(EButtonState_Normal);
				else
					mBtn2->ChangeStatus(EButtonState_Disabled);
				break;
			case EScrollType_Horizontal:
				if (((imageSize.width + imageLoc.h) - frameLoc.h) > frameSize.width)
					mBtn2->ChangeStatus(EButtonState_Normal);
				else
					mBtn2->ChangeStatus(EButtonState_Disabled);
				break;
		}
	}
}
