#include "T2ScoreData.h"
#include "UT2Utils.h"

#include <LStream.h>
#include <string.h>

T2ScoreData::T2ScoreData()
	: mBallPlayed(false)
{
}

T2ScoreData::T2ScoreData(LStream &stream) {
	Load(stream);
}

void T2ScoreData::GetHomeTeamName(LString &str) {
	str = mHomeTeamName;
}

void T2ScoreData::SetHomeTeamName(const LString &str) {
	mHomeTeamName = str;
	SetScore();
}

void T2ScoreData::TeamsArrive() {
	SetScore();
	mGameInProgress = false;
	mBallPlayed = false;
}

void T2ScoreData::Playball() {
	mBallPlayed = true;
	mGameInProgress = true;
	mHalfNum = 0;
}

void T2ScoreData::GameSet() {
	mGameInProgress = false;
}

void T2ScoreData::Clear() {
	mGameInProgress = false;
	mBallPlayed = false;
	mAwayTeam.mName = mHomeTeam.mName = "";
}

Boolean T2ScoreData::SetHalfNum(UInt16 halfNum) {
	Boolean result = mHalfNum != halfNum;
	if (result)
		mHalfNum = halfNum;
	return result;
}

Boolean T2ScoreData::SetCurrentTime(UInt16 a, UInt16 b, UInt16 c) {
	Boolean result = false;

	if (mGameInProgress) {
		UInt16 val = mInnings * 2;
		if (mIsHomeTeamWinning && mHomeTeam.mRuns[mInnings - 1] == 0)
			val--;
		UInt16 halfNum = (val * (c - a)) / (b - a);
		result = SetHalfNum(halfNum);
	}

	return result;
}

UInt16 T2ScoreData::GetTotalRuns(const T2TeamScoreData *team) const {
	UInt16 result = 0;

	if (!mGameInProgress) {
		result = team->mTotalRuns;
	} else {
		int num = (mHalfNum + (team->mIsPlaying ? 1 : 0)) / 2;
		for (int i = 0; i < num; i++) {
			result += team->mRuns[i];
		}
	}

	return result;
}

UInt16 T2ScoreData::GetTotalHits(const T2TeamScoreData *team) const {
	UInt16 result = 0;

	if (!mGameInProgress) {
		result = team->mTotalHits;
	} else {
		int num = (mHalfNum + (team->mIsPlaying ? 1 : 0)) / 2;
		for (int i = 0; i < num; i++) {
			result += team->mHits[i];
		}
	}

	return result;
}

UInt16 T2ScoreData::GetTotalErrs(const T2TeamScoreData *team) const {
	UInt16 result = 0;

	if (!mGameInProgress) {
		result = team->mTotalErrs;
	} else {
		int num = (mHalfNum + (team->mIsPlaying ? 1 : 0)) / 2;
		for (int i = 0; i < num; i++) {
			result += team->mErrs[i];
		}
	}

	return result;
}

void T2ScoreData::GetRandomTeam(LStr255 &str, ConstStr255Param exceptFor) {
	ConstStringPtr options[7] = {
		"\pMileEnd",
		"\pRemmy's",
		"\pMatts",
		"\pYoot's",
		"\pScott's",
		"\pKoji's",
		"\pShinobu's"
	};

	do {
		str = options[UT2Utils::Randomize(7)];
	} while (exceptFor && str == exceptFor);
}

void T2ScoreData::SetScore() {
	GetRandomTeam(mAwayTeam.mName, mHomeTeamName.Length() ? (ConstStringPtr) mHomeTeamName : 0);
	if (mHomeTeamName.Length() != 0) {
		mHomeTeam.mName = mHomeTeamName;
	} else {
		GetRandomTeam(mHomeTeam.mName, mAwayTeam.mName);
	}

	mAwayTeam.mIsPlaying = true;
	mHomeTeam.mIsPlaying = false;

	mAwayTeam.mTotalRuns = mHomeTeam.mTotalRuns = 0;
	mAwayTeam.mTotalHits = mHomeTeam.mTotalHits = 0;
	mAwayTeam.mTotalErrs = mHomeTeam.mTotalErrs = 0;
	mInnings = 9;

	for (int i = 0; i < mInnings; i++) {
		SetInningScore(i);
	}

	if (mAwayTeam.mTotalRuns == mHomeTeam.mTotalRuns) {
		SetInningScore(mInnings);
		if (mAwayTeam.mTotalRuns == mHomeTeam.mTotalRuns) {
			mHomeTeam.mRuns[mInnings]++;
			mHomeTeam.mTotalRuns++;
			mHomeTeam.mHits[mInnings]++;
			mHomeTeam.mTotalHits++;
		}
		mInnings++;
	}

	mIsHomeTeamWinning = mAwayTeam.mTotalRuns < mHomeTeam.mTotalRuns;
}

