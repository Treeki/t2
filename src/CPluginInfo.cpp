#include "CPluginInfo.h"

CPluginInfo *CPluginInfo::ReadPluginInfo(LStream &stream) {
	CPluginInfo *info;

	info = new CPluginInfo;
	info->Read(stream);

	return info;
}

CPluginInfo::CPluginInfo() {
	_00 = 0;
	_04 = 0;
	_08 = 0;
	_0A = 0;
	name[0] = 0;
	fileName[0] = 0;
	_14C = 0;
}

CPluginInfo::CPluginInfo(UInt32 _00, UInt32 _04, short _08, short _0A, Byte *name, Byte *fileName, Byte _14C) {
	this->_00 = _00;
	this->_04 = _04;
	this->_08 = _08;
	this->_0A = _0A;
	LString::CopyPStr(name, this->name, 255);
	LString::CopyPStr(fileName, this->fileName, 63);
	this->_14C = _14C;
}

CPluginInfo::~CPluginInfo() {
}

void CPluginInfo::GetName(StringPtr str) {
	LString::CopyPStr(name, str, 255);
}

void CPluginInfo::GetFileName(StringPtr str) {
	LString::CopyPStr(fileName, str, 255);
}

void CPluginInfo::Read(LStream &stream) {
	stream >> _00;
	stream >> _04;
	stream >> _08;
	stream >> _0A;
	stream >> name;

	Byte fileNameLen;
	stream >> fileNameLen;
	fileName[0] = fileNameLen;
	for (int i = 1; i <= fileNameLen; i++) {
		stream >> fileName[i];
	}

	stream >> _14C;
}

void CPluginInfo::Write(LStream &stream) {
	stream << _00;
	stream << _04;
	stream << _08;
	stream << _0A;
	stream << name;

	Byte length = fileName[0];
	for (int i = 0; i <= length; i++) {
		stream << fileName[i];
	}

	stream << _14C;
}
