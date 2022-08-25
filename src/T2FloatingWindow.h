#pragma once

#include <LWindow.h>
#include <Palettes.h>

class T2TowerDoc;

class T2FloatingWindow : public LWindow {
public:
	T2FloatingWindow(LStream *inStream);
	void SetShowHideCommand(CommandT command);
	void ClickInGoAway(const EventRecord &event);
	void CloseDocument(T2TowerDoc *doc);
	void TowerWindowActivated(T2TowerDoc *inDocument, PaletteHandle pal);

	virtual void DocumentSet();

protected:
	T2TowerDoc *mT2TowerDoc;
	CommandT mShowHideCommand;
};
