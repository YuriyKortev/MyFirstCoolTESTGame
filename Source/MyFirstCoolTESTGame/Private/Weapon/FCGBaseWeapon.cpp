// MyFirstCoolTESTGame. All rights RESRVED!

#include "Engine/World.h"
#include "Weapon/FCGBaseWeapon.h"
#include "Player/FCTCharacter.h"

#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

#include "Components/SkeletalMeshComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AFCGBaseWeapon::AFCGBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void AFCGBaseWeapon::StartFire()
{
	WantsFire = true;
}

void AFCGBaseWeapon::EndFire()
{
	WantsFire = false;
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
	check(WeaponMesh);
}

void AFCGBaseWeapon::MakeShot()
{
		
}

