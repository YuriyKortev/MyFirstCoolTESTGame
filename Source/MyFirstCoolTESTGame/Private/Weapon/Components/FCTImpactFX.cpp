// MyFirstCoolTESTGame. All rights RESRVED!


#include "Weapon/Components/FCTImpactFX.h"
#include "NiagaraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFCTImpactFX::AFCTImpactFX()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SceneComponent->Mobility = EComponentMobility::Static;
	SetRootComponent(SceneComponent);
	
	ImpactFX = CreateDefaultSubobject<UNiagaraComponent>("ImpactFX");
	ImpactFX->SetupAttachment(GetRootComponent());

	DecalComponent = CreateDefaultSubobject<UDecalComponent>("DecalComponent");
	DecalComponent->SetupAttachment(GetRootComponent());

	DecalComponent->DecalSize = FVector(10.0f);
	DecalComponent->FadeStartDelay = 5.0f;
	DecalComponent->FadeDuration = 0.7f;
	DecalComponent->bDestroyOwnerAfterFade = true;
}

void AFCTImpactFX::SetNiagaraVariable(FLinearColor& Variable)
{
	ImpactFX->SetColorParameter("UserColor", Variable);
}

// Called when the game starts or when spawned
void AFCTImpactFX::BeginPlay()
{
	Super::BeginPlay();
	
}


