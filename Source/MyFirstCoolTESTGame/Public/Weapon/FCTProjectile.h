// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FCTProjectile.generated.h"

class USphereComponent;

UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCTProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AFCTProjectile();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	USphereComponent* SphereComponent;
	
	virtual void BeginPlay() override;

public:	

};
