// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FCTNextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API UFCTNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFCTNextLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Radius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector AimLocationKey;
	
};
