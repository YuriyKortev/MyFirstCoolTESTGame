// MyFirstCoolTESTGame. All rights RESRVED!


#include "Pickups/FCTPickupFactory.h"
#include "Pickups/FCTBasePickup.h"

// Sets default values
AFCTPickupFactory::AFCTPickupFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AFCTPickupFactory::BeginPlay()
{
	Super::BeginPlay();
	CreatePickup();
}

void AFCTPickupFactory::CreatePickup()
{
	const FVector PickupLocation = GetActorLocation();
	const FTransform PickupTransform = FTransform(FRotator::ZeroRotator, PickupLocation);
	const auto Pickup = GetWorld()->SpawnActor<AFCTBasePickup>(PickupClass, PickupTransform);
	
	Pickup->OnPickupTaken.AddUObject(this, &AFCTPickupFactory::CreatePickupLater);
}

void AFCTPickupFactory::CreatePickupLater()
{
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AFCTPickupFactory::CreatePickup,Delay);
}

