// MyFirstCoolTESTGame. All rights RESRVED!


#include "Player/FCTCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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
}

// Called when the game starts or when spawned
void AFCTCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
}

void AFCTCharacter::MoveForward(float AxisValue)
{
	// AddMovementInput(GetActorForwardVector(), AxisValue);
	
	if ((Controller != nullptr) && (AxisValue != 0.0f))
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
	
}

void AFCTCharacter::MoveRight(float AxisValue)
{
	// AddMovementInput(GetActorRightVector(), Amount);
	
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
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AFCTCharacter::StartCrouch()
{
	Crouch();
}

void AFCTCharacter::EndCrouch()
{
	UnCrouch();
}

inline void AFCTCharacter::StartRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 1000;
}

