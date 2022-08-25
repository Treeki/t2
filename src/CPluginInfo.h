#pragma once

#include <LStream.h>
#include <LString.h>

class CPluginInfo {
public:
	UInt32 _00, _04;
	short _08, _0A;
	Str255 name;
	Str63 fileName;
	Byte _14C;

	static CPluginInfo *ReadPluginInfo(LStream &stream);

	CPluginInfo();
	CPluginInfo(UInt32 _00, UInt32 _04, short _08, short _0A, Byte *name, Byte *fileName, Byte _14C);
	virtual ~CPluginInfo();

	void GetName(StringPtr str);
	void GetFileName(StringPtr str);
	void Read(LStream &stream);
	void Write(LStream &stream);
};

