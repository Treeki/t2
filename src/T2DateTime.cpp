#include "T2DateTime.h"
#include "T2TowerDoc.h"
#include "T2WorldPlugin.h"

#include <LStream.h>

T2DateTime::T2DateTime() {
	mYear = 0;
	mMonth = 0;
	mHourMinute = 0;
	mX = 0;
}

T2DateTime::T2DateTime(UInt16 year, UInt16 day, UInt16 hour, UInt16 minute, UInt16 x) {
	mYear = year;
	mMonth = day;
	mHourMinute = hour * 60 + minute;
	mX = x;
}

T2DateTime::T2DateTime(LStream &stream) {
	stream >> mYear;
	stream >> mMonth;
	stream >> mHourMinute;
	stream >> mX;
}

T2DateTime::~T2DateTime() {
}

int T2DateTime::GetTimeZone() {
	short hour = mHourMinute / 60;

	if (hour < 2)
		return 0;
	else if (hour < 6)
		return 1;
	else if (hour < 9)
		return 2;
	else if (hour < 10)
		return 3;
	else if (hour < 12)
		return 4;
	else if (hour < 13)
		return 5;
	else if (hour < 15)
		return 6;
	else if (hour < 18)
		return 7;
	else if (hour < 22)
		return 8;
	else
		return 9;
}

Boolean T2DateTime::IsEqualDate(T2DateTime *a, T2DateTime *b) {
	return a->mYear == b->mYear && a->mMonth == b->mMonth;
}

Boolean T2DateTime::IsEqualDateTime(T2DateTime *a, T2DateTime *b) {
	return IsEqualDate(a, b) && a->mHourMinute == b->mHourMinute;
}

void T2DateTime::AddMinutes(UInt16 num) {
	mHourMinute += num;
	Validate();
}

Boolean T2DateTime::IsIncDateTime() {
	Boolean result = false;

	mX++;
	if (mX >= 4) {
		result = true;
		mX = 0;
		mHourMinute++;
		if (mHourMinute >= (60 * 24)) {
			mMonth++;
			mHourMinute -= (60 * 24);
		}
		if (mMonth >= 12) {
			mYear++;
			mMonth -= 12;
		}
	}

	return result;
}

void T2DateTime::IncDate() {
	mMonth++;
	if (mMonth >= 12) {
		mYear++;
		mMonth -= 12;
	}
}

UInt32 T2DateTime::CalcLapseDays(UInt32 num) const {
	return (mMonth + ((mYear - 1) * 12)) - num;
}

UInt32 T2DateTime::CalcLapseYears(UInt32 num) const {
	return ((mMonth + ((mYear - 1) * 12)) - num) / 12;
}

Boolean T2DateTime::WithinHour(Int16 lo, Int16 hi) const {
	return WithinMinutes(lo * 60, hi * 60);
}

Boolean T2DateTime::WithinMinutes(Int16 lo, Int16 hi) const {
	Boolean result = true;
	Int16 adjLo = AdjustMinutes(lo);
	Int16 adjHi = AdjustMinutes(hi);
	if (adjLo < adjHi) {
		if (mHourMinute < adjLo || mHourMinute >= adjHi)
			result = false;
	} else if (adjLo > adjHi) {
		if (mHourMinute >= adjHi && mHourMinute < adjLo)
			result = false;
	}
	return result;
}

Int16 T2DateTime::AdjustMinutes(Int16 num) const {
	Int16 result = num;
	if (result < 0)
		result += (60 * 24);
	else if (result >= (60 * 24))
		result -= (60 * 24);
	return result;
}

void T2DateTime::Write(LStream &stream) {
	stream << mYear;
	stream << mMonth;
	stream << mHourMinute;
	stream << mX;
}

Boolean T2DateTime::IsHoliday(T2TowerDoc *doc) {
	T2WorldPlugin *plugin = doc->GetWorldPlugin();
	return plugin->IsHoliday(this);
}

void T2DateTime::Validate() {
	mHourMinute += (mX / 4);
	mX %= 4;

	mMonth += (mHourMinute / (60 * 24));
	mHourMinute %= (60 * 24);

	mYear += (mMonth / 12);
	mMonth %= 12;
}
