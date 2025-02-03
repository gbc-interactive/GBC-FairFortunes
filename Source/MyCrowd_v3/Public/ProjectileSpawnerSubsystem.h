#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ProjectileBase.h"
#include "ProjectileSpawnerSubsystem.generated.h"

class UPlayerStatsManagementSubsystem;

/// <summary>
/// This class defines a world subsystem that will be responsible for the lifetime of projectiles that a player can spawn.
/// It creates object pools of the projectiles on initialization and manages spawning from and de-spawning back to the pool.
/// </summary>
UCLASS()
class MYCROWD_V3_API UProjectileSpawnerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	const TSubclassOf<class AProjectileBase>* m_gunProjectile;
	const TSubclassOf<class AProjectileBase>* m_grenadeProjectile;

	TArray<AProjectileBase*> m_gunProjectilePool;
	TArray<AProjectileBase*> m_grenadeProjectilePool;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void SpawnGunProjectile(FVector _location, FRotator _rotation);

	
	UFUNCTION(BlueprintCallable)
	void DespawnGunProjectile(AProjectileBase* projectileToDespawn);

private:
	void ActivateActor(AActor* actorToActivate);
	void DeactivateActor(AActor* actorToDeactivate);
	void OnPlayerDataLoaded(const UPlayerStatsManagementSubsystem* dataManager);
};
