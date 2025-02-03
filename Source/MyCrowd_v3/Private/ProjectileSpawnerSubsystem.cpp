#include "ProjectileSpawnerSubsystem.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FFLogger.h"
#include "PlayerStatsManagementSubsystem.h"
#include <Engine/AssetManager.h>

void UProjectileSpawnerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UPlayerStatsManagementSubsystem* dataManager = (UPlayerStatsManagementSubsystem*) Collection.InitializeDependency(UPlayerStatsManagementSubsystem::StaticClass());

	if (!dataManager)
	{
		return;
	}

	dataManager->DataLoadCompleteEvent.AddUObject(this, &UProjectileSpawnerSubsystem::OnPlayerDataLoaded);
}

void UProjectileSpawnerSubsystem::OnPlayerDataLoaded(const UPlayerStatsManagementSubsystem* dataManager)
{
	const FProjectileSpawnerSystemData* subsystemData = dataManager->GetProjectileSpawnerSystemData();

	m_gunProjectile = &subsystemData->projectileToSpawn_Gun;
	m_grenadeProjectile = &subsystemData->projectileToSpawn_Grenade;

	m_gunProjectilePool = TArray<AProjectileBase*>();
	m_grenadeProjectilePool = TArray<AProjectileBase*>();

	m_gunProjectilePool.Reserve(subsystemData->gunProjectilePoolSize);
	m_grenadeProjectilePool.Reserve(subsystemData->grenadeProjectilePoolSize);

	for (int i = 0; i < subsystemData->gunProjectilePoolSize; i++)
	{
		AProjectileBase* gunProjectile = (AProjectileBase*)GetWorld()->SpawnActor(m_gunProjectile->Get());
		DeactivateActor(gunProjectile);
		m_gunProjectilePool.Add(gunProjectile);
	}

	for (int i = 0; i < subsystemData->grenadeProjectilePoolSize; i++)
	{
		AProjectileBase* grenadeProjectile = (AProjectileBase*)GetWorld()->SpawnActor(m_grenadeProjectile->Get());
		DeactivateActor(grenadeProjectile);
		m_grenadeProjectilePool.Add(grenadeProjectile);
	}
}


void UProjectileSpawnerSubsystem::SpawnGunProjectile(FVector _location, FRotator _rotation)
{
	FFLogger::LogMessage(LogMessageSeverity::Debug, "Spawning bullet projectile");

	if(m_gunProjectilePool.Num() > 0)
	{
		AProjectileBase* actorToSpawn = m_gunProjectilePool.Pop(false);

		actorToSpawn->SetActorLocation(_location);
		actorToSpawn->FindComponentByClass<UProjectileMovementComponent>()->Velocity = _rotation.Vector() * actorToSpawn->projectileSpeed;

		FFLogger::LogMessage(LogMessageSeverity::Debug, "Spawning " + actorToSpawn->GetActorNameOrLabel());

		ActivateActor(actorToSpawn);


		actorToSpawn->Execute_OnSpawnFromPool(actorToSpawn, _location, _rotation);
	}
	else
	{
		//why is the pool empty?? this should not happen
		FFLogger::LogMessage(LogMessageSeverity::Warning, "Projectile Spawner object pool empty, spawning new actor and adding it to pool");

		AProjectileBase* gunProjectile = (AProjectileBase*)GetWorld()->SpawnActor(m_gunProjectile->Get());
		m_gunProjectilePool.Add(gunProjectile);
	}
}


void UProjectileSpawnerSubsystem::DespawnGunProjectile(AProjectileBase* projectileToDespawn)
{
	DeactivateActor(projectileToDespawn);
	m_gunProjectilePool.Push(projectileToDespawn);

	projectileToDespawn->Execute_OnReturnToPool(projectileToDespawn);
}


void UProjectileSpawnerSubsystem::ActivateActor(AActor* actorToActivate)
{
	actorToActivate->SetActorHiddenInGame(false);
	//actorToActivate->SetActorEnableCollision(true);
	UProjectileMovementComponent* comp = actorToActivate->FindComponentByClass<UProjectileMovementComponent>();
	comp->bSimulationEnabled = true;

}

void UProjectileSpawnerSubsystem::DeactivateActor(AActor* actorToDeactivate)
{
	actorToDeactivate->SetActorHiddenInGame(true);
	actorToDeactivate->SetActorLocation(FVector::ZeroVector);
	//actorToDeactivate->SetActorEnableCollision(false);
	UProjectileMovementComponent* comp = actorToDeactivate->FindComponentByClass<UProjectileMovementComponent>();
	if (!comp)
	{
		return;
	}
	comp->bSimulationEnabled = false;

}