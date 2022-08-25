#include "T2TemplatePlugin.h"

class T2SilhouetteDef : public T2TemplatePlugin {
public:
	T2SilhouetteDef(UInt32 id, LStream *stream);
	~T2SilhouetteDef();

	void GetName(LString &str);
	Int32 DrawData(Int32 pos);
	Int32 GetSortKey();

	Int16 GetSilhouetteType() const { return mSilhouetteType; }
	Int16 GetWidth() const { return m16; }
	Int16 GetRouteType() const { return m18; }
	RgnHandle GetSilhouette(UInt32 a, UInt32 b) const { return mSilhouette[a][b]; }

	Int16 mSilhouetteType;
	Int16 m16;
	Int16 m18;
	Int16 mSilhouetteID;
	RgnHandle mSilhouette[2][3];
	Str31 mName;
};
