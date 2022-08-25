#include "T2Balloon.h"
#include "T2EquipDef.h"
#include "T2TowerMainView.h"
#include "T2TowerMessage.h"
#include "T2TowerDoc.h"
#include "UT2Coordinate.h"

#include <LArrayIterator.h>
#include <LPane.h>
#include <LWindow.h>
#include <UDesktop.h>
#include <UDrawingState.h>

T2TowerMessage::T2TowerMessage(T2TowerDoc *towerDoc) {
	mTowerDoc = towerDoc;
	m8 = 0;
	mCurResFile = ::CurResFile();
	mArray = new LArray;
	m14 = 0;
	mBalloon = 0;
	StartIdling();
}

T2TowerMessage::~T2TowerMessage() {
	UT2Balloon::Pick(mTowerDoc, true);
	StopIdling();
	SetInfoBarMsg(0);
	if (mArray) {
		InfoBarMsgItem *item;
		while (mArray->FetchItemAt(LArray::index_First, &item)) {
			mArray->RemoveItemsAt(1, LArray::index_First);
			delete item;
		}
		delete mArray;
	}
}

void T2TowerMessage::InfoBarMessage(const LString &str, Int16 a, Int16 b, T2PluginSound *pluginSound, CFilePlugin *filePlugin) {
	if (mArray) {
		InfoBarMsgItem *check;
		if (mArray->FetchItemAt(LArray::index_First, &check)) {
			if (check->m110 && check->m10C != -1 && check->m10C > 120)
				check->m110 = check->m110 - check->m10C + 120;
		}

		if (mArray->GetCount() < 20) {
			InfoBarMsgItem *item;
			item = new InfoBarMsgItem(str, a, b, pluginSound, filePlugin);
			mArray->InsertItemsAt(1, LArray::index_Last, &item);
		}
	}
}

void T2TowerMessage::CancelInfoBarMessage(const LString &str) {
	if (mArray) {
		InfoBarMsgItem *item = 0;
		LArrayIterator iter(*mArray);

		while (iter.Next(&item)) {
			if (iter.GetCurrentIndex() > 1 && str.CompareTo(item->mString) == 0) {
				mArray->RemoveItemsAt(1, iter.GetCurrentIndex());
				delete item;
			}
		}
	}
}

void T2TowerMessage::PassiveInfoBarMessage(const LString &str, Int16 a) {
	Boolean found = false;

	if (mArray) {
		InfoBarMsgItem *item = 0;
		LArrayIterator iter(*mArray);

		while (!found && iter.Next(&item)) {
			found = str == item->mString;
		}

		if (!found)
			InfoBarMessage(str, a, 0, 0, 0);
	}
}

void T2TowerMessage::SetInfoBarMsg(InfoBarMsgItem *item) {
	// TODO: T2MsgWindow, T2SoundPlayer, T2PluginSound
}

void T2TowerMessage::EquipBalloonMessage(const LString &str, T2Equip *equip) {
	if (equip) {
		// TODO: T2Equip
	}
}

void T2TowerMessage::PeopleBalloonMessage(const LString &str, T2People *people) {
	if (people) {
		// TODO: T2People, T2TowerMainView
	}
}

void T2TowerMessage::EquipBalloonMessage(const LString &str, Point pt) {
	UT2Balloon::DoBalloon(mTowerDoc, pt, str, 0);
}

void T2TowerMessage::BuildErr(const LString &str) {
	Point pt;
	::GetMouse(&pt);
	mTowerDoc->GetMainView()->LocalToPortPoint(pt);
	UT2Balloon::DoBalloon(mTowerDoc, pt, str, 0);
}

void T2TowerMessage::BuildErr(UInt32 a, T2EquipDef *equipDef) {
	LStr255 str;
	if (GetBuildErrString(a, str)) {
		if (equipDef) {
			LStr255 toolName;
			equipDef->GetToolName(toolName, 0);
			str.Insert(toolName, 0);
		}
		BuildErr(str);
	}
}

Boolean T2TowerMessage::GetBuildErrString(UInt32 a, LString &str) {
	Boolean result = (a != 0 && a < 76);

	if (result)
		str.Assign(9999, a);

	return result;
}

