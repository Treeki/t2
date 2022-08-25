#include "T2Balloon.h"
#include "T2GWorld.h"
#include "T2ImageObj.h"
#include "T2Sprite.h"
#include "T2TowerDoc.h"
#include "T2TowerMainView.h"
#include "T2TowerMessage.h"
#include "URect.h"
#include "UT2Coordinate.h"

#include <math.h>
#include <LString.h>
#include <UDrawingState.h>

T2Balloon::T2Balloon(T2TowerDoc *towerDoc, Point pt, const LString &str, Int32 time) {
	Int32 zoom;
	T2TowerMainView *mainView;
	Rect portFrame;

	mTowerDoc = towerDoc;
	mSpriteIndex = 0;
	mDidPauseDoc = false;

	if (mTowerDoc) {
		if ((mainView = mTowerDoc->GetMainView())) {
			if (mainView->CalcPortFrameRect(portFrame)) {
				Rect balloonRect;
				EOrientation orientation = MakeRect(pt, portFrame, str, balloonRect);
				T2GWorld *gworld = new T2GWorld(balloonRect, 8, 0, 0, 0);
				if (gworld) {
					DrawBalloon(gworld, str, orientation);

					Point localPt = pt;
					mainView->PortToLocalPoint(localPt);

					zoom = mTowerDoc->GetZoomLevel();
					localPt.v <<= zoom;
					localPt.h <<= zoom;

					ImgObjDef objDef;
					objDef.id = 'BALL';
					objDef.rect = balloonRect;

					T2ImageObj *obj = new T2ImageObj(gworld, 1, &objDef, 6, true);
					if (obj) {
						mSpriteIndex = mTowerDoc->mSprite->NewSprite(obj, objDef.id, T2Sprite::ELayer_6, false);
						if (mSpriteIndex) {
							obj = 0;
							gworld = 0;
							mTowerDoc->mSprite->MoveSprite(mSpriteIndex, localPt);
							mTowerDoc->mSprite->ShowSprite(mSpriteIndex, true);
							if (time < 0) {
								mShowUntil = -1;
								if (!mTowerDoc->Get88()) {
									mTowerDoc->Pause();
									mDidPauseDoc = true;
								}
							} else {
								mShowUntil = ::TickCount() + (time > 0 ? time : 90);
							}
						}

						delete obj;
					}

					delete gworld;
				}
			}
		}
	}

	::SetRect(&mResumeArea, 0, 0, 0, 0);
}

T2Balloon::~T2Balloon() {
	if (mSpriteIndex && mTowerDoc->mSprite)
		mTowerDoc->mSprite->DeleteSprite(mSpriteIndex);
	if (mDidPauseDoc)
		mTowerDoc->Start();
}

void T2Balloon::DrawBalloon(T2GWorld *gworld, const LString &str, EOrientation orientation) {
	if (gworld->BeginDrawing()) {
		StColorPenState state;
		state.Normalize();

		RGBColor clr;
		clr.red = 51200;
		clr.green = 51200;
		clr.blue = 51200;
		::RGBBackColor(&clr);

		Rect rect, textRect;
		gworld->GetBounds(rect);

		switch (orientation) {
			case TopRight:
				DrawBalloonTopRight(rect, textRect);
				break;
			case BottomRight:
				DrawBalloonBottomRight(rect, textRect);
				break;
			case BottomLeft:
				DrawBalloonBottomLeft(rect, textRect);
				break;
			case TopLeft:
				DrawBalloonTopLeft(rect, textRect);
				break;
		}

		::TETextBox((Ptr) &str[1], str[0], &textRect, -2);
		gworld->EndDrawing();
	}
}

void T2Balloon::DrawBalloonTopRight(Rect rect, Rect &textRect) {
	textRect = rect;
	textRect.bottom -= 15;

	::EraseRoundRect(&textRect, 24, 24);
	::FrameRoundRect(&textRect, 24, 24);
	PolyHandle poly = ::OpenPoly();
	::MoveTo(textRect.left + 12, textRect.bottom - 1);
	::LineTo(textRect.left + 2, textRect.bottom + 12);
	::LineTo(textRect.left + 22, textRect.bottom - 1);
	::ClosePoly();
	::ErasePoly(poly);
	::FramePoly(poly);
	::KillPoly(poly);
	::InsetRect(&textRect, 12, 12);
}

