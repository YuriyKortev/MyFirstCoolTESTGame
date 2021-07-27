// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FCTImpactFX.generated.h"

class UNiagaraComponent;
class UDecalComponent;
class USceneComponent;

UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCTImpactFX : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFCTImpactFX();

	void SetNiagaraVariable(FLinearColor& Variable);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Transform")
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	UNiagaraComponent* ImpactFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	UDecalComponent* DecalComponent;
};
