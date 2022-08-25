#pragma once

#include <LStream.h>

class T2UnitInfo {
protected:
	UInt16 mMover, mTenant;

public:
	T2UnitInfo();
	~T2UnitInfo();

	Boolean IsBuildable() const;
	Boolean IsMoverID(UInt16 id) const;
	Boolean IsRequestID(UInt16 id) const;
	UInt16 GetTenantID() const;
	UInt16 GetMoverID() const;
	UInt16 GetRequestID() const;
	void FillTenantID(UInt16 id);
	void FillMoverID(UInt16 id);
	void InitMask(LStream &stream);
	void Read(LStream &stream);
	void Write(LStream &stream);
};
