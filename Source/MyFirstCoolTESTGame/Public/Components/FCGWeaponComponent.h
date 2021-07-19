// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "FCGWeaponComponent.generated.h"

class AFCGBaseWeapon;
class AFCTCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTCOOLTESTGAME_API UFCGWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFCGWeaponComponent();

	void StartFire();
	void EndFire();
	void NextWeapon();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TArray<TSubclassOf<AFCGBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponAttachPointName = "Weapon";
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName ArmoryAttachPointName = "ArmorySocket";

	UPROPERTY()
	AFCTCharacter* WeaponOwner;

private:
	UPROPERTY()
	AFCGBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<AFCGBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	void AttachWeaponToSocket(AFCGBaseWeapon* Weapon, USceneComponent* Scene, const FName& SocketName);
	void SpawnWeapons();
	void EquipWeapon(int32 WeaponIndex);
};
