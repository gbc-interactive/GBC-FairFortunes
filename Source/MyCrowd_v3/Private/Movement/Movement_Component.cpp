#include "Movement/Movement_Component.h"
#include "Kismet/KismetMathLibrary.h"

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

	float currentFrameStaminaRecoveryAmount = _deltaTime / staminaRechargeCooldownSeconds;

	m_currentStamina = FMath::Clamp(m_currentStamina + currentFrameStaminaRecoveryAmount, 0.0f, 1.0f);
}

void UMovement_Component::BeginPlay()
{
	Super::BeginPlay();


	//Initialise all our references and variables
	m_selfPawn = Cast<APawn>(GetOwner());
	m_charMovementComp = Cast<UCharacterMovementComponent>(m_selfPawn->GetMovementComponent());
	m_isSprinting = false;
	m_currentStamina = 1.0f;
}

// Called every frame
void UMovement_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_isSprinting == true)
	{
		float currentFrameStaminaReduction = DeltaTime / sprintMaxDurationSeconds;

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
	m_charMovementComp->MaxWalkSpeed = sprintingSpeed;
}

void UMovement_Component::StopSprinting()
{
	m_charMovementComp->MaxWalkSpeed = walkingSpeed;
}

