// MyFirstCoolTESTGame. All rights RESRVED!


#include "FCTGameModeBase.h"

#include "Player/FCTCharacter.h"
#include "Player/FCTCPlayerController.h"

AFCTGameModeBase::AFCTGameModeBase()
{
	DefaultPawnClass = AFCTCharacter::StaticClass();
	PlayerControllerClass = AFCTCPlayerController::StaticClass();
}
