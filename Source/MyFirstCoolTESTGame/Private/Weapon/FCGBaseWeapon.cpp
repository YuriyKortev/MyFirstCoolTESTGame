// MyFirstCoolTESTGame. All rights RESRVED!

#include "Engine/World.h"
#include "Weapon/FCGBaseWeapon.h"

#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

#include "Components/SkeletalMeshComponent.h"

#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

// Sets default values
AFCGBaseWeapon::AFCGBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void AFCGBaseWeapon::Fire()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("FIRE"));
	MakeShot();
}

void AFCGBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
}

void AFCGBaseWeapon::MakeShot()
{
	if(!GetWorld()) return;

	// const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	FVector TraceStart;
	FVector TraceEnd;

	if(!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if(HitResult.bBlockingHit)
	{
		UE_LOG(LogBaseWeapon, Display, TEXT("Hitted: %s"), *HitResult.BoneName.ToString());
		
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);

		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);

		MakeDamage(HitResult);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
		
}

APlayerController* AFCGBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if(!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool AFCGBaseWeapon::GetPlayerViewPoint(FRotator& Rotator, FVector& Location) const
{
	const auto Controller = GetPlayerController();
	if(!Controller) return false;
	Controller->GetPlayerViewPoint(Location, Rotator);
	return true;
}

FVector AFCGBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool AFCGBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FRotator ViewRotation;
	FVector ViewLocation;

	if(!GetPlayerViewPoint(ViewRotation, ViewLocation)) return false;
	
	TraceStart = GetMuzzleWorldLocation(); // ViewLocation
	const FVector ShootDirection = ViewRotation.Vector(); // SocketTransform.GetRotation().GetForwardVector();
	
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	
	return true;
}

void AFCGBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
		CollisionQueryParams);
}


void AFCGBaseWeapon::MakeDamage(const FHitResult& HitResult) const
{
	const auto HitActor = HitResult.GetActor();
	if(!HitActor) return;
	
	HitActor->TakeDamage(Damage, FDamageEvent{}, GetPlayerController(), GetOwner());
}


