#include "T2DateTime.h"
#include "T2Settlement.h"
#include "T2SettlementDialog.h"
#include "T2TowerDoc.h"
#include "T2WorldDef.h"
#include "T2WorldPlugin.h"
#include "UT2Utils.h"

#include <LCaption.h>

T2SettlementDialog::T2SettlementDialog(LStream *inStream)
	: T2StdDialog(inStream)
{
}

T2SettlementDialog::~T2SettlementDialog() {
}

void T2SettlementDialog::FinishCreateSelf() {
	T2TowerDoc *theDoc = GetDocument();
	if (theDoc)
		theDoc->mWorldPlugin->SettlementSetup(theDoc, this);
	LDialogBox::FinishCreateSelf();
}

void T2SettlementDialog::StandardSetup() {
	T2TowerDoc *theDocument = GetDocument();
	#line 88
	Assert_(theDocument != 0);

	T2WorldDef *theWorldDef = theDocument->mWorldDef;
	#line 90
	Assert_(theWorldDef != 0);

	LStr255 str;
	T2DateTime *dateTime = theDocument->someDateTime; // r20
	UInt16 r21 = (dateTime->GetDay() / 3) + 1; // r21
	T2Settlement *settlement = theDocument->mSettlement; // r22

	LCaption *theCaption = (LCaption *) FindPaneByID(2); // r26
	#line 100
	Assert_(theCaption != 0);
	theCaption->SetDescriptor(LStr255((Int32) dateTime->GetYear()));

	theCaption = (LCaption *) FindPaneByID(3); // r26
	#line 105
	Assert_(theCaption != 0);
	theCaption->SetDescriptor(LStr255((Int32) r21));

	theCaption = (LCaption *) FindPaneByID(4); // r26
	#line 110
	Assert_(theCaption != 0);
	theCaption->SetDescriptor(LStr255((Int32) ((r21 - 1) * 3 + 1)));

	theCaption = (LCaption *) FindPaneByID(5); // r26
	#line 115
	Assert_(theCaption != 0);
	theCaption->SetDescriptor(LStr255((Int32) (r21 * 3)));

	theCaption = (LCaption *) FindPaneByID(6); // r26
	#line 120
	Assert_(theCaption != 0);
	UT2Utils::GetMonetaryString(theWorldDef->ExchangeMoney(-settlement->GetTotalSettlement(3)), str);
	theCaption->SetDescriptor(str);

	theCaption = (LCaption *) FindPaneByID(7); // r26
	#line 127
	Assert_(theCaption != 0);
	UT2Utils::GetMonetaryString(theWorldDef->ExchangeMoney(settlement->GetTotalSettlement(0)), str);
	theCaption->SetDescriptor(str);

	theCaption = (LCaption *) FindPaneByID(8); // r26
	#line 134
	Assert_(theCaption != 0);
	UT2Utils::GetMonetaryString(theWorldDef->ExchangeMoney(-settlement->GetTotalSettlement(5)), str);
	theCaption->SetDescriptor(str);

	theCaption = (LCaption *) FindPaneByID(9); // r26
	#line 141
	Assert_(theCaption != 0);
	UT2Utils::GetMonetaryString(theWorldDef->ExchangeMoney(-settlement->GetTotalSettlement(6)), str);
	theCaption->SetDescriptor(str);

	theCaption = (LCaption *) FindPaneByID(10); // r26
	#line 148
	Assert_(theCaption != 0);
	UT2Utils::GetMonetaryString(theWorldDef->ExchangeMoney(settlement->GetTotalSettlement(1)), str);
	theCaption->SetDescriptor(str);

	theCaption = (LCaption *) FindPaneByID(11); // r26
	#line 155
	Assert_(theCaption != 0);
	UT2Utils::GetMonetaryString(theWorldDef->ExchangeMoney(settlement->GetPreviousFunds()), str);
	theCaption->SetDescriptor(str);

	theCaption = (LCaption *) FindPaneByID(12); // r26
	#line 162
	Assert_(theCaption != 0);
	UT2Utils::GetMonetaryString(theWorldDef->ExchangeMoney(settlement->GetCurrentFunds()), str);
	theCaption->SetDescriptor(str);
}
