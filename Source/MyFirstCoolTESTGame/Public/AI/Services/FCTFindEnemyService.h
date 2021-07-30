// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FCTFindEnemyService.generated.h"



/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API UFCTFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UFCTFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
