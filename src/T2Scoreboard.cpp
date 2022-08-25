#include "T2Scoreboard.h"
#include "T2ScoreData.h"
#include "UT2Coordinate.h"

#include <LStream.h>
#include <UDrawingState.h>
#include <UDrawingUtils.h>
#include <UTextTraits.h>

T2Scoreboard::T2Scoreboard(LStream *inStream)
	: LPane(inStream)
{
	mScoreData = 0;

	inStream->ReadData(&mMaxColumns, sizeof(mMaxColumns));
	inStream->ReadData(&mNameColWidth, sizeof(mNameColWidth));
	inStream->ReadData(&mScoreColWidth, sizeof(mScoreColWidth));
	inStream->ReadData(&mRunsColWidth, sizeof(mRunsColWidth));
	inStream->ReadData(&mHitsColWidth, sizeof(mHitsColWidth));
	inStream->ReadData(&mErrsColWidth, sizeof(mErrsColWidth));
	inStream->ReadData(&mRowHeight, sizeof(mRowHeight));
	inStream->ReadPString(mStr38);
	inStream->ReadPString(mStr144);
	inStream->ReadPString(mStr250);
	inStream->ReadData(&mTextTraits, sizeof(mTextTraits));
}

void T2Scoreboard::DrawSelf() {
	Rect frameRect;

	if (CalcLocalFrameRect(frameRect) && mScoreData) {
		StColorPenState state;
		state.Normalize();

		UTextTraits::SetPortTextTraits(mTextTraits);

		Point pt = topLeft(frameRect);
		DrawTitleRow(pt);

		pt.v += mRowHeight;
		DrawTeamScore(mScoreData, &mScoreData->mAwayTeam, pt);
		pt.v += mRowHeight;
		DrawTeamScore(mScoreData, &mScoreData->mHomeTeam, pt);
	}
}

void T2Scoreboard::SetScore(T2ScoreData *scoreData) {
	mScoreData = scoreData;

	Rect frameRect;
	if (CalcPortFrameRect(frameRect))
		InvalPortRect(&frameRect);
}

inline short _min(short a, short b) {
	return (a < b) ? a : b;
}

void T2Scoreboard::DrawTeamScore(const T2ScoreData *scoreData, const T2TeamScoreData *team, Point pt) const {
	if (!team)
		return;

	Point pt1 = pt;

	Rect rect;
	FontInfo fontInfo;
	::GetFontInfo(&fontInfo);

	// r26
	Int16 height = fontInfo.ascent + fontInfo.descent + fontInfo.leading;

	UT2Coordinate::MakeRect(rect, pt1, mNameColWidth, height);
	pt1.h += mNameColWidth;
	UTextDrawing::DrawWithJustification((Ptr) &team->mName[1], team->mName[0], rect, -2);

	if (!scoreData->mBallPlayed)
		return;

	Int32 innings;
	if (scoreData->mGameInProgress)
		innings = (scoreData->mHalfNum + (team->mIsPlaying ? 1 : 0)) / 2;
	else
		innings = scoreData->mInnings;

	Int32 cols = _min(mMaxColumns, innings);

	Point pt2 = pt1;

	for (int i = 0; i < cols; i++) {
		LStr255 str;
		if (!team->mIsPlaying && scoreData->mIsHomeTeamWinning && i == (scoreData->mInnings - 1) && team->mRuns[i] == 0) {
			str = 'X';
		} else {
			Int32 value /*r27*/ = team->mRuns[i];
			str = value;
			if (!team->mIsPlaying && scoreData->mIsHomeTeamWinning && i == (scoreData->mInnings - 1) && team->mRuns[i] < 10)
				str.Append('X');
		}

		UT2Coordinate::MakeRect(rect, pt2, mScoreColWidth, height);
		pt2.h += mScoreColWidth;
		UTextDrawing::DrawWithJustification((Ptr) &str[1], str[0], rect, -1, 1);
	}

	pt1.h += mScoreColWidth * mMaxColumns;

	if (mRunsColWidth != 0) {
		LStr255 str = (Int32) scoreData->GetTotalRuns(team);
		UT2Coordinate::MakeRect(rect, pt1, mRunsColWidth, height);
		pt1.h += mRunsColWidth;
		UTextDrawing::DrawWithJustification((Ptr) &str[1], str[0], rect, -1, 1);
	}

	if (mHitsColWidth != 0) {
		LStr255 str = (Int32) scoreData->GetTotalHits(team);
		UT2Coordinate::MakeRect(rect, pt1, mHitsColWidth, height);
		pt1.h += mHitsColWidth;
		UTextDrawing::DrawWithJustification((Ptr) &str[1], str[0], rect, -1, 1);
	}

	if (mErrsColWidth != 0) {
		LStr255 str = (Int32) scoreData->GetTotalErrs(team);
		UT2Coordinate::MakeRect(rect, pt1, mErrsColWidth, height);
		pt1.h += mErrsColWidth;
		UTextDrawing::DrawWithJustification((Ptr) &str[1], str[0], rect, -1, 1);
	}
}

void T2Scoreboard::DrawTitleRow(Point pt) const {
	Point pt1 = pt;
	Rect rect;
	FontInfo fontInfo;

	::GetFontInfo(&fontInfo);

	Int16 r29 = fontInfo.ascent + fontInfo.descent + fontInfo.leading;

	UT2Coordinate::MakeRect(rect, pt1, mNameColWidth, r29);

	pt1.h += mNameColWidth;
	rect.left -= fontInfo.widMax / 2;

	const LStr255 *whichStr; // r28
	if (mScoreData && mScoreData->mGameInProgress)
		whichStr = &mStr144;
	else if (mScoreData && mScoreData->mBallPlayed)
		whichStr = &mStr38;
	else
		whichStr = &mStr250;

	UTextDrawing::DrawWithJustification((Ptr) &(*whichStr)[1], (*whichStr) [0], rect, 1);

	for (Int32 i = 0; i < mMaxColumns; i++) {
		LStr255 str(i + 1);
		UT2Coordinate::MakeRect(rect, pt1, mScoreColWidth, r29);
		pt1.h += mScoreColWidth;
		UTextDrawing::DrawWithJustification((Ptr) &str[1], str[0], rect, 1);
	}

	if (mRunsColWidth) {
		LStr255 str('R');
		UT2Coordinate::MakeRect(rect, pt1, mRunsColWidth, r29);
		pt1.h += mRunsColWidth;
		UTextDrawing::DrawWithJustification((Ptr) &str[1], str[0], rect, 1);
	}

	if (mHitsColWidth) {
		LStr255 str('H');
		UT2Coordinate::MakeRect(rect, pt1, mHitsColWidth, r29);
		pt1.h += mHitsColWidth;
		UTextDrawing::DrawWithJustification((Ptr) &str[1], str[0], rect, 1);
	}

	if (mErrsColWidth) {
		LStr255 str('E');
		UT2Coordinate::MakeRect(rect, pt1, mErrsColWidth, r29);
		pt1.h += mErrsColWidth;
		UTextDrawing::DrawWithJustification((Ptr) &str[1], str[0], rect, 1);
	}
}
