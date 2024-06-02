// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraControls/CameraControl_Component.h"

// Sets default values for this component's properties
UCameraControl_Component::UCameraControl_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraControl_Component::BeginPlay()
{
	Super::BeginPlay();

	m_pawn = Cast<APawn>(GetOwner());

}


// Called every frame
void UCameraControl_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	//RotationInterpolation

	if(useSmoothRotation == true)
	{
		if(accumulatedRotationInput.Length() > stoppingTolerance)
		{
			//creating variables for Yaw Input
			float cameraSpeed = DeltaTime * cameraRotationSpeed;
			float cameraRotationInputX = accumulatedRotationInput.X * cameraSpeed;
			float cameraRotationInputY = accumulatedRotationInput.Y * cameraSpeed;

			//adding to Yaw
			m_pawn->AddControllerYawInput(cameraRotationInputX);

			//setting accumulatedRotationInput
			accumulatedRotationInput.X = accumulatedRotationInput.X - cameraRotationInputX;

			//Setting Pitch Input
			if(invertYAxis == true)
			{
				//adding to Pitch
				m_pawn->AddControllerPitchInput(cameraRotationInputY * -1.0f);
				//setting accumulatedRotationInput
				accumulatedRotationInput.Y = accumulatedRotationInput.Y - (cameraRotationInputY * -1.0f);
			}
			else
			{
				//adding to Pitch
				m_pawn->AddControllerPitchInput(cameraRotationInputY);
				//setting accumulatedRotationInput
				accumulatedRotationInput.Y = accumulatedRotationInput.Y - cameraRotationInputY;
			}

		}
	}


}

void UCameraControl_Component::AddRotationInput(FVector2D actionValue)
{

	//Setting input vector
	FVector2D inputVector = lookSensitivity * actionValue;

	if(useSmoothRotation == true)
	{
		accumulatedRotationInput.X = inputVector.X + accumulatedRotationInput.X;
		accumulatedRotationInput.Y = inputVector.Y + accumulatedRotationInput.Y;
	}
	else
	{
		m_pawn->AddControllerYawInput(inputVector.X);

		if(invertYAxis == true)
		{
			m_pawn->AddControllerPitchInput(inputVector.Y * -1.0f);
		}
		else
		{
			m_pawn->AddControllerPitchInput(inputVector.Y);
		}

	}

}

void UCameraControl_Component::ToggleSmoothRotation()
{
	useSmoothRotation = !useSmoothRotation;
	accumulatedRotationInput = FVector2D{0.0f, 0.0f};
}

