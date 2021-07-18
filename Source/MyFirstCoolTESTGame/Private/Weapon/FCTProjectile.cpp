// MyFirstCoolTESTGame. All rights RESRVED!


#include "Weapon/FCTProjectile.h"
#include "Components/SphereComponent.h"

// Sets default values
AFCTProjectile::AFCTProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	SphereComponent->InitSphereRadius(5.0f);
	SetRootComponent(SphereComponent);

}

void AFCTProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


