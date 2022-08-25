#include "T2GWorld.h"
#include "T2ImageObj.h"
#include "T2MainWindow.h"
#include "T2Sprite.h"
#include "T2TowerDoc.h"
#include "T2TowerMainView.h"
#include "T2TowerWindow.h"
#include "T2WorldDef.h"
#include "URect.h"
#include "UT2Coordinate.h"

#include <LArrayIterator.h>
#include <UException.h>
#include <URegions.h>

T2TowerMainView::T2TowerMainView(LStream *stream)
	: T2UnitUpdtView(stream)
{
	mTowerDoc = 0;
	::SetRect(&m98, 0, 0, 0, 0);
	mGWorld = 0;
	mCursorGWorld = 0;
	mToolDef = 0;
	mB4 = 0;
	mB5 = 17;
	mB6 = 0;
	mB8 = 0;
	mCursorSpriteIndex = 0;
	mArrowSpriteIndex = 0;
	::SetRect(&mC4, 0, 0, 0, 0);
	mCC = 0;
	mDC = true;
	mEmergencyFlag = false;
}

T2TowerMainView::~T2TowerMainView() {
	if (mGWorld)
		delete mGWorld;
	mGWorld = 0;
	mTowerDoc->mTowerMainView = 0;
}

void T2TowerMainView::InitT2TowerMainView(T2TowerDoc *doc, Int32 a, Int32 b) {
	mTowerDoc = doc;

	GDHandle mainGDH = ::GetMainDevice();
	#line 130
	Assert_(mainGDH != 0);

	PixMapHandle gdPMapH = (*mainGDH)->gdPMap;
	#line 132
	Assert_(gdPMapH != 0);

	Rect bounds = (*gdPMapH)->bounds;
	bounds.right -= 20;
	bounds.bottom -= 60;

	T2WorldDef *worldDef = mTowerDoc->GetWorldDef();
	CTabHandle ctab = worldDef->mCTabH;
	mGWorld = new T2GWorld(bounds, 8, ctab, 0, 0);
	ThrowIfNil_(mGWorld);

	::SetRect(&m98, 0, 0, worldDef->m152, worldDef->m150);
	AdjustWorldBounds();

	if (a < 0) {
		Point pt = mTowerDoc->mWorldDef->mInitPos;
		UT2Coordinate::UnitToQD(pt, mTowerDoc->GetZoomLevel(), 1);
		a = pt.v - (mFrameSize.height / 2);
		b = pt.h - (mFrameSize.width / 2);
	}

	ScrollImageTo(b, a, false);
	mRect3 = mRect1;
	mRect2 = mRect3;
}

void T2TowerMainView::AdjustCursorSelf(Point pt, const EventRecord &event) {
}

void T2TowerMainView::DrawSelf() {
	Rect srcRect = mRevealedRect;
	::OffsetRect(&srcRect, -srcRect.left, -srcRect.top);
	Rect dstRect = srcRect;
	::OffsetRect(&dstRect, mPortOrigin.h, mPortOrigin.v);
	mGWorld->CopyImage(GetMacPort(), srcRect, dstRect, 0, 0);
}

void T2TowerMainView::AddSpriteUpdateRect(const Rect &rect, Boolean flag1, Boolean flag2) {
	Rect frameRect;
	if (CalcLocalFrameRect(frameRect)) {
		Rect qdRect, unitRect;
		if (::SectRect(&rect, &frameRect, &qdRect)) {
			UT2Coordinate::QDToUnit(qdRect, unitRect, mTowerDoc->GetZoomLevel());
			if (flag1) {
				if (flag2) {
					if (::EmptyRect(&mSpriteUpdateRect))
						mSpriteUpdateRect = unitRect;
					else
						::UnionRect(&mSpriteUpdateRect, &unitRect, &mSpriteUpdateRect);
					InvalUnitRect(unitRect, false);
				} else {
					InvalUnitRect(unitRect, true);
				}
			} else {
				InvalUnitRect(unitRect, !flag2);
			}
		}
	}
}

