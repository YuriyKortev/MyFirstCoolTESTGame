// MyFirstCoolTESTGame. All rights RESRVED!


#include "AI/Tasks/FCTFireTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AI/FCTAICharacter.h"
#include "Components/FCGWeaponComponent.h"

UFCTFireTask::UFCTFireTask()
{
	NodeName = "Fire Task";
}

EBTNodeResult::Type UFCTFireTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if(!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	AIOwner = Cast<AFCTAICharacter>(Controller->GetPawn());
	if(!AIOwner) return EBTNodeResult::Failed;

	OwnersWeaponComponent = Pawn->FindComponentByClass<UFCGWeaponComponent>();

	if(OwnersWeaponComponent)
	{
		AIOwner->StartAim();
		OwnersWeaponComponent->StartFire();
		return EBTNodeResult::InProgress;
	}
	
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UFCTFireTask::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIOwner->EndAim();
	OwnersWeaponComponent->EndFire();
	
	return EBTNodeResult::Aborted;
}
