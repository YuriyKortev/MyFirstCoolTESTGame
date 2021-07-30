// MyFirstCoolTESTGame. All rights RESRVED!


#include "AI/Services/FCTCheckAmmoService.h"
#include "Components/FCGWeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UFCTCheckAmmoService::UFCTCheckAmmoService()
{
	NodeName = "CheckAmmo";
}

void UFCTCheckAmmoService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto Pawn = Controller->GetPawn();

		const auto WeaponComponent = Pawn->FindComponentByClass<UFCGWeaponComponent>();

		FAmmoData CurrentWeaponAmmo;
		if (WeaponComponent && WeaponComponent->GetCurrentAmmoData(CurrentWeaponAmmo))
		{
			const bool BulletsCondition = CurrentWeaponAmmo.Bullets == 0;
			Blackboard->SetValueAsBool(IsLastWeapon.SelectedKeyName, WeaponComponent->IsLastWeapon());
			Blackboard->SetValueAsBool(ClipEmpty.SelectedKeyName, BulletsCondition);
			Blackboard->SetValueAsBool(AmmoEmpty.SelectedKeyName,
			                           BulletsCondition && CurrentWeaponAmmo.Clips == 0);
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
