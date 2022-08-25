#include "T2TemplatePluginDB.h"
#include "T2ToolDef.h"
#include <LArrayIterator.h>

T2TemplatePluginDB::T2TemplatePluginDB()
	: LArray(sizeof(T2TemplatePluginList *))
{
}

T2TemplatePluginDB::~T2TemplatePluginDB() {
}

void T2TemplatePluginDB::Regist(T2TemplatePlugin *plugin) {
	if (!plugin)
		return;

	Boolean found;
	LArrayIterator iter(*this);
	T2TemplatePluginList *list;

	found = false;

	while (!found && iter.Next(&list)) {
		if (list->GetID() == plugin->GetID()) {
			list->Add(plugin);
			found = true;
		}
	}

	if (!found) {
		list = new T2TemplatePluginList(plugin->GetID());
		list->Add(plugin);
		InsertItemsAt(1, index_Last, &list);
	}
}

void T2TemplatePluginDB::Add(T2TemplatePluginList *list) {
	LArrayIterator iter(*this);
	T2TemplatePluginList *iterList;
	Boolean found = false;

	while (!found && iter.Next(&iterList)) {
		if (iterList->GetID() == list->GetID()) {
			LArrayIterator subIter(*list);
			T2TemplatePlugin *plugin;
			while (subIter.Next(&plugin)) {
				iterList->Add(plugin);
			}
			found = true;
		}
	}

	if (!found)
		InsertItemsAt(1, index_Last, &list);
}

T2TemplatePluginList *T2TemplatePluginDB::GetTemplatePluginList(UInt32 id) {
	LArrayIterator iter(*this);
	T2TemplatePluginList *list;

	while (iter.Next(&list)) {
		if (id == list->GetID())
			return list;
	}

	return NULL;
}

T2TemplatePlugin *T2TemplatePluginDB::FindFloor() {
	LArrayIterator iter(*this);
	T2TemplatePluginList *list;

	while (iter.Next(&list)) {
		if (list->GetID() == 'TnDf')
			return list->FindFloor();
	}

	return NULL;
}
