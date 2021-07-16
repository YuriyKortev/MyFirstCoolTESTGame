// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FCGWeaponComponent.generated.h"

class AFCGBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTCOOLTESTGAME_API UFCGWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFCGWeaponComponent();

	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<AFCGBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponAttachPointName = "Weapon";

private:
	UPROPERTY()
	AFCGBaseWeapon* CurrentWeapon = nullptr;
	
	void SpawnWeapon();
};
