// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"

#include "Components/FCGWeaponComponent.h"
#include "GameFramework/Character.h"
#include "FCTCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UFCGHealthComponent;
class UTextRenderComponent;
class UAnimMontage;
class UFCGWeaponComponent;


UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFCTCharacter();
	
	void StartAim();
	void EndAim();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UFCGHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* DeathAnimMontage;
	
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	UFCGWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement")
	bool WantsAim = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxWalkSpeed = 600.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxRunSpeed = 1000.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxCrouchSpeed = 250.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxAimSpeed = 250.0f;

	bool IsAlreadyDead = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsAim() const;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void LookUp(float Amount);
	void TurnAround(float Amount);

	void StartRun();
	void EndRun();
	
	void StartCrouch();
	void EndCrouch();
	
	void OnDeath();
	void OnHealthChanged(float Health);

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);

};

