#include "CFilePluginList.h"
#include "T2CitySelectTable.h"
#include "T2GWorld.h"
#include "T2WorldPlugin.h"
#include "URect.h"

#include <LArrayIterator.h>
#include <UDrawingState.h>
#include <UGAColorRamp.h>

T2CitySelectTable::T2CitySelectTable(LStream *inStream)
	: LTable(inStream)
{
	mClickMessage = 'clik';
	mDoubleClickMessage = 'dblk';
}

T2CitySelectTable::~T2CitySelectTable() {
}

void T2CitySelectTable::Add(CFilePluginList *list) {
	TableIndexT index = 0;

	if (list) {
		LArrayIterator iter(*list);
		CFilePlugin *plugin;

		while (iter.Next(&plugin)) {
			index++;
			InsertCols(1, index, &plugin);
		}
	}
}

Boolean T2CitySelectTable::FetchLocalCellFrame(const TableCellT &cell, Rect &rect) {
	SPoint32 pt;
	pt.h = (cell.col - 1) * mColWidth;
	pt.v = (cell.row - 1) * mRowHeight;

	Boolean result = ImageRectIntersectsFrame(pt.h, pt.v, pt.h + mColWidth, pt.v + mRowHeight);
	ImageToLocalPoint(pt, topLeft(rect));

	rect.right = rect.left + mColWidth;
	rect.bottom = rect.top + mRowHeight;

	return result;
}

void T2CitySelectTable::DrawSelf() {
	LTable::DrawSelf();

	if (IsActive() && IsEnabled()) {
		Rect frameRect;
		if (CalcLocalFrameRect(frameRect)) {
			StColorPenState state;
			state.Normalize();

			Rect outline = frameRect;
			outline.bottom = outline.top + 4;

			RGBColor *c = &UGAColorRamp::GetColor(colorRamp_Gray7);
			::RGBForeColor(c);
			::PaintRect(&outline);
		}
	}
}

void T2CitySelectTable::DrawCell(const TableCellT &cell) {
	DrawButton(cell, EqualCell(cell, mSelectedCell));
}

void T2CitySelectTable::SelectCell(const TableCellT &cell) {
	if (IsValidCell(cell)) {
		Rect frameRect, cellFrame;
		CalcLocalFrameRect(frameRect);
		FetchLocalCellFrame(cell, cellFrame);

		if (cellFrame.left < frameRect.left) {
			Int32 delta = cellFrame.left - frameRect.left;
			ScrollPinnedImageBy(delta, 0, true);
		} else if (cellFrame.right > frameRect.right) {
			Int32 delta = cellFrame.right - frameRect.right;
			ScrollPinnedImageBy(delta, 0, true);
		}

		LTable::SelectCell(cell);

		CFilePlugin *plugin;
		GetCellData(mSelectedCell, &plugin);
		if (plugin)
			BroadcastMessage(mClickMessage, plugin);
	}
}

void T2CitySelectTable::HiliteCell(const TableCellT &cell) {
	DrawButton(cell, true);
}

void T2CitySelectTable::UnhiliteCell(const TableCellT &cell) {
	DrawButton(cell, false);
}

void T2CitySelectTable::CalcIconRect(const Rect &inRect, Rect &outRect) {
	Rect workRect;

	if (URect::Height(inRect) > URect::Height(outRect)) {
		workRect.top = inRect.top + (URect::Height(inRect) - URect::Height(outRect)) / 2;
		workRect.bottom = workRect.top + URect::Height(outRect);
	} else {
		workRect.top = inRect.top;
		workRect.bottom = inRect.bottom;
	}

	if (URect::Width(inRect) > URect::Width(outRect)) {
		workRect.left = inRect.left + (URect::Width(inRect) - URect::Width(outRect)) / 2;
		workRect.right = workRect.left + URect::Width(outRect);
	} else {
		workRect.left = inRect.left;
		workRect.right = inRect.right;
	}

	outRect = workRect;
}

void T2CitySelectTable::GetCellPICTFrame(T2GWorld *gworld, Rect &rect) {
	gworld->GetBounds(rect);
	rect.bottom = rect.top + URect::Height(rect) / 2;
}

void T2CitySelectTable::DrawButton(const TableCellT &cell, Boolean selected) {
	Rect cellFrame;
	if (!FetchLocalCellFrame(cell, cellFrame))
		return;

	T2WorldPlugin *plugin;
	GetCellData(cell, &plugin);
	if (!plugin)
		return;

	T2GWorld *pict = plugin->GetMainPicture();
	if (!pict)
		return;

	::ForeColor(blackColor);

	Rect pictFrame;
	GetCellPICTFrame(pict, pictFrame);

	Rect iconRect = pictFrame;
	CalcIconRect(cellFrame, iconRect);

	if (selected)
		::OffsetRect(&pictFrame, 0, pictFrame.bottom - pictFrame.top);

	pict->CopyImage(GetMacPort(), pictFrame, iconRect, 0, 0);

	RGBColor clr = (IsActive() && IsEnabled()) ? UGAColorRamp::GetBlackColor() : UGAColorRamp::GetColor(colorRamp_Gray4);
	::RGBForeColor(&clr);

	Rect iconFrameRect = iconRect;
	::InsetRect(&iconFrameRect, -1, -1);
	::PenSize(1, 1);
	::FrameRect(&iconFrameRect);

	if (IsActive() && IsEnabled())
		DrawButtonShadow(iconFrameRect, selected);
}

void T2CitySelectTable::DrawButtonShadow(Rect rect, Boolean selected) const {
	StColorPenState state;
	state.Normalize();

	ApplyForeAndBackColors();
	RGBColor col;
	if (selected)
		GetForeAndBackColors(0, &col);
	else
		col = UGAColorRamp::GetColor(colorRamp_Gray7);

	::RGBForeColor(&col);

	Rect r = rect;
	for (int i = 0; i < 2; i++) {
		::OffsetRect(&r, 1, 1);
		::MoveTo(r.right - 1, r.top);
		::LineTo(r.right - 1, r.bottom - 1);
		::LineTo(r.left, r.bottom - 1);
	}
}
