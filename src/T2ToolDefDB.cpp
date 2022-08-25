#include "T2ToolDefDB.h"
#include <LArrayIterator.h>

T2ToolDefDB::T2ToolDefDB()
	: LArray(sizeof(T2ToolDefList *))
{
}

T2ToolDefDB::~T2ToolDefDB() {
}

void T2ToolDefDB::AllClear() {
	RemoveItemsAt(mItemCount, index_First);
}

void T2ToolDefDB::Regist(T2ToolDef *toolDef) {
	if (!toolDef)
		return;

	Int16 category = toolDef->GetCategory();
	Int32 index = 1;
	Boolean found;
	LArrayIterator iter(*this);
	T2ToolDefList *list;

	found = false;

	while (!found && iter.Next(&list)) {
		Int16 listCategory = list->GetCategory();
		if (listCategory == category) {
			list->Add(toolDef);
			found = true;
		} else if (listCategory > category) {
			break;
		}

		index++;
	}

	if (!found) {
		list = new T2ToolDefList(category);
		list->Add(toolDef);
		InsertItemsAt(1, index, &list);
	}
}

void T2ToolDefDB::Add(T2ToolDefList *list) {
	LArrayIterator iter(*this);
	T2ToolDefList *iterList;
	Boolean found = false;

	while (!found && iter.Next(&iterList)) {
		if (iterList->GetCategory() == list->GetCategory()) {
			LArrayIterator subIter(*list);
			T2ToolDef *toolDef;
			while (subIter.Next(&toolDef)) {
				iterList->Add(toolDef);
			}
			found = true;
		}
	}

	if (!found)
		InsertItemsAt(1, index_Last, &list);
}

T2ToolDefList *T2ToolDefDB::GetToolDefList(Int16 category) {
	LArrayIterator iter(*this);
	T2ToolDefList *list;

	while (iter.Next(&list)) {
		if (category == list->GetCategory())
			return list;
	}

	return NULL;
}

T2ToolDef *T2ToolDefDB::FindFloor() {
	LArrayIterator iter(*this);
	T2ToolDefList *list;

	while (iter.Next(&list)) {
		T2ToolDef *floor = list->FindFloor();
		if (floor)
			return floor;
	}

	return NULL;
}
