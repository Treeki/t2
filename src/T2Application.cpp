#include "T2Application.h"

#include "C3DBorderAttachment.h"
#include "CCaptionListener.h"
#include "CGDevice.h"
#include "CGDeviceIterator.h"
#include "CPicHandleView.h"
#include "CPieChartView.h"
#include "CPiledMultiBarChartView.h"
#include "CRepeater.h"
#include "CScrollerBorderAttachment.h"
#include "CScrollerNoBorder.h"
#include "CSpinButtons.h"
#include "CToggleButtonDisabled.h"
#include "CTransparentPicture.h"
#include "StVBLAnmCursor.h"
#include "T2ActiveScroller.h"
#include "T2AboutPluginDialogBox.h"
#include "T2GlobalData.h"
#include "T2PluginTable.h"
#include "T2SoundPlayer.h"
#include "T23DCaption.h"
#include "UPluginLoader.h"

#include <Dialogs.h>
#include <Gestalt.h>
#include <LowMem.h>
#include <LActiveScroller.h>
#include <LArrayIterator.h>
#include <LString.h>
#include <LTextEdit.h>
#include <MacMemory.h>
#include <Movies.h>
#include <Palettes.h>
#include <PPobClasses.h>
#include <Processes.h>
#include <UDesktop.h>
#include <UDrawingState.h>
#include <UEnvironment.h>
#include <UGALibRegistry.h>
#include <UModalDialogs.h>
#include <UReanimator.h>
#include <URegistrar.h>

T2Application *T2Application::sT2Application;

Boolean PluginTypeCheckFunc(CInfoPBPtr info, void *stuff) {
	UInt32 *array = (UInt32 *) stuff;
	Boolean ok = false;
	int index = 0;

	while (!ok && index < array[0]) {
		ok = info->hFileInfo.ioFlFndrInfo.fdType == array[index + 1];
	}

	return ok;
}

CFilePlugin *MakePluginFunc(UInt32 id, const FSSpec &spec) {
	// TODO needs lots of stuff
}

T2Application::T2Application() {
	//TODO
	//UEnvironment::InitEnvironment();

	int osVersion = 100; // UEnvironment::GetOSVersion();
	if (osVersion < 0x750) {
		LStr255 str = "Yoot's Tower requires MacOS 7.5 or later.";
		::ParamText(str, "\p", "\p", "\p");
		::StopAlert(6000, NULL);
		::ExitToShell();
	}

	long qtVersion;
	if (::Gestalt(gestaltQuickTimeVersion, &qtVersion) != 0 || EnterMovies == NULL) {
		LStr255 str = "Yoot's Tower requires QuickTime.";
		::ParamText(str, "\p", "\p", "\p");
		::StopAlert(6000, NULL);
		::ExitToShell();
	}

	sT2Application = this;

	mSoundPlayer = NULL;
	m9C = 1;
	m84 = 0;
	m85 = 0;

	EnterMovies();

	mInternationalExchanger = new CInternationalExchanger;
	Assert_(mInternationalExchanger != 0);

	mControlWindow = 0;
	mToolWindow = 0;
	mMsgWindow = 0;
	mCalendarWindow = 0;
	mGlobalData = 0;

	mSoundPlayer = new T2SoundPlayer;
	ThrowIfNULL_(mSoundPlayer);

	m90 = 0;
	m94 = 0;
	mGraphicsDeviceArray = NULL;

	RegisterAllPPClasses();
	TRegistrar<LActiveScroller>::Register();
	RegisterAllGAClasses();
	RegisterAllT2Classes();
}

void T2Application::RegisterAllGAClasses() {
	RegisterGALibraryClasses();
	//TRegistrar<LOffscreenView>::Register();
	TRegistrar<LColorEraseAttachment>::Register();
	TRegistrar<LEraseAttachment>::Register();
	TRegistrar<LBorderAttachment>::Register();
	//TRegistrar<LCmdBevelButton>::Register();
	TRegistrar<C3DBorderAttachment>::Register();
}

