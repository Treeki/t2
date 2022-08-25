#pragma once

#include "T2TemplatePlugin.h"

class T2SilhouetteDef;
class T2TemplatePluginList;

class T2MatterDef : public T2TemplatePlugin {
public:
	T2MatterDef(UInt32 id, LStream *stream, CProgramPlugin *programPlugin);
	~T2MatterDef();

	void GetName(LString &str);
	virtual void AssignSilhouette(T2TemplatePluginList *list);
	Int32 DrawData(Int32 pos);

	T2SilhouetteDef *GetSilhouetteDef() const { return mSilhouetteDef; }
	Int16 GetAttribute() const { return mAttribute; }
	Int16 GetMatterType() const { return mMatterType; }

	Int16 mMatterType;
	Int16 mAttribute;
	Int16 mSilhouetteType;
	T2SilhouetteDef *mSilhouetteDef;
};
