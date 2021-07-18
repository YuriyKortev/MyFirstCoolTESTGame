// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FCGBaseWeapon.generated.h"

class USkeletalMeshComponent;
class AFCTCharacter;

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AFCGBaseWeapon();

	virtual void StartFire();
	virtual void EndFire();

	void SetWeaponOwner(AFCTCharacter* NewOwner) { WeaponOwner = NewOwner; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditAnywhere, Category="Animation")
	UAnimMontage* FireAnimMontage;

	UPROPERTY()
	AFCTCharacter* WeaponOwner;

	bool WantsFire=false;

	virtual void BeginPlay() override;

	virtual void MakeShot();
	
	FVector GetMuzzleWorldLocation() const;
};
