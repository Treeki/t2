#include "CFilePluginList.h"
#include <LArrayIterator.h>

CFilePluginList::CFilePluginList(UInt32 id)
	: LArray(sizeof(CFilePlugin*))
{
	mId = id;
}

CFilePluginList::~CFilePluginList() {
}

void CFilePluginList::AllClear() {
	RemoveItemsAt(GetCount(), index_First);
}

void CFilePluginList::Add(CFilePlugin *plugin) {
	Boolean found = false;
	LArrayIterator iter(*this);
	void *listPluginPtr;

	while (!found && iter.Next(&listPluginPtr)) {
		if (((CFilePlugin *) listPluginPtr)->GetStrangeID() == plugin->GetStrangeID())
			found = true;
	}

	if (!found)
		InsertItemsAt(1, index_Last, &plugin);
}

UInt32 CFilePluginList::GetItemCount() {
	return GetCount();
}

CFilePlugin *CFilePluginList::GetItemAt(long index){
	CFilePlugin *plugin;
	if (FetchItemAt(index, &plugin))
		return plugin;
	else
		return NULL;
}

CFilePlugin *CFilePluginList::GetItem(UInt32 id) {
	LArrayIterator iter(*this);
	void *pluginPtr;

	while (iter.Next(&pluginPtr)) {
		if (((CFilePlugin *) pluginPtr)->GetStrangeID() == id)
			return (CFilePlugin *) pluginPtr;
	}

	return NULL;
}
