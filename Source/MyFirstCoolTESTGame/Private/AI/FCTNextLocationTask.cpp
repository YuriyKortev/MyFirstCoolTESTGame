// MyFirstCoolTESTGame. All rights RESRVED!


#include "AI/FCTNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UFCTNextLocationTask::UFCTNextLocationTask()
{
	NodeName = "NextLocation";
}

EBTNodeResult::Type UFCTNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if(!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;

	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if(!NavSys) return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	auto Location = Pawn->GetActorLocation();
	
	if(!SelfCenter)
	{
		const auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		if(!CenterActor) return EBTNodeResult::Failed;
		Location = CenterActor->GetActorLocation();
	}
	
	const bool IsFound = NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
	if(!IsFound) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;
}
