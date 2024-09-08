#include "ProjectileSpawnerSubsystem.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <FFLogger.h>

void UProjectileSpawnerSubsystem::InitializeSubsystem(TSubclassOf<class AProjectileBase> gunProjectileClass, int gunProjectilePoolSize, TSubclassOf<class AProjectileBase> grenadeProjectileClass, int grenadeProjectilePoolSize)
{
	gunProjectilePool = TArray<AProjectileBase*>();
	grenadeProjectilePool = TArray<AProjectileBase*>();

	gunProjectilePool.Reserve(gunProjectilePoolSize);
	grenadeProjectilePool.Reserve(grenadeProjectilePoolSize);

	for (int i = 0; i < gunProjectilePoolSize; i++)
	{
		AProjectileBase* gunProjectile = (AProjectileBase*) GetWorld()->SpawnActor(gunProjectileClass);
		DeactivateActor(gunProjectile);
		gunProjectilePool.Add(gunProjectile);
	}

	/*for(int i = 0; i < grenadeProjectilePoolSize; i++)
	{
		AProjectileBase* grenadeProjectile = (AProjectileBase*) GetWorld()->SpawnActor(grenadeProjectileClass);
		DeactivateActor(grenadeProjectile);
		grenadeProjectilePool.Add(grenadeProjectile);
	}*/
}


void UProjectileSpawnerSubsystem::SpawnGunProjectile(FVector _location, FRotator _rotation)
{
	FFLogger::LogMessage(LogMessageSeverity::Debug, "Spawning bullet projectile");

	if(gunProjectilePool.Num() > 0)
	{
		AProjectileBase* actorToSpawn = gunProjectilePool.Pop(false);

		actorToSpawn->SetActorLocation(_location);
		actorToSpawn->FindComponentByClass<UProjectileMovementComponent>()->Velocity = _rotation.Vector() * actorToSpawn->projectileSpeed;

		FFLogger::LogMessage(LogMessageSeverity::Debug, "Spawning " + actorToSpawn->GetActorNameOrLabel());

		ActivateActor(actorToSpawn);


		actorToSpawn->Execute_OnSpawnFromPool(actorToSpawn, _location, _rotation);
	}
	else
	{
		//why is the pool empty?? this should not happen
	}
}


void UProjectileSpawnerSubsystem::DespawnGunProjectile(AProjectileBase* projectileToDespawn)
{
	DeactivateActor(projectileToDespawn);
	gunProjectilePool.Push(projectileToDespawn);

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
	comp->bSimulationEnabled = false;

}