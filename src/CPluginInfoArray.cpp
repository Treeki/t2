#include "CPluginInfoArray.h"
#include <LArrayIterator.h>

CPluginInfoArray::CPluginInfoArray(Boolean flag)
	: LArray(sizeof(CPluginInfo*), CPluginInfoComparator::GetComparator(), true)
{
	mOwnsComparator = false;
	_28 = flag;
}

CPluginInfoArray::~CPluginInfoArray() {
	if (_28) {
		LArrayIterator iter(*this);
		CPluginInfo *info;
		while (iter.Next(&info)) {
			delete info;
		}
	}
}

int CPluginInfoArray::GetUsedCount() {
	int count = 0;

	LArrayIterator iter(*this);
	CPluginInfo *info;
	void *infoPtr;

	while (iter.Next(&infoPtr)) {
		info = (CPluginInfo *) infoPtr;
		if (info->_14C)
			++count;
	}

	return count;
}
