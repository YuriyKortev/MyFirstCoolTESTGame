// MyFirstCoolTESTGame. All rights RESRVED!


#include "Pickups/FCTHealthPickup.h"
#include "Components/FCGHealthComponent.h"
#include "FCTUtils.h"

bool AFCTHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = FCTUtils::GetFCTPlayerComponent<UFCGHealthComponent>(PlayerPawn);
	if(HealthComponent && HealthComponent->TryAddHealth(HealthRestore))
	{
		return true;
	}
	return false;
}
