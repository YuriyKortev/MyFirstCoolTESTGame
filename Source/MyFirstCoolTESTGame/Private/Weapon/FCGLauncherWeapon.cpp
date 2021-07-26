// MyFirstCoolTESTGame. All rights RESRVED!


#include "Weapon/FCGLauncherWeapon.h"
#include "Weapon/FCTProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"

void AFCGLauncherWeapon::StartFire()
{
	if(IsClipEmpty())
	{
		OnBulletsEmpty.Broadcast();
		return;
	}
	
	Super::StartFire();
	MakeShot();
}

void AFCGLauncherWeapon::EndFire()
{
	Super::EndFire();
	
}

void AFCGLauncherWeapon::MakeShot()
{
	Super::MakeShot();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());

	auto Projectile = GetWorld()->SpawnActorDeferred<AFCTProjectile>(ProjectileClass, SpawnTransform);
	
	if(Projectile)
	{
		Projectile->SetShootDirection(ArrowComponent->GetForwardVector());
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
	
	DecreaseAmmo();
}