void T2TowerMainView::DrawSimulation() {
	if (!::EmptyRect(&mRect3)) {
		Rect r = mRect3;
		FocusDraw();
		DrawSimulationOffscreen();
		CopySimulationImage(r);
	}
	mDC = false;
}

void T2TowerMainView::DrawSimulationOffscreen() {
	if (mGWorld && mGWorld->BeginDrawing()) {
		StRegion region;
		::GetClip(region);
		::SetOrigin(mPortOrigin.h, mPortOrigin.v);

		Rect frameRect, unitRect;
		CalcLocalFrameRect(frameRect);
		UT2Coordinate::UnitToQD(mRect2, unitRect, mTowerDoc->GetZoomLevel(), 1);
		::SectRect(&unitRect, &frameRect, &unitRect);
		::ClipRect(&unitRect);

		Rect bgRect;
		UT2Coordinate::UnitToBkgnd(mRect2, bgRect);
		mTowerDoc->DrawBkgnd(bgRect);

		Rect spriteRect;
		if (::EmptyRect(&mRect2)) {
			spriteRect = mSpriteUpdateRect;
		} else if (::EmptyRect(&mSpriteUpdateRect)) {
			spriteRect = mRect2;
		} else {
			::UnionRect(&mRect2, &mSpriteUpdateRect, &spriteRect);
		}

		if (!::EmptyRect(&spriteRect)) {
			UT2Coordinate::UnitToQD(spriteRect, unitRect, mTowerDoc->GetZoomLevel(), 1);
			::SectRect(&unitRect, &frameRect, &unitRect);
			::ClipRect(&unitRect);
			mTowerDoc->mSprite->DrawLayer(mGWorld, T2Sprite::ELayer_1, mTowerDoc->GetZoomLevel());
		}

		UT2Coordinate::UnitToQD(mRect3, unitRect, mTowerDoc->GetZoomLevel(), 1);
		::SectRect(&unitRect, &frameRect, &unitRect);
		::ClipRect(&unitRect);
		mTowerDoc->DrawBuilding(mRect3, spriteRect);
		mTowerDoc->mSprite->DrawLayer(mGWorld, T2Sprite::ELayer_4, mTowerDoc->GetZoomLevel());
		mTowerDoc->mSprite->DrawLayer(mGWorld, T2Sprite::ELayer_5, mTowerDoc->GetZoomLevel());
		FrameCursor();
		mTowerDoc->mSprite->DrawLayer(mGWorld, T2Sprite::ELayer_6, mTowerDoc->GetZoomLevel());

		::SetOrigin(0, 0);
		::SetClip(region);
		mGWorld->EndDrawing();

		URect::SetEmpty(mSpriteUpdateRect);
		ClearUpdateRect();
	}
}

void T2TowerMainView::CopySimulationImage(const Rect &rect) {
	Rect srcRect, dstRect;
	UT2Coordinate::UnitToQD(rect, dstRect, mTowerDoc->GetZoomLevel(), 1);
	srcRect = dstRect;
	::OffsetRect(&srcRect, -mPortOrigin.h, -mPortOrigin.v);
	mGWorld->CopyImage(GetMacPort(), srcRect, dstRect, 0, 0);
}

void T2TowerMainView::ScrollImageBy(Int32 h, Int32 v, Boolean refresh) {
	mImageLocation.h -= h;
	mImageLocation.v -= v;
	CalcPortOrigin();
	SetClipURect();

	if (refresh) {
		Int32 absH = h;
		if (absH < 0) absH = -absH;

		Int32 absV = v;
		if (absV < 0) absV = -absV;

		if (absH < (mRevealedRect.right - mRevealedRect.left) && absV < (mRevealedRect.bottom - mRevealedRect.top)) {
			ScrollBits(h, v);
		} else {
			mRect3 = mRect1;
			mRect2 = mRect3;
			DrawSimulationOffscreen();
		}
	}

	OutOfFocus(this);

	LArrayIterator iter(mSubPanes);
	LPane *subPane;

	while (iter.Next(&subPane)) {
		subPane->AdaptToSuperScroll(h, v);
	}

	if (mSuperView)
		mSuperView->SubImageChanged(this);

	if (refresh) {
		FocusDraw();
		DrawSelf();
	}
}

