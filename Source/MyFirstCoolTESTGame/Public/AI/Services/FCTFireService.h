// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"

#include "FCTFireService.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API UFCTFireService : public UBTService
{
	GENERATED_BODY()

public:
	UFCTFireService();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector EnemyActorKey;
	
};
