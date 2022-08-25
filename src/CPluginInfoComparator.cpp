#include "CPluginInfoComparator.h"

CPluginInfoComparator *CPluginInfoComparator::sCPluginInfoComparator;

Int32 CPluginInfoComparator::Compare(const void *inItemOne, const void *inItemTwo, Uint32 inSizeOne, Uint32 inSizeTwo) const {
	const CPluginInfo *one = *(const CPluginInfo **) inItemOne;
	const CPluginInfo *two = *(const CPluginInfo **) inItemTwo;

	if (two == NULL)
		return -1;
	else if (one == 0)
		return 1;
	else
		return one->_04 - two->_04;
}

Boolean CPluginInfoComparator::IsEqualTo(const void *inItemOne, const void *inItemTwo, Uint32 inSizeOne, Uint32 inSizeTwo) const {
	const CPluginInfo *one = *(const CPluginInfo **) inItemOne;
	const CPluginInfo *two = *(const CPluginInfo **) inItemTwo;

	return one->_04 == two->_04;
}

Int32 CPluginInfoComparator::CompareToKey(const void *inItem, Uint32 inSize, const void *inKey) const {
	const CPluginInfo *pluginA;
	UInt32 keyB;

	pluginA = *((const CPluginInfo **) inItem);
	keyB = *((const UInt32 *) inKey);

	return pluginA->_04 - keyB;
}

CPluginInfoComparator *CPluginInfoComparator::GetComparator() {
	if (sCPluginInfoComparator == NULL)
		sCPluginInfoComparator = new CPluginInfoComparator;

	return sCPluginInfoComparator;
}

CPluginInfoComparator::~CPluginInfoComparator() {
}
