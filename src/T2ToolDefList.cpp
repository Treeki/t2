#include "T2ToolDefList.h"
#include "T2TempPluginComparator.h"
#include <LArrayIterator.h>

T2ToolDefList::T2ToolDefList(Int16 categoryNo)
	: LArray(sizeof(T2ToolDef *))
{
	mCategoryNo = categoryNo;
	SetComparator(T2TempPluginComparator::GetComparator());
	mOwnsComparator = false;
	SetKeepSorted(true);
	m2A = 1;
	m2C = 0;
}

T2ToolDefList::~T2ToolDefList() {
}

void T2ToolDefList::AllClear() {
	RemoveItemsAt(GetCount(), index_First);
}

void T2ToolDefList::Regist(T2ToolDef *toolDef) {
	InsertItemsAt(1, index_Last, &toolDef);
}

void T2ToolDefList::Add(T2ToolDef *toolDef) {
	if (toolDef) {
		LArrayIterator iter(*this);
		Boolean added = false; // r31
		Int32 index = 1; // r30

		T2ToolDef *check;
		while (!added && iter.Next(&check)) {
			if (check->GetToolNo() < toolDef->GetToolNo()) {
				InsertItemsAt(1, index, &toolDef);
				added = true;
			}
			index++;
		}

		if (!added)
			InsertItemsAt(1, index, &toolDef);
	}
}

UInt32 T2ToolDefList::GetItemCount() {
	return GetCount();
}

T2ToolDef *T2ToolDefList::GetItemAt(long index){
	T2ToolDef *toolDef;
	if (FetchItemAt(index, &toolDef))
		return toolDef;
	else
		return NULL;
}

T2ToolDef *T2ToolDefList::FindFloor() {
	LArrayIterator iter(*this);
	T2ToolDef *toolDef;

	while (iter.Next(&toolDef)) {
		if (toolDef->IsTenant() && toolDef->IsSetAttribute(0x2000))
			return toolDef;
	}

	return 0;
}

T2ToolDef *T2ToolDefList::FindTenantDef(Int16 which) {
	LArrayIterator iter(*this);
	T2ToolDef *toolDef;

	while (iter.Next(&toolDef)) {
		if (toolDef->IsTenant() && toolDef->GetToolType() == which)
			return toolDef;
	}

	return 0;
}

T2ToolDef *T2ToolDefList::FindMoverDef(Int16 which) {
	LArrayIterator iter(*this);
	T2ToolDef *toolDef;

	while (iter.Next(&toolDef)) {
		if (toolDef->IsMover() && toolDef->GetToolType() == which)
			return toolDef;
	}

	return 0;
}

T2ToolDef *T2ToolDefList::FindOutObjDef(Int16 which) {
	LArrayIterator iter(*this);
	T2ToolDef *toolDef;

	while (iter.Next(&toolDef)) {
		if (toolDef->IsOutObj() && toolDef->GetToolType() == which)
			return toolDef;
	}

	return 0;
}

T2GWorld *T2ToolDefList::GetCategoryIcon() {
	T2GWorld *result = 0;
	T2ToolDef *toolDef = GetItemAt(1);
	if (toolDef)
		result = toolDef->mCategoryIcon;
	return result;
}

T2GWorld *T2ToolDefList::GetCategoryHelp(T2WorldDef *worldDef) {
	T2GWorld *result = 0;
	T2ToolDef *toolDef = GetItemAt(1);
	if (toolDef)
		result = toolDef->GetCategoryHelpGWorld(worldDef);
	return result;
}

Boolean T2ToolDefList::GetCategoryName(LStr255 &str) {
	T2ToolDef *toolDef = GetItemAt(1);
	if (toolDef) {
		toolDef->GetCategoryName(str);
		return true;
	} else {
		return false;
	}
}

Boolean T2ToolDefList::GetToolName(Int16 which, LStr255 &str, Int16 index) {
	T2ToolDef *toolDef = GetItemAt(which);
	if (toolDef) {
		toolDef->GetToolName(str, index);
		return true;
	} else {
		return false;
	}
}