void T2Application::RegisterAllT2Classes() {
	TRegistrar<CTransparentPicture>::Register();
                    /* T2TM */
                    /* T2fw */
                    /* T2Tw */
	TRegistrar<T2ActiveScroller>::Register();
                    /* T2pd */
                    /* T2it */
                    /* T2pi */
	TRegistrar<T2PluginTable>::Register();
                    /* T2sp */
                    /* T2DL */
                    /* T2GI */
                    /* T2MM */
                    /* PPTb */
                    /* T2PI */
                    /* T2ss */
                    /* T2ev */
                    /* MoTb */
                    /* HeTb */
                    /* MtTb */
                    /* GrTb */
                    /* T2Sd */
                    /* T2OI */
                    /* AdTb */
                    /* Merc */
                    /* MerF */
                    /* MoPn */
                    /* T2PB */
                    /* T2SG */
                    /* T2HG */
                    /* T2SD */
                    /* NmTb */
                    /* T2RF */
                    /* T2tw */
                    /* T2gt */
                    /* T2tt */
                    /* T2pl */
                    /* T2ct */
                    /* PBtn */
                    /* T2cw */
                    /* T2BT */
                    /* T2cT */
                    /* T2sl */
                    /* T2si */
                    /* T2ms */
                    /* T2Cw */
                    /* T2cV */
                    /* T2GF */
	TRegistrar<CPieChartView>::Register();
	TRegistrar<CPiledMultiBarChartView>::Register();
                    /* T2DB */
                    /* T2sD */
                    /* CsTb */
	TRegistrar<T23DCaption>::Register();
                    /* CEdw */
                    /* CEPc */
                    /* T2St */
                    /* T2FN */
                    /* T2EC */
                    /* T2ES */
	TRegistrar<CSpinButtons>::Register();
                    /* T2tc */
	TRegistrar<CScrollerNoBorder>::Register();
	TRegistrar<CScrollerBorderAttachment>::Register();
	TRegistrar<CToggleButtonDisabled>::Register();
                    /* T2sb */
	TRegistrar<CRepeater>::Register();
                    /* Dt2t */
                    /* TSpd */
                    /* T2fi */
                    /* DFIV */
                    /* DefT */
                    /* TSDf */
                    /* DefV */
                    /* DbFI */
                    /* CETb */
                    /* PLTb */
                    /* PATb */
                    /* PDbg */
                    /* T2PE */
                    /* CPRD */
                    /* capL */
                    /* TstD */
                    /* T2SV */
                    /* FTGD */
                    /* TGPn */
	TRegistrar<T2AboutPluginDialogBox>::Register();
                    /* PIfT */
                    /* T2tx */
	TRegistrar<CPicHandleView>::Register();
}

T2Application::~T2Application() {
	delete mSoundPlayer;
	delete mControlWindow;
	delete mToolWindow;
	delete mMsgWindow;
	delete mCalendarWindow;

	if (mGlobalData != NULL) {
		delete mGlobalData;
		mGlobalData = NULL;
	}

	UPluginLoader::DisposeAllFilePlugin();

	if (mGraphicsDeviceArray != NULL) {
		LArrayIterator iter(*mGraphicsDeviceArray);
		CGDevice *element;
		while (iter.Next(&element)) {
			delete element;
		}
		delete mGraphicsDeviceArray;
	}
}

void T2Application::Initialize() {
	mGlobalData = new T2GlobalData;

	// there's some missing code here, cracked binary maybe??

	short vRefNum;
	long dirID;
	if (AdjustScreenDepth() && ::HGetVol(NULL, &vRefNum, &dirID) == 0) {
		LStr255 name1(1000, 4);
		QHdrPtr hdr = ::GetVCBQHdr();

		for (VCBPtr elem = (VCBPtr) hdr->qHead; elem != NULL; elem = (VCBPtr) elem->qLink) {
			if (LString::CompareBytes(&elem->vcbVN[1], &name1[1], elem->vcbVN[0], name1[0]) == 0) {
				m84 = true;
				break;
			}
		}

		LStr255 name2(1000, 5);
		CInfoPBRec pb;
		pb.dirInfo.ioNamePtr = name2;
		pb.dirInfo.ioVRefNum = vRefNum;
		pb.dirInfo.ioFDirIndex = 0;
		pb.dirInfo.ioDrDirID = dirID;
		if (::PBGetCatInfoSync(&pb) == 0 && pb.dirInfo.ioFlAttrib & ioDirMask)
			m85 = true;

		DisplayLogos();
		m9C = 0;
	}
}

void T2Application::StartUp() {
	if (m9C) {
		ObeyCommand(10, NULL);
	} else {
		ObeyCommand(7999, NULL);
	}
}

void T2Application::LoadPlugin() {
	LStr255 str1(1000, 1);
	LStr255 str2(1000, 2);

	UInt32 *buffer = (UInt32 *) ::NewPtr(0x24);
	ThrowIfMemError_();

	buffer[0] = 7;
	buffer[1] = 'WdPI';
	buffer[2] = 'TnPI';
	buffer[3] = 'MvPI';
	buffer[4] = 'OoPI';
	buffer[5] = 'MoPI';
	buffer[6] = 'HePI';
	buffer[7] = 'AdPI';

	if (UPluginLoader::InitPluginLoader(str1, str2) == false) {
		ObeyCommand(cmd_Quit, NULL);
	} else {
		UPluginLoader::MakeAllFilePlugin(PluginTypeCheckFunc, buffer, MakePluginFunc);
		::DisposePtr((Ptr) buffer);
	}
}

