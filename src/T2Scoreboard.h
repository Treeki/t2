#pragma once

#include <LPane.h>
#include <LString.h>

class LStream;
class T2ScoreData;
struct T2TeamScoreData;

class T2Scoreboard : public LPane {
public:
	T2Scoreboard(LStream *inStream);
	void DrawSelf();
	void SetScore(T2ScoreData *scoreData);
	void DrawTeamScore(const T2ScoreData *scoreData, const T2TeamScoreData *team, Point pt) const;
	void DrawTitleRow(Point pt) const;

protected:
	UInt16 mMaxColumns;
	UInt16 mNameColWidth;
	UInt16 mScoreColWidth;
	UInt16 mRunsColWidth;
	UInt16 mHitsColWidth;
	UInt16 mErrsColWidth;
	UInt16 mRowHeight;
	LStr255 mStr38;
	LStr255 mStr144;
	LStr255 mStr250;
	ResIDT mTextTraits;
	T2ScoreData *mScoreData;
};
