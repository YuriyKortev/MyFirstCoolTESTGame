// MyFirstCoolTESTGame. All rights RESRVED!


#include "Player/FCTCharacter.h"

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
}

void AFCTCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AFCTCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void AFCTCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void AFCTCharacter::TurnAround(float Amount)
{
	AddControllerYawInput(Amount);
}

