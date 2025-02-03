#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CartInteractionSubsystem.generated.h"

class UPlayerStatsManagementSubsystem;

/**
 * Manages interactions between player character and the various carts in the game.
 */
UCLASS(Blueprintable)
class MYCROWD_V3_API UCartInteractionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	TEnumAsByte<ECollisionChannel> m_InteractionRaycastChannel;
	float m_playerInteractionRange;

public:
	// Overrides
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;


	// API
	UFUNCTION(BlueprintCallable)
	void RequestInteractionWithCart(AActor* interactor);

private:
	void OnPlayerDataLoaded(const UPlayerStatsManagementSubsystem* dataManager);
};
