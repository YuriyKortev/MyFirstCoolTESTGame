// MyFirstCoolTESTGame. All rights RESRVED!


#include "Player/FCTCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Camera/CameraComponent.h"

#include "Components/InputComponent.h"
#include "Components/FCGHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/FCGWeaponComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY_STATIC(LogMainCharacter, All, All)

// Sets default values
AFCTCharacter::AFCTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UFCGHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());

	WeaponComponent = CreateDefaultSubobject<UFCGWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void AFCTCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &AFCTCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AFCTCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &AFCTCharacter::OnGroundLanded);
}

// Called every frame
void AFCTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFCTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFCTCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFCTCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AFCTCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &AFCTCharacter::TurnAround);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFCTCharacter::StartRun);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFCTCharacter::EndRun);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFCTCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AFCTCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UFCGWeaponComponent::Fire);
	
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AFCTCharacter::StartAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AFCTCharacter::EndAim);
}

void AFCTCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
	/*
	if ((Controller != nullptr) && (AxisValue != 0.0f))
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
	*/
}

void AFCTCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
	/*
	if ((Controller != nullptr) && (AxisValue != 0.0f))
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement in that direction
		AddMovementInput(Direction, AxisValue);
	}
	*/
}

void AFCTCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void AFCTCharacter::TurnAround(float Amount)
{
	AddControllerYawInput(Amount);
}

void AFCTCharacter::EndRun()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

void AFCTCharacter::StartCrouch()
{
	Crouch();
}

void AFCTCharacter::EndCrouch()
{
	UnCrouch();
}

void AFCTCharacter::StartAim()
{
	WantsAim = true;
	GetCharacterMovement()->MaxWalkSpeed = MaxAimSpeed;
}

void AFCTCharacter::EndAim()
{
	WantsAim = false;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

void AFCTCharacter::OnDeath()
{
	UE_LOG(LogMainCharacter, Display, TEXT("Character %s is dead"), *GetName())

	if(IsAlreadyDead) return;
	IsAlreadyDead = true;
	
	PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);

	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AFCTCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}


void AFCTCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;

	UE_LOG(LogMainCharacter, Display, TEXT("Landed: %f"), FallVelocityZ);

	if(FallVelocityZ < LandedDamage.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage,
		FallVelocityZ);

	UE_LOG(LogMainCharacter, Display, TEXT("Final Damage: %f"), FinalDamage);

	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void AFCTCharacter::StartRun()
{
	if(WantsAim) return;
	GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
}


