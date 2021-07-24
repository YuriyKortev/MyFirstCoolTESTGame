// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "Pickups/FCTBasePickup.h"
#include "FCTAmmoPickup.generated.h"

class AFCGBaseWeapon;

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCTAmmoPickup : public AFCTBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta=(ClampMin="1.0", ClampMax="10.0"))
	int32 ClipsAmount = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta=(ClampMin="1.0", ClampMax="10.0"))
	TSubclassOf<AFCGBaseWeapon> WeaponType;
	
private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
