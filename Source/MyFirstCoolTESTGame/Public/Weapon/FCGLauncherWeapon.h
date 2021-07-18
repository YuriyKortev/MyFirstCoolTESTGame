// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"

#include "FCTProjectile.h"
#include "Weapon/FCGBaseWeapon.h"
#include "FCGLauncherWeapon.generated.h"

class AFCTProjectile;

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCGLauncherWeapon : public AFCGBaseWeapon
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Ammo")
	TSubclassOf<AFCTProjectile> ProjectileClass;
	
	virtual void StartFire() override;	
	virtual void EndFire() override;	
	virtual void MakeShot() override;	
	
};
