// MyFirstCoolTESTGame. All rights RESRVED!


#include "Components/FCTAIPerceptionComponent.h"
#include "AIController.h"
#include "Components/FCGHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* UFCTAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PerceivedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
	if(PerceivedActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if(!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return nullptr;
	
	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for(const auto PerceiveActor : PerceivedActors)
	{
		const auto HealthComponent = PerceiveActor->FindComponentByClass<UFCGHealthComponent>();
		
		if(HealthComponent && !HealthComponent->IsDead()) // TODO: Check is enemy
		{
			const auto CurrentDistance = (PerceiveActor->GetActorLocation()
				- Pawn->GetActorLocation()).Size();

			if(CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PerceiveActor;
			}
		}
	}

	return BestPawn;
}
