// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MYCROWD_V3_API ProjectileSpawnerSubsystem : public UGameInstanceSubsystem
{
private:

	TArray<TSubclassOf<AActor>> m_actorCollection;


public:
	ProjectileSpawnerSubsystem();
	~ProjectileSpawnerSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
