// MyFirstCoolTESTGame. All rights RESRVED!


#include "Pickups/FCTAmmoPickup.h"
#include "Components/FCGHealthComponent.h"
#include "Components/FCGWeaponComponent.h"

#include "FCTUtils.h"

bool AFCTAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = FCTUtils::GetFCTPlayerComponent<UFCGHealthComponent>(PlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = FCTUtils::GetFCTPlayerComponent<UFCGWeaponComponent>(PlayerPawn);
	if(!WeaponComponent) return false;
	
	return WeaponComponent->TryToAddClipsTo(WeaponType, ClipsAmount);;
}
