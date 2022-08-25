#include "T2BufferedFileStream.h"
#include <UMemoryMgr.h>

T2BufferedFileStream::T2BufferedFileStream(const FSSpec &spec)
	: LFile(spec)
{
	mBuffer = ::NewPtrClear(0x20000);
	#line 42
	ThrowIfNil_(mBuffer);

	SetLength(0x10000);
	mInternalBuffer = true;
	mTotalSize = 0;
	mEndian = 1;
	mReadSoFar = 0;
	mReadRemain = 0;
	mHasDataInFile = false;
}

T2BufferedFileStream::T2BufferedFileStream(const FSSpec &spec, Ptr buffer, Int32 length)
	: LFile(spec)
{
	mBuffer = buffer;
	#line 65
	ThrowIfNil_(mBuffer);

	SetLength(length);
	mInternalBuffer = false;
	mTotalSize = 0;
	mEndian = 1;
	mReadSoFar = 0;
	mReadRemain = 0;
	mHasDataInFile = false;
}

T2BufferedFileStream::~T2BufferedFileStream() {
	if (mInternalBuffer && mBuffer)
		::DisposePtr((Ptr) mBuffer);
}

ExceptionCode T2BufferedFileStream::PutBytes(const void *buffer, Int32 &length) {
	ExceptionCode code = 0;
	Int32 writeAmount;
	Byte cvbuf[4];
	Byte tmp;

	if (length + GetMarker() > 0x10000) {
		writeAmount = GetMarker();
		code = ::FSWrite(GetDataForkRefNum(), &writeAmount, mBuffer);
		if (code != noErr)
			return code;
		mTotalSize += writeAmount;
		SetMarker(0, streamFrom_Start);
	}

	if (!code && length > 1 && !mEndian) {
		if (length == 2) {
			*((UInt16 *) cvbuf) = *((const UInt16 *) buffer);
			tmp = cvbuf[0];
			cvbuf[0] = cvbuf[1];
			cvbuf[1] = tmp;
			code = LDataStream::PutBytes(cvbuf, length);
		} else if (length == 4) {
			*((UInt32 *) cvbuf) = *((const UInt32 *) buffer);
			tmp = cvbuf[0];
			cvbuf[0] = cvbuf[3];
			cvbuf[3] = tmp;
			tmp = cvbuf[1];
			cvbuf[1] = cvbuf[2];
			cvbuf[2] = tmp;
			code = LDataStream::PutBytes(cvbuf, length);
		} else {
			code = LDataStream::PutBytes(buffer, length);
		}
	} else {
		code = LDataStream::PutBytes(buffer, length);
	}

	return code;
}

ExceptionCode T2BufferedFileStream::Flush() {
	Int32 length = GetMarker();
	ExceptionCode code = ::FSWrite(GetDataForkRefNum(), &length, mBuffer);
	if (code != noErr)
		return code;

	mTotalSize += length;
	SetMarker(0, streamFrom_Start);
	return code;
}

ExceptionCode T2BufferedFileStream::GetBytes(void *buffer, Int32 &length) {
	ExceptionCode code;

	if (!mHasDataInFile) {
		code = GetFileInfo();
		if (code != noErr)
			return code;
	}

	if (length > mReadSoFar - GetMarker()) {
		// read more data
		Int32 amount = mReadSoFar - GetMarker();
		if (amount > 0)
			::BlockMoveData((Ptr) mBuffer + GetMarker(), mBuffer, amount);

		Int32 toRead = (mReadRemain > (0x10000 - amount)) ? (0x10000 - amount) : mReadRemain;
		if (toRead <= 0)
			#line 185
			ThrowIfOSErr_(eofErr);
		code = ::FSRead(GetDataForkRefNum(), &toRead, (Ptr) mBuffer + amount);
		if (code != noErr)
			return code;

		mTotalSize += toRead;
		mReadSoFar = amount + toRead;
		mReadRemain -= toRead;
		SetMarker(0, streamFrom_Start);
	}

	code = LDataStream::GetBytes(buffer, length);
	if (code == noErr && length > 1 && !mEndian) {
		Byte tmp;
		Byte *p = (Byte *) buffer;
		if (length == 2) {
			tmp = p[0];
			p[0] = p[1];
			p[1] = tmp;
		} else if (length == 4) {
			tmp = p[0];
			p[0] = p[3];
			p[3] = tmp;
			tmp = p[1];
			p[1] = p[2];
			p[2] = tmp;
		}
	}

	return code;
}

ExceptionCode T2BufferedFileStream::GetFileInfo() {
	ExceptionCode code;

	code = ::GetEOF(GetDataForkRefNum(), &mReadRemain);
	if (code != noErr)
		return code;

	Int32 toRead = (mReadRemain > 0x10000) ? 0x10000 : mReadRemain;
	code = ::FSRead(GetDataForkRefNum(), &toRead, GetBufferEnd());
	mTotalSize += toRead;
	mReadSoFar = toRead;
	mReadRemain -= toRead;
	mHasDataInFile = true;
	return code;
}

Int32 T2BufferedFileStream::Write2ByteDataArrayHandle(Int16 **handle) {
	Int32 totalSize = 0;

	if (handle) {
		Int32 size = ::GetHandleSize((Handle) handle);
		*this << size;

		StHandleLocker locker((Handle) handle);
		Int16 *ptr = *handle;
		for (int i = 0; i < (size / 2); i++) {
			Int32 elementLength = 2;
			PutBytes(ptr++, elementLength);
		}

		totalSize = size;
	} else {
		*this << (Int32) -1;
	}

	return totalSize + 4;
}

Int32 T2BufferedFileStream::Write4ByteDataArrayHandle(Int32 **handle) {
	Int32 totalSize = 0;

	if (handle) {
		Int32 size = ::GetHandleSize((Handle) handle);
		*this << size;

		StHandleLocker locker((Handle) handle);
		Int32 *ptr = *handle;
		for (int i = 0; i < (size / 4); i++) {
			Int32 elementLength = 4;
			PutBytes(ptr++, elementLength);
		}

		totalSize = size;
	} else {
		*this << (Int32) -1;
	}

	return totalSize + 4;
}

Int32 T2BufferedFileStream::Read2ByteDataArrayHandle(Handle &handle) {
	Int32 totalSize = 0;

	handle = 0;

	Int32 size;
	*this >> size;

	if (size != -1) {
		StHandleBlock block(size);
		StHandleLocker locker(block);
		Int16 *ptr = (Int16 *) *block.mHandle;

		for (int i = 0; i < (size / 2); i++) {
			Int32 elementLength = 2;
			GetBytes(ptr++, elementLength);
		}

		totalSize = size;
		handle = block.mHandle;
		block.mHandle = 0;
	}

	return totalSize + 4;
}

Int32 T2BufferedFileStream::Read4ByteDataArrayHandle(Handle &handle) {
	Int32 totalSize = 0;

	handle = 0;

	Int32 size;
	*this >> size;

	if (size != -1) {
		StHandleBlock block(size);
		StHandleLocker locker(block);
		Int32 *ptr = (Int32 *) *block.mHandle;

		for (int i = 0; i < (size / 4); i++) {
			Int32 elementLength = 4;
			GetBytes(ptr++, elementLength);
		}

		totalSize = size;
		handle = block.mHandle;
		block.mHandle = 0;
	}

	return totalSize + 4;
}

Byte T2BufferedFileStream::GetEndian() {
	return mEndian;
}
