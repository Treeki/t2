#include "T2Matter.h"
#include "T2ReturnStack.h"

#include <LStream.h>
#include <UException.h>

T2Matter::T2Matter() {
	Initialize();
	try {
		mReturnStack = new T2ReturnStack;
		#line 27
		ThrowIfNil_(mReturnStack);
	} catch (ExceptionCode code) {
		delete this;
		#line 32
		Throw_(code);
	}
}

void T2Matter::Initialize() {
	mMatterID = 0;
	mMatterDef = 0;
	mRgn = 0;
	mWorkTenant = 0;
	mHomeTenant = 0;
	mCurrEquipID = 0;
	mDstTenant = 0;
	mCurPosition.v = 0;
	mCurPosition.h = 0;
	mCurrDestPos.v = 0;
	mCurrDestPos.h = 0;
	mStartTime = -1;
	mReturnStack = 0;
	m2C = 0;
	m30 = 0;
	mDirection = -1;
	mWalkStyle = 0;
}

T2Matter::~T2Matter() {
	delete mReturnStack;
}

void T2Matter::SetUsed(Boolean value) {
	T2Object::SetUsed(value);
	if (value && mReturnStack)
		mReturnStack->Init();
}

void T2Matter::Initialize(T2MatterDef *def) {
	mMatterDef = def;
	mRgn = 0;
	mWorkTenant = 0;
	mHomeTenant = 0;
	mCurrEquipID = 0;
	mDstTenant = 0;
	mCurPosition.v = 0;
	mCurPosition.h = 0;
	mCurrDestPos.v = 0;
	mCurrDestPos.h = 0;
	mStartTime = -1;
	m2C = 0;
	m30 = 0;
	mDirection = -1;
	mWalkStyle = 0;
}

void T2Matter::FlipDirection() {
	if (mDirection == 0)
		mDirection = 1;
	else if (mDirection == 1)
		mDirection = 0;
}

void T2Matter::SetDestination(UInt16 dstTenant, UInt16 startTime) {
	mDstTenant = dstTenant;
	mStartTime = startTime;
}

void T2Matter::ClearDestination() {
	mDstTenant = 0;
	mStartTime = -1;
}

Boolean T2Matter::IsStartTime(UInt16 v) const {
	Boolean result = false;

	if (mStartTime > -1 && mStartTime <= v)
		result = true;

	return result;
}

Boolean T2Matter::IsSetReturn() const {
	return mReturnStack->IsSet();
}

Boolean T2Matter::IsSetReturnTime() const {
	return mReturnStack->IsSetTime();
}

UInt16 T2Matter::GetReturnTime() const {
	return mReturnStack->GetTime();
}

UInt16 T2Matter::GetReturn() const {
	return mReturnStack->GetTenant();
}

Boolean T2Matter::SetReturn(UInt16 tenant, UInt16 time) {
	return mReturnStack->Push(tenant, time);
}

void T2Matter::SetReturnTime(UInt16 time) {
	mReturnStack->SetTime(time);
}

Boolean T2Matter::PopReturn(UInt16 &tenant, UInt16 &time) {
	return mReturnStack->Pop(tenant, time);
}

Boolean T2Matter::SetReturnToDestination() {
	Boolean result = false;
	UInt16 tenant, time;

	if (mReturnStack->Pop(tenant, time)) {
		SetDestination(tenant, time);
		result = true;
	}

	return result;
}

Boolean T2Matter::SetDestinationToReturn() {
	return SetReturn(mDstTenant, mStartTime);
}

void T2Matter::DayChanged() {
	if (mStartTime >= 1440) {
		mStartTime -= 1440;
	} else if (mStartTime > 1438) {
		mStartTime = 0;
	}

	if (mReturnStack)
		mReturnStack->DayChanged();
}

Boolean T2Matter::RemoveReturn(UInt16 tenant) {
	Boolean result = false;

	if (mReturnStack)
		result = mReturnStack->Remove(tenant);

	return result;
}

void T2Matter::LoadSelf(LStream &stream, T2TowerDoc *doc) {
	T2Object::LoadSelf(stream, doc);
	if (IsUsed()) {
		stream >> mMatterID;
		stream >> mWorkTenant;
		stream >> mHomeTenant;
		stream >> mCurrEquipID;
		stream >> mDstTenant;
		stream >> mCurPosition;
		stream >> mCurrDestPos;
		stream >> mStartTime;
		stream >> mDirection;
		stream >> mWalkStyle;

		FourCharCode type;
		stream >> type;
		if (type == 'RSTK')
			mReturnStack->Read(stream);
	}
}

void T2Matter::SaveSelf(LStream &stream) {
	T2Object::SaveSelf(stream);
	if (IsUsed()) {
		stream << mMatterID;
		stream << mWorkTenant;
		stream << mHomeTenant;
		stream << mCurrEquipID;
		stream << mDstTenant;
		stream << mCurPosition;
		stream << mCurrDestPos;
		stream << mStartTime;
		stream << mDirection;
		stream << mWalkStyle;

		FourCharCode type = mReturnStack ? 'RSTK' : 'xRSK';
		stream << type;
		if (type == 'RSTK')
			mReturnStack->Write(stream);
	}
}
