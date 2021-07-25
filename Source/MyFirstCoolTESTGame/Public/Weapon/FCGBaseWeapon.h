// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FCGBaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnBulletsEmpty)

class USkeletalMeshComponent;
class AFCTCharacter;
class UArrowComponent;

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Ammo")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Ammo", meta=(EditCondition =  "!Infinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Ammo")
	bool Infinite;
	
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	UTexture2D* CrossHairIcon;
};

UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AFCGBaseWeapon();

	virtual void StartFire();
	virtual void EndFire();
	
	void OnReloadFinished(USkeletalMeshComponent* Mesh);
	
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	int32 ClipsAvailable() const;
	void LogAmmo();

	FString GetTextCurrentAmmo() const;

	bool IsFullAmmo() const;

	FWeaponUIData GetUIData() const { return UIData; }
	FAmmoData GetCurrentAmmoData() const { return CurrentAmmoData; }

	void SetWeaponOwner(AFCTCharacter* NewOwner) { WeaponOwner = NewOwner; }
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ammo")
	bool Reloading = false;

	FOnBulletsEmpty OnBulletsEmpty;

	bool TryAddClips(int32 ClipsAmount);


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Ammo")
	FAmmoData DefaultAmmoData{25, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	FWeaponUIData UIData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, Category="Ammo")
	UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditAnywhere, Category="Animation")
	UAnimMontage* FireAnimMontage;

	AFCTCharacter* WeaponOwner;

	bool WantsFire=false;

	virtual void BeginPlay() override;

	virtual void MakeShot();
	
	FVector GetMuzzleWorldLocation() const;

	void DecreaseAmmo();

private:
	FAmmoData CurrentAmmoData;
};
