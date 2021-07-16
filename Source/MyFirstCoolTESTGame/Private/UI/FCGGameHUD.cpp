// MyFirstCoolTESTGame. All rights RESRVED!


#include "UI/FCGGameHUD.h"
#include "Engine/Canvas.h"

void AFCGGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void AFCGGameHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

	const float HalfLineSize = 10.0f;
	const float LineThikness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize,
		Center.Max, LineColor, LineThikness);
	
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min,
		Center.Max + HalfLineSize, LineColor, LineThikness);
}
