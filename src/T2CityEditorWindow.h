#pragma once

#include <LDialogBox.h>

class T2CityEditorPicture;
class T2CitySelectTable;
class T2WorldPlugin;

class T2CityEditorWindow : public LDialogBox {
public:
	T2CityEditorWindow(LStream *inStream);
	void FindCommandStatus(CommandT inCommand, Boolean &outEnabled, Boolean &outUsesMark, Char16 &outMark, Str255 outName);
	void FinishCreateSelf();
	void ListenToMessage(MessageT message, void *param);
	void ChangeSelection(T2WorldPlugin *plugin);
	void AdjustButtons();
	void DisplaySelection();

protected:
	T2WorldPlugin *mSelectedWorld;
	T2CitySelectTable *mCitySelectTable;
	T2CityEditorPicture *mPictPane;
	LPane *mNamePane;
	LPane *mFundPane;
	LPane *mHitePane;
	LPane *mWithPane;
	LPane *mDescPane;
	LPane *mLeftPane;
	LPane *mRigtPane;
	Int16 mCityCount;
};