void T2Application::AdjustCursor(const EventRecord &inMacEvent) {
	if (StVBLAnmCursor::sCurrentCursor == NULL) {
		LEventDispatcher::AdjustCursor(inMacEvent);
	}
}

void T2Application::DoQuit(Int32 inSaveOption) {
	LApplication::DoQuit(inSaveOption);
}

void T2Application::OpenDocument(FSSpec *inMacFSSpec) {
	// BIGGEST TODO
}

LModelObject *T2Application::MakeNewDocument() {
	LWindow::CreateWindow(1000, this);
	return NULL;
}

void T2Application::ChooseDocument() {
	UDesktop::Deactivate();

	OSType types[4] = { 'T2CE', 'T2Dc', 0, 0 };
	StandardFileReply reply;
	::StandardGetFile(NULL, 2, types, &reply);

	UDesktop::Activate();

	if (reply.sfGood) {
		SendAEOpenDoc(reply.sfFile);
	} else {
		ObeyCommand(7999, NULL);
	}
}

void T2Application::PrintDocument(FSSpec *inMacFSSpec) {
}

Boolean T2Application::ObeyCommand(CommandT inCommand, void *ioParam) {
	LWindow *wnd;
	LWindow *thePrefDialog;
	LWindow *theFloorInfoWindow;

	switch (inCommand) {
		case 7999:
			wnd = LWindow::CreateWindow(1001, this);
			if (wnd != NULL) {
				// TODO what LListener subclass is 1001?
				//UReanimator::LinkListenerToControls(wnd, wnd, 1001);
			}
			return true;
		case 1091:
			AboutPlugin();
			return true;
		case 1001:
			if (mMsgWindow->IsVisible()) {
				mMsgWindow->Hide();
			} else {
				mMsgWindow->Show();
			}
			return true;
		case 1002:
			if (mToolWindow->IsVisible()) {
				mToolWindow->Hide();
			} else {
				mToolWindow->Show();
			}
			return true;
		case 1003:
			if (mControlWindow->IsVisible()) {
				mControlWindow->Hide();
			} else {
				mControlWindow->Show();
			}
			return true;
		case 1004:
			if (mCalendarWindow->IsVisible() && ioParam == NULL) {
				mCalendarWindow->Hide();
			} else {
				// TODO T2CalendarWindow stuff
			}
			return true;
		case 1093:
			thePrefDialog = LWindow::CreateWindow(4000, this);
			Assert_(thePrefDialog != 0);
			return true;
		case 10003:
			theFloorInfoWindow = LWindow::CreateWindow(10003, this);
			Assert_(theFloorInfoWindow != 0);
			theFloorInfoWindow->Show();
			return true;
		default:
			return LDocApplication::ObeyCommand(inCommand, ioParam);
	}
}

void T2Application::FindCommandStatus(CommandT inCommand, Boolean &outEnabled, Boolean &outUsesMark, Char16 &outMark, Str255 outName) {
	switch (inCommand) {
		case cmd_New:
		case cmd_Open:
		case cmd_Close:
			outEnabled = false;
			break;
		case 1091:
			outEnabled = true;
			break;
		case 1001:
			if (mMsgWindow && /* TODO */ false) {
				outEnabled = true;
				if (mMsgWindow->IsVisible())
					::GetIndString(outName, 130, 1);
				else
					::GetIndString(outName, 130, 2);
			}
			break;
		case 1002:
			if (mToolWindow && /* TODO */ false) {
				outEnabled = true;
				if (mToolWindow->IsVisible())
					::GetIndString(outName, 131, 1);
				else
					::GetIndString(outName, 131, 2);
			}
			break;
		case 1003:
			if (mControlWindow && /* TODO */ false) {
				outEnabled = true;
				if (mControlWindow->IsVisible())
					::GetIndString(outName, 132, 1);
				else
					::GetIndString(outName, 132, 2);
			}
			break;
		case 1093:
			outEnabled = true;
			break;
		case 5003:
			// TODO TowerDoc
			break;
		case 10003:
			// TODO TowerDoc
			break;
		default:
			LDocApplication::FindCommandStatus(inCommand, outEnabled, outUsesMark, outMark, outName);
	}
}

