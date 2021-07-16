// MyFirstCoolTESTGame. All rights RESRVED!


#include "Components/FCGWeaponComponent.h"

#include "Weapon/FCGBaseWeapon.h"
#include "GameFramework/Character.h"


// Sets default values for this component's properties
UFCGWeaponComponent::UFCGWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UFCGWeaponComponent::Fire()
{
	if(!CurrentWeapon) return;

	CurrentWeapon->Fire();
}


// Called when the game starts
void UFCGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	
}

void UFCGWeaponComponent::SpawnWeapon()
{
	if(!GetWorld()) return;
	
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if(!Owner) return;

	CurrentWeapon = GetWorld()->SpawnActor<AFCGBaseWeapon>(WeaponClass);

	if(!CurrentWeapon) return;
		
	CurrentWeapon->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
		WeaponAttachPointName);
	CurrentWeapon->SetOwner(GetOwner());
}

