#include <LComparator.h>

class T2TempPluginComparator : public LComparator {
public:
	Int32 Compare(const void* inItemOne, const void* inItemTwo, Uint32 inSizeOne, Uint32 inSizeTwo) const;
	Boolean IsEqualTo(const void* inItemOne, const void* inItemTwo, Uint32 inSizeOne, Uint32 inSizeTwo) const;

	static T2TempPluginComparator *GetComparator();

	static T2TempPluginComparator *sT2TempPluginComparator;
};
