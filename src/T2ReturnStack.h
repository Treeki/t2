#pragma once

#include <PP_Types.h>

class LStream;

class T2ReturnStack {
public:
	T2ReturnStack();
	virtual ~T2ReturnStack();
	void Init();
	Boolean Current(UInt16 &tenant, UInt16 &time);
	Boolean Push(UInt16 tenant, UInt16 time);
	Boolean Pop(UInt16 &tenant, UInt16 &time);
	Boolean IsSetTime() const;
	UInt16 GetTenant() const;
	UInt16 GetTime() const;
	void SetTime(UInt16 time);
	void DayChanged();
	Boolean Remove(UInt16 tenant);
	void Peek(Int32 index, UInt16 &tenant, UInt16 &time);
	void Poke(Int32 index, UInt16 tenant, UInt16 time);
	void Read(LStream &stream);
	void Write(LStream &stream);

	Boolean IsSet() const { return mCount > 0; }

	struct Entry {
		UInt16 tenant, time;
	};
	Entry mEntries[3];
	Int32 mCount;
};