void T2TowerMainView::ScrollBits(Int32 h, Int32 v) {
	Rect portFrameRect, localFrameRect, rectV, rectH;

	CalcPortFrameRect(portFrameRect);
	mGWorld->ScrollBits(portFrameRect, h, v);
	CalcLocalFrameRect(localFrameRect);

	rectV = rectH = localFrameRect;

	if (v != 0) {
		if (v > 0) {
			rectV.top = localFrameRect.bottom - v;
			rectH.bottom = rectV.top;
		} else {
			rectV.bottom = localFrameRect.top - v;
			rectH.top = rectV.bottom;
		}

		UT2Coordinate::QDToUnit(rectV, mTowerDoc->GetZoomLevel());
		InvalUnitRect(rectV, true);
		DrawSimulationOffscreen();
	}

	if (h != 0) {
		if (h > 0) {
			rectH.left = localFrameRect.right - h;
		} else {
			rectH.right = localFrameRect.left - h;
		}

		UT2Coordinate::QDToUnit(rectH, mTowerDoc->GetZoomLevel());
		InvalUnitRect(rectH, true);
		DrawSimulationOffscreen();
	}
}

void T2TowerMainView::Click(SMouseDownEvent &event) {
	FocusDraw();
	LView::Click(event);
}

void T2TowerMainView::ClickSelf(const SMouseDownEvent &event) {
	if (mEmergencyFlag)
		return;

	// TODO an obscene amount of shit
}

Int32 T2TowerMainView::LimitCheckLeftDelta(Int32 value) {
	Int32 result = value;

	if (result != 0) {
		Int32 delta = mImageLocation.h - result;
		if (delta > mFrameLocation.h) {
			if (mImageLocation.h <= mFrameLocation.h)
				result = mImageLocation.h - mFrameLocation.h;
			else if (result < 0)
				result = 0;
		} else if ((delta + mImageSize.width) < (mFrameLocation.h + mFrameSize.width)) {
			if ((mImageLocation.h + mImageSize.width) >= (mFrameLocation.h + mFrameSize.width))
				result = (mImageSize.width + (mImageLocation.h - mFrameLocation.h)) - mFrameSize.width;
			else if (result > 0)
				result = 0;
		}
	}

	return result;
}

Int32 T2TowerMainView::LimitCheckTopDelta(Int32 value) {
	Int32 result = value;

	if (result != 0) {
		Int32 delta = mImageLocation.v - result;
		if (delta > mFrameLocation.v) {
			if (mImageLocation.v <= mFrameLocation.v)
				result = mImageLocation.v - mFrameLocation.v;
			else if (result < 0)
				result = 0;
		} else if ((delta + mImageSize.height) < (mFrameLocation.v + mFrameSize.height)) {
			if ((mImageLocation.v + mImageSize.height) >= (mFrameLocation.v + mFrameSize.height))
				result = (mImageSize.height + (mImageLocation.v - mFrameLocation.v)) - mFrameSize.height;
			else if (result > 0)
				result = 0;
		}
	}

	return result;
}

void T2TowerMainView::AdjustWorldBounds() {
	Rect rect = m98;
	UT2Coordinate::UnitToQD(rect, mTowerDoc->GetZoomLevel(), 1);
	ResizeImageTo(rect.right - rect.left, rect.bottom - rect.top, false);

	WindowPtr windowPtr = GetMacPort();
	T2TowerWindow *window = (T2TowerWindow *) LWindow::FetchWindowObject(windowPtr);
	Rect bounds;
	mGWorld->GetBounds(bounds);

	Int16 width = (URect::Width(bounds) >= mImageSize.width) ? mImageSize.width : (bounds.right - bounds.left);
	Int16 height = (URect::Height(bounds) >= mImageSize.height) ? mImageSize.height : (bounds.bottom - bounds.top);
	width += 15;
	height += 15;

	SDimension16 dim = { 0, 0 };
	dim.width = width;
	dim.height = height;
	window->DoSetStandardSize(dim);
}

