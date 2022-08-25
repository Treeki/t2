#include "T2AboutPluginDialogBox.h"
#include "CFilePlugin.h"
#include "CPicHandleView.h"
#include <LFile.h>
#include <PP_Messages.h>

T2AboutPluginDialogBox *T2AboutPluginDialogBox::CreateT2AboutPluginDialogBoxStream(LStream *inStream) {
	return new T2AboutPluginDialogBox(inStream);
}

T2AboutPluginDialogBox::T2AboutPluginDialogBox(LStream *inStream)
	: LDialogBox(inStream)
{
	m138 = 0;
}

T2AboutPluginDialogBox::~T2AboutPluginDialogBox() {
}

void T2AboutPluginDialogBox::FinishCreateSelf() {
	LDialogBox::FinishCreateSelf();
}

void T2AboutPluginDialogBox::ListenToMessage(MessageT inMessage, void *ioParam) {
	CFilePlugin *plugin;
	LFile *file;
	PicHandle pic;
	CPicHandleView *view;

	switch (inMessage) {
		case msg_OK:
		case msg_Cancel:
			DoClose();
			break;
		case 1400:
			plugin = (CFilePlugin *) ioParam;
			if (plugin != NULL) {
				file = plugin->mFile;
				if (file != NULL) {
					pic = 0;
					try {
						file->OpenResourceFork(1);
						pic = (PicHandle) ::Get1Resource('PICT', 900);
						if (pic)
							::DetachResource((Handle) pic);
						file->CloseResourceFork();
					} catch (ExceptionCode code) {

					}
					if (pic) {
						view = (CPicHandleView *) FindPaneByID('pict');
						if (view) {
							view->SetPicHandle(pic);
							view->Refresh();
						}
					}
				}
			}
			break;
		default:
			LDialogBox::ListenToMessage(inMessage, ioParam);
	}
}
