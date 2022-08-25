#pragma once

#include <LArray.h>

class LStream;

enum EEquipPos {
	EEquipPos_0,
	EEquipPos_1,
	EEquipPos_2,
	EEquipPos_3
};

class T2StopInfoArray : public LArray {
public:
	T2StopInfoArray();
	~T2StopInfoArray();

	void Init(Int16 v);
	void AllClear();
	void Expand(EEquipPos equipPos, Int16 v);
	Boolean IsStopPos(Int16 a, Int16 b) const;
	Boolean IsOnStopPos(Int16 a, Int16 b) const;
	Boolean IsOffStopPos(Int16 a, Int16 b) const;
	void SetOnStop(Int16 a, Int16 b);
	void SetOffStop(Int16 a, Int16 b);
	void ClearOnStop(Int16 a, Int16 b);
	void ClearOffStop(Int16 a, Int16 b);
	Int8 GetStopAt(Int16 a, Int16 b) const;
	void SetStopAt(Int16 a, Int16 b, Int8 value);
	Int32 GetIndex(Int16 a, Int16 b) const;

	static T2StopInfoArray *ReadStopInfoArray(LStream &stream);
	static void WriteStopInfoArray(T2StopInfoArray *array, LStream &stream);

	virtual void Read(LStream &stream);
	virtual void Write(LStream &stream);
};
