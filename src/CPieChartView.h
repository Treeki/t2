#pragma once

#include <LPane.h>

class CPieChartView : public LPane {
public:
	struct PieSlice {
		UInt32 value;
		RGBColor color;
	};

	struct Pie {
		UInt32 totalValue;
		UInt16 sliceCount;
		PieSlice *slices;
	};

	enum { class_ID = 'pie ' };

	static CPieChartView *CreateCPieChartViewStream(LStream *inStream);

	CPieChartView(LStream *inStream);
	~CPieChartView();
	void DrawSelf();
	void CutPie(const Pie *pie);

protected:
	ResIDT mTextTraits;
	Int16 mBorderWidth;
	const Pie *mPie;
};
