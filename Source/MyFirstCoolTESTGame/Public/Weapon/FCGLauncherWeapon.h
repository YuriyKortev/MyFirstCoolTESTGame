// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "Weapon/FCGBaseWeapon.h"
#include "FCGLauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCGLauncherWeapon : public AFCGBaseWeapon
{
	GENERATED_BODY()

protected:
	virtual void StartFire() override;	
	virtual void EndFire() override;	
	virtual void MakeShot() override;	
	
};
