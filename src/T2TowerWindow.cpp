#include "T2Application.h"
#include "T2TowerDoc.h"
#include "T2TowerWindow.h"

#include <Palettes.h>
#include <UException.h>
#include <UWindows.h>

T2TowerWindow::T2TowerWindow(LStream *inStream)
	: T2MainWindow(inStream)
{
}

void T2TowerWindow::InitTowerWindow(T2TowerDoc *towerDoc) {
	mTowerDoc = towerDoc;
}

void T2TowerWindow::DoSetStandardSize(SDimension16 size) {
	mStandardSize = size;
	mMinMaxSize.right = size.width;
	mMinMaxSize.bottom = size.height;

	Rect windowRect, clippedRect;
	windowRect = UWindows::GetWindowContentRect(mMacWindowP);
	clippedRect = windowRect;

	if (mMinMaxSize.right < mFrameSize.width)
		clippedRect.right -= (mFrameSize.width - mMinMaxSize.right);
	if (mMinMaxSize.bottom < mFrameSize.height)
		clippedRect.bottom -= (mFrameSize.height - mMinMaxSize.bottom);

	if (!::EqualRect(&clippedRect, &windowRect))
		SendAESetBounds(&clippedRect, true);
}

void T2TowerWindow::DoSetZoom(Boolean flag) {
	if (!HasAttribute(windAttr_Zoomable))
		#line 95
		ThrowOSErr_(errAENotModifiable);

	Rect currBounds = UWindows::GetWindowContentRect(mMacWindowP);
	Rect zoomBounds;

	if (flag) {
		if (CalcStandardBounds(zoomBounds))
			return;
	} else {
		zoomBounds = mUserBounds;
		if (mMoveOnlyUserZoom) {
			zoomBounds.right = zoomBounds.left + (currBounds.right - currBounds.left);
			zoomBounds.bottom = zoomBounds.top + (currBounds.bottom - currBounds.top);
		}
	}

	Int16 width = zoomBounds.right - zoomBounds.left;
	Int16 height = zoomBounds.bottom - zoomBounds.top;
	mMoveOnlyUserZoom = false;

	if (((currBounds.right - currBounds.left) == width) && ((currBounds.bottom - currBounds.top) == height)) {
		::MoveWindow(mMacWindowP, zoomBounds.left, zoomBounds.top, false);
		mMoveOnlyUserZoom = true;
	} else if (::EqualPt(topLeft(currBounds), topLeft(zoomBounds))) {
		::SizeWindow(mMacWindowP, width, height, false);
		ResizeFrameTo(width, height, true);
	} else {
		FocusDraw();
		ApplyForeAndBackColors();
		::EraseRect(&mMacWindowP->portRect);
		if (flag) {
			SetWindowStandardState(mMacWindowP, &zoomBounds);
			::ZoomWindow(mMacWindowP, inZoomOut, false);
		} else {
			SetWindowUserState(mMacWindowP, &zoomBounds);
			::ZoomWindow(mMacWindowP, inZoomIn, false);
		}
		ResizeFrameTo(width, height, true);
	}
}

void T2TowerWindow::ActivateSelf() {
	LWindow::ActivateSelf();

	PaletteHandle palette = ::GetPalette(mMacWindowP);
	T2Application *app = mTowerDoc->GetApplication();

	// TODO: T2FloatingWindow, T2ToolWindow, T2ControlWindow, UT2Balloon
}

void T2TowerWindow::DeactivateSelf() {
	LWindow::DeactivateSelf();

	// TODO: UT2Balloon
}
