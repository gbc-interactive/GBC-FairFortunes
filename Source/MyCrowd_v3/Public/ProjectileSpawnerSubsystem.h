#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ProjectileBase.h"
#include "ProjectileSpawnerSubsystem.generated.h"

/// <summary>
/// This class defines a world subsystem that will be responsible for the lifetime of projectiles that a player can spawn.
/// It creates object pools of the projectiles on initialization and manages spawning from and de-spawning back to the pool.
/// </summary>
UCLASS()
class MYCROWD_V3_API UProjectileSpawnerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	TArray<AProjectileBase*> gunProjectilePool;
	TArray<AProjectileBase*> grenadeProjectilePool;

public:
	void InitializeSubsystem(TSubclassOf<class AProjectileBase> gunProjectileClass, int gunProjectilePoolSize, TSubclassOf<class AProjectileBase> grenadeProjectileClass, int grenadeProjectilePoolSize);
	void SpawnGunProjectile(FVector _location, FRotator _rotation);
	UFUNCTION(BlueprintCallable)
	void DespawnGunProjectile(AProjectileBase* projectileToDespawn);

private:
	void ActivateActor(AActor* actorToActivate);
	void DeactivateActor(AActor* actorToDeactivate);
};
