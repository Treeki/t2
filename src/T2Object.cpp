#include "T2Object.h"

#include <LStream.h>

T2Object::T2Object() {
	mUsed = false;
	mStatus = 0;
	mFavorite = false;
}

void T2Object::SetFavorite(Boolean value) {
	mFavorite = value;
}

void T2Object::Load(LStream &stream, T2TowerDoc *doc) {
	LoadSelf(stream, doc);
	InitLoaded();
}

void T2Object::Save(LStream &stream) {
	SaveSelf(stream);
}

void T2Object::LoadSelf(LStream &stream, T2TowerDoc *doc) {
	stream >> mUsed;
	stream >> mStatus;
	stream >> mFavorite;
}

void T2Object::SaveSelf(LStream &stream) {
	stream << mUsed;
	stream << mStatus;
	stream << mFavorite;
}

void T2Object::InitLoaded() {
}

// all of these might be inlines...?

T2Object::~T2Object() {
}

/*void T2Object::SetUsed(Boolean value) {
	mUsed = value;
}*/

Int32 T2Object::Enter(CLink *link) {
	return 0;
}

Int32 T2Object::Leave(CLink *link) {
	return 0;
}

UInt32 T2Object::Idle(T2TowerDoc *doc) {
	return 0;
}

void T2Object::SetupDialog(T2Dialog *dialog) {
}

Int32 T2Object::DialogOK(T2Dialog *dialog) {
	return 0;
}

void T2Object::ForgetDialog() {
}
