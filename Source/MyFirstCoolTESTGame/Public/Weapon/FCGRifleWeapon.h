// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "Weapon/FCGBaseWeapon.h"
#include "FCGRifleWeapon.generated.h"

UENUM(BlueprintType)
enum class EFireType : uint8
{
	Auto,
	SingleShot,
	Burst,
	TypesNum
};

UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCGRifleWeapon : public AFCGBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void EndFire() override;

protected:
	virtual void BeginPlay() override;

	virtual void MakeShot() override;

	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	float SingleBulletDamage = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	EFireType FireType = EFireType::Auto;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	float FireRate = 0.066f; // 14.16f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	int32 NumOfShotsInBurst = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	float HipFireAccuracy = 1.5f;

	FTimerHandle FireTimer;
	int32 ShootNum=0;

	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FRotator& Rotator, FVector& Location) const;
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
	
	void MakeDamage(const FHitResult& HitResult) const;
};
