// MyFirstCoolTESTGame. All rights RESRVED!


#include "UI/FCTPlayerHudWidget.h"
#include "Components/FCGHealthComponent.h"

float UFCTPlayerHudWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return 0.0f;

	const auto Component = Player->GetComponentByClass(UFCGHealthComponent::StaticClass());
	const auto HealthComponent = Cast<UFCGHealthComponent>(Component);

	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}
