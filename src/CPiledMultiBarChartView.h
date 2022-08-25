#pragma once

#include <LPane.h>

class CPiledMultiBarChartView : public LPane {
public:
	struct GraphData {
		short piles, bars;
		int *data;
	};

	enum { class_ID = 'pmbc' };

	static CPiledMultiBarChartView *CreateCPiledMultiBarChartViewStream(LStream *inStream);

	CPiledMultiBarChartView(LStream *inStream);
	~CPiledMultiBarChartView();
	void DrawSelf();
	void SetGraphData(const GraphData *graphData);
	void SetPixelPerValue(Int32 value, Boolean refresh);
	void SetColorOfPiles(short count, const RGBColor *colors, Boolean refresh);

protected:
	Boolean mSkipDrawing;
	Int16 mPiles, mBars, mBarWidth, mBarInterval, mXOffset, mLines, mLineInterval, mLineLength;
	long mPixelPerValue;
	RGBColor *mColorOfPiles;
	const GraphData *mGraphData;
};