void T2Balloon::DrawBalloonBottomRight(Rect rect, Rect &textRect) {
	textRect = rect;
	textRect.left += 15;

	::EraseRoundRect(&textRect, 24, 24);
	::FrameRoundRect(&textRect, 24, 24);
	PolyHandle poly = ::OpenPoly();
	::MoveTo(textRect.left + 1, textRect.top + 10);
	::LineTo(textRect.left - 15, textRect.top);
	::LineTo(textRect.left + 1, textRect.top + 20);
	::ClosePoly();
	::ErasePoly(poly);
	::KillPoly(poly);
	::MoveTo(textRect.left, textRect.top + 10);
	::LineTo(textRect.left - 15, textRect.top);
	::LineTo(textRect.left, textRect.top + 20);
	::InsetRect(&textRect, 12, 12);
}

void T2Balloon::DrawBalloonBottomLeft(Rect rect, Rect &textRect) {
	textRect = rect;
	textRect.right -= 15;

	::EraseRoundRect(&textRect, 24, 24);
	::FrameRoundRect(&textRect, 24, 24);
	PolyHandle poly = ::OpenPoly();
	::MoveTo(textRect.right - 1, textRect.top + 10);
	::LineTo(textRect.right + 14, textRect.top);
	::LineTo(textRect.right - 1, textRect.top + 20);
	::ClosePoly();
	::ErasePoly(poly);
	::KillPoly(poly);
	::MoveTo(textRect.right, textRect.top + 10);
	::LineTo(textRect.right + 14, textRect.top);
	::LineTo(textRect.right, textRect.top + 20);
	::InsetRect(&textRect, 12, 12);
}

void T2Balloon::DrawBalloonTopLeft(Rect rect, Rect &textRect) {
	textRect = rect;
	textRect.bottom -= 15;

	::EraseRoundRect(&textRect, 24, 24);
	::FrameRoundRect(&textRect, 24, 24);
	PolyHandle poly = ::OpenPoly();
	::MoveTo(textRect.right - 12, textRect.bottom - 1);
	::LineTo(textRect.right - 2, textRect.bottom + 12);
	::LineTo(textRect.right - 22, textRect.bottom - 1);
	::ClosePoly();
	::ErasePoly(poly);
	::FramePoly(poly);
	::KillPoly(poly);
	::InsetRect(&textRect, 12, 12);
}

T2Balloon::EOrientation T2Balloon::MakeRect(Point pt, Rect inRect, const LString &str, Rect &outRect) {
	Int16 r30;
	Int16 r29;
	UInt32 result = 0; // top right
	Int16 r27;
	Int16 r26;
	Int16 r25;

	r25 = 1.4f * ::StringWidth(str);
	r30 = sqrt(r25 / 25);

	Int16 maxWidth;
	r27 = CalcCR(str, maxWidth);
	if (r30 < r27) {
		r30 = r27;
		r26 = r27 * 16;
		r29 = maxWidth + 10;
	} else {
		r26 = r30 * 16;
		r29 = (r30 * 25) + 20;
	}
	outRect.bottom = pt.v;
	outRect.top = outRect.bottom - r26;
	outRect.left = pt.h;
	outRect.right = outRect.left + r29;

	if ((r29 * r30) < (r25 + 16))
		outRect.top -= 16;

	::InsetRect(&outRect, -18, -12);
	::OffsetRect(&outRect, 18, -12);

	outRect.top -= 15;

	if (outRect.top < inRect.top) {
		outRect.top += 15;
		::OffsetRect(&outRect, 0, URect::Height(outRect));
		outRect.right += 15;
		result ^= 2; // bottom right
	}

	if (outRect.right >= inRect.right) {
		::OffsetRect(&outRect, -URect::Width(outRect), 0);
		result ^= 1; // switch to left side
	}

	::OffsetRect(&outRect, -pt.h, -pt.v);

	return (EOrientation) result;
}

