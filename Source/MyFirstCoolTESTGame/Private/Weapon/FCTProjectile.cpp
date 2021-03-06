// MyFirstCoolTESTGame. All rights RESRVED!


#include "Weapon/FCTProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/FCTWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFCTProjectile::AFCTProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	SphereComponent->InitSphereRadius(5.0f);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SetRootComponent(SphereComponent);

	ProjectileFX = CreateDefaultSubobject<UNiagaraComponent>("ProjectileFX");
	ProjectileFX->SetupAttachment(GetRootComponent());

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");

	WeaponFXComponent = CreateDefaultSubobject<UFCTWeaponFXComponent>("WeaponFXComponent");

}

void AFCTProjectile::BeginPlay()
{
	Super::BeginPlay();
	check(SphereComponent);
	check(ProjectileMovement);
	check(WeaponFXComponent);
	
	ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;

	SphereComponent->OnComponentHit.AddDynamic(this, &AFCTProjectile::OnCollision);

	SetLifeSpan(LifeTime);
}

void AFCTProjectile::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(!GetWorld()) return;

	ProjectileMovement->StopMovementImmediately();

	WeaponFXComponent->PlayImpactFX(Hit);
	
	// add damage
	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageValue, GetActorLocation(), DamageRadius,
		UDamageType::StaticClass(), {GetOwner()}, this, GetController(), DoFullDamage);

	/*DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24,
		FColor::Red, false, 5.0f);*/
	
	Destroy();
}

AController* AFCTProjectile::GetController() const
{
	const auto Player= Cast<APawn>(GetOwner());

	return Player ? Player->GetController() : nullptr;
}



