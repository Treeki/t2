#pragma once

#include <PP_Types.h>
#include "CLink.h"

class LStream;
class T2Dialog;
class T2TowerDoc;

class T2Object {
public:
	T2Object();
	virtual ~T2Object();

	void Load(LStream &stream, T2TowerDoc *doc);
	void Save(LStream &stream);

	virtual void SetUsed(Boolean value) { mUsed = value; }
	virtual Int32 Enter(CLink *link);
	virtual Int32 Leave(CLink *link);
	virtual UInt32 Idle(T2TowerDoc *doc);
	virtual void SetupDialog(T2Dialog *dialog);
	virtual Int32 DialogOK(T2Dialog *dialog);
	virtual void ForgetDialog();
	virtual void SetFavorite(Boolean value);
	virtual void LoadSelf(LStream &stream, T2TowerDoc *doc);
	virtual void SaveSelf(LStream &stream);
	virtual void InitLoaded();

	Boolean IsUsed() const { return mUsed; }
	Int16 GetStatus() const { return mStatus; }
	Boolean IsFavorite() const { return mFavorite; }
	void SetStatus(Int16 s) { mStatus = s; }

// protected:
	Boolean mUsed;
	Boolean _1;
	Int16 mStatus;
	Boolean mFavorite;
};
