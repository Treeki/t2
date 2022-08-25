#include "T2OutObjf.h"
#include "T2PeopleDef.h"
#include "T2SilhouetteDef.h"
#include "T2ToolDef.h"
#include "T2TemplatePluginList.h"
#include "T2TempPluginComparator.h"
#include <LArrayIterator.h>

T2TemplatePluginList::T2TemplatePluginList(UInt32 id)
	: LArray(sizeof(T2TemplatePlugin*))
{
	mId = id;
	SetComparator(T2TempPluginComparator::GetComparator());
	mOwnsComparator = false;
	SetKeepSorted(true);
}

T2TemplatePluginList::~T2TemplatePluginList() {
}

void T2TemplatePluginList::AllClear() {
	RemoveItemsAt(GetCount(), index_First);
}

void T2TemplatePluginList::Regist(T2TemplatePlugin *plugin) {
	if (plugin)
		InsertItemsAt(1, index_Last, &plugin);
}

void T2TemplatePluginList::Add(T2TemplatePlugin *plugin) {
	if (plugin)
		InsertItemsAt(1, index_Last, &plugin);
}

UInt32 T2TemplatePluginList::GetItemCount() {
	return GetCount();
}

UInt32 T2TemplatePluginList::CalcCategoryCount() {
	Int32 count = 0;
	LArray array(sizeof(Int16));
	LArrayIterator iter(*this);
	T2ToolDef *plugin;

	while (iter.Next(&plugin)) {
		Int16 categoryNo = plugin->mCategoryNo;
		Boolean found = false;

		LArrayIterator checkID(array);
		Int16 iterNo;
		while (checkID.Next(&iterNo)) {
			if (iterNo == categoryNo) {
				found = true;
				break;
			}
		}

		if (!found) {
			array.InsertItemsAt(1, array.GetCount() + 1, &categoryNo);
			count++;
		}
	}

	return count;
}

T2TemplatePlugin *T2TemplatePluginList::GetItemAt(long index){
	T2TemplatePlugin *plugin;
	if (FetchItemAt(index, &plugin))
		return plugin;
	else
		return NULL;
}

T2ToolDef *T2TemplatePluginList::FindFloor() {
	if (mId != 'TnDf')
		return 0;

	LArrayIterator iter(*this);
	T2ToolDef *def;

	while (iter.Next(&def)) {
		if (def->IsSetAttribute(0x2000))
			return def;
	}

	return 0;
}

T2ToolDef *T2TemplatePluginList::FindTenantDef(Int16 which) {
	if (mId != 'TnDf')
		return 0;

	LArrayIterator iter(*this);
	T2ToolDef *def;

	while (iter.Next(&def)) {
		if (def->GetToolType() == which)
			return def;
	}

	return 0;
}

T2ToolDef *T2TemplatePluginList::FindMoverDef(Int16 which) {
	if (mId != 'MvDf')
		return 0;

	LArrayIterator iter(*this);
	T2ToolDef *toolDef;

	while (iter.Next(&toolDef)) {
		if (toolDef->GetToolType() == which)
			return toolDef;
	}

	return 0;
}

T2OutObjDef *T2TemplatePluginList::FindOutObjDef(Int16 which) {
	if (mId != 'OODf')
		return 0;

	LArrayIterator iter(*this);
	T2OutObjDef *def;

	while (iter.Next(&def)) {
		if (def->GetToolType() == which)
			return def;
	}

	return 0;
}

T2PeopleDef *T2TemplatePluginList::FindPeopleDef(Int16 which) {
	if (mId != 'PPDf')
		return 0;

	LArrayIterator iter(*this);
	T2PeopleDef *def;

	while (iter.Next(&def)) {
		if (which == def->GetMatterType())
			return def;
	}

	return 0;
}

T2SilhouetteDef *T2TemplatePluginList::FindSilhouette(Int16 which) {
	if (mId != 'SlDf')
		return 0;

	LArrayIterator iter(*this);
	T2SilhouetteDef *def;

	while (iter.Next(&def)) {
		if (which == def->GetSilhouetteType())
			return def;
	}

	return 0;
}

void T2TemplatePluginList::DispatchIdle(T2TowerDoc *doc) {
	if (mId == 'OODf' || mId == 'MvDf' || mId == 'TnDf') {
		LArrayIterator iter(*this);
		T2ToolDef *plugin;

		while (iter.Next(&plugin)) {
			plugin->DefIdleProc(doc);
		}
	}
}
