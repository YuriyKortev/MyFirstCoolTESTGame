// MyFirstCoolTESTGame. All rights RESRVED!


#include "FCTGameModeBase.h"

#include "Player/FCTCharacter.h"
#include "Player/FCTCPlayerController.h"
#include "UI/FCGGameHUD.h"

AFCTGameModeBase::AFCTGameModeBase()
{
	DefaultPawnClass = AFCTCharacter::StaticClass();
	PlayerControllerClass = AFCTCPlayerController::StaticClass();
	HUDClass = AFCGGameHUD::StaticClass();
}