void T2TowerMainView::DoHandScroll() {
	// TODO: T2ToolWindow
}

void T2TowerMainView::DoZoom(const SMouseDownEvent &event) {
	Point pt = event.whereLocal;
	Int16 oldZoom = mTowerDoc->GetZoomLevel();
	Boolean isZoomOut = !(event.macEvent.modifiers & optionKey);

	UT2Coordinate::QDToUnit(pt, oldZoom);

	if (isZoomOut) {
		if (oldZoom <= 0) return;
		mTowerDoc->SetZoomLevel(oldZoom - 1);
	} else {
		if (oldZoom >= 2) return;
		mTowerDoc->SetZoomLevel(oldZoom + 1);
	}

	UT2Coordinate::UnitToQD(pt, mTowerDoc->GetZoomLevel(), 1);

	AdjustWorldBounds();

	Int32 h = pt.h - (mFrameSize.width / 2);
	Int32 v = pt.v - (mFrameSize.height / 2);
	ScrollPinnedImageBy(h + (mImageLocation.h - mFrameLocation.h), v + (mImageLocation.v - mFrameLocation.v), false);

	mRect3 = mRect1;
	mRect2 = mRect3;
	DrawSimulation();
}

void T2TowerMainView::DoZoomNormal(const Rect &rect) {
	Point qdPt, tempPt, unitPt;
	unitPt.h = (rect.left + rect.right) / 2;
	unitPt.v = (rect.top + rect.bottom) / 2;

	tempPt = unitPt;
	qdPt = tempPt;
	mTowerDoc->SetZoomLevel(0);

	UT2Coordinate::UnitToQD(qdPt, mTowerDoc->GetZoomLevel(), 1);

	AdjustWorldBounds();

	Int32 r28 = qdPt.h - (mFrameSize.width / 2);
	Int32 r27 = qdPt.v - (mFrameSize.height / 2);
	ScrollPinnedImageBy(r28 + (mImageLocation.h - mFrameLocation.h), r27 + (mImageLocation.v - mFrameLocation.v), false);

	mRect3 = mRect1;
	mRect2 = mRect3;
	DrawSimulation();
}

void T2TowerMainView::SetClipURect() {
	CalcLocalFrameRect(mRect1);
	UT2Coordinate::QDToUnit(mRect1, mTowerDoc->GetZoomLevel());
	::SectRect(&mRect1, &m98, &mRect1);
}

void T2TowerMainView::ResizeFrameBy(Int16 width, Int16 height, Boolean refresh) {
	Rect oldFrameRect;
	CalcLocalFrameRect(oldFrameRect);
	LPane::ResizeFrameBy(width, height, refresh);
	CalcRevealedRect();
	SetClipURect();

	if (refresh) {
		Rect newFrameRect;
		CalcLocalFrameRect(newFrameRect);

		Rect rect1, rect2;
		rect1 = rect2 = newFrameRect;

		if (newFrameRect.bottom > oldFrameRect.bottom) {
			rect1.top = oldFrameRect.bottom;
			rect2.bottom = oldFrameRect.bottom;
			UT2Coordinate::QDToUnit(rect1, mTowerDoc->GetZoomLevel());
			::SectRect(&rect1, &m98, &rect1);
			InvalUnitRect(rect1, true);
			DrawSimulationOffscreen();
		}

		if (newFrameRect.right > oldFrameRect.right) {
			rect2.left = oldFrameRect.right;
			UT2Coordinate::QDToUnit(rect2, mTowerDoc->GetZoomLevel());
			::SectRect(&rect2, &m98, &rect2);
			InvalUnitRect(rect2, true);
			DrawSimulationOffscreen();
		}
	}

	OutOfFocus(this);

	LArrayIterator iter(mSubPanes);
	LPane *subPane;

	while (iter.Next(&subPane)) {
		subPane->AdaptToSuperFrameSize(width, height, refresh);
	}

	ReconcileFrameAndImage(refresh);
}