void T2Application::DispatchEvent(const EventRecord &inMacEvent) {
	LEventDispatcher::DispatchEvent(inMacEvent);
	if (m9D) {
		m9D = false;
		LCommander::SetUpdateCommandStatus(true);
	}
}

void T2Application::NewTowerDocument(T2WorldPlugin *worldPlugin) {
	// TODO new TowerDoc
}

void T2Application::ProcessNextEvent() {
	if (m90 <= 0 || ::TickCount() > m94) {
		// TODO TowerDoc
	} else {
		m94 = m90 + ::TickCount();
		LApplication::ProcessNextEvent();
	}
}

void T2Application::EventResume(const EventRecord &inMacEvent) {
	SetSleepTime(0);
	LEventDispatcher::EventResume(inMacEvent);
}

void T2Application::EventSuspend(const EventRecord &inMacEvent) {
	::RestoreDeviceClut(NULL);
	SetSleepTime(6);
	LEventDispatcher::EventSuspend(inMacEvent);
}

void T2Application::OpeningSound() {
	// TODO T2SoundPlayer
}

void T2Application::DisplayLogos() {
	WindowRef window = ::GetNewCWindow(8003, 0, (WindowRef) -1);
	if (window == NULL)
		return;

	::MoveWindow(window, 0, 0, false);
	::SizeWindow(
		window,
		UQDGlobals::GetQDGlobals()->screenBits.bounds.right,
		UQDGlobals::GetQDGlobals()->screenBits.bounds.bottom,
		false);

	SInt16 menuBarHeight = ::LMGetMBarHeight();
	::LMSetMBarHeight(0);
	::ShowWindow(window);
	::SetPort(window);

	Rect rect;
	::SetRect(&rect,
		UQDGlobals::GetQDGlobals()->screenBits.bounds.top,
		UQDGlobals::GetQDGlobals()->screenBits.bounds.left,
		UQDGlobals::GetQDGlobals()->screenBits.bounds.right,
		UQDGlobals::GetQDGlobals()->screenBits.bounds.bottom);

	RgnHandle rgn = ::NewRgn();
	::RectRgn(rgn, &rect);
	::UnionRgn(GetWindowPort(window)->visRgn, rgn, GetWindowPort(window)->visRgn);
	::DisposeRgn(rgn);

	::FillRect(&rect, &UQDGlobals::GetQDGlobals()->black);

	PicHandle pic = ::GetPicture(8001);
	Rect picRect = (*pic)->picFrame;
	AdjustDestRect(pic, &picRect);
	::DrawPicture(pic, &picRect);
	::ReleaseResource((Handle) pic);

	UInt32 startTicks = ::TickCount();
	while (!::Button()) {
		if (::TickCount() >= (startTicks + 60))
			break;
	}

	pic = ::GetPicture(8002);
	picRect = (*pic)->picFrame;
	AdjustDestRect(pic, &picRect);
	::DrawPicture(pic, &picRect);
	::ReleaseResource((Handle) pic);

	OpeningSound();
	unsigned long finalTicks;
	::Delay(30, &finalTicks);

	SetupTowerEnvironment();

	startTicks = ::TickCount();
	while (!::Button()) {
		if (::TickCount() >= (startTicks + 60))
			break;
	}

	::LMSetMBarHeight(menuBarHeight);
	::DrawMenuBar();
	::HideWindow(window);
	::DisposeWindow(window);
	::RestoreDeviceClut(NULL);
}

void T2Application::AdjustDestRect(PicHandle pic, Rect *rect) {
	short screenWidth = UQDGlobals::GetQDGlobals()->screenBits.bounds.right;
	short screenHeight = UQDGlobals::GetQDGlobals()->screenBits.bounds.bottom;
	short picWidth = (*pic)->picFrame.right - (*pic)->picFrame.left;
	short picHeight = (*pic)->picFrame.bottom - (*pic)->picFrame.top;
	short offsetX = (screenWidth / 2) - (picWidth / 2);
	short offsetY = (screenHeight / 2) - (picHeight / 2);

	Rect newRect;
	newRect.top = rect->top + offsetY;
	newRect.bottom = rect->bottom + offsetY;
	newRect.left = rect->left + offsetX;
	newRect.right = rect->right + offsetX;

	*rect = newRect;
}

