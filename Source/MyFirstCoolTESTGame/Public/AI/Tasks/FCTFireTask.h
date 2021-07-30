// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FCTFireTask.generated.h"

class UFCGWeaponComponent;
class AFCTAICharacter;

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API UFCTFireTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFCTFireTask();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UFCGWeaponComponent* OwnersWeaponComponent;
	AFCTAICharacter* AIOwner;

};