void T2TowerMainView::ReconcileFrameAndImage(Boolean refresh) {
	if (mReconcileOverhang) {
		SPoint32 oldPos, newPos;
		GetScrollPosition(oldPos);
		newPos = oldPos;

		if ((mFrameLocation.v + mFrameSize.height) > (mImageLocation.v + mImageSize.height)) {
			newPos.v = mImageSize.height - mFrameSize.height;
			if (newPos.v < 0)
				newPos.v = 0;
		}
		if ((mFrameLocation.h + mFrameSize.width) > (mImageLocation.h + mImageSize.width)) {
			newPos.h = mImageSize.width - mFrameSize.width;
			if (newPos.h < 0)
				newPos.h = 0;
		}

		if (newPos.v != oldPos.v || newPos.h != oldPos.h) {
			ScrollImageTo(newPos.h, newPos.v, refresh);
			if (refresh)
				DontRefresh();
		}
	}
}

void T2TowerMainView::InvalUnitView() {
	CalcLocalFrameRect(mRect1);
	UT2Coordinate::QDToUnit(mRect1, mTowerDoc->GetZoomLevel());
	::SectRect(&mRect1, &m98, &mRect1);
	mRect3 = mRect1;
	mRect2 = mRect1;
}

Boolean T2TowerMainView::IsScrollToPt(Point pt, Int16 var) {
	Boolean result = false;

	UInt32 check = PointAreaCheck(pt);
	if (check) {
		Int32 r30, r29;
		r30 = r29 = 0;

		static const Point unit = { 1, 1 };
		Point qdPt = unit;
		UT2Coordinate::UnitToQD(qdPt, var, 1);

		if (check & 1)
			r30 = -qdPt.v;
		else if (check & 2)
			r30 = qdPt.v;

		if (check & 4)
			r29 = -qdPt.h;
		else if (check & 8)
			r29 = qdPt.h;

		if (r30 != 0 || r29 != 0) {
			ScrollPinnedImageBy(r29, r30, true);
			result = true;
		}
	}

	return result;
}

UInt32 T2TowerMainView::PointAreaCheck(Point pt) {
	if (::PtInRect(pt, &mRect1))
		return 0;

	UInt32 result = 0;

	if (pt.v < mRect1.top)
		result |= 1;
	else if (pt.v >= mRect1.bottom)
		result |= 2;

	if (pt.h < mRect1.left)
		result |= 4;
	else if (pt.h >= mRect1.right)
		result |= 8;

	return result;
}

void T2TowerMainView::CenterOnView(Rect rect) {
	Rect qdRect;
	UT2Coordinate::UnitToQD(rect, qdRect, mTowerDoc->GetZoomLevel(), 0);

	Rect local28;
	local28.right = ((qdRect.left + qdRect.right) / 2) - (mFrameSize.width / 2);
	local28.bottom = ((qdRect.top + qdRect.bottom) / 2) - (mFrameSize.height / 2);
	local28.left = mImageLocation.h;
	local28.top = mImageLocation.v;

	Int32 r30 = LimitCheckLeftDelta(local28.left + local28.right);
	Int32 r29 = LimitCheckTopDelta(local28.top + local28.bottom);
	ScrollImageBy(r30, r29, true);
}

