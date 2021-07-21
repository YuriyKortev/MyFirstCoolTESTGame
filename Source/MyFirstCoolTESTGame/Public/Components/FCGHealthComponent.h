// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FCGHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTCOOLTESTGAME_API UFCGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFCGHealthComponent();

	
	float GetHealth() const
	{
		return Health;
	}

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	UFUNCTION(BlueprintCallable, Category="Health")
	float GetHealthPercent() const { return Health/ MaxHealth; }


	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health", meta=(ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health")
	bool AutoRecovery = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health", meta=(ClampMin = "0.0", ClampMax = "10.0", EditCondition = "AutoRecovery"))
	float RecoveryDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health", meta=(ClampMin = "0.0", ClampMax = "2.0", EditCondition = "AutoRecovery"))
	float RecoveryRate = 0.3f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health", meta=(ClampMin = "0.0", ClampMax = "50.0", EditCondition = "AutoRecovery"))
	float RecoveryStep = 5.0f;
	
private:
	float Health = 0.0f;
	
	UFUNCTION()
	void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

	void OnRecoveryIter();
	FTimerHandle RecoveryTimer;

	void SetHealth(float HealthUpdate);
};
