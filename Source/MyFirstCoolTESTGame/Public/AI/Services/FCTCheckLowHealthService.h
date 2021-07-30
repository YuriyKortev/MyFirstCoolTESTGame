// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FCTCheckLowHealthService.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API UFCTCheckLowHealthService : public UBTService
{
	GENERATED_BODY()
		
public:
	UFCTCheckLowHealthService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	FBlackboardKeySelector LowHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float HealthPercentThreshold;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
