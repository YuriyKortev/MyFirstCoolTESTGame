// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FCTBasePickup.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPickupTaken)

class USphereComponent;

UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCTBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFCTBasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual  void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, Category="Pickups")
	USphereComponent* CollisionComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnPickupTaken OnPickupTaken;

private:
	float RotationYaw = 0.0f;
	
	virtual bool GivePickupTo(APawn* PlayerPawn);
	void GenerateRotationYaw();
};
