#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SpawnPoolSubsystem.generated.h"

USTRUCT()
struct FPoolArray {
	GENERATED_BODY()


	UPROPERTY()
	TArray<AActor*> m_actorPool;

public:
	bool IsEmpty() const { return m_actorPool.IsEmpty(); }
	AActor* Pop() { return m_actorPool.Pop(); }
	void Add(AActor* _actor) { m_actorPool.Add(_actor); }
};

UCLASS()
class MYCROWD_V3_API USpawnPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	TMap<UClass*, FPoolArray> m_actorPoolCollection;

public:

	UFUNCTION(BlueprintCallable, Category = "SpawnPool", meta=(DeterminesOutputType="_actorClass", DynamicOutputParam="spawnedActor"))
	void SpawnFromPool(TSubclassOf<AActor> _actorClass, const FVector& _position, const FRotator& _rotation, AActor*& spawnedActor);

	template<typename T>
	T* SpawnFromPool(TSubclassOf<AActor> _actorClass, const FVector& _position, const FRotator& _rotation);

	UFUNCTION(BlueprintCallable, Category = "SpawnPool")
	void ReturnToPool(AActor* _actor);
	
};