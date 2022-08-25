#include "T2GWorld.h"
#include "T2OutObj.h"
#include "T2OutObjDef.h"
#include "T2TemplatePluginList.h"
#include "T2TowerDoc.h"
#include "T2TowerMainView.h"
#include "UT2Coordinate.h"

#include <LStream.h>

T2OutObj::T2OutObj() {
	mToolType = 0;
	::SetRect(&mOutObjArea, 0, 0, 0, 0);
	mDefIndex = 0;
}

T2OutObj::~T2OutObj() {
}

Int32 T2OutObj::InitOutObj(T2OutObjDef *def, const Rect &rect, UInt32 valiation) {
	Int32 result = 0;

	mSubPlugin = 0;
	if (def) {
		mDefIndex = def->GetToolType();
		mToolDef = def;
	}

	mOutObjArea = rect;
	mValiation = valiation;
	SetUsed(true);

	return result;
}

void T2OutObj::StartBuild(T2TowerDoc *) {
	mStatus = 1;
}

Int32 T2OutObj::DoDestruct(T2TowerDoc *doc, Int16 s, Point ptA, Point ptB, Rect &rect) {
	Int32 result = 0;
	if (GetToolDef())
		result = GetToolDef()->DestructProc(doc, this, ptA, rect);
	return result;
}

Int32 T2OutObj::Destruct(T2TowerDoc *doc, Rect &rect) {
	GetOutObjArea(rect);
	if (doc->mFloorInfo) {
		// TODO: T2FloorInfo
		if (GetToolDef())
			GetToolDef()->DestructFinishProc(doc, this);
	}
	SetUsed(false);
	return 1;
}

void T2OutObj::GetOutObjArea(Rect &rect) const {
	rect = mOutObjArea;
}

void T2OutObj::Draw(T2TowerDoc *doc, const Rect &rect) {
	T2ToolDef *def = GetToolDef();
	if (def) {
		if (def->HasDrawProc()) {
			def->DrawProc(this, rect, doc);
		} else {
			T2GWorld *world = def->GetOffscreen(mValiation);
			if (world) {
				Rect srcRectQD, srcRect, dstRectQD, dstRect;
				GetOutObjArea(dstRect);
				srcRect = dstRect;
				::OffsetRect(&srcRect, -srcRect.left, -srcRect.top);
				UT2Coordinate::UnitToQD(srcRect, srcRectQD, 0, 1);
				UT2Coordinate::UnitToQD(dstRect, dstRectQD, doc->GetZoomLevel(), 0);
				world->CopyOffImage(doc->GetMainView()->mGWorld, srcRectQD, dstRectQD);
			}
		}
	}
}

UInt32 T2OutObj::Idle(T2TowerDoc *doc) {
	UInt32 result = 0;
	if (GetToolDef())
		result = GetToolDef()->IdleProc(this, doc);
	if (result != 0)
		doc->GetMainView()->InvalUnitRect(mOutObjArea, false);
	return result;
}

void T2OutObj::LoadSelf(LStream &stream, T2TowerDoc *doc) {
	T2Object::LoadSelf(stream, doc);
	if (IsUsed()) {
		stream >> mToolType;
		stream >> mOutObjArea;
		stream >> mValiation;
		stream >> mDefIndex;

		mToolDef = doc->mOOTemplates->FindOutObjDef(mDefIndex);
		if (mToolDef) {
			mToolDef->LoadExtraData(stream, doc, this);
		} else {
			Int32 size;
			stream >> size;
			for (Int32 i = 0; i < size; i++) {
				Byte b;
				stream >> b;
			}
		}
	}
}

void T2OutObj::SaveSelf(LStream &stream) {
	T2Object::SaveSelf(stream);
	if (IsUsed()) {
		stream << mToolType;
		stream << mOutObjArea;
		stream << mValiation;
		stream << mDefIndex;

		if (mToolDef) {
			mToolDef->SaveExtraData(stream, this);
		} else {
			Int32 size = 0;
			stream << size;
		}
	}
}
