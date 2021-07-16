// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FCGBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AFCGBaseWeapon();

	virtual void Fire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Damage = 30.0f;

	virtual void BeginPlay() override;

	void MakeShot();
	
	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FRotator& Rotator, FVector& Location) const;
	FVector GetMuzzleWorldLocation() const;
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
	
	void MakeDamage(const FHitResult& HitResult) const;
};
