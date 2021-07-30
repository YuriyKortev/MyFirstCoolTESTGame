// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EQC_FCTGetEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API UEQC_FCTGetEnemy : public UEnvQueryContext
{
	GENERATED_BODY()

public:
	
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FName EnemyActorKeyName = "EnemyActor";
};
