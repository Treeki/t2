#include "T23DCaption.h"
#include <LStream.h>
#include <UDrawingUtils.h>
#include <UGAColorRamp.h>
#include <UTextTraits.h>

T23DCaption *T23DCaption::CreateT23DCaptionStream(LStream *inStream) {
	return new T23DCaption(inStream);
}

T23DCaption::T23DCaption(LStream *inStream)
	: LCaption(inStream)
{
	inStream->ReadData(&mInverted, sizeof(mInverted));
}

void T23DCaption::DrawSelf() {
	Rect frame;
	CalcLocalFrameRect(frame);

	Int16 justification = UTextTraits::SetPortTextTraits(mTxtrID);

	RGBColor original;
	RGBColor grey = UGAColorRamp::GetColor(colorRamp_Gray7);
	RGBColor white = UGAColorRamp::GetWhiteColor();

	::GetForeColor(&original);

	ApplyForeAndBackColors();

	if (IsActive()) {
		::RGBForeColor(!mInverted ? &grey : &white);
		UTextDrawing::DrawWithJustification((Ptr) &mText[1], mText[0], frame, justification);

		::OffsetRect(&frame, 2, 2);

		::RGBForeColor(!mInverted ? &white : &grey);
		UTextDrawing::DrawWithJustification((Ptr) &mText[1], mText[0], frame, justification);

		::OffsetRect(&frame, -1, -1);
	} else {
		::OffsetRect(&frame, 1, 1);
	}

	::RGBForeColor(&original);
	UTextDrawing::DrawWithJustification((Ptr) &mText[1], mText[0], frame, justification);
}
