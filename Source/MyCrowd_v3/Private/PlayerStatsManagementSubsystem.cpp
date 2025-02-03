// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatsManagementSubsystem.h"
#include "FFLogger.h"

void UPlayerStatsManagementSubsystem::InitializeSubsystemData(const UPlayerAbilityStatsData* playerData)
{
	playerStats = playerData;

	DataLoadCompleteEvent.Broadcast(this);

	DataLoadCompleteEvent.RemoveAll(&DataLoadCompleteEvent);
}
