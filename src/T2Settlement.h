#pragma once

#include <LArray.h>

class LStream;
class LString;
class T2DateTime;
class T2ToolDef;
class T2TowerDoc;

class T2Settlement {
public:
	T2Settlement(T2TowerDoc *doc, Int32 funds);
	T2Settlement(T2TowerDoc *doc, LStream &stream);
	~T2Settlement();
	LStream &Write(LStream &stream) const;
	void DoPay(Int32, Int16);
	void DoPayTool(Int32, Int16, T2ToolDef *inToolDef);
	void EmitPayToolMessage(T2TowerDoc *doc, T2ToolDef *toolDef, const LString &str, Int16, Int16);
	T2DateTime *GetTimeLimitOfMessage(T2TowerDoc *doc, T2ToolDef *toolDef, Int16);
	void SetTimeLimitOfMessage(T2TowerDoc *doc, T2ToolDef *toolDef, Int16, T2DateTime *dateTime);
	T2DateTime *FindCategoryTimeLimit(T2TowerDoc *doc, T2ToolDef *toolDef);
	void LinkCategoryTimeLimit(T2TowerDoc *doc, T2ToolDef *toolDef, T2DateTime *dateTime);
	T2DateTime *CalcTimeLimitOfMessage(T2DateTime *dateTime, Int16);
	Int32 GetCurrentFunds() const;
	Int32 GetPreviousFunds() const;
	Int32 GetTotalSettlement(Int16) const;
	Int32 GetToolSettlement(T2ToolDef *toolDef) const;
	Int32 GetCategorySettlement(Int16) const;
	void Initialize(T2TowerDoc *doc, Int32 funds);
	void Update();

	// all funcs need to be decompiled
	// depends on T2ToolDef, T2TowerMessage, other fun stuff.

	T2TowerDoc *mDocument;
	Int32 mCurrentFunds;
	Int32 mPreviousFunds;
	Int32 mC;
	Int32 m10;
	Int32 m14;
	Int32 m18;
	Int32 m1C;
	LArray *mCategoryTimeLimitList;
};
