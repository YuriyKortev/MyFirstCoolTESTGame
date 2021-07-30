// MyFirstCoolTESTGame. All rights RESRVED!


#include "AI/Services/FCTFireService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/FCTAICharacter.h"
#include "Components/FCGWeaponComponent.h"


UFCTFireService::UFCTFireService()
{
	NodeName = "Fire";
}

void UFCTFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto FCTCharacter = Cast<AFCTAICharacter>(Controller->GetPawn());

	const bool HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if(Controller)
	{
		const auto WeaponComponent = FCTCharacter->FindComponentByClass<UFCGWeaponComponent>();
		if(WeaponComponent)
		{
			if(HasAim)
			{
				FCTCharacter->StartAim();
				WeaponComponent->StartFire();
			}else
			{
				WeaponComponent->EndFire();
				FCTCharacter->EndAim();
			}
		}
	}

	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
