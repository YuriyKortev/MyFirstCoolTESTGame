// MyFirstCoolTESTGame. All rights RESRVED!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FCGBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class MYFIRSTCOOLTESTGAME_API AFCGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AFCGBaseWeapon();

	virtual void Fire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;
	
	virtual void BeginPlay() override;
};
