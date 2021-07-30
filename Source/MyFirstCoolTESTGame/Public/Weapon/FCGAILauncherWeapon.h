// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "Weapon/FCGLauncherWeapon.h"
#include "FCGAILauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCGAILauncherWeapon : public AFCGLauncherWeapon
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	float FireRate = 1.0;

	virtual void StartFire() override;
	virtual void EndFire() override;
	virtual void MakeShot() override;

private:
	FTimerHandle FireTimer;
};
