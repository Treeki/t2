#pragma once

#include <LDocApplication.h>
#include <LString.h>
#include <LWindow.h>
#include "CInternationalExchanger.h"

class T2GlobalData;
class T2SoundPlayer;
class T2WorldPlugin;

class T2Application : public LDocApplication {
public:
	T2Application();
	~T2Application();

	static T2Application *sT2Application;

	void RegisterAllGAClasses();
	void RegisterAllT2Classes();
	void Initialize();
	void StartUp();
	void LoadPlugin();
	void AdjustCursor(const EventRecord &inMacEvent);
	void DoQuit(Int32 inSaveOption);
	void OpenDocument(FSSpec *inMacFSSpec);
	LModelObject *MakeNewDocument();
	void ChooseDocument();
	void PrintDocument(FSSpec *inMacFSSpec);
	Boolean ObeyCommand(CommandT inCommand, void *ioParam);
	void FindCommandStatus(CommandT inCommand, Boolean &outEnabled, Boolean &outUsesMark, Char16 &outMark, Str255 outName);
	void DispatchEvent(const EventRecord &inMacEvent);
	void NewTowerDocument(T2WorldPlugin *worldPlugin);
	void ProcessNextEvent();
	void EventResume(const EventRecord &inMacEvent);
	void EventSuspend(const EventRecord &inMacEvent);
	void OpeningSound();
	void DisplayLogos();
	void AdjustDestRect(PicHandle pic, Rect *rect);
	Boolean AdjustScreenDepth();
	Boolean SetupTowerEnvironment();
	void ShowAboutBox();
	void AboutPlugin();
	int GetMoviePath(short id, LStr255 &string);

	CInternationalExchanger *mInternationalExchanger;
	LWindow *mControlWindow;
	LWindow *mToolWindow;
	LWindow *mMsgWindow;
	LWindow *mCalendarWindow;
	Byte m84, m85;
	T2GlobalData *mGlobalData;
	T2SoundPlayer *mSoundPlayer;
	UInt32 m90, m94;
	LArray *mGraphicsDeviceArray;
	Byte m9C;
	Boolean m9D;
};
