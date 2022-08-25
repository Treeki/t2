#pragma once

#include <LArray.h>

class LStream;
class T2OutObj;
class T2OutObjArray;
class T2TowerDoc;

class T2OutObjArrayList : public LArray {
public:
	T2OutObjArrayList();
	~T2OutObjArrayList();

	void Add(T2OutObjArray *array);
	T2OutObjArray *GetItemAt(Int32 index);
	T2OutObj *FindUnusedOutObj();
	void DispatchIdle(T2TowerDoc *doc);
	T2OutObj *GetIndOutObj(UInt16 index);
	T2OutObj *GetOutObjByID(UInt16 index);
	Int32 CalcMentenanceCost(T2TowerDoc *doc) const;
	void Read(LStream &stream, T2TowerDoc *doc);
	void Write(LStream &stream);
};
