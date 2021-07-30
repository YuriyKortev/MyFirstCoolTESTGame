// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FCTCheckAmmoService.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API UFCTCheckAmmoService : public UBTService
{
	GENERATED_BODY()
	
public:
	UFCTCheckAmmoService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammo")
	FBlackboardKeySelector ClipEmpty;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammo")
	FBlackboardKeySelector AmmoEmpty;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammo")
	FBlackboardKeySelector IsLastWeapon;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
