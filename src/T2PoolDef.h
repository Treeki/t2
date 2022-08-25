#pragma once

#include "T2DumpObj.h"

#include <PP_Types.h>

class LStream;
class T2WorldPlugin;

enum { kMaxDemand = 8 };
enum { kPoolUnitSize = 20 };
enum { kMaxTimeZone = 24 };

// name not known
struct T2PoolTimeZoneDef_Inner {
	UInt8 m0;
	UInt8 m1;
	UInt8 m2;
	UInt8 mRate;
	UInt32 m4;
};

class T2PoolTimeZoneDef {
public:
	T2PoolTimeZoneDef(LStream &stream);
	void Initialize();
	~T2PoolTimeZoneDef();
	T2PoolTimeZoneDef_Inner *GetPeopleElem(UInt32 index) const;

	UInt32 mNumOfElems;
	T2PoolTimeZoneDef_Inner *mPeopleElems;
};

// name unknown
struct T2PoolDefDemandElem_Inner {
	Int16 a;
	UInt16 b;
};

class T2PoolDefDemandElem {
public:
	T2PoolDefDemandElem();
	void Initialize(LStream &stream);
	~T2PoolDefDemandElem();
	T2PoolDefDemandElem_Inner *GetTimeZoneInfo(UInt32 index) const;

	UInt32 GetNumOfElems() const { return mNumOfElems; }

	UInt32 mNumOfElems;
	T2PoolDefDemandElem_Inner *mElems;
};

class T2PoolGradeDef {
public:
	T2PoolGradeDef(LStream &stream);
	void Initialize();
	virtual ~T2PoolGradeDef();
	T2PoolDefDemandElem *GetDemandElem(UInt32 index) const;

	UInt32 GetNumOfElems() const { return mNumOfElems; }

	UInt32 mNumOfElems;
	T2PoolDefDemandElem *mElems;
};

// name not known
struct T2PoolDef_Inner {
	UInt8 a, b;
};

class T2PoolDef : public T2DumpObj {
public:
	T2PoolDef(LStream &stream, T2WorldPlugin *worldPlugin);
	void Initialize();
	virtual ~T2PoolDef();
	OSErr OpenResourceFork(Int16 permission);
	void CloseResourceFork();
	T2PoolDef_Inner *GetDemandInfo(UInt32 index) const;
	ResIDT GetGradeDefResID(UInt32 index) const;

	Byte GetNumOfDemand() const { return mNumOfDemand; }

	T2WorldPlugin *mWorldPlugin;
	Int16 m8;
	ResIDT mGradeDefResID[5];
	Byte m14;
	Byte mNumOfDemand;
	T2PoolDef_Inner *mDemand;
};
