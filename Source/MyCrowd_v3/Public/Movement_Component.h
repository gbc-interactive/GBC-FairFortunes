#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Movement_Component.generated.h"


/// <summary>
/// This class handles character movement. It can receive directional input and a toggle for whether or not the character should be sprinting and perform appropriate movements.
/// </summary>
UCLASS( ClassGroup=(CharacterBehaviourComponents), meta=(BlueprintSpawnableComponent) )
class MYCROWD_V3_API UMovement_Component : public UActorComponent
{
	GENERATED_BODY()

private:
	APawn* m_selfPawn;

	UCharacterMovementComponent* m_charMovementComp;

	bool m_isSprinting;

	float m_currentStamina;

	float m_timeSinceSprintStart;

	float m_currentMoveSpeed;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float walkingSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float sprintingSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))
	float adsMovementSpeedMultiplierPercent = 70.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float sprintMaxDurationSeconds = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float staminaRechargeCooldownSeconds = 1.0f;

private:
	void RechargeStamina(float _deltaTime);

	void OnBeginADS();

	void OnEndADS();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UMovement_Component();


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void PerformMovement(FVector2D _direction);

	UFUNCTION(BlueprintCallable)
	void StartSprinting();

	UFUNCTION(BlueprintCallable)
	void StopSprinting();
};
