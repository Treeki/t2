#pragma once

#include <LArray.h>
#include "T2ToolDefList.h"

class T2ToolDefDB : public LArray {
public:
	T2ToolDefDB();
	~T2ToolDefDB();

	void AllClear();
	void Regist(T2ToolDef *toolDef);
	void Add(T2ToolDefList *list);
	T2ToolDefList *GetToolDefList(Int16 category);
	T2ToolDef *FindFloor();
};
