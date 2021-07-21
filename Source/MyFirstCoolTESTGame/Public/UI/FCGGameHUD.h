// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FCGGameHUD.generated.h"


UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCGGameHUD : public AHUD
{
	GENERATED_BODY()

private:
public:
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;

	void DrawCrossHair(const FVector2D& DrawPoint);
	void DrawCrossHair();

	void DrawAimCollision(FVector& Point, float Distance) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> PlayerHudWidgetClass;
};
