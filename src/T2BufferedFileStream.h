#pragma once

#include <LDataStream.h>
#include <LFile.h>

class T2BufferedFileStream : public LFile, public LDataStream {
public:
	T2BufferedFileStream(const FSSpec &spec);
	T2BufferedFileStream(const FSSpec &spec, Ptr buffer, Int32 length);
	~T2BufferedFileStream();

	virtual Byte GetEndian();
	virtual void SetEndian(Byte endian) { mEndian = endian; }
	virtual Int32 GetTotalSize() { return mTotalSize; }
	virtual ExceptionCode PutBytes(const void *buffer, Int32 &length);
	virtual ExceptionCode Flush();
	virtual ExceptionCode GetBytes(void *buffer, Int32 &length);
	virtual Int32 Write2ByteDataArrayHandle(Int16 **handle);
	virtual Int32 Write4ByteDataArrayHandle(Int32 **handle);
	virtual Int32 Read2ByteDataArrayHandle(Handle &handle);
	virtual Int32 Read4ByteDataArrayHandle(Handle &handle);
	virtual ExceptionCode GetFileInfo();

	void *GetBufferEnd() {
		return (Ptr) mBuffer + GetMarker();
	}

protected:
	Boolean mInternalBuffer;
	Int32 mTotalSize;
	Byte mEndian;
	Boolean mHasDataInFile;
	Int32 mReadSoFar;
	Int32 mReadRemain;
};

/*
                             __vt__20T2BufferedFileStream                    XREF[1]:     101e7840(*)
        102123ec 10 21 23 e4     addr       PTR_s_T2BufferedFileStream_102123e4              = 10212371
        102123f0 00              ??         00h
        102123f4 10 1e e4 dc     addr       PTR___dt__20T2BufferedFileStreamFv               = 1009631c
        102123f8 10 1e bf 54     addr       PTR_SetSpecifier__5LFileFRC6FSSpec               = 10043d94
			  10
        102123fc 10 1e bf 44     addr       PTR_MakeAlias__5LFileFP6FSSpec                   = 10043ec0
        10212400 10 1e bf 3c     addr       PTR_CreateNewFile__5LFileFUlUls                  = 10043f34
        10212404 10 1e bf 34     addr       PTR_CreateNewDataFile__5LFileFUlUls              = 10044060
        10212408 10 1e bf 2c     addr       PTR_OpenDataFork__5LFileFs                       = 10044194
			  20
        1021240c 10 1e bf 24     addr       PTR_CloseDataFork__5LFileFv                      = 100442b8
        10212410 10 1e bf 14     addr       PTR_ReadDataFork__5LFileFv                       = 1004440c
        10212414 10 1e bf 0c     addr       PTR_WriteDataFork__5LFileFPCvl                   = 10044704
        10212418 10 1e bf 04     addr       PTR_OpenResourceFork__5LFileFs                   = 100448d0
			  30
        1021241c 10 1e be fc     addr       PTR_CloseResourceFork__5LFileFv                  = 10044a04
		[LFile End]
        10212420 10 21 23 e4     addr       PTR_s_T2BufferedFileStream_102123e4              = 10212371
        10212424 ff              ??         FFh
        10212428 10 1e e4 74     addr       PTR_@80@__dt__20T2BufferedFileStreamFv           = 1009710c
			  40
        1021242c 10 1e cd 6c     addr       PTR_SetMarker__7LStreamFl11EStreamFrom           = 10069930
        10212430 10 1e cd 64     addr       PTR_GetMarker__7LStreamCFv                       = 10069a44
        10212434 10 1e cd 5c     addr       PTR_SetLength__7LStreamFl                        = 10069a78
        10212438 10 1e cd 54     addr       PTR_GetLength__7LStreamCFv                       = 10069b3c
			  50
        1021243c 10 1e e4 8c     addr       PTR_@80@PutBytes__20T2BufferedFileStreamFPCvRl   = 10097104
        10212440 10 1e e4 94     addr       PTR_@80@GetBytes__20T2BufferedFileStreamFPvRl    = 100970fc
        10212444 10 1e bf 84     addr       PTR_ReadData__7LStreamFPvl                       = 100374b4
        10212448 10 1e e4 7c     addr       PTR_SetBuffer__11LDataStreamFPvl                 = 10097044
			  60
        1021244c 10 1e e4 84     addr       PTR_GetBuffer__11LDataStreamFv                   = 100970c4
		[LDataStream end]
        10212450 10 1e e4 5c     addr       PTR_GetEndian__20T2BufferedFileStreamFv          = 10097004
        10212454 10 1e e4 64     addr       PTR_SetEndian__20T2BufferedFileStreamFUc         = 1006037c
        10212458 10 1e e4 6c     addr       PTR_GetTotalSize__20T2BufferedFileStreamFv       = 10060338
			  70
        1021245c 10 1e e4 d4     addr       PTR_PutBytes__20T2BufferedFileStreamFPCvRl       = 100963f8
        10212460 10 1e e4 cc     addr       PTR_Flush__20T2BufferedFileStreamFv              = 100965ec
        10212464 10 1e e4 c4     addr       PTR_GetBytes__20T2BufferedFileStreamFPvRl        = 100966d0
        10212468 10 1e e4 b4     addr       PTR_Write2ByteDataArrayHandle__20T2BufferedFil   = 10096af4
			  80
        1021246c 10 1e e4 ac     addr       PTR_Write4ByteDataArrayHandle__20T2BufferedFil   = 10096c2c
        10212470 10 1e e4 a4     addr       PTR_Read2ByteDataArrayHandle__20T2BufferedFile   = 10096d64
        10212474 10 1e e4 9c     addr       PTR_Read4ByteDataArrayHandle__20T2BufferedFile   = 10096eb4
        10212478 10 1e e4 bc     addr       PTR_GetFileInfo__20T2BufferedFileStreamFv        = 100969bc
*/
