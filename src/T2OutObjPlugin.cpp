#include "CFilePluginList.h"
#include "T2OutObj.h"
#include "T2OutObjDef.h"
#include "T2OutObjPlugin.h"
#include "T2TowerDoc.h"
#include "T2TowerMessage.h"
#include "T2WorldDef.h"

#include <LFile.h>
#include <LHandleStream.h>
#include <UException.h>

T2OutObjPlugin::T2OutObjPlugin(UInt32 id, const FSSpec &spec)
	: T2ToolPlugin(id, spec)
{
	mSubPluginList = 0;
}

T2OutObjPlugin::~T2OutObjPlugin() {
	if (mSubPluginList)
		delete mSubPluginList;
}

CFilePluginList *T2OutObjPlugin::GetSubPluginList() {
	return mSubPluginList;
}

OSErr T2OutObjPlugin::LoadAllTemplatePlugin(T2WorldDef *worldDef, Int16 mask, T2TemplatePluginDB *) {
	OSErr result = 32001;
	Int16 myMask = u2_b;
	if (myMask == 0 || myMask & mask) {
		Int16 refnum = mFile->OpenResourceFork(1);
		LoadT2OutObjDef(worldDef);
		mFile->CloseResourceFork();
		result = 0;
	}

	return result;
}

void T2OutObjPlugin::Add(CResourcePlugin *plugin) {
	// TODO: T2AdvertisePlugin
}

void T2OutObjPlugin::LoadT2OutObjDef(T2WorldDef *worldDef) {
	Int16 resCount = ::Count1Resources('OODf');
	Handle resHandle;
	if ((resHandle = ::Get1IndResource('OODf', 1))) {
		::DetachResource(resHandle);
		LHandleStream *stream;
		stream = new LHandleStream(resHandle);
		T2OutObjDef *outObjDef = new T2OutObjDef('OODf', stream, worldDef, this);
		delete stream;
		mTemplatePlugin = outObjDef;
	}
}

Int32 T2OutObjPlugin::AreaCheck2Proc(T2TowerDoc *inDoc, Rect &rect, UInt32 var, Boolean flag) {
	Int32 result = 1;

	#line 155
	Assert_(mTemplatePlugin != 0);
	Assert_(inDoc != 0 && inDoc->mWorldDef != 0 && inDoc->mFloorInfo != 0);

	if (rect.top <= inDoc->mWorldDef->m1C || rect.bottom >= (inDoc->mWorldDef->mGroundLine - 2)) {
		result = 0;
	} else {
		for (Int16 v = rect.top; v < rect.bottom && result == 1; v++) {
			for (Int16 h = rect.left; h < rect.right && result == 1; h++) {
				// TODO: T2FloorInfo
			}
		}
	}

	if (result != 1) {
		if (flag)
			inDoc->mTowerMessage->BuildErr(8, 0);
	} else {
		if (mAreaCheck2Proc)
			result = mAreaCheck2Proc(this, inDoc, rect, var, flag);
	}

	return result;
}

Int32 T2OutObjPlugin::DestructProc(T2TowerDoc *doc, T2HaveOutViewObject *obj, Point pt, Rect *rect) {
	Int32 result;
	if (mDestructProc) {
		result = mDestructProc(this, doc, obj, pt, rect);
	} else {
		result = ((T2OutObj *) obj)->Destruct(doc, *rect);
	}
	return result;
}
