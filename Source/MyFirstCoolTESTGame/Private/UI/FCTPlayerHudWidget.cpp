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

FString UFCTPlayerHudWidget::GetCurrentWeaponAmmoData() const
{
	if(!WeaponComponent) return "0 / 0";
	
	return WeaponComponent->GetTextCurrentAmmo();
}
