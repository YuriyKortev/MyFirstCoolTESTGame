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
	bool GetCurrentAmmoData(FAmmoData& OutAmmoData) const;

	UFUNCTION(BlueprintCallable, Category="Character")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category="Character")
	bool IsPlayerSpectating() const;

protected:
	UPROPERTY()
	UFCGHealthComponent* HealthComponent;

	UPROPERTY()
	UFCGWeaponComponent* WeaponComponent;
};
