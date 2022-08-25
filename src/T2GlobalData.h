#pragma once

#include <LString.h>
#include "T2MovieParamArray.h"

class T2GlobalData {
protected:
	UInt32 _0;
	Boolean mMovieRegistered;
	UInt32 _8;
	T2MovieParamArray *mMovieParamArray;
	char mSerial[16];
	UInt32 _20;

public:
	T2GlobalData();
	virtual ~T2GlobalData();
	void GetSerialString(LStr255 &str);
	void RegistMovie(UInt32 id, Int32 param);
	Int32 GetMovieParam(UInt32 id);
	void Read(LStream &stream);
	void Write(LStream &stream);
	Boolean IsCheckSerial();
	Boolean Check_Product();
	Boolean Check_Serial(char *serial);
};
