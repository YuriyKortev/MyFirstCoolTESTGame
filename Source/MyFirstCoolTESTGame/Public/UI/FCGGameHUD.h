// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FCGGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCGGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

private:
	void DrawCrossHair();
	
};
