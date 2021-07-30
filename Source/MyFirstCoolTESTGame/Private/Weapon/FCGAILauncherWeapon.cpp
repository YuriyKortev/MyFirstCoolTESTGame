// MyFirstCoolTESTGame. All rights RESRVED!


#include "Weapon/FCGAILauncherWeapon.h"

void AFCGAILauncherWeapon::StartFire()
{
	AFCGBaseWeapon::StartFire();
	
	GetWorldTimerManager().SetTimer(FireTimer, this, &AFCGAILauncherWeapon::MakeShot, FireRate, true);

}

void AFCGAILauncherWeapon::EndFire()
{
	Super::EndFire();
	GetWorldTimerManager().ClearTimer(FireTimer);
}

void AFCGAILauncherWeapon::MakeShot()
{
	Super::MakeShot();
}