Boolean T2Application::AdjustScreenDepth() {
	mGraphicsDeviceArray = new LArray;

	CGDeviceIterator deviceIter;
	int count1 = 0;
	int count2 = 0;
	GDHandle handle;

	while (deviceIter.Next(handle)) {
		CGDevice *device = new CGDevice(handle);
		mGraphicsDeviceArray->InsertItemsAt(1, LArray::index_Last, &device);

		if (device->GetDepth() != 8 || device->IsColor() == false)
			count1++;
		if (device->HasDepth(8, 1))
			count2++;
	}

	if (count1 != 0 || count2 != 0) {
		UDesktop::Deactivate();
		short response = ::Alert(1003, NULL);
		UDesktop::Activate();
		if (response == 2)
			return false;
	}

	LArrayIterator arrayIter(*mGraphicsDeviceArray);
	CGDevice *device;
	while (arrayIter.Next(&device)) {
		device->SetDepth(8, true);
	}

	::DrawMenuBar();
	return true;
}

Boolean T2Application::SetupTowerEnvironment() {
	LoadPlugin();

	mControlWindow = LWindow::CreateWindow(2500, this);
	Assert_(mControlWindow != 0);

	mToolWindow = LWindow::CreateWindow(2000, this);
	Assert_(mControlWindow != 0);

	mMsgWindow = LWindow::CreateWindow(3000, this);
	Assert_(mMsgWindow != 0);

	mCalendarWindow = LWindow::CreateWindow(3100, this);
	Assert_(mCalendarWindow != 0);

	return true;
}

void T2Application::ShowAboutBox() {
	LWindow *topModal = UDesktop::FetchTopModal();
	if (topModal != NULL && topModal->GetPaneID() == 1300)
		return;

	StDialogHandler dlog(1300, this);
	LDialogBox *theDialog;
	Assert_((theDialog = (LDialogBox*) dlog.GetDialog()) != 0);

	LPane *theSerial = theDialog->FindPaneByID('serl');
	Assert_(theSerial != 0);

	LStr255 serial;
	mGlobalData->GetSerialString(serial);
	theSerial->SetDescriptor(serial);

	LTextEdit *theTextEdit = (LTextEdit *) theDialog->FindPaneByID('text');
	Assert_(theTextEdit != 0);

	SDimension32 imageSize;
	SDimension16 frameSize;

	theTextEdit->GetImageSize(imageSize);
	theTextEdit->GetFrameSize(frameSize);

	int counter = 0;
	theTextEdit->ScrollImageTo(0, -frameSize.height, true);

	while (dlog.DoDialog() != msg_OK) {
		theTextEdit->ScrollImageBy(0, 1, true);
		counter++;
		if (imageSize.height + frameSize.height < counter) {
			counter = 0;
			theTextEdit->ScrollImageTo(0, 1 - frameSize.height, true);
		}
	}
}

void T2Application::AboutPlugin() {
	StDialogHandler dlog(1400, this);
	T2AboutPluginDialogBox *theDialog;
	Assert_((theDialog = (T2AboutPluginDialogBox*) dlog.GetDialog()) != 0);

	T2PluginTable *thePluginTable = (T2PluginTable *) theDialog->FindPaneByID(12);
	Assert_(thePluginTable != 0);

	thePluginTable->Add(UPluginLoader::GetFilePluginList('WdPI'));
	thePluginTable->Add(UPluginLoader::GetFilePluginList('TnPI'));
	thePluginTable->Add(UPluginLoader::GetFilePluginList('MvPI'));
	thePluginTable->Add(UPluginLoader::GetFilePluginList('MoPI'));
	thePluginTable->Add(UPluginLoader::GetFilePluginList('HePI'));
	thePluginTable->Add(UPluginLoader::GetFilePluginList('OoPI'));
	thePluginTable->Add(UPluginLoader::GetFilePluginList('AdPI'));
	thePluginTable->AddListener(theDialog);

	TableCellT cell;
	cell.row = 1;
	cell.col = 1;
	thePluginTable->SelectCell(cell);

	while (dlog.DoDialog() != msg_OK) {
	}
}

int T2Application::GetMoviePath(short id, LStr255 &string) {
	if (id == 1) {
		if (m85) {
			LStr255 name(1000, 5);
			string = "\p:";
			string.Append(name);
			string.Append("\p:");
		} else if (m84) {
			string.Assign(1000, 4);
			string.Append("\p:");
			LStr255 name(1000, 5);
			string.Append(name);
			string.Append("\p:");
			id = 2;
		} else {
			id = 0;
		}
	} else if (id == 2) {
		if (m84) {
			string.Assign(1000, 4);
			string.Append("\p:");
			LStr255 name(1000, 5);
			string.Append(name);
			string.Append("\p:");
		} else if (m85) {
			LStr255 name(1000, 5);
			string = ":";
			string.Append(name);
			string.Append("\p:");
			id = 1;
		} else {
			id = 0;
		}
	}

	return id;
}
