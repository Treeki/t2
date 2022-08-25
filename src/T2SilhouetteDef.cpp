#include "T2GWorld.h"
#include "T2SilhouetteDef.h"
#include "UDebugUtils.h"

T2SilhouetteDef::T2SilhouetteDef(UInt32 id, LStream *stream)
	: T2TemplatePlugin(id, stream, 0)
{
	(*stream) >> mSilhouetteType;
	(*stream) >> m16;
	(*stream) >> m18;
	(*stream) >> mSilhouetteID;

	(*stream) >> mName[0];
	for (int i = 1; i <= mName[0]; i++)
		(*stream) >> mName[i];

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			mSilhouette[i][j] = 0;
		}
	}

	T2GWorld *w = new T2GWorld(mSilhouetteID, 1, 0, 0, 0);
	if (w) {
		UInt16 unused = 0;
		Rect srcRect = { 0, 0, 36, 16 };
		Rect dstRect = { 0, 0, 36, 16 };
		T2GWorld *w2 = new T2GWorld(dstRect, 1, 0, 0, 0);
		if (w2) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 3; j++) {
					w->CopyOffImage(w2, srcRect, dstRect, 0, 0);
					mSilhouette[i][j] = w2->MakeRgn();
					::OffsetRect(&srcRect, 0, 36);
				}
			}
		}
		delete w2;
		delete w;
	}

	mLoaded = true;
}

T2SilhouetteDef::~T2SilhouetteDef() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if (mSilhouette[i][j])
				::DisposeRgn(mSilhouette[i][j]);
			mSilhouette[i][j] = 0;
		}
	}
}

void T2SilhouetteDef::GetName(LString &str) {
	str = mName;
}

Int32 T2SilhouetteDef::DrawData(Int32 pos) {
	LStr255 str;

	Int16 p = pos;
	::MoveTo(10, p);
	::DrawString("\p================================");

	p += 16;
	::MoveTo(10, p);
	::DrawString("\pmSilhouetteType : ");

	str = (Int32) mSilhouetteType;
	::DrawString(str);

	for (Int32 i = 0; i < 2; i++) {
		for (Int32 j = 0; j < 3; j++) {
			p += 16;
			::MoveTo(10, p);
			::DrawString("\pmSilhouetteID[");
			str = i;
			::DrawString(str);
			::DrawString("\p][");
			str = j;
			::DrawString(str);
			::DrawString("\p] : ");
			str = (Int32) mSilhouetteID;
			::DrawString(str);
		}
	}

	p += 16;
	::MoveTo(10, p);
	::DrawString("\p================================");

	RgnHandle rgn = ::NewRgn();

	for (Int32 i = 0; i < 2; i++) {
		for (Int32 j = 0; j < 3; j++) {
			p += 16;
			::MoveTo(10, p);
			::DrawString("\pmSilhouette[");
			str = i;
			::DrawString(str);
			::DrawString("\p][");
			str = j;
			::DrawString(str);
			::DrawString("\p] : ");
			UDebugUtils::HexString(&mSilhouette[i][j], str);
			::DrawString(str);

			if (mSilhouette[i][j]) {
				::CopyRgn(mSilhouette[i][j], rgn);
				::OffsetRgn(rgn, 10, p);
				::PaintRgn(rgn);

				Rect rect = (*rgn)->rgnBBox;
				::InsetRect(&rect, -1, -1);
				::FrameRect(&rect);

				p += (rect.bottom - rect.top) + 16;
			}
		}
	}

	::DisposeRgn(rgn);

	return p;
}

Int32 T2SilhouetteDef::GetSortKey() {
	return mSilhouetteType;
}
