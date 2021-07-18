// MyFirstCoolTESTGame. All rights RESRVED!


#include "UI/FCGGameHUD.h"

//#include "../../../../../../Epic Games/UE_4.26/Engine/Shaders/Private/ScreenSpaceDenoise/SSDPublicHarmonics.ush"
#include "Engine/Canvas.h"

void AFCGGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void AFCGGameHUD::DrawCrossHair(const FVector2D& DrawPoint)
{
	const float HalfLineSize = 10.0f;
	const float LineThikness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;

	DrawLine(DrawPoint.X - HalfLineSize, DrawPoint.Y, DrawPoint.X + HalfLineSize,
		DrawPoint.Y, LineColor, LineThikness);
	
	DrawLine(DrawPoint.X, DrawPoint.Y - HalfLineSize, DrawPoint.X,
		DrawPoint.Y + HalfLineSize, LineColor, LineThikness);
}

void AFCGGameHUD::DrawCrossHair()
{
	const FVector2D Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
	DrawCrossHair(Center);
}
