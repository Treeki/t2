#pragma once

#include "T2StdDialog.h"

class T2SettlementDialog : public T2StdDialog {
public:
	T2SettlementDialog(LStream *inStream);
	~T2SettlementDialog();
	void FinishCreateSelf();
	void StandardSetup();
};
