#include "T2TenantMemberDef.h"

#include <LStream.h>
#include <LString.h>
#include <stdio.h>

T2TenantMemberDef::T2TenantMemberDef() {
}

T2TenantMemberDef::~T2TenantMemberDef() {
}

void T2TenantMemberDef::Initialize(LStream &stream, float f) {
	for (UInt32 i = 0; i < 16; i++) {
		Byte b;
		stream >> b;
		mName[i] = b;
	}

	stream >> mDemandType;
	stream >> mStartSilhouetteType;
	stream >> mEndSilhouetteType;
	stream >> mOptionType;
	stream >> mPercent;
	stream >> mNumOfPeople;
	if (f > 0.0f && mPercent != 0) {
		mRate = (f * mPercent) / 100.0f;
	}
}

Int32 T2TenantMemberDef::DrawData(Int32 pos) {
	Int16 p = pos;
	LStr255 tmp;
	char buf[256];

	p += 16;
	::MoveTo(10, p);
	::DrawString("\p================================");

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmName : ");
	::DrawString(mName);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmDemandType : ");
	tmp = (Int32) mDemandType;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmStartSilhouetteType : ");
	tmp = (Int32) mStartSilhouetteType;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmEndSilhouetteType : ");
	tmp = (Int32) mEndSilhouetteType;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmOptionType : ");
	tmp = (Int32) mOptionType;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmPercent : ");
	tmp = (Int32) mPercent;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmNumOfPeople : ");
	tmp = (Int32) mNumOfPeople;
	::DrawString(tmp);

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmRate : ");
	sprintf(buf, "%9.6f", mRate);
	tmp = buf;
	::DrawString(tmp);

	return p;
}
