// MyFirstCoolTESTGame. All rights RESRVED!


#include "Components/FCGWeaponComponent.h"

#include "Player/FCTCharacter.h"

#include "Weapon/FCGBaseWeapon.h"
#include "GameFramework/Character.h"


// Sets default values for this component's properties
UFCGWeaponComponent::UFCGWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UFCGWeaponComponent::StartFire()
{
	if(!CurrentWeapon) return;

	CurrentWeapon->StartFire();
}

void UFCGWeaponComponent::EndFire()
{
	if(!CurrentWeapon) return;

	CurrentWeapon->EndFire();
}


// Called when the game starts
void UFCGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void UFCGWeaponComponent::SpawnWeapon()
{
	if(!GetWorld()) return;
	
	AFCTCharacter* WeaponOwner = Cast<AFCTCharacter>(GetOwner());
	if(!WeaponOwner) return;

	CurrentWeapon = GetWorld()->SpawnActor<AFCGBaseWeapon>(WeaponClass);

	if(!CurrentWeapon) return;
		
	CurrentWeapon->AttachToComponent(WeaponOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
		WeaponAttachPointName);

	CurrentWeapon->SetWeaponOwner(WeaponOwner);
	CurrentWeapon->SetOwner(GetOwner());
}

