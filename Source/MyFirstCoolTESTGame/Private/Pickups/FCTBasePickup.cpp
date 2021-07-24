// MyFirstCoolTESTGame. All rights RESRVED!


#include "Pickups/FCTBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All)

// Sets default values
AFCTBasePickup::AFCTBasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void AFCTBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFCTBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	GivePickupTo(Pawn);
	
	OnPickupTaken.Broadcast();
	Destroy();
}

// Called every frame
void AFCTBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AFCTBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

