#include "T2FloatingWindow.h"
#include "T2TowerDoc.h"
#include <MacWindows.h>
#include <UException.h>

T2FloatingWindow::T2FloatingWindow(LStream *inStream)
	: LWindow(inStream)
{
	mT2TowerDoc = 0;
	mShowHideCommand = 0;
}

void T2FloatingWindow::SetShowHideCommand(CommandT command) {
	mShowHideCommand = command;
}

void T2FloatingWindow::ClickInGoAway(const EventRecord &event) {
	if (::TrackGoAway(mMacWindowP, event.where)) {
		ObeyCommand(mShowHideCommand, 0);
		SetUpdateCommandStatus(true);
	}
}

void T2FloatingWindow::CloseDocument(T2TowerDoc *doc) {
	if (mT2TowerDoc == doc) {
		mT2TowerDoc = NULL;
		DocumentSet();
	}
}

void T2FloatingWindow::TowerWindowActivated(T2TowerDoc *inDocument, PaletteHandle pal) {
	#line 91
	Assert_(inDocument != 0);

	mT2TowerDoc = inDocument;
	DocumentSet();
	::SetPalette(mMacWindowP, pal, true);

	if (mT2TowerDoc->IsFloatingInitialVisible(mShowHideCommand))
		Show();
}

void T2FloatingWindow::DocumentSet() {
}
