#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IPoolable.h"
#include "ProjectileBase.generated.h"

UCLASS(Blueprintable)
class MYCROWD_V3_API AProjectileBase : public AActor, public IPoolable
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float projectileSpeed;

public:
	AProjectileBase();

};