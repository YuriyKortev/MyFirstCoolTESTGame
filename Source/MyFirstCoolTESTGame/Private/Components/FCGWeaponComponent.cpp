// MyFirstCoolTESTGame. All rights RESRVED!


#include "Components/FCGWeaponComponent.h"

#include "Player/FCTCharacter.h"

#include "Weapon/FCGBaseWeapon.h"
#include "GameFramework/Character.h"

#include "Animations/FCTEquipFinishedAnimNotify.h"
#include "Animations/FCTChangeWeaponAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)


// Sets default values for this component's properties
UFCGWeaponComponent::UFCGWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UFCGWeaponComponent::StartFire()
{
	if(!CurrentWeapon || !CanShoot) return;

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
	
	WeaponOwner = Cast<AFCTCharacter>(GetOwner());

	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
	InitAnimations();
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

void UFCGWeaponComponent::NextWeapon()
{
	if(Equiping) return;
	
	CanShoot = false;
	Equiping = true;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	PlayAnimMontage(EquipAnimMontage);
}

void UFCGWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage) const
{
	WeaponOwner->PlayAnimMontage(AnimMontage);
}

void UFCGWeaponComponent::InitAnimations()
{
	if(!EquipAnimMontage) return;
	
	const auto NotifyEvents = EquipAnimMontage->Notifies;
	for(auto NotifyEvent : NotifyEvents)
	{
		const auto EquipFinishedNotify = Cast<UFCTEquipFinishedAnimNotify>(NotifyEvent.Notify);
		const auto ChangeWeaponNotify = Cast<UFCTChangeWeaponAnimNotify>(NotifyEvent.Notify);
		if(EquipFinishedNotify)
		{
			EquipFinishedNotify->OnNotified.AddUObject(this, &UFCGWeaponComponent::OnEquipFinished);
		}
		if(ChangeWeaponNotify)
		{
			ChangeWeaponNotify->OnNotified.AddUObject(this, &UFCGWeaponComponent::OnChangeWeapon);
		}
	}
}

void UFCGWeaponComponent::OnEquipFinished(USkeletalMeshComponent* Mesh)
{
	if(WeaponOwner->GetMesh() != Mesh) return;
	
	CanShoot = true;
	Equiping = false;
	
	UE_LOG(LogWeaponComponent, Display, TEXT("EquipFinished"))
}

void UFCGWeaponComponent::OnChangeWeapon(USkeletalMeshComponent* Mesh)
{
	if(WeaponOwner->GetMesh() != Mesh) return;

	EquipWeapon(CurrentWeaponIndex);
}

