// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/FCGWeaponComponent.h"
#include "FCTPlayerHudWidget.generated.h"

class UFCGHealthComponent;

/**
 * 
 */
UCLASS()
class MYFIRSTCOOLTESTGAME_API UFCTPlayerHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintCallable, Category="UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& OutUIData) const;

	UFUNCTION(BlueprintCallable, Category="Ammo")
	FString GetCurrentWeaponAmmoData() const;

protected:
	UPROPERTY()
	UFCGHealthComponent* HealthComponent;

	UPROPERTY()
	UFCGWeaponComponent* WeaponComponent;
};
