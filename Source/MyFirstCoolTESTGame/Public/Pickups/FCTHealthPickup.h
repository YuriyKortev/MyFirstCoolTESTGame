// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "Pickups/FCTBasePickup.h"
#include "FCTHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCTHealthPickup : public AFCTBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Pickup")
	float HealthRestore=50.0f;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
	
};