void T2TowerMainView::PointByArrow(const Rect &rect, Boolean flag, Int16 var) {
	Rect qdRect;
	UT2Coordinate::UnitToQD(rect, qdRect, 0, !flag);
	::OffsetRect(&qdRect, 0, var);
	T2GWorld *theArrow = 0;

	if (mArrowSpriteIndex == 0) {
		theArrow = new T2GWorld(12000, 8, 0, 0, 0);
		#line 1484
		Assert_(theArrow != 0);

		ImgObjDef imgObjDef;
		imgObjDef.id = 'ARRW';
		theArrow->GetBounds(imgObjDef.rect);

		Point pt;
		::SetPt(&pt, URect::Width(imgObjDef.rect) / 2, URect::Height(imgObjDef.rect));
		::OffsetRect(&imgObjDef.rect, -pt.h, -pt.v);
		theArrow->SetBounds(imgObjDef.rect);

		T2ImageObj *imageObj = new T2ImageObj(theArrow, 1, &imgObjDef, 6, true);
		mArrowSpriteIndex = mTowerDoc->mSprite->NewSprite(imageObj, 'ARRW', T2Sprite::ELayer_3, false);
	}

	if (mArrowSpriteIndex) {
		Rect bounds;
		theArrow->GetBounds(bounds);

		Point pt;
		::SetPt(&pt, (qdRect.left + qdRect.right) / 2, qdRect.top);
		mTowerDoc->mSprite->MoveSprite(mArrowSpriteIndex, pt);
		mTowerDoc->mSprite->ShowSprite(mArrowSpriteIndex, true);
		mD4 = mTowerDoc->Get88();
		mTowerDoc->Pause();
		mArrowPauseUntilTicks = ::TickCount() + 180;
	}
}

void T2TowerMainView::CheckIfHideArrow() {
	if (mArrowSpriteIndex && mArrowPauseUntilTicks < ::TickCount()) {
		HideArrow();
		if (!mD4 && mTowerDoc->Get88()) {
			mTowerDoc->Start();
		}
	}
}

void T2TowerMainView::HideArrow() {
	if (mArrowSpriteIndex) {
		mTowerDoc->mSprite->DeleteSprite(mArrowSpriteIndex);
		mArrowSpriteIndex = 0;
	}
}

Boolean T2TowerMainView::IsPauseByArrow() const {
	return mArrowSpriteIndex && !mD4;
}

void T2TowerMainView::DisposeCursors() {
	mToolDef = 0;
	mB6 = 0;
	mB8 = 0;
	if (mCursorSpriteIndex)
		mTowerDoc->mSprite->DeleteSprite(mCursorSpriteIndex);
	mCursorSpriteIndex = 0;
}

void T2TowerMainView::TrackingCursor(const EventRecord &event) {
	// TODO T2ToolDef
}

void T2TowerMainView::HideCursor() {
	DisposeCursors();
}

void T2TowerMainView::SimulateDragBuild(Point pt, Rect &rect) {
	Int16 unk = 0;
	Point pt1 = pt;
	Point pt2 = pt1;
	Rect workRect = rect;
	Point startTL = topLeft(rect);
	UT2Coordinate::UnitToQD(startTL, 0, 0);

	while (::StillDown()) {
		if (pt1.h != pt2.h) {
			mTowerDoc->DoDragByTenantTool(workRect, unk);
			IsScrollToPt(pt1, mTowerDoc->GetZoomLevel());
			pt2 = pt1;
		}

		Point mouse;
		::GetMouse(&mouse);
		pt1 = mouse;
		UT2Coordinate::QDToUnit(pt1, mTowerDoc->GetZoomLevel());

		workRect = rect;
		::OffsetRect(&workRect, pt1.h - pt.h, 0);
		mC4 = workRect;

		mouse = startTL;
		mouse.h += (pt1.h - pt.h) * 8;
		mTowerDoc->mSprite->MoveSprite(mCursorSpriteIndex, mouse);
	}

	rect = workRect;
}

void T2TowerMainView::FrameCursor() {
	if (mCursorSpriteIndex) {
		Rect qdRect;
		UT2Coordinate::UnitToQD(mC4, qdRect, mTowerDoc->GetZoomLevel(), 1);
		mGWorld->DrawFocusRect(qdRect, mCC);
	}
}

void T2TowerMainView::DoEmergency() {
	mEmergencyFlag = true;
	DisposeCursors();
}
