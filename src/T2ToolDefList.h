#pragma once

#include <LArray.h>
#include "T2ToolDef.h"

class T2GWorld;
class T2MoverDef;
class T2OutObjDef;
class T2TenantDef;
class T2ToolDef;
class T2TowerDoc;
class T2WorldDef;

class T2ToolDefList : public LArray {
public:
	T2ToolDefList(Int16 categoryNo);
	~T2ToolDefList();

	void AllClear();
	void Regist(T2ToolDef *toolDef);
	void Add(T2ToolDef *toolDef);
	UInt32 GetItemCount();
	T2ToolDef *GetItemAt(long index);
	T2ToolDef *FindFloor();
	T2ToolDef *FindTenantDef(Int16 which);
	T2ToolDef *FindMoverDef(Int16 which);
	T2ToolDef *FindOutObjDef(Int16 which);
	T2GWorld *GetCategoryIcon();
	T2GWorld *GetCategoryHelp(T2WorldDef *worldDef);
	Boolean GetCategoryName(LStr255 &str);
	Boolean GetToolName(Int16 which, LStr255 &str, Int16 index);

	Int16 GetCategory() { return mCategoryNo; }

	Int16 mCategoryNo;
	Int16 m2A, m2C;
};
