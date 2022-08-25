#include "T2TempPluginComparator.h"
#include "T2TemplatePlugin.h"

T2TempPluginComparator *T2TempPluginComparator::sT2TempPluginComparator;

T2TempPluginComparator *T2TempPluginComparator::GetComparator() {
	if (!sT2TempPluginComparator)
		sT2TempPluginComparator = new T2TempPluginComparator;
	return sT2TempPluginComparator;
}

Int32 T2TempPluginComparator::Compare(const void* inItemOne, const void* inItemTwo, Uint32 inSizeOne, Uint32 inSizeTwo) const {
	T2TemplatePlugin *a = *((T2TemplatePlugin **) inItemOne);
	T2TemplatePlugin *b = *((T2TemplatePlugin **) inItemTwo);

	if (!b) {
		return -1;
	} else if (!a) {
		return 1;
	} else {
		return a->GetSortKey() - b->GetSortKey();
	}
}

Boolean T2TempPluginComparator::IsEqualTo(const void* inItemOne, const void* inItemTwo, Uint32 inSizeOne, Uint32 inSizeTwo) const {
	T2TemplatePlugin *a = *((T2TemplatePlugin **) inItemOne);
	T2TemplatePlugin *b = *((T2TemplatePlugin **) inItemTwo);

	return a->GetSortKey() == b->GetSortKey();
}
