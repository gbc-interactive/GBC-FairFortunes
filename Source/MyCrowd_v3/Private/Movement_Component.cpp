#include "Movement_Component.h"
#include "Kismet/KismetMathLibrary.h"
#include "CameraControl_Component.h"
#include "FFLogger.h"
#include "PlayerStatsManagementSubsystem.h"

// Sets default values for this component's properties
UMovement_Component::UMovement_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UMovement_Component::RechargeStamina(float _deltaTime)
{
	if (m_currentStamina >= 1.0f)
	{
		return;
	}

	float currentFrameStaminaRecoveryAmount = _deltaTime / m_staminaRechargeCooldownSeconds;

	m_currentStamina = FMath::Clamp(m_currentStamina + currentFrameStaminaRecoveryAmount, 0.0f, 1.0f);
}

void UMovement_Component::BeginPlay()
{
	Super::BeginPlay();

	FFLogger::LogMessage(LogMessageSeverity::Debug, "Init Movement Component");

	//Initialise all our references and variables
	m_selfPawn = Cast<APawn>(GetOwner());
	m_charMovementComp = Cast<UCharacterMovementComponent>(m_selfPawn->GetMovementComponent());

	const FPlayerMovementStats* movementStats = GetWorld()->GetSubsystem<UPlayerStatsManagementSubsystem>()->GetMovementStats();
	m_walkingSpeed = movementStats->walkSpeed;
	m_sprintingSpeed = movementStats->sprintSpeed;
	m_adsMovementSpeedMultiplierPercent = movementStats->MovementSpeedMultiplierADS;
	m_sprintMaxDurationSeconds = movementStats->sprintStaminaDuration;
	m_staminaRechargeCooldownSeconds = movementStats->staminaRechargeCooldown;

	m_isSprinting = false;
	m_currentStamina = 1.0f;
	m_currentMoveSpeed = m_walkingSpeed;

	m_selfPawn->GetComponentByClass<UCameraControl_Component>()->ADSBeginEvent.BindUObject(this, &UMovement_Component::OnBeginADS);
	m_selfPawn->GetComponentByClass<UCameraControl_Component>()->ADSEndEvent.BindUObject(this, &UMovement_Component::OnEndADS);
}

// Called every frame
void UMovement_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_isSprinting == true)
	{
		float currentFrameStaminaReduction = DeltaTime / m_sprintMaxDurationSeconds;

		m_currentStamina = FMath::Clamp(m_currentStamina - currentFrameStaminaReduction, 0.0f, 1.0f);

		if(m_currentStamina <= 0.0f)
		{
			StopSprinting();
		}
	}
	else
	{
		RechargeStamina(DeltaTime);
	}
}

void UMovement_Component::PerformMovement(FVector2D _direction)
{
	FRotator currentRotation = m_selfPawn->GetControlRotation();

	FVector rightDirection = UKismetMathLibrary::GetRightVector(currentRotation);
	FVector forwardDirection = UKismetMathLibrary::GetForwardVector(currentRotation);

	FVector movementDirection = rightDirection * _direction.X + forwardDirection * _direction.Y;

	movementDirection.Normalize();

	m_selfPawn->AddMovementInput(movementDirection);
}

void UMovement_Component::StartSprinting()
{
	FFLogger::LogMessage(LogMessageSeverity::Debug, "Start Sprinting");
	m_charMovementComp->MaxWalkSpeed = m_sprintingSpeed;
}

void UMovement_Component::StopSprinting()
{
	FFLogger::LogMessage(LogMessageSeverity::Debug, "Stop Sprinting");
	m_charMovementComp->MaxWalkSpeed = m_walkingSpeed;
}

void UMovement_Component::OnBeginADS()
{
	FFLogger::LogMessage(LogMessageSeverity::Debug, "Begin ADS movement speed slowed");
	m_charMovementComp->MaxWalkSpeed = m_walkingSpeed * (m_adsMovementSpeedMultiplierPercent / 100.0f);
}

void UMovement_Component::OnEndADS() {
	FFLogger::LogMessage(LogMessageSeverity::Debug, "End ADS movement speed returned to normal");
	m_charMovementComp->MaxWalkSpeed = m_walkingSpeed;
}
