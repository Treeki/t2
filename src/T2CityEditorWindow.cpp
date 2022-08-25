#include "T2Application.h"
#include "T2CityEditorPicture.h"
#include "T2CityEditorWindow.h"
#include "T2CitySelectTable.h"
#include "UPluginLoader.h"

#include <PP_Messages.h>

T2CityEditorWindow::T2CityEditorWindow(LStream *inStream)
	: LDialogBox(inStream)
{
	mCitySelectTable = 0;
	mSelectedWorld = 0;
}

void T2CityEditorWindow::FindCommandStatus(CommandT inCommand, Boolean &outEnabled, Boolean &outUsesMark, Char16 &outMark, Str255 outName) {
	switch (inCommand) {
		case cmd_New:
		case cmd_Open:
			outEnabled = false;
			break;
		default:
			LWindow::FindCommandStatus(inCommand, outEnabled, outUsesMark, outMark, outName);
	}
}

void T2CityEditorWindow::FinishCreateSelf() {
	LDialogBox::FinishCreateSelf();

	mCitySelectTable = (T2CitySelectTable *) FindPaneByID('slct');
	if (mCitySelectTable) {
		CFilePluginList *list = UPluginLoader::GetFilePluginList('WdPI');
		if (list) {
			mCitySelectTable->Add(list);
			mCityCount = list->GetItemCount();
		}

		mCitySelectTable->AddListener(this);
	}

	mLeftPane = FindPaneByID('left');
	// ADD LISTENER
	mRigtPane = FindPaneByID('rigt');
	// ADD LISTENER

	mPictPane = (T2CityEditorPicture *) FindPaneByID('pict');
	mNamePane = FindPaneByID('name');
	mFundPane = FindPaneByID('fund');
	mHitePane = FindPaneByID('hite');
	mWithPane = FindPaneByID('with');
	mDescPane = FindPaneByID('desc');

	// TABLE TODO
}

void T2CityEditorWindow::ListenToMessage(MessageT message, void *param) {
	switch (message) {
		case 'left':
			// hurf durf
			break;
		case 'rigt':
			// hurf durf
			break;
		case 'clik':
			ChangeSelection((T2WorldPlugin *) param);
			break;
		case msg_OK:
			if (mSelectedWorld) {
				T2Application *app = dynamic_cast<T2Application *>(GetSuperCommander());
				if (app)
					app->NewTowerDocument(mSelectedWorld);
				DoClose();
			}
			break;
		case msg_Cancel:
			AttemptClose();
			break;
	}
}

void T2CityEditorWindow::ChangeSelection(T2WorldPlugin *plugin) {
	if (plugin && plugin != mSelectedWorld) {
		mSelectedWorld = plugin;
		DisplaySelection();
		AdjustButtons();
	}
}

void T2CityEditorWindow::AdjustButtons() {
	TableCellT cell;
	UInt32 rows, cols;
	mCitySelectTable->GetSelectedCell(cell);
	mCitySelectTable->GetTableSize(rows, cols);

	if (cell.col == 1)
		mLeftPane->Disable();
	else
		mLeftPane->Enable();

	if (cell.col == cols)
		mRigtPane->Disable();
	else
		mRigtPane->Enable();

	LPane *btn = FindPaneByID('OK  ');
	if (btn) {
		if (mSelectedWorld)
			btn->Enable();
		else
			btn->Disable();
	}
}

void T2CityEditorWindow::DisplaySelection() {
	// TODO
}
