// MyFirstCoolTESTGame. All rights RESRVED!


#include "Weapon/FCGLauncherWeapon.h"
#include "Weapon/FCTProjectile.h"
#include "Kismet/GameplayStatics.h"

void AFCGLauncherWeapon::StartFire()
{
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

	auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
	// set params

	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}
