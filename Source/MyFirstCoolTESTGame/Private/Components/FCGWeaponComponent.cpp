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

void UFCGWeaponComponent::NextWeapon()
{
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}


// Called when the game starts
void UFCGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponOwner = Cast<AFCTCharacter>(GetOwner());

	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void UFCGWeaponComponent::AttachWeaponToSocket(AFCGBaseWeapon* Weapon, USceneComponent* Scene, const FName& SocketName)
{
	if(!Weapon || !Scene) return;
	Weapon->AttachToComponent(Scene, FAttachmentTransformRules::SnapToTargetIncludingScale,
		SocketName);
}

void UFCGWeaponComponent::SpawnWeapons()
{
	if(!GetWorld() || !WeaponOwner) return;

	for(const auto WeaponClass : WeaponClasses)
	{
		const auto Weapon = GetWorld()->SpawnActor<AFCGBaseWeapon>(WeaponClass);

		if(!Weapon) continue;
		Weapon->SetWeaponOwner(WeaponOwner);
		Weapon->SetOwner(GetOwner());

		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, WeaponOwner->GetMesh(), ArmoryAttachPointName);
		
	}

}

void UFCGWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if(!WeaponOwner) return;

	if(CurrentWeapon)
	{
		CurrentWeapon->EndFire();
		AttachWeaponToSocket(CurrentWeapon, WeaponOwner->GetMesh(), ArmoryAttachPointName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, WeaponOwner->GetMesh(), WeaponAttachPointName);
}

