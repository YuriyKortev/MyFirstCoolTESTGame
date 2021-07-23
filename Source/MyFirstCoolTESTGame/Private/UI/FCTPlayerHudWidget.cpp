// MyFirstCoolTESTGame. All rights RESRVED!


#include "UI/FCTPlayerHudWidget.h"
#include "Components/FCGHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerHUD, All, All)

bool UFCTPlayerHudWidget::Initialize()
{
	Super::Initialize();

	const auto Player = GetOwningPlayerPawn();
	if(!Player) return 0.0f;

	const auto HealthBaseComponent = Player->GetComponentByClass(UFCGHealthComponent::StaticClass());
	const auto WeaponBaseComponent = Player->GetComponentByClass(UFCGWeaponComponent::StaticClass());
	HealthComponent = Cast<UFCGHealthComponent>(HealthBaseComponent);
	WeaponComponent = Cast<UFCGWeaponComponent>(WeaponBaseComponent);
	if(HealthComponent && WeaponComponent)
	{
		return true;
	}
	return false;
	
}

float UFCTPlayerHudWidget::GetHealthPercent() const
{

	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool UFCTPlayerHudWidget::GetCurrentWeaponUIData(FWeaponUIData& OutUIData) const
{
	if(!WeaponComponent) return false;
	
	return WeaponComponent->GetCurrentUIData(OutUIData);
}

bool UFCTPlayerHudWidget::GetCurrentAmmoData(FAmmoData& OutAmmoData) const
{
	if(!WeaponComponent) return false;
	
	return WeaponComponent->GetCurrentAmmoData(OutAmmoData);
}

bool UFCTPlayerHudWidget::IsPlayerAlive() const
{
	if(!HealthComponent) return false;

	return !HealthComponent->IsDead();
}

bool UFCTPlayerHudWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();

	return Controller && Controller->GetStateName() == NAME_Spectating;
}