void T2TowerMessage::ClearBuildErr() {
	UT2Balloon::Pick(mTowerDoc, true);
}

void T2TowerMessage::ObjectBalloonMessage(const LString &str, const Rect &rect) {
	if (!mBalloon) {
		Point tl = topLeft(rect);
		Point br = botRight(rect);
		UT2Coordinate::UnitToQD(tl, mTowerDoc->GetZoomLevel(), 1);
		UT2Coordinate::UnitToQD(br, mTowerDoc->GetZoomLevel(), 1);

		T2TowerMainView *mainView = mTowerDoc->GetMainView();
		mainView->FocusDraw();
		mainView->LocalToPortPoint(tl);
		mainView->LocalToPortPoint(br);

		Rect r;
		::Pt2Rect(tl, br, &r);
		UT2Balloon::DoBalloon(mTowerDoc, r, str, -1);
		if (mBalloon)
			mBalloon->SetResumeArea(rect);
	}
}

void T2TowerMessage::InfoDialogMessage(const LString &str, PaneIDT paneID, Int16 timeout) {
	LWindow *window = UDesktop::FetchTopModal();
	if (window) {
		StColorState state;
		RGBColor foreClr, backClr;
		window->GetForeAndBackColors(&foreClr, &backClr);
		::RGBForeColor(&foreClr);
		::RGBBackColor(&backClr);

		LPane *pane = (LPane *) window->FindPaneByID(paneID);
		if (pane) {
			LStr255 saveText;
			if (timeout != -1)
				pane->GetDescriptor(saveText);
			pane->SetDescriptor(str);
			pane->FocusDraw();

			Rect rect;
			pane->CalcLocalFrameRect(rect);
			::EraseRect(&rect);
			pane->Draw(0);

			if (timeout != -1) {
				UInt32 endAt = ::TickCount() + timeout;
				do {} while (endAt > ::TickCount());
				pane->SetDescriptor(saveText);
				pane->FocusDraw();
				::EraseRect(&rect);
				pane->Draw(0);
			}
		}
	}
}

void T2TowerMessage::AleatMessage(const LString &str, ResIDT id) {
	Int16 saveResFile = ::CurResFile();
	::UseResFile(mCurResFile);
	::ParamText(str, 0, 0, 0);

	switch (id) {
		case 0:
			::StopAlert(6000, 0);
			break;
		case 1:
			::NoteAlert(6000, 0);
			break;
		case 2:
			::CautionAlert(6000, 0);
			break;
		default:
			::Alert(6000, 0);
	}

	::UseResFile(saveResFile);
}

void T2TowerMessage::SpendTime(const EventRecord &event) {
	if (mArray) {
		Boolean found = false;

		while (mArray->GetCount() != 0) {
			found = false;
			InfoBarMsgItem *item;
			if (mArray->FetchItemAt(LArray::index_First, &item)) {
				if (item->m110 == 0)
					SetInfoBarMsg(item);
				if (item->m10C != -1) {
					if (item->m110 >= ::TickCount())
						break;
				}
				mArray->RemoveItemsAt(1, LArray::index_First);
				found = item->m10C != -1;
				delete item;
			}
		}
		if (found)
			SetInfoBarMsg(0);
	}

	UT2Balloon::Pick(mTowerDoc, false);
}

LWindow *T2TowerMessage::FindFloatingWindow(Int16 var) {
	LWindow *window;
	WindowPtr macWindow = ::FrontWindow();

	while ((window = LWindow::FetchWindowObject(macWindow)) != 0) {
		if (window->HasAttribute(windAttr_Floating) && IsWindowVisible(macWindow) && window->GetPaneID() == var)
			break;
		macWindow = GetNextWindow(macWindow);
	}

	return window;
}

InfoBarMsgItem::InfoBarMsgItem(const LString &str, Int16 a, Int16 b, T2PluginSound *pluginSound, CFilePlugin *filePlugin) {
	mString = str;
	m10C = a;
	m114 = b;
	mPluginSound = pluginSound;
	mFilePlugin = filePlugin;
	m110 = 0;
}

InfoBarMsgItem::~InfoBarMsgItem() {
}
