#pragma once

#include <LArray.h>
#include <LStream.h>

class T2MovieParamArray : public LArray {
public:
	T2MovieParamArray();
	~T2MovieParamArray();

	Boolean Regist(UInt32 id, Int32 param);
	Int32 GetParam(UInt32 id);

	static T2MovieParamArray *ReadMovieParamArray(LStream &stream);
	static void WriteMovieParamArray(T2MovieParamArray *array, LStream &stream);

	virtual void Read(LStream &stream);
	virtual void Write(LStream &stream);
};
