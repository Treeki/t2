#include "T2Request.h"
#include "T2TowerDoc.h"
#include "T2TowerMainView.h"

T2Request::T2Request() {
	mRequestID = 0;
	mMoverID = 0;
	mUpDown = 0;
	mHeadPosition.v = 0;
	mHeadPosition.h = 0;
	mModuleIndex = -1;
	mDrawWidth = 0;
	m18 = 0;
	m1A = 0;
	mOnPeople = 0;
	mOffPeople = 0;
	m24 = 0;
	m28 = 0;
	m2C = false;
	mPeopleRemoved = false;
	mNumOfContent = 0;
}

T2Request::~T2Request() {
}

void T2Request::InitRequest(T2FloorInfo *floorInfo, UInt16 moverID, Point headPosition, Int16 upDown) {}
void T2Request::RemoveRequest(T2TowerDoc *doc) {}
void T2Request::RemoveContents(T2FloorInfo *floorInfo) {}
void T2Request::SetUsed(Boolean value) {}
void T2Request::StopRemoved(T2TowerDoc *doc, Int16 a) {}
void T2Request::CalcArea(Rect &rect) {}
void T2Request::CalcOnArea(Rect &rect) {}
void T2Request::CalcOffArea(Rect &rect) {}
void T2Request::CalcPrevArea(Rect &rect) {}
Boolean T2Request::CalcPersonArea(T2People *people, Rect &rect) {}
Boolean T2Request::CalcIncQueueArea(Rect &rect) const {}
Boolean T2Request::Regist(T2TowerDoc *doc, T2People *people) {}
Int32 T2Request::Enter(CLink *link) {}
Int32 T2Request::Leave(CLink *link) {}
T2People *T2Request::LeaveFirst() {}
void T2Request::ChangeOffPPLStatus(T2FloorInfo *floorInfo, T2People *people) {}
void T2Request::AddOnPeople(T2People *people) {}
T2People *T2Request::RemoveOnPeople() {}
void T2Request::AddOffPeople(T2People *people) {}
T2People *T2Request::RemoveOffPeople() {}
UInt32 T2Request::Idle(T2TowerDoc *doc) {}
void T2Request::DrawFinished() {}
void T2Request::Draw(T2TowerDoc *doc, const Rect &rect) {}
void T2Request::DrawUp(T2TowerDoc *doc, const Rect &rect) {}
void T2Request::DrawDown(T2TowerDoc *doc, const Rect &rect) {}
T2People *T2Request::FindPeople(Int32 var) const {}
T2People *T2Request::FindUpPeople(Int32 var) const {}
T2People *T2Request::FindDownPeople(Int32 var) const {}
void T2Request::BreakoutEmergency(T2TowerDoc *doc) {}
void T2Request::LoadSelf(LStream &stream, T2TowerDoc *doc) {}
void T2Request::SaveSelf(LStream &stream) {}
