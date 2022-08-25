#pragma once

#include <PP_Types.h>

class LStream;
class T2TowerDoc;

class T2DateTime {
//protected:
public:
	UInt16 mYear, mMonth, mHourMinute, mX;

public:
	T2DateTime();
	T2DateTime(UInt16 year, UInt16 day, UInt16 hour, UInt16 minute, UInt16 x);
	T2DateTime(LStream &stream);
	virtual ~T2DateTime();
	int GetTimeZone();

	static Boolean IsEqualDate(T2DateTime *a, T2DateTime *b);
	static Boolean IsEqualDateTime(T2DateTime *a, T2DateTime *b);

	UInt16 GetYear() const { return mYear; }
	UInt16 GetQuarter() const { return mMonth / 3 + 1; }
	UInt16 GetSeason() const { return mMonth / 3 + 1; }
	UInt16 GetDay() const { return mMonth % 3 + 1; }
	UInt16 GetMonth() const { return mMonth + 1; }
	UInt16 GetHour() const { return (mHourMinute % 720) / 60; }
	UInt16 Get24Hour() const { return mHourMinute / 60; }
	UInt16 GetMinutes() const { return mHourMinute % 60; }
	UInt16 GetRawMinutes() const { return mHourMinute; }
	Int32 CalcTotalDays() const { return (mYear - 1) * 12 + mMonth; }
	Boolean IsWeekday(T2TowerDoc *doc) { return !IsHoliday(doc); }
	Boolean IsDay() const {
		return (mHourMinute >= 360) && (mHourMinute < 1080);
	}
	Boolean IsMidNight() const { return mHourMinute < 360; }
	// Boolean IsOclock24() const { ... }

	void AddMinutes(UInt16 num);
	Boolean IsIncDateTime();
	void IncDate();
	UInt32 CalcLapseDays(UInt32 num) const;
	UInt32 CalcLapseYears(UInt32 num) const;
	Boolean WithinHour(Int16 lo, Int16 hi) const;
	Boolean WithinMinutes(Int16 lo, Int16 hi) const;

protected:
	Int16 AdjustMinutes(Int16 num) const;

	UInt16 CalcTotalCount() const {
		return mX + ((mYear * 12 + mMonth) * 1440 + mHourMinute) * 4;
	}

public:
	void Write(LStream &stream);
	Boolean IsHoliday(T2TowerDoc *doc);

	void Validate();
};
