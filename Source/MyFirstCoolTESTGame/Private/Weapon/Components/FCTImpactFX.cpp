// MyFirstCoolTESTGame. All rights RESRVED!


#include "Weapon/Components/FCTImpactFX.h"
#include "NiagaraComponent.h"

// Sets default values
AFCTImpactFX::AFCTImpactFX()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ImpactFX = CreateDefaultSubobject<UNiagaraComponent>("ImpactFX");
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


