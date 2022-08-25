#include "CFilePluginDB.h"
#include <LArrayIterator.h>

CFilePluginDB::CFilePluginDB()
	: LArray(sizeof(CFilePluginList*))
{
}

CFilePluginDB::~CFilePluginDB() {
}

void CFilePluginDB::Add(CFilePlugin *plugin) {
	Boolean found;
	LArrayIterator iter(*this);
	CFilePluginList *list;

	found = false;

	while (!found && iter.Next(&list)) {
		if (list->GetID() == plugin->GetID()) {
			list->Add(plugin);
			found = true;
		}
	}

	if (!found) {
		list = new CFilePluginList(plugin->GetID());
		list->Add(plugin);
		InsertItemsAt(1, index_Last, &list);
	}
}

CFilePluginList *CFilePluginDB::GetFilePluginList(UInt32 id) {
	LArrayIterator iter(*this);
	CFilePluginList *list;

	while (iter.Next(&list)) {
		if (id == list->GetID())
			return list;
	}

	return NULL;
}
