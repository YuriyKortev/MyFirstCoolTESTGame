// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "FCTProjectile.generated.h"

class USphereComponent;
class UFCTWeaponFXComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;

UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCTProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AFCTProjectile();

	void SetShootDirection(const FVector& Direction){ ShootDirection = Direction; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	UFCTWeaponFXComponent* WeaponFXComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	UNiagaraComponent* ProjectileFX;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Movement")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	float LifeTime = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	float DamageRadius = 200.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	float DamageValue = 50.f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Damage")
	bool DoFullDamage = false;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnCollision(UPrimitiveComponent* HitComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

private:
	FVector ShootDirection;

	AController* GetController() const;

};
