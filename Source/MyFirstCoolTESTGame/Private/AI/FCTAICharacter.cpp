// MyFirstCoolTESTGame. All rights RESRVED!


#include "AI/FCTAICharacter.h"

#include "AI/FCTAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AFCTAICharacter::AFCTAICharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AFCTAIController::StaticClass();
	
	bUseControllerRotationYaw = false;

	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}