Int32 T2Balloon::CalcCR(const LString &str, Int16 &outMaxWidth) {
	Int32 result = 0; // r26
	Int16 r30 = 1;
	Int16 r29 = 0;

	for (Int16 i = 1; i < str.Length(); i++) {
		if (str[i] == 13) {
			result += 1;
			if (i == r30) {
				// empty line
				r30++;
			} else {
				(void)r29; // mess with the register allocator a little bit
				Int16 r28 = ::TextWidth(str, r30, i - r30);
				if (r29 < r28)
					r29 = r28;
				r30 = i + 1;
			}
		}
	}

	outMaxWidth = r29;
	return result;
}

Boolean T2Balloon::MouseInRect() {
	Boolean result = false;

	if (mSpriteIndex && mTowerDoc->mSprite && !::EmptyRect(&mResumeArea)) {
		T2TowerMainView *mainView = mTowerDoc->GetMainView();
		if (mainView) {
			mainView->FocusDraw();

			SPoint32 unusedPt;
			Point pt;
			SPoint32 imagePt;

			::GetMouse(&pt);
			mainView->LocalToImagePoint(pt, imagePt);

			pt.h = imagePt.h;
			pt.v = imagePt.v;
			UT2Coordinate::QDToUnit(pt, mTowerDoc->GetZoomLevel());

			result = ::PtInRect(pt, &mResumeArea);
		}
	}

	return result;
}

void T2Balloon::SetResumeArea(const Rect &rect) {
	mResumeArea = rect;
}



void UT2Balloon::DoBalloon(T2TowerDoc *towerDoc, Point pt, const LString &str, Int32 time) {
	T2Balloon *balloon = towerDoc->mTowerMessage->mBalloon;

	if (IsBalloonOn(towerDoc)) {
		delete balloon;
		balloon = new T2Balloon(towerDoc, pt, str, time);
		if (balloon && (balloon->mSpriteIndex != 0) == false) {
			delete balloon;
			balloon = 0;
		}
		towerDoc->mTowerMessage->mBalloon = balloon;
	}
}

void UT2Balloon::DoBalloon(T2TowerDoc *towerDoc, const Rect &rect, const LString &str, Int32 time) {
	T2Balloon *balloon = towerDoc->mTowerMessage->mBalloon;

	if (IsBalloonOn(towerDoc)) {
		delete balloon;
		Point pt, pt2, pt3;
		pt3.h = (rect.left + rect.right) / 2;
		pt3.v = (rect.top + rect.bottom) / 2;
		pt2 = pt3;
		pt = pt2;
		balloon = new T2Balloon(towerDoc, pt, str, time);
		if (balloon && (balloon->mSpriteIndex != 0) == false) {
			delete balloon;
			balloon = 0;
		}
		towerDoc->mTowerMessage->mBalloon = balloon;
	}
}

void UT2Balloon::Pick(T2TowerDoc *towerDoc, Boolean flag) {
	if (towerDoc->mTowerMessage->mBalloon) {
		Int32 showUntil = towerDoc->mTowerMessage->mBalloon->GetShowUntil();
		Boolean willHide;
		(void)willHide; // mess with the register allocator

		if (flag) {
			willHide = true;
		} else if (showUntil < 0) {
			willHide = !towerDoc->mTowerMessage->mBalloon->MouseInRect();
		} else {
			willHide = showUntil < ::TickCount();
		}

		if (willHide) {
			delete towerDoc->mTowerMessage->mBalloon;
			towerDoc->mTowerMessage->mBalloon = 0;
		}
	}
}

void UT2Balloon::SetBalloonOn(T2TowerDoc *towerDoc, Boolean on) {
	towerDoc->mTowerMessage->m14 = on;
}

Boolean UT2Balloon::IsBalloonOn(T2TowerDoc *towerDoc) {
	return towerDoc->mTowerMessage->m14;
}
