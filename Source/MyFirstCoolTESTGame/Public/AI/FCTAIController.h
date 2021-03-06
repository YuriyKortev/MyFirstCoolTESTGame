// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FCTAIController.generated.h"

class UFCTAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCTAIController : public AAIController
{
	GENERATED_BODY()

public:
	AFCTAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UFCTAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKey = "EnemyActor";
	
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

private:
	AActor* GetFocusOnActor() const;
};
