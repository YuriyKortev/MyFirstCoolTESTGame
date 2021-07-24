// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FCTPickupFactory.generated.h"

class AFCTBasePickup;

UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCTPickupFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFCTPickupFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Pickups")
	TSubclassOf<AFCTBasePickup> PickupClass;

	UPROPERTY(EditDefaultsOnly, Category="Pickups")
	float Delay=10.0f;

	FTimerHandle SpawnTimer;
	
private:
	void CreatePickup();
	
	void CreatePickupLater();
};
