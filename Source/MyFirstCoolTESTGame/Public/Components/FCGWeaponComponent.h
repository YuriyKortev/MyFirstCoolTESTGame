// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/FCGBaseWeapon.h"

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
	void Reload();

	bool GetCurrentUIData(FWeaponUIData& OutUIData) const;
	bool GetCurrentAmmoData(FAmmoData& OutAmmoData) const;
	FString GetTextCurrentAmmo() const;

	void AddCurrentWeaponClips(int32 ClipsAmount) const;
	bool TryToAddClipsTo(TSubclassOf<AFCGBaseWeapon> WeaponType, int32 ClipsAmount);

	float GetEquipingTime() const;

	bool IsLastWeapon() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TArray<TSubclassOf<AFCGBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponAttachPointName = "Weapon";
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName ArmoryAttachPointName = "ArmorySocket";
	
	UPROPERTY(EditAnywhere, Category="Animation")
	UAnimMontage* EquipAnimMontage;
	
	UPROPERTY(EditAnywhere, Category="Animation")
	UAnimMontage* ReloadAnimMontage;

	UPROPERTY()
	AFCTCharacter* WeaponOwner;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Weapon")
	bool Equiping = false;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Weapon")
	bool Reloading = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Weapon")
	bool Firing = false;

private:
	UPROPERTY()
	AFCGBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<AFCGBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	void AttachWeaponToSocket(AFCGBaseWeapon* Weapon, USceneComponent* Scene, const FName& SocketName);
	void SpawnWeapons();
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* AnimMontage) const;
	void InitAnimations();

	void OnEquipFinished(USkeletalMeshComponent* Mesh);
	void OnChangeWeapon(USkeletalMeshComponent* Mesh);

	bool IsReadyShoot() const;

	void ReloadFinished(USkeletalMeshComponent* Mesh);
};
