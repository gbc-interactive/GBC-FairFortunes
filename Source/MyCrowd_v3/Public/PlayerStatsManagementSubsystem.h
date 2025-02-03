// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PlayerAbilityStatsData.h"
#include "PlayerStatsManagementSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(DataLoadCompleteDelegate, const UPlayerStatsManagementSubsystem*)

UCLASS(Blueprintable)
class MYCROWD_V3_API UPlayerStatsManagementSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Player Ability Stats Data"))
	const UPlayerAbilityStatsData* playerStats;

public:
	DataLoadCompleteDelegate DataLoadCompleteEvent;
	
public:
	UFUNCTION(BlueprintCallable)
	void InitializeSubsystemData(const UPlayerAbilityStatsData* playerData);

	inline const FPlayerMovementStats* GetMovementStats() const { return &playerStats->movementStats; }

	inline const FPlayerInteractionStats* GetInteractionStats() const { return &playerStats->interactionStats; }

	inline const FPlayerWeaponStats* GetWeaponStats() const { return &playerStats->weaponStats; }

	inline const FProjectileSpawnerSystemData* GetProjectileSpawnerSystemData() const { return &playerStats->projectileSpawnerSystemData; }

	inline const FCameraData* GetCameraData() const { return &playerStats->cameraData; }
};
