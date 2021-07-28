// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "Player/FCTCharacter.h"
#include "FCTAICharacter.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCTAICharacter : public AFCTCharacter
{
	GENERATED_BODY()

public:
	AFCTAICharacter();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;
};
