// MyFirstCoolTESTGame. All rights RESRVED!


#include "AI/Tasks/FCTChangeWeaponTask.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/FCGWeaponComponent.h"

UFCTChangeWeaponTask::UFCTChangeWeaponTask()
{
	NodeName = "Change Weapon";
}

EBTNodeResult::Type UFCTChangeWeaponTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if(!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;

	const auto WeaponComponent = Pawn->FindComponentByClass<UFCGWeaponComponent>();

	if(WeaponComponent)
	{
		Blackboard->SetValueAsFloat(EquipingTime.SelectedKeyName, WeaponComponent->GetEquipingTime());
		WeaponComponent->NextWeapon();
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
