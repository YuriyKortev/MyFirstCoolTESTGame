// MyFirstCoolTESTGame. All rights RESRVED!


#include "Components/FCGWeaponComponent.h"

#include "Player/FCTCharacter.h"

#include "Weapon/FCGBaseWeapon.h"
#include "GameFramework/Character.h"

#include "Animations/FCTEquipFinishedAnimNotify.h"
#include "Animations/FCTChangeWeaponAnimNotify.h"
#include "Animations/FCTReloadAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

constexpr int32 WeaponNum = 2;

// Sets default values for this component's properties
UFCGWeaponComponent::UFCGWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UFCGWeaponComponent::StartFire()
{
	if(!GetWorld() || !IsReadyShoot()) return;
	Firing = true;
	CurrentWeapon->StartFire();
}

void UFCGWeaponComponent::EndFire()
{
	if(!CurrentWeapon) return;
	Firing = false;
	CurrentWeapon->EndFire();
}


// Called when the game starts
void UFCGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponClasses.Num() == WeaponNum, TEXT("Character should keep only %i weapons"), WeaponNum)
	
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

		Weapon->OnBulletsEmpty.AddUObject(this, &UFCGWeaponComponent::Reload);

		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, WeaponOwner->GetMesh(), ArmoryAttachPointName);
		
	}

}

void UFCGWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if(WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("Out of Weapons index"))
		return;
	}
	
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
	if(Equiping || CurrentWeapon->Reloading || Firing) return;
	
	Equiping = true;
	PlayAnimMontage(EquipAnimMontage);
}

void UFCGWeaponComponent::Reload() // TODO: Fix flags
{
	if(CurrentWeapon->ClipsAvailable() <= 0 || CurrentWeapon->IsFullAmmo()
		|| CurrentWeapon->Reloading || Equiping) return;
	
	CurrentWeapon->Reloading = true;
	Reloading = true;
	WeaponOwner->PlayAnimMontage(ReloadAnimMontage);
}

bool UFCGWeaponComponent::GetCurrentUIData(FWeaponUIData& OutUIData) const
{
	if(CurrentWeapon)
	{
		OutUIData = CurrentWeapon->GetUIData();
		return true;
	}else
	{
		return false;
	}
}

bool UFCGWeaponComponent::GetCurrentAmmoData(FAmmoData& OutAmmoData) const
{
	if(CurrentWeapon)
	{
		OutAmmoData = CurrentWeapon->GetCurrentAmmoData();
		return true;
	}else
	{
		return false;
	}
}

FString UFCGWeaponComponent::GetTextCurrentAmmo() const
{
	if(!CurrentWeapon) return "0 / 0";

	return CurrentWeapon->GetTextCurrentAmmo();
}

void UFCGWeaponComponent::AddCurrentWeaponClips(int32 ClipsAmount) const
{
	CurrentWeapon->TryAddClips(ClipsAmount);
}

bool UFCGWeaponComponent::TryToAddClipsTo(TSubclassOf<AFCGBaseWeapon> WeaponType, int32 ClipsAmount)
{
	for(const auto Weapon : Weapons)
	{
		if(Weapon && Weapon->IsA(WeaponType))
		{
			return Weapon->TryAddClips(ClipsAmount);
		}
	}
	return false;
}

float UFCGWeaponComponent::GetEquipingTime() const
{
	return EquipAnimMontage->GetPlayLength() * EquipAnimMontage->RateScale;
}

bool UFCGWeaponComponent::IsLastWeapon() const
{
	return CurrentWeaponIndex == Weapons.Num() - 1;
}

void UFCGWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage) const
{
	WeaponOwner->PlayAnimMontage(AnimMontage);
}

void UFCGWeaponComponent::InitAnimations()
{
	if(!EquipAnimMontage) return;
	
	const auto EquipNotifyEvents = EquipAnimMontage->Notifies;
	for(const auto NotifyEvent : EquipNotifyEvents)
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
	
	if(!ReloadAnimMontage) return;

	const auto ReloadNotifyEvents = ReloadAnimMontage->Notifies;
	for(auto NotifyEvent : ReloadNotifyEvents)
	{
		const auto ReloadFinishedNotify = Cast<UFCTReloadAnimNotify>(NotifyEvent.Notify);
		if(ReloadFinishedNotify)
		{
			ReloadFinishedNotify->OnNotified.AddUObject(this, &UFCGWeaponComponent::ReloadFinished);
		}
	}
}

void UFCGWeaponComponent::OnEquipFinished(USkeletalMeshComponent* Mesh)
{
	if(WeaponOwner->GetMesh() != Mesh) return;
	
	Equiping = false;
	
	UE_LOG(LogWeaponComponent, Display, TEXT("EquipFinished"))
}

void UFCGWeaponComponent::OnChangeWeapon(USkeletalMeshComponent* Mesh)
{
	if(WeaponOwner->GetMesh() != Mesh) return;

	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

bool UFCGWeaponComponent::IsReadyShoot() const
{
	return !Equiping && !CurrentWeapon->Reloading && !CurrentWeapon->IsAmmoEmpty();
}

void UFCGWeaponComponent::ReloadFinished(USkeletalMeshComponent* Mesh)
{
	Reloading = false;
	CurrentWeapon->OnReloadFinished(Mesh);
}

