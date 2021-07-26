// MyFirstCoolTESTGame. All rights RESRVED!


#include "Weapon/Components/FCTWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Weapon/Components/FCTImpactFX.h"

// Sets default values for this component's properties
UFCTWeaponFXComponent::UFCTWeaponFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UFCTWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UFCTWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	
	const FTransform SpawnTransform(Hit.ImpactNormal.Rotation(), Hit.ImpactPoint);

	auto Impact = GetWorld()->SpawnActorDeferred<AFCTImpactFX>(ImpactClass, SpawnTransform);
	
	auto Color = DefaultColor;
	if(Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if(EffectsMap.Contains(PhysMat))
		{
			Color = EffectsMap[PhysMat];
		}
	}
	
	if(Impact)
	{
		Impact->SetNiagaraVariable(Color);
		Impact->FinishSpawning(SpawnTransform);
	}
}

