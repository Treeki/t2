#include "CProgramPlugin.h"
#include "T2GWorld.h"
#include "T2TemplatePlugin.h"

#include <LString.h>
#include <UException.h>

T2TemplatePlugin::T2TemplatePlugin(UInt32 id, LStream *stream, CProgramPlugin *programPlugin)
	: CDefRsrcPlugin(id, stream)
{
	mProgramPlugin = programPlugin;
}

T2TemplatePlugin::~T2TemplatePlugin() {
	if (mProgramPlugin)
		mProgramPlugin->mTemplatePlugin = 0;
}

Int16 T2TemplatePlugin::InitObject(T2Object *obj) {
	return -1;
}

OSErr T2TemplatePlugin::OpenResourceFork(Int16 permissions) {
	#line 67
	ThrowIfNil_(mProgramPlugin);

	return mProgramPlugin->OpenResourceFork(permissions);
}

void T2TemplatePlugin::CloseResourceFork() {
	#line 81
	ThrowIfNil_(mProgramPlugin);

	mProgramPlugin->CloseResourceFork();
}

Int32 T2TemplatePlugin::DrawGWorld(T2GWorld *gworld, Int16 var) {
	Int32 work = var;

	if (gworld) {
		work += 4;

		Rect src, dst;
		GrafPtr port;

		::GetPort(&port);
		gworld->GetBounds(src);
		::SetRect(&dst, 10, work, (src.right + 10) - src.left, (work + src.bottom) - src.top);
		gworld->CopyImage(port, src, dst, 0, 0);
		work += src.bottom - src.top;
	}

	return work;
}

void T2TemplatePlugin::DrawRect(const Rect &rect) {
	LStr255 tmp;

	tmp = (Int32) rect.top;
	::DrawString(tmp);

	::DrawString("\p, ");

	tmp = (Int32) rect.left;
	::DrawString(tmp);

	::DrawString("\p, ");

	tmp = (Int32) rect.bottom;
	::DrawString(tmp);

	::DrawString("\p, ");

	tmp = (Int32) rect.right;
	::DrawString(tmp);
}

void T2TemplatePlugin::DrawPoint(const Point &point) {
	LStr255 tmp;

	tmp = (Int32) point.v;
	::DrawString(tmp);

	::DrawString("\p, ");

	tmp = (Int32) point.h;
	::DrawString(tmp);
}

Boolean T2TemplatePlugin::HasDrawProc() const {
	Boolean result = false;

	if (mProgramPlugin)
		result = mProgramPlugin->HasDrawProc();

	return result;
}

Int32 T2TemplatePlugin::GetSortKey() {
	return 0;
}
