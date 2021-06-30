// MyFirstCoolTESTGame. All rights RESRVED!


#include "Components/FCGHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
UFCGHealthComponent::UFCGHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UFCGHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();

	if(ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UFCGHealthComponent::OnTakeAnyDamageHandle);
	}
}

void UFCGHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{

	if(Damage <= 0.0f || IsDead())
	{
		// UE_LOG(LogHealthComponent, Display, TEXT("Damage < 0 or already death"))
		return;
	}
	
	SetHealth(Health - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	} else if(AutoRecovery && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(RecoveryTimer, this, &UFCGHealthComponent::OnRecoveryIter,
			RecoveryRate, true, RecoveryDelay);
	}

	
}

void UFCGHealthComponent::OnRecoveryIter()
{
	SetHealth(Health + RecoveryStep);
	if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(RecoveryTimer);
	}
}

void UFCGHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}
