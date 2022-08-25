#pragma once

#include <PP_Types.h>
#include <LString.h>

class LStream;

struct T2TeamScoreData {
	LStr255 mName;
	Boolean mIsPlaying;
	UInt16 mRuns[20];
	UInt16 mHits[20];
	UInt16 mErrs[20];
	UInt16 mTotalRuns;
	UInt16 mTotalHits;
	UInt16 mTotalErrs;
};

class T2ScoreData {
public:
	T2ScoreData();
	T2ScoreData(LStream &stream);
	void GetHomeTeamName(LString &str);
	void SetHomeTeamName(const LString &str);
	void TeamsArrive();
	void Playball();
	void GameSet();
	void Clear();
	Boolean SetHalfNum(UInt16 halfNum);
	Boolean SetCurrentTime(UInt16 a, UInt16 b, UInt16 c);
	UInt16 GetTotalRuns(const T2TeamScoreData *team) const;
	UInt16 GetTotalHits(const T2TeamScoreData *team) const;
	UInt16 GetTotalErrs(const T2TeamScoreData *team) const;
	void GetRandomTeam(LStr255 &str, ConstStr255Param exceptFor);
	void SetScore();
	void SetInningScore(UInt16 inning);
	void Load(LStream &stream);
	void LoadTeamScoreData(LStream &stream, T2TeamScoreData &team);
	void Save(LStream &stream) const;
	void SaveTeamScoreData(LStream &stream, const T2TeamScoreData &team) const;
	static Int32 GetSaveDataSize();

	LStr255 mHomeTeamName;
	Boolean mBallPlayed;
	UInt16 mInnings;
	T2TeamScoreData mAwayTeam;
	T2TeamScoreData mHomeTeam;
	Boolean mIsHomeTeamWinning;
	Boolean mGameInProgress;
	UInt16 mHalfNum;
};
