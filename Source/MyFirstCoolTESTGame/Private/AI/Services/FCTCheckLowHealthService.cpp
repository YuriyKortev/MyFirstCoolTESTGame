// MyFirstCoolTESTGame. All rights RESRVED!


#include "AI/Services/FCTCheckLowHealthService.h"
#include "Components/FCGHealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UFCTCheckLowHealthService::UFCTCheckLowHealthService()
{
	NodeName = "CheckLowHealth";
}

void UFCTCheckLowHealthService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if(Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto Pawn = Controller->GetPawn();

		const auto HealthComponent = Pawn->FindComponentByClass<UFCGHealthComponent>();
		if(HealthComponent)
		{
			Blackboard->SetValueAsBool(LowHealth.SelectedKeyName,
				HealthComponent->GetHealthPercent() < HealthPercentThreshold);
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
