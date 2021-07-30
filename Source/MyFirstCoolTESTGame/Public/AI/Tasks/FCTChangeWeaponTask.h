// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FCTChangeWeaponTask.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API UFCTChangeWeaponTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UFCTChangeWeaponTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
	FBlackboardKeySelector EquipingTime;
};
