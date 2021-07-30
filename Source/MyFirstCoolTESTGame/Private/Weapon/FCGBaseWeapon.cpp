// MyFirstCoolTESTGame. All rights RESRVED!

#include "Weapon/FCGBaseWeapon.h"

#include "Engine/World.h"
#include "Player/FCTCharacter.h"

#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AFCGBaseWeapon::AFCGBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ShootDirection");
	ArrowComponent->SetupAttachment(GetRootComponent());
	
	MuzzleFXComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");
	MuzzleFXComponent->bAutoActivate = false;
	MuzzleFXComponent->bAutoManageAttachment = true;

	MuzzleFXComponent->SetAutoAttachmentParameters(GetRootComponent(), MuzzleSocketName,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget);
}

void AFCGBaseWeapon::StartFire()
{
	WantsFire = true;
	
	MuzzleFXComponent->Activate();
}

void AFCGBaseWeapon::EndFire()
{
	WantsFire = false;
	MuzzleFXComponent->Deactivate();
}

/*
void AFCGBaseWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(WeaponOwner->IsAim())
	{
		FVector TraceStart;
		FVector TraceEnd;

		if(!GetTraceData(TraceStart, TraceEnd)) return;

		FHitResult HitResult;
		MakeHit(HitResult, TraceStart, TraceEnd);
		
		if(HitResult.bBlockingHit)
		{
			FVector2D ScreenPosition;
			UGameplayStatics::ProjectWorldToScreen(GetPlayerController(), HitResult.ImpactPoint, ScreenPosition);

			AHUD* BaseHUD = GetPlayerController()->GetHUD();

			AFCGGameHUD* HUD = Cast<AFCGGameHUD, AHUD>(BaseHUD);

			if(HUD)
			{
				HUD->DrawCrossHair(ScreenPosition);
			}
		}
	}
}
*/

void AFCGBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	checkf(DefaultAmmoData.Bullets > 0, TEXT("Bullets can't be less or equal zero"))
	checkf(DefaultAmmoData.Clips > 0, TEXT("Clips can't be less or equal zero"))
	check(WeaponMesh);
	
	CurrentAmmoData = DefaultAmmoData;
}

void AFCGBaseWeapon::MakeShot()
{
	
}

FVector AFCGBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

void AFCGBaseWeapon::DecreaseAmmo()
{	
	CurrentAmmoData.Bullets--;
	LogAmmo();
}

/*
UNiagaraComponent* AFCGBaseWeapon::SpawnMuzzleFX() const
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX, //
		WeaponMesh, //
		MuzzleSocketName, //
		FVector::ZeroVector,//
		FRotator::ZeroRotator, //
		EAttachLocation::SnapToTarget, //
		true);
}
*/

bool AFCGBaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmoData.Infinite && CurrentAmmoData.Clips == 0 && IsClipEmpty();
}

bool AFCGBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmoData.Bullets == 0;
}

int32 AFCGBaseWeapon::ClipsAvailable() const
{
	return CurrentAmmoData.Clips;
}


void AFCGBaseWeapon::OnReloadFinished(USkeletalMeshComponent* Mesh)
{
	if(WeaponOwner->GetMesh() != Mesh) return;
	
	CurrentAmmoData.Bullets = DefaultAmmoData.Bullets;
	if(!CurrentAmmoData.Infinite)
	{
		CurrentAmmoData.Clips--;
	}
	Reloading=false;
}

void AFCGBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmoData.Bullets) + "/";
	AmmoInfo += CurrentAmmoData.Infinite ? "Infinite" : FString::FromInt(CurrentAmmoData.Clips);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo)
}

FString AFCGBaseWeapon::GetTextCurrentAmmo() const
{
	return FString::Printf(TEXT("%i / %i"), CurrentAmmoData.Bullets, CurrentAmmoData.Clips);
}

bool AFCGBaseWeapon::IsFullAmmo() const
{
	return CurrentAmmoData.Bullets == DefaultAmmoData.Bullets &&
		(CurrentAmmoData.Clips == DefaultAmmoData.Clips || CurrentAmmoData.Infinite);
}

bool AFCGBaseWeapon::TryAddClips(int32 ClipsAmount)
{
	if(IsFullAmmo() || CurrentAmmoData.Infinite) return false;
	CurrentAmmoData.Clips = FMath::Clamp(CurrentAmmoData.Clips + ClipsAmount, 0, DefaultAmmoData.Clips);
	return true;
}
