// MyFirstCoolTESTGame. All rights RESRVED!


#include "AI/FCTAIController.h"

#include "AI/FCTAICharacter.h"
#include "Components/FCTAIPerceptionComponent.h"

AFCTAIController::AFCTAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UFCTAIPerceptionComponent>("AIPerceptionComponent");

	SetPerceptionComponent(*AIPerceptionComponent);
}

void AFCTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto FCTCharacter = Cast<AFCTAICharacter>(InPawn);
	if(FCTCharacter)
	{
		RunBehaviorTree(FCTCharacter->BehaviorTree);
	}
	
}

void AFCTAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto AimActor = AIPerceptionComponent->GetClosestEnemy();
	SetFocus(AimActor);
}
