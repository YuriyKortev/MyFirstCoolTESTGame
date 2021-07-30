// MyFirstCoolTESTGame. All rights RESRVED!


#include "AI/Services/FCTFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/FCTAIPerceptionComponent.h"

UFCTFindEnemyService::UFCTFindEnemyService()
{
	NodeName = "FindEnemy";
}

void UFCTFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = Controller->FindComponentByClass<UFCTAIPerceptionComponent>();
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
