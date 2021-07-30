// MyFirstCoolTESTGame. All rights RESRVED!


#include "Weapon/FCGRifleWeapon.h"
#include "Player/FCTCharacter.h"
#include "Weapon/Components/FCTWeaponFXComponent.h"

#include "DrawDebugHelpers.h"

AFCGRifleWeapon::AFCGRifleWeapon()
{
	ImpactFXComponent = CreateDefaultSubobject<UFCTWeaponFXComponent>("WeaponFXComponent");
}

void AFCGRifleWeapon::StartFire()
{
	if(Reloading) return;
	
	Super::StartFire();

	switch (FireType)
	{
	case EFireType::Auto:
		MakeShot();
		GetWorldTimerManager().SetTimer(FireTimer, this, &AFCGRifleWeapon::MakeShot, FireRate, true);
		break;
	case EFireType::Burst:
		MakeShot();
		GetWorldTimerManager().SetTimer(FireTimer, this, &AFCGRifleWeapon::MakeShot, FireRate, true);
		break;
	case EFireType::SingleShot:
		MakeShot();
		break;
	default:
		MakeShot();
	}
}

void AFCGRifleWeapon::EndFire()
{
	Super::EndFire();
	GetWorldTimerManager().ClearTimer(FireTimer);
	ShootNum=0;
}

void AFCGRifleWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(ImpactFXComponent);
}

void AFCGRifleWeapon::MakeShot()
{
	Super::MakeShot();
/*
	if(IsClipEmpty() && !IsAmmoEmpty())
	{
		if(FirstBulletsEmpty)
		{
			EndFire();
			FirstBulletsEmpty=false;
			return;
		}
		FirstBulletsEmpty=true;
		EndFire();
		OnBulletsEmpty.Broadcast();
		return;
	}*/

	if(IsClipEmpty())
	{
		EndFire();
		return;
	}
	
	if(FireType == EFireType::Burst && ShootNum > NumOfShotsInBurst)
		return;
	else if(FireType == EFireType::Burst)
		ShootNum++;
	
	WeaponOwner->PlayAnimMontage(FireAnimMontage);

	// const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	FVector TraceStart;
	FVector TraceEnd;

	if(!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if(HitResult.bBlockingHit)
	{
		// UE_LOG(LogBaseWeapon, Display, TEXT("Hitted: %s"), *HitResult.BoneName.ToString());
		
		// DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);

		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
		ImpactFXComponent->PlayImpactFX(HitResult);
		
		MakeDamage(HitResult);
	}
	else
	{
		// DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}

	DecreaseAmmo();
}

APlayerController* AFCGRifleWeapon::GetPlayerController() const
{
	return WeaponOwner->GetController<APlayerController>();
}

bool AFCGRifleWeapon::GetPlayerViewPoint(FRotator& Rotator, FVector& Location) const
{
	const auto FCTCharacter = Cast<ACharacter>(GetOwner());
	if(!FCTCharacter) return false;

	if(FCTCharacter->IsPlayerControlled())
	{
		const auto Controller = GetPlayerController();
		if(!Controller) return false;
		
		Controller->GetPlayerViewPoint(Location, Rotator);
	}else
	{
		Location = GetMuzzleWorldLocation();
		// Rotator = WeaponMesh->GetSocketRotation(MuzzleSocketName);
		Rotator = GetOwner()->GetActorRotation(); // TODO: Change correct direction
	}
	
	return true;
}

bool AFCGRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FRotator ViewRotation;
	FVector ViewLocation;

	if(!GetPlayerViewPoint(ViewRotation, ViewLocation)) return false;
	
	TraceStart = ViewLocation; // GetMuzzleWorldLocation(); 

	const FVector ShootDirection = WeaponOwner->IsAim() ?
		ViewRotation.Vector() : FMath::VRandCone(ViewRotation.Vector(), HipFireAccuracy);
	
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	
	return true;
}

void AFCGRifleWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
		CollisionQueryParams);
}


void AFCGRifleWeapon::MakeDamage(const FHitResult& HitResult) const
{
	const auto HitActor = HitResult.GetActor();
	if(!HitActor) return;
	
	HitActor->TakeDamage(SingleBulletDamage, FDamageEvent{}, GetPlayerController(), GetOwner());
}

