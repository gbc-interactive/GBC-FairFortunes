// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoolSubsystem.h"
#include "IPoolable.h"


void USpawnPoolSubsystem::SpawnFromPool(TSubclassOf<AActor> _actorClass, const FVector& _position, const FRotator& _rotation, AActor*& spawnedActor)
{
	spawnedActor = SpawnFromPool<AActor>(_actorClass, _position, _rotation);
}

void USpawnPoolSubsystem::ReturnToPool(AActor* _actor)
{
	const UClass* actorClass = _actor->GetClass();

	if (actorClass->ImplementsInterface(UPoolable::StaticClass()))
	{
		IPoolable::Execute_OnReturnToPool(_actor);

		FPoolArray* actorPoolStruct = m_actorPoolCollection.Find(actorClass);
		actorPoolStruct->Add(_actor);
	}
	else
	{
		_actor->Destroy();
	}
}


template<typename T>
T* USpawnPoolSubsystem::SpawnFromPool(TSubclassOf<AActor> _actorClass, const FVector& _position, const FRotator& _rotation)
{
	T* spawnedActor = nullptr;

	if (_actorClass.Get()->ImplementsInterface(UPoolable::StaticClass()))
	{
		FPoolArray& actorPoolStruct = m_actorPoolCollection.FindOrAdd(_actorClass);

		if (actorPoolStruct.IsEmpty())
		{
			FActorSpawnParameters spawnParams;

			spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			spawnedActor = GetWorld()->SpawnActor<T>(_actorClass, _position, _rotation, spawnParams);
			//spawnedActor = GetWorld()->SpawnActor(_actorClass->StaticClass(), NAME_None, _position, _rotation, spawnParams);
		}
		else
		{
			spawnedActor = CastChecked<T>(actorPoolStruct.Pop());
			spawnedActor->SetActorLocationAndRotation(_position, _rotation);

		}

		IPoolable::Execute_OnSpawnFromPool(spawnedActor, _position, _rotation);
	}

	return spawnedActor;
}
