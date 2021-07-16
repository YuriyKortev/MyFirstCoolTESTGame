// MyFirstCoolTESTGame. All rights RESRVED!


#include "Weapon/FCGBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

// Sets default values
AFCGBaseWeapon::AFCGBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void AFCGBaseWeapon::Fire()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("FIRE"));
}

void AFCGBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


