// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPoolable.generated.h"

UINTERFACE(MinimalAPI)
class UPoolable: public UInterface
{
	GENERATED_BODY()
};

class MYCROWD_V3_API IPoolable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Poolable")
	void OnSpawnFromPool(const FVector& _worldSpawnLocation, const FRotator& _worldForwardDirection);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Poolable")
	void OnReturnToPool();
};