void T2ScoreData::SetInningScore(UInt16 inning) {
	Int16 r29 = UT2Utils::Randomize(2) ? 10 : 3;
	Int16 r28 = UT2Utils::Randomize(2) ? 10 : 3;

	mAwayTeam.mRuns[inning] = (UT2Utils::Randomize(4) == 0) ? UT2Utils::Randomize(r29) : 0;
	mHomeTeam.mRuns[inning] = (UT2Utils::Randomize(4) == 0) ? UT2Utils::Randomize(r28) : 0;

	mAwayTeam.mTotalRuns += mAwayTeam.mRuns[inning];
	mHomeTeam.mTotalRuns += mHomeTeam.mRuns[inning];

	mAwayTeam.mHits[inning] = (UT2Utils::Randomize(3) * (mAwayTeam.mRuns[inning] + UT2Utils::Randomize(3)) / 2);
	mHomeTeam.mHits[inning] = (UT2Utils::Randomize(3) * (mHomeTeam.mRuns[inning] + UT2Utils::Randomize(3)) / 2);

	mAwayTeam.mTotalHits += mAwayTeam.mHits[inning];
	mHomeTeam.mTotalHits += mHomeTeam.mHits[inning];

	mAwayTeam.mErrs[inning] = (UT2Utils::Randomize(8) == 0) ? UT2Utils::Randomize(3) : 0;
	mHomeTeam.mErrs[inning] = (UT2Utils::Randomize(8) == 0) ? UT2Utils::Randomize(3) : 0;

	mAwayTeam.mTotalErrs += mAwayTeam.mErrs[inning];
	mHomeTeam.mTotalErrs += mHomeTeam.mErrs[inning];
}

void T2ScoreData::Load(LStream &stream) {
	Str255 s;
	stream >> s;
	mHomeTeamName = s;

	stream >> mBallPlayed;
	stream >> mInnings;
	LoadTeamScoreData(stream, mAwayTeam);
	LoadTeamScoreData(stream, mHomeTeam);
	stream >> mIsHomeTeamWinning;
	stream >> mGameInProgress;
	stream >> mHalfNum;
}

void T2ScoreData::LoadTeamScoreData(LStream &stream, T2TeamScoreData &team) {
	Str255 s;
	stream >> s;
	team.mName = s;

	stream >> team.mIsPlaying;
	for (int i = 0; i < 20; i++)
		stream >> team.mRuns[i];
	for (int i = 0; i < 20; i++)
		stream >> team.mHits[i];
	for (int i = 0; i < 20; i++)
		stream >> team.mErrs[i];
	stream >> team.mTotalRuns;
	stream >> team.mTotalHits;
	stream >> team.mTotalErrs;
}

void T2ScoreData::Save(LStream &stream) const {
	Int32 size = GetSaveDataSize();
	stream << size;

	Str255 s;
	memcpy(s, &mHomeTeamName[0], 256);
	stream << s;

	stream << mBallPlayed;
	stream << mInnings;
	SaveTeamScoreData(stream, mAwayTeam);
	SaveTeamScoreData(stream, mHomeTeam);
	stream << mIsHomeTeamWinning;
	stream << mGameInProgress;
	stream << mHalfNum;
}

void T2ScoreData::SaveTeamScoreData(LStream &stream, const T2TeamScoreData &team) const {
	Str255 s;
	memcpy(s, &team.mName[0], 256);
	stream << s;

	stream << team.mIsPlaying;
	for (int i = 0; i < 20; i++)
		stream << team.mRuns[i];
	for (int i = 0; i < 20; i++)
		stream << team.mHits[i];
	for (int i = 0; i < 20; i++)
		stream << team.mErrs[i];
	stream << team.mTotalRuns;
	stream << team.mTotalHits;
	stream << team.mTotalErrs;
}

Int32 T2ScoreData::GetSaveDataSize() {
	return 0x405;
}
